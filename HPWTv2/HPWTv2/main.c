#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <mmsystem.h>  // mciSendString() 
#include <digitalv.h>  // 음악 반복재생
#pragma comment (lib, "winmm.lib") // MCI


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
#define MAX_BLOCK   10	// 블럭의 최대수

#define EX3_R  20   // 3교시 창 크기
#define EX3_C  15

#define EX5_R  56  // 5교시 창 크기
#define EX5_C  30
#define BEAST_SIZE			5	// 동물 세로크기
#define MAX_POINT			9	// 홀의 크기
#define BEAST_APPEAR_TIME	2	// 동물 등장시간(1500ms) 5초
#define HEART_APPEAR_TIME	1	// 하트 등장시간(1000ms)
#define MISS				-1	// 실수
#define INTERVAL			1	// 0.5초 (동물 등장간격)

char key;
int score[5];
int i, j;
int rank[5] = { 0 };  // 1위부터 5위까지 등록
clock_t start_time, new_time;

typedef enum { Flitwick, Hooch, Snape, Moody, Hagrid } PROFESSOR;
enum DIRECT { LEFT_DOWN, LEFT_UP, RIGHT_UP, RIGHT_DOWN };

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
	mciOpen.lpstrElementName = L"prologue.mp3"; // 파일이름
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);

	MCI_PLAY_PARMS mciPlay; // 재생
	mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);
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

