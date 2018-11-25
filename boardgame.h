#ifndef BOARDGAME_H
#define BOARDGAME_H

#include <QString>

struct Boardgame {
    int id;
    QString name;
    int min;
    int max;
    int time;
    int rating;
};

#endif // BOARDGAME_H
