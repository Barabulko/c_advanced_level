#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#define WIDTH 30
#define HEIGHT 20
#define SNAKE_MAX_LENGTH 100

int snakeX[SNAKE_MAX_LENGTH], snakeY[SNAKE_MAX_LENGTH];
int snakeLength = 1;
int fruitX, fruitY;
int direction = 0; // 0 - вверх, 1 - вправо, 2 - вниз, 3 - влево

void generateFruit() {
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
}

void setup() {
    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;
    generateFruit();
}

void findNextMove() {
    if (snakeX[0] < fruitX) {
        direction = 1; // Двигаться вправо
    } else if (snakeX[0] > fruitX) {
        direction = 3; // Двигаться влево
    } else if (snakeY[0] < fruitY) {
        direction = 2; // Двигаться вниз
    } else {
        direction = 0; // Двигаться вверх
    }
}

void draw() {
    system("cls");
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == snakeX[0] && y == snakeY[0]) {
                printf("O"); // Голова змейки
            } else if (x == fruitX && y == fruitY) {
                printf("X"); // Фрукт
            } else {
                int printSnake = 0;
                for (int i = 1; i < snakeLength; i++) {
                    if (x == snakeX[i] && y == snakeY[i]) {
                        printf("o"); // Часть змейки
                        printSnake = 1;
                        break;
                    }
                }
                if (!printSnake) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
}

void logic() {
    // Движение змейки
    for (int i = snakeLength; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // Управление змейкой компьютером
    findNextMove();

    // Движение в соответствии с выбранной направлением
    switch(direction) {
        case 0:
            snakeY[0]--;
            break;
        case 1:
            snakeX[0]++;
            break;
        case 2:
            snakeY[0]++;
            break;
        case 3:
            snakeX[0]--;
            break;
    }

    // Проверка на столкновение со стеной
    if (snakeX[0] < 0 || snakeX[0] >= WIDTH || snakeY[0] < 0 || snakeY[0] >= HEIGHT) {
        // Игра окончена
        // Допишите здесь логику завершения игры
    }

    // Проверка на поедание фрукта
    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        // Увеличение длины змейки
        snakeLength++;
        generateFruit();
    }
}

int main() {
    setup();

    while (1) {
        draw();
        logic();
	Sleep(50);
    }

    return 0;
}