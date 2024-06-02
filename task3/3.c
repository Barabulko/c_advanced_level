#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>

#define MAX_X 15
#define MAX_Y 15

int isPaused = 0;
int score = 0;

typedef struct tail_t{
	int x;
	int y;
	} tail_t;
	
typedef struct snake_t{
	int x;
	int y;
	int dx;
	int dy;
	struct tail_t * tail;
	size_t tsize;
	}  snake_t;

typedef struct fruit_t{
	int x;
	int y;
	} fruit_t;

struct snake_t initSnake(int x, int y, size_t tsize){
	struct snake_t snake;
	snake.x = x;
	snake.y = y;
	snake.dx = 1;
	snake.dy = 0;
	snake.tsize = tsize;
	snake.tail = (tail_t *) malloc (sizeof(tail_t) * 100);
	for (int i =0; i < tsize; ++i){
		snake.tail[i].x = x + i + 1;
		snake.tail[i].y = y;
		}
	return snake;
}

struct fruit_t initFruit(){
	struct fruit_t fruit;
	fruit.x = rand() % MAX_X;
	fruit.y = rand() % MAX_Y;
	return fruit;
}

	
// @**
void printField(struct snake_t snake, struct fruit_t fruit){
		char matrix[MAX_X][MAX_Y];
		for (int i = 0; i < MAX_X; ++i){
			for (int j = 0; j < MAX_Y; ++j)
			{
				matrix[i][j] = ' ';
				}}
		
		matrix[fruit.x][fruit.y] = 'O';
		
		matrix[snake.x][snake.y] = '@';
		for (int i = 0; i < snake.tsize; ++i){
			matrix[snake.tail[i].x][snake.tail[i].y] = '*';
			}
		
		for (int j = 0; j < MAX_Y; ++j){
			for (int i = 0; i < MAX_X; ++i)
			{
				printf("%c", matrix[i][j]);
				}
				printf("\n");
				}
		printf("Score: %d\n", score);
	}
	
snake_t move(snake_t snake){
	for (int i = snake.tsize - 1; i > 0; i--){
		snake.tail[i] = snake.tail[i-1];
		}
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;
	
	snake.x += snake.dx;
	snake.y += snake.dy;

	if (snake.x >= MAX_X)
        	snake.x = 0;
	
	if (snake.x < 0){
		snake.x = MAX_X - 1;
		}
	
        if (snake.y >= MAX_Y)
    		snake.y = 0;

	if (snake.y < 0)
        	snake.y = MAX_Y - 1;

	return snake;
	}

void logic(snake_t *snake, fruit_t *fruit) {
	if ((snake->x==fruit->x) && (snake->y == fruit->y))
	{
		fruit->x = rand() % MAX_X;
		fruit->y = rand() % MAX_Y;
		snake->tsize=snake->tsize+1;
		score=score+1;
	}
}

void input(snake_t *snake) //дз №2.2
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
	    if(snake->dx==0) 
                snake->dx = -1; //учитываем требование дз №2.1
            snake->dy = 0;
            break;
        case 'd':
            if(snake->dx==0) 
                snake->dx = 1;
            snake->dy = 0;
            break;
        case 'w':
            snake->dx = 0;
            if(snake->dy==0) 
                snake->dy = -1;
            break;
        case 's':
            snake->dx = 0;
            if(snake->dy==0) 
                snake->dy = 1;
            break;
	case 'p': //Задание 3.3 - пауза
	    isPaused = !isPaused;
	    break;
        }
    }
}	
	
int main(){
	struct snake_t snake = initSnake( 10, 5, 6);
	struct fruit_t fruit = initFruit();
	printField(snake, fruit);
	while(1)
	{	
		if (score<20) {Sleep(200-score*10);} else {Sleep(10);} //Задание 3.2 - увеличение скорости
		input(&snake);
		if(!isPaused)
		{
			logic(&snake, &fruit); //Задание 3.1 - фрукты и счетчик
			snake = move(snake);
			system("cls");
			printField(snake, fruit);
		}
	}
	return 0;
	}