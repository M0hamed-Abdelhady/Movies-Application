//
// Created by Mohamed Abdelhady on 6/20/2023.
//


using namespace std;

#ifndef MOVIESAPP_MOVIE_H
#define MOVIESAPP_MOVIE_H

#include "../Assistant.h"
#include <string>
#include <vector>

namespace Model {
    class Movie {
        string id, name, year, rate, story, creationTime;
        int duration;

    public:
        Movie();

        Movie(const string &entity);

        Movie(const string &id, const string &name, const string &year, const string &rate, const string &duration,
              const string &story, const string &creationTime);

        const string toString();

        string &getName();

        void setName(const string &name);

        string &getId();

        void setId(const string &id);

        string &getRate();

        void setRate(const string &rate);

        string &getYear();

        void setYear(const string &year);

        string &getStory();

        void setStory(const string &story);

        string &getCreationTime();

        void setCreationTime(const string &creationTime);

        int getDuration();

        void setDuration(int duration);

    };

}
#endif //MOVIESAPP_MOVIE_H