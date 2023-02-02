#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h> 
#define High 25  //��Ϸ����ߴ� 
#define Width 60
int canvas[High][Width] = {0};
int food_x,food_y;//ʳ�� 
int extraLife_x,extraLife_y;//��������
int life=1;//С��1
int life2=1;//С��2 
int slowDown_x,slowDown_y;//���ٵ��� 
int slow=0;//�ж��Ƿ�Ե����ٵ��� 
int moveDirection=3;//С��1�ƶ������������ҷֱ���1��2��3��4��ʾ
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
	canvas[High/2][Width/3*2]=1;//��ʼ��С��1��ͷλ��
	for(i=1;i<=4;i++){	//��ʼ������������Ԫ��ֵ�ֱ�Ϊ2��3��4��5... 
		canvas[High/2][Width/3*2+i]=i+1;
	} 
	canvas[High/2][Width/3]=-5;//��ʼ��С��2��ͷλ��
	for(i=1;i<=4;i++){ //��ʼ������������Ԫ��ֵ�ֱ�Ϊ-6��-7��-8��-9... 
		canvas[High/2][Width/3-i]=canvas[High/2][Width/3]-1;
	} 
	//��ʼ��ʳ��λ�� 
	food_x=rand()%(High-5)+2;
	food_y=rand()%(Width-5)+2;
	canvas[food_x][food_y]=-2;
	//��ʼ����������
//	extraLife_x=rand()%(High-5)+3;
//	extraLife_y=rand()%(Width-5)+3;
//	canvas[extraLife_x][extraLife_y]=-3;
		 
	
		
}
void show(){//��ʾ����
	int i,j; 
	Sleep(150);
	gotoxy(0,0);//����ƶ���ԭ��λ�ã������ػ�����
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
void moveSnakeByDirection2(){ //�ƶ�С��2 
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
			}//ɨ������canvas����Ԫ�أ��ҵ�С�ڵ���-5��Ԫ�ؼ�1 
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
	canvas[oldTail_i][oldTail_j]=0;//�ҵ���СԪ�أ�����β�ͣ��������Ϊ0
	for(i=0;i<High;i++){
		for(j=0;j<Width;j++){
			if(canvas[i][j]==-6){ //�ҵ���ͷ 
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
	
	if(canvas[newHead_i][newHead_j]==-2){ //����ͷ�Ե�ʳ�� 
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
void updateWithoutInput(){ //���û������޹صĸ��� 
	moveSnakeByDirection();
	moveSnakeByDirection2();
}
void updateWithInput(){ //���û������йصĸ���(С��1�� 
	char input;
	if(kbhit()){//�ж��Ƿ������� 
		input=getch();
	}
	//����input��ֵ 
	//�ı�moveDirection��ֵ����С���ƶ�λ��
	//����moveSnakeByDirectionʵ���ƶ� 
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
void updateWithInput2(){ //���û������йصĸ��� 
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
	printf("\n��Ϸ��ʼ�����С���밴�����ϡ�w������s������a������d����������С���������ҷ���\n");
	printf("\n\t�ұ�С���밴�����ϡ�i������k������j������l����������С���������ҷ���\n");
	printf("\n�밴1��ʼ��Ϸ\n");
	scanf("%d",&number);
	system("cls");
	startup();//���ݳ�ʼ��
	while(1){
		if(number==1){
			show();//˫��ģʽ����
			updateWithoutInput();//���û������޹صĸ���
			updateWithInput();//���û������йصĸ��� 
			updateWithInput2();//���û������йصĸ��� 
		}	
	} 
	return 0;
}
