#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>

#define MAX_X 15
#define MAX_Y 15

int dx = 1, dy = 0; // направление движения змейки (по умолчанию вправо)

typedef struct tail_t{
	int x;
	int y;
	} tail_t;
	
typedef struct snake_t{
	int x;
	int y;
	struct tail_t * tail;
	size_t tsize;
	}  snake_t;
// --> x
// || Y
// \/
// @**
struct snake_t initSnake(int x, int y, size_t tsize){
	struct snake_t snake;
	snake.x = x;
	snake.y = y;
	snake.tsize = tsize;
	snake.tail = (tail_t *) malloc (sizeof(tail_t) * 100);
	for (int i =0; i < tsize; ++i){
		snake.tail[i].x = x + i +1;
		snake.tail[i].y = y;
		}
	return snake;
}

	
// @**
void printSnake(struct snake_t snake){
		char matrix[MAX_X][MAX_Y];
		for (int i = 0; i < MAX_X; ++i){
			for (int j = 0; j < MAX_Y; ++j)
			{
				matrix[i][j] = ' ';
				}}
		
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
	}
	
// <--  @** tsize = 2
//     @**

//  @**      @***
//    * <--     *
//  ***        **
snake_t moveLeft(snake_t snake){
	for (int i = snake.tsize - 1; i > 0; i--){
		snake.tail[i] = snake.tail[i-1];
		}
	snake.tail[0].x = snake.x;
	snake.tail[0].y = snake.y;
	
	snake.x += dx;
	snake.y += dy;

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

void input() //дз №2.2
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
	
int main(){
	struct snake_t snake = initSnake( 10, 5, 6);
	printSnake(snake);
	while(1)//for( int i = 0; i < 8; ++i)
	{
		input();
		snake = moveLeft(snake);
		Sleep(100);
		system("cls");
		printSnake(snake);
	}
	return 0;
	}