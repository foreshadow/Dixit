#include "chatform.h"
#include "ui_chatform.h"

#include <QTime>

ChatForm::ChatForm(QString myId, QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::ChatForm),
    myId(myId)
{
    ui->setupUi(this);
}

ChatForm::~ChatForm()
{
    delete ui;
}

void ChatForm::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}

void ChatForm::on_pushButton_clicked()
{
    QString message = ui->lineEdit->text();
    emit send(message);
    ui->lineEdit->clear();
}

void ChatForm::append(QString message)
{
    ui->textEdit->append(message);
}
