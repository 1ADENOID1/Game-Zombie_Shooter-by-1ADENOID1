    #include "TXlib.h"
    #include <cmath>

    using namespace std;

    //! @file 1ADENOID1Lib.h
    //! @brief Библиотека для игры
    //!
    //! @version 0.1.0
    //! @author 1ADENOID1
    //! @date 18.05.21
    //!
    //! @warning Для работы библиотеки необходим TXlib.h  и файлы текстур спрайтов (прилагается в комплекте)
    //!

    HDC zombieImage = txLoadImage("zombie.bmp");   //загрузка текстурки

    //! @brief Рассчитывает Y координату для второй точки отрезка, повёрнутого на angle градусов относительно нулевого отрезка
    //! @param x0 Начальная координата нулевого отрезка по оси абсцисс
    //! @param y0 Начальная координата нулевого отрезка по оси ординат
    //! @param x1 Конечная координата нулевого отрезка по оси абсцисс
    //! @param y1 Конечная координата нулевого отрезка по оси ординат
    //! @param angle Угол поворота относительно нулевого отрезка
    double findY(int x0, int y0, int x1, int y1, int angle) {
        return ((x1 - x0) * sin(angle * M_PI / 180)) + (y1 - y0) * cos(angle * M_PI / 180) + y0;
    }

    //! @brief Рассчитывает X координату для второй точки отрезка, повёрнутого на angle градусов относительно нулевого отрезка
    //! @param x0 Начальная координата нулевого отрезка по оси абсцисс
    //! @param y0 Начальная координата нулевого отрезка по оси ординат
    //! @param x1 Конечная координата нулевого отрезка по оси абсцисс
    //! @param y1 Конечная координата нулевого отрезка по оси ординат
    //! @param angle Угол поворота относительно нулевого отрезка
    double findX(int x0, int y0, int x1, int y1, int angle) {
        return ((x1 - x0) * cos(angle * M_PI / 180)) - (y1 - y0) * sin(angle * M_PI / 180) + x0;
    }

    //! @brief Рисует пушку на холсте TXlib
    //! @param x0 Координата центра пушки (оси вращения ствола) по оси абсцисс
    //! @param y0 Координата центра пушки (оси вращения ствола) по оси ординат
    //! @param x1 Координата конца ствола пушки по оси абсцисс
    //! @param y1 Координата конца ствола пушки по оси ординат
    void drawWeapon(int x0, int y0, int x, int y) {

        txSetColor(TX_BLACK);
        txSetFillColor(TX_WHITE);
        txCircle(x0, y0, 10);
        txLine(x0, y0, x, y);
    }

    //! @brief Класс пули. Способен отрисовывать и перемещать пульку на холсте TXlib
    class Bullet {
    private:
        int x0, y0, angle0, speedX, speedY;
    public:

        //! @brief Конструктор класса Bullet
        //! @param x Координата начальной точки по оси абсцисс
        //! @param y Координата начальной точки по оси ординат
        //! @param angle Угол отклонения траектории движения пули
        Bullet(int x, int y, int angle) {
            x0=x;
            y0=y;
            angle0=angle;
            speedX = cos(angle0 * M_PI / 180) * 6;
            speedY = sin(angle0 * M_PI / 180) * 6;
        }

        //! @brief Устанавливает координату пули по оси абсцисс
        //! @param x Координата точки, в которую нужно переместить пулю по оси абсцисс
        void setX(int x) {
            x0 = x;
        }

        //! @brief Устанавливает координату пули по оси ординат
        //! @param н Координата точки, в которую нужно переместить пулю по оси ординат
        void setY(int x) {
            y0 = x;
        }

        //! @brief Устанавливает угол отклонения траектории движения пули
        //! @param angle Угол, на который требуется отклонить траекторию пули
        void setAngle(int angle) {
            angle0 = angle;
        }

        //! @brief Возвращает положение пули на холсте TXlib по оси абсцисс
        int getX() {
            return x0;
        }

        //! @brief Возвращает положение пули на холсте TXlib по оси ординат
        int getY() {
            return y0;
        }

        //! @brief Возвращает угол отклонения пули
        int getAngle() {
            return angle0;
        }

        //! @brief Перемещает пулю на ~6 пикселей в направлении угла отклонения траектории пули
        void moveBullet() {
            x0 = x0 + speedX;
            y0 = y0 + speedY;
            draw();
        }

        //! @brief Рисует пулю на холсте TXlib. При вызове данного метода автоматически вызывается метод moveBullet()
        void draw() {
            txSetColor(TX_BLACK);
            txSetFillColor(TX_YELLOW);
            txCircle(getX(), getY(), 2);
        }
};

