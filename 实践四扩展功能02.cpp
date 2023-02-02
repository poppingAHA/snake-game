#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h> 
#define High 20  //游戏画面尺寸 
#define Width 30
int canvas[High][Width] = {0};
int food_x,food_y;//食物 
int extraLife_x,extraLife_y;//加命道具
int life=1;//小蛇的生命 
int snakeLong=5;//小蛇的长度 
int slowDown_x,slowDown_y;//减速道具 
int slow=0;//判断是否吃到减速道具,0为否，1为是 
int moveDirection=4;//小蛇移动方向，上下左右分别用1，2，3，4表示
int score=0;//游戏得分 
void gotoxy(int x,int y){//光标移动到（x,y）位置 
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(handle,pos); 
}
void startup(){//数据初始化 
	int i,j;
	int max=0;
	srand(time(0));
	for(i=0;i<High;i++){
		canvas[i][0]=-1;
		canvas[i][Width-1]=-1;
	}
	for(j=0;j<Width;j++){
		canvas[0][j]=-1;
		canvas[High-1][j]=-1;
	}
	//值为0输出空格
	//值为-1输出边框#
	canvas[High/2][Width/2]=1;//初始化蛇头位置
	for(i=1;i<=4;i++){	//初始化蛇身，画布中元素值分别为2，3，4，5... 
		canvas[High/2][Width/2-i]=i+1;
	} 
	//初始化食物位置 
	food_x=rand()%(High-5)+2;
	food_y=rand()%(Width-5)+2;
	canvas[food_x][food_y]=-2;
	//初始化加命道具
	extraLife_x=rand()%(High-5)+3;
	extraLife_y=rand()%(Width-5)+3;
	//初始化减速道具
	slowDown_x=rand()%(High-5)+4;
	slowDown_y=rand()%(Width-5)+4; 
}
void show(){//显示画面
	int i,j; 
	gotoxy(0,0);//光标移动到原点位置，以下重画清屏
	if(snakeLong>=6){
		for(i=0;i<High;i++){
			for(j=0;j<Width;j++){
				if(canvas[i][j]!=-3&&life==1){
					canvas[extraLife_x][extraLife_y]=-3;
				}else if(life>1){
					if(canvas[extraLife_x][extraLife_y]<0)
						canvas[extraLife_x][extraLife_y]=0;
				}
			}
		}	
	} 
	if(snakeLong>=7){
		for(i=0;i<High;i++){
			for(j=0;j<Width;j++){
				if(canvas[i][j]!=-4&&slow==0){
					canvas[slowDown_x][slowDown_y]=-4;
				}else if(slow==1){
					if(canvas[slowDown_x][slowDown_y]<0)
						canvas[slowDown_x][slowDown_y]=0;
				}
			}
		}	
	} 
	for(i=0;i<High;i++){
		for(j=0;j<Width;j++){
			if(canvas[i][j]==0){
				printf(" ");
			}else if(canvas[i][j]==-1){
				printf("#");
			}else if(canvas[i][j]==-2){
				printf("F");
			}else if(canvas[i][j]==1){
				printf("@");
			}else if(canvas[i][j]>1){
				printf("*");
			}else if(canvas[i][j]==-3){
				printf("L");
			}else if(canvas[i][j]==-4){
				printf("S");
			}
		}
		printf("\n");
	} 
}
void moveSnakeByDirection(){ //移动小蛇 
	int i,j;
	int oldHead_i,oldHead_j;
	int newHead_i,newHead_j;
	int max=0;
	int oldTail_i,oldTail_j;
	int newLife_i,newLife_j;
	for(i=0;i<High;i++){
		for(j=0;j<Width;j++){
			if(canvas[i][j]>0){ 
				canvas[i][j]++; 
			}//扫描数组canvas所有元素，找到正数元素都+1
		}
	}
	for(i=0;i<High;i++){
		for(j=0;j<Width;j++){
			if(max<canvas[i][j]){
				max=canvas[i][j];
				oldTail_i=i;
				oldTail_j=j;
			} 
		}
	}
	canvas[oldTail_i][oldTail_j]=0;//找到最大元素（即蛇尾巴），把其变为0
	for(i=0;i<High;i++){
		for(j=0;j<Width;j++){
			if(canvas[i][j]==2){ //找到蛇头 
				oldHead_i=i;
				oldHead_j=j;
			}
		}
	}
	
	//根据输出的上下左右方向，把对应的另一个像素值设为1（新蛇头）
	if(moveDirection==1){//向上移动
		newHead_i=oldHead_i-1;
		newHead_j=oldHead_j; 
	}else if(moveDirection==2){//向下移动
		newHead_i=oldHead_i+1;
		newHead_j=oldHead_j;
	}else if(moveDirection==3){//向左移动
		newHead_i=oldHead_i;
		newHead_j=oldHead_j-1;
	}else if(moveDirection==4){//向右移动 
		newHead_i=oldHead_i;
		newHead_j=oldHead_j+1;
	}	
	
	
	if(canvas[newHead_i][newHead_j]==-2){ //新蛇头吃到食物 
		canvas[food_x][food_y]=0;
		food_x=rand()%(High-5)+2;
		food_y=rand()%(Width-5)+2;
		canvas[food_x][food_y]=-2;
		canvas[newHead_i][newHead_j]=0;
		for(i=0;i<High;i++){
			for(j=0;j<Width;j++){
				if(max<canvas[i][j]){
					max=canvas[i][j];
					oldTail_i=i;
					oldTail_j=j;
				} 
			}
		}
		canvas[oldTail_i][oldTail_j]=max;
		snakeLong=max; 
		slow=0;
		score+=10;
	}else if(canvas[newHead_i][newHead_j]==-3){//吃到加命道具 
		canvas[extraLife_x][extraLife_y]=0;
		extraLife_x=rand()%(High-5)+3;
		extraLife_y=rand()%(Width-5)+3;
		canvas[extraLife_x][extraLife_y]=-3;
		canvas[newHead_i][newHead_j]=0;
		life+=2;
//		printf("\nlife:%d\n",life);
		score+=20;
	}else if(canvas[newHead_i][newHead_j]==-4){//吃到减速道具
		canvas[slowDown_x][slowDown_y]=0;
		slowDown_x=rand()%(High-5)+4;
		slowDown_y=rand()%(Width-5)+4; 
		canvas[slowDown_x][slowDown_y]=-4;
		canvas[newHead_i][newHead_j]=0;
		slow=1; 
		score+=5;
	}
	
	if(canvas[newHead_i][newHead_j]>0||canvas[newHead_i][newHead_j]==-1){
		life--;
//		printf("\nlife:%d\n",life);
	}
	
	
	if(life==0){
		printf("\n\tGame over!\n");
		printf("\n\tYour score is:%d\n",score);
		Sleep(1000);
		system("pause");
		exit(0);
	}
	else if(life>0){
//		printf("\n\tcontinue!\n");
		for(i=0;i<High;i++){
			if(canvas[i][0]!=-1 || canvas[i][Width-1]!=-1){
				canvas[i][0]=-1;
				canvas[i][Width-1]=-1;
			}		
		}		
		for(j=0;j<Width;j++){
			if(canvas[0][j]!=-1 || canvas[High-1][j]!=-1){
				canvas[0][j]=-1;
				canvas[High-1][j]=-1;
			}	
		}
	}
	canvas[newHead_i][newHead_j]=1;	
	
} 
void updateWithoutInput(){ //与用户输入无关的更新 
	moveSnakeByDirection();
}
void updateWithInput(){ //与用户输入有关的更新 
	char input;
	if(kbhit()){//判断是否有输入 
		input=getch();
	}
	//根据input的值 
	//改变moveDirection的值控制小蛇移动位置
	//调用moveSnakeByDirection实现移动 
	switch(input){
		case 72:
			moveDirection=1;
			moveSnakeByDirection();
			break;
		case 80:
			moveDirection=2;
			moveSnakeByDirection();
			break;
		case 75:
			moveDirection=3;
			moveSnakeByDirection();
			break;
		case 77:
			moveDirection=4;
			moveSnakeByDirection();
			break;
	}
}
//void updateWithInput2(){ //与用户输入有关的更新 
//	char input;
//	if(kbhit()){//判断是否有输入 
//		input=getch();
//	}
//	//根据input的值 
//	//改变moveDirection的值控制小蛇移动位置
//	//调用moveSnakeByDirection实现移动 
//	switch(input){
//		case 72:
//			moveDirection=1;
//			moveSnakeByDirection();
//			break;
//		case 80:
//			moveDirection=2;
//			moveSnakeByDirection();
//			break;
//		case 75:
//			moveDirection=3;
//			moveSnakeByDirection();
//			break;
//		case 77:
//			moveDirection=4;
//			moveSnakeByDirection();
//			break;
//	}
//}
 
int main(){
	int number;
	printf("\n\t贪吃蛇小游戏\n");
	printf("\n游戏开始后，请按键盘上任意方向键，控制小蛇方向\n");
	printf("\n1.单人模式 2.双人模式\n");
	printf("\n请选择：\n");
	scanf("%d",&number);
	system("cls");
	startup();//数据初始化
	while(1){
		if(number==1){
			if(slow==0){
				Sleep(150);
			}else if(slow==1){
				Sleep(250);
			}
			show();//显示画面
			updateWithoutInput();//与用户输入无关的更新
			updateWithInput();//与用户输入有关的更新 
//			printf("\nmainlife:%d\n",life);
		}else if(number==2){
			Sleep(150);
//			show2();//双人模式画面
			updateWithoutInput();//与用户输入无关的更新
//			updateWithInput2();//与用户输入有关的更新 
		}	
	} 
	return 0;
}
