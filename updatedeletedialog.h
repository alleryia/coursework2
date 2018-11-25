#ifndef UPDATEDELETEDIALOG_H
#define UPDATEDELETEDIALOG_H

#include <QDialog>

#include "dbmanagement.h"
#include "boardgame.h"

namespace Ui {
class Dialog;
}

class UpdateDeleteDialog : public QDialog
{
    Q_OBJECT
public:
    UpdateDeleteDialog(const Boardgame& game, QWidget *parent = nullptr);
    ~UpdateDeleteDialog();

signals:
    void gameSentToUpdate(const Boardgame&);
    void gameSentToDelete(int);

private slots:
    void on_cancelButton_clicked();
    void on_deleteButton_clicked();
    void on_saveButton_clicked();

private:
    Ui::Dialog *ui;
    Boardgame game;
};

#endif // UPDATEDELETEDIALOG_H
