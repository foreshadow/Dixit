#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QString>
#include "tcpsocket.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString id;
    TcpSocket *socket = new TcpSocket;
    LoginDialog dlg(socket, id);
    if (dlg.exec() == QDialog::Accepted)
    {
        MainWindow w(socket, id);
        w.show();
        int r = a.exec();
        delete socket;
        return r;
    }
    delete socket;
    return 0;
}
