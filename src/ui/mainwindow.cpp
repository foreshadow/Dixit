#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "chatform.h"
#include <QSplashScreen>
#include <QInputDialog>
#include <QObject>
#include "clientdata.h"
#include "serverdata.h"
#include "card.h"



MainWindow::MainWindow(TcpSocket *socket, QString id) :
    ui(new Ui::MainWindow), socket(socket), myId(id), rabbits(), //players(),
    dixitGame(new DixitGame),
    ca(new CenterArea(500, 200)), gbReady(new GraphicsButton), headline(new GraphicsHeadline)
{
    connect(socket, SIGNAL(received(QByteArray)), this, SLOT(received(QByteArray)));

    QSplashScreen splash(QPixmap("img/splash.png"));
    splash.show();

    splash.showMessage("正在找桌游", Qt::AlignLeft, Qt::white);

    connect(dixitGame, SIGNAL(statusChanged()), this, SLOT(statusChanged()));
    connect(dixitGame, SIGNAL(descriptionChanged()), this, SLOT(descriptionChanged()));
    connect(dixitGame, SIGNAL(tableUpdated()), this, SLOT(tableUpdated()));
    connect(dixitGame, SIGNAL(playerListChanged()), this, SLOT(playerListChanged()));

    splash.showMessage("正在报名参加", Qt::AlignLeft, Qt::white);
//    sendClientData(ClientData(ClientData::Type::SET_ID, myId, myId));

    splash.showMessage("正在找座位", Qt::AlignLeft, Qt::white);
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->setSceneRect(0, 0, 798, 598);
    ui->graphicsView->scene()->addPixmap(QPixmap("img/d.png").scaledToWidth(ui->graphicsView->width()));
    for (int i = 1; i <= 84; i++)
    {
        splash.showMessage(QString("正在拿出卡牌 (%1 / 84)").arg(i),
                           Qt::AlignLeft, Qt::white);
        Card *c = new Card(i, QString("img/cards/%1.png").arg(i, 2, 10, QChar('0')));
        connect(c, SIGNAL(doubleClicked()), this, SLOT(selected()));
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
        rabbits[i]->hide();
        ui->graphicsView->scene()->addItem(rabbits[i]);
    }
    splash.showMessage("正在准备茶水", Qt::AlignLeft, Qt::white);
    ChatForm *cf = new ChatForm(myId, this);
    connect(cf, SIGNAL(send(QString)), this, SLOT(chatFormSend(QString)));
    connect(this, SIGNAL(chatFormAppend(QString)), cf, SLOT(append(QString)));
    cf->setFeatures(QDockWidget::DockWidgetFloatable);
    QPoint mtg = mapToGlobal(this->geometry().topLeft());
    cf->setGeometry(mtg.x() + this->width() - cf->width(), mtg.y(), cf->width(), cf->height());
    splash.showMessage("正在说你好", Qt::AlignLeft, Qt::white);
    sendClientData(ClientData(ClientData::Type::SET_ID, myId, myId));
    sendClientData(ClientData(ClientData::Type::CHAT, myId, myId + "加入了房间。"));
    connect(gbReady, SIGNAL(clicked()), this, SLOT(onGBReadyClicked()));
    gbReady->setImage("img/start.png");
    gbReady->setPos(600, 500);
    ui->graphicsView->scene()->addItem(gbReady);
    headline->setImage("img/banner.png");
    headline->setPos(180, 120);
    headline->setText("欢迎！");
    ui->graphicsView->scene()->addItem(headline);
    connect(ca, SIGNAL(cardDrop(int)), this, SLOT(playCard(int)));
    ca->setPos(150, 175);
    ui->graphicsView->scene()->addItem(ca);

    sendClientData(ClientData(ClientData::Type::SYNC, myId));
}

MainWindow::~MainWindow()
{
    deck.clear();
    delete ui;
}

void MainWindow::sync(ServerData sd)
{
    if (sd.getContent() == "GAME")
    {
        dixitGame->update(sd.getDixitGame());
    }
    // compatible with old versions
    else if (sd.getContent() == "DESC" && sd.getFromUser() == myId)
    {
        bool ok = false;
        QString input;
        while (ok == false || input.isEmpty())
            input = QInputDialog::getText(this, "你的回合", "描述一张卡牌",
                                          QLineEdit::Normal, "", &ok);
        sendClientData(ClientData(ClientData::Type::DESC, myId, input));
    }
}

