#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

ofstream openOutputFile(string &filename, const string &mode = "a")
{
    ofstream file;
    if (mode == "a")
    {
        file.open(filename, ios::app);
    }
    else
    {
        file.open(filename, ios::out);
    }

    if (!file.is_open())
    {
        cout << "Failed to open file " << filename << endl;
    }
    return file;
}

// open file for reading
ifstream openInputFile(string &filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Failed to open file " << filename << endl;
    }
    return file;
}

void deleteLine(const string& filename, const string& str) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Failed to open file " << filename << endl;
        return;
    }

    stringstream ss;
    string line;
    while (getline(inputFile, line)) {
        if (line.find(str) != string::npos) {
            continue;
        }
        ss << line << endl;
    }
    inputFile.close();

    ofstream outputFile(filename);
    outputFile << ss.str();
    outputFile.close();
}

vector<string> splitString(const string& input, char delimiter) {
    vector<string> tokens;
    stringstream ss(input);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool checkDuplicate(ifstream& file, const string& keyword, const int pos) {
    string line;
    while (getline(file, line)) {
        vector<string> row = splitString(line, ',');
        if (row.size() > pos && row[pos] == keyword) {
            return true;
        }
    }
    return false;
}

string joinString(const vector<string>& strings, char delimiter) {
    string result;
    for (size_t i = 0; i < strings.size(); i++) {
        result += strings[i];
        if (i < strings.size() - 1) {
            result += delimiter;
        }
    }
    return result;
}