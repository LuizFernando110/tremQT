#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
}

Client::~Client()
{
    delete ui;
}



void Client::on_horizontalSlider_valueChanged(int value)
{
    ui->speed->setText(QString::number(value));
}

