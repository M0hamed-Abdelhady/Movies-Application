//
// Created by Mohamed Abdelhady on 6/19/2023.
//
#include "Admin.h"


namespace Model {
    Admin::Admin(const std::string &entity) {
        std::vector<std::string> data = Assistant::removingDelimiter(entity, '|');
        this->setId(data[0]) ;
        this->setUsername(data[1]);
        this->setPassword(data[2]);
        this->setName(data[3]);
        this->setEmail(data[4]);
        this->setCreationTime(data[5]);
        this->setBecameAdminTime(data[6]);
    }

    const std::string Admin::toString() {
        std::vector<std::string> data = {this->getId(), this->getUsername(), this->getPassword()};
        data.push_back(this->getName());
        data.push_back(this->getEmail());
        data.push_back(this->getCreationTime());
        data.push_back(this->becameAdminTime);
        return Assistant::addingDelimiter(data, '|');
    }

    const std::string &Admin::getBecameAdminTime() const {
        return becameAdminTime;
    }

    void Admin::setBecameAdminTime(const std::string &becameAdminTime) {
        Admin::becameAdminTime = becameAdminTime;
    }
}