#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "persondialog.h"
#include "person.h"
#include <cmath>
//#include <stdio.h>
#include <stdlib.h>


#define MAXLENGTH 20

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void addPersonDialog();
    void cancelPersonDlg( PersonDialog*);

    void on_addDialogBtn_clicked();

    void on_calculateBtn_clicked();

private:
    Ui::MainWindow *ui;
    QList<PersonDialog*> m_PersonDlgs;



///    char pound = 156;
    QString pound;

    void insertion_sort(Person label[], int length);
    double average(Person label[], int length);
    void transactionNeed(Person label[], int length, double average);

};

#endif // MAINWINDOW_H
