#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dbmanagement.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addData(const Boardgame& game);
    void updateData(const Boardgame& game);
    void deleteData(int id);
    void gameSelected(const QModelIndex&);
    void searchingName(QString name);
    void searchingPlayer(int amt);
    void searchingTime(int min, int max);
    void searchingOther(int amt, int min, int max);
    void on_addition_clicked();
    void on_searchButton_clicked();
    void on_undoButton_clicked();

private:
    Ui::MainWindow *ui;
    DBManagement* db;
    std::vector<Boardgame> vect;

    void redrawTable();
};

#endif // MAINWINDOW_H
