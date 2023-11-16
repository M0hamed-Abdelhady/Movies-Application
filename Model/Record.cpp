//
// Created by Mohamed Abdelhady on 9/29/2023.
//

#include "Record.h"

namespace Model {
    Record::Record() {}

    Record::Record(const std::string &entity) {
        std::vector<std::string> data = Assistant::removingDelimiter(entity, '|');
        this->userId = data[0];
        this->movieId = data[1];
        this->type = stoi(data[2]);
        this->watchedRatio = stod(data[3]);
        this->time = data[4];
    }

    Record::Record(const std::string &userId, const std::string &movieId, const int &type, const std::string &time,
                   double watchedRatio)
            :  userId(userId), movieId(movieId), time(time), type(type),
              watchedRatio(watchedRatio) {}

    std::string Record::toString() const {
        std::vector<std::string> data{ this->userId, this->movieId, std::to_string(this->type), std::to_string(this->watchedRatio),
                            this->time};
        return Assistant::addingDelimiter(data, '|');
    }

    const std::string &Record::getUserId() const {
        return userId;
    }

    void Record::setUserId(const std::string &userId) {
        Record::userId = userId;
    }

    const std::string &Record::getMovieId() const {
        return movieId;
    }

    void Record::setMovieId(const std::string &movieId) {
        Record::movieId = movieId;
    }

    const std::string &Record::getTime() const {
        return time;
    }

    void Record::setTime(const std::string &time) {
        Record::time = time;
    }

    double Record::getWatchedRatio() const {
        return watchedRatio;
    }

    void Record::setWatchedRatio(double watchedRatio) {
        Record::watchedRatio = watchedRatio;
    }

    int Record::getType() const {
        return type;
    }

    void Record::setType(int type) {
        Record::type = type;
    }

} // Model