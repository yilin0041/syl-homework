#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define space ' '
#define wall '*'
#define max 20
#define snake_head 'H'
#define snake_body 'X'

//�ȶ�������õ����к��� 
void output();
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
	} else
	{
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = space;//�ӿո� 
				for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1]; //ÿһ�ڵ�λ�ñ�Ϊǰһ�ڵ�ԭλ��
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = snake_body; //ԭ��ͷλ�ñ�Ϊ����
		snakeX[0]--;
		map[snakeY[0]][snakeX[0]] = snake_head; //��ͷ��λ�� 
	}
	output();//���������ͼ 
}
//���溯����˼���left������ͬ���ʲ�һһע�� 
void right(){ 
	int i;
	if(map[snakeY[0]][snakeX[0] + 1] == snake_body ||
	   map[snakeY[0]][snakeX[0] + 1] == wall){
		play = 0;
		return;
	} else{
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = space;
		for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1];
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = snake_body;
		snakeX[0]++;
		map[snakeY[0]][snakeX[0]] = snake_head;
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
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = space;
		for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1];
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = snake_body;
		snakeY[0]++;
		map[snakeY[0]][snakeX[0]] = snake_head;
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
			map[snakeY[snakeLength - 1]][snakeX[snakeLength - 1]] = space;
		for(i = snakeLength - 1; i > 0; i--){
			snakeX[i] = snakeX[i - 1];
			snakeY[i] = snakeY[i - 1];
		}
		map[snakeY[0]][snakeX[0]] = snake_body;
		snakeY[0]--;
		map[snakeY[0]][snakeX[0]] = snake_head;
	}
	output();
}
