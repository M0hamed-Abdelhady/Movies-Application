//
// Created by Mohamed Abdelhady on 9/28/2023.
//

#ifndef INC_DE9262A6A4F5421F846C6B48EBD75342
#define INC_DE9262A6A4F5421F846C6B48EBD75342

#include "../Assistant.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <map>

namespace Model {

    class Person {

        std::string id, username, name, password, email, creationTime;
        bool state;


    public:
        Person();

        Person(std::string &id, const std::string &name, const std::string &username, const std::string &password,
               const std::string &email, const std::string &creationTime, bool state);

        virtual const std::string toString();

        bool operator==(const long long &id) const;

        bool operator==(const std::string &username) const;

        const std::string &getUsername() const;

        void setUsername(const std::string &username);

        const std::string &getName() const;

        void setName(const std::string &name);

        const std::string &getId() const;

        void setId(const std::string &id);

        const std::string &getPassword() const;

        void setPassword(const std::string &password);

        const std::string &getEmail() const;

        void setEmail(const std::string &email);

        bool getState() const;

        void setState(bool state);

        const std::string &getCreationTime() const;

        void setCreationTime(const std::string &creationTime);
    };

} // Model

#endif //INC_DE9262A6A4F5421F846C6B48EBD75342
