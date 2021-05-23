#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <mmsystem.h>  // mciSendString() 
#pragma comment (lib, "winmm.lib") //MCI


// 콘솔창 글자에 색 입히기 
#define col GetStdHandle(STD_OUTPUT_HANDLE)					// 콘솔창의 핸들정보를 받아옵니다.
#define WHITE		SetConsoleTextAttribute(col, 0x000f)	// 흰색
#define YELLOW		SetConsoleTextAttribute(col, 0x000e)	// 노란색
#define PURPLE		SetConsoleTextAttribute(col, 0x000d)	// 자주색
#define RED			SetConsoleTextAttribute(col, 0x000c)	// 빨간색
#define SKY			SetConsoleTextAttribute(col, 0x000b)	// 하늘색
#define YELGREEN	SetConsoleTextAttribute(col, 0x000a)	// 연두색
#define BLUE		SetConsoleTextAttribute(col, 0x0009)	// 파란색
#define GOLD		SetConsoleTextAttribute(col, 0x0006)	// 금색
#define VIOLET		SetConsoleTextAttribute(col, 0x0005)	// 보라색
#define BLOOD		SetConsoleTextAttribute(col, 0x0004)	// 피색
#define BLUE_GREEN	SetConsoleTextAttribute(col, 0x0003)	// 청녹색
#define GREEN		SetConsoleTextAttribute(col, 0x0002)	// 녹색

#define LEFT   75
#define RIGHT  77
#define UP     72
#define DOWN   80
#define SPACE  32

#define WINDOW_ROW  40 
#define WINDOW_COL  30

#define EX2_R   60   // 2교시 창 크기
#define EX2_C   22	

#define MAX_BLOCK   15	// 블럭의 최대수
#define MAX_BULLET   2	// 총알의 종류
#define CON_CENTER_W_STR(msg)	((EX2_R-strlen(msg))/2)	// 콘솔창의 중앙(가로) x좌표

#define EX3_R  20   // 3교시 창 크기
#define EX3_C  15

#define EX5_R  30   // 5교시 창 크기
#define EX5_C  30

#define MOLE_SIZE			3	// 동물 세로크기
#define BUCKET_SIZE			3	// 먹이통 세로크기
#define HOLE_SIZE			9	// 홀의 크기
#define MOLE_APPEAR_TIME	15	// 동물 등장시간(1500ms)
#define BUCKET_APPEAR_TIME	12	//  먹이통시간(1000ms)
#define MISS				-1// 실수
#define GEN_TIME			5	// 0.5초 (동물 등장간격)
#define GAME_TIME			30.0


char key;
int score[5];
int i, j;
int rank[5] = { 0,0,0,0,0 };  // 1위부터 5위까지 등록
clock_t start_time, new_time;

typedef enum { Flitwick, Hooch, Snape, Moody, Hagrid } PROFESSOR;


