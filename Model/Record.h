//
// Created by Mohamed Abdelhady on 9/29/2023.
//

#ifndef INC_67FA1C105AB14B46870832465FF2DE9B
#define INC_67FA1C105AB14B46870832465FF2DE9B

#include "../Assistant.h"

namespace Model {

    class Record {
        std::string userId, movieId, time;
        int type;
        double watchedRatio;

    public:
        Record();

        Record(const std::string &entity);

        Record(const std::string &userId, const std::string &movieId, const int &type, const std::string &time,
               double watchedRatio = 0);

        std::string toString() const;

        const std::string &getUserId() const;

        void setUserId(const std::string &userId);

        const std::string &getMovieId() const;

        void setMovieId(const std::string &movieId);

        const std::string &getTime() const;

        void setTime(const std::string &time);

        double getWatchedRatio() const;

        void setWatchedRatio(double watchedRatio);

        int getType() const;

        void setType(int type);
    };

} // Model

#endif //INC_67FA1C105AB14B46870832465FF2DE9B
