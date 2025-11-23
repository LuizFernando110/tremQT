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

    QString target = parts[0];
    int tremId = parts[1].toInt();
    QString action = parts[2];

    int velocidade = 0;

    if(parts.size() >= 4) {
        velocidade = parts[3].toInt();
    }

    Trem* alvo = nullptr;
    for(Trem *trem : std::as_const(trens)){
        if(trem->getId() == tremId) {
            alvo = const_cast<Trem*>(trem);
            break;
        }
    }

    if (!alvo) {
            qDebug() << "Trem" << tremId << "não encontrado";
            return;
    }

    if(action == "continue") alvo->setEnable(true);
    else if (action == "stop") alvo->setEnable(false);
    alvo->setVelocidade(velocidade);
}
