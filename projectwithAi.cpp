#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;

class Library
{
    string id, name, author, status;

public:
    void addBook();
    void deleteBook();
    void showAllBook();
    void searchBook();
    void issueBook();
    void returnBook();
    void recommendBooks();  // New recommendation feature
};

Library obj;

// MAIN FUNCTION

int main()
{
    char choice;

    while (true)
    {
        cout << "\n\n======================================" << endl;
        cout << "       LIBRARY MANAGEMENT SYSTEM" << endl;
        cout << "======================================" << endl;

        cout << "1 - Add Book" << endl;
        cout << "2 - Delete Book" << endl;
        cout << "3 - Show All Books" << endl;
        cout << "4 - Search Book" << endl;
        cout << "5 - Issue Book" << endl;
        cout << "6 - Return Book" << endl;
        cout << "7 - AI Book Recommendation" << endl;
        cout << "8 - Exit" << endl;

        cout << "======================================" << endl;
        cout << "Enter your choice :: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case '1':
            obj.addBook();
            break;

        case '2':
            obj.deleteBook();
            break;

        case '3':
            obj.showAllBook();
            break;

        case '4':
            obj.searchBook();
            break;

        case '5':
            obj.issueBook();
            break;

        case '6':
            obj.returnBook();
            break;

        case '7':
            obj.recommendBooks();
            break;

        case '8':
            cout << "\nThank you for using Library Management System!" << endl;
            return 0;

        default:
            cout << "\nInvalid choice....!" << endl;
        }
    }

    return 0;
}

// ADD BOOK

void Library::addBook()
{
    string newId, newName, newAuthor;

    cout << "\nEnter Book ID :: ";
    getline(cin, newId);

    cout << "Enter Book Name :: ";
    getline(cin, newName);

    cout << "Enter Book's Author Name :: ";
    getline(cin, newAuthor);

    // Check for duplicate ID
    fstream checkFile;
    checkFile.open("bookData.txt", ios::in);

    if (checkFile.is_open())
    {
        while (getline(checkFile, id, '*') &&
               getline(checkFile, name, '*') &&
               getline(checkFile, author, '*') &&
               getline(checkFile, status))
        {
            if (newId == id)
            {
                cout << "\nBook ID already exists!" << endl;
                checkFile.close();
                return;
            }
        }

        checkFile.close();
    }

    // Open file in append mode
    fstream file;
    file.open("bookData.txt", ios::out | ios::app);

    if (!file.is_open())
    {
        cout << "\nFile could not be opened!" << endl;
        return;
    }

    file << newId << "*"
         << newName << "*"
         << newAuthor << "*"
         << "Available" << endl;

    file.close();

    cout << "\nBook added successfully...!" << endl;
}

// DELETE BOOK

void Library::deleteBook()
{
    string searchId;

    cout << "\nEnter Book ID to delete :: ";
    getline(cin, searchId);

    fstream file;
    fstream tempFile;

    file.open("bookData.txt", ios::in);
    tempFile.open("temp.txt", ios::out);

    if (!file.is_open() || !tempFile.is_open())
    {
        cout << "\nFile could not be opened!" << endl;
        return;
    }

    bool found = false;

    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, author, '*') &&
           getline(file, status))
    {
        if (searchId == id)
        {
            found = true;
            continue;
        }

        tempFile << id << "*"
                 << name << "*"
                 << author << "*"
                 << status << endl;
    }

    file.close();
    tempFile.close();

    if (remove("bookData.txt") != 0)
    {
        cout << "Error deleting old file!" << endl;
        return;
    }

    if (rename("temp.txt", "bookData.txt") != 0)
    {
        cout << "Error replacing file!" << endl;
        return;
    }

    if (found)
        cout << "\nBook deleted successfully...!" << endl;
    else
        cout << "\nBook ID not found...!" << endl;
}

// SHOW ALL BOOKS

void Library::showAllBook()
{
    fstream file;
    file.open("bookData.txt", ios::in);

    if (!file.is_open())
    {
        cout << "\nNo book data found!" << endl;
        return;
    }

    cout << "\n-------------------------------------------------" << endl;
    cout << "Book ID\t\tBook Name\t\tAuthor\t\tStatus" << endl;
    cout << "-------------------------------------------------" << endl;

    bool found = false;

    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, author, '*') &&
           getline(file, status))
    {
        found = true;

        cout << id << "\t\t"
             << name << "\t\t"
             << author << "\t\t"
             << status << endl;
    }

    file.close();

    if (!found)
        cout << "\nNo books available." << endl;

    cout << "-------------------------------------------------" << endl;
}

// SEARCH BOOK