// 점수 초기화
void score_init() {
	for (i = 1; i <= 5; i++) {
		score[i] = 0;
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

	gotoxy(14, 7);	printf("해리포터가 다섯 과목의 마법 시험을 치르는 게임입니다.");
	Sleep(800);
	gotoxy(11, 10);	printf("이동은 방향키로, 선택과 공격시에는 스페이스바를 누르세요.");
	Sleep(800);
	gotoxy(19, 13);	printf("각 교수님들의 안내에 따라 게임을 진행하고,");
	Sleep(800);
	gotoxy(14, 16);	printf("게임 점수가 상위 5위 안에 들 경우 랭킹에 등록됩니다.");
	Sleep(800);
	gotoxy(7, 21);	GOLD; printf("해리포터가 되어 호그와트 마법 시험을 치르고 높은 성적을 받아보세요~");

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
	print_edge();

	gotoxy(34, 5);
	printf("[WIZARDING TEST]");

	for (i = 1; i <= 5; i++) {
		gotoxy(16, 7 + 2 * i);
		printf("%d 교시  :    %3d점", i, score[i]);
		score[0] += score[i];
		Sleep(800);
	}

	gotoxy(14, 21);
	printf("최종 점수 :    %3d점", score[0]);

	gotoxy(16, 23);
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
		gotoxyHP(x, y);	printf("     ");

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
	gotoxy(22, 23); printf("오늘이 표준 마법사 시험이 있는 날이구나, 해리");
	gotoxy(22, 24); printf("준비는 잘 하였니?");
	Sleep(2000);

	delete_dialog();
	gotoxy(11, 23); printf("해리포터 :");
	gotoxy(22, 23); printf("......");
	Sleep(2000);

	gotoxy(11, 23); printf("덤블도어 :");
	gotoxy(22, 23); printf("흠.. 1교시는 마법 주문, 2교시는 비행,");
	Sleep(1000);
	gotoxy(22, 24); printf("3교시는 마법약, 4교시는 어둠의 마법 방어술");
	Sleep(1000);
	gotoxy(22, 25); printf("5교시에는 신비한 동물 돌보기 시험이 있구나.");
	Sleep(1000);

	delete_dialog();
	gotoxy(22, 23); printf("시험 방식은 교수님마다 설명해주실거다.");
	gotoxy(22, 24); printf("그럼 좋은 결과 있기를...");
	gotoxy(22, 25); printf("행운을 비네!");
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

	Sleep(500);
	gotoxyHP(38, 13); printf("     ");
	for (i = 12; i > 0; i--) {
		gotoxyHP(38, i); printf("○-○");
		Sleep(90);
		gotoxyHP(38, i); printf("     ");
	}

	class1();
}

void class1() {
	system("cls");

	print_class(Flitwick);
	gotoxy(11, 23); printf("플리트윅 :");
	gotoxy(22, 23); printf("해리포터 군. 이번 시험은 마법 주문 시험이란다.");
	gotoxy(22, 24); printf("문제는 총 5문제고, 맞는 번호를 누르면 된단다.");
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
	gotoxy(23, 24); printf("30초 안에 날아다니는 골든 스니치를 잡으면 된다.");
	gotoxy(23, 25); printf("물론 블러저도 날아오니까 잘 피하고~");
	Sleep(1000);

	delete_dialog();
	gotoxy(23, 23); printf("30초 안에 날아다니는 골든 스니치를 잡으면 된다.");
	gotoxy(23, 24); printf("물론 블러저도 날아오니까 잘 피하고~");
	gotoxy(23, 25); printf("퀴디치 선수도 했었으니 잘 할거라고 생각되구나.");

	Sleep(3000);
	exam2();
}

void class3() {
	system("cls");

	int potion = rand() % 2;

	print_class(Snape);
	gotoxy(11, 23); printf("스네이프 :");
	gotoxy(22, 23); printf("곧 시험을 시작하겠다.");
	gotoxy(22, 24); printf("30초 안에 칠판에 적힌 물약을 만드는데 필요한");
	gotoxy(22, 25); printf("재료를 찾아와라.");
	Sleep(1000);

	gotoxy(30, 5);
	if (potion == 0) { BLUE; printf("♠"); }
	else { VIOLET; printf("♣"); }
	WHITE; printf("   =   ?  +  ?  +  ?");

	delete_dialog();
	gotoxy(22, 23);	printf("단 3개만 가져올 것. 과연 니녀석이 잘 찾아 올지");
	gotoxy(22, 24); printf("의문이구나");
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
	gotoxy(22, 25); printf("소환해서 처리하면 된다.");
	Sleep(2000);

	delete_dialog();
	gotoxy(22, 23); printf("볼드모트가 살아있는 동안 이정도의 마법은 잘 할");
	gotoxy(22, 24); printf("수 있어야 한다.");
	gotoxy(22, 25); printf("특히 해리포터라면 기대해봐도 되겠지.");

	Sleep(3000);
	exam4();
}

void class5() {
	system("cls");

	print_class(Hagrid);
	gotoxy(11, 23); printf("해그리드 :");
	gotoxy(22, 23); printf("오 해리야. 이제 마지막 시험이지?");
	gotoxy(22, 24); printf("이번 시험은 신비한 동물을 돌보는 시험이란다.");
	gotoxy(22, 25); printf("후후, 기대되지?");
	Sleep(2000);

	delete_dialog();
	gotoxy(22, 23); printf("마침 동물들 밥 줄 시간이라서 먹이를 주고 친밀도");
	gotoxy(22, 24); printf("를 높여보렴. 녀석들은 경계심이 강해서 보통 나무");
	gotoxy(22, 25); printf("위에 숨어있지만 먹이 냄새를 맡으면 나타날거야.");
	Sleep(2000);

	delete_dialog();
	gotoxy(22, 23); printf("를 높여보렴. 녀석들은 경계심이 강해서 보통 나무");
	gotoxy(22, 24); printf("위에 숨어있지만 먹이 냄새를 맡으면 나타날거야.");
	gotoxy(22, 25); printf("그 때 나무 번호를 눌러 먹이를 주면 된단다.");
	Sleep(2000);

	delete_dialog();
	gotoxy(22, 23); printf("그리고 이번에 새로 데려온 동물이 하나 있는데 시");
	gotoxy(22, 24); printf("험이 끝나면 론이랑 헤르미온느랑 같이 오두막으로");
	gotoxy(22, 25); printf("놀러오렴. 어쩌구 저쩌구......");

	Sleep(3000);
	exam5();
}


/// 1교시

 // 문제 정보에 대한 구조체
typedef struct {
	char* question;    // 주문
	char* choice[3];    // 선택지
	char answer;       // 정답
	BOOL already;      // 중복인지 확인
} QUESTION;

QUESTION question_data[] = {
	{ "패트로누스를 소환해 디멘트를 물리칠 때 사용하는 주문은?", "엑스펠리아르무스", "익스펙토 패트로눔", "레파로", '2', FALSE},
	{ "먼 거리에 있는 물체를 소환할 때 사용하는 주문은?", "레파로", "익스펙토 패트로눔", "윙가르디움 레비오사", '1', FALSE},
	{ "물체를 공중으로 떠오르게 하는 공중부양 주문은?","윙가르디움 레비오사","윙가르디움 레비오우사","윙가르디움 레비우사", '2', FALSE},
	{ "섹튬 셈프라로 다친 부위를 치료하는 주문은?","비페라 이바네스카","볼네라 사넨투르","레질리먼시", '2', FALSE},
	{ "상대방의 기억을 수정하거나 지우는 주문은?","레질리먼시","오블리비아테","아바다 케다브라", '2', FALSE },
	{ "용서받지 못할 저주 중 하나로 살인 저주인 주문은?","아바다 케다브라","크루시오","봄바르다", '1', FALSE },
	{ "물체를 폭파시킬 때 사용하는 주문은?", "디센디움", "봄바르다", "디센도", '2', FALSE  },
	{ "문을 열거나 무너뜨릴 때 사용하는 주문은?", "디센도", "레파로", "에피스키", '1', FALSE },
	{ "부러진 뼈를 붙일 때 사용하는 주문은?", "엑스펄소", "아바다케다브라", "에피스키", '1', FALSE },
	{ "용서받지 못할 저주 중 하나로 상대를 복종시키는 주문은?", "아바다케다브라", "임페리오", "임페디멘타", '2', FALSE },
	{ "몸이 마비되어 정지시킬 때 사용하는 주문은?", "임페디멘타", "임페르비우스", "아바다케다브라", '1', FALSE }
};

void exam1() {
	int selectnum, sel;

	for (sel = 0; sel < 5; sel++) {
		system("cls");
		print_edge();

		do {
			selectnum = rand() % (sizeof(question_data) / sizeof(question_data[0]));
		} while (question_data[selectnum].already == TRUE);
		question_data[selectnum].already = TRUE;

		gotoxy(16, 6); printf("%d. %s", sel + 1, question_data[selectnum].question);  // 문제 출력
		for (i = 0; i < 3; i++) {  // 선택지 출력
			gotoxy(19, 9 + i * 3);
			printf("(%d) %s", i + 1, question_data[selectnum].choice[i]);
		}
		gotoxy(18, 21); printf("(1), (2), (3) 중 하나를 선택하세요  :  ");

		key = _getch();
		printf("%c", key);

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

// 방애물 정보에 대한 구조체
typedef struct {
	int direction;  // 날아오는 방향
	int width;      // 블럭의 크기
	int height;
	double x;          // 출력 좌표
	double y;
	double speed;      // 속도
} BLOCK;

// 사용자 정보에 대한 구조체
typedef struct {
	char* shape;
	int	  width;
	int	  height;
	int	  x;
	int	  y;
} PLAYER;

PLAYER gamer;
BLOCK bludger[MAX_BLOCK];
BLOCK snitch;

// 장애물 좌표 및 속도 재설정 함수
void reset_block(BLOCK* block) {
	int interval = rand() % 5 + 4;  // 4 ~ 8
	block->direction = rand() % 3;

	switch (block->direction) {
	case 0:                    // 위쪽에서 나타남
		block->x = rand() % (EX2_R - 6) + 2;  // 2 ~ (EX2_R - 6 + 2)			
		block->y = (rand() % MAX_BLOCK) * -interval;
		break;
	case 1:                    // 왼쪽에서 나타남		
		block->x = (rand() % MAX_BLOCK) * -interval;
		block->y = rand() % (EX2_C - 3) + 1;
		break;
	case 2:                   // 오른쪽에서 나타남
		block->x = EX2_R + (rand() % MAX_BLOCK) * interval;
		block->y = rand() % (EX2_C - 3) + 1;
		break;
	}
}

// 장애물 좌표 및 출력 갱신 함수
void update_block() {
	for (i = 0; i < MAX_BLOCK; i++) {
		if (2 < bludger[i].x && bludger[i].x < EX2_R - 3 && 1 < bludger[i].y && bludger[i].y < EX2_C - 1) {
			gotoxy(bludger[i].x, bludger[i].y); printf("  ");
		}

		switch (bludger[i].direction) {
		case 0: // 하강
			bludger[i].y += bludger[i].speed;
			if (bludger[i].y > EX2_C) reset_block(&bludger[i]);
			break;
		case 1:
			bludger[i].x += bludger[i].speed;
			if (bludger[i].x > EX2_R) reset_block(&bludger[i]);
			break;
		case 2:
			bludger[i].x -= bludger[i].speed;
			if (bludger[i].x < 2) reset_block(&bludger[i]);
			break;
		}

		if (2 < bludger[i].x && bludger[i].x < EX2_R - 3 && 1 < bludger[i].y && bludger[i].y < EX2_C - 1) {
			gotoxy(bludger[i].x, bludger[i].y); printf("●");
		}
	}
}

void update_snitch() {
	gotoxy(snitch.x, snitch.y); printf("  ");

	switch (snitch.direction) {
	case LEFT_DOWN:   //↘
		snitch.x++;
		snitch.y++;
		if (snitch.x > EX2_R * 1.5 || snitch.y > EX2_C * 1.5) {
			if (snitch.x > EX2_R * 1.5) snitch.direction = RIGHT_DOWN;
			else snitch.direction = LEFT_UP;
		}
		break;
	case LEFT_UP:     //↗
		snitch.x++;
		snitch.y--;
		if (snitch.x > EX2_R * 1.5 || snitch.y < -(EX2_C / 2)) {
			if (snitch.x > EX2_R * 1.5) snitch.direction = RIGHT_UP;
			else snitch.direction = LEFT_DOWN;
		}
		break;
	case RIGHT_DOWN:  //↙
		snitch.x--;
		snitch.y++;
		if (snitch.x < -(EX2_R / 2) || snitch.y > EX2_C * 1.5) {
			if (snitch.x < -(EX2_R / 2)) snitch.direction = LEFT_DOWN;
			else snitch.direction = RIGHT_UP;
		}
		break;
	case RIGHT_UP:    //↖
		snitch.x--;
		snitch.y--;
		if (snitch.x < -(EX2_R / 2) || snitch.y < -(EX2_C / 2)) {
			if (snitch.x < -(EX2_R / 2)) snitch.direction = LEFT_UP;
			else snitch.direction = RIGHT_DOWN;
		}
		break;
	}

	if (2 < snitch.x && snitch.x < EX2_R - 3 && 1 < snitch.y && snitch.y < EX2_C - 1) {
		gotoxy(snitch.x, snitch.y);
		GOLD; printf("¤"); WHITE;
	}
}

void init2() {
	for (i = 0; i < MAX_BLOCK; i++) {  // 장애물 초기화
		bludger[i].width = 2;
		bludger[i].height = 1;
		bludger[i].speed = 0.4;
		reset_block(&bludger[i]);
	}

	snitch.width = 2;
	snitch.height = 1;
	reset_block(&snitch);

	gamer.shape = "○-○";  // 사용자 초기화
	gamer.width = 5;
	gamer.height = 1;
	gamer.x = 27;
	gamer.y = EX2_C - 4;
}

void exam2() {
	system("cls");

	int gameloop = 1;
	RECT GamerRect, BlockRect1, BlockRect2, CollisionRect;

	init2();
	start_time = clock();

	while (gameloop) {
		print_edge2();

		if (_kbhit()) { // 어떠한 입력을 받았을 때
			key = _getch();
			gotoxy(gamer.x, gamer.y); printf("     ");

			// 이동 크기를 구한다. 화면 밖으로 나가지 못하도록 계산하여 고정
			switch (key) {
			case LEFT:
				gamer.x -= 2;
				if (gamer.x < 2) gamer.x = 2;
				break;
			case RIGHT:
				gamer.x += 2;
				if (gamer.x > EX2_R - 2 - strlen(gamer.shape))
					gamer.x = EX2_R - 2 - strlen(gamer.shape);
				break;
			case UP:
				gamer.y -= 1;
				if (gamer.y < 1) gamer.y = 1;
				break;
			case DOWN:
				gamer.y += 1;
				if (gamer.y > EX2_C - 2) gamer.y = EX2_C - 2;
				break;
			}
		}

		gotoxy(gamer.x, gamer.y);
		printf("%s", gamer.shape);

		update_block();
		update_snitch();

		// 충돌체크
		SetRect(&GamerRect, gamer.x, gamer.y, gamer.x + gamer.width, gamer.y + gamer.height);

		for (i = 0; i < MAX_BLOCK; i++) {
			SetRect(&BlockRect1, (int)bludger[i].x, (int)bludger[i].y, (int)bludger[i].x + bludger[i].width, (int)bludger[i].y + bludger[i].height);

			if (IntersectRect(&CollisionRect, &GamerRect, &BlockRect1)) {  // 블러저에 맞으면 종료
				gameloop = 0;
				break;
			}
		}

		SetRect(&BlockRect2, (int)snitch.x, (int)snitch.y, (int)snitch.x + snitch.width, (int)snitch.y + snitch.height);

		if (IntersectRect(&CollisionRect, &GamerRect, &BlockRect2)) {  // 스니치 잡으면 종료
			gameloop = 0;

			new_time = clock();
			if (new_time - start_time < 10000) score[2] = 100;
			else if (new_time - start_time < 15000) score[2] = 90;
			else if (new_time - start_time < 20000) score[2] = 80;
			else if (new_time - start_time < 25000) score[2] = 70;
			else score[2] = 60;
			break;
		}

		new_time = clock();
		if (new_time - start_time >= 30000) gameloop = 0;  // 제한시간 30초 지나면 종료
	}
	Sleep(500);
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
		{1,1,1,0,2,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1},
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
			else printf("  ");
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
		gotoxyHP3(nx, ny);
		GOLD; printf("┌┘"); WHITE; // 사용자 출력
		int dx = 0, dy = 0;  // 증감값 초기화

		key = _getch();
		gotoxyHP3(nx, ny); printf("  ");

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

// 공격 함수. 사슴
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

// 타겟 출력 함수. 디멘터
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
	clock_t curr_time;

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
	if (cnt4 > 22) score[4] += 100;
	else if (cnt4 > 18) score[4] += 90;
	else if (cnt4 > 13) score[4] += 80;
	else if (cnt4 > 10) score[4] += 60;
	else score[4] += 40;

	Sleep(500);
	class5();
}


/// 5교시

char* beast[BEAST_SIZE] = {
	" Эへ  ",
	" ㆎŀψ",
	"ξ||√ ",
	" ∫ト  ",
	"ξ  ζ "
};

// 위치 지정
POINT tree[MAX_POINT] = {
	{ 9, 3 }, { 25, 3 }, { 41, 3 },
	{ 9, 12 }, { 25, 12 }, { 41, 12 },
	{ 9, 21 }, { 25, 21 }, { 41, 21 }
};

// 경계선 출력 함수3
void print_edge5() {
	for (i = 0; i < EX5_R / 2; i++) {
		gotoxy(i * 2, 0); printf("▦");
		gotoxy(i * 2, EX5_C - 1); printf("▦");
	}
	for (i = 1; i < EX5_C - 1; i++) {
		gotoxy(0, i); printf("▦");
		gotoxy(EX5_R - 2, i); printf("▦");
	}

	int hit_num[] = { 7, 8, 9, 4, 5, 6, 1, 2, 3 };
	for (i = 0; i < MAX_POINT; i++) {
		gotoxy(tree[i].x, tree[i].y + BEAST_SIZE);
		printf("[ %d ]", hit_num[i]);
	}

	gotoxy(2, 9);  printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣)");
	gotoxy(2, 10); printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣");

	gotoxy(7, 18);  printf("(￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣");
	gotoxy(7, 19); printf(" ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣");

	gotoxy(2, 27);  printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣)");
	gotoxy(2, 28); printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣");
}

// tree에 동물 생성
void gen_beast(int b[]) {
	int pos, sum = 0;

	while (1) {
		pos = rand() % MAX_POINT;
		if (b[pos] == 0) {
			b[pos] = BEAST_APPEAR_TIME;
			break;
		}

		for (i = 0; i < MAX_POINT; i++) { // 모든 홀에 동물이 있으면 0 반환 
			if (b[i] > 0) {
				sum++;
				if (sum == MAX_POINT) return 0;
			}
		}
	}
}

// pos에 동물이 존재하면 1 반환
int is_hit(int b[], int pos) {
	return (pos >= 0 && b[pos] > 0);
}

// 동물 등장 시간 감소
void check_beast_timer(int b[]) {
	for (i = 0; i < MAX_POINT; i++) {
		if (b[i] > 0) b[i]--;
	}
}

// 하트 등장 시간 감소
void check_food_timer(int h[]) {
	for (i = 0; i < MAX_POINT; i++) {
		if (h[i] > 0) h[i]--;
	}
}

// 동물 출력
void update_beast(int b[]) {
	for (i = 0; i < MAX_POINT; i++) {
		if (b[i] > 0) { // 배열에 동물이 존재하면
			for (j = 0; j < BEAST_SIZE; j++) {
				YELGREEN;
				gotoxy(tree[i].x, tree[i].y + j);
				printf("%s", beast[j]);
				WHITE;
			}
		}
		else            // b[i] == 0
			for (j = 0; j < BEAST_SIZE; j++) {
				gotoxy(tree[i].x, tree[i].y + j);
				printf("       ");
			}
	}
}

// 하트 출력
void update_food(int h[]) {
	for (i = 0; i < MAX_POINT; i++) {
		if (h[i] > 0) { // 배열에 하트가 있으면
			gotoxy(tree[i].x + 2, tree[i].y - 1);
			RED; printf("♥"); WHITE;
		}
		else {
			gotoxy(tree[i].x + 2, tree[i].y - 1);
			printf("  ");
		}
	}
}

// 키입력 처리
int update_key(int h[]) {
	int hit_pos = MISS;
	key = _getch();

	for (i = 0; i < MAX_POINT; i++) h[i] = 0;     // clear

	switch (key) {
	case '7':
		h[0] = HEART_APPEAR_TIME; hit_pos = 0; break;
	case '8':
		h[1] = HEART_APPEAR_TIME; hit_pos = 1; break;
	case '9':
		h[2] = HEART_APPEAR_TIME; hit_pos = 2; break;
	case '4':
		h[3] = HEART_APPEAR_TIME; hit_pos = 3; break;
	case '5':
		h[4] = HEART_APPEAR_TIME; hit_pos = 4; break;
	case '6':
		h[5] = HEART_APPEAR_TIME; hit_pos = 5; break;
	case '1':
		h[6] = HEART_APPEAR_TIME; hit_pos = 6; break;
	case '2':
		h[7] = HEART_APPEAR_TIME; hit_pos = 7; break;
	case '3':
		h[8] = HEART_APPEAR_TIME; hit_pos = 8; break;
	}
	return hit_pos;
}

void exam5() {
	system("cls");
	print_edge5();

	int bowt[MAX_POINT] = { 0 }, heart[MAX_POINT] = { 0 };	   // 0:없음, 1~APPEAR_TIME:있음	
	int cnt5 = 0, hit_pos, time_count = 0;

	start_time = clock();

	while (1) {
		gotoxy(58, 2);
		RED; printf("친밀도 : %2d", cnt5); WHITE;

		check_beast_timer(bowt);
		check_food_timer(heart);

		time_count++;
		if (time_count == INTERVAL) {
			gen_beast(bowt);
			time_count = 0;
		}

		if (_kbhit()) {
			hit_pos = update_key(heart);

			if (hit_pos != MISS) {
				if (is_hit(bowt, hit_pos)) { // 맞췄으면
					cnt5++;
					bowt[hit_pos] = 0;       // 동물 제거				
				}
			}
		}

		update_beast(bowt);
		update_food(heart);

		new_time = clock();
		if (new_time - start_time >= 30000) break;

		Sleep(1000);  // 1초 간격
	}
	if (cnt5 >= 22) score[5] += 100;
	else if (cnt5 > 18) score[5] += 90;
	else if (cnt5 > 13) score[5] += 80;
	else if (cnt5 > 10) score[5] += 60;
	else score[5] += 40;

	the_end();
}

void main() {
	srand((unsigned int)time(NULL));
	soundtrack();

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
			if (menu == 1) {
				//score_init();
				game_intro();
			}
			else if (menu == 2) game_info();
			else rank_show();
			break;
		}
	}
}




/*
void bonus() {
	int bonusmap[WINDOW_COL - 2][WINDOW_ROW - 2] = { 0 };
	bonusmap[3][3] = 1;
	for (i = 2; i < WINDOW_COL - 2; i++) {
		for (j = 2; j < WINDOW_ROW - 2; j++) {
			if (bonusmap[i][j] == 1) {
				gotoxy(j * 2, i);
				RED; printf("★"); WHITE;
			}
		}
	}
	print_edge();
	for (i = 2; i < WINDOW_COL - 2; i++) {
		for (j = 2; j < WINDOW_ROW - 2; j++) {
			gotoxy(j * 2, i);
			printf("▒");
		}
	}
	int x = 76, y = 15;
	int dx, dy;

	start_time = clock();
	while (1) {
		gotoxyHP(x, y); printf("┌┘");

		key = _getch();
		gotoxyHP(x, y); printf("  ");

		dx = 0, dy = 0;

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
		case SPACE:
			if (x + dx == '★' || y + dy == '★') {
				gotoxy(x + dx, y + dy); printf(" ");
			}
			break;
		};

		if (x + dx != '★' || y + dy != '★') {
			x += dx;
			y += dy;
		}
		else break;

	}
}
*/