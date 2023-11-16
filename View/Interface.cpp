//
// Created by Mohamed Abdelhady on 6/20/2023.
//
#include "Interface.h"

namespace View
{
    Interface::Interface()
    {
        Controller::UserController::readUsers();
        Controller::UserController::readRecords();
        Controller::MovieController::readMovies();
        Controller::AdminController::readAdmins();
        vector<string> logs = Assistant::readLogs();
        if (stoi(logs[0]) && ((Controller::AdminController::allAdminsId.count(logs[2])) ||
                              (!stoi(logs[1]) && Controller::UserController::allUsersId.count(logs[2]))))
        {
            if (stoi(logs[1]))
                Controller::AdminController::
                    MainInterface(Controller::AdminController::allAdminsId[logs[2]].getUsername());
            else
                Controller::UserController::
                    MainInterface(Controller::UserController::allUsersId[logs[2]].getUsername());
        }
        else
            defaultInterface();
    }

    void Interface::defaultInterface()
    {
        while (true)
        {
            vector<string> menu{"Login", "Signup", "Exit"};
            int choice = Assistant::runMenu(menu);
            if (choice == 1)
                login();
            else if (choice == 2)
                signup();
            else
                exit(0);
        }
    }

    void Interface::login()
    {
        cout << "\tLogin\nusername: ";
        string username, password;
        cin >> username;
        cout << "Password: ";
        cin >> password;
        if (Controller::AdminController::checkPassword(username, password))
        {
            Assistant::writeLogs(true, true, Controller::AdminController::allAdminsUsername[username].getId());
            Controller::AdminController::MainInterface(username);
        }
        else if (Controller::UserController::checkPassword(username, password))
        {
            Assistant::writeLogs(true, false, Controller::UserController::allUsersUsername[username].getId());
            Controller::UserController::MainInterface(username);
        }
        else
        {
            cout << "Wrong Password or username!\n";
        }
    }

    void Interface::signup()
    {
        string name, email, username, password;
        cout << "\tSignup\nName: ";
        cin.ignore();
        getline(cin, name);
        cout << "email: ";
        while (true)
        {
            getline(cin, email);
            auto it = email.find(' ');
            if (it != string::npos)
            {
                cout << "ERROR! invalid character -space-\nplease input valid email: ";
                cin.ignore();
                continue;
            }
            else if (!Assistant::emailValidation(email))
            {
                cout << "ERROR! invalid email format\nplease input valid email: ";
                cin.ignore();
                continue;
            }
            break;
        }
        username = Controller::AdminController::inputUserUsername(true);
        cout << "Password: ";
        while (true)
        {
            getline(cin, password);
            auto it = password.find(' ');
            if (it != string::npos)
            {
                cout << "ERROR! invalid character -space- in password\nplease input valid Password: ";
                cin.ignore();
                continue;
            }
            string tmp;
            cout << "Confirm Password: ";
            getline(cin, tmp);
            if (tmp != password)
            {
                cout << "ERROR! not matched\nPassword: ";
                cin.ignore();
                continue;
            }
            break;
        }
        string id = to_string(Controller::UserController::generateId());
        Model::User user(id, name, username, password, email,
                         Assistant::currentTimeToString(),
                         false);
        Controller::UserController::allUsersId[id] = user;
        Controller::UserController::allUsersUsername[username] = user;
        Controller::UserController::reloadUsers();
        Assistant::writeLogs(true, false, id);
        Controller::UserController::MainInterface(username);
    }

    void Interface::logout(const string &id, const bool &authority)
    {
        Assistant::writeLogs(false, authority, id);
        defaultInterface();
    }

}