void MainWindow::handle(ServerData sd)
{
    switch (sd.getType())
    {
    case ServerData::Type::CHAT:
    case ServerData::Type::PHRASE:
        emit chatFormAppend(QString("%1 %2\n  %3")
                            .arg(sd.getFromUser())
                            .arg(sd.getUtc().toLocalTime().toString("hh:mm:ss"))
                            .arg(sd.getContent()));
        break;
    case ServerData::Type::REQUEST_ID:
        break;
    case ServerData::Type::READY:
//        if (sd.getFromUser() == myId)
//            gbReady->hide();
//        rabbits.at(players.size())->show();
//        players.append(new Player(sd.getFromUser(), nullptr));
        emit chatFormAppend(sd.getFromUser() + "准备就绪。");
        break;
    case ServerData::Type::DESC:
        emit chatFormAppend(QString("%1的描述为\n  %2").arg(sd.getFromUser()).arg(sd.getContent()));
        headline->setText(sd.getContent());
        update();
        break;
    case ServerData::Type::PLAY:
        if (sd.getFromUser() == myId)
            ca->addCard(hcards.takeCard(sd.getCards().first()));
        else
            ca->addCard(deck.getCard(sd.getCards().first()));
        break;
    case ServerData::Type::SELECT:
        break;
    case ServerData::Type::DRAW:
        for (int i = 0; i < sd.getCards().size(); i++)
            hcards.addCard(deck.getCard(sd.getCards().at(i)));
        update();
        break;
    case ServerData::Type::SYNC:
        sync(sd);
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
    sendClientData(ClientData(ClientData::Type::CHAT, myId, message));
}

void MainWindow::onGBReadyClicked()
{
    sendClientData(ClientData(ClientData::Type::READY, myId, myId));
}

void MainWindow::playCard(int id)
{
    if (deck.getCard(id)->getLocation() == Card::Location::HAND_DRAGGABLE)
        sendClientData(ClientData(ClientData::Type::PLAY, myId, "", QList<int>({id})));
}

void MainWindow::selected()
{
    int id = qobject_cast<Card *>(sender())->getId();
    if (dixitGame->status() == DixitGame::Status::DIXIT_IN_GAME_SELECTING)
        sendClientData(ClientData(ClientData::Type::SELECT, myId, id));
}

void MainWindow::statusChanged()
{
    switch (dixitGame->status())
    {
    case DixitGame::Status::DIXIT_BEFORE_GAME:
        setWindowTitle("Dixit - 准备开始");
        break;
    case DixitGame::Status::DIXIT_IN_GAME_DESCRIBING:
        setWindowTitle("Dixit - 描述卡牌中");
        break;
    case DixitGame::Status::DIXIT_IN_GAME_PLAYING:
        setWindowTitle("Dixit - 出牌中");
        break;
    case DixitGame::Status::DIXIT_IN_GAME_SELECTING:
        setWindowTitle("Dixit - 选择中");
        break;
    case DixitGame::Status::DIXIT_IN_GAME_SETTLING:
        setWindowTitle("Dixit - 结算中");
        break;
    }
}

void MainWindow::descriptionChanged()
{
    headline->setText(dixitGame->description());
}

void MainWindow::tableUpdated()
{
    ca->clear();
    for (int i : dixitGame->table())
        ca->addCard(deck.getCard(i));
}

void MainWindow::playerListChanged()
{
    int self;
    for (int i = 0; i < dixitGame->constPlayerList().size(); i++)
        if (dixitGame->constPlayerList().at(i).getId() == myId)
            self = i;
    static const Player::Color c[] =
    {
        Player::Color::Green,
        Player::Color::Blue,
        Player::Color::Black,
        Player::Color::Pink,
        Player::Color::Yellow,
        Player::Color::White
    };
    static const QPoint p[] =
    {
        {   0,   0 },
        { 300,   0 },
        { 650,   0 },
        {   0, 200 },
        { 650, 200 },
        {   0, 400 }
    };
    auto getIndexInPoints = [&](Player::Color color)
    {
        for (int i = 0; i < 6; i++)
            if (c[i] == color)
                return i;
        return -1;
    };
    int cpDiff = getIndexInPoints(dixitGame->constPlayerList().at(self).getColor()) - 5;
    for (int i = 0; i < 6; i++)
        rabbits[i]->hide();
    for (int i = 0; i < dixitGame->constPlayerList().size(); i++)
    {
        int k = getIndexInPoints(dixitGame->constPlayerList().at(i).getColor());
        rabbits[k]->show();
        rabbits[k]->setPos(p[(k - cpDiff + 6) % 6]);
    }
}
