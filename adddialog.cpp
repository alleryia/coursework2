#include "ui_dialog.h"
#include "adddialog.h"

#include <QMessageBox>

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->deleteButton->hide();
    ui->saveButton->setDefault(true);
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_cancelButton_clicked()
{
    close();
}

void AddDialog::on_saveButton_clicked()
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

    Boardgame game;
    game.name = ui->nameEdit->displayText();
    game.min = ui->minEdit->value();
    game.max = ui->maxEdit->value();
    game.time = ui->timeEdit->value();
    game.rating = ui->ratingEdit->value();
    emit gameSentForAddition(game);
    close();
}
