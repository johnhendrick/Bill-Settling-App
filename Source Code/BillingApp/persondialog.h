#ifndef PERSONDIALOG_H
#define PERSONDIALOG_H

#include <QWidget>

namespace Ui {
class PersonDialog;
}

class PersonDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PersonDialog(QWidget *parent = 0);
    QString name() const;
    qreal price() const;
    ~PersonDialog();
signals:
    void cancelPersonDlg( PersonDialog*);

private slots:
    void on_cancelBtn_clicked();
    void on_priceLineEdit_textChanged(const QString &arg1);

private:
    Ui::PersonDialog *ui;
    QString pound;

    bool isInvalidPrice(const QString & priceStr);
};

#endif // PERSONDIALOG_H
