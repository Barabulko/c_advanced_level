#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 20
#define RED 12
#define GREEN 10
#define BLUE 9

int snakeX[2][100], snakeY[2][100]; // массивы для хранения координат двух змеек
int fruitX, fruitY; // фрукты
int length[2] = { 1, 1 }; // длины змеек
int direction[2][2] = { 0, 1 }; // направления движения змеек (по умолчанию вправо)
int score[2] = { 0, 0 }; // счетчики съеденной еды
int isPaused = 0; // флаг паузы

void setup()
{
    for (int s = 0; s < 2; s++)
    {
        snakeX[s][0] = WIDTH / 2 - s; // начальные координаты змеек
        snakeY[s][0] = HEIGHT / 2;
    }

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

            int print = 0;
            for (int s = 0; s < 2; s++)
            {
                for (int k = 0; k < length[s]; k++)
                {
                    if (i == snakeY[s][k] && j == snakeX[s][k])
                    {
                        if (k == 0)
                            printf("\x1B[38;5;%dmO", s == 0 ? RED : BLUE);
                        else
                            printf("\x1B[38;5;%dmo", s == 0 ? GREEN : BLUE);
                        print = 1;
                    }
                }
            }

            if (!print)
            {
                if (i == fruitY && j == fruitX)
                    printf("\x1B[38;5;11mX");
                else
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

    printf("Score Player 1: %d\tScore Player 2: %d\n", score[0], score[1]);
}

void input()
{
    if (_kbhit())
    {
        char key = _getch();
	for (int s = 0; s < 2; s++) {
	        switch (key)
        	{
	        case 'a':
	            direction[s][0] = -1;
	            direction[s][1] = 0;
	            break;
	        case 'd':
	            direction[s][0] = 1;
	            direction[s][1] = 0;
	            break;
	        case 'w':
	            direction[s][1] = -1;
	            direction[s][0] = 0;
	            break;
	        case 's':
	            direction[s][1] = 1;
	            direction[s][0] = 0;
	            break;
		}
	}
	switch(key)
	{
        case 'p':
            isPaused = !isPaused;
            break;
        case 'q':
            exit(0);
	}
    }
}

void logic()
{
    for (int s = 0; s < 2; s++)
    {
        for (int i = length[s]; i > 0; i--)
        {
            snakeX[s][i] = snakeX[s][i - 1];
            snakeY[s][i] = snakeY[s][i - 1];
        }

        snakeX[s][0] += direction[s][0];
        snakeY[s][0] += direction[s][1];

        if (snakeX[s][0] == fruitX && snakeY[s][0] == fruitY)
        {
            length[s]++;
            score[s]++;
            fruitX = rand() % WIDTH;
            fruitY = rand() % HEIGHT;
        }
    }
}

int main()
{
    setup();
    while (1)
    {
        if (!isPaused)
        {
            draw();
            input();
            logic();
            Sleep(100); // задержка в миллисекундах
        }
    }

    return 0;
}