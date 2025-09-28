#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <conio.h>
#include <sstream>
#include <ctime>
#include "User.h"
#include "Task.h"
#include "TaskManager.h"

using namespace std;

string getMaskedPassword();

string User::encodePassword(const string& password) {
    string encoded = password;
    for (char& ch : encoded) ch += 3;
    return encoded;
}

void User::registerUser() {
    string username, password, confirmPassword;
    cout << "Enter new username: ";
    cin >> username;

    for (char ch : username) {
        if (isspace(ch)) {
            cout << "Username cannot contain spaces.\n";
            return;
        }
    }

    cout << "Enter new password: ";
    password = getMaskedPassword();
    cout << "Confirm password: ";
    confirmPassword = getMaskedPassword();

    if (password != confirmPassword) {
        cout << "Passwords do not match. Try again.\n";
        return;
    }

    ofstream file("users.txt", ios::app);
    file << username << " " << encodePassword(password) << endl;
    file.close();
    cout << "Registration successful!\n";
}

void User::loginUser() {
    string username, password, u, p;
    bool success = false;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    password = getMaskedPassword();
    string encodedPass = encodePassword(password);

    ifstream file("users.txt");
    while (file >> u >> p) {
        if (u == username && p == encodedPass) {
            success = true;
            break;
        }
    }
    file.close();

    if (success) {
        ofstream session("session.txt");
        session << username;
        session.close();
        cout << "Login successful! Welcome, " << username << ".\n";
    } else {
        ofstream session("session.txt", ios::trunc); 
        session.close();
        cout << "Login failed.\n";
    }
}

void User::logoutUser() {
    ofstream session("session.txt", ios::trunc);
    session.close();
    cout << "Logged out successfully.\n";
}

void User::showDashboard() {
    ifstream session("session.txt");
    string username;
    getline(session, username);
    session.close();

    if (username.empty()) {
        cout << "No user is currently logged in.\n";
        return;
    }

    TaskManager taskManager(username);
    int choice;
    do {
        cout << "\n====== DASHBOARD ======\n"
             << "1. Add Task\n"
             << "2. View Tasks\n"
             << "3. Update Task by ID\n"
             << "4. Update Task by Title\n"
             << "5. Delete Task by ID\n"
             << "6. Delete Task by Title\n"
             << "7. Sort by Due Date\n"
             << "8. Sort by Priority\n"
             << "9. Search by Keyword\n"
             << "10. Filter by Priority\n"
             << "11. Filter Due Today\n"
             << "12. Export Tasks to CSV\n"
             << "13. Logout\n"
             << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: taskManager.addTask(); break;
            case 2: taskManager.displayTasks(); break;
            case 3: {
                int id;
                cout << "Enter Task ID: ";
                cin >> id;
                taskManager.updateTaskById(id);
                break;
            }
            case 4: {
                string title;
                cout << "Enter Task Title: ";
                getline(cin, title);
                taskManager.updateTaskByTitle(title);
                break;
            }
            case 5: {
                int id;
                cout << "Enter Task ID: ";
                cin >> id;
                taskManager.deleteTaskById(id);
                break;
            }
            case 6: {
                string title;
                cout << "Enter Task Title: ";
                getline(cin, title);
                taskManager.deleteTaskByTitle(title);
                break;
            }
            case 7: taskManager.sortTasksByDate(); break;
            case 8: taskManager.sortTasksByPriority(); break;
            case 9: {
                string keyword;
                cout << "Enter keyword: ";
                getline(cin, keyword);
                taskManager.searchTasksByKeyword(keyword);
                break;
            }
            case 10: {
                string priority;
                cout << "Enter priority: ";
                getline(cin, priority);
                taskManager.filterTasksByPriority(priority);
                break;
            }
            case 11: taskManager.filterTasksDueToday(); break;
            case 12: taskManager.exportTasksToFile(); break;
            case 13: logoutUser(); break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 13);
}

string User::getLoggedInUsername() {
    ifstream session("session.txt");
    string username;
    getline(session, username);
    session.close();
    return username;
}

string getMaskedPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        } else {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return password;
}
