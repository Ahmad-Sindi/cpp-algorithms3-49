#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

/*
 * Algorithm Challenge – Level 3 | #49 Find Client by Account Number
 *
 * This program demonstrates how to search for a specific client inside a text file using a unique identifier (Account Number).
 *
 * Engineering Workflow:
 *   - Open the client file automatically
 *   - Read records line by line
 *   - Parse each line into a structured object
 *   - Search sequentially for a matching account number
 *   - Display the client data if found
 */

// Client file name
const string ClientFileName1 = "Clients.txt";

// Structure that represents client data
struct ClientStructData
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phon;
    double AccountBalance;
};

// Splits a string using a specific delimiter
vector<string> SplitString(string S1, string Delim)
{
    vector<string> VecString;
    short Position = 0;
    string Token;

    while ((Position = S1.find(Delim)) != string::npos)
    {
        Token = S1.substr(0, Position);

        if (Token != "")
            VecString.push_back(Token);

        S1.erase(0, Position + Delim.length());
    }

    if (S1 != "")
        VecString.push_back(S1);

    return VecString;
}

// Converts a text line into a client structure
ClientStructData ConvertLineToRecord(string Line, string Seperator = "#//#")
{
    ClientStructData Client;
    vector<string> ClientData = SplitString(Line, Seperator);

    Client.AccountNumber = ClientData[0];
    Client.PinCode = ClientData[1];
    Client.Name = ClientData[2];
    Client.Phon = ClientData[3];
    Client.AccountBalance = stod(ClientData[4]);

    return Client;
}

// Loads all clients from the file into a vector
vector<ClientStructData> LoadClientsDataFromFile(string FileName)
{
    vector<ClientStructData> VecClients;
    fstream FileClients;

    FileClients.open(FileName, ios::in); // Read mode

    if (FileClients.is_open())
    {
        string Line;
        ClientStructData Client;

        // Each line represents one client
        while (getline(FileClients, Line))
        {
            Client = ConvertLineToRecord(Line);
            VecClients.push_back(Client);
        }

        FileClients.close();
    }

    return VecClients;
}

// Prints a single client card
void PrintClientCard(ClientStructData Client)
{
    cout << "\nClient Information\n";
    cout << "-----------------------\n";
    cout << "Account Number : " << Client.AccountNumber << endl;
    cout << "Pin Code       : " << Client.PinCode << endl;
    cout << "Full Name      : " << Client.Name << endl;
    cout << "Phone Number   : " << Client.Phon << endl;
    cout << "Account Balance: " << Client.AccountBalance << endl;
}

// Searches for a client by account number
bool FindClientByAccountNumber(string AccountNumber, ClientStructData &Client)
{
    vector<ClientStructData> vClients =
        LoadClientsDataFromFile(ClientFileName1);

    // Sequential search
    for (ClientStructData C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C; // Pass data by reference
            return true;
        }
    }

    return false;
}

// Reads account number from the user
string ReadClientAccountNumber()
{
    string AccountNumber;
    cout << "Enter Account Number: ";
    cin >> AccountNumber;
    return AccountNumber;
}

int main()
{
    ClientStructData Client;
    string AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(AccountNumber, Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "\nClient with Account Number ("
             << AccountNumber << ") was not found.\n";
    }

    return 0;
}
