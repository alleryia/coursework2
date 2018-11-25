#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddialog.h"
#include "updatedeletedialog.h"
#include "searching.h"

#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = new DBManagement("D:\\Matherials\\Programming\\Course works\\Course work 2 V.Shekhovtsova\\Boardgames.sqlite");

    connect(ui->table, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(gameSelected(const QModelIndex&)));

    setFixedWidth(643);

    ui->undoButton->hide();

    ui->table->setColumnCount(6);
    ui->table->setColumnHidden(0, true);
    ui->table->setColumnWidth(1, 200);
    ui->table->setColumnWidth(2, 100);
    ui->table->setColumnWidth(3, 100);
    ui->table->setColumnWidth(4, 100);
    ui->table->setColumnWidth(5, 100);

    QStringList header;
    header << "" << "Name" << "Min players" << "Max players" << "Average time" << "Rating";
    ui->table->setHorizontalHeaderLabels(header);

    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table->setSelectionMode(QAbstractItemView::SingleSelection);
    vect = db->selectAllData();
    redrawTable();
}


MainWindow::~MainWindow()
{
    delete ui;
    delete db;
}

void MainWindow::redrawTable()
{
    ui->table->clearContents();
    ui->table->setRowCount(static_cast<int>(vect.size()));

    ui->table->setSortingEnabled(false);

    for (unsigned i = 0; i < vect.size(); i++)
    {
        ui->table->setItem(static_cast<int>(i), 0, new QTableWidgetItem(QString::number(i)));
        ui->table->setItem(static_cast<int>(i), 1, new QTableWidgetItem(vect[i].name));
        ui->table->setItem(static_cast<int>(i), 2, new QTableWidgetItem(QString("%1").arg(vect[i].min, 2)));
        ui->table->item(static_cast<int>(i), 2)->setTextAlignment(Qt::AlignCenter);
        ui->table->setItem(static_cast<int>(i), 3, new QTableWidgetItem(QString("%1").arg(vect[i].max, 2)));
        ui->table->item(static_cast<int>(i), 3)->setTextAlignment(Qt::AlignCenter);
        ui->table->setItem(static_cast<int>(i), 4, new QTableWidgetItem(QString("%1").arg(vect[i].time, 3)));
        ui->table->item(static_cast<int>(i), 4)->setTextAlignment(Qt::AlignCenter);
        ui->table->setItem(static_cast<int>(i), 5, new QTableWidgetItem(QString::number(vect[i].rating)));
        ui->table->item(static_cast<int>(i), 5)->setTextAlignment(Qt::AlignCenter);
    }
    ui->table->setSortingEnabled(true);
}

void MainWindow::addData(const Boardgame& game)
{
    db->addGame(game);

    vect = db->selectAllData();
    redrawTable();
}

void MainWindow::updateData(const Boardgame& game)
{
    db->updateGame(game);

    vect = db->selectAllData();
    redrawTable();
}

void MainWindow::deleteData(int id)
{
    db->deleteGame(id);

    vect = db->selectAllData();
    redrawTable();
}

void MainWindow::searchingName(QString name)
{
    vect = db->searchByName(name);
    redrawTable();

    ui->undoButton->show();
}

void MainWindow::searchingPlayer(int amt)
{
    vect = db->searchByPlayers(amt);
    redrawTable();

    ui->undoButton->show();
}

void MainWindow::searchingTime(int min, int max)
{
    vect = db->searchByTime(min, max);
    redrawTable();

    ui->undoButton->show();
}

void MainWindow::searchingOther(int amt, int min, int max)
{
    vect = db->searchByOther(amt, min, max);
    redrawTable();

    ui->undoButton->show();
}

void MainWindow::gameSelected(const QModelIndex&)
{
    UpdateDeleteDialog udd(vect[ui->table->item(ui->table->currentRow(), 0)->text().toUInt()]);
    connect(&udd, SIGNAL(gameSentToUpdate(const Boardgame&)), SLOT(updateData(const Boardgame&)));
    connect(&udd, SIGNAL(gameSentToDelete(int)), SLOT(deleteData(int)));
    udd.exec();
    udd.disconnect();
}

void MainWindow::on_addition_clicked()
{
    AddDialog addd;
    connect(&addd, SIGNAL(gameSentForAddition(const Boardgame&)), SLOT(addData(const Boardgame&)));
    addd.exec();
    addd.disconnect();
}

void MainWindow::on_searchButton_clicked()
{
    Searching srch;
    connect(&srch, SIGNAL(nameSent(QString)), SLOT(searchingName(QString)));
    connect(&srch, SIGNAL(playersSent(int)), SLOT(searchingPlayer(int)));
    connect(&srch, SIGNAL(timeSent(int, int)), SLOT(searchingTime(int, int)));
    connect(&srch, SIGNAL(otherSent(int, int, int)), SLOT(searchingOther(int, int, int)));
    srch.exec();
    srch.disconnect();
}

void MainWindow::on_undoButton_clicked()
{
    vect = db->selectAllData();
    redrawTable();
    ui->undoButton->hide();
}
