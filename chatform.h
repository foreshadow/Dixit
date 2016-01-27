#ifndef CHATFORM_H
#define CHATFORM_H

#include <QWidget>

namespace Ui {
class ChatForm;
}

class ChatForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatForm(QWidget *parent = 0);
    ~ChatForm();

private:
    Ui::ChatForm *ui;
};

#endif // CHATFORM_H
