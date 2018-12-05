#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define space ' '
#define wall '*'
#define max 20
#define snake_head 'H'
#define snake_body 'X'
#define food '$'
//�ȶ�������õ����к��� 
void output();
void get_food();
void clear(); 
void left();
void right();
void up();
void down();
//��ʼ����ͼ 
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
int snakeX[max] = {5, 4, 3, 2, 1};//����ߵ��� 
int snakeY[max] = {1, 1, 1, 1, 1};//����ߵ��� 
int snakeLength = 5;//�ߵĳ��� 
int  play = 1; //��ʶ�Ƿ�Game over
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
void output()//��ӡ��ͼ 
{
	int i; 
	for(i = 0; i < 12; i++){
	printf("\t%s\n", map[i]);
	}
}

void clear()//�����Ļ 
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
	while(play){ //�ж����Ƿ����������ܱ�left��right��up��down���ı�
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
			break;//ƥ�䵽���������ַ�����Ҫ����������
		}
		} 
	}		
	printf("\nGame over!\n");
} 
void left(){
	int i;
	if(map[snakeY[0]][snakeX[0] - 1] == snake_body ||
	   map[snakeY[0]][snakeX[0] - 1] == wall){
		play = 0; //��ͷ���������ǽ��ʱ��������Ϸ
		return;
	} else{
	
		int bool_tem = 0; //�ж��ǲ��ǳԵ���ʳ� 
		if(map[snakeY[0]][snakeX[0] - 1] == food){
			bool_tem = 1;
			if(snakeLength != max)
				snakeLength++;//����Ե�������+1.����������20�� 
		} else
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = space;//�ӿո� 
				for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1]; //ÿһ�ڵ�λ�ñ�Ϊǰһ�ڵ�ԭλ��
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = snake_body; //ԭ��ͷλ�ñ�Ϊ����
		snakeX[0]--;
		map[snakeY[0]][snakeX[0]] = snake_head; //��ͷ����λ��
		if(bool_tem)
			get_food(); //�����ƶ���������ʳ��
	}
	output();//��ӡ��ͼ 
}
//���溯����˼����left��ͬ���ʲ��������� 
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
