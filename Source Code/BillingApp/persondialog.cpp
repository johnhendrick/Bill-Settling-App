#include "persondialog.h"
#include "ui_persondialog.h"

PersonDialog::PersonDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonDialog),
    pound( "£" )
{
    ui->setupUi(this);
    ui->priceLineEdit->setText( pound + "0" );
//    ui->priceLineEdit->setValidator( new QIntValidator(0, 100, this) );
}

QString PersonDialog::name() const
{
    return ui->nameLineEdit->text();
}

qreal PersonDialog::price() const
{
    QString tmpStrPrice = ui->priceLineEdit->text();
    tmpStrPrice.replace( pound  , "" );
    return tmpStrPrice.toDouble();
}

PersonDialog::~PersonDialog()
{
    delete ui;
}

void PersonDialog::on_cancelBtn_clicked()
{
    emit cancelPersonDlg( this );
}

void PersonDialog::on_priceLineEdit_textChanged(const QString &arg1)
{
    blockSignals( true );
    if( arg1.size() > 0 && arg1.at( 0 ) != pound ){
        ui->priceLineEdit->setText( pound + arg1 );
    }
    else if( arg1.isEmpty() ){
        ui->priceLineEdit->setText( pound + "0" );
    }
    if( isInvalidPrice( arg1 ) )
        ui->priceLineEdit->setText( pound + "0" );
    blockSignals( false );

}

bool PersonDialog::isInvalidPrice(const QString &priceStr )
{
    QDoubleValidator v( 0.0 , 99999999.99 , 2 , this);
    QString str = priceStr;
    str.replace( pound  , "" );
    int pos = 0;
    v.validate( str , pos );
    QValidator::State state =  v.validate( str , pos );
    return state == QValidator::Invalid;
}
