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
int activeSnake = 0;
int isPaused = 0;
int crashWarning[MAX_SNAKES];

void generateFruit(int index) {
    fruitX[index] = rand() % WIDTH;
    fruitY[index] = rand() % HEIGHT;
}

void setup() {
    for (int i = 0; i < MAX_SNAKES; i++) {
        snakeX[i][0] = WIDTH / 2;
        snakeY[i][0] = HEIGHT / 2;
        generateFruit(i);
        snakeLength[i] = 2;
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

void draw() {
    system("cls");
	
    printf("keys 1..5 - choose snake, 0 - autopilot\n");
    printf("keys 'wasd' - move snake, 'p' - pause\n");

    for (int y = -1; y <= HEIGHT; y++) {
        for (int x = -1; x <= WIDTH; x++) {
	    if (x==WIDTH) {printf("#\n"); continue;}
	    if (y==-1) {printf("#"); continue;}
	    if (y==HEIGHT) {printf("#"); continue;}
	    if (x==-1) {printf("#"); continue;}

            // Отрисовка змеек и фруктов
            int printed = 0;
            for (int i = 0; i < MAX_SNAKES; i++) {
                if (x == snakeX[i][0] && y == snakeY[i][0]) {
                    if (i==activeSnake) {printf("@");} else {printf("O");} // Голова змейки
                    printed = 1;
                } else {
                    for (int j = 1; j < snakeLength[i]; j++) {
                        if (x == snakeX[i][j] && y == snakeY[i][j]) {
                            if (i==activeSnake) {printf("*");} else {printf("o");} // Часть змейки
                            printed = 1;
                        }
                    }
                }
                if (x == fruitX[i] && y == fruitY[i]) {
                    printf("X"); // Фрукт
                    printed = 1;
                }
            }
            if (!printed) {
                printf(" ");
            }
        }
    }

    printf("\n");
    printf("Scores:\n");
    for (int i = 0; i<MAX_SNAKES; i++) {
	printf("%d - [%d]\n", i+1, snakeLength[i]-2);
    }

    printf("\n");

    for (int i = 0; i<MAX_SNAKES; i++) {
	if(crashWarning[i]) {printf("snake %d crashed!\n", i+1);}
    }    
}

void logic() {
    // Движение каждой змейки
    for (int i = 0; i < MAX_SNAKES; i++) {
        // Логика движения
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
		direction[i]=0;
        }
        
        if (direction[i] == 0) {
            snakeY[i][0]--;
        } else if (direction[i] == 1) {
            snakeX[i][0]++;
        } else if (direction[i] == 2) {
            snakeY[i][0]++;
        } else if (direction[i] == 3) {
            snakeX[i][0]--;
        }
        
        // Проверка съедания фрукта
	for(int j=0; j<MAX_SNAKES; j++) {
	        if (snakeX[i][0] == fruitX[j] && snakeY[i][0] == fruitY[j]) {
        	    snakeLength[i]++;
	            generateFruit(j);
	        }
	}

	//Проверка столкновения змейки с концом
	if(snakeX[i][0] == snakeX[i][snakeLength[i]] && snakeY[i][0] == snakeY[i][snakeLength[i]] && snakeLength[i]>2) {
		crashWarning[i] = 1;
	}
        
        // Передвижение остальных частей змейки
        for (int j = snakeLength[i]; j > 0; j--) {
            snakeX[i][j] = snakeX[i][j - 1];
            snakeY[i][j] = snakeY[i][j - 1];
        }
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
	        case '0':
	            activeSnake = -1;
	            break;
	        case '1':
	            activeSnake = 0;
	            break;
	        case '2':
	            activeSnake = 1; 
	            break;
	        case '3':
	            activeSnake = 2;
	            break;
	        case '4':
	            activeSnake = 3;
	            break;
	        case '5':
	            activeSnake = 4;
	            break;
	        case 'p':
	            isPaused = !isPaused;
	            break;
	    }
      }
}

int main() {
    setup();

    while (1) {

        // Управление и поиск следующего хода для каждой змейки
        for (int i = 0; i < MAX_SNAKES; i++) {
	    if (i==activeSnake) {controlSnake(i);}
            else {findNextMove(i);}
        }
	if (!isPaused) {
	        logic();
        	draw();
	}
	Sleep(200);

        // Обработка клавиатурного ввода (если необходимо)
    }

    return 0;
}