#include "TXlib.h"
#include <cmath>
#include <vector>
#include <stdio.h>
#include "1ADENOID1Lib.h"

using namespace std;



void keyboardInput(bool* left, bool* right, bool* space) {
    *left = GetAsyncKeyState(VK_LEFT);
    *right = GetAsyncKeyState(VK_RIGHT);
    *space = GetAsyncKeyState(VK_SPACE);
}

int main() {
    int windowWidth = 400;
    int windowHeight = 600;
    int angle = 0;
    int x0 = windowWidth / 2;
    int y0 = windowHeight;
    int x = x0 + 30;
    int y = y0;
    int timer = 0;
    int lives = 100;
    int score = 0;
    int ammoLevel = 30;
    int ammo = ammoLevel;
    int ammoTimer = 1;
    int damageLevel = 30;
    int reloadTime = 250;

    bool left = false;
    bool right = false;
    bool space = false;
    bool startMenu=true;
    bool stop = false;

    char l[10];
    char s[100];
    char ammoChar[255];

    vector <Bullet> Bullets;
    vector <Zombie> Zombies;

    Button startButton((windowWidth/4)-20, (windowHeight/2)-70, "          Начать игру         ", 40);
    Button damageUpButton(420, 100, "damage+", 15);
    Button reloadTimeButton(420, 130, "reload-", 15);
    Button ammoCountButton(420, 160, "ammo+", 15);

    txCreateWindow(windowWidth + 90, windowHeight);
    txSelectFont("Arial", 40);

    txClear();
    while (true)
    {
    while(startMenu)
    {
        txSetFillColor(RGB(122, 122, 122));
        txRectangle(0, 0 ,windowWidth+90, windowHeight);
        startButton.drawButton();
        if (startButton.getPressed())
        {
            startMenu=false;

        }
        txSleep(20);
        txClear();
    }
    while (not stop)
    {
        timer++;
        if (ammo<=0)
        {
            ammoTimer++;
        }
        else
        {
            ammoTimer=1;
        }
        keyboardInput(&left, &right, &space);

        if (left)
        {
            angle = angle - 3;
        }

        if (right)
        {
            angle = angle + 3;
        }

        if ((space) and (timer % 5 == 0) and (ammo>0))
        {
            ammo--;
            Bullet bullet(x0, y0, angle);
            Bullets.push_back(bullet);
        }

        if ((ammo<=0) and (ammoTimer % reloadTime == 0))
        {
            ammo=ammoLevel;
            timer=0;
        }

        txSetFillColor(TX_WHITE);
        drawWeapon(x0, y0, findX(x0, y0, x, y, angle), findY(x0, y0, x, y, angle));
        txSetFillColor(TX_GREY);
        txRectangle(windowWidth, 0, windowWidth + 90, windowHeight);

        damageUpButton.drawButton();
        reloadTimeButton.drawButton();
        ammoCountButton.drawButton();

        if ((damageUpButton.getPressed()) and (score>=100) and (damageLevel<=100))
        {
            damageLevel=damageLevel+5;
            score=score-100;
        }

        if ((reloadTimeButton.getPressed()) and (score>=50) and (reloadTime>=100))
        {
            reloadTime=reloadTime-20;
            score=score-50;
        }

        if ((ammoCountButton.getPressed()) and (score>=70) and (ammoLevel<=300))
        {
            ammoLevel=ammoLevel+10;
            score=score-70;
        }

        {
            auto it = Bullets.begin();
            while (it != Bullets.end())
            {
                it->moveBullet();

                if ((it->getX() > windowWidth) or (it->getX() < 0) or (it->getY() > windowHeight) or (it->getY() < 0))
                {
                    it = Bullets.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        if (timer % 170 == 0)
        {
            Zombie zombie(rand() % (windowWidth - 40) + 20, 10);
            Zombies.push_back(zombie);

        }

        {
            auto it = Zombies.begin();
            while (it != Zombies.end())
            {
                it->moveZombie();

                if (it->getY() > windowHeight)
                {
                    it = Zombies.erase(it);
                    lives=lives-10;
                }
                else
                {
                    ++it;
                }
            }
        }

        {
            auto it_b = Bullets.begin();
            while (it_b != Bullets.end())
            {
                bool remove_bullet = false;

                auto it_z = Zombies.begin();
                while (it_z != Zombies.end())
                {

                    if ((it_b->getX() >= it_z->getX()) and (it_b->getX() <= (it_z->getX() + 43)) and
                        (it_b->getY() >= it_z->getY()) and (it_b->getY() <= (it_z->getY() + 35)))
                    {
                        remove_bullet = true;
                        it_z->downLives(damageLevel);
                        if (it_z->getLives() <=0)
                        {
                            score=score+10;
                            it_z = Zombies.erase(it_z);
                        }
                        break;
                    }
                    else
                    {
                        ++it_z;
                    }
                }

                if (remove_bullet)
                {
                    it_b = Bullets.erase(it_b);
                }
                else
                {//remove_bullet = true;
                    ++it_b;
                }
            }
        }



        snprintf(l, 10, "%d", lives);
        snprintf(s, 10, "%d", score);
        if (ammo<=0)
        {
            strcpy(ammoChar, "Reloading..");
        }
        else
        {
            snprintf(ammoChar, 10, "%d", ammo);
        }
        txSelectFont("Arial", 40);
        txSetColor(TX_BLACK);
        txTextOut(20, 20, l);
        txTextOut(360, 20, s);
        txTextOut(180, 20, ammoChar);

        if (lives <= 0) {
            stop = true;
            Zombies.clear();
        }

        /* (score>=66666) {


            stop=false;
            txClear();
            screamer = true;
            break;
        }
        */
        txSetFillColor(RGB(122, 122, 122));
        txSleep(20);
        txClear();
    }

    while(stop)
    {
        txSetFillColor(RGB(122, 122, 122));
        txRectangle(0, 0 ,windowWidth+90, windowHeight);
        txSetColor(TX_GREEN);
        txTextOut((windowWidth/2)-30, (windowHeight/2)-100, "Вы проиграли. ");
        if (GetAsyncKeyState(13))
        {
            stop=false;
            score=0;
            lives=100;
            ammoLevel=30;
            damageLevel=30;
            reloadTime=250;
        }
        txSleep(20);
        txClear();


    }


    }
    return 0;
 }
