#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    tcpServer = new QTcpServer(this);
}

void Server::addTrem(Trem *trem){
    trens.append(trem);
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

    processCommand(data);

    // Envia de volta (eco)
    clientSocket->write("Servidor recebeu: " + data);
}

void Server::processCommand(const QString &command){
    QStringList parts = command.split(" ");

    if(parts.size() < 3){
        qDebug() << "Comando inválido:" << command;
        return;
    }

    QString target = parts[0];  // "trem"
    QString tremIdStr = parts[1];  // "all" ou número
    QString action = parts[2];  // "continue" ou "stop"

    int velocidade = (parts.size() >= 4) ? parts[3].toInt() : 0;

    // 🔥 Se for comando para TODOS
    if (tremIdStr == "all") {
        for (Trem *trem : trens) {
            trem->setEnable(action == "continue");
            trem->setVelocidade(velocidade);
        }
        qDebug() << "Comando aplicado a todos os trens!";
        return;
    }

    // 🔹 Caso contrário, trata um trem só
    int tremId = tremIdStr.toInt();
    Trem *alvo = nullptr;
    for (Trem *trem : trens) {
        if (trem->getId() == tremId) {
            alvo = trem;
            break;
        }
    }

    if (!alvo) {
        qDebug() << "Trem" << tremId << "não encontrado";
        return;
    }

    alvo->setEnable(action == "continue");
    alvo->setVelocidade(velocidade);
}

