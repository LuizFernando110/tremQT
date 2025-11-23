#ifndef TREM_H
#define TREM_H

#include <QObject>
#include <thread>
#include <chrono>
#include <QSemaphore>
#include <cstdlib>
#include <iostream>

using namespace std;

class Trem : public QObject
{
    Q_OBJECT
public:
    Trem(int,int,int);
    ~Trem();
    void start();
    void run();
    void setVelocidade(int);
    void setEnable(bool);

    static int trem4X, trem4Y;
    static int trem5X, trem5Y;
    static QSemaphore semaphores[9];

signals:
    void updateGUI(int,int,int);

private:
   std::thread threadTrem;
   int id;
   int x;
   int y;
   int velocidade;
   bool enable;
};

#endif // TREM_H
