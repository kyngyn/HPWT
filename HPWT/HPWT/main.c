#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <mmsystem.h>  // mciSendString() 
#pragma comment (lib, "winmm.lib") //MCI


// 夔樂璽 旋濠縑 儀 殮�鰼� 
#define col GetStdHandle(STD_OUTPUT_HANDLE)					// 夔樂璽曖 с菟薑爾蒂 嫡嬴褫棲棻.
#define WHITE		SetConsoleTextAttribute(col, 0x000f)	// �羃�
#define YELLOW		SetConsoleTextAttribute(col, 0x000e)	// 喻塢儀
#define PURPLE		SetConsoleTextAttribute(col, 0x000d)	// 濠輿儀
#define RED			SetConsoleTextAttribute(col, 0x000c)	// 說除儀
#define SKY			SetConsoleTextAttribute(col, 0x000b)	// ж棺儀
#define YELGREEN	SetConsoleTextAttribute(col, 0x000a)	// 翱舒儀
#define BLUE		SetConsoleTextAttribute(col, 0x0009)	// だ塢儀
#define GOLD		SetConsoleTextAttribute(col, 0x0006)	// 旎儀
#define VIOLET		SetConsoleTextAttribute(col, 0x0005)	// 爾塭儀
#define BLOOD		SetConsoleTextAttribute(col, 0x0004)	// Я儀
#define BLUE_GREEN	SetConsoleTextAttribute(col, 0x0003)	// 羶喬儀
#define GREEN		SetConsoleTextAttribute(col, 0x0002)	// 喬儀

#define LEFT   75
#define RIGHT  77
#define UP     72
#define DOWN   80
#define SPACE  32

#define WINDOW_ROW  40 
#define WINDOW_COL  30

#define EX2_R   60   // 2掖衛 璽 觼晦
#define EX2_C   22	

#define MAX_BLOCK   15	// 綰楣曖 譆渠熱
#define MAX_BULLET   2	// 識憲曖 謙盟
#define CON_CENTER_W_STR(msg)	((EX2_R-strlen(msg))/2)	// 夔樂璽曖 醞懈(陛煎) x謝ル

#define EX3_R  20   // 3掖衛 璽 觼晦
#define EX3_C  15

#define EX5_R  30   // 5掖衛 璽 觼晦
#define EX5_C  30

#define MOLE_SIZE			3	// 翕僭 撮煎觼晦
#define BUCKET_SIZE			3	// 詳檜鱔 撮煎觼晦
#define HOLE_SIZE			9	// �池� 觼晦
#define MOLE_APPEAR_TIME	15	// 翕僭 蛔濰衛除(1500ms)
#define BUCKET_APPEAR_TIME	12	//  詳檜鱔衛除(1000ms)
#define MISS				-1// 褒熱
#define GEN_TIME			5	// 0.5蟾 (翕僭 蛔濰除問)
#define GAME_TIME			30.0


char key;
int score[5];
int i, j;
int rank[5] = { 0,0,0,0,0 };  // 1嬪睡攪 5嬪梱雖 蛔煙
clock_t start_time, new_time;

typedef enum { Flitwick, Hooch, Snape, Moody, Hagrid } PROFESSOR;


