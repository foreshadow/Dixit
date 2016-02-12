#ifndef CHATFORM_H
#define CHATFORM_H

#include <QDockWidget>

namespace Ui {
class ChatForm;
}

class ChatForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChatForm(QWidget *parent = 0, QString myId = QString());
    ~ChatForm();

    void resizeEvent(QResizeEvent *);

    void setId(const QString &id);

    void appendc(QString msg, QColor color = Qt::black);

private slots:
    void on_lineEdit_returnPressed();
    void on_pushButton_clicked();

private:
    Ui::ChatForm *ui;

protected:
    QString myId;

signals:
    void send(QString);

public slots:
//    void append(QString message);
//    void appendSys(QString message);
};

#endif // CHATFORM_H
