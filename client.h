#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class Client;
}

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();
    void connectToServer(); // Conecta na porta fixa
    void sendMessage(const QString &message);

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void onConnected();   // Quando conectar
    void onReadyRead();

    void on_connectButton_clicked();

    void on_stopButton_2_clicked();
    void on_continueButton_clicked();

private:
    Ui::Client *ui;
    QTcpSocket *socket;
};

#endif // CLIENT_H
