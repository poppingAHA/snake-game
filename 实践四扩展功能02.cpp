#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h> 
#define High 20  //��Ϸ����ߴ� 
#define Width 30
int canvas[High][Width] = {0};
int food_x,food_y;//ʳ�� 
int extraLife_x,extraLife_y;//��������
int life=1;//С�ߵ����� 
int snakeLong=5;//С�ߵĳ��� 
int slowDown_x,slowDown_y;//���ٵ��� 
int slow=0;//�ж��Ƿ�Ե����ٵ���,0Ϊ��1Ϊ�� 
int moveDirection=4;//С���ƶ������������ҷֱ���1��2��3��4��ʾ
int score=0;//��Ϸ�÷� 
void gotoxy(int x,int y){//����ƶ�����x,y��λ�� 
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(handle,pos); 
}
void startup(){//���ݳ�ʼ�� 
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
void show(){//��ʾ����
	int i,j; 
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
void moveSnakeByDirection(){ //�ƶ�С�� 
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
		life+=2;
//		printf("\nlife:%d\n",life);
		score+=20;
	}else if(canvas[newHead_i][newHead_j]==-4){//�Ե����ٵ���
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
void updateWithoutInput(){ //���û������޹صĸ��� 
	moveSnakeByDirection();
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
//void updateWithInput2(){ //���û������йصĸ��� 
//	char input;
//	if(kbhit()){//�ж��Ƿ������� 
//		input=getch();
//	}
//	//����input��ֵ 
//	//�ı�moveDirection��ֵ����С���ƶ�λ��
//	//����moveSnakeByDirectionʵ���ƶ� 
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
	printf("\n\t̰����С��Ϸ\n");
	printf("\n��Ϸ��ʼ���밴���������ⷽ���������С�߷���\n");
	printf("\n1.����ģʽ 2.˫��ģʽ\n");
	printf("\n��ѡ��\n");
	scanf("%d",&number);
	system("cls");
	startup();//���ݳ�ʼ��
	while(1){
		if(number==1){
			if(slow==0){
				Sleep(150);
			}else if(slow==1){
				Sleep(250);
			}
			show();//��ʾ����
			updateWithoutInput();//���û������޹صĸ���
			updateWithInput();//���û������йصĸ��� 
//			printf("\nmainlife:%d\n",life);
		}else if(number==2){
			Sleep(150);
//			show2();//˫��ģʽ����
			updateWithoutInput();//���û������޹صĸ���
//			updateWithInput2();//���û������йصĸ��� 
		}	
	} 
	return 0;
}
