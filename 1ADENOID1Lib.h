    #include "TXlib.h"
    #include <cmath>

    using namespace std;

    //! @file 1ADENOID1Lib.h
    //! @brief ���������� ��� ����
    //!
    //! @version 0.1.0
    //! @author 1ADENOID1
    //! @date 18.05.21
    //!
    //! @warning ��� ������ ���������� ��������� TXlib.h  � ����� ������� �������� (����������� � ���������)
    //!

    HDC zombieImage = txLoadImage("zombie.bmp");   //�������� ���������

    //! @brief ������������ Y ���������� ��� ������ ����� �������, ���������� �� angle �������� ������������ �������� �������
    //! @param x0 ��������� ���������� �������� ������� �� ��� �������
    //! @param y0 ��������� ���������� �������� ������� �� ��� �������
    //! @param x1 �������� ���������� �������� ������� �� ��� �������
    //! @param y1 �������� ���������� �������� ������� �� ��� �������
    //! @param angle ���� �������� ������������ �������� �������
    double findY(int x0, int y0, int x1, int y1, int angle) {
        return ((x1 - x0) * sin(angle * M_PI / 180)) + (y1 - y0) * cos(angle * M_PI / 180) + y0;
    }

    //! @brief ������������ X ���������� ��� ������ ����� �������, ���������� �� angle �������� ������������ �������� �������
    //! @param x0 ��������� ���������� �������� ������� �� ��� �������
    //! @param y0 ��������� ���������� �������� ������� �� ��� �������
    //! @param x1 �������� ���������� �������� ������� �� ��� �������
    //! @param y1 �������� ���������� �������� ������� �� ��� �������
    //! @param angle ���� �������� ������������ �������� �������
    double findX(int x0, int y0, int x1, int y1, int angle) {
        return ((x1 - x0) * cos(angle * M_PI / 180)) - (y1 - y0) * sin(angle * M_PI / 180) + x0;
    }

    //! @brief ������ ����� �� ������ TXlib
    //! @param x0 ���������� ������ ����� (��� �������� ������) �� ��� �������
    //! @param y0 ���������� ������ ����� (��� �������� ������) �� ��� �������
    //! @param x1 ���������� ����� ������ ����� �� ��� �������
    //! @param y1 ���������� ����� ������ ����� �� ��� �������
    void drawWeapon(int x0, int y0, int x, int y) {

        txSetColor(TX_BLACK);
        txSetFillColor(TX_WHITE);
        txCircle(x0, y0, 10);
        txLine(x0, y0, x, y);
    }

    //! @brief ����� ����. �������� ������������ � ���������� ������ �� ������ TXlib
    class Bullet {
    private:
        int x0, y0, angle0, speedX, speedY;
    public:

        //! @brief ����������� ������ Bullet
        //! @param x ���������� ��������� ����� �� ��� �������
        //! @param y ���������� ��������� ����� �� ��� �������
        //! @param angle ���� ���������� ���������� �������� ����
        Bullet(int x, int y, int angle) {
            x0=x;
            y0=y;
            angle0=angle;
            speedX = cos(angle0 * M_PI / 180) * 6;
            speedY = sin(angle0 * M_PI / 180) * 6;
        }

        //! @brief ������������� ���������� ���� �� ��� �������
        //! @param x ���������� �����, � ������� ����� ����������� ���� �� ��� �������
        void setX(int x) {
            x0 = x;
        }

        //! @brief ������������� ���������� ���� �� ��� �������
        //! @param � ���������� �����, � ������� ����� ����������� ���� �� ��� �������
        void setY(int x) {
            y0 = x;
        }

        //! @brief ������������� ���� ���������� ���������� �������� ����
        //! @param angle ����, �� ������� ��������� ��������� ���������� ����
        void setAngle(int angle) {
            angle0 = angle;
        }

        //! @brief ���������� ��������� ���� �� ������ TXlib �� ��� �������
        int getX() {
            return x0;
        }

        //! @brief ���������� ��������� ���� �� ������ TXlib �� ��� �������
        int getY() {
            return y0;
        }

        //! @brief ���������� ���� ���������� ����
        int getAngle() {
            return angle0;
        }

        //! @brief ���������� ���� �� ~6 �������� � ����������� ���� ���������� ���������� ����
        void moveBullet() {
            x0 = x0 + speedX;
            y0 = y0 + speedY;
            draw();
        }

        //! @brief ������ ���� �� ������ TXlib. ��� ������ ������� ������ ������������� ���������� ����� moveBullet()
        void draw() {
            txSetColor(TX_BLACK);
            txSetFillColor(TX_YELLOW);
            txCircle(getX(), getY(), 2);
        }
};

