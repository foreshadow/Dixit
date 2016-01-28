#include "logindialog.h"
#include "ui_logindialog.h"

#include "clientdata.h"

LoginDialog::LoginDialog(TcpSocket *socket, QString &id) :
    ui(new Ui::LoginDialog),
    socket(socket),
    id(id)
{
    ui->setupUi(this);
    ui->label->setStyleSheet("color: rgb(255, 255, 255);");
    ui->label_2->setStyleSheet("color: rgb(255, 255, 255);");
    ui->labelEcho->setStyleSheet("color: rgb(255, 255, 255);");
    QPixmap pix = QPixmap("img/bg.png").scaledToHeight(this->height());
    ui->labelPicture->setGeometry(0, 0, this->width(), this->height());
    ui->labelPicture->setPixmap(pix);
    echo("欢迎!");
    ui->lineEdit_2->setFocus();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::echo(QString message)
{
    ui->labelEcho->setText(ui->labelEcho->text() + message + "\n");
    QStringList slist = ui->labelEcho->text().split("\n");
    while (slist.size() >= 6)
        slist.erase(slist.begin());
    ui->labelEcho->setText(slist.join("\n"));
}

void LoginDialog::on_pushButtonEnter_clicked()
{
//    accept();
    QString username = ui->lineEdit_2->text();
    if (username.left(1) == "/" || username.contains(" "))
    {
        echo("Infinity不喜欢这个名字，请你换一个。");
        return;
    }
    if (socket->isConnected() == false)
    {
        QString url = ui->lineEdit->text();
        QString host = url.section(":", 0, 0);
        uint port = url.section(":", 1, 1).toInt();
        ui->pushButtonEnter->setDisabled(true);
        ui->pushButtonEnter->setText("连接中");
        repaint();
        if (socket->connectToHost(QHostAddress(host), port))
        {
            id = username;
            accept();
        }
        else
        {
            echo("连接服务器失败。");
            ui->pushButtonEnter->setEnabled(true);
            ui->pushButtonEnter->setText("连接");
        }
    }
}
