#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>

#define MAX_X 20
#define MAX_Y 20

#define GRN   "\x1B[32m"
#define RED   "\x1B[31m"
#define BLUE   "\x1B[34m"

#define RESET "\x1B[0m"

int isPaused = 0;
int score = 0;
int plc= 0; //player count.


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
	} snake_t;

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
	for (int i = 0; i < tsize; ++i){
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

void printField(snake_t (*snake) [2], struct fruit_t fruit){
		char* matrix[MAX_X][MAX_Y];
		for (int i = 0; i < MAX_X; ++i){
			for (int j = 0; j < MAX_Y; ++j)
			{
				matrix[i][j] = " ";
				}}
		
		matrix[fruit.x][fruit.y] = GRN"O"RESET;
		
		matrix[snake[0]->x][snake[0]->y] = RED"@"RESET;
		matrix[snake[1]->x][snake[1]->y] = BLUE"@"RESET;

		for (int i = 0; i < snake[0]->tsize; ++i){
			matrix[snake[0]->tail[i].x][snake[0]->tail[i].y] = RED"*"RESET;
			}

		for (int i = 0; i < snake[1]->tsize; ++i){
			matrix[snake[1]->tail[i].x][snake[1]->tail[i].y] = BLUE"*"RESET;
			}


		for (int j = 0; j < MAX_Y; ++j){
			for (int i = 0; i < MAX_X; ++i)
			{
				printf("%s", matrix[i][j]);
				}
				printf("\n");
				}
		printf("Score: %d\n", score);
	}
	
void move(snake_t (*snake) [2]){

	for (int j = 0; j<2; j++){
		for (int i = snake[j]->tsize - 1; i > 0; i--){
			snake[j]->tail[i] = snake[j]->tail[i-1];
			}
		snake[j]->tail[0].x = snake[j]->x;
		snake[j]->tail[0].y = snake[j]->y;

		snake[j]->x += snake[j]->dx;
		snake[j]->y += snake[j]->dy;
		//printf("pos1(%d, %d), pos2(%d, %d)", snake[0]->x, snake[0]->y, snake[1]->x, snake[1]->y);		

		if (snake[j]->x >= MAX_X)
	        	snake[j]->x = 0;
		
		if (snake[j]->x < 0){
			snake[j]->x = MAX_X - 1;
			}
		
	        if (snake[j]->y >= MAX_Y)
	    		snake[j]->y = 0;
	
		if (snake[j]->y < 0)
	        	snake[j]->y = MAX_Y - 1;

		}	
	}

void logic(snake_t (*snake) [2], fruit_t *fruit) {
	
	for (int j=0; j<2; j++){
		if ((snake[j]->x==fruit->x) && (snake[j]->y == fruit->y))
		{
			fruit->x = rand() % MAX_X;
			fruit->y = rand() % MAX_Y;
			snake[j]->tsize=snake[j]->tsize+1;
			printf("jlen %d",snake[j]->tsize);
			score=score+1;
		}
	}
}

void input(snake_t (*snake) [2]) //дз №2.2
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
		for (int i=0; i<(2-plc+1); i++)
		{
		    if(snake[i]->dx==0) 
        	        snake[i]->dx = -1; //учитываем требование дз №2.1
	            snake[i]->dy = 0;
		}
            break;
        case 'd':
		for (int i=0; i<(2-plc+1); i++)
		{
		    if(snake[i]->dx==0) 
        	        snake[i]->dx = 1; //учитываем требование дз №2.1
	            snake[i]->dy = 0;
		}
            break;
        case 'w':
		for (int i=0; i<(2-plc+1); i++)
		{
		    if(snake[i]->dy==0) 
        	        snake[i]->dy = -1; //учитываем требование дз №2.1
	            snake[i]->dx = 0;
		}
            break;
        case 's':
		for (int i=0; i<(2-plc+1); i++)
		{
		    if(snake[i]->dy==0) 
        	        snake[i]->dy = 1; //учитываем требование дз №2.1
	            snake[i]->dx = 0;
		}
            break;
        case 'j':
		for (int i=plc-1; i<2; i++)
		{
		    if(snake[i]->dx==0) 
        	        snake[i]->dx = -1; //учитываем требование дз №2.1
	            snake[i]->dy = 0;
		}
            break;
        case 'l':
		for (int i=plc-1; i<2; i++)
		{
		    if(snake[i]->dx==0) 
        	        snake[i]->dx = 1; //учитываем требование дз №2.1
	            snake[i]->dy = 0;
		}
            break;
        case 'i':
		for (int i=plc-1; i<2; i++)
		{
		    if(snake[i]->dy==0) 
        	        snake[i]->dy = -1; //учитываем требование дз №2.1
	            snake[i]->dx = 0;
		}
            break;
        case 'k':
		for (int i=plc-1; i<2; i++)
		{
		    if(snake[i]->dy==0) 
        	        snake[i]->dy = 1; //учитываем требование дз №2.1
	            snake[i]->dx = 0;
		}
            break;


	case 'p': //Задание 3.3 - пауза
	    isPaused = !isPaused;
	    break;
        }
    }
}	

int startMenu(){
	printf("Choose an option:\n1. 1 player\n2. 2 players\n3. Choose colors\n4. Exit\n");
	int menu_option = 0;
	scanf("%d", &menu_option);	
	return menu_option;
}

int chooseColor(){
	printf("Choose color scheme:\n1. RBG\n2. RGB\n3. GRB\n");
	int res = 1;
	scanf("%d", &res);
	switch (res) {
	case 1:
		//TODO
		break;
	case 2:
		//TODO	
		break;
	case 3:
		//TODO
		break;
	}
}
	
int main(){
	
	while ((plc=startMenu())>2){
		if (plc==4) exit(0);
		if (plc==3) chooseColor();		
	}
	
//	struct snake_t snake = initSnake( 10, 5, 6);
	snake_t snake1 = initSnake(10, 5, 3);
	snake_t snake2 = initSnake(5, 10, 4);

	snake_t snakes [2] = {snake1, snake2};
	struct fruit_t fruit = initFruit();
	printField(&snakes, fruit);
	while(1)
	{	
		if (score<20) {Sleep(200-score*10);} else {Sleep(10);} //Задание 3.2 - увеличение скорости
		input(&snakes);
		if(!isPaused)
		{
			logic(&snakes, &fruit); //Задание 3.1 - фрукты и счетчик
			move(&snakes);
			system("cls");
			printField(&snakes, fruit);
		}
	}
	return 0;
	}