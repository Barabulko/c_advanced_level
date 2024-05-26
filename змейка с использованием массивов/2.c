#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 20

int snakeX[100], snakeY[100]; // массивы для хранения координат змейки
int length = 1; // длина змейки
int fruitX, fruitY; // координаты фрукта
int dx = 1, dy = 0; // направление движения змейки (по умолчанию вправо)

void setup()
{
    snakeX[0] = WIDTH / 2; // начальные координаты змейки
    snakeY[0] = HEIGHT / 2;

    // генерируем случайные координаты для пищи
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
}

void draw()
{
    system("cls"); // очищаем экран

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0)
                printf("#");
            if (i == snakeY[0] && j == snakeX[0])
                printf("@");
            else if (i == fruitY && j == fruitX)
                printf("X");
            else
            {
                int print = 0;
                for (int k = 1; k < length; k++)
                {
                    if (i == snakeY[k] && j == snakeX[k])
                    {
                        printf("*");
                        print = 1;
                    }
                }
                if (print == 0)
                    printf(" ");
            }

            if (j == WIDTH - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
	    if(dx==0) 
                dx = -1; //учитываем требование дз №2.1
            dy = 0;
            break;
        case 'd':
            if(dx==0) 
                dx = 1;
            dy = 0;
            break;
        case 'w':
            dx = 0;
            if(dy==0) 
                dy = -1;
            break;
        case 's':
            dx = 0;
            if(dy==0) 
                dy = 1;
            break;
        }
    }
}

void logic()
{
    int prevX = snakeX[0];
    int prevY = snakeY[0];
    int prev2X, prev2Y;
    snakeX[0] += dx; // обновляем голову змейки
    snakeY[0] += dy;

    for (int i = 1; i < length; i++)
    {
        prev2X = snakeX[i];
        prev2Y = snakeY[i];
        snakeX[i] = prevX;
        snakeY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // если змейка вышла за пределы экрана, передвигаем ее на противоположную сторону
    if (snakeX[0] >= WIDTH)
        snakeX[0] = 0;
    else if (snakeX[0] < 0)
        snakeX[0] = WIDTH - 1;

    if (snakeY[0] >= HEIGHT)
        snakeY[0] = 0;
    else if (snakeY[0] < 0)
        snakeY[0] = HEIGHT - 1;

    // проверка на столкновение с пищей
    if (snakeX[0] == fruitX && snakeY[0] == fruitY)
    {
        length++;
        fruitX = rand() % WIDTH; // генерируем новую пищу
        fruitY = rand() % HEIGHT;
    }
}

int main()
{
    setup();
    while (1)
    {
        draw();
        input();
        logic();
        Sleep(100); // устанавливаем задержку для создания анимации
    }

    return 0;
}
