#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <mmsystem.h>  // mciSendString() 
#pragma comment (lib, "winmm.lib") //MCI


// �ܼ�â ���ڿ� �� ������ 
#define col GetStdHandle(STD_OUTPUT_HANDLE)					// �ܼ�â�� �ڵ������� �޾ƿɴϴ�.
#define WHITE		SetConsoleTextAttribute(col, 0x000f)	// ���
#define YELLOW		SetConsoleTextAttribute(col, 0x000e)	// �����
#define PURPLE		SetConsoleTextAttribute(col, 0x000d)	// ���ֻ�
#define RED			SetConsoleTextAttribute(col, 0x000c)	// ������
#define SKY			SetConsoleTextAttribute(col, 0x000b)	// �ϴû�
#define YELGREEN	SetConsoleTextAttribute(col, 0x000a)	// ���λ�
#define BLUE		SetConsoleTextAttribute(col, 0x0009)	// �Ķ���
#define GOLD		SetConsoleTextAttribute(col, 0x0006)	// �ݻ�
#define VIOLET		SetConsoleTextAttribute(col, 0x0005)	// �����
#define BLOOD		SetConsoleTextAttribute(col, 0x0004)	// �ǻ�
#define BLUE_GREEN	SetConsoleTextAttribute(col, 0x0003)	// û���
#define GREEN		SetConsoleTextAttribute(col, 0x0002)	// ���

#define LEFT   75
#define RIGHT  77
#define UP     72
#define DOWN   80
#define SPACE  32

#define WINDOW_ROW  40 
#define WINDOW_COL  30

#define EX2_R   60   // 2���� â ũ��
#define EX2_C   22	

#define MAX_BLOCK   15	// ���� �ִ��
#define MAX_BULLET   2	// �Ѿ��� ����
#define CON_CENTER_W_STR(msg)	((EX2_R-strlen(msg))/2)	// �ܼ�â�� �߾�(����) x��ǥ

#define EX3_R  20   // 3���� â ũ��
#define EX3_C  15

#define EX5_R  30   // 5���� â ũ��
#define EX5_C  30

#define MOLE_SIZE			3	// ���� ����ũ��
#define BUCKET_SIZE			3	// ������ ����ũ��
#define HOLE_SIZE			9	// Ȧ�� ũ��
#define MOLE_APPEAR_TIME	15	// ���� ����ð�(1500ms)
#define BUCKET_APPEAR_TIME	12	//  ������ð�(1000ms)
#define MISS				-1// �Ǽ�
#define GEN_TIME			5	// 0.5�� (���� ���尣��)
#define GAME_TIME			30.0


char key;
int score[5];
int i, j;
int rank[5] = { 0,0,0,0,0 };  // 1������ 5������ ���
clock_t start_time, new_time;

typedef enum { Flitwick, Hooch, Snape, Moody, Hagrid } PROFESSOR;


