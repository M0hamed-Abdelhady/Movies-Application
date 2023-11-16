//
// Created by Mohamed Abdelhady on 10/1/2023.
//

#ifndef INC_E8E80A4FAB9542E5BFE69AA1894B8AAE
#define INC_E8E80A4FAB9542E5BFE69AA1894B8AAE

#include "MovieController.h"
#include "../Model/Record.h"
#include <fstream>

namespace View { class Interface; }

namespace Controller {
    class AdminController;

    class UserController {
    public:
        static map<string, Model::User, Assistant::comparator> allUsersId;
        static map<string, Model::User> allUsersUsername;
        static map<vector<string>, Model::Record> allRecords;
        static Model::User currentUser;
        static long long lastId, maximumName, maximumUsername;

        static bool checkPassword(const string &username, const string &password);

        static void MainInterface(const string &username);

        static void accountInformation(Model::User &user = currentUser);

        static void watch(Model::Movie &movie);

        static void showUnwatchedMovies();

        static void openMovie(Model::Movie &movie);

        static void printMovie(Model::Movie &movie);

        static void showHistory();

        static void printHistoryRecord(Model::Record record, const int &maxName, const int &maxId);

        static void addToHistory(Model::Movie &movie, double &watchedRatio);

        static void removeFromHistory(const string &movieId);

        static void showFavourite();

        static void printFavouriteRecord(Model::Record record, const int &maxName, const int &maxId);

        static void addToFavourite(Model::Movie &movie);

        static void removeFromFavourite(const string &movieId);

        static void deleteAccount();

        static void reloadUsers();

        static void reloadRecords(const string &id = "0", const bool &movie = false);

        static long long generateId();

        static void readUsers();

        static void readRecords();
    };

} // Controller

#endif //INC_E8E80A4FAB9542E5BFE69AA1894B8AAE