//! @brief Класс зомби. Способен отрисовывать и перемещать зомби на холсте TXlib
class Zombie {
    private:
        int x0, y0;
        int lives0=100;
    public:

        //! @brief Конструктор класса Zombie
        //! @param x Координата начальной точки по оси абсцисс
        //! @param y Координата начальной точки по оси ординат
        Zombie(int x, int y) {
            x0=x;
            y0=y;
        }

        //! @brief Устанавливает координату зомби по оси абсцисс
        //! @param x Координата точки, в которую нужно переместить зомби по оси абсцисс
        void setX(int x) {
            x0 = x;
        }

        //! @brief Устанавливает координату зомби по оси ординат
        //! @param y Координата точки, в которую нужно переместить зомби по оси ординат
        void setY(int x) {
            y0 = x;
        }

        //! @brief Возвращает положение зомби на холсте TXlib по оси абсцисс
        int getX() {
            return x0;
        }

        //! @brief Возвращает положение зомби на холсте TXlib по оси ординат
        int getY() {
            return y0;
        }

        //! @brief Возвращает здоровье зомби (по умолчанию = 100)
        int getLives()
        {
            return lives0;
        }

        //! @brief Уменьшает здоровье зомби
        //! @param lives количество отнимаемых хп.
        //! @warning Если ХП <=0 то зомби не уничтожается.
        void downLives(int lives)
        {
            lives0=lives0-lives;
        }

        //! @brief Перемещает зомби вниз по экрану. Вызывает метод drawZombie()
        void moveZombie() {
            y0 = y0 + 1;
            drawZombie();
        }

        //! @brief Рисует зомби на холсте TXlib
        //! @warning Необходимо наличие файла-текстуры (расширение .bmp) в директории с библиотекой. При отсутствии такового на экран вылетит ошибка
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

//! @brief Класс кнопки. Способен отрисовывать кнопку на холсте TXlib. Вшита обработка нажатия мышью на кнопку
class Button
    {
        private:
            int x0, y0, textSize0;
            char text0[255];
            bool pressed=false;
        public:

            //! @brief Конструктор класса Button
            //! @param x Координата начальной точки по оси абсцисс
            //! @param y Координата начальной точки по оси ординат
            //! @param text Текст, который отобразится на кнопке
            //! @param textSize Размер шрифта текста на кнопке
            Button(int x, int y, char text[255], int textSize)
            {
                x0=x;
                y0=y;
                textSize0=textSize;
                strcpy(text0, text);
            }

            //! @brief Смотри классы Bullet и Zombie
            void setX(int x)
            {
                x0=x;
            }

            //! @brief Смотри классы Bullet и Zombie
            void setY(int y)
            {
                y0=y;
            }

            //! @brief Устанавливает текст на кнопке
            //! @param Ваш текст
            void setText(char text[255])
            {
                strcpy(text0, text);
            }

            //! @brief Возвращает true если кнопка была нажата мышью, иначе возвращает false
            bool getPressed()
            {
                return pressed;
            }

            //! @brief Рисует кнопку на холсте TXlib. Вызывает метод pressCheck
            void drawButton()
            {
                txSetColor(TX_GREEN);
                txSelectFont("Arial", textSize0);
                txRectangle(x0, y0, x0+10+txGetTextExtentX(text0), y0+6+txGetTextExtentY(text0));
                txTextOut(x0+5, y0+3, text0);
                pressCheck();
            }

            //! @brief Производит обработку нажатия мышью на кнопку (Не путать с getPressed())
            //! @warning Метод getPressed() возвращает значение переменной, в которую сохраняется состояние кнопки (нажата или нет), а pressCheck() непосредственно обрабатывает это событие
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
