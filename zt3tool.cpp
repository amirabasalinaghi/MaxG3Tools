#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <dump_name>" << endl;
        return 1;
    }

    string filename = argv[1];
    
    ifstream file(filename, ios::binary);
    if (!file) {
        cerr << "Cannot open the file!" << endl;
        return 1;
    }
    
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    
    string fileContent(buffer.begin(), buffer.end());
    vector<size_t> locations;
    
    // change encrypting key to default one
    locations = findPattern(fileContent, "SCOOTER_VCU_xxU2");
    if (!locations.empty()) {
        for (size_t location : locations) {
            fileContent.replace(location+0x20, DEFAULT_KEY.size(), DEFAULT_KEY);
        }
        cout << "The scooter key has been changed." << endl;
    } else {
        cerr << "ERROR: The scooter key could not be changed." << endl;
    }

    // change SN region to US
    locations = findPattern(fileContent, "1K1", 0x1F000);
    if (!locations.empty()) {
        for (size_t location : locations) {
            fileContent[location + 3] = 'U';
        }
        cout << "The region of the scooter has been changed to the US." << endl;
    } else {
        cerr << "ERROR: Serial number not found in file!" << endl;
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