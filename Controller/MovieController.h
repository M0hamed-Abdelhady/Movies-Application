//
// Created by Mohamed Abdelhady on 10/1/2023.
//

#ifndef INC_463E745347AE426E9CF3F7410E9A2C77
#define INC_463E745347AE426E9CF3F7410E9A2C77

#include "../Model/Admin.h"
#include "../Model/User.h"

namespace View { class Interface; }
namespace Controller {
    class UserController;

    class AdminController;

    class MovieController {

    public:
        static map<string, Model::Movie, Assistant::comparator> allMovies;
        static set<string> moviesName;
        static long long lastId, maximumName;

    public:
        static int watch(Model::Movie &movie);

        static void showAll(Model::Movie admin);

        static void showRecentlyAddedMovies();

        static void showDetails(Model::Movie &movie);

        static void printMovie(Model::Movie movie);

        static void reloadMovies();

        static long long generateId();

        static void readMovies();

        static void showAll(const bool &admin);
    };

} // Controller

#endif //INC_463E745347AE426E9CF3F7410E9A2C77
