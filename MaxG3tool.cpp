#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const string DEFAULT_KEY = "\xFE\x80\x1C\xB2\xD1\xEF\x41\xA6\xA4\x17\x31\xF5\xA0\x68\x24\xF0\x63\x66\x77\x2E\x73\x68";

vector<size_t> findPattern(string& content, string pattern, size_t offset = 0) {
    vector<size_t> locations;

    while ((offset = content.find(pattern, offset)) != string::npos) {
        locations.push_back(offset);
        offset += pattern.size();
    }

    return locations;
}

string openFile(string filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        throw runtime_error("Cannot open the file! " + filename);
    }
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    string fileContent(buffer.begin(), buffer.end());
    return fileContent;
}

void changeRegion(string& content, string region) {
    if (region.empty()) {
        throw invalid_argument("You must specify the char of the SN region!");
    }

    vector<string> regions = {"C", "B"};
    if (find(regions.begin(), regions.end(), region) == regions.end()) {
        throw invalid_argument("Wrong SN region!");
    }

    vector<size_t> locations = findPattern(content, "1CG", 0x1F000);
    if (!locations.empty()) {
        for (size_t location : locations) {
            content[location + 3] = region.at(0);
        }
        cout << "The region of the scooter has been changed to the specified: " + region << endl;
    } else {
        throw runtime_error("Serial number not found in file!");
    }
}

void replaceKey(string& content, string encKey = DEFAULT_KEY) {
    vector<size_t> locations = findPattern(content, "SCOOTER_VCU_xxG3");
    if (encKey.size() != 0x16) {
        throw runtime_error("The key is not 0x16 long!");
    }
    if (!locations.empty()) {
        for (size_t location : locations) {
            content.replace(location+0x20, 0x16, encKey);
        }
        cout << "The scooter key has been changed." << endl;
    } else {
        throw runtime_error("The scooter key could not be changed.");
    }
}

string extractOldKey(string oldDump) {
    vector<size_t> locations = findPattern(oldDump, "SCOOTER_VCU_xxG3");
    if (locations.empty()) {
        throw runtime_error("Cannot find the location of the key in the original dump!");
    }
    
    string key = oldDump.substr(locations[0]+0x20, 0x16);
    for (size_t key_offset : locations) {
        if (oldDump.substr(key_offset+0x20, 0x16) != key) {
            throw runtime_error("The memory dump contains different keys!");
        }
    }
    return key;
}

int main(int argc, char* argv[]) {
    cout << "ZT3Tools V3 | MIT License Copyright (c) 2025 ScooterTeam" << endl;
    if (argc != 3 && argc != 4) {
        cerr << "Usage: " << argv[0] << " <dump_filename> <option> [optional]" << endl;
        cerr << "Options: " << endl 
             << "changeregion {Z,U,E,D,A} - change SN region" << endl 
             << "key - change encrypting key to the default one" << endl
             << "verify - verify memory dump" << endl
             << "fixkey [og_dump_filename] - fix encrypting key" << endl;
        return 1;
    }

    string filename = argv[1];
    string user_option = argv[2];
    string optional_arg, fileContent;

    if (argc == 4) optional_arg = argv[3];

    try {
        fileContent = openFile(filename);
        if (user_option == "changeregion") {
            // change the SN region to the one specified by the user
            changeRegion(fileContent, optional_arg);
        } else if (user_option == "key") {
            // change encrypting key to the default one
            replaceKey(fileContent);
        } else if (user_option == "verify") {
            // verify if there are certain phrases in the memory dump file of the scooter
            if (findPattern(fileContent, "SCOOTER_VCU_xxG3").size() != 2 || findPattern(fileContent, "1CG", 0x1F000).size() != 2) {
                throw runtime_error("The dump memory is probably corrupted!");
            }
            cout << "Dump correct." << endl;
            return 0;
        } else if (user_option == "fixkey") {
            // find the location of the key in the old dump and copy it to the new one
            if (optional_arg.empty()) {
                throw invalid_argument("You must provide the location of the old dump!");
            }
            string oldKey = extractOldKey(openFile(optional_arg));
            replaceKey(fileContent, oldKey);
        } else {
            throw invalid_argument("Wrong option! " + user_option);
        }
    } catch (const exception& e) {
        cerr << "ERORR: " << e.what() << endl;
        return 1;
    }

    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "Cannot save the file!" << endl;
        return 1;
    }
    outFile.write(fileContent.data(), fileContent.size());
    outFile.close();

    return 0;
}