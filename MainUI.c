#include"headerFiles.h"
void MainUI() {
	ScreenPrint(4, 2, "---------------------------------------------");
	ScreenPrint(7, 4, "Tour Reservation and Scheduling System");
	ScreenPrint(8, 6, "- gkgkgkgk -");
	ScreenPrint(4, 8, "---------------------------------------------");
	ScreenPrint(4, 10, "[ M E N U ]");
	ScreenPrint(4, 12, "1. �����ϱ�");
	ScreenPrint(4, 13, "2. ����Ȯ��");
	ScreenPrint(4, 14, "3. �������");
	ScreenPrint(4, 15, "4. ��� ������Ȳ Ȯ��");
	ScreenPrint(4, 26, "Copyright(c) 2018 Team5. all rights reserved. ");
	ScreenPrint(4, 28, "---------------------------------------------");
}

void init(int *MoveBar) { // �ý��� �ʱ�ȭ �ܰ�
	Stage = MAIN;
	*MoveBar = 12;

	// RB �ʱ�ȭ ===========================================
	HT_MakeSentinel();


	// �׷��� �ʱ�ȭ =========================================



}

void Render(int *MoveBar) {

	ScreenClear();
	switch (Stage) {
	case MAIN:
		MainUI();
		SelectBAR(*MoveBar);
		break;
	case RESERVATION:
		break;
	case CHECK:
		break;
	case CANCEL:
		break;
	case CHECKALL:
		break;
	}

	ScreenFlipping();
}

void SelectBAR(int Move) {
	ScreenPrint(2, Move, "��");
}