void gotoxy(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//사용자 위치지정 함수
void gotoxyHP(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 커서 숨겨주는 함수
void hideCursor() {
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

// 배경음악 실행 함수
void soundtrack() {
	MCI_OPEN_PARMS mciOpen; // MCI_OPEN_PARAMS 구조체 변수 
	mciOpen.lpstrDeviceType = L"mpegvideo"; // mp3 형식 
	mciOpen.lpstrElementName = L"Prologue.mp3"; // 파일이름
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);

	MCI_PLAY_PARMS mciPlay; // 재생
	mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
}


// 함수 선언
void class1();
void exam1();
void exam2();
void exam3(int potion);
void exam4();
void exam5();



// 경계선 출력 함수
void print_edge() {
	for (i = 0; i < WINDOW_ROW; i++) {
		gotoxy(i * 2, 0);
		printf("▦");
		gotoxy(i * 2, WINDOW_COL - 1);
		printf("▦");
	}
	for (i = 1; i < WINDOW_COL; i++) {
		gotoxy(0, i);
		printf("▦");
		gotoxy((WINDOW_ROW - 1) * 2, i);
		printf("▦");
	}
}

// 메인화면 함수
void title() {
	system("cls");
	GOLD;
	printf("\n");
	printf("\n");
	printf("                                          ■■■                                    \n");
	printf("           ■                ■■          ■   ■                                  \n");
	printf("     ■    ■   ■■   ■■  ■ ■         ■   ■         ■                       \n");
	printf("     ■    ■       ■ ■ ■ ■     ■   ■■   ■ ■■  ■■■  ■          ■■   \n");
	printf("     ■  ■■■ ■■■ ■    ■ ■  ■   ■■ ■  ■  ■   ■  ■■■  ■■  ■ ■  \n");
	printf("   ■■■  ■   ■  ■ ■    ■   ■       ■     ■  ■   ■    ■   ■  ■ ■     \n");
	printf("     ■    ■   ■■■ ■        ■      ■■     ■  ■   ■    ■   ■■■ ■     \n");
	printf("     ■    ■              ■■■         ■        ■     ■    ■   ■     ■     \n");
	printf("           ■                             ■                 ■  ■    ■■         \n");
	printf("                                          ■                      ■■              \n");
	printf("                                          ■     AND THE                            \n");
	printf("\n");
	printf("\n");
	printf("     ■  ■  ■  ■  ■■■■     ■     ■■■    ■■■    ■  ■    ■   ■■■   \n");
	printf("     ■  ■  ■  ■       ■    ■  ■   ■    ■  ■    ■  ■  ■■  ■  ■        \n");
	printf("     ■  ■  ■  ■     ■     ■■■■  ■■■    ■    ■  ■  ■ ■ ■  ■  ■■  \n");
	printf("       ■  ■    ■   ■       ■    ■  ■    ■  ■    ■  ■  ■  ■■  ■    ■  \n");
	printf("       ■  ■    ■  ■■■■  ■    ■  ■    ■  ■■■    ■  ■    ■   ■■■   \n");
	printf("\n");
	printf("                             ■■■  ■■■  ■■■ ■■■         \n");
	printf("                               ■    ■      ■       ■           \n");
	printf("                               ■    ■■■  ■■■   ■           \n");
	printf("                               ■    ■          ■   ■           \n");
	printf("                               ■    ■■■  ■■■   ■           \n");

	gotoxy(22, 29); printf("게임 시작");
	gotoxy(41, 29); printf("게임 설명");
	gotoxy(60, 29); printf("순위 확인");
	gotoxy(0, 30); printf(" "); //30줄까지 화면에 나타내기 위해서
}

// 게임 설명 메뉴 함수
void game_info() {
	system("cls");
	WHITE;
	print_edge();

	gotoxy(9, 8);	printf("해리포터가 5개 과목의 시험을 보면서 점수를 획득하는 게임입니다.");
	Sleep(800);
	gotoxy(10, 10);	printf("이동은 방향키로, 말을 걸고싶으면 스페이스바를 누르면 됩니다.");
	Sleep(800);
	gotoxy(14, 12);	printf("각 교수님들의 설명을 읽고 게임을 진행 하면 됩니다.");
	Sleep(800);
	gotoxy(14, 14);	printf("게임점수가 상위 5위 안에 들 경우 랭킹에 등록 됩니다.");
	Sleep(800);
	gotoxy(9, 20);	GOLD; printf("해리포터가 되어서 호그와트 시험을 보고 높은 점수를 받아보세요~");
	
	_getch();
	title();
}

// 순위 확인 메뉴 함수
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
		printf("%d위     %3d점", i + 1, rank[i]);
	}

	_getch();
	title();
}

void aplus(int x, int y) {
	BLOOD;
	gotoxy(x, y);	   printf("                     ■");
	gotoxy(x, y + 1);  printf("                     ■");
	gotoxy(x, y + 2);  printf("        ■       ■■■■■");
	gotoxy(x, y + 3);  printf("       ■■          ■");
	gotoxy(x, y + 4);  printf("      ■  ■         ■");
	gotoxy(x, y + 5);  printf("     ■    ■          ");
	gotoxy(x, y + 6);  printf("    ■      ■         ");
	gotoxy(x, y + 7);  printf("   ■■■■■■        ");
	gotoxy(x, y + 8);  printf("  ■          ■       ");
	gotoxy(x, y + 9);  printf(" ■            ■      ");
	gotoxy(x, y + 10); printf("■              ■     ");
}

