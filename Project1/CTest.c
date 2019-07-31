#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
//kbhit() , getch()

//�Լ�����
void gotoxy(int, int);
void drawChar();
void drawHuddle();
void drawUI();
void keyInput();

void setColor(unsigned short text,unsigned short back);


//������ �����ƾ �Լ���
void inputThreadMain(void* arg);
void drawThreadMain(void* arg);
void jumpThreadMain(void* arg);
void animThreadMain(void* arg);
void huddleThreadMain(void* arg);
void collisionThreadMain(void* arg);

//��������
char input;
int playerYPos=0;

int isJumpingAnim = 0;
int isJumpPhysics = 0;

int animation = 0; //0 : idle,10 run0 11 run1 12 run2 13 run3
                   //101 jump1 102 jump2 103 jump3 104 jump4 105 jump5

int huddleXPos=80;
int huddleSpeed=50;
int isHuddle1Drawing = 1;

int score = 0;
int HP = 5;
int playerState = 0;


int main() {
	

	int inputThreadID;
	int drawThreadID;
	int jumpThreadID;
	int animThreadID;
	int huddleThreadID;
	int collisionThreadID;

	int isGameNotEnd = 1;
	time_t t;
	//�����ѹ� �õ带 �����Ѵ�.
	srand(&t);
	//Ŀ���� �Ⱥ��̰��Ѵ�
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);



	//���α׷��� Ÿ��Ʋ�� �����Ѵ�
	system("title ���ѱ���� Made By MJ");

	//ȭ���� ũ�⸦ �����Ѵ�
	system("mode con:lines=40 cols=100");
	
	//Ÿ��Ʋ�� ���� ǥ���Ѵ�
	puts("���ѱ���� Made By MJ\n\n");
	setColor(15, 0);
	gotoxy(3, 3);
	puts("����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
	for (int i = 4; i < 34; i++) {
		gotoxy(3, i);
		printf("%s","��");
	}
	gotoxy(3, 34);
	
	puts("����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

	

	for (int i = 4; i < 34; i++) {
		gotoxy(94, i);
		printf("%d", i);
	}

	/* ����
	setColor(0, 11);
	for (int i = 4; i < 10; i++) {
		gotoxy(5, i);
		printf("                                                                                         ");
	}
	*/


	//Input �����带 �����Ų��
	inputThreadID = _beginthread(inputThreadMain, 0, NULL);
	//Draw �����带 �����Ų��
	drawThreadID = _beginthread(drawThreadMain, 0, NULL);
	//Jump �����带 �����Ų��
	jumpThreadID = _beginthread(jumpThreadMain, 0, NULL);
	//Animation �����带 �����Ų��.
	animThreadID = _beginthread(animThreadMain, 0, NULL);
	//Huddle �����带 �����Ų��.
	huddleThreadID = _beginthread(huddleThreadMain, 0, NULL);


	while (isGameNotEnd) {
		Sleep(1000);
	}

	return 0;
}

void inputThreadMain(void* arg) {
	
	keyInput();
}
void drawThreadMain(void* arg) {
	
	
	while (1) {
		drawChar();
		Sleep(5);
		drawHuddle();
		Sleep(5);
		drawUI();
		Sleep(5);
		
	}
}
void jumpThreadMain(void* arg) {

	while (1) {
		if (isJumpPhysics) {
			//���

			//����ڼ�
			playerYPos = 0;
			Sleep(100);

			//���
			playerYPos = 1;
			Sleep(12);
			playerYPos = 2;
			Sleep(15);
			playerYPos = 3;
			Sleep(20);
			playerYPos = 4;
			Sleep(25);
			playerYPos = 5;
			Sleep(32);
			playerYPos = 6;
			Sleep(35);
			playerYPos = 7;
			Sleep(40);
			playerYPos = 8;
			Sleep(40);
			playerYPos = 9;
			Sleep(45);
			playerYPos = 10;
			Sleep(80);
			//����
			playerYPos = 10;
			Sleep(35);
			playerYPos = 9;
			Sleep(32);
			playerYPos = 8;
			Sleep(30);
			playerYPos = 7;
			Sleep(27);
			playerYPos = 6;
			Sleep(25);
			playerYPos = 5;
			Sleep(27);
			playerYPos = 4;
			Sleep(20);
			playerYPos = 3;
			Sleep(17);
			playerYPos = 2;
			Sleep(15);
			playerYPos = 1;
			Sleep(10);
			playerYPos = 0;
			
			//����
			Sleep(200);
			
			isJumpPhysics = 0;
		}
		else {
			
			Sleep(100);
			playerYPos = 2;
			Sleep(100);
			playerYPos = 0;
			
		}
	}
}
void animThreadMain(void* arg) {

	while (1) {
		if (isJumpingAnim) {//���������϶�
			
			animation = 100;
			Sleep(100);

			animation = 101;
			Sleep(800);
		

			animation = 100;
			Sleep(200);

			isJumpingAnim = 0;
		}
		else {//�޸�������϶�
			animation = 10;
			Sleep(100);

			if (isJumpingAnim)
				continue;

			animation = 11;
			Sleep(100);
			
			if (isJumpingAnim)
				continue;

			animation = 12;
			Sleep(100);

			if (isJumpingAnim)
				continue;

			animation = 13;
			Sleep(100);
		
			if (isJumpingAnim)
				continue;
		}
		
			
		
		
		
		
	}
}
void huddleThreadMain(void* arg) {
	while (1) {
		if (huddleXPos <= 5 && isHuddle1Drawing) {
			isHuddle1Drawing = 0;
			huddleXPos = 80;

			score++;
		}
		else {
			huddleXPos -= 1;
		}
		if (isHuddle1Drawing == 0) {
			do {
				huddleSpeed = rand() % 50;
			} while (huddleSpeed < 20);
			isHuddle1Drawing = 1;
		}
		Sleep(huddleSpeed);
	}
	
}
void collisionThreadMain(void* arg) {

}
//�Է��Լ�
void keyInput() {
	while (1) {
		Sleep(10);
		if (_kbhit()) {
			input = _getch();

			if (input == 32 && isJumpPhysics == 0 && isJumpingAnim == 0) {
				isJumpPhysics = 1;
				isJumpingAnim = 1;
			}

		}
	}
}

//�׸��� �Լ���
void drawChar() {
	
	//ĳ���� ���� �ʱ�ȭ
	setColor(0, 0);
	for (int i = 5; i < 34; i++) {
		gotoxy(5, i);
		printf("                         ");
	}
	
	//ĳ���� �׸���
	
	//ĳ���� UI DRAW
	gotoxy(12, getPlayerYPos() - 16);
	setColor(10, 15);
	
	for (int i = 0; i < 5; i++) {
		if (HP > i)
			printf("��");
		else
			printf("  ");
	}

	//animation = 101; //�ִϸ��̼� �����
	
	setColor(14, playerState);
	if (animation == 10) { //�޸��� 0
		gotoxy(15, getPlayerYPos() - 12);
		setColor(14, playerState); printf("����");
		gotoxy(14, getPlayerYPos() - 11);
		printf("������");
		gotoxy(12, getPlayerYPos() - 10);
		printf("���"); printf("���"); setColor(12, playerState); printf("��");//22
		gotoxy(12, getPlayerYPos() - 9);
		setColor(14, playerState); printf("��"); setColor(14, playerState); printf("������");//23
		gotoxy(14, getPlayerYPos() - 8);
		printf("���"); //24 
		gotoxy(14, getPlayerYPos() - 7);
		printf("��"); //25
		gotoxy(12, getPlayerYPos() - 6);
		setColor(3, playerState); printf("���"); setColor(14, playerState); //26
		gotoxy(12, getPlayerYPos() - 5);
		printf("��"); setColor(3, playerState); printf("��"); setColor(14, playerState); //27
		gotoxy(14, getPlayerYPos() - 4);
		printf("���"); //28
		gotoxy(13, getPlayerYPos() - 3);
		setColor(8, playerState); printf("���"); //29
		gotoxy(12, getPlayerYPos() - 2);
		printf("��   ��"); //30
		gotoxy(7, getPlayerYPos() - 1);
		setColor(15, playerState); printf("��"); setColor(14, playerState); printf("���      ��"); //31
		gotoxy(7, getPlayerYPos());
		setColor(15, playerState); printf("��"); setColor(14, playerState); printf("           ��"); //32
		gotoxy(20, getPlayerYPos() + 1);
		setColor(15, playerState); printf("���"); //33
	}
	else if (animation == 11) { //�޸��� 1
		gotoxy(15, getPlayerYPos() - 12);
		setColor(14, playerState); printf("����");
		gotoxy(14, getPlayerYPos() - 11);
		printf("������");
		gotoxy(12, getPlayerYPos() - 10);
		printf("���");   printf("���"); setColor(12, playerState); printf("��"); setColor(14, playerState);
		gotoxy(12, getPlayerYPos() - 9);
		printf("��");  printf("������");
		gotoxy(14, getPlayerYPos() - 8);
		printf("���"); //24 
		gotoxy(14, getPlayerYPos() - 7);
		printf("��"); //25
		gotoxy(10, getPlayerYPos() - 6);
		printf("��"); setColor(3, playerState); printf("����"); //26
		gotoxy(9, getPlayerYPos() - 5);
		setColor(14, playerState); printf("��   "); setColor(3, playerState); printf("��"); setColor(14, playerState); printf("���"); //27
		gotoxy(10, getPlayerYPos() - 4);
		printf("���"); setColor(8, playerState); printf("��"); //28
		gotoxy(13, getPlayerYPos() - 3);
		printf("���"); //29
		gotoxy(12, getPlayerYPos() - 2);
		printf("��   ��"); //30
		gotoxy(10, getPlayerYPos() - 1);
		setColor(14, playerState); printf("��       ��"); //31
		gotoxy(7, getPlayerYPos());
		setColor(15, playerState); printf("��"); setColor(14, playerState); printf("��       ��"); //32
		gotoxy(7, getPlayerYPos() + 1);
		setColor(15, playerState); printf("��        ���"); //33
	}
	else if (animation == 12) { //�޸��� 2
		gotoxy(15, getPlayerYPos() - 12);
		setColor(14, playerState); printf("����");
		gotoxy(14, getPlayerYPos() - 11);
		printf("������");
		gotoxy(12, getPlayerYPos() - 10);
		printf("���");   printf("���"); setColor(12, playerState); printf("��");
		gotoxy(12, getPlayerYPos() - 9);
		setColor(14, playerState); printf("��");  printf("������");
		gotoxy(14, getPlayerYPos() - 8);
		printf("���"); //24 
		gotoxy(14, getPlayerYPos() - 7);
		printf("��"); //25
		gotoxy(12, getPlayerYPos() - 6);
		printf("��"); setColor(3, playerState); printf("��  "); setColor(14, playerState); printf("��"); //26
		gotoxy(12, getPlayerYPos() - 5);
		printf("��"); setColor(3, playerState); printf("��"); setColor(14, playerState); printf("��"); //27
		gotoxy(12, getPlayerYPos() - 4);
		printf("���"); //28
		gotoxy(13, getPlayerYPos() - 3);
		setColor(8, playerState); printf("����"); //29
		gotoxy(13, getPlayerYPos() - 2);
		printf("��    ��"); //30
		gotoxy(14, getPlayerYPos() - 1);
		setColor(14, playerState); printf("��  ��"); //31
		gotoxy(13, getPlayerYPos());
		printf("�� ��"); //32
		gotoxy(12, getPlayerYPos() + 1);
		setColor(15, playerState); printf("���"); //33
	}
	else if (animation == 13) { //�޸��� 3
		gotoxy(15, getPlayerYPos() - 12);
		setColor(14, playerState); printf("����");
		gotoxy(14, getPlayerYPos() - 11);
		printf("������");
		gotoxy(12, getPlayerYPos() - 10);
		printf("���");   printf("���"); setColor(12, playerState); printf("��");
		gotoxy(12, getPlayerYPos() - 9);
		setColor(14, playerState); printf("��"); printf("������");
		gotoxy(14, getPlayerYPos() - 8);
		printf("���"); //24 
		gotoxy(14, getPlayerYPos() - 7);
		printf("��"); //25
		gotoxy(12, getPlayerYPos() - 6);
		printf("��"); setColor(3, playerState); printf("�� "); setColor(14, playerState); //26
		gotoxy(13, getPlayerYPos() - 5);
		printf("�����"); //27
		gotoxy(14, getPlayerYPos() - 4);
		setColor(8, playerState); printf("��"); //28
		gotoxy(13, getPlayerYPos() - 3);
		printf("���"); //29
		gotoxy(14, getPlayerYPos() - 2);
		printf("���"); //30
		gotoxy(14, getPlayerYPos() - 1);
		setColor(14, playerState); printf("��  ��"); //31
		gotoxy(8, getPlayerYPos());
		setColor(15, playerState); printf("��"); setColor(14, playerState); printf("���   ��"); //32
		gotoxy(8, getPlayerYPos() + 1);
		setColor(15, playerState); printf("��       ���"); //33
	}
	else if (animation == 100) {//���� 0
		gotoxy(18, getPlayerYPos() - 9);
		printf("�����");
		gotoxy(15, getPlayerYPos() - 8);
		printf("������"); setColor(12, playerState); printf("��"); //24 
		gotoxy(17, getPlayerYPos() - 7);
		setColor(14, playerState); printf("�������"); //25
		gotoxy(11, getPlayerYPos() - 6);
		printf("���    ���");//26
		gotoxy(9, getPlayerYPos() - 5);
		printf("��    ��"); setColor(3, playerState); printf("��"); //27
		gotoxy(13, getPlayerYPos() - 4);
		setColor(14, playerState); printf("��"); setColor(3, playerState); printf("��"); //28
		gotoxy(11, getPlayerYPos() - 3);
		setColor(14, playerState); printf("�� "); setColor(8, playerState); printf("��"); //29
		gotoxy(13, getPlayerYPos() - 2);
		printf("�� ��"); //30
		gotoxy(15, getPlayerYPos() - 1);
		setColor(14, playerState); printf("�� ��"); //31
		gotoxy(14, getPlayerYPos());
		printf("�� ��");//32
		gotoxy(13, getPlayerYPos() + 1);
		setColor(15, playerState); printf("�����"); //33
	}
	else if (animation == 101) {//���� 1
		gotoxy(20, getPlayerYPos() - 15);
		printf("���"); //17
		gotoxy(19, getPlayerYPos() - 14);
		printf("����"); //18
		gotoxy(13, getPlayerYPos() - 13);
		printf("��   �����"); //19
		gotoxy(13, getPlayerYPos() - 12);
		printf("��   ����"); setColor(12, playerState); printf("��"); setColor(14, playerState); //20
		gotoxy(13, getPlayerYPos() - 11);
		printf("��   ������"); //21
		gotoxy(14, getPlayerYPos() - 10);
		printf("��  ���"); //22
		gotoxy(15, getPlayerYPos() - 9);
		
		setColor(3, playerState); printf("��"); setColor(14, playerState); printf(" ��   ��"); //23
		gotoxy(17, getPlayerYPos() - 8);
		setColor(3, playerState);
		printf("���"); setColor(14, playerState); printf("��");  //24 
		gotoxy(17, getPlayerYPos() - 7);
		setColor(3, playerState); printf("��");  //25
		gotoxy(17, getPlayerYPos() - 6);
		setColor(8, playerState);
		printf("��");  //26
		gotoxy(16, getPlayerYPos() - 5);
		
		printf("���");   //27
		gotoxy(15, getPlayerYPos() - 4);
		printf("�� ��");   //28
		gotoxy(15, getPlayerYPos() - 3);
		setColor(14, playerState);
		printf("�� ��");   //29
		gotoxy(15, getPlayerYPos() - 2);
		printf("�� ��");    //30
		gotoxy(14, getPlayerYPos() - 1);
		printf("�� ��");   //31
		gotoxy(13, getPlayerYPos());
		setColor(15, playerState);
		printf("�� ��");   //32
		gotoxy(14, getPlayerYPos() + 1);
		printf("�� ��");   //33
	}
	/* �ִϸ��̼� Ʋ
	gotoxy(8, getPlayerYPos() - 17);
	printf(""); //15
	gotoxy(8, getPlayerYPos() - 16);
	printf(""); //16
	gotoxy(8, getPlayerYPos() - 15);
	printf(""); //17
	gotoxy(8, getPlayerYPos() - 14);
	printf(""); //18
	gotoxy(8, getPlayerYPos() - 13);
	printf(""); //19
	gotoxy(8, getPlayerYPos() - 12);
	printf(""); //20
	gotoxy(8, getPlayerYPos() - 11);
	printf(""); //21
	gotoxy(8, getPlayerYPos() - 10);
	printf(""); //22
	gotoxy(8, getPlayerYPos() - 9);
	printf(""); //23
	gotoxy(8, getPlayerYPos() - 8);
	printf("");  //24
	gotoxy(8, getPlayerYPos() - 7);
	printf("");  //25
	gotoxy(8, getPlayerYPos() - 6);
	printf("");  //26
	gotoxy(8, getPlayerYPos() - 5);
	printf("");   //27
	gotoxy(8, getPlayerYPos() - 4);
	printf("");   //28
	gotoxy(8, getPlayerYPos() - 3);
	printf("");   //29
	gotoxy(8, getPlayerYPos() - 2);
	printf("");    //30
	gotoxy(8, getPlayerYPos() - 1);
	printf("");   //31
	gotoxy(8, getPlayerYPos());
	printf("");   //32
	gotoxy(8, getPlayerYPos() + 1);
	printf("");   //33
	*/


	
	

}
void drawHuddle() {
	
	//huddleXPos = 70;

	setColor(0, 0);
	for (int i = 28; i <= 33; i++) {
		gotoxy(huddleXPos, i);
		printf("�������");
	}


	if (isHuddle1Drawing) {
		setColor(12, 15);
		gotoxy(huddleXPos + 4, 28);
		printf("��");

		gotoxy(huddleXPos + 2, 29);
		printf("��"); printf("��");

		gotoxy(huddleXPos, 30);
		printf("��"); gotoxy(huddleXPos + 4, 30); printf("��");

		gotoxy(huddleXPos, 31);
		printf("��"); gotoxy(huddleXPos + 4, 31); printf("��");

		gotoxy(huddleXPos, 32);
		printf("��"); gotoxy(huddleXPos + 4, 32); setColor(15, 15); printf("����");

		gotoxy(huddleXPos, 33);
		printf("��"); setColor(15, 15); printf("���");
	}
}
void drawUI() {
	
	setColor(15, 0);
	//���ھ� ǥ��
	gotoxy(5,35);
	printf("S C O R E : %d",score);

	//����Ű ǥ��
	gotoxy(70, 35);
	printf("jump : space bar");

}

void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int getPlayerYPos() {
	return 32 - playerYPos;
}

void setColor(unsigned short text, unsigned short back) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
