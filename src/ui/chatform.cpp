#include "chatform.h"
#include "ui_chatform.h"

#include <QTime>

ChatForm::ChatForm(QWidget *parent, QString myId) :
    QWidget(parent),
    ui(new Ui::ChatForm),
    myId(myId)
{
    ui->setupUi(this);
}

ChatForm::~ChatForm()
{
    delete ui;
}

void ChatForm::resizeEvent(QResizeEvent *)
{
    int i = 1;
}

void ChatForm::setId(const QString &id)
{
    myId = id;
}

void ChatForm::appendc(QString msg, QColor color)
{
    msg
    .replace("&", "&amp;").replace(">", "&gt;")
    .replace("<", "&lt;").replace("\"", "&quot;")
    .replace("\'", "&#39;").replace("  ", "&nbsp;")
    .replace("\n", "<br>").replace("\r", "<br>");
    QByteArray ca;
    ca.append(color.red());
    ca.append(color.green());
    ca.append(color.blue());
    ui->textEdit->append(QString("<span style=\" color:#%1;\">%2</span>")
                         .arg(QString(ca.toHex())).arg(msg));
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

//void ChatForm::append(QString message)
//{
//    ui->textEdit->append(message);
//}

//void ChatForm::appendSys(QString message)
//{
//    ui->textEdit->append(QString("<span style=\"color:#0000FF;\">%1</span>").arg(message));
//}
