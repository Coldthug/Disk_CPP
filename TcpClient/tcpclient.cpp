#include "tcpclient.h"
#include "ui_tcpclient.h"
#include <QHostAddress>
#include <QDebug>
#include <QMessageBox>

TcpClient::TcpClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);
    loadConfig();



    connect(&m_tcpScoket,SIGNAL(connected()),this,SLOT(showConnect())); // **bug**  connected拼错了
    // 连接服务器
    m_tcpScoket.connectToHost(QHostAddress(m_strIP),m_usPort);

}

TcpClient::~TcpClient()
{
    delete ui;
}

void TcpClient::loadConfig()
{
    QFile file(":/client.config");
    if(file.open(QIODevice::ReadOnly)){
        QByteArray baData= file.readAll();
        QString strData = baData.toStdString().c_str();

        //
        strData.replace("\r\n"," "); //去除换行

        QStringList strList=strData.split(" "); // 分隔字符串
        for (int i=0;i<strList.size();i++) {
            qDebug()<<strList[i];
        }
        m_strIP=strList.at(0);
        m_usPort=strList.at(1).toUShort();
        qDebug()<<"ip:"<<m_strIP<<" port:"<<m_usPort;

        file.close();
    }else {
        QMessageBox::critical(this,"open config","open config failed");
    }

}

void TcpClient::showConnect()
{
    QMessageBox::information(this,"连接服务器","连接服务器成功");
}
