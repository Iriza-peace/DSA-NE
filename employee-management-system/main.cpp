#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "utilities.cpp"

using namespace std;

string EMPLOYEES_FILE = "employees.csv";

void listEmployees()
{
    ifstream file = openInputFile(EMPLOYEES_FILE);
    string employee;
    int count = 0;
    while (getline(file, employee))
    {
        count++;
        cout << employee << endl;
    }
    if (count == 0)
    {
        cout << "No employees found" << endl;
    }
    file.close();
}

void registerEmployee(string &id, string &name, string &department)
{

    ofstream file = openOutputFile(EMPLOYEES_FILE);
    ifstream inputFile = openInputFile(EMPLOYEES_FILE);

    if (!checkDuplicate(inputFile, id, 0))
    {
        file << id << "," << name << "," << department << endl;
        cout << "Employee is registered successfully." << endl;
    }
    else
    {
        cout << "Employee with id: " << id << " already exists." << endl;
    }

    file.close();
    inputFile.close();
}

void updateEmployee(string &id, string &name, string &department)
{

    ifstream inputFile = openInputFile(EMPLOYEES_FILE);

    if (!checkDuplicate(inputFile, id, 0))
    {
        cout << "Employee with id: " << id << " doesn't exist." << endl;
    }
    else
    {
        inputFile.close();
        inputFile.open(EMPLOYEES_FILE);

        vector<string> fileData;
        string line;

        while (getline(inputFile, line))
        {
            vector<string> row = splitString(line, ',');

            if (row[0] == id)
            {
                row[1] = name;
                row[2] = department;

                line = joinString(row, ',');
            }
            fileData.push_back(line);
        }

        ofstream file = openOutputFile(EMPLOYEES_FILE, "w");

        for (size_t i = 0; i < fileData.size(); i++)
        {
            file << fileData[i] << endl;
        }
        file.close();
        cout << "Employee with id: " << id << " updated successfully." << endl;
    }

    inputFile.close();
}

void deleteEmployee(string &id)
{
    ifstream inputFile = openInputFile(EMPLOYEES_FILE);

    if (!checkDuplicate(inputFile, id, 0))
    {
        cout << "Employee with id: " << id << " doesn't exist." << endl;
    }
    else
    {
        deleteLine(EMPLOYEES_FILE, id);
        cout << "Employee with id : " << id << " deleted successfully." << endl;
    }

    inputFile.close();
}

void help()
{
    cout << " ===========================================================================" << endl;
    cout << " *                                   HELP MENU                              *" << endl;
    cout << " ===========================================================================" << endl;
    cout << " list                                      :List employees" << endl;
    cout << " delete <employeeID>                       :Delete an employee" << endl;
    cout << " register <ID> <name> <department>         :Register an employee" << endl;
    cout << " update <employeeID> <name> <department>   :Update an existing employee" << endl;
    cout << " help                                      :Prints user manual" << endl;
    cout << " exit                                      :Exit the program" << endl;
    cout << " =============================================================================" << endl;
}

void invalidCommand(string correctCommand)
{
    cout << "Invalid command. Usage: " << correctCommand << endl;
}

int processCommands()
{
    cout << "Need help? Type 'help' then press Enter key." << endl;

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
        if (command == "delete")
        {
            string employeeId;
            if (iss >> employeeId)
            {
                deleteEmployee(employeeId);
            }
            else
            {
                invalidCommand("delete <employeeID>");
            }
        }
        else if (command == "list")
        {
            listEmployees();
        }
        else if (command == "register")
        {
            string id;
            string name;
            string department;
            iss >> id >> name >> department;

            if (!(id.empty() && name.empty() && department.empty()))
            {
                registerEmployee(id, name, department);
            }
            else
            {
                invalidCommand("register <ID> <name> <department> ");
            }
        }
        else if (command == "update")
        {
            string id;
            string name;
            string department;
            iss >> id >> name >> department;

            if (!(id.empty() && name.empty() && department.empty()))
            {
                updateEmployee(id, name, department);
            }
            else
            {
                invalidCommand("update <ID> <name> <department> ");
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
    cout << "*     Welcome to Employee Management System!     *" << endl;
    cout << "*  **************************************** *" << endl;
    cout << "*                           *" << endl;
    cout << "* It is developed by 'NKUBITO Pacis' as practical *" << endl;
    cout << "* evaluation for the end of Year 3.               *" << endl;
    cout << " ====================================================" << endl;

    processCommands();
    return 0;
}
