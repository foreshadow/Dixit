#include "chatform.h"
#include "ui_chatform.h"

ChatForm::ChatForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatForm)
{
    ui->setupUi(this);
}

ChatForm::~ChatForm()
{
    delete ui;
}
