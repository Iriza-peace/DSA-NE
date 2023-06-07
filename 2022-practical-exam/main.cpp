#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <fstream>

using namespace std;

string LOCATIONS_FILE = "locations.csv";
string CASES_FILE = "cases.csv";

ofstream openOutputFile(string &filename,const string& mode = "a")
{
    ofstream file;
    if(mode == "a"){
        file.open(filename, ios::app);
    }
    else{
        file.open(filename, ios::out);
    }

    if (!file.is_open())
    {
        cout << "Failed to open file " << filename << endl;
    }
    return file;
}

ifstream openInputFile(string &filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Failed to open file " << filename << endl;
    }
    return file;
}

void deleteLine(string &filename, string &str)
{
    ifstream inputFile = openInputFile(filename);
    ofstream outputFile;

    string line;
    stringstream ss;

    while (getline(inputFile, line))
    {
        if (line.find(str) != string::npos)
        {
            continue;
        }
        ss << line << endl;
    }
    inputFile.close();
    outputFile.open(filename);
    outputFile << ss.str();
    outputFile.close();
}

vector<string> splitString(string &input, char delimiter)
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

bool checkDuplicate(ifstream &file, string &keyword, const int &pos)
{
    string line;
    while (getline(file, line))
    {
        vector<string> row = splitString(line, ',');
        if (row[pos] == keyword)
        {
            return true;
        }
    }
    return false;
}

bool checkLineContains(ifstream& file, const string& lineToFind)
{
    string line;
    while (getline(file, line))
    {
        if (line.find(lineToFind) != string::npos)
        {
            return true;
        }
    }
    return false;
}


string joinString(const vector<string> &strings, char delimiter)
{
    string result;
    for (size_t i = 0; i < strings.size(); i++)
    {
        result += strings[i];
        if (i < strings.size() - 1)
        {
            result += delimiter;
        }
    }
    return result;
}

void addLocation(string &location)
{

    ofstream file = openOutputFile(LOCATIONS_FILE);
    ifstream inputFile = openInputFile(LOCATIONS_FILE);

    if (!checkDuplicate(inputFile, location, 0))
    {
        file << location << endl;
        cout << location << " is added to locations successfully." << endl;
    }
    else
    {
        cout << "Location already exists." << endl;
    }

    file.close();
    inputFile.close();
}

void listLocations()
{
    ifstream file = openInputFile(LOCATIONS_FILE);
    string location;
    while (getline(file, location))
    {
        cout << location << endl;
    }
    file.close();
}

void deleteLocation(string &location)
{
    ofstream file = openOutputFile(LOCATIONS_FILE);
    ifstream inputFile = openInputFile(LOCATIONS_FILE);
    if (checkDuplicate(inputFile, location, 0))
    {
        deleteLine(LOCATIONS_FILE, location);
        cout << "Location " << location << " successfully deleted" << endl;
    }
    else
    {
        cout << "Location " << location << " not found!" << endl;
    }

    file.close();
    inputFile.close();
}

void recordCasesOfADiseaseInALocation(string& location, string& disease, int& cases)
{
    ofstream casesOutputfile = openOutputFile(CASES_FILE);
    ifstream locationsInputFile = openInputFile(LOCATIONS_FILE);
    ifstream casesInputFile = openInputFile(CASES_FILE);

    if (!checkDuplicate(locationsInputFile, location, 0))
    {
        cout << "Location << " << location << "not found!" << endl;
    }
    else
    {
        if (checkLineContains(casesInputFile, location + ","+disease))
        {   
            casesInputFile.close();
            casesInputFile.open(CASES_FILE);

            vector<string> fileData;
            string line;
            
            while (getline(casesInputFile, line))
            {
                vector<string> row = splitString(line, ',');

                if (row[0] == location && row[1] == disease)
                {
                    row[2] = to_string(cases);
                    line = joinString(row, ',');
                }
                fileData.push_back(line);
            }
            casesOutputfile.close();
            casesOutputfile = openOutputFile(CASES_FILE, "w");
            for (size_t i = 0; i < fileData.size(); i++)
            {
                casesOutputfile << fileData[i] << endl;
            }
        }
        else
        {
            casesOutputfile << location << "," << disease << "," << cases << endl;
        }
        cout << "Disease recorded successfully" << endl;
    }
    casesInputFile.close();
    casesOutputfile.close();
    locationsInputFile.close();
}

void listDiseases(){
    ifstream casesInputFile = openInputFile(CASES_FILE);
    
    string line;
    vector<string> diseases;

    while(getline(casesInputFile, line)){
        vector<string> row = splitString(line,',');
        string disease = row[1];

        if(find(diseases.begin(),diseases.end(),disease) == diseases.end()){
            cout << disease << endl;
            diseases.push_back(disease);
        }
    }
}

void findWhereDiseaseExists(string& disease){
    ifstream casesInputFile = openInputFile(CASES_FILE);
    
    string line;
    while(getline(casesInputFile,line)){
        vector<string> row = splitString(line,',');
        if(row[1] == disease){
            cout << row[0] <<endl;
        }
    }
}

