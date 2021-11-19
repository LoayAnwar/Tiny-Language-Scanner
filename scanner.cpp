#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

bool isReserved(string s) {
    map<string, bool> reserved;
    reserved["if"] = 1;
    reserved["then"] = 1;
    reserved["else"] = 1;
    reserved["end"] = 1;
    reserved["repeat"] = 1;
    reserved["until"] = 1;
    reserved["read"] = 1;
    reserved["write"] = 1;
    return reserved[s];
}

vector <vector<string>> string_parse(string tiny) {
    string scannedChar = "";
    vector <vector<string>> scanned(2);
     
    for (int i = 0; i < tiny.length(); i++) {
        if (isalpha(tiny[i])) {
            while(isalpha(tiny[i])){
                scannedChar += tiny[i];
                i++;
            }
            i--;
            scanned[0].push_back(scannedChar);
            if (isReserved(scannedChar)) {
                scanned[1].push_back("reserved");
            }
            else {
                scanned[1].push_back("identifier");
            }
            scannedChar = "";
        }
        else if (isdigit(tiny[i])) {
            while (isdigit(tiny[i])) {
                scannedChar += tiny[i];
                i++;
            }
            i--;
            scanned[0].push_back(scannedChar);
            scanned[1].push_back("number");
            scannedChar = "";
        }
        else if (isspace(tiny[i])) {
            continue;
        }
        else if (tiny[i] == '{') {
            while (tiny[i] != '}') {
                i++;
            }
        }
        else if (tiny[i] == ':' && tiny[i + 1] == '=') {
            scanned[0].push_back(":=");
            scanned[1].push_back("ASSIGN");
            i++;
        }
        else if (tiny[i] == '+') {
            scannedChar += tiny[i];
            scanned[0].push_back(scannedChar);
            scanned[1].push_back("PLUS");
            scannedChar = "";
        }
        else if (tiny[i] == '-') {
            scannedChar += tiny[i];
            scanned[0].push_back(scannedChar);
            scanned[1].push_back("MINUS");
            scannedChar = "";
        }
        else if (tiny[i] == '/') {
            scannedChar += tiny[i];
            scanned[0].push_back(scannedChar);
            scanned[1].push_back("DIVIDE");
            scannedChar = "";
        }
        else if (tiny[i] == '*') {
            scannedChar += tiny[i];
            scanned[0].push_back(scannedChar);
            scanned[1].push_back("MULTIPLY");
            scannedChar = "";
        }
        else if (tiny[i] == '=') {
            scannedChar += tiny[i];
            scanned[0].push_back(scannedChar);
            scanned[1].push_back("RELATION");
            scannedChar = "";
        }
        else if (tiny[i] == '<') {
            scannedChar += tiny[i];
            scanned[0].push_back(scannedChar);
            scanned[1].push_back("RELATION");
            scannedChar = "";
        }
        else if (tiny[i] == '(') {
            scannedChar += tiny[i];
            scanned[0].push_back(scannedChar);
            scanned[1].push_back("(");
            scannedChar = "";
        }
        else if (tiny[i] == ')') {
            scannedChar += tiny[i];
            scanned[0].push_back(scannedChar);
            scanned[1].push_back(")");
            scannedChar = "";
        }
        else if (tiny[i] == ';') {
            scannedChar += tiny[i];
            scanned[0].push_back(scannedChar);
            scanned[1].push_back("SEMI");
            scannedChar = "";
        }
    }
    return scanned;
}


string readFileIntoString(const string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
            << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

void fileOut(vector<vector<string>> s) {
    ofstream myfile;
    myfile.open("output.txt");
    for (int i = 0; i < s[0].size(); i++) {
        myfile << s[0][i] << ", " << s[1][i] << "\n";
    }
    myfile.close();
}

int main()
{

    string filename("input.txt");
    string file_contents;

    file_contents = readFileIntoString(filename);

    vector<vector<string>> scanned;

    scanned = string_parse(file_contents);

    fileOut(scanned);

    return 0;
}