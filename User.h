#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    void registerUser();   
    void loginUser();                   
    void logoutUser();                  
    void showDashboard();              
    std::string getLoggedInUsername();  
    void exportTasksToCSV();           

private:
    std::string encodePassword(const std::string& password); 
};

#endif
