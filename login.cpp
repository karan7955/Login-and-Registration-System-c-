#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <io.h>

using namespace std;

class LoginSystem {
private:
    const string databasePath = "user_database/";

    void createDatabaseDir() {
        #if defined(_WIN32)
            _mkdir(databasePath.c_str());
        #else
            mkdir(databasePath.c_str(), 0777);
        #endif
    }

    string getFilePath(const string& username) {
        return databasePath + username + ".txt";
    }

    bool userExists(const string& username) {
        ifstream userFile(getFilePath(username));
        return userFile.good();
    }

    bool validateCredentials(const string& username, const string& password) {
        ifstream userFile(getFilePath(username));
        if (userFile.is_open()) {
            string storedUsername, storedPassword;
            userFile >> storedUsername >> storedPassword;
            userFile.close();
            return (storedUsername == username && storedPassword == password);
        }
        return false;
    }

public:
    LoginSystem() {
        createDatabaseDir();
    }

    void registerUser() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (userExists(username)) {
            cout << "Username already exists. Try a different username." << endl;
            return;
        }

        ofstream userFile(getFilePath(username));
        if (userFile.is_open()) {
            userFile << username << endl;
            userFile << password << endl;
            userFile.close();
            cout << "Registration successful." << endl;
        } else {
            cout << "Error creating user file." << endl;
        }
    }

    void loginUser() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (validateCredentials(username, password)) {
            cout << "Login successful. Welcome, " << username << "!" << endl;
        } else {
            cout << "Invalid username or password." << endl;
        }
    }
};

int main() {
    LoginSystem system;
    int choice;

    do {
        cout << "1. Register" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.registerUser();
                break;
            case 2:
                system.loginUser();
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}