// 최종 결과 함수
void the_end() {
	system("cls");
	WHITE;
	print_edge();

	gotoxy(34, 4);
	printf("WIZARDING TEST");
	
	for (i = 1; i <= 5; i++) {
		gotoxy(16, 6 + 2 * i);
		printf("%d 교시  :    %3d점", i, score[i]);
		score[0] += score[i];
	}
	
	gotoxy(14, 20);
	printf("최종 점수 :    %3d점", score[0]);

	gotoxy(16, 22);
	printf("학   점 :       ");

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


// 대화창 출력 함수
void print_chat() {
	gotoxy(9, 21); printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓");
	gotoxy(8, 22); printf("∥");
	gotoxy(8, 23); printf("∥");
	gotoxy(8, 24); printf("∥");
	gotoxy(8, 25); printf("∥");
	gotoxy(8, 26); printf("∥");
	gotoxy(70, 22); printf("∥");
	gotoxy(70, 23); printf("∥");
	gotoxy(70, 24); printf("∥");
	gotoxy(70, 25); printf("∥");
	gotoxy(70, 26); printf("∥");
	gotoxy(9, 27); printf("〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓〓");
}

// 대화창 자리 지워주는 함수
void delete_chat() {
	for (j = 21; j < 28; j++) {
		for (i = 8; i < 72; i++) {
			gotoxy(i, j);
			printf(" ");
		}
	}
}

// 대화 지워주는 함수
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

	// 복도
	for (i = 1; i < WINDOW_COL - 1; i++) {
		gotoxy(29, i); printf("｜");
		gotoxy(49, i); printf("｜");
	}
	BLUE_GREEN;
	gotoxy(35, 9);	printf("   / ＼");
	gotoxy(35, 10); printf("  /    ＼");
	gotoxy(35, 11);	printf("∠________＞");
	WHITE;
	gotoxy(35, 12);	printf("(;; Ð--Ð)");

	gotoxyHP(38, 28); printf("○-○");
	Sleep(300);

	// 이동
	gotoxy(38, 28); printf("     ");
	for (i = WINDOW_COL - 2; i > 13; i--) {
		gotoxyHP(38, i); printf("○-○");
		Sleep(90);
		gotoxyHP(38, i); printf("     ");
	}

	// 고정
	gotoxyHP(38, 13); printf("○-○");
	Sleep(300);

	delete_chat();
	print_chat();
	gotoxy(11, 23); printf("덤블도어 :");
	gotoxy(22, 23); printf("오늘이 표준 마법사 시험이 있는 날이구나");
	gotoxy(22, 24); printf("준비는 잘 하였니?");
	Sleep(2000);

	delete_dialog();
	gotoxy(11, 23); printf("해리포터 :");
	gotoxy(22, 23); printf("......");
	Sleep(2000);

	gotoxy(11, 23); printf("덤블도어 :");
	gotoxy(22, 23); printf("흠.. 1교시는 마법주문시험, 2교시는 비행시험,");
	Sleep(1000);
	gotoxy(22, 24); printf("3교시는 마법약시험, 4교시는 어둠의마법방어술시험");
	Sleep(1000);
	gotoxy(22, 25); printf("5교시는 신비한 동물 돌보기 시험이 있구나.");
	Sleep(1000);

	delete_dialog();
	gotoxy(22, 23); printf("시험 방식은 교수님마다 설명해주실거다.");
	gotoxy(22, 24); printf("그럼 좋은 결과 있기를...");
	gotoxy(22, 25); printf("행운을 비네.");
	Sleep(2000);

	system("cls");

	print_edge();
	for (i = 1; i < WINDOW_COL - 1; i++) {
		gotoxy(29, i); printf("｜");
		gotoxy(49, i); printf("｜");
	}
	gotoxyHP(38, 13); printf("○-○");

	delete_chat();
	print_chat();
	gotoxy(11, 23); printf("해리포터 :");
	gotoxy(22, 23); printf("!!!!!!");
	Sleep(1000);

	delete_chat();
	for (i = 1; i < WINDOW_COL - 1; i++) {
		gotoxy(29, i); printf("｜");
		gotoxy(49, i); printf("｜");
	}

	gotoxyHP(38, 13); printf("     ");
	for (i = 12; i > 0; i--) {
		gotoxyHP(38, i); printf("○-○");
		Sleep(90);
		gotoxyHP(38, i); printf("     ");
	}

	class1();
}


