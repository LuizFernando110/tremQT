#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QDebug>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void startServer(); // Inicia o servidor com porta fixa

private slots:
    void onNewConnection(); // Dispara quando um cliente se conecta
    void onReadyRead();     // Dispara quando recebe dados

private:
    QTcpServer *tcpServer;
    QList<QTcpSocket*> clients;  // Lista de clientes conectados
};

#endif // SERVER_H
