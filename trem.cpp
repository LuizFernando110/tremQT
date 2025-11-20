#include "trem.h"

Trem::Trem(int id, int x, int y)
{
    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = 250;
    enable = true;
}

Trem::~Trem()
{
    threadTrem.join();
}

void Trem::setVelocidade(int velocidade)
{
    this->velocidade = velocidade;
}

void Trem::setEnable(bool enable)
{
    this->enable = enable;
}

void Trem::start()
{
    threadTrem = std::thread(&Trem::run,this);
}

void Trem::run()
{
    while(true){
        switch(id){
        case 1:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == 30 && x <220)
                    x+=10;
                else if (x == 220 && y < 130)
                    y+=10;
                else if (x > 80 && y == 130)
                    x-=10;
                else
                    y-=10;
            }
            break;
        case 2:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == 30 && x <360)
                    x+=10;
                else if (x == 360 && y < 130)
                    y+=10;
                else if (x > 220 && y == 130)
                    x-=10;
                else
                    y-=10;
            }
            break;
        case 3:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == 30 && x < 500)
                    x+=10;
                else if (x == 500 && y < 130)
                    y+=10;
                else if (x > 360 && y == 130)
                    x-=10;
                else
                    y-=10;
            }
            break;
        case 4:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if(x == 130 && y < 230)
                    y+=10;
                else if (y == 230 && x<430)
                    x+=10;
                else if (x==430 && y>130)
                    y-=10;
                else
                    x-=10;
            }
            break;
        case 5:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if(x == 130 && y < 230)
                    y+=10;
                else if (y == 230 && x<430)
                    x+=10;
                else if (x==430 && y>130)
                    y-=10;
                else
                    x-=10;
            }
            break;
        case 6:
            if (enable)
            {
                emit updateGUI(id,x,y);
                if (y == 230 && x < 280)
                    x+=10;
                else if (x == 280 && y < 330)
                    y+=10;
                else if (x > 70 && y == 330)
                    x-=10;
                else
                    y-=10;
            }
            break;
        case 7:
            if(enable) {
                emit updateGUI(id,x,y);
                if(y == 230 && x < 490)
                    x+=10;
                else if(x == 490 && y < 330)
                    y+=10;
                else if(y == 330 && x > 280)
                    x-=10;
                else
                    y-=10;
            }
        default:
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}

