//
// Created by Mohamed Abdelhady on 6/19/2023.
//


#ifndef MOVIESAPP_COSTUMER_H
#define MOVIESAPP_COSTUMER_H

#include "Person.h"
#include "Record.h"
#include "Movie.h"

namespace Model {
    class User : public Person {
        map<string, Model::Record> history, favourite;

    public:
        using Person::Person;

        explicit User(const std::string &entity);

        map<string, bool> watched, isInFavourite;

        const std::string toString() override;

        const map<std::string, Model::Record> &getHistory();

        void setHistory(map<string, Model::Record> &allHistory);

        const map<string, Model::Record> &getFavourite();

        void setFavourite(map<string, Model::Record> &allFavourite);

        Model::Record &getRecord(const string &movieId,int type);

        void setRecord(Model::Record &record);

        void removeFromRecords(const string &movieId,int type);

        void clearHistory();

        void clearFavourite();

    };
} // Model

#endif //MOVIESAPP_COSTUMER_H