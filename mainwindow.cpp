#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSplashScreen>
#include <ctime>

#include "card.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QSplashScreen splash(QPixmap("splash.png"));
    int t = clock();
    splash.show();
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->setSceneRect(0, 0, 798, 558);
    for (int i = 0; i < 84; i++)
    {
        QGraphicsItem *item = new Card(i, QString("img/%1.png").arg(i + 1, 2, 10, QChar('0')));
        item->setPos(i % 14 * 50, i / 14 * 50);
        item->setVisible(false);
        ui->graphicsView->scene()->addItem(item);
    }
    while (clock() - t < 2500)
        QCoreApplication::processEvents();
}

MainWindow::~MainWindow()
{
    delete ui;
}
