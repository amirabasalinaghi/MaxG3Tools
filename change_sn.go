package main

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"strings"
)

const (
	prefix       = "1CG"
	skipSerial   = "1CGC0000000001"
	serialLength = 14
	//defaultSN    = "1CGCC0000C0000"
)

func patchSerials(content []byte, newSerial string) (int, error) {
	count := 0
	for i := 0; i <= len(content)-serialLength; i++ {
		if bytes.Equal(content[i:i+3], []byte(prefix)) {
			sn := content[i : i+serialLength]
			if bytes.Equal(sn, []byte(skipSerial)) {
				i += serialLength - 1
				continue
			}
			copy(content[i:i+serialLength], []byte(newSerial))
			count++
			i += serialLength - 1
		}
	}
	if count == 0 {
		return 0, fmt.Errorf("no serials replaced")
	}
	return count, nil
}

func findFirstBinFile() (string, error) {
	entries, err := os.ReadDir(".")
	if err != nil {
		return "", err
	}
	for _, entry := range entries {
		if !entry.IsDir() && strings.HasSuffix(strings.ToLower(entry.Name()), ".bin") {
			return entry.Name(), nil
		}
	}
	return "", fmt.Errorf("no .bin file found in current directory")
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	var fileName = ""

	defaultFile, err := findFirstBinFile()
	if len(defaultFile) > 0 {
		fmt.Printf("Enter filename [default: %s]: ", defaultFile)
		fileName, _ = reader.ReadString('\n')
		fileName = strings.TrimSpace(fileName)
		if fileName == "" {
			fileName = defaultFile
		}
	} else {
		fmt.Print("Enter filename: ")
		fileName, _ = reader.ReadString('\n')
		fileName = strings.TrimSpace(fileName)
		if fileName == "" {
			fileName = defaultFile
		}
	}

	if len(fileName) == 0 {
		fmt.Fprintln(os.Stderr, "file not defined:", err)
		os.Exit(1)
	}

	fmt.Print("Enter new serial number (must be 14 characters): ")
	newSerial, _ := reader.ReadString('\n')
	newSerial = strings.TrimSpace(newSerial)

	if len(newSerial) != serialLength {
		fmt.Fprintln(os.Stderr, "Invalid serial number format")
		os.Exit(1)
	}

	data, err := os.ReadFile(fileName)
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error reading file:", err)
		os.Exit(1)
	}

	count, err := patchSerials(data, newSerial)
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error patching serials:", err)
		os.Exit(1)
	}
	fmt.Printf("Replaced %d serial number(s)\n", count)

	outFile := fileName + ".sn_changed.bin"
	err = os.WriteFile(outFile, data, 0644)
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error writing file:", err)
		os.Exit(1)
	}
	fmt.Println("Patched file saved as:", outFile)
}
