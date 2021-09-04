#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include  <QtGui/QGuiApplication>
#include <QMetaObject>
#include <QVariant>
#include <QQmlApplicationEngine>
bool isconnect=false;


Widget* Widget::widget = nullptr;
Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);



this->resize(1200,700);

  this->widget = this;
  InitSystem();


  //QQmlApplicationEngine engine;
  //engine.load(QUrl("QML:/LandingGearUI.qml"));

  //ui->quickWidget->setSource(QUrl("QML:/ LandingGearQml.qml"));

    m_timer  = new QTimer(this);
    m_timer->setInterval(100);
    connect(m_timer,&QTimer::timeout,this,&Widget::UpdateAllEntityStatus);
    m_timer->start();
    m_tcpserver = new QTcpServer(this);
    m_tcpserver->listen(QHostAddress::Any,10086);
    connect(m_tcpserver,&QTcpServer::newConnection,this,&Widget::accpetclient);
}
void Widget::accpetclient()
{

        clientSocket = new QTcpSocket(this);
        this->clientSocket = m_tcpserver->nextPendingConnection();
        qDebug()<<clientSocket->peerAddress().toString() + ": " + QString::number(clientSocket->peerPort());
        isconnect = true;
}
Widget::~Widget()
{
  delete ui;
}

void Widget::InitHandShank()
{

}

void Widget::InitSystem()
{
  GlobalClock* g = GlobalClock::GetClockInstance();

  m_as = new AnalogSwitch();
  //初始化起落架门
    m_lgd = new LandingGearDoor();
   m_ger = new LandingGear();
   m_ctr = new Controller(m_lgd,m_ger);
   m_hs = new HandShank(m_ctr,m_as);
}

void Widget::UpdateAllEntityStatus()
{
    switch (m_lgd->GetStatus()) {
        case LandingGearDoor::CLOSE:
            ui->label_door->setText("关闭");
        break;
    case LandingGearDoor::OPEN:
        ui->label_door->setText("打开");
    break;
    case LandingGearDoor::CLOSING:
        ui->label_door->setText("正在关闭");
    break;
    case LandingGearDoor::OPENING:
        ui->label_door->setText("正在打开");
    break;
    case LandingGearDoor::STOP:
        ui->label_door->setText("停止");
    break;
    }

    switch (m_ger->GetStatus()) {
        case LandingGear::RETRACTED:
            ui->label_gear->setText("关闭");
        break;
    case LandingGear::EXTENDED:
        ui->label_gear->setText("伸出");
    break;
    case LandingGear::EXTENDING:
        ui->label_gear->setText("正在伸出");
    break;
    case LandingGear::RETRACTING:
        ui->label_gear->setText("正在回收");
    break;
    case LandingGear::STOP:
        ui->label_gear->setText("停止");
    break;
    }
char buf[128];
sprintf(buf,"door: %d, gear: %d",m_lgd->GetStatus(),m_ger->GetStatus());
if(isconnect)
clientSocket->write(buf);

}

void Widget:: paintEvent(QPaintEvent* event)
{
  QPainter painter(this);
  QBrush brush;
  QPen pen;
  pen.setWidth(10);
  pen.setColor(Qt::blue);

  painter.setPen(pen);



  //绘制起落架门
  painter.drawLine(m_lgd->Getconpos(),m_lgd->Gettailpos());

  //绘制起落架
  pen.setColor(Qt::green);
  painter.setPen(pen);
  painter.drawLine(m_ger->GetConpos(),m_ger->GetTailpos());

  pen.setColor(Qt::black);
  pen.setWidth(15);
  painter.setPen(pen);


  painter.drawEllipse(m_ger->GetTailpos(),5,20);

  update();

}



