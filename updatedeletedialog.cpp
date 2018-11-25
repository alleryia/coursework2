#include "ui_dialog.h"
#include "updatedeletedialog.h"

#include <QMessageBox>

UpdateDeleteDialog::UpdateDeleteDialog(const Boardgame& game, QWidget *parent) :
    QDialog(parent)
  , ui(new Ui::Dialog)
  , game(game)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->saveButton->setDefault(true);

    ui->nameEdit->setText(game.name);
    ui->minEdit->setValue(game.min);
    ui->maxEdit->setValue(game.max);
    ui->timeEdit->setValue(game.time);
    ui->ratingEdit->setValue(game.rating);
}

UpdateDeleteDialog::~UpdateDeleteDialog()
{
    delete ui;
}

void UpdateDeleteDialog::on_cancelButton_clicked()
{
    close();
}

void UpdateDeleteDialog::on_saveButton_clicked()
{
    if (ui->nameEdit->displayText().length() == 0)
    {
       QMessageBox::warning(this, "Ahtung!", "You have not written the name!");
       return;
    }

    if (ui->minEdit->value() > ui->maxEdit->value())
    {
        QMessageBox::warning(this, "Ahtung!", "Maximum value have to be more then minimum!");
        return;
    }

    if (game.name != ui->nameEdit->displayText() ||
        game.min != ui->minEdit->value() ||
        game.max != ui->maxEdit->value() ||
        game.time != ui->timeEdit->value() ||
        game.rating != ui->ratingEdit->value())
    {
        Boardgame newGame;
        newGame.id = game.id;
        newGame.name = ui->nameEdit->displayText();
        newGame.min = ui->minEdit->value();
        newGame.max = ui->maxEdit->value();
        newGame.time = ui->timeEdit->value();
        newGame.rating = ui->ratingEdit->value();
        emit gameSentToUpdate(newGame);
    }

    close();
}


void UpdateDeleteDialog::on_deleteButton_clicked()
{
    auto answer = QMessageBox::question(this,
                          "Question",
                          "Are you sure?",
                          QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                          QMessageBox::Cancel);
    if (answer == QMessageBox::Yes)
    {
        emit gameSentToDelete(game.id);
        close();
    }
    else if (answer == QMessageBox::No)
    {
        close();
    }
}
