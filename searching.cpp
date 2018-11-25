#include "ui_search.h"
#include "searching.h"

#include <QMessageBox>

Searching::Searching(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

Searching::~Searching()
{
    delete ui;
}

void Searching::on_cancleButton_clicked()
{
    close();
}

void Searching::on_searchButton_clicked()
{
    if (ui->tabWidget->currentIndex() == 0)
    {
        if (ui->nameSearch->displayText().length() == 0)
        {
           QMessageBox::warning(this, "Ahtung!", "You have not written the name!");
           return;
        }
        emit nameSent(ui->nameSearch->displayText());
    }
    else if (ui->tabWidget->currentIndex() == 1)
    {
        emit playersSent(ui->playersEdit->value());
    }
    else if (ui->tabWidget->currentIndex() == 2)
    {
        if (ui->maxTimeSearch->value() < ui->minTimeSearch->value())
        {
           QMessageBox::warning(this, "Ahtung!", "Maximum have to be more then minimum!");
           return;
        }
        emit timeSent(ui->minTimeSearch->value(), ui->maxTimeSearch->value());
    }
    else if (ui->tabWidget->currentIndex() == 3)
    {
        if (ui->maxTimeSearch->value() < ui->minTimeSearch->value())
        {
           QMessageBox::warning(this, "Ahtung!", "Maximum have to be more then minimum!");
           return;
        }
        emit otherSent(ui->playersSpinBox->value(), ui->minTimeSpinBox->value(), ui->maxTimeSpinBox->value());
    }
    close();
}
