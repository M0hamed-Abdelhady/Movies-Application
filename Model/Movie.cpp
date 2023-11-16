//
// Created by Mohamed Abdelhady on 6/20/2023.
//
#include "Movie.h"

namespace Model {
    Movie::Movie() {}

    Movie::Movie(const string &entity) {
        vector <string> data = Assistant::removingDelimiter(entity, '|');
        this->id = data[0];
        this->name = data[1];
        this->year = data[2];
        this->rate = data[3];
        this->duration = stoi(data[4]);
        this->story = data[5];
        this->creationTime = data[6];

    }

    Movie::Movie(const string &id, const string &name, const string &year, const string &rate, const string &duration,
                 const string &story, const string &creationTime) : id(id), name(name), year(year), rate(rate),
                                                                    duration(stoi(duration)), story(story),
                                                                    creationTime(creationTime) {}

    const string Movie::toString() {
        vector <string> data = {this->id, this->name, this->year, this->rate, to_string(this->duration), this->story,
                                this->creationTime};
        return Assistant::addingDelimiter(data, '|');
    }

    string &Movie::getName() {
        return this->name;
    }

    void Movie::setName(const string &name) {
        this->name = name;
    }

    string &Movie::getId() {
        return this->id;
    }

    void Movie::setId(const string &id) {
        this->id = id;

    }

    string &Movie::getRate() {
        return this->rate;
    }

    void Movie::setRate(const string &rate) {
        this->rate = rate;
    }

    string &Movie::getYear() {
        return this->year;
    }

    void Movie::setYear(const string &year) {
        this->year = year;
    }

    string &Movie::getStory() {
        return this->story;
    }

    void Movie::setStory(const string &story) {
        this->story = story;
    }

    string &Movie::getCreationTime() {
        return this->creationTime;
    }

    void Movie::setCreationTime(const string &creationTime) {
        this->creationTime = creationTime;
    }

    int Movie::getDuration() {
        return this->duration;
    }

    void Movie::setDuration(int duration) {
        this->duration = duration;
    }
}

