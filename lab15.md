# 智能蛇学习心得
## VT100控制码
   VT100是一个终端类型定义,VT100控制码是用来在终端扩展显示的代码.比如在终端上任意坐标用不同的颜色显示字符.所有的控制符是'\033'(033是八进制的数,十进制对应的是27,即ESC的ASCII码,如果需要查看,可以使用shell命令:man ascii)开头.用输出字符语句来输出,在C程序中用printf来输出VT100的控制字符.
通过sin——demo的学习，我对VT100有了初步了解，但还有一些问题没有解决。这里就不放出sindemo代码。
## 实现 kbhit()
```
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#define space ' '
#define wall '*'
#define max 20
#define snake_head 'H'
#define snake_body 'X'
#define food '$'
static struct termios ori_attr, cur_attr;

static __inline 
int tty_reset(void)
{
        if (tcsetattr(STDIN_FILENO, TCSANOW, &ori_attr) != 0)
                return -1;

        return 0;
}


static __inline
int tty_set(void)
{
        
        if ( tcgetattr(STDIN_FILENO, &ori_attr) )
                return -1;
        
        memcpy(&cur_attr, &ori_attr, sizeof(cur_attr) );
        cur_attr.c_lflag &= ~ICANON;
//        cur_attr.c_lflag |= ECHO;
        cur_attr.c_lflag &= ~ECHO;
        cur_attr.c_cc[VMIN] = 1;
        cur_attr.c_cc[VTIME] = 0;

        if (tcsetattr(STDIN_FILENO, TCSANOW, &cur_attr) != 0)
                return -1;

        return 0;
}

static __inline
int kbhit(void) 
{
                   
        fd_set rfds;
        struct timeval tv;
        int retval;

        /* Watch stdin (fd 0) to see when it has input. */
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        /* Wait up to five seconds. */
        tv.tv_sec  = 0;
        tv.tv_usec = 0;

        retval = select(1, &rfds, NULL, NULL, &tv);
        /* Don't rely on the value of tv now! */

        if (retval == -1) {
                perror("select()");
                return 0;
        } else if (retval)
                return 1;
        /* FD_ISSET(0, &rfds) will be true. */
        else
                return 0;
        return 0;
}

//将你的 snake 代码放在这里
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
int main()
{
        //设置终端进入非缓冲状态
        int tty_set_flag;
        tty_set_flag = tty_set();
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
        //将你的 snake 代码放在这里
        printf("pressed `q` to quit!\n");
        while(1) {

                if( kbhit() ) {
                        const int key = getchar();
                        printf("%c pressed\n", key);
                        if(key == 'q')
                                break;
                } else {
                       ;// fprintf(stderr, "<no key detected>\n");
                }
        }

        //恢复终端设置
        if(tty_set_flag == 0) 
                tty_reset();
        return 0;
}
```

通过该函数，无需弹出输入的字符即可实现移动等操作。

##编写智能算法
伪代码
```
 // Hx,Hy: 头的位置
    // Fx,Fy：食物的位置
	function whereGoNext(Hx,Hy,Fx,Fy) {
	// 用数组movable[3]={“a”,”d”,”w”,”s”} 记录可走的方向
	// 用数组distance[3]={0,0,0,0} 记录离食物的距离
	// 分别计算蛇头周边四个位置到食物的距离。H头的位置，F食物位置
	//     例如：假设输入”a” 则distance[0] = |Fx – (Hx-1)| + |Fy – Hy|
	//           如果 Hx-1，Hy 位置不是Blank，则 distance[0] = 9999
	// 选择distance中存最小距离的下标p，注意最小距离不能是9999
	// 返回 movable[p]
	}
    下面是我在他人帮助下和自己已学知识勉勉强强写出来的代码
    ```
    int whereToGoNext(int hx,int hy,int fx,int fy,int diretion) {
	int i=0,min,p=0;
	int movable[4] = {'a','w','s','d'};
	int distance[4] = {0,0,0,0};
	
	for(i=0;i<4;i++) {
		switch(i) {
			case 0:
				if(map[hy][hx-1] != BLANK_CELL && map[hy][hx-1] != SNAKE_FOOD) {
					distance[i]=9999;
				}
				else {
					distance[i]=abs(fx-(hx-1))+abs(fy-hy);
				}
				break;
			case 1:
				if(map[hy-1][hx] != BLANK_CELL && map[hy-1][hx] != SNAKE_FOOD) {
					distance[i]=9999;
				}
				else {
					distance[i]=abs(fx-hx)+abs(fy-(hy-1));
				}
				break;
			case 2:
				if(map[hy+1][hx] != BLANK_CELL && map[hy+1][hx] != SNAKE_FOOD) {
					distance[i]=9999;
				}
				else {
					distance[i]=abs(fx-hx)+abs(fy-(hy+1));
				}
				break;
			case 3:
				if(map[hy][hx+1] != BLANK_CELL && map[hy][hx+1] != SNAKE_FOOD) {
					distance[i]=9999;
				}
				else {
					distance[i]=abs(fx-(hx+1))+abs(fy-hy);
				}
				break;
		}
	}
	
	min=distance[0];
	for(i=1;i<4;i++) {
		if(min>distance[i]) {
			min=distance[i];
			if(min != 9999) {
				p=i;
			}
		}
	}
	
	if(min != 9999) {
		return movable[p];
	}
	else {
		return diretion;
	}
}
```
如果想困住智能蛇，可以设计一个“|___|"形状的障碍。
## 小结
尽管自己写出来的智能蛇更像是“智障蛇”，但也毕竟是学习路上的一次伟大尝试。这次智能蛇学习最成功的地方是理解了kbhit()的实现方式。
希望以后能学习的更加深入，让智能蛇更加智能。
