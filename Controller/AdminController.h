//
// Created by Mohamed Abdelhady on 10/1/2023.
//

#ifndef INC_A1620D432F594413A595C442BE7803EA
#define INC_A1620D432F594413A595C442BE7803EA

#include "UserController.h"
#include "MovieController.h"
#include "../Assistant.h"

namespace View { class Interface; }

namespace Controller {

    class AdminController {
    public:
        static map<string, Model::Admin> allAdminsUsername, allAdminsId;
        static Model::Admin currentAdmin;
        static long long lastId;

        static bool checkPassword(const string &username, const string &password);

        static void MainInterface(const string &username);

        static void accountInformation();

        static void addMovie();

        static void deleteMovie(const string &movieId);

        static void showAllUsers();

        static void showUser(const string &username);

        static void showAllHistory();

        static void printHistoryRecord(Model::Record record, const int &maxUsername, const int &maxMovieId);

        static void designateAsAdmin(const string &username);

        static void deleteAdmin(const string &username);

        static void deleteUser(const string &username);

        static string inputAdminUsername();

        static string inputUserUsername(const bool &New);

        static string inputMovieId();

        static string inputMovieName();

        static string inputMovieReleaseYear();

        static string inputMovieRate();

        static string inputMovieDuration();

        static string inputMovieStory();

        static void reload();

        static void readAdmins();
    };

} // Controller

#endif //INC_A1620D432F594413A595C442BE7803EA
