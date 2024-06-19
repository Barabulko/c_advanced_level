#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20
#define MAX_SNAKES 5
#define SNAKE_MAX_LENGTH 100

int snakeX[MAX_SNAKES][SNAKE_MAX_LENGTH], snakeY[MAX_SNAKES][SNAKE_MAX_LENGTH];
int snakeLength[MAX_SNAKES];
int fruitX[MAX_SNAKES], fruitY[MAX_SNAKES];
int direction[MAX_SNAKES]; // 0 - вверх, 1 - вправо, 2 - вниз, 3 - влево

void generateFruit(int index) {
    fruitX[index] = rand() % WIDTH;
    fruitY[index] = rand() % HEIGHT;
}

void setup() {
    for (int i = 0; i < MAX_SNAKES; i++) {
        snakeX[i][0] = WIDTH / 2;
        snakeY[i][0] = HEIGHT / 2;
        generateFruit(i);
        snakeLength[i] = 1;
        direction[i] = rand() % 4; // Случайное начальное направление
    }
}

void findNextMove(int index) {
    if (snakeX[index][0] < fruitX[index]) {
        direction[index] = 1; // Двигаться вправо
    } else if (snakeX[index][0] > fruitX[index]) {
        direction[index] = 3; // Двигаться влево
    } else if (snakeY[index][0] < fruitY[index]) {
        direction[index] = 2; // Двигаться вниз
    } else {
        direction[index] = 0; // Двигаться вверх
    }
}

void controlSnake(int index) {
    if (_kbhit()) {
	char input = getch();
	    switch(input) {
	        case 'w':
	            direction[index] = 0; // Вверх
        	    break;
	        case 'd':
	            direction[index] = 1; // Вправо
	            break;
	        case 's':
	            direction[index] = 2; // Вниз
	            break;
	        case 'a':
	            direction[index] = 3; // Влево
	            break;
	    }
      }
}

void draw() {
    system("cls");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // Отрисовка змеек и фруктов
            int printed = 0;
            for (int i = 0; i < MAX_SNAKES; i++) {
                if (x == snakeX[i][0] && y == snakeY[i][0]) {
                    printf("O"); // Голова змейки
                    printed = 1;
                } else {
                    for (int j = 1; j < snakeLength[i]; j++) {
                        if (x == snakeX[i][j] && y == snakeY[i][j]) {
                            printf("o"); // Тело змейки
                            printed = 1;
                        }
                    }
                }
            }
            if (!printed) {
                for (int i = 0; i < MAX_SNAKES; i++) {
                    if (x == fruitX[i] && y == fruitY[i]) {
                        printf("*"); // Фрукт
                        printed = 1;
                    }
                }
            }
            if (!printed) {
                printf(" "); // Пустое место
            }
        }
        printf("\n");
    }
}

void update() {
    for(int i = 0; i < MAX_SNAKES; i++) {
        // Перемещаем голову змейки в соответствии с направлением
        switch(direction[i]) {
            case 0:
                snakeY[i][0]--;
                break;
            case 1:
                snakeX[i][0]++;
                break;
            case 2:
                snakeY[i][0]++;
                break;
            case 3:
                snakeX[i][0]--;
                break;
        }

        // Проверяем столкновение с границами экрана
        if(snakeX[i][0] < 0) {
		direction[i]=1;
	}
	if(snakeX[i][0] >= WIDTH) {
		direction[i]=3;
	}
	if(snakeY[i][0] < 0) {
		direction[i]=2;
	}
	if(snakeY[i][0] >= HEIGHT) {
		direction[i]=4;
        }

        // Проверяем столкновение с фруктом
        if(snakeX[i][0] == fruitX[i] && snakeY[i][0] == fruitY[i]) {
            // Змейка съела фрукт, увеличиваем длину и генерируем новый фрукт
            snakeLength[i]++;
            generateFruit(i);
        }

        // Перемещаем тело змейки
        for(int j = snakeLength[i]; j > 0; j--) {
            snakeX[i][j] = snakeX[i][j-1];
            snakeY[i][j] = snakeY[i][j-1];
        }
    }

    // Дополнительная логика проверки столкновений между змейками, если необходимо
}

int main() {
    srand(time(NULL));
    setup();

    while (1) {
        draw();
        for (int i = 0; i < MAX_SNAKES; i++) {
            findNextMove(i);
            controlSnake(i);
	    update();
	    Sleep(100);
        }
    }

    return 0;
}