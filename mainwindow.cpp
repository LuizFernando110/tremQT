#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    trem1 = new Trem(1,110,30);
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));    
    trem1->start();
    
    trem2 = new Trem(2, 240, 30);
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    trem2->start();

    trem3 = new Trem(3, 390, 30);
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    trem3->start();

    trem4 = new Trem(4, 130, 180);
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    trem4->start();

    trem5 = new Trem(5, 430, 180);
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    trem5->start();

    trem6 = new Trem(6, 70, 280);
    connect(trem6,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    trem6->start();

    trem7 = new Trem(7, 490, 280);
    connect(trem7,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    trem7->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInterface(int id, int x, int y)
{
    switch(id){
        case 1:
            ui->labelTrem01->setGeometry(x,y,20,20);
            break;
        case 2:
            ui->labelTrem02->setGeometry(x,y,20,20);
            break;
        case 3:
            ui->labelTrem03->setGeometry(x,y,20,20);
            break;
        case 4:
            ui->labelTrem04->setGeometry(x,y,20,20);
            break;
        case 5:
            ui->labelTrem05->setGeometry(x,y,20,20);
            break;
        case 6:
            ui->labelTrem06->setGeometry(x,y,20,20);
            break;
        case 7:
            ui->labelTrem07->setGeometry(x,y,20,20);
            break;
        default:
            break;
    }
}

