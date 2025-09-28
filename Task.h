#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
public:
    int id;
    std::string title;
    std::string description;
    std::string dueDate;
    std::string priority;
    std::string status;
    Task* next;             
    
    Task();  
    Task(int id, const std::string& title, const std::string& description, const std::string& dueDate, const std::string& priority);

    void displayTask() const;

    static int compareDate(const std::string& date1, const std::string& date2);
    static int comparePriority(const std::string& p1, const std::string& p2);
};

#endif