void print_class(int prof) {
	print_edge();

	// 칠판
	gotoxy(7, 3);	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(6, 4); 	printf("｜");
	gotoxy(73, 4); 	printf("｜");
	gotoxy(6, 5); 	printf("｜");
	gotoxy(73, 5); 	printf("｜");
	gotoxy(6, 6); 	printf("｜");
	gotoxy(73, 6); 	printf("｜");
	gotoxy(7, 7);	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	
	// 책상
	gotoxy(8, 11);	printf("┏━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(8, 12); 	printf("｜");
	gotoxy(32, 12); printf("｜");
	gotoxy(8, 13);	printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(8, 14);	printf("┏━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(8, 15); 	printf("｜");
	gotoxy(32, 15); printf("｜");
	gotoxy(8, 16);	printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(8, 17);	printf("┏━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(8, 18); 	printf("｜");
	gotoxy(32, 18); printf("｜");
	gotoxy(8, 19);	printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(47, 11);	printf("┏━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(47, 12); printf("｜");
	gotoxy(71, 12); printf("｜");
	gotoxy(47, 13);	printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(47, 14);	printf("┏━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(47, 15); printf("｜");
	gotoxy(71, 15); printf("｜");
	gotoxy(47, 16);	printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");
	gotoxy(47, 17);	printf("┏━━━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(47, 18); printf("｜");
	gotoxy(71, 18); printf("｜");
	gotoxy(47, 19);	printf("┗━━━━━━━━━━━━━━━━━━━━━━━┛");

	//교수 캐릭터
	switch (prof) {
	case Flitwick:
		gotoxy(36, 7); 	printf("/   ＼");
		gotoxy(35, 8); 	printf("/      ＼");
		gotoxy(34, 9); 	printf("( ;;＇ㅿ＇) / ");
		break;
	case Hooch:
		gotoxy(37, 7); 	printf("/   ＼");
		gotoxy(36, 8); 	printf("/      ＼");
		gotoxy(31, 9); 	printf("∋─ (  ˚ ˇ˚)");
		break;
	case Snape:
		gotoxy(37, 7); 	printf("/   ＼");
		gotoxy(36, 8); 	printf("/      ＼");
		gotoxy(35, 9); 	printf("(  ｀ㅂ´ ) /");
		break;
	case Moody:
		gotoxy(37, 7); 	printf("/   ＼");
		gotoxy(36, 8); 	printf("/      ＼");
		gotoxy(35, 9); 	printf("(  Φ  ㅇ )");
		gotoxy(39, 10); printf("⌒");
		break;
	case Hagrid:
		gotoxy(36, 6); 	printf("§⌒⌒⌒§");
		gotoxy(35, 7);  printf("§ ㆆ  ㆆ §");
		gotoxy(34, 8); 	printf("§ωωㅁωω§");
		gotoxy(36, 9); 	printf("ωωωωω");
		break;
	}

	int x = 38, y = 28;

	//지정 위치에서 선택하기 전까지 반복
	while (y != 10 || key != SPACE) {
		gotoxyHP(x, y); printf("○-○");

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

	gotoxyHP(x, y); printf("○-○");
	print_chat();
}

void class1() {
	system("cls");

	print_class(Flitwick);
	gotoxy(11, 23); printf("플리트윅 :");
	gotoxy(22, 23); printf("해리포터 군. 이번 시험은 마법 주문 시험이란다.");
	gotoxy(22, 24); printf("문제는 총 5문제이고, 맞는 번호를 누르면 된단다.");
	Sleep(2000);

	delete_dialog();
	gotoxy(22, 23); printf("그동안 수업 열심히 들었으니까 잘할 수 있겠지?");

	Sleep(3000);
	exam1();
}

void class2() {
	system("cls");

	print_class(Hooch);
	gotoxy(12, 23); printf("후치여사 :");
	gotoxy(23, 23); printf("포터구나. 이번 시험은 비행 시험이란다.");
	gotoxy(23, 24); printf("30초 안에 날아다니는 스니치 10개를 잡으면 된다.");
	gotoxy(23, 25); printf("물론 블러저도 날아오니까 잘 피하고~");
	Sleep(1000);

	delete_dialog();
	gotoxy(23, 23); printf("30초 안에 날아다니는 스니치 10개를 잡으면 된다.");
	gotoxy(23, 24); printf("물론 블러저도 날아오니까 잘 피하고~");
	gotoxy(23, 25); printf("퀴디치 선수도 했었으니까 잘할거라고 생각 되구나");

	Sleep(3000);
	exam2();
}

void class3() {
	system("cls");

	int potion = rand() % 2;
		
	print_class(Snape);
	gotoxy(11, 23); printf("스네이프 :");
	gotoxy(22, 23); printf("곧 시험을 시작하겠다.");
	gotoxy(22, 24); printf("30초안에 칠판에 적힌 물약을 만드는데 필요한");
	gotoxy(22, 25); printf("재료를 찾아와라.");
	Sleep(1000);

	gotoxy(30, 5);
	if (potion == 0) { BLUE; printf("♠"); }
	else { VIOLET; printf("♣"); }	
	WHITE; printf("   =   ?  +  ?  +  ?");

	delete_dialog();
	gotoxy(22, 23);	printf("단 3개만 가져올것. 과연 너가 잘 찾아 가지고");
	gotoxy(22, 24); printf("올지는 의문이구나");
	gotoxy(22, 25); printf("뭘 기다리고 있는거냐! 빨리 시작하지않고");

	Sleep(3000);
	exam3(potion);
}

void class4() {
	system("cls");

	print_class(Moody);
	gotoxy(11, 23); printf(" 무   디 :");
	gotoxy(22, 23); printf("이번 시험은 디멘터를 물리치는 시험이다.");
	gotoxy(22, 24); printf("제한 시간은 30초. 각자 자신의 패트로누스 동물을");
	gotoxy(22, 25); printf("불러내서 처리하면 된다.");
	Sleep(2000);

	delete_dialog();
	gotoxy(22, 23); printf("볼드모트가 살아있는 동안 이정도의 마법은 잘 할");
	gotoxy(22, 24); printf("수 있어야 한다. ");
	gotoxy(22, 25); printf("특히 해리포터라면 기대해봐도 되겠지.");

	Sleep(3000);
	exam4();
}

void class5() {
	system("cls");

	print_class(Hagrid);
	gotoxy(11, 23); printf("해그리드 :");
	gotoxy(22, 23); printf("오 해리야. 이제 마지막시험이구나~");
	gotoxy(22, 24); printf("이번 시험은 정말 쉽단다. 흩어져 있는 동물들을");
	gotoxy(22, 25); printf("찾아서 먹이를 주고 친밀도를 쌓으면 된단다.");
	Sleep(800);
	delete_dialog();
	gotoxy(22, 23); printf("이번 시험은 정말 쉽단다. 흩어져 있는 동물들을");
	gotoxy(22, 24); printf("찾아서 먹이를 주고 친밀도를 쌓으면 된단다.");
	gotoxy(22, 25); printf("먹이를 많이 줄수록 좋은 점수를 받을 수 있단다.");
	Sleep(2000);

	delete_dialog();
	gotoxy(22, 23); printf("그리고 이번에 데려온 동물이 하나 있는데 보여주고");
	gotoxy(22, 24); printf("싶구나. 시험이 끝나면 론이랑 헤르미온느랑 같이");
	gotoxy(22, 25); printf("오두막으로 한번 찾아오거라. 어쩌구 저쩌구......");

	Sleep(3000);
	exam5();
}


/// 1교시

 // 문제 정보에 대한 구조체
typedef struct {
	char *question;
	int *choice[2];
	int answer;
	BOOL already;
} QUESTION;

QUESTION question_data[] = {
	   { "패트로누스를 소환해 디멘트를 물리칠 때 사용하는 주문은?\n","엑스펠리아르무스","익스펙토 패트로눔",2, FALSE},
	   { "먼거리에 있는 물체를 소환할 때 사용하는 주문은?\n","레파로","익스펙토 패트로눔", 1, FALSE},
	   { "물체를 공중으로 떠오르게 하는 공중부양 주문은?\n","윙가르디움 레비오사","윙가르디움 레비오우사", 2, FALSE},
	   { "섹튬 셈프라로 다친 부위를 치료하는 주문은?\n","비페라 이바네스카","볼네라 사넨투르", 2, FALSE},
	   { "상대방의 기억을 수정하거나 지우는 주문은?\n","레질리먼시","오블리비아테", 2, FALSE },
	   { "용서받지 못할 저주 중 하나로 살인 저주인 주문은?\n","아바다 케다브라","크루시오", 1 ,FALSE },
	   { "물체를 폭파시킬 때 사용하는 주문은?\n","디센디움","봄바르다", 2, FALSE  },
	   { "문을열거나 무너뜨릴 때 사용하는 주문은?\n","디센도","레파로", 1,FALSE },
	   { "부러진 뼈를 붙일 때 사용하는 주문은?\n","엑스펄소","아바다케다브라", 1, FALSE },
	   { "용서받지 못할 저주 중 하나로 상대를 복종시키는 주문은?\n","아바다케다브라","임페리오" , 2, FALSE },
	   { "몸이 마비되어 정지시킬 때 사용하는 주문은?\n","임페디멘타","임페르비우스", 1, FALSE }
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

		gotoxy(16, 7); printf("%d. %s", sel + 1, question_data[selectnum].question);  // 문제

		for (i = 0; i < 2; i++) {  // 선택지
			gotoxy(19, 11 + i * 3);
			printf("(%d) %s", i + 1, question_data[selectnum].choice[i]);
		}

		gotoxy(18, 19); printf("(1), (2) 중 하나를 선택하세요  :  ");
		key = _getch();
		printf("%c", key);

		key -= 0x30;  // key는 정수형이라 입력받은 값에서 변환시켜줘야함						
		if (key == question_data[selectnum].answer) score[1] += 20;

		Sleep(500);
	}
	class2();
}


// 2교시

//경계선 출력 함수2
void print_edge2() {
	for (i = 0; i < EX2_R / 2; i++) {
		gotoxy(i * 2, 0); printf("▦");
		gotoxy(i * 2, EX2_C - 1); printf("▦");
	}

	for (i = 1; i < EX2_C - 1; i++) {
		gotoxy(0, i); printf("▦");
		gotoxy(EX2_R - 2, i); printf("▦");
	}
}

// 장애물 정보에 대한 구조체
typedef struct {
	int    type;   // 종류
	int    width;  // 블럭의 크기
	int    height;
	int    x;      // 출력 좌표
	double y;
	double speed;  // 속도
} BULLET_BLOCK;

// 사용자 정보에 대한 구조체
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

// 장애물 좌표 및 속도 재설정 함수
void reset_block(BULLET_BLOCK* block) {
	int interval = rand() % 5 + 2;

	block->x = rand() % (EX2_R - 6) + 2;  // 3 ~ (EX2_R - 6 + 3)	
	if (block->x % 2 == 1) block->x++;   // x좌표가 홀수면 짝수로 변환

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

// 초기화 함수
void init2() {	
	for (i = 0; i < MAX_BLOCK; i++) {  // 장애물 초기화
		bullet_block[i].width = 2;
		bullet_block[i].height = 1;
		reset_block(&bullet_block[i]);
	}

	gamer.shape = "○-○";  // 사용자 초기화
	gamer.width = 5;
	gamer.height = 1;
	gamer.x = 27;
	gamer.y = EX2_C - 4;
}

//장애물 지워주는 함수
void delete_bullet() {
	for (i = 0; i < MAX_BLOCK; i++) {
		gotoxy(bullet_block[i].x, (int)bullet_block[i].y);
		printf("  ");
	}
}

// 장애물 좌표 및 출력 갱신 함수
void update_bullet() {
	for (i = 0; i < MAX_BLOCK; i++) {		
		bullet_block[i].y += bullet_block[i].speed;  // 이동(하강)

		if (bullet_block[i].y > 1) {  // y좌표가 경계선 아래이면			
			if (bullet_block[i].y > EX2_C - 1) {  // 화면 밖을 벗어나면 재설정		
				reset_block(&bullet_block[i]);
				continue;
			}
			
			switch (bullet_block[i].type) {
			case OBSTACLE:
				gotoxy(bullet_block[i].x, (int)bullet_block[i].y);
				printf("○");
				break;
			case SNICH:
				YELLOW;
				gotoxy(bullet_block[i].x, (int)bullet_block[i].y);
				printf("●");
				WHITE;  // 장애물의 색상만 변하도록 
				break;
			}
		}
	}
}

// 사용자 이동 함수
void update_gamer(char key) {
	gotoxy(gamer.x, gamer.y);
	printf("     ");

	// 이동 크기를 구한다. 화면 밖으로 나가지 못하도록 계산하여 고정
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
		gotoxy(62, 2);  // 정보 출력
		printf("잡은 스니치 개수");
		gotoxy(62, 3);  // 정보 출력
		printf("● : %2d", cnt2);
		WHITE;
		
		if (_kbhit()) { // 어떠한 입력을 받았을 때
			key = _getch();
			update_gamer(key);
		}		

		gotoxy(gamer.x, gamer.y);
		printf("%s", gamer.shape);

		delete_bullet();
		update_bullet();
				
		for (i = 0; i < MAX_BLOCK; i++) {  // 충돌체크
			SetRect(&GamerRect, gamer.x, gamer.y, gamer.x + gamer.width, gamer.y + gamer.height);
			SetRect(&BulletRect, bullet_block[i].x, (int)bullet_block[i].y, bullet_block[i].x + bullet_block[i].width, (int)bullet_block[i].y + bullet_block[i].height);

			if (IntersectRect(&CollisionRect, &GamerRect, &BulletRect)) {
				if (bullet_block[i].type == OBSTACLE) { // 블러저에 맞으면 종료
					gameloop = 0;
					break;
				}
				else if (bullet_block[i].type == SNICH) { // 스니치 잡으면 개수 증가
					reset_block(bullet_block + i);
					cnt2++;
					if (cnt2 == snich_count) { //스니치 잡은 개수가 10이면 종료
						gameloop = 0;
						break;
					}
				}
			}
		}
		Sleep(50);  // 바로 끝나버려서 지연시켜줌

		new_time = clock();
		if (new_time - start_time >= 30000) break;  // 제한시간 30초 지나면 종료
	}
	Sleep(100);
	score[2] += snich_count * 10;
	class3();
}


/// 3교시

// 아스키코드 사용하여 x좌표값 2배 해줌
void gotoxy3(int x, int y) {  
	COORD Pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void gotoxyHP3(int x, int y) {
	COORD Pos = { x * 2 , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int warehouse[2][EX3_C][EX3_R] = {                 // 1. ▩ 벽  2. □ 장애물  3. ▣ 지정된 위치
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

 // 저장된 값에 맞게 출력해주는 함수
void print_warehouse(int map, int potion) {
	for (i = 0; i < EX3_C; i++) {
		for (j = 0; j < EX3_R; j++) {
			gotoxy3(j, i);

			if (warehouse[map][i][j] == 1) {
				WHITE; printf("▩");
			}
			else if (warehouse[map][i][j] == 2) {
				WHITE; printf("□");
			}
			else if (warehouse[map][i][j] == 3) {
				WHITE; printf("▣");
			}
			else if (warehouse[map][i][j] == 4) {  
				YELLOW; printf("●");
			}
			else if (warehouse[map][i][j] == 5) { 
				BLOOD; printf("●");
			}
			else if (warehouse[map][i][j] == 6) {   
				if (potion == 0) YELGREEN;         // potion 0 일 때 YELLO + YELGREEN
				else BLUE;                         // potion 1 일 때 YELLO + BLOOD
				printf("●");
			}
			else if (warehouse[map][i][j] == 7) {  // 모양 재료
				WHITE;
				if (potion == 0) printf("♤");
				else printf("♧");
			}
			else printf(" ");
		}
	}
}

void exam3(int potion) {
	system("cls");
	
	int nx = 9, ny = 7;   // 현재 위치값	

	int cnt = 3; 
	int item[4], order = 0, overlap;
	int map = rand() % 2;  // 맵 랜덤

	for (i = 0; i < 4; i++) { // 재료 순서 랜덤
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
		gotoxyHP3(nx, ny); printf("/");  // 사용자 출력
		int dx = 0, dy = 0;  // 증감값 초기화

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

		// 이동하기 전에
		while (1) {  // 이동 조건 확인
			if (warehouse[map][ny + dy][nx + dx] != 1) {                                    // 이동 하려는 곳에 벽이 없으면
				if (warehouse[map][ny + dy][nx + dx] == 2) {                                // 장애물 밀고자 할 때
					if (warehouse[map][ny + (dy * 2)][nx + (dx * 2)] == 0 || warehouse[map][ny + (dy * 2)][nx + (dx * 2)] == 3) {  //장애물 밀고하 자는 곳이 비어있거나 지정된 위치라면
						if (warehouse[map][ny + dy][nx + dx] == 3)                          // 지나가도 변화없음
							warehouse[map][ny + dy][nx + dx] = 3;
						else warehouse[map][ny + dy][nx + dx] = 0;

						if (warehouse[map][ny + (dy * 2)][nx + (dx * 2)] == 0)              // 빈 곳에 장애물 밀어넣음 
							warehouse[map][ny + (dy * 2)][nx + (dx * 2)] = 2;  
						else warehouse[map][ny + (dy * 2)][nx + (dx * 2)] = item[order++];  // 지정된 위치에 장애물 밀어넣으면 재료 나타남 
					}
					else break;
				}
				// 재료 선택할 때
				else if (warehouse[map][ny + dy][nx + dx] == 4) {  
					warehouse[map][ny + dy][nx + dx] = 0;          // 재료 선택하면 공백으로 표시
					cnt--;
					if (potion == 0) score[3] += 30;               // 맞는 재료일때만 점수 부여
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
				nx += dx;    // 증감값 더하여 현재위치 갱신
				ny += dy;
			}
			break;
		}		
		if (cnt == 0) {      // 재료 3개 선택하면 종료
			score[3] += 10;  // 제한 시간안에 끝내면 추가 점수 
			break;
		}

		new_time = clock();
		if (new_time - start_time >= 30000) break;
	}
	Sleep(500);
	class4();
}


/// 4교시

// 타켓 정보에 대한 구조체
typedef struct target {
	int state;          // UP, DOWN
	int pos_x;
	int pos_y;
	clock_t down_time;  
	clock_t	up_time;    
	clock_t	past_time;  // 이전 시각	
} target;

target dementors[5];

// 지팡이 출력 함수
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

// 공격 함수. 사슴입니다
void print_patronus(x, y) { 
	gotoxy(x - 2, y);     printf(" V V");
	gotoxy(x - 2, y + 1); printf("(   )");
	gotoxy(x - 2, y + 2); printf("/   ＼");
	gotoxy(x - 2, y + 3); printf("(  ˘ )");
	gotoxy(x - 2, y + 4); printf(" Ｕ  Ｕ");
}

void delete_patronus(x, y) {
	gotoxy(x - 4, y);     printf("         ");
	gotoxy(x - 4, y + 1); printf("         ");
	gotoxy(x - 4, y + 2); printf("         ");
	gotoxy(x - 4, y + 3); printf("         ");
	gotoxy(x - 4, y + 4); printf("         ");
}

// 타겟 출력 함수. 디멘터입니다
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

	int pos[5] = { 41,54,67,15,28 };  // x좌표값 지정
	int w_y = 22;                     // wand y좌표값
	int w_x = 0, d_x = 0;             // pos 인덱스 및 x좌표값	
	int cnt4 = 0;                      // 맞춘 횟수

	clock_t start_time, new_time, curr_time;
	start_time = clock();

	for (i = 0; i < 5; i++) {  // 타겟 초기화
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
		for (i = 0; i < 5; i++) {  // 타겟 출현	
			if (dementors[i].state == 1) {  // UP
				print_dementor(dementors[i].pos_x, dementors[i].pos_y);
			}
			else delete_dementor(dementors[i].pos_x, dementors[i].pos_y);  // DOWN
		}

		print_wand(pos[w_x], w_y);

		gotoxy(62, 1);
		printf("맞힌 횟수 : %2d", cnt4);

		if (_kbhit()) { // 어떠한 입력을 받지않아도 타겟 랜덤 출현
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

			case SPACE: // 공격
				print_patronus(pos[w_x], dementors[w_x].pos_y + 2);  // 공격 텀을 둠
				Sleep(400);

				delete_patronus(pos[w_x], dementors[w_x].pos_y + 2);
				print_patronus(pos[w_x], dementors[w_x].pos_y);
				Sleep(400);

				delete_patronus(pos[w_x], dementors[w_x].pos_y);
				for (i = 0; i < 5; i++) {
					if (dementors[i].state == 1 && pos[w_x] == dementors[i].pos_x) {  // 공격한 위치에 타겟이 있었는지 탐색
						cnt4++;
						dementors[i].state = 0;  // 맞았으면 바로 DOWN 상태로 전환
						break;  // 한번에 하나만 맞힐 수 있기 때문에 찾으면 빠져나감
					}
				}
				break;
			}
		}
		new_time = clock();
		if (new_time - start_time >= 30000) break;

		curr_time = clock();

		for (i = 0; i < 5; i++) {  // 타겟 상태 갱신
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


/// 5교시

//경계선 출력 함수3
void print_edge5() {
	for (i = 0; i < EX5_R / 2; i++) {
		gotoxy(i * 2, 0); printf("▦");
		gotoxy(i * 2, EX5_C - 1); printf("▦");
	}

	for (i = 1; i < EX5_C - 1; i++) {
		gotoxy(0, i); printf("▦");
		gotoxy(EX5_R - 2, i); printf("▦");
	}
}

char* mole[MOLE_SIZE] = { "∩ ∩",
						  "(^ ^)",
						  "O   O" }; //동물


char* bucket[BUCKET_SIZE] = { "┏━━┓",
							 "┃♡┃",
							"┗━━┛" }; //먹이통

char* blank[BUCKET_SIZE] = { "       ","        " ,"        " };

POINT xy_hole[HOLE_SIZE] = { { 4, 5 }, { 12, 5 }, { 20, 5 },
							 { 4, 10 }, { 12, 10 }, { 20, 10 },
							 { 4, 15 }, { 12, 15 }, { 20, 15 } };//홀의 위치를 정해줌


void genMole(int m[]) {
	int pos, exit = 0, sum = 0;

	while (!exit) {
		pos = rand() % HOLE_SIZE;
		if (m[pos] == 0) {
			m[pos] = MOLE_APPEAR_TIME;
			break;
		} //홀에 동물이 랜덤으로 나오도록 설정


		for (int i = 0; i < HOLE_SIZE; i++) {
			if (m[i] > 0) {
				sum++;
				if (sum == HOLE_SIZE) return 0;
			}//모든 홀에 동물이 있을 경우
		}
	}
}


int isHit(int m[], int pos) {
	return (pos >= 0 && m[pos] > 0);
} //pos에 동물이 있으면 리턴시킨다


void checkMoleTimer(int m[]) {
	for (i = 0; i < HOLE_SIZE; i++) {
		if (m[i] > 0) m[i]--;
	}
}//동물등장시간


void checkHammerTimer(int h[]) {
	for (i = 0; i < HOLE_SIZE; i++) {
		if (h[i] > 0) h[i]--;
	}
}//먹이통 등장시간


int keyPlayer(char key, int h[]) {
	int hit_pos = -1;

	for (i = 0; i < HOLE_SIZE; i++) h[i] = 0; // CLEAR한 상태로 만듦

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
	} //각각 키위치를 케이스별로 지정
	return hit_pos;
}

void updateHole(int m[]) {
	int str_pos[] = { 7, 8, 9, 4, 5, 6, 1, 2, 3 };

	for (i = 0; i < HOLE_SIZE; i++) {
		// 화면에 동물이 존재하면 표시
		if (m[i] > 0) {
			for (j = 0; j < MOLE_SIZE; j++) {
				gotoxy(xy_hole[i].x, xy_hole[i].y + j);
				printf("%s", mole[j]);
			}
		}
		// 화면에 홀 번호 표시
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
			}// 홀에 동물이 있으면
		}
	}
	WHITE;
}// 먹이통표시

void deleteHammer(int h[]) {
	for (i = 0; i < HOLE_SIZE; i++) {
			for (j = 0; j < BUCKET_SIZE; j++) {
				gotoxy(xy_hole[i].x, xy_hole[i].y + j - MOLE_SIZE);
				printf("%s", blank[j]);
			}
	}
	
}// 먹이통 지움

void exam5() {
	system("cls");

	int mole_hole[HOLE_SIZE] = { 0, };
	int hammer_hole[HOLE_SIZE] = { 0, };
	int closeness = 0, hit_pos, time_count = 0;
	double game_time; // 시간을 실수형으로 선언
	game_time = GAME_TIME; // 제한시간

	start_time = clock();
	print_edge5();
	while (1) {
		
		gotoxy(EX5_R + 1, 2); printf("친밀도 쌓기 : %3d", closeness);


		game_time -= 0.1;	// 0.1 초씩 감소
		if (game_time <= 0.0) break;

		// 출력 유지 타이머 체크
		checkMoleTimer(mole_hole);
		checkHammerTimer(hammer_hole);

		time_count++;
		if (time_count == GEN_TIME)
		{
			// 동물 생성
			genMole(mole_hole);
			time_count = 0;
		}

		if (_kbhit()) { // 어떠한 입력을 받았을 때
			key = _getch();
			hit_pos = keyPlayer(key, hammer_hole);
			if (hit_pos != MISS) { //MISS 맞지 않음
				if (isHit(mole_hole, hit_pos)) {
					closeness += 3; //동물에게 먹이를 주면 점수증가
					mole_hole[hit_pos] = 0; // 동물을 제거 상태로				
				}
			}
					}
		
		deleteHole(mole_hole);
		// 동물, 하트 출력
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
		printf("▶");
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