void Library::searchBook()
{
    string searchId;

    cout << "\nEnter Book ID to search :: ";
    getline(cin, searchId);

    fstream file;
    file.open("bookData.txt", ios::in);

    if (!file.is_open())
    {
        cout << "No book data found!" << endl;
        return;
    }

    bool found = false;

    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, author, '*') &&
           getline(file, status))
    {
        if (searchId == id)
        {
            cout << "\n========== BOOK FOUND ==========" << endl;
            cout << "Book ID       : " << id << endl;
            cout << "Book Name     : " << name << endl;
            cout << "Author Name   : " << author << endl;
            cout << "Status        : " << status << endl;
            cout << "================================" << endl;

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nBook ID not found...!" << endl;
}

// ISSUE BOOK

void Library::issueBook()
{
    string searchId;

    cout << "\nEnter Book ID to issue :: ";
    getline(cin, searchId);

    fstream file, tempFile;

    file.open("bookData.txt", ios::in);
    tempFile.open("temp.txt", ios::out);

    if (!file.is_open() || !tempFile.is_open())
    {
        cout << "\nFile could not be opened!" << endl;
        return;
    }

    bool found = false;
    bool alreadyIssued = false;

    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, author, '*') &&
           getline(file, status))
    {
        if (searchId == id)
        {
            found = true;

            if (status == "Issued")
                alreadyIssued = true;
            else
                status = "Issued";
        }

        tempFile << id << "*"
                 << name << "*"
                 << author << "*"
                 << status << endl;
    }

    file.close();
    tempFile.close();

    if (remove("bookData.txt") != 0)
    {
        cout << "\nError deleting old file!" << endl;
        return;
    }

    if (rename("temp.txt", "bookData.txt") != 0)
    {
        cout << "\nError replacing file!" << endl;
        return;
    }

    if (!found)
        cout << "\nBook ID not found...!" << endl;
    else if (alreadyIssued)
        cout << "\nBook is already issued!" << endl;
    else
        cout << "\nBook issued successfully...!" << endl;
}

// RETURN BOOK

void Library::returnBook()
{
    string searchId;

    cout << "\nEnter Book ID to return :: ";
    getline(cin, searchId);

    fstream file, tempFile;

    file.open("bookData.txt", ios::in);
    tempFile.open("temp.txt", ios::out);

    if (!file.is_open() || !tempFile.is_open())
    {
        cout << "\nFile could not be opened!" << endl;
        return;
    }

    bool found = false;
    bool alreadyAvailable = false;

    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, author, '*') &&
           getline(file, status))
    {
        if (searchId == id)
        {
            found = true;

            if (status == "Available")
                alreadyAvailable = true;
            else
                status = "Available";
        }

        tempFile << id << "*"
                 << name << "*"
                 << author << "*"
                 << status << endl;
    }

    file.close();
    tempFile.close();

    if (remove("bookData.txt") != 0)
    {
        cout << "\nError deleting old file!" << endl;
        return;
    }

    if (rename("temp.txt", "bookData.txt") != 0)
    {
        cout << "\nError replacing file!" << endl;
        return;
    }

    if (!found)
        cout << "\nBook ID not found...!" << endl;
    else if (alreadyAvailable)
        cout << "\nBook is already available!" << endl;
    else
        cout << "\nBook returned successfully...!" << endl;
}

// AI BOOK RECOMMENDATION
// Keyword-based recommendation prototype

void Library::recommendBooks()
{
    string interest;

    cout << "\n===== AI BOOK RECOMMENDATION =====" << endl;
    cout << "Enter your interest (C++, Java, Python, Data Structures, SQL): ";
    getline(cin, interest);

    // Convert input to lowercase
    transform(interest.begin(), interest.end(), interest.begin(),
              [](unsigned char c)
              {
                  return static_cast<char>(tolower(c));
              });

    if (interest.empty())
    {
        cout << "\nPlease enter a valid interest!" << endl;
        return;
    }

    fstream file;
    file.open("bookData.txt", ios::in);

    if (!file.is_open())
    {
        cout << "\nNo book data found!" << endl;
        return;
    }

    bool found = false;

    cout << "\nRecommended Books for You:\n" << endl;

    while (getline(file, id, '*') &&
           getline(file, name, '*') &&
           getline(file, author, '*') &&
           getline(file, status))
    {
        string bookName = name;
        string bookAuthor = author;

        // Convert book details to lowercase
        transform(bookName.begin(), bookName.end(),
                  bookName.begin(),
                  [](unsigned char c)
                  {
                      return static_cast<char>(tolower(c));
                  });

        transform(bookAuthor.begin(), bookAuthor.end(),
                  bookAuthor.begin(),
                  [](unsigned char c)
                  {
                      return static_cast<char>(tolower(c));
                  });

        // Find matching interest in title or author
        if (bookName.find(interest) != string::npos ||
            bookAuthor.find(interest) != string::npos)
        {
            cout << "Book Name : " << name << endl;
            cout << "Author    : " << author << endl;
            cout << "Status    : " << status << endl;
            cout << "------------------------------" << endl;

            found = true;
        }
    }

    file.close();

    if (!found)
    {
        cout << "No matching books found for your interest." << endl;
        cout << "Try another keyword, such as C++, Java, or Python." << endl;
    }
}
