//
// Created by Mohamed Abdelhady on 6/19/2023.
//
#include "User.h"

using namespace std;


namespace Model {
    User::User(const std::string &entity) {
        std::vector<std::string> data = Assistant::removingDelimiter(entity, '|');
        this->setId(data[0]) ;
        this->setUsername(data[1]);
        this->setPassword(data[2]);
        this->setName(data[3]);
        this->setEmail(data[4]);
        this->setCreationTime(data[5]);
    }

    const std::string User::toString() {
        vector<string> data = {this->getId(), this->getUsername(), this->getPassword()};
        data.push_back(this->getName());
        data.push_back(this->getEmail());
        data.push_back(this->getCreationTime());
        return Assistant::addingDelimiter(data, '|');
    }

    const map<std::string, Model::Record> &User::getHistory() {
        return history;
    }

    void User::setHistory(map<string, Model::Record> &allHistory) {
        history = allHistory;
    }

    const map<string, Model::Record> &User::getFavourite() {
        return favourite;
    }

    void User::setFavourite(map<string, Model::Record> &allFavourite) {
        favourite = allFavourite;
    }

    Model::Record &User::getRecord(const std::string &movieId, int type) {
        if (type == 1)
            return this->history[movieId];
        else if (type == 2)
            return this->favourite[movieId];
    }

    void User::setRecord(Model::Record &record) {
        if (record.getType() == 1)
            history[record.getMovieId()] = record,
                    watched[record.getMovieId()] = true;
        else if (record.getType() == 2)
            this->favourite[record.getMovieId()] = record,
                    this->isInFavourite[record.getMovieId()] = true;
    }

    void User::removeFromRecords(const std::string &movieId, int type) {
        if (type == 1)
            history.erase(movieId),
                    watched.erase(movieId);
        else if (type == 2)
            this->favourite.erase(movieId),
                    this->isInFavourite.erase(movieId);
    }

    void User::clearHistory() {
        this->history.clear();
        this->watched.clear();
    }

    void User::clearFavourite() {
        this->favourite.clear();
        this->isInFavourite.clear();

    }


} // Model
