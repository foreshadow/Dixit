#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

#include "tcpsocket.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(TcpSocket *socket, QString &id);
    ~LoginDialog();

private:
    void echo(QString message);

private slots:
    void on_pushButtonEnter_clicked();

private:
    Ui::LoginDialog *ui;
    TcpSocket *socket;
    QString &id;
};

#endif // LOGINDIALOG_H
