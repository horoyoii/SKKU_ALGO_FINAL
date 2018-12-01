#include"headerFiles.h"


int IdxPos, IdyPos; // Global 2, 3

void CheckAllUI(RSV_node_ptr head) {
	gotoxy(0, 0); printf(" ");
	// ����� ��� ������Ȳ ���
	gotoxy(2, 0); printf("[��� ������Ȳ Ȯ��]");
	gotoxy(0, 2); printf("=======================================================================================================================");
	gotoxy(0, 4); printf("=======================================================================================================================");
	gotoxy(0, 3); printf("ID"); gotoxy(16, 3); printf("���"); gotoxy(23, 3); printf("����"); gotoxy(30, 3); printf("������ ����"); 
	
	IdxPos = 0;
	IdyPos = 6;
	RSV_Inorder(head);
	gotoxy(40, 0); printf("����ȭ�� ���ư����� enter �Է�");
}

void ShowReserveInfo(RSV_node_ptr head, int IdxPos, int IdyPos) {
	gotoxy(IdxPos, IdyPos); printf("%s  ", head->Key);
	hotel_site_ptr Data = head->Path;
	hotel_site_ptr temp;
	int DaySum = 0;
	int CostSum = 0;
	//Path
	temp = Data;
	gotoxy(16, IdyPos); printf("S-%d", temp->CityNum);
	gotoxy(30, IdyPos + 1); printf("[���]\t");
	while (temp != NULL) {
		printf("S-%d\t", temp->CityNum);
		if (temp->next == NULL) {
			gotoxy(23, IdyPos); printf("S-%d", temp->CityNum);
			CostSum = head->InputBudget - temp->Budget;
		}
		temp = temp->next;
	}
	temp = Data;
	gotoxy(30, IdyPos + 3); printf("[ȣ��]\t");
	while (temp != NULL) {
		printf("H-%d\t", temp->Hotel);
		temp = temp->next;
	}
	
	temp = Data;
	gotoxy(30, IdyPos + 5); printf("[�Ⱓ]\t");
	while (temp != NULL) {
		printf("%d\t", temp->Day);
		DaySum += temp->Day;
		temp = temp->next;
	}
	gotoxy(82, IdyPos + 6); printf("\t\t\t[�� �Ⱓ] : %d", DaySum);
	gotoxy(82, IdyPos + 7); printf("\t\t\t[���] : %d", CostSum);
	gotoxy(1, IdyPos + 8); printf("---------------------------------------------------------------------------------------------------------------------");

}


void RSV_Inorder(RSV_node_ptr head) {
	if (head != Sentinel) {
		RSV_Inorder(head->left);
		ShowReserveInfo(head, IdxPos, IdyPos);
		IdyPos += 9;
		RSV_Inorder(head->right);
	}
}


/*
void ShowReserveInfo(RSV_node_ptr head) {
gotoxy(IdxPos, IdyPos); printf("%s  ", head->Key);
hotel_site_ptr Data = head->Path;
hotel_site_ptr temp;
int DaySum = 0;
int CostSum = 0;
//Path
temp = Data;
gotoxy(16, IdyPos); printf("S-%d", temp->CityNum);
gotoxy(30, IdyPos + 1); printf("[���]\t");
while (temp != NULL) {
printf("S-%d\t", temp->CityNum);
if (temp->next == NULL) {
gotoxy(23, IdyPos); printf("S-%d", temp->CityNum);
CostSum = head->InputBudget - temp->Budget;
}
temp = temp->next;
}
temp = Data;
gotoxy(30, IdyPos + 3); printf("[ȣ��]\t");
while (temp != NULL) {
printf("H-%d\t", temp->Hotel);
temp = temp->next;
}

temp = Data;
gotoxy(30, IdyPos + 5); printf("[�Ⱓ]\t");
while (temp != NULL) {
printf("%d\t", temp->Day);
DaySum += temp->Day;
temp = temp->next;
}
gotoxy(82, IdyPos + 6); printf("\t\t\t[�� �Ⱓ] : %d", DaySum);
gotoxy(82, IdyPos + 7); printf("\t\t\t[���] : %d", CostSum);
gotoxy(1, IdyPos + 8); printf("---------------------------------------------------------------------------------------------------------------------");

}
*/