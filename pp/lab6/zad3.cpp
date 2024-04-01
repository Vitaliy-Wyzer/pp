#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

bool isEmailAddress(const std::string& str) {
    return str.find('@') != std::string::npos;
}

int filterEmailAddresses(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open input file: " << inputFile << std::endl;
        return 0;
    }

    std::ofstream outFile(outputFile);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open output file: " << outputFile << std::endl;
        inFile.close();
        return 0;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string token;
        while (iss >> token) {
            if (isEmailAddress(token)) {
                outFile << token << std::endl;
                break; // Found email, move to next line
            }
        }
    }

    inFile.close();
    outFile.close();

    return 1;
}

int main() {
    std::string inputFile = "in.txt";
    std::string outputFile = "out.txt";

    if (filterEmailAddresses(inputFile, outputFile)) {
        std::cout << "Filtered email addresses saved to " << outputFile << std::endl;
    } else {
        std::cerr << "Failed to filter email addresses." << std::endl;
    }

    return 0;
}
