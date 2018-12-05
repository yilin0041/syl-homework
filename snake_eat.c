#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define space ' '
#define wall '*'
#define max 20
#define snake_head 'H'
#define snake_body 'X'
#define food '$'
//先定义出所用的所有函数 
void output();
void get_food();
void clear(); 
void left();
void right();
void up();
void down();
//初始化地图 
char map[12][13] = {
	"************",
	"*XXXXH     *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"************"
};
int snakeX[max] = {5, 4, 3, 2, 1};//标记蛇的列 
int snakeY[max] = {1, 1, 1, 1, 1};//标记蛇的行 
int snakeLength = 5;//蛇的长度 
int  play = 1; //标识是否Game over
void get_food(){

	int row, column;

	do{
		srand(time(NULL));
		row = 1 + rand() % 11;
		srand(time(NULL));
		column = 1 + rand() % 11;
	} while(map[row][column] != space);
	map[row][column] = food;
}
void output()//打印地图 
{
	int i; 
	for(i = 0; i < 12; i++){
	printf("\t%s\n", map[i]);
	}
}

void clear()//清空屏幕 
{
    #ifdef _WIN32
    system("cls");
    #elif __linux__
    system("clear");
    #endif
}
int main(){
	char ch;
	get_food();
	output();
	while(play){ //判断蛇是否死亡，可能被left、right、up、down所改变
		printf("please input w/a/s/d to control the snake.\n");
		ch = getchar(); 
		switch(ch){
			case 'A':case 'a':{
			clear();left();	
				break;
			}
			case 'D':case 'd':{
			clear();right();	
				break;
			}
			case 'W':case 'w':{
			clear();up();	
				break;
			}
			case 'S':case 's':{
			clear();down();	
				break;
			}
			default:{ 
			break;//匹配到其他所有字符，都要求重新输入
		}
		} 
	}		
	printf("\nGame over!\n");
} 
void left(){
	int i;
	if(map[snakeY[0]][snakeX[0] - 1] == snake_body ||
	   map[snakeY[0]][snakeX[0] - 1] == wall){
		play = 0; //蛇头碰到蛇身或墙壁时，结束游戏
		return;
	} else{
	
		int bool_tem = 0; //判断是不是吃掉了食物。 
		if(map[snakeY[0]][snakeX[0] - 1] == food){
			bool_tem = 1;
			if(snakeLength != max)
				snakeLength++;//如果吃掉，长度+1.（但不超过20） 
		} else
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = space;//加空格 
				for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1]; //每一节的位置变为前一节的原位置
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = snake_body; //原蛇头位置变为蛇身
		snakeX[0]--;
		map[snakeY[0]][snakeX[0]] = snake_head; //蛇头的新位置
		if(bool_tem)
			get_food(); //蛇身移动后，再生成食物
	}
	output();//打印地图 
}
//下面函数的思想与left相同，故不作阐述。 
void right(){ 
	int i;
	if(map[snakeY[0]][snakeX[0] + 1] == snake_body ||
	   map[snakeY[0]][snakeX[0] + 1] == wall){
		play = 0;
		return;
	} else{
		int bool_tem = 0;
		if(map[snakeY[0]][snakeX[0] + 1] == food){
			bool_tem = 1;
			if(snakeLength != max)
				snakeLength++;
		} else
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = space;
		for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1];
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = snake_body;
		snakeX[0]++;
		map[snakeY[0]][snakeX[0]] = snake_head;
		if(bool_tem)
			get_food();
	}
	output();
} 
void up(){
	int i;
	if(map[snakeY[0] - 1][snakeX[0]] == snake_body ||
	   map[snakeY[0] - 1][snakeX[0]] == wall){
		play = 0;
		return;
	} else{
		int bool_tem = 0;
		if(map[snakeY[0] - 1][snakeX[0]] == food){
			bool_tem = 1;
			if(snakeLength != max)
			snakeLength++;
		} else
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = space;
		for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1];
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = snake_body;
		snakeY[0]--;
		map[snakeY[0]][snakeX[0]] = snake_head;
		if(bool_tem)
			get_food();
	}
	output();
}
void down(){
	int i;
	if(map[snakeY[0] + 1][snakeX[0]] == snake_body ||
	   map[snakeY[0] + 1][snakeX[0]] == wall){
		play = 0;
		return;
	} else{
		int bool_tem = 0;
		if(map[snakeY[0] + 1][snakeX[0]] == food){
			bool_tem = 1;
			if(snakeLength != max)
				snakeLength++;
		} else
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = space;

		for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1];
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = snake_body;
		snakeY[0]++;
		map[snakeY[0]][snakeX[0]] = snake_head;
		if(bool_tem)
			get_food();
	}
output();
}
