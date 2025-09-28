#include "Task.h"
#include <iostream>

Task::Task() {
    status = "Pending";   
    next = nullptr;
}

Task::Task(int id, const std::string& title, const std::string& description,
           const std::string& dueDate, const std::string& priority) {
    this->id = id;
    this->title = title;
    this->description = description;
    this->dueDate = dueDate;
    this->priority = priority;
    this->status = "Pending";  
    this->next = nullptr;
}

void Task::displayTask() const {
    std::cout << "\nTask ID      : " << id
              << "\nTitle        : " << title
              << "\nDescription  : " << description
              << "\nDue Date     : " << dueDate
              << "\nPriority     : " << priority
              << "\nStatus       : " << status
              << "\n-----------------------------";
}

int Task::compareDate(const std::string& d1, const std::string& d2) {
    int day1 = stoi(d1.substr(0, 2)), month1 = stoi(d1.substr(3, 2)), year1 = stoi(d1.substr(6, 4));
    int day2 = stoi(d2.substr(0, 2)), month2 = stoi(d2.substr(3, 2)), year2 = stoi(d2.substr(6, 4));

    if (year1 != year2) return year1 - year2;
    if (month1 != month2) return month1 - month2;
    return day1 - day2;
}

int Task::comparePriority(const std::string& p1, const std::string& p2) {
    int val1 = (p1 == "High") ? 1 : (p1 == "Medium") ? 2 : 3;
    int val2 = (p2 == "High") ? 1 : (p2 == "Medium") ? 2 : 3;
    return val1 - val2;
}