void gotoxy(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//餌辨濠 嬪纂雖薑 л熱
void gotoxyHP(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 醴憮 獗啖輿朝 л熱
void hideCursor() {
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

// 寡唳擠學 褒ч л熱
void soundtrack() {
	MCI_OPEN_PARMS mciOpen; // MCI_OPEN_PARAMS 掘褻羹 滲熱 
	mciOpen.lpstrDeviceType = L"mpegvideo"; // mp3 ⑽衝 
	mciOpen.lpstrElementName = L"Prologue.mp3"; // だ橾檜葷
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);

	MCI_PLAY_PARMS mciPlay; // 營儅
	mciSendCommand(mciOpen.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
}


// л熱 摹樹
void class1();
void exam1();
void exam2();
void exam3(int potion);
void exam4();
void exam5();



// 唳啗摹 轎溘 л熱
void print_edge() {
	for (i = 0; i < WINDOW_ROW; i++) {
		gotoxy(i * 2, 0);
		printf("〩");
		gotoxy(i * 2, WINDOW_COL - 1);
		printf("〩");
	}
	for (i = 1; i < WINDOW_COL; i++) {
		gotoxy(0, i);
		printf("〩");
		gotoxy((WINDOW_ROW - 1) * 2, i);
		printf("〩");
	}
}

// 詭檣�飛� л熱
void title() {
	system("cls");
	GOLD;
	printf("\n");
	printf("\n");
	printf("                                          ﹥﹥﹥                                    \n");
	printf("           ﹥                ﹥﹥          ﹥   ﹥                                  \n");
	printf("     ﹥    ﹥   ﹥﹥   ﹥﹥  ﹥ ﹥         ﹥   ﹥         ﹥                       \n");
	printf("     ﹥    ﹥       ﹥ ﹥ ﹥ ﹥     ﹥   ﹥﹥   ﹥ ﹥﹥  ﹥﹥﹥  ﹥          ﹥﹥   \n");
	printf("     ﹥  ﹥﹥﹥ ﹥﹥﹥ ﹥    ﹥ ﹥  ﹥   ﹥﹥ ﹥  ﹥  ﹥   ﹥  ﹥﹥﹥  ﹥﹥  ﹥ ﹥  \n");
	printf("   ﹥﹥﹥  ﹥   ﹥  ﹥ ﹥    ﹥   ﹥       ﹥     ﹥  ﹥   ﹥    ﹥   ﹥  ﹥ ﹥     \n");
	printf("     ﹥    ﹥   ﹥﹥﹥ ﹥        ﹥      ﹥﹥     ﹥  ﹥   ﹥    ﹥   ﹥﹥﹥ ﹥     \n");
	printf("     ﹥    ﹥              ﹥﹥﹥         ﹥        ﹥     ﹥    ﹥   ﹥     ﹥     \n");
	printf("           ﹥                             ﹥                 ﹥  ﹥    ﹥﹥         \n");
	printf("                                          ﹥                      ﹥﹥              \n");
	printf("                                          ﹥     AND THE                            \n");
	printf("\n");
	printf("\n");
	printf("     ﹥  ﹥  ﹥  ﹥  ﹥﹥﹥﹥     ﹥     ﹥﹥﹥    ﹥﹥﹥    ﹥  ﹥    ﹥   ﹥﹥﹥   \n");
	printf("     ﹥  ﹥  ﹥  ﹥       ﹥    ﹥  ﹥   ﹥    ﹥  ﹥    ﹥  ﹥  ﹥﹥  ﹥  ﹥        \n");
	printf("     ﹥  ﹥  ﹥  ﹥     ﹥     ﹥﹥﹥﹥  ﹥﹥﹥    ﹥    ﹥  ﹥  ﹥ ﹥ ﹥  ﹥  ﹥﹥  \n");
	printf("       ﹥  ﹥    ﹥   ﹥       ﹥    ﹥  ﹥    ﹥  ﹥    ﹥  ﹥  ﹥  ﹥﹥  ﹥    ﹥  \n");
	printf("       ﹥  ﹥    ﹥  ﹥﹥﹥﹥  ﹥    ﹥  ﹥    ﹥  ﹥﹥﹥    ﹥  ﹥    ﹥   ﹥﹥﹥   \n");
	printf("\n");
	printf("                             ﹥﹥﹥  ﹥﹥﹥  ﹥﹥﹥ ﹥﹥﹥         \n");
	printf("                               ﹥    ﹥      ﹥       ﹥           \n");
	printf("                               ﹥    ﹥﹥﹥  ﹥﹥﹥   ﹥           \n");
	printf("                               ﹥    ﹥          ﹥   ﹥           \n");
	printf("                               ﹥    ﹥﹥﹥  ﹥﹥﹥   ﹥           \n");

	gotoxy(22, 29); printf("啪歜 衛濛");
	gotoxy(41, 29); printf("啪歜 撲貲");
	gotoxy(60, 29); printf("牖嬪 �挫�");
	gotoxy(0, 30); printf(" "); //30還梱雖 �飛橦� 釭顫頂晦 嬪п憮
}

// 啪歜 撲貲 詭景 л熱
void game_info() {
	system("cls");
	WHITE;
	print_edge();

	gotoxy(9, 8);	printf("п葬ん攪陛 5偃 婁跡曖 衛я擊 爾賊憮 薄熱蒂 �僱磈炴� 啪歜殮棲棻.");
	Sleep(800);
	gotoxy(10, 10);	printf("檜翕擎 寞щ酈煎, 蜓擊 勘堅談戲賊 蝶む檜蝶夥蒂 援腦賊 腌棲棻.");
	Sleep(800);
	gotoxy(14, 12);	printf("陝 掖熱椒菟曖 撲貲擊 檗堅 啪歜擊 霞ч ж賊 腌棲棻.");
	Sleep(800);
	gotoxy(14, 14);	printf("啪歜薄熱陛 鼻嬪 5嬪 寰縑 菟 唳辦 楨韁縑 蛔煙 腌棲棻.");
	Sleep(800);
	gotoxy(9, 20);	GOLD; printf("п葬ん攪陛 腎橫憮 �ㄠ袗芢� 衛я擊 爾堅 堪擎 薄熱蒂 嫡嬴爾撮蹂~");
	
	_getch();
	title();
}

// 牖嬪 �挫� 詭景 л熱
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
		printf("%d嬪     %3d薄", i + 1, rank[i]);
	}

	_getch();
	title();
}

void aplus(int x, int y) {
	BLOOD;
	gotoxy(x, y);	   printf("                     ﹥");
	gotoxy(x, y + 1);  printf("                     ﹥");
	gotoxy(x, y + 2);  printf("        ﹥       ﹥﹥﹥﹥﹥");
	gotoxy(x, y + 3);  printf("       ﹥﹥          ﹥");
	gotoxy(x, y + 4);  printf("      ﹥  ﹥         ﹥");
	gotoxy(x, y + 5);  printf("     ﹥    ﹥          ");
	gotoxy(x, y + 6);  printf("    ﹥      ﹥         ");
	gotoxy(x, y + 7);  printf("   ﹥﹥﹥﹥﹥﹥        ");
	gotoxy(x, y + 8);  printf("  ﹥          ﹥       ");
	gotoxy(x, y + 9);  printf(" ﹥            ﹥      ");
	gotoxy(x, y + 10); printf("﹥              ﹥     ");
}

// 譆謙 唸婁 л熱
void the_end() {
	system("cls");
	WHITE;
	print_edge();

	gotoxy(34, 4);
	printf("WIZARDING TEST");
	
	for (i = 1; i <= 5; i++) {
		gotoxy(16, 6 + 2 * i);
		printf("%d 掖衛  :    %3d薄", i, score[i]);
		score[0] += score[i];
	}
	
	gotoxy(14, 20);
	printf("譆謙 薄熱 :    %3d薄", score[0]);

	gotoxy(16, 22);
	printf("з   薄 :       ");

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


// 渠�倥� 轎溘 л熱
void print_chat() {
	gotoxy(9, 21); printf("㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑");
	gotoxy(8, 22); printf("‵");
	gotoxy(8, 23); printf("‵");
	gotoxy(8, 24); printf("‵");
	gotoxy(8, 25); printf("‵");
	gotoxy(8, 26); printf("‵");
	gotoxy(70, 22); printf("‵");
	gotoxy(70, 23); printf("‵");
	gotoxy(70, 24); printf("‵");
	gotoxy(70, 25); printf("‵");
	gotoxy(70, 26); printf("‵");
	gotoxy(9, 27); printf("㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑㏑");
}

// 渠�倥� 濠葬 雖錶輿朝 л熱
void delete_chat() {
	for (j = 21; j < 28; j++) {
		for (i = 8; i < 72; i++) {
			gotoxy(i, j);
			printf(" ");
		}
	}
}

// 渠�� 雖錶輿朝 л熱
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

	// 犒紫
	for (i = 1; i < WINDOW_COL - 1; i++) {
		gotoxy(29, i); printf("��");
		gotoxy(49, i); printf("��");
	}
	BLUE_GREEN;
	gotoxy(35, 9);	printf("   / ′");
	gotoxy(35, 10); printf("  /    ′");
	gotoxy(35, 11);	printf("－________ˇ");
	WHITE;
	gotoxy(35, 12);	printf("(;; 芍--芍)");

	gotoxyHP(38, 28); printf("∞-∞");
	Sleep(300);

	// 檜翕
	gotoxy(38, 28); printf("     ");
	for (i = WINDOW_COL - 2; i > 13; i--) {
		gotoxyHP(38, i); printf("∞-∞");
		Sleep(90);
		gotoxyHP(38, i); printf("     ");
	}

	// 堅薑
	gotoxyHP(38, 13); printf("∞-∞");
	Sleep(300);

	delete_chat();
	print_chat();
	gotoxy(11, 23); printf("渾綰紫橫 :");
	gotoxy(22, 23); printf("螃棺檜 ル遽 葆徹餌 衛я檜 氈朝 陳檜掘釭");
	gotoxy(22, 24); printf("遽綠朝 澀 ж艘棲?");
	Sleep(2000);

	delete_dialog();
	gotoxy(11, 23); printf("п葬ん攪 :");
	gotoxy(22, 23); printf("......");
	Sleep(2000);

	gotoxy(11, 23); printf("渾綰紫橫 :");
	gotoxy(22, 23); printf("��.. 1掖衛朝 葆徹輿僥衛я, 2掖衛朝 綠ч衛я,");
	Sleep(1000);
	gotoxy(22, 24); printf("3掖衛朝 葆徹擒衛я, 4掖衛朝 橫菸曖葆徹寞橫獎衛я");
	Sleep(1000);
	gotoxy(22, 25); printf("5掖衛朝 褐綠и 翕僭 給爾晦 衛я檜 氈掘釭.");
	Sleep(1000);

	delete_dialog();
	gotoxy(22, 23); printf("衛я 寞衝擎 掖熱椒葆棻 撲貲п輿褒剪棻.");
	gotoxy(22, 24); printf("斜歲 謠擎 唸婁 氈晦蒂...");
	gotoxy(22, 25); printf("ч遴擊 綠啻.");
	Sleep(2000);

	system("cls");

	print_edge();
	for (i = 1; i < WINDOW_COL - 1; i++) {
		gotoxy(29, i); printf("��");
		gotoxy(49, i); printf("��");
	}
	gotoxyHP(38, 13); printf("∞-∞");

	delete_chat();
	print_chat();
	gotoxy(11, 23); printf("п葬ん攪 :");
	gotoxy(22, 23); printf("!!!!!!");
	Sleep(1000);

	delete_chat();
	for (i = 1; i < WINDOW_COL - 1; i++) {
		gotoxy(29, i); printf("��");
		gotoxy(49, i); printf("��");
	}

	gotoxyHP(38, 13); printf("     ");
	for (i = 12; i > 0; i--) {
		gotoxyHP(38, i); printf("∞-∞");
		Sleep(90);
		gotoxyHP(38, i); printf("     ");
	}

	class1();
}


void print_class(int prof) {
	print_edge();

	// 艦っ
	gotoxy(7, 3);	printf("旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
	gotoxy(6, 4); 	printf("��");
	gotoxy(73, 4); 	printf("��");
	gotoxy(6, 5); 	printf("��");
	gotoxy(73, 5); 	printf("��");
	gotoxy(6, 6); 	printf("��");
	gotoxy(73, 6); 	printf("��");
	gotoxy(7, 7);	printf("曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
	
	// 疇鼻
	gotoxy(8, 11);	printf("旨收收收收收收收收收收收收收收收收收收收收收收收旬");
	gotoxy(8, 12); 	printf("��");
	gotoxy(32, 12); printf("��");
	gotoxy(8, 13);	printf("曲收收收收收收收收收收收收收收收收收收收收收收收旭");
	gotoxy(8, 14);	printf("旨收收收收收收收收收收收收收收收收收收收收收收收旬");
	gotoxy(8, 15); 	printf("��");
	gotoxy(32, 15); printf("��");
	gotoxy(8, 16);	printf("曲收收收收收收收收收收收收收收收收收收收收收收收旭");
	gotoxy(8, 17);	printf("旨收收收收收收收收收收收收收收收收收收收收收收收旬");
	gotoxy(8, 18); 	printf("��");
	gotoxy(32, 18); printf("��");
	gotoxy(8, 19);	printf("曲收收收收收收收收收收收收收收收收收收收收收收收旭");
	gotoxy(47, 11);	printf("旨收收收收收收收收收收收收收收收收收收收收收收收旬");
	gotoxy(47, 12); printf("��");
	gotoxy(71, 12); printf("��");
	gotoxy(47, 13);	printf("曲收收收收收收收收收收收收收收收收收收收收收收收旭");
	gotoxy(47, 14);	printf("旨收收收收收收收收收收收收收收收收收收收收收收收旬");
	gotoxy(47, 15); printf("��");
	gotoxy(71, 15); printf("��");
	gotoxy(47, 16);	printf("曲收收收收收收收收收收收收收收收收收收收收收收收旭");
	gotoxy(47, 17);	printf("旨收收收收收收收收收收收收收收收收收收收收收收收旬");
	gotoxy(47, 18); printf("��");
	gotoxy(71, 18); printf("��");
	gotoxy(47, 19);	printf("曲收收收收收收收收收收收收收收收收收收收收收收收旭");

	//掖熱 議葛攪
	switch (prof) {
	case Flitwick:
		gotoxy(36, 7); 	printf("/   ′");
		gotoxy(35, 8); 	printf("/      ′");
		gotoxy(34, 9); 	printf("( ;;ㄖ歹ㄖ) / ");
		break;
	case Hooch:
		gotoxy(37, 7); 	printf("/   ′");
		gotoxy(36, 8); 	printf("/      ′");
		gotoxy(31, 9); 	printf("↓式 (  ◥ ╡◥)");
		break;
	case Snape:
		gotoxy(37, 7); 	printf("/   ′");
		gotoxy(36, 8); 	printf("/      ′");
		gotoxy(35, 9); 	printf("(  �鄐甜� ) /");
		break;
	case Moody:
		gotoxy(37, 7); 	printf("/   ′");
		gotoxy(36, 8); 	printf("/      ′");
		gotoxy(35, 9); 	printf("(  白  仄 )");
		gotoxy(39, 10); printf("÷");
		break;
	case Hagrid:
		gotoxy(36, 6); 	printf("＝÷÷÷＝");
		gotoxy(35, 7);  printf("＝ 爪  爪 ＝");
		gotoxy(34, 8); 	printf("＝企企仃企企＝");
		gotoxy(36, 9); 	printf("企企企企企");
		break;
	}

	int x = 38, y = 28;

	//雖薑 嬪纂縑憮 摹鷗ж晦 瞪梱雖 奩犒
	while (y != 10 || key != SPACE) {
		gotoxyHP(x, y); printf("∞-∞");

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

	gotoxyHP(x, y); printf("∞-∞");
	print_chat();
}

void class1() {
	system("cls");

	print_class(Flitwick);
	gotoxy(11, 23); printf("Ы葬お嬤 :");
	gotoxy(22, 23); printf("п葬ん攪 捱. 檜廓 衛я擎 葆徹 輿僥 衛я檜塢棻.");
	gotoxy(22, 24); printf("僥薯朝 識 5僥薯檜堅, 蜃朝 廓�ㄧ� 援腦賊 脹欽棻.");
	Sleep(2000);

	delete_dialog();
	gotoxy(22, 23); printf("斜翕寰 熱機 翮褕�� 菟歷戲棲梱 澀й 熱 氈啊雖?");

	Sleep(3000);
	exam1();
}

void class2() {
	system("cls");

	print_class(Hooch);
	gotoxy(12, 23); printf("�闡▼彿� :");
	gotoxy(23, 23); printf("ん攪掘釭. 檜廓 衛я擎 綠ч 衛я檜塢棻.");
	gotoxy(23, 24); printf("30蟾 寰縑 陳嬴棻棲朝 蝶棲纂 10偃蒂 濩戲賊 脹棻.");
	gotoxy(23, 25); printf("僭煩 綰楝盪紫 陳嬴螃棲梱 澀 Яж堅~");
	Sleep(1000);

	delete_dialog();
	gotoxy(23, 23); printf("30蟾 寰縑 陳嬴棻棲朝 蝶棲纂 10偃蒂 濩戲賊 脹棻.");
	gotoxy(23, 24); printf("僭煩 綰楝盪紫 陳嬴螃棲梱 澀 Яж堅~");
	gotoxy(23, 25); printf("襪蛤纂 摹熱紫 ц歷戲棲梱 澀й剪塭堅 儅陝 腎掘釭");

	Sleep(3000);
	exam2();
}

void class3() {
	system("cls");

	int potion = rand() % 2;
		
	print_class(Snape);
	gotoxy(11, 23); printf("蝶啻檜Щ :");
	gotoxy(22, 23); printf("埠 衛я擊 衛濛ж啊棻.");
	gotoxy(22, 24); printf("30蟾寰縑 艦っ縑 瞳�� 僭擒擊 虜萄朝等 в蹂и");
	gotoxy(22, 25); printf("營猿蒂 瓊嬴諦塭.");
	Sleep(1000);

	gotoxy(30, 5);
	if (potion == 0) { BLUE; printf("Ⅳ"); }
	else { VIOLET; printf("Ⅷ"); }	
	WHITE; printf("   =   ?  +  ?  +  ?");

	delete_dialog();
	gotoxy(22, 23);	printf("欽 3偃虜 陛螳螢匙. 婁翱 傘陛 澀 瓊嬴 陛雖堅");
	gotoxy(22, 24); printf("螢雖朝 曖僥檜掘釭");
	gotoxy(22, 25); printf("劂 晦棻葬堅 氈朝剪傍! 說葬 衛濛ж雖彊堅");

	Sleep(3000);
	exam3(potion);
}

void class4() {
	system("cls");

	print_class(Moody);
	gotoxy(11, 23); printf(" 鼠   蛤 :");
	gotoxy(22, 23); printf("檜廓 衛я擎 蛤詮攪蒂 僭葬纂朝 衛я檜棻.");
	gotoxy(22, 24); printf("薯и 衛除擎 30蟾. 陝濠 濠褐曖 ぬお煎援蝶 翕僭擊");
	gotoxy(22, 25); printf("碳楝頂憮 籀葬ж賊 脹棻.");
	Sleep(2000);

	delete_dialog();
	gotoxy(22, 23); printf("獐萄賅お陛 髦嬴氈朝 翕寰 檜薑紫曖 葆徹擎 澀 й");
	gotoxy(22, 24); printf("熱 氈橫撿 и棻. ");
	gotoxy(22, 25); printf("か�� п葬ん攪塭賊 晦渠п瑭紫 腎啊雖.");

	Sleep(3000);
	exam4();
}

void class5() {
	system("cls");

	print_class(Hagrid);
	gotoxy(11, 23); printf("п斜葬萄 :");
	gotoxy(22, 23); printf("螃 п葬撿. 檜薯 葆雖虞衛я檜掘釭~");
	gotoxy(22, 24); printf("檜廓 衛я擎 薑蜓 蔣欽棻. �蟛轀� 氈朝 翕僭菟擊");
	gotoxy(22, 25); printf("瓊嬴憮 詳檜蒂 輿堅 耀塵紫蒂 論戲賊 脹欽棻.");
	Sleep(800);
	delete_dialog();
	gotoxy(22, 23); printf("檜廓 衛я擎 薑蜓 蔣欽棻. �蟛轀� 氈朝 翕僭菟擊");
	gotoxy(22, 24); printf("瓊嬴憮 詳檜蒂 輿堅 耀塵紫蒂 論戲賊 脹欽棻.");
	gotoxy(22, 25); printf("詳檜蒂 號檜 還熱煙 謠擎 薄熱蒂 嫡擊 熱 氈欽棻.");
	Sleep(2000);

	delete_dialog();
	gotoxy(22, 23); printf("斜葬堅 檜廓縑 等溥螞 翕僭檜 ж釭 氈朝等 爾罹輿堅");
	gotoxy(22, 24); printf("談掘釭. 衛я檜 部釭賊 煩檜嫌 ④腦嘐螞替嫌 偽檜");
	gotoxy(22, 25); printf("螃舒虞戲煎 и廓 瓊嬴螃剪塭. 橫翹掘 盪翹掘......");

	Sleep(3000);
	exam5();
}


/// 1掖衛

 // 僥薯 薑爾縑 渠и 掘褻羹
typedef struct {
	char *question;
	int *choice[2];
	int answer;
	BOOL already;
} QUESTION;

QUESTION question_data[] = {
	   { "ぬお煎援蝶蒂 模�納� 蛤詮お蒂 僭葬艦 陽 餌辨ж朝 輿僥擎?\n","縈蝶ゃ葬嬴腦鼠蝶","櫛蝶め饜 ぬお煎揹",2, FALSE},
	   { "試剪葬縑 氈朝 僭羹蒂 模�納� 陽 餌辨ж朝 輿僥擎?\n","溯だ煎","櫛蝶め饜 ぬお煎揹", 1, FALSE},
	   { "僭羹蒂 奢醞戲煎 集螃腦啪 ж朝 奢醞睡曄 輿僥擎?\n","嶽陛腦蛤遺 溯綠螃餌","嶽陛腦蛤遺 溯綠螃辦餌", 2, FALSE},
	   { "播え 撬Щ塭煎 棻耀 睡嬪蒂 纂猿ж朝 輿僥擎?\n","綠む塭 檜夥啻蝶蘋","獐啻塭 餌喧癱腦", 2, FALSE},
	   { "鼻渠寞曖 晦橘擊 熱薑ж剪釭 雖辦朝 輿僥擎?\n","溯韓葬試衛","螃綰葬綠嬴纔", 2, FALSE },
	   { "辨憮嫡雖 跤й 盪輿 醞 ж釭煎 髦檣 盪輿檣 輿僥擎?\n","嬴夥棻 馨棻粽塭","觼瑞衛螃", 1 ,FALSE },
	   { "僭羹蒂 ァだ衛鑒 陽 餌辨ж朝 輿僥擎?\n","蛤撫蛤遺","瑤夥腦棻", 2, FALSE  },
	   { "僥擊翮剪釭 鼠傘嗑萵 陽 餌辨ж朝 輿僥擎?\n","蛤撫紫","溯だ煎", 1,FALSE },
	   { "睡楝霞 鄙蒂 稱橾 陽 餌辨ж朝 輿僥擎?\n","縈蝶ぺ模","嬴夥棻馨棻粽塭", 1, FALSE },
	   { "辨憮嫡雖 跤й 盪輿 醞 ж釭煎 鼻渠蒂 犒謙衛酈朝 輿僥擎?\n","嬴夥棻馨棻粽塭","歜む葬螃" , 2, FALSE },
	   { "跺檜 葆綠腎橫 薑雖衛鑒 陽 餌辨ж朝 輿僥擎?\n","歜む蛤詮顫","歜む腦綠辦蝶", 1, FALSE }
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

		gotoxy(16, 7); printf("%d. %s", sel + 1, question_data[selectnum].question);  // 僥薯

		for (i = 0; i < 2; i++) {  // 摹鷗雖
			gotoxy(19, 11 + i * 3);
			printf("(%d) %s", i + 1, question_data[selectnum].choice[i]);
		}

		gotoxy(18, 19); printf("(1), (2) 醞 ж釭蒂 摹鷗ж撮蹂  :  ");
		key = _getch();
		printf("%c", key);

		key -= 0x30;  // key朝 薑熱⑽檜塭 殮溘嫡擎 高縑憮 滲�紗藥捘鉧萩�						
		if (key == question_data[selectnum].answer) score[1] += 20;

		Sleep(500);
	}
	class2();
}


// 2掖衛

//唳啗摹 轎溘 л熱2
void print_edge2() {
	for (i = 0; i < EX2_R / 2; i++) {
		gotoxy(i * 2, 0); printf("〩");
		gotoxy(i * 2, EX2_C - 1); printf("〩");
	}

	for (i = 1; i < EX2_C - 1; i++) {
		gotoxy(0, i); printf("〩");
		gotoxy(EX2_R - 2, i); printf("〩");
	}
}

// 濰擁僭 薑爾縑 渠и 掘褻羹
typedef struct {
	int    type;   // 謙盟
	int    width;  // 綰楣曖 觼晦
	int    height;
	int    x;      // 轎溘 謝ル
	double y;
	double speed;  // 樓紫
} BULLET_BLOCK;

// 餌辨濠 薑爾縑 渠и 掘褻羹
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

// 濰擁僭 謝ル 塽 樓紫 營撲薑 л熱
void reset_block(BULLET_BLOCK* block) {
	int interval = rand() % 5 + 2;

	block->x = rand() % (EX2_R - 6) + 2;  // 3 ~ (EX2_R - 6 + 3)	
	if (block->x % 2 == 1) block->x++;   // x謝ル陛 �汝鷏� 礎熱煎 滲��

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

// 蟾晦�� л熱
void init2() {	
	for (i = 0; i < MAX_BLOCK; i++) {  // 濰擁僭 蟾晦��
		bullet_block[i].width = 2;
		bullet_block[i].height = 1;
		reset_block(&bullet_block[i]);
	}

	gamer.shape = "∞-∞";  // 餌辨濠 蟾晦��
	gamer.width = 5;
	gamer.height = 1;
	gamer.x = 27;
	gamer.y = EX2_C - 4;
}

//濰擁僭 雖錶輿朝 л熱
void delete_bullet() {
	for (i = 0; i < MAX_BLOCK; i++) {
		gotoxy(bullet_block[i].x, (int)bullet_block[i].y);
		printf("  ");
	}
}

// 濰擁僭 謝ル 塽 轎溘 偵褐 л熱
void update_bullet() {
	for (i = 0; i < MAX_BLOCK; i++) {		
		bullet_block[i].y += bullet_block[i].speed;  // 檜翕(ж鬼)

		if (bullet_block[i].y > 1) {  // y謝ル陛 唳啗摹 嬴楚檜賊			
			if (bullet_block[i].y > EX2_C - 1) {  // �飛� 夤擊 慇橫釭賊 營撲薑		
				reset_block(&bullet_block[i]);
				continue;
			}
			
			switch (bullet_block[i].type) {
			case OBSTACLE:
				gotoxy(bullet_block[i].x, (int)bullet_block[i].y);
				printf("∞");
				break;
			case SNICH:
				YELLOW;
				gotoxy(bullet_block[i].x, (int)bullet_block[i].y);
				printf("≒");
				WHITE;  // 濰擁僭曖 儀鼻虜 滲ж紫煙 
				break;
			}
		}
	}
}

// 餌辨濠 檜翕 л熱
void update_gamer(char key) {
	gotoxy(gamer.x, gamer.y);
	printf("     ");

	// 檜翕 觼晦蒂 掘и棻. �飛� 夤戲煎 釭陛雖 跤ж紫煙 啗骯ж罹 堅薑
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
		gotoxy(62, 2);  // 薑爾 轎溘
		printf("濩擎 蝶棲纂 偃熱");
		gotoxy(62, 3);  // 薑爾 轎溘
		printf("≒ : %2d", cnt2);
		WHITE;
		
		if (_kbhit()) { // 橫集и 殮溘擊 嫡懊擊 陽
			key = _getch();
			update_gamer(key);
		}		

		gotoxy(gamer.x, gamer.y);
		printf("%s", gamer.shape);

		delete_bullet();
		update_bullet();
				
		for (i = 0; i < MAX_BLOCK; i++) {  // 醱給羹觼
			SetRect(&GamerRect, gamer.x, gamer.y, gamer.x + gamer.width, gamer.y + gamer.height);
			SetRect(&BulletRect, bullet_block[i].x, (int)bullet_block[i].y, bullet_block[i].x + bullet_block[i].width, (int)bullet_block[i].y + bullet_block[i].height);

			if (IntersectRect(&CollisionRect, &GamerRect, &BulletRect)) {
				if (bullet_block[i].type == OBSTACLE) { // 綰楝盪縑 蜃戲賊 謙猿
					gameloop = 0;
					break;
				}
				else if (bullet_block[i].type == SNICH) { // 蝶棲纂 濩戲賊 偃熱 隸陛
					reset_block(bullet_block + i);
					cnt2++;
					if (cnt2 == snich_count) { //蝶棲纂 濩擎 偃熱陛 10檜賊 謙猿
						gameloop = 0;
						break;
					}
				}
			}
		}
		Sleep(50);  // 夥煎 部釭幗溥憮 雖翱衛麵邀

		new_time = clock();
		if (new_time - start_time >= 30000) break;  // 薯и衛除 30蟾 雖釭賊 謙猿
	}
	Sleep(100);
	score[2] += snich_count * 10;
	class3();
}


/// 3掖衛

// 嬴蝶酈囀萄 餌辨ж罹 x謝ル高 2寡 п邀
void gotoxy3(int x, int y) {  
	COORD Pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void gotoxyHP3(int x, int y) {
	COORD Pos = { x * 2 , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int warehouse[2][EX3_C][EX3_R] = {                 // 1. 十 漁  2. ﹤ 濰擁僭  3. 〡 雖薑脹 嬪纂
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

 // 盪濰脹 高縑 蜃啪 轎溘п輿朝 л熱
void print_warehouse(int map, int potion) {
	for (i = 0; i < EX3_C; i++) {
		for (j = 0; j < EX3_R; j++) {
			gotoxy3(j, i);

			if (warehouse[map][i][j] == 1) {
				WHITE; printf("十");
			}
			else if (warehouse[map][i][j] == 2) {
				WHITE; printf("﹤");
			}
			else if (warehouse[map][i][j] == 3) {
				WHITE; printf("〡");
			}
			else if (warehouse[map][i][j] == 4) {  
				YELLOW; printf("≒");
			}
			else if (warehouse[map][i][j] == 5) { 
				BLOOD; printf("≒");
			}
			else if (warehouse[map][i][j] == 6) {   
				if (potion == 0) YELGREEN;         // potion 0 橾 陽 YELLO + YELGREEN
				else BLUE;                         // potion 1 橾 陽 YELLO + BLOOD
				printf("≒");
			}
			else if (warehouse[map][i][j] == 7) {  // 賅曄 營猿
				WHITE;
				if (potion == 0) printf("Ⅲ");
				else printf("Ⅶ");
			}
			else printf(" ");
		}
	}
}

void exam3(int potion) {
	system("cls");
	
	int nx = 9, ny = 7;   // ⑷營 嬪纂高	

	int cnt = 3; 
	int item[4], order = 0, overlap;
	int map = rand() % 2;  // 裘 楠渾

	for (i = 0; i < 4; i++) { // 營猿 牖憮 楠渾
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
		gotoxyHP3(nx, ny); printf("/");  // 餌辨濠 轎溘
		int dx = 0, dy = 0;  // 隸馬高 蟾晦��

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

		// 檜翕ж晦 瞪縑
		while (1) {  // 檜翕 褻勒 �挫�
			if (warehouse[map][ny + dy][nx + dx] != 1) {                                    // 檜翕 ж溥朝 夠縑 漁檜 橈戲賊
				if (warehouse[map][ny + dy][nx + dx] == 2) {                                // 濰擁僭 塵堅濠 й 陽
					if (warehouse[map][ny + (dy * 2)][nx + (dx * 2)] == 0 || warehouse[map][ny + (dy * 2)][nx + (dx * 2)] == 3) {  //濰擁僭 塵堅ж 濠朝 夠檜 綠橫氈剪釭 雖薑脹 嬪纂塭賊
						if (warehouse[map][ny + dy][nx + dx] == 3)                          // 雖釭陛紫 滲�倌衋�
							warehouse[map][ny + dy][nx + dx] = 3;
						else warehouse[map][ny + dy][nx + dx] = 0;

						if (warehouse[map][ny + (dy * 2)][nx + (dx * 2)] == 0)              // 綴 夠縑 濰擁僭 塵橫厥擠 
							warehouse[map][ny + (dy * 2)][nx + (dx * 2)] = 2;  
						else warehouse[map][ny + (dy * 2)][nx + (dx * 2)] = item[order++];  // 雖薑脹 嬪纂縑 濰擁僭 塵橫厥戲賊 營猿 釭顫陴 
					}
					else break;
				}
				// 營猿 摹鷗й 陽
				else if (warehouse[map][ny + dy][nx + dx] == 4) {  
					warehouse[map][ny + dy][nx + dx] = 0;          // 營猿 摹鷗ж賊 奢寥戲煎 ル衛
					cnt--;
					if (potion == 0) score[3] += 30;               // 蜃朝 營猿橾陽虜 薄熱 睡罹
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
				nx += dx;    // 隸馬高 渦ж罹 ⑷營嬪纂 偵褐
				ny += dy;
			}
			break;
		}		
		if (cnt == 0) {      // 營猿 3偃 摹鷗ж賊 謙猿
			score[3] += 10;  // 薯и 衛除寰縑 部頂賊 蹺陛 薄熱 
			break;
		}

		new_time = clock();
		if (new_time - start_time >= 30000) break;
	}
	Sleep(500);
	class4();
}


/// 4掖衛

// 顫鰍 薑爾縑 渠и 掘褻羹
typedef struct target {
	int state;          // UP, DOWN
	int pos_x;
	int pos_y;
	clock_t down_time;  
	clock_t	up_time;    
	clock_t	past_time;  // 檜瞪 衛陝	
} target;

target dementors[5];

// 雖な檜 轎溘 л熱
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

// 奢問 л熱. 餌蝙殮棲棻
void print_patronus(x, y) { 
	gotoxy(x - 2, y);     printf(" V V");
	gotoxy(x - 2, y + 1); printf("(   )");
	gotoxy(x - 2, y + 2); printf("/   ′");
	gotoxy(x - 2, y + 3); printf("(  ◢ )");
	gotoxy(x - 2, y + 4); printf(" ��  ��");
}

void delete_patronus(x, y) {
	gotoxy(x - 4, y);     printf("         ");
	gotoxy(x - 4, y + 1); printf("         ");
	gotoxy(x - 4, y + 2); printf("         ");
	gotoxy(x - 4, y + 3); printf("         ");
	gotoxy(x - 4, y + 4); printf("         ");
}

// 顫啃 轎溘 л熱. 蛤詮攪殮棲棻
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

	int pos[5] = { 41,54,67,15,28 };  // x謝ル高 雖薑
	int w_y = 22;                     // wand y謝ル高
	int w_x = 0, d_x = 0;             // pos 檣策蝶 塽 x謝ル高	
	int cnt4 = 0;                      // 蜃轔 �蝦�

	clock_t start_time, new_time, curr_time;
	start_time = clock();

	for (i = 0; i < 5; i++) {  // 顫啃 蟾晦��
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
		for (i = 0; i < 5; i++) {  // 顫啃 轎⑷	
			if (dementors[i].state == 1) {  // UP
				print_dementor(dementors[i].pos_x, dementors[i].pos_y);
			}
			else delete_dementor(dementors[i].pos_x, dementors[i].pos_y);  // DOWN
		}

		print_wand(pos[w_x], w_y);

		gotoxy(62, 1);
		printf("蜃�� �蝦� : %2d", cnt4);

		if (_kbhit()) { // 橫集и 殮溘擊 嫡雖彊嬴紫 顫啃 楠渾 轎⑷
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

			case SPACE: // 奢問
				print_patronus(pos[w_x], dementors[w_x].pos_y + 2);  // 奢問 籤擊 菸
				Sleep(400);

				delete_patronus(pos[w_x], dementors[w_x].pos_y + 2);
				print_patronus(pos[w_x], dementors[w_x].pos_y);
				Sleep(400);

				delete_patronus(pos[w_x], dementors[w_x].pos_y);
				for (i = 0; i < 5; i++) {
					if (dementors[i].state == 1 && pos[w_x] == dementors[i].pos_x) {  // 奢問и 嬪纂縑 顫啃檜 氈歷朝雖 鬚儀
						cnt4++;
						dementors[i].state = 0;  // 蜃懊戲賊 夥煎 DOWN 鼻鷓煎 瞪��
						break;  // и廓縑 ж釭虜 蜃�� 熱 氈晦 陽僥縑 瓊戲賊 緒螳釭馬
					}
				}
				break;
			}
		}
		new_time = clock();
		if (new_time - start_time >= 30000) break;

		curr_time = clock();

		for (i = 0; i < 5; i++) {  // 顫啃 鼻鷓 偵褐
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


/// 5掖衛

//唳啗摹 轎溘 л熱3
void print_edge5() {
	for (i = 0; i < EX5_R / 2; i++) {
		gotoxy(i * 2, 0); printf("〩");
		gotoxy(i * 2, EX5_C - 1); printf("〩");
	}

	for (i = 1; i < EX5_C - 1; i++) {
		gotoxy(0, i); printf("〩");
		gotoxy(EX5_R - 2, i); printf("〩");
	}
}

char* mole[MOLE_SIZE] = { "↘ ↘",
						  "(^ ^)",
						  "O   O" }; //翕僭


char* bucket[BUCKET_SIZE] = { "旨收收旬",
							 "早Ⅴ早",
							"曲收收旭" }; //詳檜鱔

char* blank[BUCKET_SIZE] = { "       ","        " ,"        " };

POINT xy_hole[HOLE_SIZE] = { { 4, 5 }, { 12, 5 }, { 20, 5 },
							 { 4, 10 }, { 12, 10 }, { 20, 10 },
							 { 4, 15 }, { 12, 15 }, { 20, 15 } };//�池� 嬪纂蒂 薑п邀


void genMole(int m[]) {
	int pos, exit = 0, sum = 0;

	while (!exit) {
		pos = rand() % HOLE_SIZE;
		if (m[pos] == 0) {
			m[pos] = MOLE_APPEAR_TIME;
			break;
		} //�江� 翕僭檜 楠渾戲煎 釭螃紫煙 撲薑


		for (int i = 0; i < HOLE_SIZE; i++) {
			if (m[i] > 0) {
				sum++;
				if (sum == HOLE_SIZE) return 0;
			}//賅萇 �江� 翕僭檜 氈擊 唳辦
		}
	}
}


int isHit(int m[], int pos) {
	return (pos >= 0 && m[pos] > 0);
} //pos縑 翕僭檜 氈戲賊 葬欐衛鑑棻


void checkMoleTimer(int m[]) {
	for (i = 0; i < HOLE_SIZE; i++) {
		if (m[i] > 0) m[i]--;
	}
}//翕僭蛔濰衛除


void checkHammerTimer(int h[]) {
	for (i = 0; i < HOLE_SIZE; i++) {
		if (h[i] > 0) h[i]--;
	}
}//詳檜鱔 蛔濰衛除


int keyPlayer(char key, int h[]) {
	int hit_pos = -1;

	for (i = 0; i < HOLE_SIZE; i++) h[i] = 0; // CLEARи 鼻鷓煎 虜虛

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
	} //陝陝 酈嬪纂蒂 馨檜蝶滌煎 雖薑
	return hit_pos;
}

void updateHole(int m[]) {
	int str_pos[] = { 7, 8, 9, 4, 5, 6, 1, 2, 3 };

	for (i = 0; i < HOLE_SIZE; i++) {
		// �飛橦� 翕僭檜 襄營ж賊 ル衛
		if (m[i] > 0) {
			for (j = 0; j < MOLE_SIZE; j++) {
				gotoxy(xy_hole[i].x, xy_hole[i].y + j);
				printf("%s", mole[j]);
			}
		}
		// �飛橦� �� 廓�� ル衛
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
			}// �江� 翕僭檜 氈戲賊
		}
	}
	WHITE;
}// 詳檜鱔ル衛

void deleteHammer(int h[]) {
	for (i = 0; i < HOLE_SIZE; i++) {
			for (j = 0; j < BUCKET_SIZE; j++) {
				gotoxy(xy_hole[i].x, xy_hole[i].y + j - MOLE_SIZE);
				printf("%s", blank[j]);
			}
	}
	
}// 詳檜鱔 雖遺

void exam5() {
	system("cls");

	int mole_hole[HOLE_SIZE] = { 0, };
	int hammer_hole[HOLE_SIZE] = { 0, };
	int closeness = 0, hit_pos, time_count = 0;
	double game_time; // 衛除擊 褒熱⑽戲煎 摹樹
	game_time = GAME_TIME; // 薯и衛除

	start_time = clock();
	print_edge5();
	while (1) {
		
		gotoxy(EX5_R + 1, 2); printf("耀塵紫 論晦 : %3d", closeness);


		game_time -= 0.1;	// 0.1 蟾噶 馬模
		if (game_time <= 0.0) break;

		// 轎溘 嶸雖 顫檜該 羹觼
		checkMoleTimer(mole_hole);
		checkHammerTimer(hammer_hole);

		time_count++;
		if (time_count == GEN_TIME)
		{
			// 翕僭 儅撩
			genMole(mole_hole);
			time_count = 0;
		}

		if (_kbhit()) { // 橫集и 殮溘擊 嫡懊擊 陽
			key = _getch();
			hit_pos = keyPlayer(key, hammer_hole);
			if (hit_pos != MISS) { //MISS 蜃雖 彊擠
				if (isHit(mole_hole, hit_pos)) {
					closeness += 3; //翕僭縑啪 詳檜蒂 輿賊 薄熱隸陛
					mole_hole[hit_pos] = 0; // 翕僭擊 薯剪 鼻鷓煎				
				}
			}
					}
		
		deleteHole(mole_hole);
		// 翕僭, жお 轎溘
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
		printf("Ⅱ");
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