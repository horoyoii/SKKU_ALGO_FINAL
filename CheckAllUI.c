#include"headerFiles.h"


int IdxPos, IdyPos; // Global 2, 3

void CheckAllUI(RSV_node_ptr head) {
	gotoxy(0, 0); printf(" ");
	// 저장된 모든 예약현황 출력
	gotoxy(2, 0); printf("[모든 예약현황 확인]");
	gotoxy(0, 2); printf("=======================================================================================================================");
	gotoxy(0, 4); printf("=======================================================================================================================");
	gotoxy(0, 3); printf("ID"); gotoxy(16, 3); printf("출발"); gotoxy(23, 3); printf("도착"); gotoxy(30, 3); printf("스케쥴 정보"); 
	
	IdxPos = 0;
	IdyPos = 6;
	RSV_Inorder(head);
	gotoxy(40, 0); printf("메인화면 돌아가려면 enter 입력");
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
	gotoxy(30, IdyPos + 1); printf("[경로]\t");
	while (temp != NULL) {
		printf("S-%d\t", temp->CityNum);
		if (temp->next == NULL) {
			gotoxy(23, IdyPos); printf("S-%d", temp->CityNum);
			CostSum = head->InputBudget - temp->Budget;
		}
		temp = temp->next;
	}
	temp = Data;
	gotoxy(30, IdyPos + 3); printf("[호텔]\t");
	while (temp != NULL) {
		printf("H-%d\t", temp->Hotel);
		temp = temp->next;
	}
	
	temp = Data;
	gotoxy(30, IdyPos + 5); printf("[기간]\t");
	while (temp != NULL) {
		printf("%d\t", temp->Day);
		DaySum += temp->Day;
		temp = temp->next;
	}
	gotoxy(82, IdyPos + 6); printf("\t\t\t[총 기간] : %d", DaySum);
	gotoxy(82, IdyPos + 7); printf("\t\t\t[비용] : %d", CostSum);
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

int Administratorlogin() {
	//while (getchar() != '\n');
	// 입력 ====================================================
	char inputpassword[100], Check[2] = { 0, }; int i = 0;
	gotoxy(2, 1); printf("[관리자 로그인이 필요합니다.]");
	gotoxy(2, 3); printf("=================================================");
	gotoxy(2, 4); printf("Password : ");
	gotoxy(2, 5); printf("=================================================");
	gotoxy(12, 4);
	char ch;
	while (1) {
		ch = getch();
		if(ch != '\0'){
			inputpassword[i] = ch;
			if (inputpassword[i] != '\r') {
				printf("*");
				i++;
			}
			else break;
		}
	}
	inputpassword[i] = 0;
				   

	
	if (strcmp(inputpassword, Administratorpassword) == 0) {
		gotoxy(2, 7); printf("[로그인 성공]");
		Sleep(1000);
		return 1;
	}
	else {
		gotoxy(2, 7); printf("[비밀번호가 틀렸습니다.]");
		gotoxy(2, 9); printf("메인화면 돌아가려면 enter 입력");
		return 0;
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
gotoxy(30, IdyPos + 1); printf("[경로]\t");
while (temp != NULL) {
printf("S-%d\t", temp->CityNum);
if (temp->next == NULL) {
gotoxy(23, IdyPos); printf("S-%d", temp->CityNum);
CostSum = head->InputBudget - temp->Budget;
}
temp = temp->next;
}
temp = Data;
gotoxy(30, IdyPos + 3); printf("[호텔]\t");
while (temp != NULL) {
printf("H-%d\t", temp->Hotel);
temp = temp->next;
}

temp = Data;
gotoxy(30, IdyPos + 5); printf("[기간]\t");
while (temp != NULL) {
printf("%d\t", temp->Day);
DaySum += temp->Day;
temp = temp->next;
}
gotoxy(82, IdyPos + 6); printf("\t\t\t[총 기간] : %d", DaySum);
gotoxy(82, IdyPos + 7); printf("\t\t\t[비용] : %d", CostSum);
gotoxy(1, IdyPos + 8); printf("---------------------------------------------------------------------------------------------------------------------");

}
*/