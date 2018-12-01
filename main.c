#include"headerFiles.h"

/*
 * Created by SKKU_ALGO Team5 on 2018.11.18
*/

int main(void) {
	// INIT ======================================
	graph_ptr gp;
	HT_MakeSentinel();
	MakeSentinel();
	GraphInit(&gp);
	RSV_node_ptr ReserveHead = RSV_MakeRBT();
	int nKey, MoveBar;
	ScreenInit();
	init(&MoveBar);
	while (1) {
		switch (Stage) {
		case RESERVATION:
			ScreenRelease(); ScreenClearFunc();
			ReservationUI(gp, &ReserveHead);
			Stage = MAIN;
			ScreenInit();
			break;
		case CHECK:
			ScreenRelease(); ScreenClearFunc();
			CheckUI(&ReserveHead);
			Stage = MAIN;
			ScreenInit();
			break;
		case CANCEL:
			ScreenRelease(); ScreenClearFunc();
			CancelUI(&ReserveHead);
			Stage = MAIN;
			ScreenInit(); 
			break;
		case CHECKALL:
			ScreenRelease(); ScreenClearFunc();
			CheckAllUI(ReserveHead);
			Stage = MAIN;
			ScreenInit(); // Screen restart
			while (getchar() != '\n');
			break;
		default: // MAIN ȭ��
			if (_kbhit()) {
				nKey = _getch();
				if (nKey == 13) { // Mainȭ�鿡�� enter �Է½� MoveBar�� ����Ű�� �ִ� Stage�� ����
					Stage = MoveBar - 11;
				}
				if (nKey == 224) { // Mainȭ�鿡�� ����Ű�� ���� MoveBar�� �����̴� ����
					nKey = _getch();
					switch (nKey) {
					case UP:
						MoveBar--;
						break;
					case DOWN:
						MoveBar++;
						break;
					case LEFT: // �ڷΰ���
						Stage = MAIN;
						break;
					case RIGHT:
						break;
					}
				}
			}
			break;
		}
		Render(&MoveBar);  // ȭ�����
	}
	ScreenRelease();
	return 0;
}


