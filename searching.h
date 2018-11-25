#ifndef SEARCHING_H
#define SEARCHING_H

#include <QDialog>

namespace Ui {
    class Search;
}
class Searching : public QDialog
{
    Q_OBJECT
public:
    Searching(QWidget *parent = nullptr);
    ~Searching();

signals:
    void nameSent(QString);
    void playersSent(int);
    void timeSent(int min, int max);
    void otherSent(int amt, int min, int max);

private slots:
    void on_cancleButton_clicked();
    void on_searchButton_clicked();

private:
    Ui::Search* ui;
};

#endif // SEARCHING_H
