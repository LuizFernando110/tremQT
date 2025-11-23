#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);
}

void Server::startServer()
{
    quint16 porta = 5000;  // Porta fixa

    if (!tcpServer->listen(QHostAddress::Any, porta)) {
        qDebug() << "Erro ao iniciar servidor:" << tcpServer->errorString();
    } else {
        qDebug() << "Servidor iniciado na porta" << porta;
        connect(tcpServer, &QTcpServer::newConnection, this, &Server::onNewConnection);
    }
}

void Server::onNewConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    clients.append(clientSocket);

    qDebug() << "Novo cliente conectado:" << clientSocket->peerAddress().toString();

    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
}

void Server::onReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;

    QByteArray data = clientSocket->readAll();
    qDebug() << "Recebido do cliente:" << data;

    // Envia de volta (eco)
    clientSocket->write("Servidor recebeu: " + data);
}
