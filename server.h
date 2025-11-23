#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QDebug>
#include "trem.h"
#include <iostream>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void startServer(); // Inicia o servidor com porta fixa

    void addTrem(Trem *trem);
    void setTrens(QList<Trem*> tremList);

private slots:
    void onNewConnection(); // Dispara quando um cliente se conecta
    void onReadyRead();     // Dispara quando recebe dados

private:
    QTcpServer *tcpServer;
    QList<QTcpSocket*> clients;  // Lista de clientes conectados
    QList<Trem*> trens;

    void processCommand(const QString &command);
};

#endif // SERVER_H
