#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this); // Instancia o socket

    connect(ui->connectButton, &QPushButton::clicked,
            this, &Client::on_connectButton_clicked);

    // Conectar sinais do socket aos slots
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    ui->stopButton_2->setEnabled(false);
    ui->continueButton->setEnabled(false);
}

Client::~Client()
{
    delete ui;
}



void Client::on_horizontalSlider_valueChanged(int value)
{
    ui->speed->setText(QString::number(value));
}


void Client::on_connectButton_clicked()
{
    qDebug() << "connect BUTTON";
    QString host = "127.0.0.1";
    quint16 porta = 5000;

    socket->connectToHost(host, porta);
}

void Client::onConnected()
{
    qDebug() << "Cliente conectado!";
    ui->stopButton_2->setEnabled(true);
    ui->connectButton->setEnabled(false);
    ui->continueButton->setEnabled(true);
}

void Client::on_stopButton_2_clicked()
{
    qDebug() << "Estado atual do socket:" << socket->state();

    if (socket->state() == QAbstractSocket::ConnectedState) {
        QString tremId = ui->lineEdit->text();
        QString acao = "stop";
        QString velocidade = ui->speed->text();

        QString comando = QString("trem %1 %2 %3").arg(tremId, acao, velocidade);

        socket->write(comando.toUtf8());
        qDebug() << "Mensagem enviada:" << comando ;
    } else {
        qDebug() << "⚠ Não está conectado ainda!";
    }
}

void Client::on_continueButton_clicked(){
    if (socket->state() == QAbstractSocket::ConnectedState){
        QString tremId = ui->lineEdit->text();
        QString acao = "continue";
        QString velocidade = ui->speed->text();

        QString comando = QString("trem %1 %2 %3").arg(tremId, acao, velocidade);
        socket->write(comando.toUtf8());
        qDebug() << "Mensagem enviada:" << comando ;
    }else{
        qDebug() << "⚠ Não está conectado ainda!";
    }
}

void Client::onReadyRead()
{
    QByteArray resposta = socket->readAll();
    qDebug() << resposta;
}

