#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h> 
#define High 20  //���˰滭��ߴ� 
#define Width 30
#define High2 25 //˫�˰滭��ߴ�
#define Width2 60 
int canvas[High][Width] = {0};//����ģʽ 
int canvas2[High2][Width2]={0};//˫��ģʽ 
int food_x,food_y;//ʳ�� 
int extraLife_x,extraLife_y;//��������
int life=1;//С��1������
int life2=1;//С��2������ 
int snakeLong=5;//С��1�ĳ���
int snakeLong2=5;//С��2�ĳ��� 
int slowDown_x,slowDown_y;//���ٵ��� 
int slow=0;//�ж��Ƿ�Ե����ٵ���,0Ϊ��1Ϊ�� 
int moveDirection=4;//С���ƶ������������ҷֱ���1��2��3��4��ʾ
int moveDirection1=3;//С��1�ƶ������������ҷֱ���1��2��3��4��ʾ 
int moveDirection2=4;//С��2�ƶ������������ҷֱ���1��2��3��4��ʾ 
int score=0;//С��1��Ϸ�÷�
int score2=0;//С��2��Ϸ�÷� 
void gotoxy(int x,int y){//����ƶ�����x,y��λ�� 
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(handle,pos); 
}
void startup(){//���ݳ�ʼ�� 
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
	//ֵΪ0����ո�
	//ֵΪ-1����߿�#
	canvas[High/2][Width/2]=1;//��ʼ����ͷλ��
	for(i=1;i<=4;i++){	//��ʼ������������Ԫ��ֵ�ֱ�Ϊ2��3��4��5... 
		canvas[High/2][Width/2-i]=i+1;
	} 
	//��ʼ��ʳ��λ�� 
	food_x=rand()%(High-5)+2;
	food_y=rand()%(Width-5)+2;
	canvas[food_x][food_y]=-2;
	//��ʼ����������
	extraLife_x=rand()%(High-5)+3;
	extraLife_y=rand()%(Width-5)+3;
	//��ʼ�����ٵ���
	slowDown_x=rand()%(High-5)+4;
	slowDown_y=rand()%(Width-5)+4; 
}
void startup2(){//˫�˰����ݳ�ʼ�� 
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
	//ֵΪ0����ո�
	//ֵΪ-1����߿�#
	canvas2[High2 /2][Width2 /3*2]=1;//��ʼ��С��1��ͷλ��
	for(i=1;i<=4;i++){	//��ʼ������������Ԫ��ֵ�ֱ�Ϊ2��3��4��5... 
		canvas2[High2 /2][Width2 /3*2+i]=i+1;
	} 
	canvas2[High2 /2][Width2 /3]=-5;//��ʼ��С��2��ͷλ��
	for(i=1;i<=4;i++){ //��ʼ������������Ԫ��ֵ�ֱ�Ϊ-6��-7��-8��-9... 
		canvas2[High2 /2][Width2 /3-i]=canvas2[High2 /2][Width2 /3]-1;
	} 
	//��ʼ��ʳ��λ�� 
	food_x=rand()%(High2-5)+2;
	food_y=rand()%(Width2-5)+2;
	canvas2[food_x][food_y]=-2;
	//��ʼ����������
	extraLife_x=rand()%(High2-5)+3;
	extraLife_y=rand()%(Width2-5)+3;
	//��ʼ�����ٵ���
	slowDown_x=rand()%(High2-5)+4;
	slowDown_y=rand()%(Width2-5)+4; 
}
void show(){//���˰���ʾ����
	int i,j; 
	if(slow==0){
		Sleep(150);
	}else if(slow==1){
		Sleep(250);
	}
	gotoxy(0,0);//����ƶ���ԭ��λ�ã������ػ�����
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
void show2(){//˫�˰���ʾ����
	int i,j; 
	if(slow==0){
		Sleep(150);
	}else if(slow==1){
		Sleep(250);
	}
	gotoxy(0,0);//����ƶ���ԭ��λ�ã������ػ�����
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
void moveSnakeByDirection(){ //���˰��ƶ�С�� 
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
			}//ɨ������canvas����Ԫ�أ��ҵ�����Ԫ�ض�+1
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
	canvas[oldTail_i][oldTail_j]=0;//�ҵ����Ԫ�أ�����β�ͣ��������Ϊ0
	for(i=0;i<High;i++){
		for(j=0;j<Width;j++){
			if(canvas[i][j]==2){ //�ҵ���ͷ 
				oldHead_i=i;
				oldHead_j=j;
			}
		}
	}	
	//����������������ҷ��򣬰Ѷ�Ӧ����һ������ֵ��Ϊ1������ͷ��
	if(moveDirection==1){//�����ƶ�
		newHead_i=oldHead_i-1;
		newHead_j=oldHead_j; 
	}else if(moveDirection==2){//�����ƶ�
		newHead_i=oldHead_i+1;
		newHead_j=oldHead_j;
	}else if(moveDirection==3){//�����ƶ�
		newHead_i=oldHead_i;
		newHead_j=oldHead_j-1;
	}else if(moveDirection==4){//�����ƶ� 
		newHead_i=oldHead_i;
		newHead_j=oldHead_j+1;
	}			
	if(canvas[newHead_i][newHead_j]==-2){ //����ͷ�Ե�ʳ�� 
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
	}else if(canvas[newHead_i][newHead_j]==-3){//�Ե��������� 
		canvas[extraLife_x][extraLife_y]=0;
		extraLife_x=rand()%(High-5)+3;
		extraLife_y=rand()%(Width-5)+3;
		canvas[extraLife_x][extraLife_y]=-3;
		canvas[newHead_i][newHead_j]=0;
		life++;
		slow=0;
		score+=5;
	}else if(canvas[newHead_i][newHead_j]==-4){//�Ե����ٵ���
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
void moveSnakeByDirection1(){ //˫�˰��ƶ�С��1
	int i,j;
	int oldHead_i,oldHead_j;
	int newHead_i,newHead_j;
	int max=0;
	int oldTail_i,oldTail_j;
	int newLife_i,newLife_j;
	for(i=0;i<High2;i++){
		for(j=0;j<Width2;j++){
			if(canvas2[i][j]>0){ //ɨ������canvas2����Ԫ�أ��ҵ�����Ԫ�ض�+1
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
	canvas2[oldTail_i][oldTail_j]=0;//�ҵ����Ԫ�أ�����β�ͣ��������Ϊ0
	for(i=0;i<High2;i++){
		for(j=0;j<Width2;j++){
			if(canvas2[i][j]==2){ //�ҵ���ͷ 
				oldHead_i=i;
				oldHead_j=j;
			}
		}
	}	
	//����������������ҷ��򣬰Ѷ�Ӧ����һ������ֵ��Ϊ1������ͷ��
	if(moveDirection1==1){//�����ƶ�
		newHead_i=oldHead_i-1;
		newHead_j=oldHead_j; 
	}else if(moveDirection1==2){//�����ƶ�
		newHead_i=oldHead_i+1;
		newHead_j=oldHead_j;
	}else if(moveDirection1==3){//�����ƶ�
		newHead_i=oldHead_i;
		newHead_j=oldHead_j-1;
	}else if(moveDirection1==4){//�����ƶ� 
		newHead_i=oldHead_i;
		newHead_j=oldHead_j+1;
	}			
	if(canvas2[newHead_i][newHead_j]==-2){ //����ͷ�Ե�ʳ�� 
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
	}else if(canvas2[newHead_i][newHead_j]==-3){//�Ե��������� 
		canvas2[extraLife_x][extraLife_y]=0;
		extraLife_x=rand()%(High2-5)+3;
		extraLife_y=rand()%(Width2-5)+3;
		canvas2[extraLife_x][extraLife_y]=-3;
		canvas2[newHead_i][newHead_j]=0;
		life++;
		slow=0;
		score+=5;
	}else if(canvas2[newHead_i][newHead_j]==-4){//�Ե����ٵ���
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
void moveSnakeByDirection2(){ //˫�˰��ƶ�С��2 
	int i,j;
	int oldHead_i,oldHead_j;
	int newHead_i,newHead_j;
	int min=-5;
	int oldTail_i,oldTail_j;
	int newLife_i,newLife_j;
	for(i=0;i<High2;i++){
		for(j=0;j<Width2;j++){
			if(canvas2[i][j]<=-5){ //ɨ������canvas����Ԫ�أ��ҵ�С�ڵ���-5��Ԫ�ض�-1
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
	canvas2[oldTail_i][oldTail_j]=0;//�ҵ���СԪ�أ�����β�ͣ��������Ϊ0
	for(i=0;i<High2;i++){
		for(j=0;j<Width2;j++){
			if(canvas2[i][j]==-6){ //�ҵ���ͷ 
				oldHead_i=i;
				oldHead_j=j;
			}
		}
	}	
	//����������������ҷ��򣬰Ѷ�Ӧ����һ������ֵ��Ϊ1������ͷ��
	if(moveDirection2==1){//�����ƶ�
		newHead_i=oldHead_i-1;
		newHead_j=oldHead_j; 
	}else if(moveDirection2==2){//�����ƶ�
		newHead_i=oldHead_i+1;
		newHead_j=oldHead_j;
	}else if(moveDirection2==3){//�����ƶ�
		newHead_i=oldHead_i;
		newHead_j=oldHead_j-1;
	}else if(moveDirection2==4){//�����ƶ� 
		newHead_i=oldHead_i;
		newHead_j=oldHead_j+1;
	}			
	if(canvas2[newHead_i][newHead_j]==-2){ //����ͷ�Ե�ʳ�� 
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
	}else if(canvas2[newHead_i][newHead_j]==-3){//�Ե��������� 
		canvas2[extraLife_x][extraLife_y]=0;
		extraLife_x=rand()%(High2-5)+3;
		extraLife_y=rand()%(Width2-5)+3;
		canvas2[extraLife_x][extraLife_y]=-3;
		canvas2[newHead_i][newHead_j]=0;
		life2++;
		slow=0;
		score2+=5;
	}else if(canvas2[newHead_i][newHead_j]==-4){//�Ե����ٵ���
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
void updateWithoutInput(){ //���û������޹صĸ��� (���˰棩 
	moveSnakeByDirection();
}
void updateWithoutInput2(){ //���û������޹صĸ��� ��˫�˰棩 
	moveSnakeByDirection1();//С��1 
	moveSnakeByDirection2();//С��2 
}
void updateWithInput(){ //���û������йصĸ��� 
	char input;
	if(kbhit()){//�ж��Ƿ������� 
		input=getch();
	}
	//����input��ֵ 
	//�ı�moveDirection��ֵ����С���ƶ�λ��
	//����moveSnakeByDirectionʵ���ƶ� 
	switch(input){
		case 72://�� 
			moveDirection=1;
			moveSnakeByDirection();
			break;
		case 80://�� 
			moveDirection=2;
			moveSnakeByDirection();
			break;
		case 75://�� 
			moveDirection=3;
			moveSnakeByDirection();
			break;
		case 77://�� 
			moveDirection=4;
			moveSnakeByDirection();
			break;
	}
}
void updateWithInput1(){ //���û������йصĸ��� ��С��1�� 
	char input;
	if(kbhit()){//�ж��Ƿ������� 
		input=getch();
	}
	//����input��ֵ 
	//�ı�moveDirection��ֵ����С���ƶ�λ��
	//����moveSnakeByDirectionʵ���ƶ� 
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
void updateWithInput2(){ //���û������йصĸ��� ��С��2�� 
	char input;
	if(kbhit()){//�ж��Ƿ������� 
		input=getch();
	}
	//����input��ֵ 
	//�ı�moveDirection��ֵ����С���ƶ�λ��
	//����moveSnakeByDirectionʵ���ƶ� 
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
	printf("\n\t̰����С��Ϸ\n");
	printf("\n1.����ģʽ 2.˫��ģʽ 3.��Ϸ����\n");
	printf("\n��ѡ��\n");
	scanf("%d",&number);
	system("cls");	
	if(number==3){
		printf("\n��F��Ϊʳ���L��Ϊ����ҩ�������ú�ɻ��һ�������Ļ��᣻��S��Ϊ����ҩ�������ú�С���ٶȼ�����\n");
		printf("\n����ģʽ����Ϸ��ʼ���밴���������ⷽ���������С�߷���\n");
		printf("\n˫��ģʽ����Ϸ��ʼ�����һ�밴�����ϡ�i������k������j������l�������ֱ�����ұ�С��1���ϡ��¡����ҷ���\n");
		printf("\n\t\t��Ҷ��밴�����ϡ�w������s������a������d�������ֱ�������С��2�ϡ��¡����ҷ���\n");
		printf("\n�밴0ѡ����Ϸģʽ\n");
		scanf("%d",&number);
		system("cls");
		if(number==0){
			printf("\n\t̰����С��Ϸ\n");
			printf("\n1.����ģʽ 2.˫��ģʽ\n");
			printf("\n��ѡ��\n");
			scanf("%d",&number);
			system("cls");
			if(number==1){
				startup();
			}else if(number==2){
				startup2();
			}
		}
	}else if(number==1){
		startup();//���ݳ�ʼ��
	}else if(number==2){
		startup2();//˫�˰����ݳ�ʼ��
	}		
	while(1){
		if(number==1){
			show();//��ʾ����
			updateWithoutInput();//���û������޹صĸ���
			updateWithInput();//���û������йصĸ��� 
		}else if(number==2){
			show2();//˫��ģʽ����
			updateWithoutInput2();//���û������޹صĸ���
			updateWithInput1();//���û������йصĸ��� ��С��1�� 
			updateWithInput2();//���û������йصĸ��� ��С��2�� 
		}	
	} 
	return 0;
}
