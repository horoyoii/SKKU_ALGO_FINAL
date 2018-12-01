#include"headerFiles.h"

void ShowTempInfo(graph_ptr gp, hotel_site_ptr head, int StartPos, int DestPos, int InputBudget){
	int IdxPos = 15;
	int IdyPos = 18;
	hotel_site_ptr temp = head;
	int DaySum = 0;
	int CostSum = 0;

	//Path
	gotoxy(2, IdyPos); printf("S-%d", temp->CityNum);
	gotoxy(IdxPos, IdyPos + 1); printf("[���]\t");
	while (temp != NULL) {
		IdxPos += 12;
		gotoxy(IdxPos, IdyPos + 1); printf("S-%d", temp->CityNum);
		if (temp->next == NULL) {
			gotoxy(9, IdyPos); printf("S-%d", temp->CityNum);
			CostSum += temp->Budget;
		}
		temp = temp->next;
	}


	// Rate
	temp = head; IdxPos = 15;
	gotoxy(IdxPos, IdyPos + 2); printf("[����]\t");
	while (temp != NULL) {
		IdxPos += 12;
		gotoxy(IdxPos, IdyPos + 2);
		switch (gp->CityInfo[temp->CityNum].perference) {
		case 0:
			printf("�١١١١�");
			break;
		case 1:
			printf("�ڡ١١١�");
			break;
		case 2:
			printf("�ڡڡ١١�");
			break;
		case 3:
			printf("�ڡڡڡ١�");
			break;
		case 4:
			printf("�ڡڡڡڡ�");
			break;
		case 5:
			printf("�ڡڡڡڡ�");
			break;
		}
		temp = temp->next;
	}


	// Hotel
	temp = head; IdxPos = 15;
	gotoxy(IdxPos, IdyPos + 4); printf("[ȣ��]\t");
	while (temp != NULL) {
		IdxPos += 12;
		gotoxy(IdxPos, IdyPos + 4);
		printf("H-%d", temp->Hotel);
		temp = temp->next;
	}
	// Hotel Rate
	temp = head; IdxPos = 15;
	gotoxy(IdxPos, IdyPos + 5); printf("[����]\t");
	while (temp != NULL) {
		IdxPos += 12;
		gotoxy(IdxPos, IdyPos + 5);
		switch (temp->rate) {
		case 1:
			printf("�ڡ١�");
			break;
		case 2:
			printf("�ڡڡ�");
			break;
		case 3:
			printf("�ڡڡ�");
			break;
		}
		temp = temp->next;
	}

	// Day
	temp = head; IdxPos = 15;
	gotoxy(IdxPos, IdyPos + 7); printf("[�Ⱓ]\t");
	while (temp != NULL) {
		IdxPos += 12;
		gotoxy(IdxPos, IdyPos + 7);
		printf("%d", temp->Day);
		DaySum += temp->Day;
		temp = temp->next;
	}
	gotoxy(82, IdyPos + 8); printf("\t\t\t[�� �Ⱓ] : %d", DaySum);
	gotoxy(82, IdyPos + 9); printf("\t\t\t[�ܾ�] : %d", CostSum);
	gotoxy(1, IdyPos + 10); printf("---------------------------------------------------------------------------------------------------------------------");

}

int askConfirmUI() {
	gotoxy(50, 29); printf("�����Ͻðڽ��ϱ�? (Y/N)");
	char nKey;
	scanf("%c", &nKey);
	if (nKey == 'y' || nKey == 'Y')
		return 1;
	else
		return 0;
}

void ReservationUI(graph_ptr gp, RSV_node_ptr *ReserveHead) {
	fflush(stdin);
	gotoxy(3, 1); printf("[�����ϱ�] - "); textcolor(10); printf("[�����Է�]"); textcolor(15); printf(" - [Ȯ��] ");
	gotoxy(3, 3); printf("=================================================");
	gotoxy(3, 5); printf("ID : ");
	gotoxy(3, 7); printf("����� : ");
	gotoxy(3, 9); printf("������ : ");
	gotoxy(3, 11); printf("��  �� : ");
	gotoxy(3, 13); printf("��  �� : ");
	gotoxy(2, 17); printf("==============================================================");

	int StartPos, DestPos;
	char id[50];
	int Period;
	int budget;

	ReservInput(&StartPos, &DestPos, id, &Period, &budget);
	node_ptr ShortestPath = Dijkstra(gp, StartPos, DestPos);
	hotel_site_ptr Data;
	if (ShortestPath != NULL) {
		Data = HS_MATCH(ShortestPath, gp, budget, Period);
		if (Data != NULL) {
			gotoxy(2, 15); printf("====================================================================================================================");
			gotoxy(2, 16); gotoxy(2, 16); printf("���"); gotoxy(9,16); printf("����"); gotoxy(15, 16); printf("������ ����");
			ShowTempInfo(gp, Data, StartPos, DestPos, budget);
			if (askConfirmUI()) {
				RSV_RB_INSERT(ReserveHead, id, Data, budget);
				gotoxy(50, 30); printf("<<����Ϸ�>>");
				gotoxy(50, 31); printf("����ȭ�� ���ư����� enter �Է�");
				//Sleep(5000);
				
			}
		}
		else {
			gotoxy(10, 20); printf("<<������� �ʰ�>>");
			gotoxy(10, 21); printf("����ȭ�� ���ư����� enter �Է�");
			//Sleep(5000);
		}
	}
	else { // ���� ���
		gotoxy(10, 20); printf("<<��ξ���>>");
		gotoxy(10, 21); printf("����ȭ�� ���ư����� enter �Է�");
		//Sleep(5000);
	}
	while (getchar() != '\n');//test
}

void ReservInput(int *StartPos, int *DestPos, char *id, int *Period, int *budget) {
	
	gotoxy(12, 5); fgets(id, 20, stdin); strtok(id, "\n");
	gotoxy(12, 7); scanf("%d", StartPos);
	gotoxy(12, 9); scanf("%d", DestPos);
	gotoxy(12, 11); scanf("%d", Period);
	while (getchar() != '\n');
	gotoxy(12, 13); scanf("%d", budget);
	while (getchar() != '\n');
}

