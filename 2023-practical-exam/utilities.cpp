#include <iostream> // Input/output stream operations
#include <fstream>  // String stream operations
#include <vector>   // Vector container
#include <sstream>  // String stream operations
#include <regex>    //Regular expressions
#include <string>    // String operations

using namespace std;

bool isValidDateFormat(const string &date)
{
    // Regex pattern to match the date format "YYYY-MM-DD"
    regex pattern("\\d{4}-(0[1-9]|1[0-2])-\\d{2}");

    if (regex_match(date, pattern))
    {
        // Extract month from the date string
        int month = stoi(date.substr(5, 2));

        // Check if the month is greater than 12
        if (month > 12)
        {
            return false;
        }

        return true;
    }

    return false;
}

bool isNumeric(const string &str)
{
    // Regex pattern to match numeric characters
    regex pattern("\\d+");

    return regex_match(str, pattern);
}

//Open output file by providing filename and mode which is either append or write(a or w)
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

//split a string into a vector of strings
vector<string> splitString(const string &input, char delimiter)
{
    vector<string> tokens;
    stringstream ss(input);
    string token;
    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

//check if a file contains a specific keyword at a certain position
bool checkDuplicate(ifstream &file, const string &keyword, const int pos)
{
    string line;
    while (getline(file, line))
    {
        vector<string> row = splitString(line, ',');
        
        if (row.size() > pos && row[pos] == keyword)
        {
            return true;
        }
    }
    return false;
}