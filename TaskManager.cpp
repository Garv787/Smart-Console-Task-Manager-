#include "TaskManager.h"
#include "Task.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

TaskManager::TaskManager(const string& user) : head(nullptr), username(user) {
    loadTasksFromFile();
}

TaskManager::~TaskManager() {
    saveTasksToFile();
    while (head) {
        Task* temp = head;
        head = head->next;
        delete temp;
    }
}

void TaskManager::loadTasksFromFile() {
    ifstream file("tasks_" + username + ".txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, title, desc, date, priority, status;
        getline(ss, id, '|');
        getline(ss, title, '|');
        getline(ss, desc, '|');
        getline(ss, date, '|');
        getline(ss, priority, '|');
        getline(ss, status, '|');

        Task* newTask = new Task(stoi(id), title, desc, date, priority);
        newTask->status = status.empty() ? "Pending" : status;
        newTask->next = head;
        head = newTask;
    }
    file.close();
}

void TaskManager::saveTasksToFile() {
    ofstream file("tasks_" + username + ".txt");
    Task* curr = head;
    while (curr) {
        file << curr->id << "|" << curr->title << "|" << curr->description << "|"
             << curr->dueDate << "|" << curr->priority << "|" << curr->status << "\n";
        curr = curr->next;
    }
    file.close();
}

void TaskManager::addTask() {
    int id;
    string title, desc, date, priority;

    cout << "Enter Task ID: "; cin >> id;
    cin.ignore();
    cout << "Enter Title: "; getline(cin, title);
    cout << "Enter Description: "; getline(cin, desc);
    cout << "Enter Due Date (dd-mm-yyyy): "; getline(cin, date);
    cout << "Enter Priority (High/Medium/Low): "; getline(cin, priority);

    Task* newTask = new Task(id, title, desc, date, priority);
    newTask->next = head;
    head = newTask;

    cout << "Task added!\n";
}

void TaskManager::displayTasks() {
    Task* curr = head;
    if (!curr) {
        cout << "No tasks found.\n";
        return;
    }

    while (curr) {
        curr->displayTask();
        curr = curr->next;
    }
}

Task* TaskManager::findTaskById(int id) {
    Task* curr = head;
    while (curr) {
        if (curr->id == id) return curr;
        curr = curr->next;
    }
    return nullptr;
}

Task* TaskManager::findTaskByTitle(const string& title) {
    Task* curr = head;
    while (curr) {
        if (curr->title == title) return curr;
        curr = curr->next;
    }
    return nullptr;
}

void TaskManager::deleteTaskById(int id) {
    Task *curr = head, *prev = nullptr;
    while (curr) {
        if (curr->id == id) {
            if (prev) prev->next = curr->next;
            else head = curr->next;
            delete curr;
            cout << "Task deleted by ID.\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Task with ID " << id << " not found.\n";
}

void TaskManager::deleteTaskByTitle(const string& title) {
    Task *curr = head, *prev = nullptr;
    while (curr) {
        if (curr->title == title) {
            if (prev) prev->next = curr->next;
            else head = curr->next;
            delete curr;
            cout << "Task deleted by title.\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Task with title \"" << title << "\" not found.\n";
}

void TaskManager::updateTaskById(int id) {
    Task* task = findTaskById(id);
    if (task) {
        cin.ignore();
        cout << "Enter new Title: "; getline(cin, task->title);
        cout << "Enter new Description: "; getline(cin, task->description);
        cout << "Enter new Due Date: "; getline(cin, task->dueDate);
        cout << "Enter new Priority: "; getline(cin, task->priority);
        cout << "Enter new Status: "; getline(cin, task->status);
        cout << "Task updated by ID.\n";
    } else {
        cout << "Task with ID " << id << " not found.\n";
    }
}

void TaskManager::updateTaskByTitle(const string& title) {
    Task* task = findTaskByTitle(title);
    if (task) {
        cout << "Enter new Title: "; getline(cin, task->title);
        cout << "Enter new Description: "; getline(cin, task->description);
        cout << "Enter new Due Date: "; getline(cin, task->dueDate);
        cout << "Enter new Priority: "; getline(cin, task->priority);
        cout << "Enter new Status: "; getline(cin, task->status);
        cout << "Task updated by title.\n";
    } else {
        cout << "Task with title \"" << title << "\" not found.\n";
    }
}

void TaskManager::sortTasksByDate() {
    if (!head || !head->next) return;
    bool swapped;
    do {
        swapped = false;
        Task* curr = head;
        while (curr->next) {
            if (Task::compareDate(curr->dueDate, curr->next->dueDate) > 0) {
                swap(*curr, *curr->next);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
    cout << "Tasks sorted by due date.\n";
}

void TaskManager::sortTasksByPriority() {
    if (!head || !head->next) return;
    bool swapped;
    do {
        swapped = false;
        Task* curr = head;
        while (curr->next) {
            if (Task::comparePriority(curr->priority, curr->next->priority) > 0) {
                swap(*curr, *curr->next);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
    cout << "Tasks sorted by priority.\n";
}

void TaskManager::searchTasksByKeyword(const string& keyword) {
    Task* curr = head;
    bool found = false;
    while (curr) {
        if (curr->title.find(keyword) != string::npos || curr->description.find(keyword) != string::npos) {
            curr->displayTask();
            found = true;
        }
        curr = curr->next;
    }
    if (!found) cout << "No tasks found with keyword: " << keyword << "\n";
}

void TaskManager::filterTasksByPriority(const string& priority) {
    Task* curr = head;
    bool found = false;
    while (curr) {
        if (curr->priority == priority) {
            curr->displayTask();
            found = true;
        }
        curr = curr->next;
    }
    if (!found) cout << "No tasks found with priority: " << priority << "\n";
}

void TaskManager::filterTasksDueToday() {
    time_t now = time(0);
    tm* local = localtime(&now);
    char today[11];
    strftime(today, 11, "%d-%m-%Y", local);

    Task* curr = head;
    bool found = false;
    while (curr) {
        if (curr->dueDate == today) {
            curr->displayTask();
            found = true;
        }
        curr = curr->next;
    }
    if (!found) cout << "No tasks due today.\n";
}

void TaskManager::exportTasksToFile() {
    string filename = username + "_tasks_export.csv";
    ofstream out(filename);
    if (!out) {
        cout << "Failed to create export file.\n";
        return;
    }

    out << "ID,Title,Description,Due Date,Priority,Status\n";
    Task* curr = head;
    while (curr) {
        out << curr->id << ","
            << curr->title << ","
            << curr->description << ","
            << curr->dueDate << ","
            << curr->priority << ","
            << curr->status << "\n";
        curr = curr->next;
    }

    out.close();
    cout << "Tasks exported to " << filename << "\n";
}
