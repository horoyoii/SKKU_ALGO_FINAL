#include"headerFiles.h"


int CancelUI(RSV_node_ptr *head) {
	// �Է� ====================================================
	char inputId[100], Check[2] = { 0, };
	gotoxy(2, 1); printf("[���������Է�] - [���]");
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
		
		gotoxy(50, 18); printf("����Ͻðڽ��ϱ�? (Y/N)");
		char nKey;
		scanf("%c", &nKey);
		if (nKey == 'y' || nKey == 'Y') {
			RSV_RB_DELETE(head, temp->Key);
			gotoxy(50, 20); printf("��ҵǾ����ϴ�.");
			Sleep(3000);
		}
		else if (nKey == 'n' || nKey == 'N') {

		}
		else {

		}
	}
	else {
		gotoxy(2, 7); printf("<< �ش� ���� ���� >>");
		gotoxy(2, 10); printf("����ȭ�� ���ư����� enter �Է�");
		while (getchar() != '\n');
	}
	//while (getchar() != '\n');

	return 1;
}