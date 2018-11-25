#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

#include "dbmanagement.h"
#include "boardgame.h"

namespace Ui {
class Dialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT
public:
    AddDialog(QWidget *parent = nullptr);
    ~AddDialog();

signals:
    void gameSentForAddition(const Boardgame&);

private slots:
    void on_cancelButton_clicked();
    void on_saveButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // ADDDIALOG_H
