#include"headerFiles.h"


void CheckUI(RSV_node_ptr *head) {
	while (getchar() != '\n');
	// �Է� ====================================================
	char inputId[100], Check[2] = { 0, };
	gotoxy(2, 1); printf("[���������Է�] - [Ȯ��]");
	gotoxy(2, 3); printf("=================================================");
	gotoxy(2, 4); printf("ID �Է� : ");
	gotoxy(2, 5); printf("=================================================");
	gotoxy(12, 4); scanf("%[^\n]", inputId);
	while (getchar() != '\n');
	// ��ȸ ===================================================
	RSV_node_ptr temp = RSV_TREE_SEARCH(*head, inputId);
	char nKey;
	int MoveBar;
	if (temp != Sentinel) {
		gotoxy(2, 5); printf("====================================================================================================================");
		gotoxy(2, 6); printf("ID"); gotoxy(16, 6); printf("���"); gotoxy(23, 6); printf("����"); gotoxy(30, 6); printf("������ ����");
		ShowReserveInfo(temp, 2, 8);

		gotoxy(2, 20); printf("����ȭ�� ���ư����� enter �Է�");
		while (getchar() != '\n');
	}
	else {
		gotoxy(2, 7); printf("<< �ش� ���� ���� >>");
		gotoxy(2, 10); printf("����ȭ�� ���ư����� enter �Է�");
		while (getchar() != '\n');
	}
}