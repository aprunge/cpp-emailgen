#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;


void replaceOWithZero(std::vector<std::string>& vec) {
    // iterate through each string in the vector
    for (auto& str : vec) { // Note the use of reference (&) to modify the original string
        // iterate through each character in the string
        for (auto& c : str) { // Note the use of reference (&) to modify the original character
            if (c == 'o' || c == 'O') { // also check for capital O's
                c = '0';
            }
        }
    }
}

void replaceSWithFive(std::vector<std::string>& vec) {
    // iterate through each string in the vector
    for (auto& str : vec) { // Note the use of reference (&) to modify the original string
        // iterate through each character in the string
        for (auto& c : str) { // Note the use of reference (&) to modify the original character
            if (c == 's' || c == 'S') {
                c = '5';
            }
        }
    }
}

void makeEmailsLowercase(std::vector<string>& vec) {
    // iterate through each string in the vector
    for (auto& str : vec) { // Note the use of reference (&) to modify the original string
        // convert the string to lowercase using std::transform
        transform(str.begin(), str.end(), str.begin(), ::tolower);
    }
}

void randomizeStrings(std::vector<std::string>& vec) {
    std::random_device rd; // obtain a random seed from the hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> dis(0, 1); // define the distribution

    // iterate through each string in the vector
    for (auto& str : vec) { // Note the use of reference (&) to modify the original string
        // iterate through each character in the string
        for (auto& c : str) { // Note the use of reference (&) to modify the original character
            if (std::isalpha(c)) { // check if the character is a letter
                if (dis(gen) == 1) { // randomly choose whether to change to upper or lower case
                    c = std::toupper(c); // change to upper case
                } else {
                    c = std::tolower(c); // change to lower case
                }
            }
        }
    }
}

string combineStrings(const std::vector<std::string>& words) {
    std::string combined;
    for (const auto& word : words) { // iterate through each string in the vector
        combined += word; // append the current string to the output string
    }
    return combined;
}

void printUsage(const char* appName) {
    printf("\n");
    printf("Usage: %s [options] email_string\n", appName);
    printf("Options:\n");
    printf("  No parameters: Only changes word order.\n");
    printf("  One parameter: Changes caps.\n");
    printf("    -c: Disables all character capitalization.\n");
    printf("    -C: Enables random character capitalization.\n");
    printf("  Two parameters: Changes certain letters to numbers.\n");
    printf("    -n: Changes all 'o' characters to '0'.\n");
    printf("    -z: Changes all 's' characters to '2'.\n");
    printf("\n");
}

int main(int argc, char** argv) {
    string email;
    bool changeCaps = false;
    bool changeCapsRandom = false;
    bool changeOToZero = false;
    bool changeSToTwo = false;

    if (argc < 2) {
        cout << "Error: no parameters specified." << endl;
        printUsage(argv[0]);
        return 1;
    } 

    for (int i = 1; i < argc; ++i) {
        string param = argv[i];
        if (param == "-h") {
            printUsage(argv[0]);
            return 0;
        } else if (param == "-c") {
            changeCaps = true;
        } else if (param == "-C") {
            changeCapsRandom = true;
        } else if (param == "-n") {
            changeOToZero = true;
        } else if (param == "-z") {
            changeSToTwo = true;
        } else if (i == argc - 1) {
            email = param;
        } else {
            cout << "Error: invalid parameter specified." << endl;
            printUsage(argv[0]);
            return 1;
        }
    }

    string input = email;
    istringstream iss(input);
    vector<string> words;

    string word;
    while (iss >> word) {
        words.push_back(word);
    }

    string domain;
    int selection;

    cout << "Select email domain:" << std::endl;
    cout << "1. @gmail.com" << std::endl;
    cout << "2. @outlook.com" << std::endl;
    cout << "3. @protonmail.com" << std::endl;

    cin >> selection;

    switch (selection) {
        case 1:
            domain = "@gmail.com";
            break;
        case 2:
            domain = "@outlook.com";
            break;
        case 3:
            domain = "@protonmail.com";
            break;
        default:
            std::cout << "Invalid selection. Please try again." << std::endl;
            return 0;
    }

    cout << "You have selected " << domain << "." << endl;
    cout << "Is this correct? (y/n)" << endl;

    string confirmation;
    cin >> confirmation;

    if (confirmation == "y" || confirmation == "Y") {
        cout << "Confirmed. Your email domain is " << domain << "." << endl;
    } else {
        cout << "Selection cancelled. Please try again." << endl;
    }

    if(changeCapsRandom && changeOToZero && changeSToTwo) {
        randomizeStrings(words);
        replaceOWithZero(words);
        replaceSWithFive(words);
    }
    if(changeCaps && changeOToZero && changeSToTwo) {
        makeEmailsLowercase(words);
        replaceOWithZero(words);
        replaceSWithFive(words);
    }
    if (changeCaps && changeCapsRandom) {
        cout << "You can't remove capitalization and randomly capitalize at the same time." << endl; 
        return 1;
    } 
    if (changeCaps && changeOToZero) {
        makeEmailsLowercase(words);
        replaceOWithZero(words);
    } 
    if (changeCaps && changeSToTwo) {
        makeEmailsLowercase(words);
        replaceSWithFive(words);
    } 
    if (changeCapsRandom && changeOToZero) {
        randomizeStrings(words);
        replaceOWithZero(words);
    } 
    if (changeCapsRandom && changeSToTwo) {
        randomizeStrings(words);
    } 
    if (changeOToZero && changeSToTwo) {
        replaceSWithFive(words);
        replaceOWithZero(words);
    } 
    if (changeCaps) {
        makeEmailsLowercase(words);
    } 
    if (changeCapsRandom) {
        randomizeStrings(words);
    } 
    if (changeOToZero) {
        replaceOWithZero(words);
    } 
    if (changeSToTwo) {
        replaceSWithFive(words);
    } 
    if (!changeCaps && !changeCapsRandom && !changeOToZero && !changeSToTwo) {
        cout<< "Error: booleans unset!";
        return 1;
    }

    string combined = combineStrings(words);

    cout << "Email: " << combined << endl;
    cout << "Change caps: " << changeCaps << endl;
    cout << "Change caps randomly: " << changeCapsRandom << endl;
    cout << "Change o to 0: " << changeOToZero << endl;
    cout << "Change s to 2: " << changeSToTwo << endl;

    return 0;
}