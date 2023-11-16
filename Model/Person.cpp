//
// Created by Mohamed Abdelhady on 9/28/2023.
//

#include "Person.h"

namespace Model {
    Person::Person() {}

    Person::Person(std::string &id, const std::string &name, const std::string &username, const std::string &password,
                   const std::string &email, const std::string &creationTime, const bool state)
            : id(id), name(name), username(username), password(password), email(email), creationTime(creationTime),
              state(state) {}

    bool Person::operator==(const long long &id) const {
        return (this->id == std::to_string(id));
    }

    bool Person::operator==(const std::string &username) const {
        return (this->username == username);
    }

    const std::string Person::toString() {
        return std::string();
    }

    const std::string &Person::getUsername() const {
        return username;
    }

    void Person::setUsername(const std::string &username) {
        Person::username = username;
    }

    const std::string &Person::getName() const {
        return name;
    }

    void Person::setName(const std::string &name) {
        Person::name = name;
    }

    const std::string &Person::getId() const {
        return id;
    }

    void Person::setId(const std::string &id) {
        Person::id = id;
    }

    const std::string &Person::getPassword() const {
        return password;
    }

    void Person::setPassword(const std::string &password) {
        Person::password = password;
    }

    const std::string &Person::getEmail() const {
        return email;
    }

    void Person::setEmail(const std::string &email) {
        Person::email = email;
    }

    bool Person::getState() const {
        return state;
    }

    void Person::setState(bool state) {
        Person::state = state;
    }

    const std::string &Person::getCreationTime() const {
        return creationTime;
    }

    void Person::setCreationTime(const std::string &creationTime) {
        Person::creationTime = creationTime;
    }

} // Model