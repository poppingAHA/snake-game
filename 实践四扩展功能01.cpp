#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h> 
#define High 25  //游戏画面尺寸 
#define Width 60
int canvas[High][Width] = {0};
int food_x,food_y;//食物 
int extraLife_x,extraLife_y;//加命道具
int life=1;//小蛇1
int life2=1;//小蛇2 
int slowDown_x,slowDown_y;//减速道具 
int slow=0;//判断是否吃到减速道具 
int moveDirection=3;//小蛇1移动方向，上下左右分别用1，2，3，4表示
int moveDirection2=4;//小蛇2移动方向，上下左右分别用1，2，3，4表示 
int score=0;//小蛇1游戏得分 
int score2=0;//小蛇2游戏得分 
void gotoxy(int x,int y){//光标移动到（x,y）位置 
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(handle,pos); 
}
void startup(){//数据初始化 
	int i,j;
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
	canvas[High/2][Width/3*2]=1;//初始化小蛇1蛇头位置
	for(i=1;i<=4;i++){	//初始化蛇身，画布中元素值分别为2，3，4，5... 
		canvas[High/2][Width/3*2+i]=i+1;
	} 
	canvas[High/2][Width/3]=-5;//初始化小蛇2蛇头位置
	for(i=1;i<=4;i++){ //初始化蛇身，画布中元素值分别为-6，-7，-8，-9... 
		canvas[High/2][Width/3-i]=canvas[High/2][Width/3]-1;
	} 
	//初始化食物位置 
	food_x=rand()%(High-5)+2;
	food_y=rand()%(Width-5)+2;
	canvas[food_x][food_y]=-2;
	//初始化加命道具
//	extraLife_x=rand()%(High-5)+3;
//	extraLife_y=rand()%(Width-5)+3;
//	canvas[extraLife_x][extraLife_y]=-3;
		 
	
		
}
void show(){//显示画面
	int i,j; 
	Sleep(150);
	gotoxy(0,0);//光标移动到原点位置，以下重画清屏
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
			}else if(canvas[i][j]==-5){
				printf("&");
			}else if(canvas[i][j]<-5){
				printf("+");
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
		score+=10;
	}else if(canvas[newHead_i][newHead_j]==-3){
		canvas[extraLife_x][extraLife_y]=0;
		extraLife_x=rand()%(High-5)+3;
		extraLife_y=rand()%(Width-5)+3;
		canvas[extraLife_x][extraLife_y]=-3;
		canvas[newHead_i][newHead_j]=0;
		life+=1;
		score+=20;
	}
	
	if(canvas[newHead_i][newHead_j]>0||canvas[newHead_i][newHead_j]==-1||canvas[newHead_i][newHead_j]<=-5){
		life--;
	}
	
	
	if(life==0){
		printf("\n\tGame over!\n");
		printf("\n\tSnake1's score is:%d\n",score);
		printf("\n\tSnake2's score is:%d\n",score2);
		if(life>life2){
			if(score>=score2){
				printf("\n\t\t\tSnake1 win!\n");	
			}else if(score<score2){
				printf("\n\t\t\tSnake2 win!\n");	
			}
		}else if(life<life2){
			if(score>score2){
				printf("\n\t\t\tSnake1 win!\n");	
			}else{
				printf("\n\t\t\tSnake2 win!\n");	
			}
		}
		Sleep(1000);
		system("pause");
		exit(0);
	}
	else if(life>1){
	
		
	}
	canvas[newHead_i][newHead_j]=1;	
	
} 
void moveSnakeByDirection2(){ //移动小蛇2 
	int i,j;
	int oldHead_i,oldHead_j;
	int newHead_i,newHead_j;
	int min=-5;
	int oldTail_i,oldTail_j;
	int newLife_i,newLife_j;
	for(i=0;i<High;i++){
		for(j=0;j<Width;j++){
			if(canvas[i][j]<=-5){ 
				canvas[i][j]--; 
			}//扫描数组canvas所有元素，找到小于等于-5的元素减1 
		}
	}
	for(i=0;i<High;i++){
		for(j=0;j<Width;j++){
			if(min>canvas[i][j]){
				min=canvas[i][j];
				oldTail_i=i;
				oldTail_j=j;
			} 
		}
	}
	canvas[oldTail_i][oldTail_j]=0;//找到最小元素（即蛇尾巴），把其变为0
	for(i=0;i<High;i++){
		for(j=0;j<Width;j++){
			if(canvas[i][j]==-6){ //找到蛇头 
				oldHead_i=i;
				oldHead_j=j;
			}
		}
	}
	
	//根据输出的上下左右方向，把对应的另一个像素值设为1（新蛇头）
	if(moveDirection2==1){//向上移动
		newHead_i=oldHead_i-1;
		newHead_j=oldHead_j; 
	}else if(moveDirection2==2){//向下移动
		newHead_i=oldHead_i+1;
		newHead_j=oldHead_j;
	}else if(moveDirection2==3){//向左移动
		newHead_i=oldHead_i;
		newHead_j=oldHead_j-1;
	}else if(moveDirection2==4){//向右移动 
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
				if(min>canvas[i][j]){
					min=canvas[i][j];
					oldTail_i=i;
					oldTail_j=j;
				} 
			}
		}
		canvas[oldTail_i][oldTail_j]=min;
		score2+=10;
	}else if(canvas[newHead_i][newHead_j]==-3){
//		canvas[extraLife_x][extraLife_y]=0;
//		extraLife_x=rand()%(High-5)+3;
//		extraLife_y=rand()%(Width-5)+3;
//		canvas[extraLife_x][extraLife_y]=-3;
//		canvas[newHead_i][newHead_j]=0;
//		life2+=1;
//		score2+=5;
	}
	
	if(canvas[newHead_i][newHead_j]>0||canvas[newHead_i][newHead_j]==-1||canvas[newHead_i][newHead_j]<=-5){
		life2--;
	}
	
	
	if(life2==0){
		printf("\n\tGame over!\n");
		printf("\n\tSnake1's score is:%d\n",score);
		printf("\n\tSnake2's score is:%d\n",score2);
		if(life>life2){
			if(score>=score2){
				printf("\n\t\t\tSnake1 win!\n");	
			}else if(score<score2){
				printf("\n\t\t\tSnake2 win!\n");	
			}
		}else if(life<life2){
			if(score>score2){
				printf("\n\t\t\tSnake1 win!\n");	
			}else{
				printf("\n\t\t\tSnake2 win!\n");	
			}
		}
		Sleep(1000);
		system("pause");
		exit(0);
	}
	else if(life2>1){
		
		
	}
	canvas[newHead_i][newHead_j]=-5;	
	
} 
void updateWithoutInput(){ //与用户输入无关的更新 
	moveSnakeByDirection();
	moveSnakeByDirection2();
}
void updateWithInput(){ //与用户输入有关的更新(小蛇1） 
	char input;
	if(kbhit()){//判断是否有输入 
		input=getch();
	}
	//根据input的值 
	//改变moveDirection的值控制小蛇移动位置
	//调用moveSnakeByDirection实现移动 
	switch(input){
		case 'i':
			moveDirection=1;
			moveSnakeByDirection();
			break;
		case 'k':
			moveDirection=2;
			moveSnakeByDirection();
			break;
		case 'j':
			moveDirection=3;
			moveSnakeByDirection();
			break;
		case 'l':
			moveDirection=4;
			moveSnakeByDirection();
			break;
	}
}
void updateWithInput2(){ //与用户输入有关的更新 
	char input;
	if(kbhit()){//判断是否有输入 
		input=getch();
	}
	//根据input的值 
	//改变moveDirection的值控制小蛇移动位置
	//调用moveSnakeByDirection实现移动 
	switch(input){
		case 'w':
			moveDirection2=1;
			moveSnakeByDirection2();
			break;
		case 's':
			moveDirection2=2;
			moveSnakeByDirection2();
			break;
		case 'a':
			moveDirection2=3;
			moveSnakeByDirection2();
			break;
		case 'd':
			moveDirection2=4;
			moveSnakeByDirection2();
			break;
	}
}
 
int main(){
	int number;
	printf("\n\t贪吃蛇小游戏\n");
	printf("\n游戏开始后，左边小蛇请按键盘上“w”、“s”、“a”、“d”键，控制小蛇上下左右方向\n");
	printf("\n\t右边小蛇请按键盘上“i”、“k”、“j”、“l”键，控制小蛇上下左右方向\n");
	printf("\n请按1开始游戏\n");
	scanf("%d",&number);
	system("cls");
	startup();//数据初始化
	while(1){
		if(number==1){
			show();//双人模式画面
			updateWithoutInput();//与用户输入无关的更新
			updateWithInput();//与用户输入有关的更新 
			updateWithInput2();//与用户输入有关的更新 
		}	
	} 
	return 0;
}