//! @brief ����� �����. �������� ������������ � ���������� ����� �� ������ TXlib
class Zombie {
    private:
        int x0, y0;
        int lives0=100;
    public:

        //! @brief ����������� ������ Zombie
        //! @param x ���������� ��������� ����� �� ��� �������
        //! @param y ���������� ��������� ����� �� ��� �������
        Zombie(int x, int y) {
            x0=x;
            y0=y;
        }

        //! @brief ������������� ���������� ����� �� ��� �������
        //! @param x ���������� �����, � ������� ����� ����������� ����� �� ��� �������
        void setX(int x) {
            x0 = x;
        }

        //! @brief ������������� ���������� ����� �� ��� �������
        //! @param y ���������� �����, � ������� ����� ����������� ����� �� ��� �������
        void setY(int x) {
            y0 = x;
        }

        //! @brief ���������� ��������� ����� �� ������ TXlib �� ��� �������
        int getX() {
            return x0;
        }

        //! @brief ���������� ��������� ����� �� ������ TXlib �� ��� �������
        int getY() {
            return y0;
        }

        //! @brief ���������� �������� ����� (�� ��������� = 100)
        int getLives()
        {
            return lives0;
        }

        //! @brief ��������� �������� �����
        //! @param lives ���������� ���������� ��.
        //! @warning ���� �� <=0 �� ����� �� ������������.
        void downLives(int lives)
        {
            lives0=lives0-lives;
        }

        //! @brief ���������� ����� ���� �� ������. �������� ����� drawZombie()
        void moveZombie() {
            y0 = y0 + 1;
            drawZombie();
        }

        //! @brief ������ ����� �� ������ TXlib
        //! @warning ���������� ������� �����-�������� (���������� .bmp) � ���������� � �����������. ��� ���������� �������� �� ����� ������� ������
        void drawZombie() {
            char livesChar[255];
            _itoa(lives0, livesChar, 10);
            txSetColor(TX_BLACK);
            txSetFillColor(RGB(255, 0, 0));
            txSelectFont("Arial", 15);
            txTextOut(x0+10, y0-10, livesChar);
            txSetFillColor(RGB(0, 255, 0));
            txSelectFont("Arial", 40);


            //txRectangle(x0, y0, x0 + 43, y0 + 35);
            if (!zombieImage)
            {
                MessageBox(txWindow(), "Error of loading file <zombie.bmp>. Please check directory with game", "Fatal error", 0);
            }
            else
            {
                txBitBlt(txDC(), x0, y0, 43, 35, zombieImage, 0, 0);
            }
        }
};

//! @brief ����� ������. �������� ������������ ������ �� ������ TXlib. ����� ��������� ������� ����� �� ������
class Button
    {
        private:
            int x0, y0, textSize0;
            char text0[255];
            bool pressed=false;
        public:

            //! @brief ����������� ������ Button
            //! @param x ���������� ��������� ����� �� ��� �������
            //! @param y ���������� ��������� ����� �� ��� �������
            //! @param text �����, ������� ����������� �� ������
            //! @param textSize ������ ������ ������ �� ������
            Button(int x, int y, char text[255], int textSize)
            {
                x0=x;
                y0=y;
                textSize0=textSize;
                strcpy(text0, text);
            }

            //! @brief ������ ������ Bullet � Zombie
            void setX(int x)
            {
                x0=x;
            }

            //! @brief ������ ������ Bullet � Zombie
            void setY(int y)
            {
                y0=y;
            }

            //! @brief ������������� ����� �� ������
            //! @param ��� �����
            void setText(char text[255])
            {
                strcpy(text0, text);
            }

            //! @brief ���������� true ���� ������ ���� ������ �����, ����� ���������� false
            bool getPressed()
            {
                return pressed;
            }

            //! @brief ������ ������ �� ������ TXlib. �������� ����� pressCheck
            void drawButton()
            {
                txSetColor(TX_GREEN);
                txSelectFont("Arial", textSize0);
                txRectangle(x0, y0, x0+10+txGetTextExtentX(text0), y0+6+txGetTextExtentY(text0));
                txTextOut(x0+5, y0+3, text0);
                pressCheck();
            }

            //! @brief ���������� ��������� ������� ����� �� ������ (�� ������ � getPressed())
            //! @warning ����� getPressed() ���������� �������� ����������, � ������� ����������� ��������� ������ (������ ��� ���), � pressCheck() ��������������� ������������ ��� �������
            void pressCheck()
            {
                if ((x0<=txMouseX()) and (x0+10+txGetTextExtentX(text0)>=txMouseX()) and (y0<=txMouseY()) and (y0+6+txGetTextExtentY(text0)>=txMouseY()) and (not((txMouseButtons() & 1)==0)))
                {
                    pressed=true;
                }
                else
                {
                    pressed=false;
                }
            }

    };
