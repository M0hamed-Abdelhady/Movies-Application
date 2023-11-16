//
// Created by Mohamed Abdelhady on 6/19/2023.
//


#ifndef MOVIESAPP_ADMIN_H
#define MOVIESAPP_ADMIN_H

#include "Person.h"

namespace Model {
    class Admin : public Person {
        std::string becameAdminTime;
    public:
        using Person::Person;

        explicit Admin(const std::string &entity);

        const std::string toString() override;

        const std::string &getBecameAdminTime() const;

        void setBecameAdminTime(const std::string &becameAdminTime);


        friend class assistant;
    };

} // Model

#endif //MOVIESAPP_ADMIN_H


