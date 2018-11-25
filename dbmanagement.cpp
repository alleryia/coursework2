#include "dbmanagement.h"

DBManagement::DBManagement(QString path)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(path);
    if (!database.open())
    {
        exit(1);
    }
    query = new QSqlQuery(database);
}

DBManagement::~DBManagement()
{
    delete query;
}

std::vector<Boardgame> DBManagement::getData(QString request)
{
    query->exec(request);

    std::vector<Boardgame> vect;
    Boardgame game;
    while (query->next())
    {
        game.id = query->value(0).toInt();
        game.name = query->value(1).toString();
        game.min = query->value(2).toInt();
        game.max = query->value(3).toInt();
        game.time = query->value(4).toInt();
        game.rating = query->value(5).toInt();
        vect.push_back(game);
    }
    return vect;
}

std::vector<Boardgame> DBManagement::selectAllData()
{
    return getData("SELECT * FROM OtherGames;");
}

void DBManagement::addGame(const Boardgame& game)
{
    query->prepare("INSERT INTO OtherGames (Name, MinPlayers, MaxPlayers, Time, Rating) "
                   "VALUES (:n, :min, :max, :t, :r);");
    query->bindValue(":n", game.name);
    query->bindValue(":min", game.min);
    query->bindValue(":max", game.max);
    query->bindValue(":t", game.time);
    query->bindValue(":r", game.rating);
    query->exec();
}

void DBManagement::updateGame(const Boardgame& game)
{
    query->prepare("UPDATE OtherGames "
                   "SET Name=:n, MinPlayers=:min, MaxPlayers=:max, Time=:t, Rating=:r "
                   "WHERE Id=:id;");
    query->bindValue(":n", game.name);
    query->bindValue(":min", game.min);
    query->bindValue(":max", game.max);
    query->bindValue(":t", game.time);
    query->bindValue(":r", game.rating);
    query->bindValue(":id", game.id);
    query->exec();
}

void DBManagement::deleteGame(int id)
{
    query->prepare("DELETE FROM OtherGames WHERE Id=:id;");
    query->bindValue(":id", id);
    query->exec();
}

std::vector<Boardgame> DBManagement::searchByName(QString name)
{
    return getData("SELECT * FROM OtherGames WHERE Name LIKE '%" + name + "%';");
}

std::vector<Boardgame> DBManagement::searchByPlayers(int amt)
{
    return getData("SELECT * FROM OtherGames WHERE MinPlayers<=" +
                   QString::number(amt) + " AND MaxPlayers>=" +
                   QString::number(amt) + ";");
}

std::vector<Boardgame> DBManagement::searchByTime(int min, int max)
{
    return getData("SELECT * FROM OtherGames WHERE Time>=" +
                   QString::number(min) + " AND Time<=" +
                   QString::number(max) + ";");
}

std::vector<Boardgame> DBManagement::searchByOther(int amt, int min, int max)
{
    return getData("SELECT * FROM OtherGames WHERE Time>=" +
                   QString::number(min) + " AND Time<=" +
                   QString::number(max) + " AND MinPlayers<=" +
                   QString::number(amt) + " AND MaxPlayers>=" +
                   QString::number(amt) + ";");
}
