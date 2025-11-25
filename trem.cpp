#include "trem.h"

QSemaphore Trem::semaphores[9] = {
    QSemaphore(1), QSemaphore(1), QSemaphore(1), QSemaphore(1),
    QSemaphore(1), QSemaphore(1), QSemaphore(1), QSemaphore(1),
    QSemaphore(1)
};

Trem::Trem(int id, int x, int y)
{
    this->id = id;
    this->x = x;
    this->y = y;
    velocidade = 250;
    enable = false;
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
    threadTrem = std::thread(&Trem::run, this);
}

int Trem::trem4X = 130;
int Trem::trem4Y = 180;
int Trem::trem5X = 430;
int Trem::trem5Y = 180;

void Trem::run()
{
    while (true) {
        int newX = x;
        int newY = y;

        switch (id) {

        case 1:
            if (enable)
            {   
                if (y == 30 && x < 220) {
                    if (x == 200) semaphores[0].acquire(1);
                    newX += 10;
                }
                else if (x == 220 && y < 130) {
                    if (y == 40) semaphores[4].acquire(1);
                    newY += 10;
                }
                else if (x > 80 && y == 130) {
                    if (x == 200) semaphores[0].release(1);
                    if (x == 120) semaphores[4].release(1);
                    newX -= 10;
                }
                else
                    newY -= 10;
            }
            break;

        case 2:
            if (enable)
            {
                if (y == 30 && x > 220) {
                    if (x == 230) semaphores[0].acquire(1);
                    if (x == 350) semaphores[1].release(1);
                    newX -= 10;
                }
                else if (x == 220 && y < 130) {
                    if (y == 100) semaphores[3].acquire(1);
                    newY += 10;
                }
                else if (y == 130 && x < 360) {
                    newX += 10;
                    if (x == 230) semaphores[0].release(1);
                    if (x == 350) semaphores[1].acquire(1);
                }
                else {
                    if (y == 110) semaphores[3].release(1);
                    newY -= 10;
                }
            }
            break;

        case 3:
            if (enable)
            {
                if (y == 30 && x < 500) {
                    if (x == 380) semaphores[1].release(1);
                    newX += 10;
                }
                else if (x == 500 && y < 130) {
                    newY += 10;
                }
                else if (x > 360 && y == 130) {
                    if (x == 370) semaphores[1].acquire(1);
                    if (x == 450) semaphores[2].acquire(1);
                    newX -= 10;
                }
                else {
                    if (y == 120) semaphores[2].release(1);
                    newY -= 10;
                }
            }
            break;

        case 4:
            if (enable)
            {
                if (x == 130 && y < 230) {
                    if (y == 140) semaphores[4].release(1);
                    if (y == 220) semaphores[7].acquire(1);
                    newY += 10;
                }
                else if (y == 230 && x < 430) {
                    if (x == 280) semaphores[5].acquire(1);
                    if (x == 280) semaphores[7].release(1);
                    newX += 10;
                }
                else if (x == 430 && y > 130) {
                    if (y == 150) semaphores[2].acquire(1);
                    if (y == 200) semaphores[5].release(1);
                    newY -= 10;
                }
                else {
                    if (x == 350) semaphores[2].release(1);
                    if (x == 380) semaphores[3].acquire(1);
                    if (x == 210) semaphores[3].release(1);
                    if (x == 240) semaphores[4].acquire(1);
                    newX -= 10;
                }

                int distancia = abs(newX - trem5X) + abs(newY - trem5Y);
                if (distancia <= 50) {
                    semaphores[8].tryAcquire(1);
                    break; 
                }

                trem4X = newX;
                trem4Y = newY;
            }
            break;

        case 5:
            if (enable)
            {
                if (x == 130 && y < 230) {
                    if (y == 140) semaphores[4].release(1);
                    if (y == 220) semaphores[7].acquire(1);
                    newY += 10;
                }
                else if (y == 230 && x < 430) {
                    if (x == 280) semaphores[5].acquire(1);
                    if (x == 280) semaphores[7].release(1);
                    newX += 10;
                }
                else if (x == 430 && y > 130) {
                    if (y == 150) semaphores[2].acquire(1);
                    if (y == 200) semaphores[5].release(1);
                    newY -= 10;
                }
                else {
                    if (x == 350) semaphores[2].release(1);
                    if (x == 380) semaphores[3].acquire(1);
                    if (x == 200) semaphores[3].release(1);
                    if (x == 240) semaphores[4].acquire(1);
                    newX -= 10;
                }

                int distancia = abs(newX - trem4X) + abs(newY - trem4Y);
                if (distancia <= 50) {
                    semaphores[8].tryAcquire(1);
                    break; 
                }

                trem5X = newX;
                trem5Y = newY;
            }
            break;

        case 6:
            if (enable)
            {
                if (y == 230 && x < 280) {
                    if (x == 260) semaphores[6].acquire(1);
                    if (x == 110) semaphores[7].acquire(1);
                    newX += 10;
                }
                else if (x == 280 && y < 330) {
                    if (y == 240) semaphores[7].release(1);
                    newY += 10;
                }
                else if (x > 70 && y == 330) {
                    if (x == 270) semaphores[6].release(1);
                    newX -= 10;
                }
                else
                    newY -= 10;
            }
            break;

        case 7:
            if (enable)
            {
                if (y == 230 && x < 490) {
                    if (x == 290) semaphores[6].release(1);
                    if (x == 430) semaphores[5].release(1);
                    newX += 10;
                }
                else if (x == 490 && y < 330) {
                    newY += 10;
                }
                else if (y == 330 && x > 280) {
                    if (x == 300) semaphores[6].acquire(1);
                    newX -= 10;
                }
                else {
                    if (y == 240) semaphores[5].acquire(1);
                    newY -= 10;
                }
            }
            break;
        }

        // Atribuição final fora do switch
        x = newX;
        y = newY;
        emit updateGUI(id, x, y);

        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}
