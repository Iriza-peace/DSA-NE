#include <iostream>  // Input/output stream operations
#include <string>    // String operations
#include <sstream>   // String stream operations
#include <fstream>   // File input/output operations
#include <vector>    // Vector container
#include <algorithm> // Algorithms
#include <iomanip>   // Input/output manipulators

#include "utilities.cpp"

using namespace std;

string ITEMS_FILE = "items.csv";

struct Item
{
    string item_id;
    string item_name;
    string item_quantity;
    string item_registration_date;
};

// Function to compare items based on item_name for sorting
bool compareItems(const Item &item1, const Item &item2)
{
    return item1.item_name < item2.item_name;
}

// Function to list all items
void listItems()
{
    ifstream file = openInputFile(ITEMS_FILE);
    string item;
    vector<Item> items;

    // Read items from file and store them in a vector
    while (getline(file, item))
    {
        vector<string> row = splitString(item, ',');

        Item newItem;
        newItem.item_id = row[0];
        newItem.item_name = row[1];
        newItem.item_quantity = row[2];
        newItem.item_registration_date = row[3];

        items.push_back(newItem);
    }

    // Check if there are any items
    if (items.empty())
    {
        cout << "No items found" << endl;
    }
    else
    {
        // Sort the items based on item_name
        sort(items.begin(), items.end(), compareItems);

        // Display each item's details
        for (const auto &item : items)
        {
            cout << "Item ID:" << setw(2) << item.item_id << "            "
                 << "Item Name:" << setw(10) << item.item_name << "                "
                 << "Quantity :" << setw(2) << item.item_quantity << "      "
                 << "Reg Date :" << item.item_registration_date << endl
                 << endl;
        }
    }

    file.close();
}

// Function to add a new item
void addItem(const string &item_id, const string &item_name, const string &item_quantity, const string &item_registration_date)
{
    // Validate the input data format
    if (!isNumeric(item_id) || !isNumeric(item_quantity) || !isValidDateFormat(item_registration_date))
    {
        cout << "Invalid data format. Please enter the following format: <item_id as a number> <item_name> <item_quantity as a number> <item_registration_date as date in YYYY-mm-dd>" << endl;
        return;
    }

    // Open the items file for reading to check for duplicates
    ifstream inputFile = openInputFile(ITEMS_FILE);

    // Check if the item with the given item_id already exists
    if (checkDuplicate(inputFile, item_id, 0))
    {
        cout << "Item with id: " << item_id << " already exists." << endl;
        inputFile.close();
        return;
    }

    inputFile.close();

    // Open the items file in append mode to add the new item
    ofstream file(ITEMS_FILE, ios::app);
    file << item_id << "," << item_name << "," << item_quantity << "," << item_registration_date << endl;
    cout << "Item is added successfully." << endl;
    file.close();
}

// Function to display the help menu
void help()
{
    cout << " ===========================================================================" << endl;
    cout << " *                            Command syntaxes                              *" << endl;
    cout << " ===========================================================================" << endl;
    cout << " itemadd <item_id> <item_name> <item_quantity> <item_registration_date>" << endl;
    cout << " itemslist" << endl;
    cout << " help                                      :Prints user manual" << endl;
    cout << " exit                                      :Exit the program" << endl;
    cout << " =============================================================================" << endl;
}

// Function to display an invalid command message
void invalidCommand(const string &correctCommand)
{
    cout << "Invalid command. Usage: " << correctCommand << endl;
}

// Function to process user commands
void processCommands()
{
    cout << "Need help? Type 'help' then press Enter key." << endl;

    string input;
    string command;

    do
    {
        cout << "Console >";
        getline(cin, input);

        istringstream iss(input);
        iss >> command;

        // Convert the command to lowercase for case-insensitive comparison
        for (size_t i = 0; i < command.length(); i++)
        {
            command[i] = tolower(command[i]);
        }
        // Process the command
        if (command == "itemslist")
        {
            cout << "------------------------------------------------------------------------------------------------------------------" << endl;

            listItems();
            cout << "------------------------------------------------------------------------------------------------------------------" << endl;
        }
        else if (command == "itemadd")
        {
            string item_id, item_name, item_quantity, item_registration_date;
            iss >> item_id >> item_name >> item_quantity >> item_registration_date;

            if (item_id.empty() || item_name.empty() || item_quantity.empty() || item_registration_date.empty())
            {
                invalidCommand("itemadd <item_id> <item_name> <item_quantity> <item_registration_date>");
            }
            else
            {
                addItem(item_id, item_name, item_quantity, item_registration_date);
            }
        }
        else if (command == "help")
        {
            help();
        }
        else
        {
            // Invalid command entered
            if (command != "exit")
            {
                cout << "Invalid command. Below is the help option to provide you a list of commands." << endl;
                help();
            }
        }
    } while (command != "exit");
}

int main()
{
    cout << " ==================================================== " << endl;
    cout << "*     Welcome to RCA Inventory System!     *" << endl;
    cout << "*  **************************************** *" << endl;
    cout << "*                           *" << endl;
    cout << "* It is developed by 'NKUBITO Pacis' as practical *" << endl;
    cout << "* evaluation for the end of Year 3.               *" << endl;
    cout << " ====================================================" << endl;

    // Start processing user commands
    processCommands();
    return 0;
}
