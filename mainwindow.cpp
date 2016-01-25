#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSplashScreen>
#include <ctime>

#include "card.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QSplashScreen splash(QPixmap("img/splash.png"));
    splash.show();
    int t = clock();
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->setSceneRect(0, 0, 798, 558);
    for (int i = 0; i < 84; i++)
    {
        splash.showMessage(QString("Loading cards (%1 / 84)").arg(i + 1),
                           Qt::AlignLeft, Qt::white);
        Card *c = new Card(i, QString("img/cards/%1.png").arg(i + 1, 2, 10, QChar('0')));
        c->setVisible(false);
        ui->graphicsView->scene()->addItem(c);
        deck.addCard(c);
    }
    while (clock() - t < 2500)
    {
        splash.showMessage(QString("Waiting (%1 / 2500)").arg(clock() - t),
                           Qt::AlignLeft, Qt::white);
        QCoreApplication::processEvents();
    }
}

MainWindow::~MainWindow()
{
    deck.clear();
    delete ui;
}
