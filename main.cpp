#include <iostream>
#include <cstdlib>
#include "User.h"
#include "TaskManager.h"

using namespace std;

void showMainMenu() {
    cout << "\n====== Smart Console Based Task Manager ======\n";
    cout << "1. Register\n2. Login\n3. Logout\n4. Exit\nEnter your choice: ";
}

void showTaskMenu(TaskManager& taskManager, const string& username) {
    int choice;
    do {
        cout << "\n===== Task Menu for " << username << " =====\n";
        cout << "1. Add Task\n";
        cout << "2. View All Tasks\n";
        cout << "3. Update Task by ID\n";
        cout << "4. Update Task by Title\n";
        cout << "5. Delete Task by ID\n";
        cout << "6. Delete Task by Title\n";
        cout << "7. Sort Tasks by Date\n";
        cout << "8. Sort Tasks by Priority\n";
        cout << "9. Search Task by Keyword\n";
        cout << "10. Filter Tasks by Priority\n";
        cout << "11. Filter Tasks Due Today\n";
        cout << "12. Export Tasks to File\n";
        cout << "13. Logout\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  

        int id;
        string title, keyword, priority;

        switch (choice) {
            case 1:
                taskManager.addTask();
                break;
            case 2:
                taskManager.displayTasks();
                break;
            case 3:
                cout << "Enter Task ID to update: ";
                cin >> id;
                taskManager.updateTaskById(id);
                break;
            case 4:
                cout << "Enter Task Title to update: ";
                getline(cin, title);
                taskManager.updateTaskByTitle(title);
                break;
            case 5:
                cout << "Enter Task ID to delete: ";
                cin >> id;
                taskManager.deleteTaskById(id);
                break;
            case 6:
                cout << "Enter Task Title to delete: ";
                getline(cin, title);
                taskManager.deleteTaskByTitle(title);
                break;
            case 7:
                taskManager.sortTasksByDate();
                break;
            case 8:
                taskManager.sortTasksByPriority();
                break;
            case 9:
                cout << "Enter keyword to search in title or description: ";
                getline(cin, keyword);
                taskManager.searchTasksByKeyword(keyword);
                break;
            case 10:
                cout << "Enter priority (High/Medium/Low): ";
                getline(cin, priority);
                taskManager.filterTasksByPriority(priority);
                break;
            case 11:
                taskManager.filterTasksDueToday();
                break;
            case 12:
                taskManager.exportTasksToFile();
                break;
            case 13:
                cout << "Logging out from Task Manager...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 13);
}

int main() {
    int choice;
    User user;

    while (true) {
        showMainMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                user.registerUser();
                break;
            case 2:
                user.loginUser();
                if (!user.getLoggedInUsername().empty()) {
                    TaskManager taskManager(user.getLoggedInUsername());
                    showTaskMenu(taskManager, user.getLoggedInUsername());
                }
                break;
            case 3:
                user.logoutUser();
                break;
            case 4:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
