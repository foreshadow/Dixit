#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "chatform.h"
#include <QSplashScreen>
#include "clientdata.h"
#include "serverdata.h"
#include "card.h"

MainWindow::MainWindow(TcpSocket *socket, QString id) :
    ui(new Ui::MainWindow), socket(socket), myId(id), rabbits(), players(),
    gbReady(new GraphicsButton), headline(new GraphicsHeadline)
{
    connect(socket, SIGNAL(received(QByteArray)), this, SLOT(received(QByteArray)));
    QSplashScreen splash(QPixmap("img/splash.png"));
    splash.show();
    splash.showMessage("正在找桌游", Qt::AlignLeft, Qt::white);
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->setSceneRect(0, 0, 798, 598);
    ui->graphicsView->scene()->addPixmap(QPixmap("img/d.png").scaledToWidth(ui->graphicsView->width()));
    for (int i = 0; i < 84; i++)
    {
        splash.showMessage(QString("正在拿出卡牌 (%1 / 84)").arg(i + 1),
                           Qt::AlignLeft, Qt::white);
        Card *c = new Card(i, QString("img/cards/%1.png").arg(i + 1, 2, 10, QChar('0')));
        c->hide();
        ui->graphicsView->scene()->addItem(c);
        deck.addCard(c);
    }
    splash.showMessage("正在调教小白兔", Qt::AlignLeft, Qt::white);
    rabbits.append(new QGraphicsPixmapItem(QPixmap("img/rabbit/green.png" ).scaledToHeight(120)));
    rabbits.append(new QGraphicsPixmapItem(QPixmap("img/rabbit/blue.png"  ).scaledToHeight(120)));
    rabbits.append(new QGraphicsPixmapItem(QPixmap("img/rabbit/black.png" ).scaledToHeight(120)));
    rabbits.append(new QGraphicsPixmapItem(QPixmap("img/rabbit/pink.png"  ).scaledToHeight(120)));
    rabbits.append(new QGraphicsPixmapItem(QPixmap("img/rabbit/yellow.png").scaledToHeight(120)));
    rabbits.append(new QGraphicsPixmapItem(QPixmap("img/rabbit/white.png" ).scaledToHeight(120)));
    for (int i = 0; i < 6; i++)
    {
        static const QPoint p[] = {{0, 0}, {300, 0}, {600, 0}, {0, 200}, {600, 200}, {0, 400}};
        rabbits[i]->setPos(p[i]);
        rabbits[i]->hide();
        ui->graphicsView->scene()->addItem(rabbits[i]);
    }
    splash.showMessage("正在准备茶水", Qt::AlignLeft, Qt::white);
    ChatForm *cf = new ChatForm(myId, this);
    connect(cf, SIGNAL(send(QString)), this, SLOT(chatFormSend(QString)));
    connect(this, SIGNAL(chatFormAppend(QString)), cf, SLOT(append(QString)));
    cf->setFeatures(QDockWidget::DockWidgetFloatable);
    cf->setFloating(true);
    QPoint mtg = mapToGlobal(this->geometry().topLeft());
    cf->setGeometry(mtg.x() + this->width() + 16, mtg.y(), cf->width(), cf->height());
    splash.showMessage("正在说你好", Qt::AlignLeft, Qt::white);
    sendClientData(ClientData(ClientData::SET_ID, myId, myId));
    sendClientData(ClientData(ClientData::CHAT, myId, myId + "加入了房间。"));
    connect(gbReady, SIGNAL(clicked()), this, SLOT(onGBReadyClicked()));
    gbReady->setImage("img/start.png");
    gbReady->setPos(600, 500);
    ui->graphicsView->scene()->addItem(gbReady);
    headline->setImage("img/banner.png");
    headline->setPos(180, 120);
    headline->setText("欢迎！");
    ui->graphicsView->scene()->addItem(headline);
}

MainWindow::~MainWindow()
{
    deck.clear();
    delete ui;
}

void MainWindow::handle(ServerData sd)
{
    switch (sd.getType())
    {
    case ServerData::CHAT:
    case ServerData::PHRASE:
        emit chatFormAppend(QString("%1 %2\n  %3")
                            .arg(sd.getFromUser())
                            .arg(sd.getUtc().toLocalTime().toString("hh:mm:ss"))
                            .arg(sd.getContent()));
        break;
    case ServerData::REQUEST_ID:
        break;
    case ServerData::READY:
        if (sd.getFromUser() == myId)
            gbReady->hide();
        rabbits.at(players.size())->show();
        players.append(new Player(sd.getFromUser(), nullptr));
        emit chatFormAppend(sd.getFromUser() + "准备就绪。");
        break;
    case ServerData::DESC:
        emit chatFormAppend(QString("%1的描述为%2。").arg(sd.getFromUser()).arg(sd.getContent()));
        break;
    case ServerData::PLAY:
        break;
    case ServerData::SELECT:
        break;
    case ServerData::DRAW:
        for (int i = 0; i < sd.getCards().size(); i++)
            hcards.addCard(deck.getCard(sd.getCards().at(i)));
        update();
        break;
    case ServerData::SYNC:
        break;
    }
}

void MainWindow::received(QByteArray message)
{
    handle(ServerData(QDataStream(message)));
}

void MainWindow::sendClientData(ClientData cd)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);
    out << cd;
    socket->send(block);
}

void MainWindow::chatFormSend(QString message)
{
    sendClientData(ClientData(ClientData::CHAT, myId, message));
}

void MainWindow::onGBReadyClicked()
{
    sendClientData(ClientData(ClientData::READY, myId, myId));
}
