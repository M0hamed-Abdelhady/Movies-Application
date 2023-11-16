//
// Created by Mohamed Abdelhady on 6/20/2023.
//

#ifndef MOVIESAPP_INTERFACE_H
#define MOVIESAPP_INTERFACE_H

#endif //MOVIESAPP_INTERFACE_H

#include "../Assistant.h"
#include "../Controller/MovieController.h"
#include "../Controller/UserController.h"
#include "../Controller/AdminController.h"

namespace View {

    class Interface {
    public:
        Interface();

        static void defaultInterface();

        static void login();

        static void signup();

        static void logout(const string &id, const bool &authority);

    };

}