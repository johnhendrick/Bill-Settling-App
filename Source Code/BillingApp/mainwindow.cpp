#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pound( "£" )
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes.append( width() / 2 );
    sizes.append( width() / 2 );
    ui->splitter->setSizes( sizes );
    addPersonDialog();
    addPersonDialog();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPersonDialog()
{
    PersonDialog *tmpDlg = new PersonDialog( this );
    tmpDlg->setContentsMargins( 0 , 0 , 0 , 0 );
//    tmpDlg->setMinimumSize( 0 , 50 );
//    tmpDlg->setMaximumSize( 10000 , 50 );
    m_PersonDlgs.append( tmpDlg );
    ui->personDlgslayout->insertWidget( 0 ,  tmpDlg );
    connect( tmpDlg , SIGNAL( cancelPersonDlg(PersonDialog*) ),
        this, SLOT( cancelPersonDlg(PersonDialog*) ) );
}

void MainWindow::cancelPersonDlg(PersonDialog * dlg)
{
     ui->personDlgslayout->removeWidget( dlg );
     m_PersonDlgs.removeAll( dlg );
     delete dlg;
}

void MainWindow::on_addDialogBtn_clicked()
{
    addPersonDialog();
}

void MainWindow::on_calculateBtn_clicked()
{
    ui->reportTextEdit->clear();
    const int LENGTH = m_PersonDlgs.size();

    Person person[ MAXLENGTH ];
    for (int i = 0; i < LENGTH; i++)
    {
        PersonDialog *tmpDlg = m_PersonDlgs.at( i );
        person[i].init(tmpDlg->name().toStdString()  , tmpDlg->price() );
    }
    ui->reportTextEdit->append( "\nPayments summary: " );
    for (int i = 0; i < LENGTH; i++)
    {
        QString name = QString::fromStdString( person[i].getName() );
        QString price = QString::number( person[i].getMoney() );

        QString msg = name + "\t" + pound + price;
        ui->reportTextEdit->append(  msg );
//        cout << person[i].getName() << "\t"<<pound << person[i].getMoney() << endl;
    }
    ui->reportTextEdit->append(  "\n" );
    insertion_sort(person, LENGTH);
    double averagePaid = average(person,LENGTH);

    for (int i = 0; i < LENGTH; i++)
    {
        double extra = (person[i].getMoney() - averagePaid);
        person[i].setShouldReceive(extra);
        if (extra > 0)
        {
            QString nameI = QString::fromStdString( person[i].getName() );
            QString price = QString::number( fabs(person[i].getShouldReceive()) );
            QString msg = "Someone needs to pay " + nameI + " " + pound + price;
            ui->reportTextEdit->append(  msg );

        }
        else if (extra < 0)
        {
            QString nameI = QString::fromStdString( person[i].getName() );
            QString price = QString::number( fabs(person[i].getShouldReceive()) );
            QString msg = nameI + " needs to pay " + pound + price;
            ui->reportTextEdit->append(  msg );

//            cout << nameI << " needs to pay " <<pound << price << endl;
        }
    }
    ui->reportTextEdit->append(  "\n" + QString(80, '-') + "\n" );
    transactionNeed(person, LENGTH,averagePaid);


}

void MainWindow::insertion_sort(Person label[], int length)
{
    int i, j;
    Person tmp;

    for (i = 1; i < length; i++)
    {
        j = i;
        while (j>0 && label[j - 1].getMoney() > label[j].getMoney())
        {
            tmp = label[j];
            label[j] = label[j - 1];
            label[j - 1] = tmp;
            j--;
        }
    }
}

double MainWindow::average(Person person[], int length)
{
    double total = 0;
    for (int i = 0; i < length; i++)
    {

        total+= person[i].getMoney();
    }
    return total/length;
}

void MainWindow::transactionNeed(Person label[], int length, double average)
{
    int halfway = length / 2;
    Q_UNUSED( halfway )
    Q_UNUSED( average )
    int i = 0;
    int j = length-1;

    while (i < j)
    {
            if (label[i].getShouldReceive() + label[j].getShouldReceive() > 0)
            {
                QString nameI = QString::fromStdString( label[i].getName() );
                QString nameJ = QString::fromStdString( label[j].getName() );
                QString price = QString::number( fabs(label[i].getShouldReceive()) );

                QString msg = nameI + " should pay " + nameJ + " " + pound + " " + price;
                ui->reportTextEdit->append(  msg );

                label[j].setShouldReceive(label[j].getShouldReceive() + label[i].getShouldReceive());
                label[i].setShouldReceive(label[i].getShouldReceive() + fabs(label[i].getShouldReceive()));
                i++;
            }
            else if (label[i].getShouldReceive() + label[j].getShouldReceive() < 0)
            {
                QString nameI = QString::fromStdString( label[i].getName() );
                QString nameJ = QString::fromStdString( label[j].getName() );
                QString price = QString::number( fabs(label[j].getShouldReceive()) );

                QString msg = nameI + " should pay " + nameJ + " " + pound + " " + price;
                ui->reportTextEdit->append(  msg );

///                cout << label[i].getName() << " should pay " << label[j].getName() << " " << pound << " " << fabs(label[j].getShouldReceive()) << endl;
                label[i].setShouldReceive(label[i].getShouldReceive() + fabs(label[j].getShouldReceive()));
                label[j].setShouldReceive(0);
                j--;
            }
            else if (label[i].getShouldReceive() + label[j].getShouldReceive() == 0)
            {
///                cout << label[i].getName() << " should pay " << label[j].getName() << " " << pound << " " << fabs(label[i].getShouldReceive()) << endl;
                QString nameI = QString::fromStdString( label[i].getName() );
                QString nameJ = QString::fromStdString( label[j].getName() );
                QString price = QString::number( fabs(label[i].getShouldReceive()) );

                QString msg = nameI + " should pay " + nameJ + " " + pound + " " + price;
                ui->reportTextEdit->append(  msg );

                i++;
                j--;
            }
    }
}
