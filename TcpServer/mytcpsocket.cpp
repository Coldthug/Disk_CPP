#include "mytcpsocket.h"

MyTcpSocket::MyTcpSocket()
{
    connect(this,SIGNAL(readyRead()),this,SLOT(recvMsg()));
}

void MyTcpSocket::recvMsg()
{
    qDebug()<< this->bytesAvailable();

    uint uiPDULen=0;
    this->read((char*)&uiPDULen,sizeof(uint));

    uint uiMsgLen=uiPDULen-sizeof(uint);
    PDU *pdu=mkPDU(uiMsgLen);
    this->read((char*)pdu+sizeof (uint),uiPDULen-sizeof(uint));
    qDebug() << pdu->uiMsgType << (char*)pdu->caMsg ;
}
