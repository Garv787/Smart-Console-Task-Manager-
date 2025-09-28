#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <string>
#include "Task.h"

class TaskManager {
private:
    Task* head;
    std::string username;

    void loadTasksFromFile();
    void saveTasksToFile();

    Task* findTaskById(int id);
    Task* findTaskByTitle(const std::string& title);

public:
    TaskManager(const std::string& user);
    ~TaskManager();

    void addTask();
    void displayTasks();
    void updateTaskById(int id);
    void updateTaskByTitle(const std::string& title);
    void deleteTaskById(int id);
    void deleteTaskByTitle(const std::string& title);

    void sortTasksByDate();
    void sortTasksByPriority();
    void searchTasksByKeyword(const std::string& keyword);
    void filterTasksByPriority(const std::string& priority);
    void filterTasksDueToday();
    void exportTasksToFile();
};

#endif