void calculateTotalCasesOfDisease(string& disease){
    ifstream casesInputFile = openInputFile(CASES_FILE);
    string line;
    int count = 0;
    while(getline(casesInputFile,line)){
        vector<string> row = splitString(line,',');
        if(row[1] == disease){
            count = count + stoi(row[2]);
        }
    }
    cout << "Total cases of '"<< disease << "' = " << count << endl;
}

void calculateTotalCasesOfDiseaseInALocation(string& disease, string& location){
    ifstream casesInputFile = openInputFile(CASES_FILE);
    ifstream locationsInputFile = openInputFile(LOCATIONS_FILE);
    if (!checkDuplicate(locationsInputFile, location, 0))
    {
        cout << "Location "<<location<<" not found" <<endl;
    }
    else{
        string line;
        int count = 0;
        while(getline(casesInputFile,line)){
            vector<string> row = splitString(line,',');
            if(row[0] == location && row[1] == disease){
                count = count + stoi(row[2]);
            }
        }
        cout << "Cases of '"<< disease << "' at "<<location<<" are: " << count << endl;
    }

}

void help()
{
    cout << " ===========================================================================" << endl;
    cout << " *                                   HELP MENU                              *" << endl;
    cout << " ===========================================================================" << endl;
    cout << " add <location>                          :Add a new location" << endl;
    cout << " delete <location>                       :Delete an existing location" << endl;
    cout << " record <location> <disease> <cases>     :Record a disease and it's cases" << endl;
    cout << " list locations                          :List all existing locations" << endl;
    cout << " list diseases                           :List existing diseases in locations" << endl;
    cout << " where <disease>                         :Find where disease exists" << endl;
    cout << " cases <location> <disease>              :Find cases of a disease in location" << endl;
    cout << " cases <disease>                         :Find total cases of a given disease" << endl;
    cout << " help                                    :Prints user manual" << endl;
    cout << " exit                                    :Exit the program" << endl;
    cout << " =============================================================================" << endl;
}

void invalidCommand(string correctCommand)
{
    cout << "Invalid command. Usage: " << correctCommand << endl;
}

int processCommands()
{
    cout << "Need a help? Type 'help' then press Enter key." << endl;

    string input;

    string command;

    do
    {
        cout << "Console >";
        getline(cin, input);

        for (size_t i = 0; i < input.length(); i++)
        {
            input[i] = tolower(input[i]);
        }

        istringstream iss(input);
        iss >> command;

        if (command == "add")
        {
            string location;
            if (iss >> location)
            {
                addLocation(location);
            }
            else
            {
                invalidCommand("add <location>");
            }
        }
        else if (command == "delete")
        {
            string location;
            if (iss >> location)
            {
                deleteLocation(location);
            }
            else
            {
                invalidCommand("delete <location>");
            }
        }
        else if (command == "list")
        {
            string keyword;
            iss >> keyword;
            if (keyword == "locations")
            {
                listLocations();
            }
            else if (keyword == "diseases"){
                listDiseases();
            }
            else
            {
                invalidCommand("list locations or list diseases");
            }
        }
        else if(command == "cases"){
            string keyword;
            string first_keyword;
            string second_keyword;
            iss >> first_keyword >> second_keyword;

            if(!first_keyword.empty() && second_keyword.empty()){
                calculateTotalCasesOfDisease(first_keyword);
            }
            else if(!first_keyword.empty() && !second_keyword.empty()){
                calculateTotalCasesOfDiseaseInALocation(second_keyword,first_keyword);
            }
            else {
                invalidCommand("cases <disease> or cases <location> <disease>");
            }
            
        }
        else if(command == "where"){
            string keyword;
            if(iss >> keyword){
                findWhereDiseaseExists(keyword);
            }
            else{
                invalidCommand("where <disease>");
            }
        }
        else if (command == "record")
        {
            string location_keyword;
            string disease_keyword;
            int cases_keyword;

            iss >> location_keyword;
            iss >> disease_keyword;
            iss >> cases_keyword;
            if (!location_keyword.empty() && !disease_keyword.empty() && cases_keyword != 0)
            {
                recordCasesOfADiseaseInALocation(location_keyword, disease_keyword, cases_keyword);
            }
            else
            {
                invalidCommand("record <location> <disease> <cases>");
            }
        }
        else if (command == "help")
        {
            help();
        }
        else
        {
            if (command != "exit")
            {
                cout << "Invalid command. Below is the help option to provide you list of commands." << endl;
                help();
            }
        }
    } while (command != "exit");

    return 0;
}

int main()
{
    cout << " ==================================================== " << endl;
    cout << "*     Welcome to Disease Cases Reporting System!     *" << endl;
    cout << "*  **************************************** *" << endl;
    cout << "*                           *" << endl;
    cout << "* It is developed by 'NKUBITO Pacis' as practical *" << endl;
    cout << "* evaluation for the end of Year 3.               *" << endl;
    cout << " ====================================================" << endl;
    cout << "Starting Time: Mon May 29 22:35:00 CAT 2023" << endl;

    processCommands();
    return 0;
}