void gotoxy(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//����� ��ġ���� �Լ�
void gotoxyHP(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// Ŀ�� �����ִ� �Լ�
void hideCursor() {
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

// ������� ���� �Լ�
void soundtrack() {
	MCI_OPEN_PARMS mciOpen; // MCI_OPEN_PARAMS ����ü ���� 
	mciOpen.lpstrDeviceType = L"mpegvideo"; // mp3 ���� 
	mciOpen.lpstrElementName = L"Prologue.mp3"; // �����̸�
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);

	MCI_PLAY_PARMS mciPlay; // ���
	mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
}


// �Լ� ����
void class1();
void exam1();
void exam2();
void exam3(int potion);
void exam4();
void exam5();



// ��輱 ��� �Լ�
void print_edge() {
	for (i = 0; i < WINDOW_ROW; i++) {
		gotoxy(i * 2, 0);
		printf("��");
		gotoxy(i * 2, WINDOW_COL - 1);
		printf("��");
	}
	for (i = 1; i < WINDOW_COL; i++) {
		gotoxy(0, i);
		printf("��");
		gotoxy((WINDOW_ROW - 1) * 2, i);
		printf("��");
	}
}

// ����ȭ�� �Լ�
void title() {
	system("cls");
	GOLD;
	printf("\n");
	printf("\n");
	printf("                                          ����                                    \n");
	printf("           ��                ���          ��   ��                                  \n");
	printf("     ��    ��   ���   ���  �� ��         ��   ��         ��                       \n");
	printf("     ��    ��       �� �� �� ��     ��   ���   �� ���  ����  ��          ���   \n");
	printf("     ��  ���� ���� ��    �� ��  ��   ��� ��  ��  ��   ��  ����  ���  �� ��  \n");
	printf("   ����  ��   ��  �� ��    ��   ��       ��     ��  ��   ��    ��   ��  �� ��     \n");
	printf("     ��    ��   ���� ��        ��      ���     ��  ��   ��    ��   ���� ��     \n");
	printf("     ��    ��              ����         ��        ��     ��    ��   ��     ��     \n");
	printf("           ��                             ��                 ��  ��    ���         \n");
	printf("                                          ��                      ���              \n");
	printf("                                          ��     AND THE                            \n");
	printf("\n");
	printf("\n");
	printf("     ��  ��  ��  ��  �����     ��     ����    ����    ��  ��    ��   ����   \n");
	printf("     ��  ��  ��  ��       ��    ��  ��   ��    ��  ��    ��  ��  ���  ��  ��        \n");
	printf("     ��  ��  ��  ��     ��     �����  ����    ��    ��  ��  �� �� ��  ��  ���  \n");
	printf("       ��  ��    ��   ��       ��    ��  ��    ��  ��    ��  ��  ��  ���  ��    ��  \n");
	printf("       ��  ��    ��  �����  ��    ��  ��    ��  ����    ��  ��    ��   ����   \n");
	printf("\n");
	printf("                             ����  ����  ���� ����         \n");
	printf("                               ��    ��      ��       ��           \n");
	printf("                               ��    ����  ����   ��           \n");
	printf("                               ��    ��          ��   ��           \n");
	printf("                               ��    ����  ����   ��           \n");

	gotoxy(22, 29); printf("���� ����");
	gotoxy(41, 29); printf("���� ����");
	gotoxy(60, 29); printf("���� Ȯ��");
	gotoxy(0, 30); printf(" "); //30�ٱ��� ȭ�鿡 ��Ÿ���� ���ؼ�
}

// ���� ���� �޴� �Լ�
void game_info() {
	system("cls");
	WHITE;
	print_edge();

	gotoxy(9, 8);	printf("�ظ����Ͱ� 5�� ������ ������ ���鼭 ������ ȹ���ϴ� �����Դϴ�.");
	Sleep(800);
	gotoxy(10, 10);	printf("�̵��� ����Ű��, ���� �ɰ������ �����̽��ٸ� ������ �˴ϴ�.");
	Sleep(800);
	gotoxy(14, 12);	printf("�� �����Ե��� ������ �а� ������ ���� �ϸ� �˴ϴ�.");
	Sleep(800);
	gotoxy(14, 14);	printf("���������� ���� 5�� �ȿ� �� ��� ��ŷ�� ��� �˴ϴ�.");
	Sleep(800);
	gotoxy(9, 20);	GOLD; printf("�ظ����Ͱ� �Ǿ ȣ�׿�Ʈ ������ ���� ���� ������ �޾ƺ�����~");
	
	_getch();
	title();
}

// ���� Ȯ�� �޴� �Լ�
void rank_show() {
	system("cls");
	WHITE;
	print_edge();

	GOLD;
	gotoxy(31, 6); printf("------------------");
	gotoxy(31, 7); printf("  RANKING  TOP 5 ");
	gotoxy(31, 8); printf("------------------");

	for (i = 0; i < 5; i++) {
		gotoxy(33, 11 + i * 2);
		printf("%d��     %3d��", i + 1, rank[i]);
	}

	_getch();
	title();
}

void aplus(int x, int y) {
	BLOOD;
	gotoxy(x, y);	   printf("                     ��");
	gotoxy(x, y + 1);  printf("                     ��");
	gotoxy(x, y + 2);  printf("        ��       ������");
	gotoxy(x, y + 3);  printf("       ���          ��");
	gotoxy(x, y + 4);  printf("      ��  ��         ��");
	gotoxy(x, y + 5);  printf("     ��    ��          ");
	gotoxy(x, y + 6);  printf("    ��      ��         ");
	gotoxy(x, y + 7);  printf("   �������        ");
	gotoxy(x, y + 8);  printf("  ��          ��       ");
	gotoxy(x, y + 9);  printf(" ��            ��      ");
	gotoxy(x, y + 10); printf("��              ��     ");
}

// ���� ��� �Լ�
void the_end() {
	system("cls");
	WHITE;
	print_edge();

	gotoxy(34, 4);
	printf("WIZARDING TEST");
	
	for (i = 1; i <= 5; i++) {
		gotoxy(16, 6 + 2 * i);
		printf("%d ����  :    %3d��", i, score[i]);
		score[0] += score[i];
	}
	
	gotoxy(14, 20);
	printf("���� ���� :    %3d��", score[0]);

	gotoxy(16, 22);
	printf("��   �� :       ");

	if (score[0] > 470) {
		printf("A+");
		aplus(44, 10);
	}
	else if (score[0] > 450) printf("A");
	else if (score[0] > 400) printf("B");
	else if (score[0] > 300) printf("C");
	else if (score[0] > 250) printf("D");
	else printf("F");

	for (i = 0; i < 5; i++) {
		if (rank[i] < score[0]) {
			for (j = 4; j >= i; j--) {
				rank[j + 1] = rank[j];
			}
			rank[i] = score[0];
			break;
		}
	}

	Sleep(5000);
	rank_show();
}


// ��ȭâ ��� �Լ�
void print_chat() {
	gotoxy(9, 21); printf("��������������������������������");
	gotoxy(8, 22); printf("��");
	gotoxy(8, 23); printf("��");
	gotoxy(8, 24); printf("��");
	gotoxy(8, 25); printf("��");
	gotoxy(8, 26); printf("��");
	gotoxy(70, 22); printf("��");
	gotoxy(70, 23); printf("��");
	gotoxy(70, 24); printf("��");
	gotoxy(70, 25); printf("��");
	gotoxy(70, 26); printf("��");
	gotoxy(9, 27); printf("��������������������������������");
}

// ��ȭâ �ڸ� �����ִ� �Լ�
void delete_chat() {
	for (j = 21; j < 28; j++) {
		for (i = 8; i < 72; i++) {
			gotoxy(i, j);
			printf(" ");
		}
	}
}

// ��ȭ �����ִ� �Լ�
void delete_dialog() {
	for (j = 23; j < 26; j++) {
		for (i = 22; i < 70; i++) {
			gotoxy(i, j);
			printf(" ");
		}
	}
}


void game_intro() {
	system("cls");
	WHITE;
	print_edge();

	// ����
	for (i = 1; i < WINDOW_COL - 1; i++) {
		gotoxy(29, i); printf("��");
		gotoxy(49, i); printf("��");
	}
	BLUE_GREEN;
	gotoxy(35, 9);	printf("   / ��");
	gotoxy(35, 10); printf("  /    ��");
	gotoxy(35, 11);	printf("��________��");
	WHITE;
	gotoxy(35, 12);	printf("(;; ��--��)");

	gotoxyHP(38, 28); printf("��-��");
	Sleep(300);

	// �̵�
	gotoxy(38, 28); printf("     ");
	for (i = WINDOW_COL - 2; i > 13; i--) {
		gotoxyHP(38, i); printf("��-��");
		Sleep(90);
		gotoxyHP(38, i); printf("     ");
	}

	// ����
	gotoxyHP(38, 13); printf("��-��");
	Sleep(300);

	delete_chat();
	print_chat();
	gotoxy(11, 23); printf("������ :");
	gotoxy(22, 23); printf("������ ǥ�� ������ ������ �ִ� ���̱���");
	gotoxy(22, 24); printf("�غ�� �� �Ͽ���?");
	Sleep(2000);

	delete_dialog();
	gotoxy(11, 23); printf("�ظ����� :");
	gotoxy(22, 23); printf("......");
	Sleep(2000);

	gotoxy(11, 23); printf("������ :");
	gotoxy(22, 23); printf("��.. 1���ô� �����ֹ�����, 2���ô� �������,");
	Sleep(1000);
	gotoxy(22, 24); printf("3���ô� ���������, 4���ô� ����Ǹ�����������");
	Sleep(1000);
	gotoxy(22, 25); printf("5���ô� �ź��� ���� ������ ������ �ֱ���.");
	Sleep(1000);

	delete_dialog();
	gotoxy(22, 23); printf("���� ����� �����Ը��� �������ֽǰŴ�.");
	gotoxy(22, 24); printf("�׷� ���� ��� �ֱ⸦...");
	gotoxy(22, 25); printf("����� ���.");
	Sleep(2000);

	system("cls");

	print_edge();
	for (i = 1; i < WINDOW_COL - 1; i++) {
		gotoxy(29, i); printf("��");
		gotoxy(49, i); printf("��");
	}
	gotoxyHP(38, 13); printf("��-��");

	delete_chat();
	print_chat();
	gotoxy(11, 23); printf("�ظ����� :");
	gotoxy(22, 23); printf("!!!!!!");
	Sleep(1000);

	delete_chat();
	for (i = 1; i < WINDOW_COL - 1; i++) {
		gotoxy(29, i); printf("��");
		gotoxy(49, i); printf("��");
	}

	gotoxyHP(38, 13); printf("     ");
	for (i = 12; i > 0; i--) {
		gotoxyHP(38, i); printf("��-��");
		Sleep(90);
		gotoxyHP(38, i); printf("     ");
	}

	class1();
}


void print_class(int prof) {
	print_edge();

	// ĥ��
	gotoxy(7, 3);	printf("������������������������������������������������������������������������������������������������������������������������������������");
	gotoxy(6, 4); 	printf("��");
	gotoxy(73, 4); 	printf("��");
	gotoxy(6, 5); 	printf("��");
	gotoxy(73, 5); 	printf("��");
	gotoxy(6, 6); 	printf("��");
	gotoxy(73, 6); 	printf("��");
	gotoxy(7, 7);	printf("������������������������������������������������������������������������������������������������������������������������������������");
	
	// å��
	gotoxy(8, 11);	printf("��������������������������������������������������");
	gotoxy(8, 12); 	printf("��");
	gotoxy(32, 12); printf("��");
	gotoxy(8, 13);	printf("��������������������������������������������������");
	gotoxy(8, 14);	printf("��������������������������������������������������");
	gotoxy(8, 15); 	printf("��");
	gotoxy(32, 15); printf("��");
	gotoxy(8, 16);	printf("��������������������������������������������������");
	gotoxy(8, 17);	printf("��������������������������������������������������");
	gotoxy(8, 18); 	printf("��");
	gotoxy(32, 18); printf("��");
	gotoxy(8, 19);	printf("��������������������������������������������������");
	gotoxy(47, 11);	printf("��������������������������������������������������");
	gotoxy(47, 12); printf("��");
	gotoxy(71, 12); printf("��");
	gotoxy(47, 13);	printf("��������������������������������������������������");
	gotoxy(47, 14);	printf("��������������������������������������������������");
	gotoxy(47, 15); printf("��");
	gotoxy(71, 15); printf("��");
	gotoxy(47, 16);	printf("��������������������������������������������������");
	gotoxy(47, 17);	printf("��������������������������������������������������");
	gotoxy(47, 18); printf("��");
	gotoxy(71, 18); printf("��");
	gotoxy(47, 19);	printf("��������������������������������������������������");

	//���� ĳ����
	switch (prof) {
	case Flitwick:
		gotoxy(36, 7); 	printf("/   ��");
		gotoxy(35, 8); 	printf("/      ��");
		gotoxy(34, 9); 	printf("( ;;���) / ");
		break;
	case Hooch:
		gotoxy(37, 7); 	printf("/   ��");
		gotoxy(36, 8); 	printf("/      ��");
		gotoxy(31, 9); 	printf("���� (  �� ����)");
		break;
	case Snape:
		gotoxy(37, 7); 	printf("/   ��");
		gotoxy(36, 8); 	printf("/      ��");
		gotoxy(35, 9); 	printf("(  �ल�� ) /");
		break;
	case Moody:
		gotoxy(37, 7); 	printf("/   ��");
		gotoxy(36, 8); 	printf("/      ��");
		gotoxy(35, 9); 	printf("(  ��  �� )");
		gotoxy(39, 10); printf("��");
		break;
	case Hagrid:
		gotoxy(36, 6); 	printf("�סҡҡҡ�");
		gotoxy(35, 7);  printf("�� ��  �� ��");
		gotoxy(34, 8); 	printf("�ץ�����������");
		gotoxy(36, 9); 	printf("����������");
		break;
	}

	int x = 38, y = 28;

	//���� ��ġ���� �����ϱ� ������ �ݺ�
	while (y != 10 || key != SPACE) {
		gotoxyHP(x, y); printf("��-��");

		key = _getch();

		gotoxyHP(x, y);
		printf("     ");

		switch (key) {
		case LEFT:
			if (34 < x) x--;
			break;
		case RIGHT:
			if (x < 42) x++;
			break;
		case UP:
			if (10 < y) y--;
			break;
		case DOWN:
			if (y < 28) y++;
			break;
		}
	}

	gotoxyHP(x, y); printf("��-��");
	print_chat();
}

void class1() {
	system("cls");

	print_class(Flitwick);
	gotoxy(11, 23); printf("�ø�Ʈ�� :");
	gotoxy(22, 23); printf("�ظ����� ��. �̹� ������ ���� �ֹ� �����̶���.");
	gotoxy(22, 24); printf("������ �� 5�����̰�, �´� ��ȣ�� ������ �ȴܴ�.");
	Sleep(2000);

	delete_dialog();
	gotoxy(22, 23); printf("�׵��� ���� ������ ������ϱ� ���� �� �ְ���?");

	Sleep(3000);
	exam1();
}

void class2() {
	system("cls");

	print_class(Hooch);
	gotoxy(12, 23); printf("��ġ���� :");
	gotoxy(23, 23); printf("���ͱ���. �̹� ������ ���� �����̶���.");
	gotoxy(23, 24); printf("30�� �ȿ� ���ƴٴϴ� ����ġ 10���� ������ �ȴ�.");
	gotoxy(23, 25); printf("���� ������ ���ƿ��ϱ� �� ���ϰ�~");
	Sleep(1000);

	delete_dialog();
	gotoxy(23, 23); printf("30�� �ȿ� ���ƴٴϴ� ����ġ 10���� ������ �ȴ�.");
	gotoxy(23, 24); printf("���� ������ ���ƿ��ϱ� �� ���ϰ�~");
	gotoxy(23, 25); printf("����ġ ������ �߾����ϱ� ���ҰŶ�� ���� �Ǳ���");

	Sleep(3000);
	exam2();
}

void class3() {
	system("cls");

	int potion = rand() % 2;
		
	print_class(Snape);
	gotoxy(11, 23); printf("�������� :");
	gotoxy(22, 23); printf("�� ������ �����ϰڴ�.");
	gotoxy(22, 24); printf("30�ʾȿ� ĥ�ǿ� ���� ������ ����µ� �ʿ���");
	gotoxy(22, 25); printf("��Ḧ ã�ƿͶ�.");
	Sleep(1000);

	gotoxy(30, 5);
	if (potion == 0) { BLUE; printf("��"); }
	else { VIOLET; printf("��"); }	
	WHITE; printf("   =   ?  +  ?  +  ?");

	delete_dialog();
	gotoxy(22, 23);	printf("�� 3���� �����ð�. ���� �ʰ� �� ã�� ������");
	gotoxy(22, 24); printf("������ �ǹ��̱���");
	gotoxy(22, 25); printf("�� ��ٸ��� �ִ°ų�! ���� ���������ʰ�");

	Sleep(3000);
	exam3(potion);
}

void class4() {
	system("cls");

	print_class(Moody);
	gotoxy(11, 23); printf(" ��   �� :");
	gotoxy(22, 23); printf("�̹� ������ ����͸� ����ġ�� �����̴�.");
	gotoxy(22, 24); printf("���� �ð��� 30��. ���� �ڽ��� ��Ʈ�δ��� ������");
	gotoxy(22, 25); printf("�ҷ����� ó���ϸ� �ȴ�.");
	Sleep(2000);

	delete_dialog();
	gotoxy(22, 23); printf("�����Ʈ�� ����ִ� ���� �������� ������ �� ��");
	gotoxy(22, 24); printf("�� �־�� �Ѵ�. ");
	gotoxy(22, 25); printf("Ư�� �ظ����Ͷ�� ����غ��� �ǰ���.");

	Sleep(3000);
	exam4();
}

void class5() {
	system("cls");

	print_class(Hagrid);
	gotoxy(11, 23); printf("�ر׸��� :");
	gotoxy(22, 23); printf("�� �ظ���. ���� �����������̱���~");
	gotoxy(22, 24); printf("�̹� ������ ���� ���ܴ�. ����� �ִ� ��������");
	gotoxy(22, 25); printf("ã�Ƽ� ���̸� �ְ� ģ�е��� ������ �ȴܴ�.");
	Sleep(800);
	delete_dialog();
	gotoxy(22, 23); printf("�̹� ������ ���� ���ܴ�. ����� �ִ� ��������");
	gotoxy(22, 24); printf("ã�Ƽ� ���̸� �ְ� ģ�е��� ������ �ȴܴ�.");
	gotoxy(22, 25); printf("���̸� ���� �ټ��� ���� ������ ���� �� �ִܴ�.");
	Sleep(2000);

	delete_dialog();
	gotoxy(22, 23); printf("�׸��� �̹��� ������ ������ �ϳ� �ִµ� �����ְ�");
	gotoxy(22, 24); printf("�ͱ���. ������ ������ ���̶� �츣�̿´��� ����");
	gotoxy(22, 25); printf("���θ����� �ѹ� ã�ƿ��Ŷ�. ��¼�� ��¼��......");

	Sleep(3000);
	exam5();
}


/// 1����

 // ���� ������ ���� ����ü
typedef struct {
	char *question;
	int *choice[2];
	int answer;
	BOOL already;
} QUESTION;

QUESTION question_data[] = {
	   { "��Ʈ�δ����� ��ȯ�� ���Ʈ�� ����ĥ �� ����ϴ� �ֹ���?\n","�����縮�Ƹ�����","�ͽ����� ��Ʈ�δ�",2, FALSE},
	   { "�հŸ��� �ִ� ��ü�� ��ȯ�� �� ����ϴ� �ֹ���?\n","���ķ�","�ͽ����� ��Ʈ�δ�", 1, FALSE},
	   { "��ü�� �������� �������� �ϴ� ���ߺξ� �ֹ���?\n","��������� �������","��������� ��������", 2, FALSE},
	   { "��Ƭ ������� ��ģ ������ ġ���ϴ� �ֹ���?\n","����� �̹ٳ׽�ī","���׶� �������", 2, FALSE},
	   { "������ ����� �����ϰų� ����� �ֹ���?\n","�������ս�","���������", 2, FALSE },
	   { "�뼭���� ���� ���� �� �ϳ��� ���� ������ �ֹ���?\n","�ƹٴ� �ɴٺ��","ũ��ÿ�", 1 ,FALSE },
	   { "��ü�� ���Ľ�ų �� ����ϴ� �ֹ���?\n","�𼾵��","���ٸ���", 2, FALSE  },
	   { "�������ų� ���ʶ߸� �� ����ϴ� �ֹ���?\n","�𼾵�","���ķ�", 1,FALSE },
	   { "�η��� ���� ���� �� ����ϴ� �ֹ���?\n","�����޼�","�ƹٴ��ɴٺ��", 1, FALSE },
	   { "�뼭���� ���� ���� �� �ϳ��� ��븦 ������Ű�� �ֹ���?\n","�ƹٴ��ɴٺ��","���丮��" , 2, FALSE },
	   { "���� ����Ǿ� ������ų �� ����ϴ� �ֹ���?\n","������Ÿ","���丣��콺", 1, FALSE }
};

void exam1() {
	int selectnum;
	int sel;

	for (sel = 0; sel < 5; sel++) {
		do {
			selectnum = rand() % (sizeof(question_data) / sizeof(question_data[0]));
		} while (question_data[selectnum].already == TRUE);

		question_data[selectnum].already = TRUE;

		system("cls");
		print_edge();

		gotoxy(16, 7); printf("%d. %s", sel + 1, question_data[selectnum].question);  // ����

		for (i = 0; i < 2; i++) {  // ������
			gotoxy(19, 11 + i * 3);
			printf("(%d) %s", i + 1, question_data[selectnum].choice[i]);
		}

		gotoxy(18, 19); printf("(1), (2) �� �ϳ��� �����ϼ���  :  ");
		key = _getch();
		printf("%c", key);

		key -= 0x30;  // key�� �������̶� �Է¹��� ������ ��ȯ���������						
		if (key == question_data[selectnum].answer) score[1] += 20;

		Sleep(500);
	}
	class2();
}


// 2����

//��輱 ��� �Լ�2
void print_edge2() {
	for (i = 0; i < EX2_R / 2; i++) {
		gotoxy(i * 2, 0); printf("��");
		gotoxy(i * 2, EX2_C - 1); printf("��");
	}

	for (i = 1; i < EX2_C - 1; i++) {
		gotoxy(0, i); printf("��");
		gotoxy(EX2_R - 2, i); printf("��");
	}
}

// ��ֹ� ������ ���� ����ü
typedef struct {
	int    type;   // ����
	int    width;  // ���� ũ��
	int    height;
	int    x;      // ��� ��ǥ
	double y;
	double speed;  // �ӵ�
} BULLET_BLOCK;

// ����� ������ ���� ����ü
typedef struct {
	char* shape;
	int	  width;  
	int	  height;
	int	  x;	 
	int	  y;
} PLAYER;

PLAYER		 gamer;
BULLET_BLOCK bullet_block[MAX_BLOCK];
enum BULLET { OBSTACLE, SNICH };

// ��ֹ� ��ǥ �� �ӵ� �缳�� �Լ�
void reset_block(BULLET_BLOCK* block) {
	int interval = rand() % 5 + 2;

	block->x = rand() % (EX2_R - 6) + 2;  // 3 ~ (EX2_R - 6 + 3)	
	if (block->x % 2 == 1) block->x++;   // x��ǥ�� Ȧ���� ¦���� ��ȯ

	block->y = (rand() % MAX_BLOCK) * -interval;
	block->type = rand() % MAX_BULLET;

	switch (block->type) {
	case OBSTACLE :
		block->speed = 0.7;
		break;
	case SNICH :	  
		block->speed = 1.0;
		break;
	}
}

// �ʱ�ȭ �Լ�
void init2() {	
	for (i = 0; i < MAX_BLOCK; i++) {  // ��ֹ� �ʱ�ȭ
		bullet_block[i].width = 2;
		bullet_block[i].height = 1;
		reset_block(&bullet_block[i]);
	}

	gamer.shape = "��-��";  // ����� �ʱ�ȭ
	gamer.width = 5;
	gamer.height = 1;
	gamer.x = 27;
	gamer.y = EX2_C - 4;
}

//��ֹ� �����ִ� �Լ�
void delete_bullet() {
	for (i = 0; i < MAX_BLOCK; i++) {
		gotoxy(bullet_block[i].x, (int)bullet_block[i].y);
		printf("  ");
	}
}

// ��ֹ� ��ǥ �� ��� ���� �Լ�
void update_bullet() {
	for (i = 0; i < MAX_BLOCK; i++) {		
		bullet_block[i].y += bullet_block[i].speed;  // �̵�(�ϰ�)

		if (bullet_block[i].y > 1) {  // y��ǥ�� ��輱 �Ʒ��̸�			
			if (bullet_block[i].y > EX2_C - 1) {  // ȭ�� ���� ����� �缳��		
				reset_block(&bullet_block[i]);
				continue;
			}
			
			switch (bullet_block[i].type) {
			case OBSTACLE:
				gotoxy(bullet_block[i].x, (int)bullet_block[i].y);
				printf("��");
				break;
			case SNICH:
				YELLOW;
				gotoxy(bullet_block[i].x, (int)bullet_block[i].y);
				printf("��");
				WHITE;  // ��ֹ��� ���� ���ϵ��� 
				break;
			}
		}
	}
}

// ����� �̵� �Լ�
void update_gamer(char key) {
	gotoxy(gamer.x, gamer.y);
	printf("     ");

	// �̵� ũ�⸦ ���Ѵ�. ȭ�� ������ ������ ���ϵ��� ����Ͽ� ����
	switch (key) {
	case LEFT :  
		gamer.x -= 2; 
		if (gamer.x < 2) gamer.x = 2; 
		break;
	case RIGHT : 
		gamer.x += 2;
		if (gamer.x > EX2_R - 2 - strlen(gamer.shape))
			gamer.x = EX2_R - 2 - strlen(gamer.shape);
		break;	
	}
}

void exam2() {
	system("cls");

	int gameloop = 1;
	int cnt2 = 0, snich_count = 10;
	RECT GamerRect, BulletRect, CollisionRect;
	
	init2();
	start_time = clock();

	while (gameloop) {
		print_edge2();		
		
		YELLOW;
		gotoxy(62, 2);  // ���� ���
		printf("���� ����ġ ����");
		gotoxy(62, 3);  // ���� ���
		printf("�� : %2d", cnt2);
		WHITE;
		
		if (_kbhit()) { // ��� �Է��� �޾��� ��
			key = _getch();
			update_gamer(key);
		}		

		gotoxy(gamer.x, gamer.y);
		printf("%s", gamer.shape);

		delete_bullet();
		update_bullet();
				
		for (i = 0; i < MAX_BLOCK; i++) {  // �浹üũ
			SetRect(&GamerRect, gamer.x, gamer.y, gamer.x + gamer.width, gamer.y + gamer.height);
			SetRect(&BulletRect, bullet_block[i].x, (int)bullet_block[i].y, bullet_block[i].x + bullet_block[i].width, (int)bullet_block[i].y + bullet_block[i].height);

			if (IntersectRect(&CollisionRect, &GamerRect, &BulletRect)) {
				if (bullet_block[i].type == OBSTACLE) { // ������ ������ ����
					gameloop = 0;
					break;
				}
				else if (bullet_block[i].type == SNICH) { // ����ġ ������ ���� ����
					reset_block(bullet_block + i);
					cnt2++;
					if (cnt2 == snich_count) { //����ġ ���� ������ 10�̸� ����
						gameloop = 0;
						break;
					}
				}
			}
		}
		Sleep(50);  // �ٷ� ���������� ����������

		new_time = clock();
		if (new_time - start_time >= 30000) break;  // ���ѽð� 30�� ������ ����
	}
	Sleep(100);
	score[2] += snich_count * 10;
	class3();
}


/// 3����

// �ƽ�Ű�ڵ� ����Ͽ� x��ǥ�� 2�� ����
void gotoxy3(int x, int y) {  
	COORD Pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void gotoxyHP3(int x, int y) {
	COORD Pos = { x * 2 , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int warehouse[2][EX3_C][EX3_R] = {                 // 1. �� ��  2. �� ��ֹ�  3. �� ������ ��ġ
	{//map1
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,3,1,1,1,0,0,0,1,0,0,0,1,1,1,1,1,1},
		{1,1,1,0,0,0,1,0,1,0,1,1,1,1,1,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,1,0,0,1,1,0,0,1,1,0,1,1},
		{1,1,1,1,0,0,1,1,1,0,0,1,1,0,2,0,1,0,1,1},
		{1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,1,1,1,3,2,2,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,1,1,1,1,0,0,0,1,1,0,1,1,0,0,0,1,1,1,1},
		{1,1,0,0,1,1,0,1,1,0,1,3,0,0,1,0,1,1,1,1},
		{1,1,1,0,0,0,0,1,1,0,1,0,0,1,1,0,0,1,1,1},
		{1,1,1,0,1,2,1,1,1,0,0,0,0,0,0,0,0,1,1,1},
		{1,1,0,0,0,0,0,3,1,1,1,0,0,0,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}},
	{//map2
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1,1,1},
		{1,1,1,1,3,0,0,0,0,0,0,0,0,2,0,0,1,1,1,1},
		{1,1,1,1,0,1,2,0,1,1,0,0,1,1,1,0,0,1,1,1},
		{1,1,1,1,0,1,0,0,1,1,3,1,1,1,0,0,0,0,1,1},
		{1,1,1,0,0,1,1,1,1,0,1,1,1,0,0,1,1,1,1,1},
		{1,1,1,0,2,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1},
		{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,1,1,1,0,0,1,1,1,0,1,1,3,1,0,1,1,0,1,1},
		{1,1,0,0,0,1,1,1,0,1,0,2,0,0,0,1,1,0,1,1},
		{1,1,1,0,0,0,3,1,1,1,0,0,0,1,1,1,1,0,1,1},
		{1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,1,0,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}}
};

 // ����� ���� �°� ������ִ� �Լ�
void print_warehouse(int map, int potion) {
	for (i = 0; i < EX3_C; i++) {
		for (j = 0; j < EX3_R; j++) {
			gotoxy3(j, i);

			if (warehouse[map][i][j] == 1) {
				WHITE; printf("��");
			}
			else if (warehouse[map][i][j] == 2) {
				WHITE; printf("��");
			}
			else if (warehouse[map][i][j] == 3) {
				WHITE; printf("��");
			}
			else if (warehouse[map][i][j] == 4) {  
				YELLOW; printf("��");
			}
			else if (warehouse[map][i][j] == 5) { 
				BLOOD; printf("��");
			}
			else if (warehouse[map][i][j] == 6) {   
				if (potion == 0) YELGREEN;         // potion 0 �� �� YELLO + YELGREEN
				else BLUE;                         // potion 1 �� �� YELLO + BLOOD
				printf("��");
			}
			else if (warehouse[map][i][j] == 7) {  // ��� ���
				WHITE;
				if (potion == 0) printf("��");
				else printf("��");
			}
			else printf(" ");
		}
	}
}

void exam3(int potion) {
	system("cls");
	
	int nx = 9, ny = 7;   // ���� ��ġ��	

	int cnt = 3; 
	int item[4], order = 0, overlap;
	int map = rand() % 2;  // �� ����

	for (i = 0; i < 4; i++) { // ��� ���� ����
		while (1) {
			item[i] = rand() % 4 + 4;  // 4 5 6 7
			overlap = 0;
			for (j = 0; j < i; ++j) {
				if (item[j] == item[i]) {
					overlap = 1;
					break;
				}
			}
			if (!overlap) break;
		}
	}		

	start_time = clock();

	while (1) {
		print_warehouse(map, potion);  
		gotoxyHP3(nx, ny); printf("/");  // ����� ���
		int dx = 0, dy = 0;  // ������ �ʱ�ȭ

		key = _getch();
		gotoxyHP3(nx, ny); printf(" ");		

		switch (key) {
		case LEFT:
			dx = -1;
			break;
		case RIGHT:
			dx = 1;
			break;
		case UP:
			dy = -1;
			break;
		case DOWN:
			dy = 1;
			break;
		}

		// �̵��ϱ� ����
		while (1) {  // �̵� ���� Ȯ��
			if (warehouse[map][ny + dy][nx + dx] != 1) {                                    // �̵� �Ϸ��� ���� ���� ������
				if (warehouse[map][ny + dy][nx + dx] == 2) {                                // ��ֹ� �а��� �� ��
					if (warehouse[map][ny + (dy * 2)][nx + (dx * 2)] == 0 || warehouse[map][ny + (dy * 2)][nx + (dx * 2)] == 3) {  //��ֹ� �а��� �ڴ� ���� ����ְų� ������ ��ġ���
						if (warehouse[map][ny + dy][nx + dx] == 3)                          // �������� ��ȭ����
							warehouse[map][ny + dy][nx + dx] = 3;
						else warehouse[map][ny + dy][nx + dx] = 0;

						if (warehouse[map][ny + (dy * 2)][nx + (dx * 2)] == 0)              // �� ���� ��ֹ� �о���� 
							warehouse[map][ny + (dy * 2)][nx + (dx * 2)] = 2;  
						else warehouse[map][ny + (dy * 2)][nx + (dx * 2)] = item[order++];  // ������ ��ġ�� ��ֹ� �о������ ��� ��Ÿ�� 
					}
					else break;
				}
				// ��� ������ ��
				else if (warehouse[map][ny + dy][nx + dx] == 4) {  
					warehouse[map][ny + dy][nx + dx] = 0;          // ��� �����ϸ� �������� ǥ��
					cnt--;
					if (potion == 0) score[3] += 30;               // �´� ����϶��� ���� �ο�
				}
				else if (warehouse[map][ny + dy][nx + dx] == 5) { 
					warehouse[map][ny + dy][nx + dx] = 0;
					cnt--;
					if (potion == 1) score[3] += 30;
				}
				else if (warehouse[map][ny + dy][nx + dx] == 6 || warehouse[map][ny + dy][nx + dx] == 7) { 
					warehouse[map][ny + dy][nx + dx] = 0;
					cnt--;
					score[3] += 30;
				}
				nx += dx;    // ������ ���Ͽ� ������ġ ����
				ny += dy;
			}
			break;
		}		
		if (cnt == 0) {      // ��� 3�� �����ϸ� ����
			score[3] += 10;  // ���� �ð��ȿ� ������ �߰� ���� 
			break;
		}

		new_time = clock();
		if (new_time - start_time >= 30000) break;
	}
	Sleep(500);
	class4();
}


/// 4����

// Ÿ�� ������ ���� ����ü
typedef struct target {
	int state;          // UP, DOWN
	int pos_x;
	int pos_y;
	clock_t down_time;  
	clock_t	up_time;    
	clock_t	past_time;  // ���� �ð�	
} target;

target dementors[5];

// ������ ��� �Լ�
void print_wand(x, y) {
	gotoxy(x, y); printf("/");
	gotoxy(x - 1, y + 1); printf("/");
	gotoxy(x - 2, y + 2); printf("/");
	gotoxy(x - 3, y + 3); printf("/");
	gotoxy(x - 4, y + 4); printf("/");
}

void delete_wand(x, y) {
	gotoxy(x, y);     printf(" ");
	gotoxy(x - 1, y + 1); printf(" ");
	gotoxy(x - 2, y + 2); printf(" ");
	gotoxy(x - 3, y + 3); printf(" ");
	gotoxy(x - 4, y + 4); printf(" ");
}

// ���� �Լ�. �罿�Դϴ�
void print_patronus(x, y) { 
	gotoxy(x - 2, y);     printf(" V V");
	gotoxy(x - 2, y + 1); printf("(   )");
	gotoxy(x - 2, y + 2); printf("/   ��");
	gotoxy(x - 2, y + 3); printf("(  �� )");
	gotoxy(x - 2, y + 4); printf(" ��  ��");
}

void delete_patronus(x, y) {
	gotoxy(x - 4, y);     printf("         ");
	gotoxy(x - 4, y + 1); printf("         ");
	gotoxy(x - 4, y + 2); printf("         ");
	gotoxy(x - 4, y + 3); printf("         ");
	gotoxy(x - 4, y + 4); printf("         ");
}

// Ÿ�� ��� �Լ�. ������Դϴ�
void print_dementor(x, y) {
	gotoxy(x - 2, y); printf(" ()");
	gotoxy(x - 3, y + 1);     printf(" /  |");
	gotoxy(x - 3, y + 2); printf("/   /");
	gotoxy(x - 3, y + 3); printf("/)()/");
}

void delete_dementor(x, y) {
	gotoxy(x - 3, y); printf("     ");
	gotoxy(x - 3, y + 1);     printf("     ");
	gotoxy(x - 3, y + 2); printf("     ");
	gotoxy(x - 3, y + 3); printf("     ");
}

void exam4() {
	system("cls");
	print_edge();

	int pos[5] = { 41,54,67,15,28 };  // x��ǥ�� ����
	int w_y = 22;                     // wand y��ǥ��
	int w_x = 0, d_x = 0;             // pos �ε��� �� x��ǥ��	
	int cnt4 = 0;                      // ���� Ƚ��

	clock_t start_time, new_time, curr_time;
	start_time = clock();

	for (i = 0; i < 5; i++) {  // Ÿ�� �ʱ�ȭ
		dementors[i].state = rand() % 2;
		dementors[i].pos_x = pos[d_x++];
		dementors[i].pos_y = 10;
		dementors[i].down_time = rand() % 6000 + 100;
		dementors[i].up_time = rand() % 4000 + 100;
		dementors[i].past_time = start_time;
	}
	dementors[1].pos_y = 4;
	dementors[4].pos_y = 4;

	while (1) {
		for (i = 0; i < 5; i++) {  // Ÿ�� ����	
			if (dementors[i].state == 1) {  // UP
				print_dementor(dementors[i].pos_x, dementors[i].pos_y);
			}
			else delete_dementor(dementors[i].pos_x, dementors[i].pos_y);  // DOWN
		}

		print_wand(pos[w_x], w_y);

		gotoxy(62, 1);
		printf("���� Ƚ�� : %2d", cnt4);

		if (_kbhit()) { // ��� �Է��� �����ʾƵ� Ÿ�� ���� ����
			key = _getch();
			delete_wand(pos[w_x], w_y);

			switch (key) {
			case LEFT:
				w_x--;
				if (w_x < 0) w_x = 4;
				break;
			case RIGHT:
				w_x++;
				if (w_x > 4) w_x = 0;
				break;

			case SPACE: // ����
				print_patronus(pos[w_x], dementors[w_x].pos_y + 2);  // ���� ���� ��
				Sleep(400);

				delete_patronus(pos[w_x], dementors[w_x].pos_y + 2);
				print_patronus(pos[w_x], dementors[w_x].pos_y);
				Sleep(400);

				delete_patronus(pos[w_x], dementors[w_x].pos_y);
				for (i = 0; i < 5; i++) {
					if (dementors[i].state == 1 && pos[w_x] == dementors[i].pos_x) {  // ������ ��ġ�� Ÿ���� �־����� Ž��
						cnt4++;
						dementors[i].state = 0;  // �¾����� �ٷ� DOWN ���·� ��ȯ
						break;  // �ѹ��� �ϳ��� ���� �� �ֱ� ������ ã���� ��������
					}
				}
				break;
			}
		}
		new_time = clock();
		if (new_time - start_time >= 30000) break;

		curr_time = clock();

		for (i = 0; i < 5; i++) {  // Ÿ�� ���� ����
			switch (dementors[i].state) {
			case 0: // DOWN
				if (curr_time - dementors[i].past_time > dementors[i].down_time) {
					dementors[i].past_time = curr_time;
					dementors[i].down_time = rand() % 6000 + 100;
					dementors[i].up_time = rand() % 4000 + 100;
					dementors[i].state = 1;
				}
				break;
			case 1: // UP
				if (curr_time - dementors[i].past_time > dementors[i].up_time) {
					dementors[i].past_time = curr_time;
					dementors[i].state = 0;
				}
				break;
			}
		}
	}
	if (cnt4 >= 22) score[4] += 100;
	else if (cnt4 > 17) score[4] += 80;
	else if (cnt4 > 10) score[4] += 60;
	else score[4] += 40;

	Sleep(500);
	class5();
}


/// 5����

//��輱 ��� �Լ�3
void print_edge5() {
	for (i = 0; i < EX5_R / 2; i++) {
		gotoxy(i * 2, 0); printf("��");
		gotoxy(i * 2, EX5_C - 1); printf("��");
	}

	for (i = 1; i < EX5_C - 1; i++) {
		gotoxy(0, i); printf("��");
		gotoxy(EX5_R - 2, i); printf("��");
	}
}

char* mole[MOLE_SIZE] = { "�� ��",
						  "(^ ^)",
						  "O   O" }; //����


char* bucket[BUCKET_SIZE] = { "��������",
							 "������",
							"��������" }; //������

char* blank[BUCKET_SIZE] = { "       ","        " ,"        " };

POINT xy_hole[HOLE_SIZE] = { { 4, 5 }, { 12, 5 }, { 20, 5 },
							 { 4, 10 }, { 12, 10 }, { 20, 10 },
							 { 4, 15 }, { 12, 15 }, { 20, 15 } };//Ȧ�� ��ġ�� ������


void genMole(int m[]) {
	int pos, exit = 0, sum = 0;

	while (!exit) {
		pos = rand() % HOLE_SIZE;
		if (m[pos] == 0) {
			m[pos] = MOLE_APPEAR_TIME;
			break;
		} //Ȧ�� ������ �������� �������� ����


		for (int i = 0; i < HOLE_SIZE; i++) {
			if (m[i] > 0) {
				sum++;
				if (sum == HOLE_SIZE) return 0;
			}//��� Ȧ�� ������ ���� ���
		}
	}
}


int isHit(int m[], int pos) {
	return (pos >= 0 && m[pos] > 0);
} //pos�� ������ ������ ���Ͻ�Ų��


void checkMoleTimer(int m[]) {
	for (i = 0; i < HOLE_SIZE; i++) {
		if (m[i] > 0) m[i]--;
	}
}//��������ð�


void checkHammerTimer(int h[]) {
	for (i = 0; i < HOLE_SIZE; i++) {
		if (h[i] > 0) h[i]--;
	}
}//������ ����ð�


int keyPlayer(char key, int h[]) {
	int hit_pos = -1;

	for (i = 0; i < HOLE_SIZE; i++) h[i] = 0; // CLEAR�� ���·� ����

	switch (key) {
	case '7':
		h[0] = BUCKET_APPEAR_TIME; hit_pos = 0; break;
	case '8':
		h[1] = BUCKET_APPEAR_TIME; hit_pos = 1; break;
	case '9':
		h[2] = BUCKET_APPEAR_TIME; hit_pos = 2; break;
	case '4':
		h[3] = BUCKET_APPEAR_TIME; hit_pos = 3; break;
	case '5':
		h[4] = BUCKET_APPEAR_TIME; hit_pos = 4; break;
	case '6':
		h[5] = BUCKET_APPEAR_TIME; hit_pos = 5; break;
	case '1':
		h[6] = BUCKET_APPEAR_TIME; hit_pos = 6; break;
	case '2':
		h[7] = BUCKET_APPEAR_TIME; hit_pos = 7; break;
	case '3':
		h[8] = BUCKET_APPEAR_TIME; hit_pos = 8; break;
	} //���� Ű��ġ�� ���̽����� ����
	return hit_pos;
}

void updateHole(int m[]) {
	int str_pos[] = { 7, 8, 9, 4, 5, 6, 1, 2, 3 };

	for (i = 0; i < HOLE_SIZE; i++) {
		// ȭ�鿡 ������ �����ϸ� ǥ��
		if (m[i] > 0) {
			for (j = 0; j < MOLE_SIZE; j++) {
				gotoxy(xy_hole[i].x, xy_hole[i].y + j);
				printf("%s", mole[j]);
			}
		}
		// ȭ�鿡 Ȧ ��ȣ ǥ��
		gotoxy(xy_hole[i].x, xy_hole[i].y + MOLE_SIZE);
		printf("[ %d]", str_pos[i]);
	}
}

void deleteHole(int m[]) {
	int str_pos[] = { 7, 8, 9, 4, 5, 6, 1, 2, 3 };

	for (i = 0; i < HOLE_SIZE; i++) {
			for (j = 0; j < MOLE_SIZE; j++) {
				gotoxy(xy_hole[i].x, xy_hole[i].y + j);
				printf("     ", mole[j]);
			}
	}
}

void updateHammer(int h[]) {
	for (i = 0; i < HOLE_SIZE; i++) {
		if (h[i] > 0) {
			RED;
			for (j = 0; j < BUCKET_SIZE; j++) {
				gotoxy(xy_hole[i].x, xy_hole[i].y + j - MOLE_SIZE);
				printf("%s", bucket[j]);
			}// Ȧ�� ������ ������
		}
	}
	WHITE;
}// ������ǥ��

void deleteHammer(int h[]) {
	for (i = 0; i < HOLE_SIZE; i++) {
			for (j = 0; j < BUCKET_SIZE; j++) {
				gotoxy(xy_hole[i].x, xy_hole[i].y + j - MOLE_SIZE);
				printf("%s", blank[j]);
			}
	}
	
}// ������ ����

void exam5() {
	system("cls");

	int mole_hole[HOLE_SIZE] = { 0, };
	int hammer_hole[HOLE_SIZE] = { 0, };
	int closeness = 0, hit_pos, time_count = 0;
	double game_time; // �ð��� �Ǽ������� ����
	game_time = GAME_TIME; // ���ѽð�

	start_time = clock();
	print_edge5();
	while (1) {
		
		gotoxy(EX5_R + 1, 2); printf("ģ�е� �ױ� : %3d", closeness);


		game_time -= 0.1;	// 0.1 �ʾ� ����
		if (game_time <= 0.0) break;

		// ��� ���� Ÿ�̸� üũ
		checkMoleTimer(mole_hole);
		checkHammerTimer(hammer_hole);

		time_count++;
		if (time_count == GEN_TIME)
		{
			// ���� ����
			genMole(mole_hole);
			time_count = 0;
		}

		if (_kbhit()) { // ��� �Է��� �޾��� ��
			key = _getch();
			hit_pos = keyPlayer(key, hammer_hole);
			if (hit_pos != MISS) { //MISS ���� ����
				if (isHit(mole_hole, hit_pos)) {
					closeness += 3; //�������� ���̸� �ָ� ��������
					mole_hole[hit_pos] = 0; // ������ ���� ���·�				
				}
			}
					}
		
		deleteHole(mole_hole);
		// ����, ��Ʈ ���
		updateHole(mole_hole);
		updateHammer(hammer_hole);

		Sleep(100);
		deleteHammer(mole_hole);

		new_time = clock();
		if (new_time - start_time >= 30000) break;
	}
	if (closeness >= 22) score[5] += 100;
	else if (closeness > 17) score[5] += 80;
	else if (closeness > 10) score[5] += 60;
	else score[5] += 40;

	the_end();
}

void main() {
	soundtrack();

	srand((unsigned int)time(NULL));
	int menu = 1;
	hideCursor();

	title();
	while (1) {
		gotoxy((menu * 19), 29);
		printf("��");
		key = _getch();
		gotoxy((menu * 19), 29);
		printf("  ");

		switch (key) {
		case LEFT:
			menu--;
			if (menu <= 0)
				menu = 3;
			break;
		case RIGHT:
			menu++;
			if (menu >= 4)
				menu = 1;
			break;
		case SPACE:
			if (menu == 1) game_intro();
			else if (menu == 2) game_info();
			else rank_show();
			break;
		}
	}
}