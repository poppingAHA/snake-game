#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h> 
#define High 20  //单人版画面尺寸 
#define Width 30
#define High2 25 //双人版画面尺寸
#define Width2 60 
int canvas[High][Width] = {0};//单人模式 
int canvas2[High2][Width2]={0};//双人模式 
int food_x,food_y;//食物 
int extraLife_x,extraLife_y;//加命道具
int life=1;//小蛇1的生命
int life2=1;//小蛇2的生命 
int snakeLong=5;//小蛇1的长度
int snakeLong2=5;//小蛇2的长度 
int slowDown_x,slowDown_y;//减速道具 
int slow=0;//判断是否吃到减速道具,0为否，1为是 
int moveDirection=4;//小蛇移动方向，上下左右分别用1，2，3，4表示
int moveDirection1=3;//小蛇1移动方向，上下左右分别用1，2，3，4表示 
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
void startup2(){//双人版数据初始化 
	int i,j;
	srand(time(0));
	for(i=0;i<High2;i++){
		canvas2[i][0]=-1;
		canvas2[i][Width2 -1]=-1;
	}
	for(j=0;j<Width2;j++){
		canvas2[0][j]=-1;
		canvas2[High2 -1][j]=-1;
	}
	//值为0输出空格
	//值为-1输出边框#
	canvas2[High2 /2][Width2 /3*2]=1;//初始化小蛇1蛇头位置
	for(i=1;i<=4;i++){	//初始化蛇身，画布中元素值分别为2，3，4，5... 
		canvas2[High2 /2][Width2 /3*2+i]=i+1;
	} 
	canvas2[High2 /2][Width2 /3]=-5;//初始化小蛇2蛇头位置
	for(i=1;i<=4;i++){ //初始化蛇身，画布中元素值分别为-6，-7，-8，-9... 
		canvas2[High2 /2][Width2 /3-i]=canvas2[High2 /2][Width2 /3]-1;
	} 
	//初始化食物位置 
	food_x=rand()%(High2-5)+2;
	food_y=rand()%(Width2-5)+2;
	canvas2[food_x][food_y]=-2;
	//初始化加命道具
	extraLife_x=rand()%(High2-5)+3;
	extraLife_y=rand()%(Width2-5)+3;
	//初始化减速道具
	slowDown_x=rand()%(High2-5)+4;
	slowDown_y=rand()%(Width2-5)+4; 
}
void show(){//单人版显示画面
	int i,j; 
	if(slow==0){
		Sleep(150);
	}else if(slow==1){
		Sleep(250);
	}
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
void show2(){//双人版显示画面
	int i,j; 
	if(slow==0){
		Sleep(150);
	}else if(slow==1){
		Sleep(250);
	}
	gotoxy(0,0);//光标移动到原点位置，以下重画清屏
	if(snakeLong>=6 || snakeLong2>=6){
		for(i=0;i<High2;i++){
			for(j=0;j<Width2;j++){
				if(canvas2[i][j]!=-3&&life==1&&life2==1){
					canvas2[extraLife_x][extraLife_y]=-3;
				}else if(life>1||life2>1){
					if(canvas2[extraLife_x][extraLife_y]<0)
						canvas2[extraLife_x][extraLife_y]=0;
				}
			}
		}	
	}
	if(snakeLong>=7 || snakeLong2>=7){
		for(i=0;i<High2;i++){
			for(j=0;j<Width2;j++){
				if(canvas2[i][j]!=-4&&slow==0){
					canvas2[slowDown_x][slowDown_y]=-4;
				}else if(slow==1){
					if(canvas2[slowDown_x][slowDown_y]<0)
						canvas2[slowDown_x][slowDown_y]=0;
				}
			}
		}	
	}
	for(i=0;i<High2;i++){
		for(j=0;j<Width2;j++){
			if(canvas2[i][j]==0){
				printf(" ");
			}else if(canvas2[i][j]==-1){
				printf("#");
			}else if(canvas2[i][j]==-2){
				printf("F");
			}else if(canvas2[i][j]==1){
				printf("@");
			}else if(canvas2[i][j]>1){
				printf("*");
			}else if(canvas2[i][j]==-3){
				printf("L");
			}else if(canvas2[i][j]==-4){
				printf("S");
			}else if(canvas2[i][j]==-5){
				printf("&");
			}else if(canvas2[i][j]<-5){
				printf("+");
			}
		}
		printf("\n");
	} 
}
void moveSnakeByDirection(){ //单人版移动小蛇 
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
		life++;
		slow=0;
		score+=5;
	}else if(canvas[newHead_i][newHead_j]==-4){//吃到减速道具
		canvas[slowDown_x][slowDown_y]=0;
		slowDown_x=rand()%(High-5)+4;
		slowDown_y=rand()%(Width-5)+4; 
		canvas[slowDown_x][slowDown_y]=-4;
		canvas[newHead_i][newHead_j]=0;
		slow=1; 
		score+=5;
	}
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
	if(canvas[newHead_i][newHead_j]>0||canvas[newHead_i][newHead_j]==-1){
		life--;
		if(life==0){
			printf("\n\tGame over!\n");
			printf("\n\tYour score is:%d\n",score);
			Sleep(1000);
			system("pause");
			exit(0);
		}
		else if(life>0){		
			canvas[newHead_i][newHead_j]=0;
			for(i=0;i<High;i++){
				for(j=0;j<Width;j++){
					if(canvas[i][j]>0){
						canvas[i][j]=0;
					}
				}
			}
			for(i=1;i<High-1;i++){
				for(j=1;j<Width-1;j++){
					if(canvas[i][j]!=1){
						canvas[High/2][Width/2]=1;
						for(int k=1;k<=4;k++){
							canvas[High/2][Width/2-k]=k+1;
						}
						moveDirection=4;
					}
				}
			}
			
		}	
	}
	canvas[newHead_i][newHead_j]=1;		
} 
void moveSnakeByDirection1(){ //双人版移动小蛇1
	int i,j;
	int oldHead_i,oldHead_j;
	int newHead_i,newHead_j;
	int max=0;
	int oldTail_i,oldTail_j;
	int newLife_i,newLife_j;
	for(i=0;i<High2;i++){
		for(j=0;j<Width2;j++){
			if(canvas2[i][j]>0){ //扫描数组canvas2所有元素，找到正数元素都+1
				canvas2[i][j]++; 
			}
		}
	}
	for(i=0;i<High2;i++){
		for(j=0;j<Width2;j++){
			if(max<canvas2[i][j]){
				max=canvas2[i][j];
				oldTail_i=i;
				oldTail_j=j;
			}
		}
	}
	canvas2[oldTail_i][oldTail_j]=0;//找到最大元素（即蛇尾巴），把其变为0
	for(i=0;i<High2;i++){
		for(j=0;j<Width2;j++){
			if(canvas2[i][j]==2){ //找到蛇头 
				oldHead_i=i;
				oldHead_j=j;
			}
		}
	}	
	//根据输出的上下左右方向，把对应的另一个像素值设为1（新蛇头）
	if(moveDirection1==1){//向上移动
		newHead_i=oldHead_i-1;
		newHead_j=oldHead_j; 
	}else if(moveDirection1==2){//向下移动
		newHead_i=oldHead_i+1;
		newHead_j=oldHead_j;
	}else if(moveDirection1==3){//向左移动
		newHead_i=oldHead_i;
		newHead_j=oldHead_j-1;
	}else if(moveDirection1==4){//向右移动 
		newHead_i=oldHead_i;
		newHead_j=oldHead_j+1;
	}			
	if(canvas2[newHead_i][newHead_j]==-2){ //新蛇头吃到食物 
		canvas2[food_x][food_y]=0;
		food_x=rand()%(High2-5)+2;
		food_y=rand()%(Width2-5)+2;
		canvas2[food_x][food_y]=-2;
		canvas2[newHead_i][newHead_j]=0;
		for(i=0;i<High2;i++){
			for(j=0;j<Width2;j++){
				if(max<canvas2[i][j]){
					max=canvas2[i][j];
					oldTail_i=i;
					oldTail_j=j;
				} 
			}
		}
		canvas2[oldTail_i][oldTail_j]=max;
		snakeLong=max; 
		slow=0;
		score+=10;
	}else if(canvas2[newHead_i][newHead_j]==-3){//吃到加命道具 
		canvas2[extraLife_x][extraLife_y]=0;
		extraLife_x=rand()%(High2-5)+3;
		extraLife_y=rand()%(Width2-5)+3;
		canvas2[extraLife_x][extraLife_y]=-3;
		canvas2[newHead_i][newHead_j]=0;
		life++;
		slow=0;
		score+=5;
	}else if(canvas2[newHead_i][newHead_j]==-4){//吃到减速道具
		canvas2[slowDown_x][slowDown_y]=0;
		slowDown_x=rand()%(High2-5)+4;
		slowDown_y=rand()%(Width2-5)+4; 
		canvas2[slowDown_x][slowDown_y]=-4;
		canvas2[newHead_i][newHead_j]=0;
		slow=1; 
		score+=5;
	}
	for(i=0;i<High2;i++){
		if(canvas2[i][0]!=-1 || canvas2[i][Width2-1]!=-1){
			canvas2[i][0]=-1;
			canvas2[i][Width2-1]=-1;
		}		
	}		
	for(j=0;j<Width2;j++){
		if(canvas2[0][j]!=-1 || canvas2[High2 -1][j]!=-1){
			canvas2[0][j]=-1;
			canvas2[High2 -1][j]=-1;
		}	
	}
	if(canvas2[newHead_i][newHead_j]>0||canvas2[newHead_i][newHead_j]==-1||canvas2[newHead_i][newHead_j]<=-5){
		life--;
		if(life==0){
			printf("\n\tGame over!\n");
			printf("\n\tSnake1's score is:%d\n",score);
			printf("\n\tSnake2's score is:%d\n",score2);
			if(life>life2){
				if(score>=score2){
					printf("\n\t\tSnake1 win!\n");	
				}else if(score<score2){
					printf("\n\t\tSnake2 win!\n");	
				}
			}else if(life<life2){
				if(score>score2){
					printf("\n\t\tSnake1 win!\n");	
				}else{
					printf("\n\t\tSnake2 win!\n");	
				}
			}
			Sleep(1000);
			system("pause");
			exit(0);
		}
		else if(life>0){		
			canvas2[newHead_i][newHead_j]=0;
			for(i=0;i<High2;i++){
				for(j=0;j<Width2;j++){
					if(canvas2[i][j]>0){
						canvas2[i][j]=0;
					}
				}
			}
			for(i=1;i<High2 -1;i++){
				for(j=1;j<Width2 -1;j++){
					if(canvas2[i][j]!=1){
						canvas2[High2 /2][Width2 /3*2]=1;
						for(int k=1;k<=4;k++){
							canvas2[High2 /2][Width2 /3*2+k]=k+1;
						}
						moveDirection1=3;
					}
				}
			}
			
		}	
	}
	canvas2[newHead_i][newHead_j]=1;		
} 
void moveSnakeByDirection2(){ //双人版移动小蛇2 
	int i,j;
	int oldHead_i,oldHead_j;
	int newHead_i,newHead_j;
	int min=-5;
	int oldTail_i,oldTail_j;
	int newLife_i,newLife_j;
	for(i=0;i<High2;i++){
		for(j=0;j<Width2;j++){
			if(canvas2[i][j]<=-5){ //扫描数组canvas所有元素，找到小于等于-5的元素都-1
				canvas2[i][j]--; 
			}
		}
	}
	for(i=0;i<High2;i++){
		for(j=0;j<Width2;j++){
			if(min>canvas2[i][j]){
				min=canvas2[i][j];
				oldTail_i=i;
				oldTail_j=j;
			}
		}
	}
	canvas2[oldTail_i][oldTail_j]=0;//找到最小元素（即蛇尾巴），把其变为0
	for(i=0;i<High2;i++){
		for(j=0;j<Width2;j++){
			if(canvas2[i][j]==-6){ //找到蛇头 
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
	if(canvas2[newHead_i][newHead_j]==-2){ //新蛇头吃到食物 
		canvas2[food_x][food_y]=0;
		food_x=rand()%(High2-5)+2;
		food_y=rand()%(Width2-5)+2;
		canvas2[food_x][food_y]=-2;
		canvas2[newHead_i][newHead_j]=0;
		for(i=0;i<High2;i++){
			for(j=0;j<Width2;j++){
				if(min>canvas2[i][j]){
					min=canvas2[i][j];
					oldTail_i=i;
					oldTail_j=j;
				} 
			}
		}
		canvas2[oldTail_i][oldTail_j]=min;
		snakeLong2++; 
		slow=0;
		score2+=10;
	}else if(canvas2[newHead_i][newHead_j]==-3){//吃到加命道具 
		canvas2[extraLife_x][extraLife_y]=0;
		extraLife_x=rand()%(High2-5)+3;
		extraLife_y=rand()%(Width2-5)+3;
		canvas2[extraLife_x][extraLife_y]=-3;
		canvas2[newHead_i][newHead_j]=0;
		life2++;
		slow=0;
		score2+=5;
	}else if(canvas2[newHead_i][newHead_j]==-4){//吃到减速道具
		canvas2[slowDown_x][slowDown_y]=0;
		slowDown_x=rand()%(High2-5)+4;
		slowDown_y=rand()%(Width2-5)+4; 
		canvas2[slowDown_x][slowDown_y]=-4;
		canvas2[newHead_i][newHead_j]=0;
		slow=1; 
		score2+=5;
	}
	for(i=0;i<High2;i++){
		if(canvas2[i][0]!=-1 || canvas2[i][Width2-1]!=-1){
			canvas2[i][0]=-1;
			canvas2[i][Width2-1]=-1;
		}		
	}		
	for(j=0;j<Width2;j++){
		if(canvas2[0][j]!=-1 || canvas2[High2 -1][j]!=-1){
			canvas2[0][j]=-1;
			canvas2[High2 -1][j]=-1;
		}	
	}
	if(canvas2[newHead_i][newHead_j]>0||canvas2[newHead_i][newHead_j]==-1||canvas2[newHead_i][newHead_j]<=-5){
		life2--;
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
		else if(life2>0){		
			canvas2[newHead_i][newHead_j]=0;
			for(i=0;i<High2;i++){
				for(j=0;j<Width2;j++){
					if(canvas2[i][j]<=-5){
						canvas2[i][j]=0;
					}
				}
			}
			for(i=1;i<High2 -1;i++){
				for(j=1;j<Width2 -1;j++){
					if(canvas2[i][j]!=-5){
						canvas2[High2 /2][Width2 /3]=-5;
						for(int k=1;k<=4;k++){
							canvas2[High2 /2][Width2 /3-k]=(-5)-k;
						}
						moveDirection2=4;
					}
				}
			}			
		}	
	}
	canvas2[newHead_i][newHead_j]=-5;		
} 
void updateWithoutInput(){ //与用户输入无关的更新 (单人版） 
	moveSnakeByDirection();
}
void updateWithoutInput2(){ //与用户输入无关的更新 （双人版） 
	moveSnakeByDirection1();//小蛇1 
	moveSnakeByDirection2();//小蛇2 
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
		case 72://上 
			moveDirection=1;
			moveSnakeByDirection();
			break;
		case 80://下 
			moveDirection=2;
			moveSnakeByDirection();
			break;
		case 75://左 
			moveDirection=3;
			moveSnakeByDirection();
			break;
		case 77://右 
			moveDirection=4;
			moveSnakeByDirection();
			break;
	}
}
void updateWithInput1(){ //与用户输入有关的更新 （小蛇1） 
	char input;
	if(kbhit()){//判断是否有输入 
		input=getch();
	}
	//根据input的值 
	//改变moveDirection的值控制小蛇移动位置
	//调用moveSnakeByDirection实现移动 
	switch(input){
		case 'i':
			moveDirection1=1;
			moveSnakeByDirection1();
			break;
		case 'k':
			moveDirection1=2;
			moveSnakeByDirection1();
			break;
		case 'j':
			moveDirection1=3;
			moveSnakeByDirection1();
			break;
		case 'l':
			moveDirection1=4;
			moveSnakeByDirection1();
			break;
	}
}
void updateWithInput2(){ //与用户输入有关的更新 （小蛇2） 
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
	printf("\n1.单人模式 2.双人模式 3.游戏规则\n");
	printf("\n请选择：\n");
	scanf("%d",&number);
	system("cls");	
	if(number==3){
		printf("\n“F”为食物；“L”为生命药剂，服用后可获得一次重生的机会；“S”为减速药剂，服用后小蛇速度减慢。\n");
		printf("\n单人模式：游戏开始后，请按键盘上任意方向键，控制小蛇方向\n");
		printf("\n双人模式：游戏开始后，玩家一请按键盘上“i”、“k”、“j”、“l”键，分别控制右边小蛇1的上、下、左、右方向\n");
		printf("\n\t\t玩家二请按键盘上“w”、“s”、“a”、“d”键，分别控制左边小蛇2上、下、左、右方向\n");
		printf("\n请按0选择游戏模式\n");
		scanf("%d",&number);
		system("cls");
		if(number==0){
			printf("\n\t贪吃蛇小游戏\n");
			printf("\n1.单人模式 2.双人模式\n");
			printf("\n请选择：\n");
			scanf("%d",&number);
			system("cls");
			if(number==1){
				startup();
			}else if(number==2){
				startup2();
			}
		}
	}else if(number==1){
		startup();//数据初始化
	}else if(number==2){
		startup2();//双人版数据初始化
	}		
	while(1){
		if(number==1){
			show();//显示画面
			updateWithoutInput();//与用户输入无关的更新
			updateWithInput();//与用户输入有关的更新 
		}else if(number==2){
			show2();//双人模式画面
			updateWithoutInput2();//与用户输入无关的更新
			updateWithInput1();//与用户输入有关的更新 （小蛇1） 
			updateWithInput2();//与用户输入有关的更新 （小蛇2） 
		}	
	} 
	return 0;
}
