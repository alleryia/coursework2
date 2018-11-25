#ifndef DBMANAGEMENT_H
#define DBMANAGEMENT_H

#include "boardgame.h"
#include <QtSql>
#include <vector>

class DBManagement
{
    QSqlDatabase database;
    QSqlQuery* query;
public:
    DBManagement(QString path);
    ~DBManagement();

    std::vector<Boardgame> selectAllData();
    void addGame(const Boardgame& game);
    void updateGame(const Boardgame& game);
    void deleteGame(int id);
    std::vector<Boardgame> searchByName(QString name);
    std::vector<Boardgame> searchByPlayers(int amt);
    std::vector<Boardgame> searchByTime(int min, int max);
    std::vector<Boardgame> searchByOther(int amt, int min, int max);

private:
    std::vector<Boardgame> getData(QString  request);
};

#endif // DBMANAGEMENT_H
