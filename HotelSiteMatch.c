#include"headerFiles.h"

hotel_site_ptr HS_MATCH(node_ptr node, graph_ptr gp, int budget, int period) { //��γ�带 ������ ��ġ
	hotel_site_ptr head;
	hotel_site_ptr ptr;
	node_ptr nptr = node;
	int sitenum = 0; //��� ��θ� ���������� head����
	int hotelbudget = budget; //hotel���࿡ �� ��
	int hotelbudgetday;

	nptr = nptr->next;
	while (nptr != NULL) { //��� ������ ��� ����
		hotelbudget -= 20 * nptr->Weight;
		nptr = nptr->next;
	}
	hotelbudgetday = hotelbudget / period; //�Ϸ翡 �� ��
	nptr = node;


	head = HS_SATISFACTION(nptr, gp, hotelbudgetday);
	head->Budget = budget; //head�� ���� �ѿ���
	head->next = NULL;
	ptr = head;
	nptr = nptr->next;
	sitenum++;


	while (nptr != NULL) {
		ptr->next = HS_SATISFACTION(nptr, gp, hotelbudgetday);
		ptr->next->Budget = ptr->Budget - 20 * nptr->Weight; //ȣ�ڻ���Ʈ�� ���� ��� ���� !!Weight(1~100) *20
		ptr = ptr->next;
		nptr = nptr->next;
		sitenum++; //��� ���϶����� site ���� ����
		if (ptr->Budget < 0) return NULL; //budget 0���� ������ NULL; ��� �������� ������ ���� ����
	}
	//hotelbudget = ptr->Budget; //��ΰ�� ���� ���� budget;
	

	/*ptr = head;
	nptr = node;
	while (ptr != NULL) {
		ptr = HS_SATISFACTION(nptr, gp, hotelbudgetday);
		ptr = ptr->next;
		nptr = nptr->next;
	}*/



	head = HS_DAY(head, period, sitenum);

	return head; //head�� NULL�̸� ���ٴ� ��
}//��ο� ������ ȣ�� ���´�.->�������� ��¥ ����

hotel_site_ptr HS_SATISFACTION(node_ptr node, graph_ptr gp, int budget) { //���� �̸��� ������ ������, �������� ����ؼ� ���� ���� ȣ�� ������ ���� ��带 ����
	hotel_site_ptr hotelsite = (hotel_site_ptr)malloc(sizeof(HotelSite));
	int satisfaction;
	//int pricesatis;
	//int prefersatis;
	int citynum = node->CityNum;
	int preference = gp->CityInfo[citynum].perference;
	HT_RBnode_ptr temp = getAllHotelinfo(gp, citynum); //citynum�� ȣ�� Ʈ�� ��
	HT_RBnode_ptr Hotel = HotelMatch(temp, budget);
	//if (Hotel == NULL) return NULL;
	int price = Hotel->Key;

	//pricesatis = 3000 - 3 * Hotel->Key; //���� 1~1000�϶�
	//prefersatis = preference * 400; //���� 0~5
	//satisfaction = pricesatis + prefersatis;
	satisfaction = preference * 400; //���� 0~5

	hotelsite->CityNum = citynum;
	hotelsite->Preference = preference;
	hotelsite->Hotel = Hotel->Hotel_Num;
	hotelsite->Price = Hotel->Key;
	hotelsite->Satisfaction = satisfaction;
	hotelsite->Day = 1; //������ �ּ� �Ϸ� ����
	hotelsite->next = NULL;

	return hotelsite;

}

hotel_site_ptr HS_DAY(hotel_site_ptr head, int period, int sitenum) {  //������ �������� ���� �Ⱓ ��� (�Ϸ� ���������� ������-500) budget -�� �� ���, budget����
	hotel_site_ptr select_day; //��¥�� ���� ȣ��
	int minusbudget = 0;
	int dayleft = period - sitenum;
	int i;
	int maxsatis;
	int budgetleft = -1;
	int minprice = 2000;
	int maxprice = -1;
	int satis_day; //������ ��¥ ȯ��
	hotel_site_ptr ptr = head;
	if (ptr == NULL) return NULL; //ptr NULL���� Ȯ��



	if (dayleft < 0) { //��μ��� ���� ������ Ŭ ��
		return NULL;
	}
	else if (dayleft == 0) { //��μ��� ���� ���� ���� ��
		return head;
	}
	else { //��μ����� ���� ���� Ŭ��

		while (ptr != NULL) {//price ������, ��������
			if (ptr->Price < minprice) minprice = ptr->Price;
			if (ptr->Price > maxprice) maxprice = ptr->Price;
			budgetleft = ptr->Budget; //��������尡 ���� ���
			ptr = ptr->next;
		}
		ptr = head;


		if (ptr != NULL)

			for (i = 0; i < dayleft; i++) {//�������� �۴��� budget���� ��Ű��
				if (budgetleft < minprice*(dayleft - i)) return NULL;
				if (budgetleft > minprice*(dayleft - i) && budgetleft < minprice*(dayleft - (i + 1)) + maxprice) {
					ptr = head;
					while (ptr != NULL) {
						if (ptr->Budget == minprice)
							ptr->Day += (dayleft - i);
					}
					break;
				}


				ptr = head;
				maxsatis = -10000; //�ʱⰪ
				while (ptr != NULL) {
					satis_day = ptr->Satisfaction - (300 * (ptr->Day - 1)); //��¥ ȯ�� �Ϸ� ���������� ������ 300�� ����
					if (maxsatis < satis_day) {
						maxsatis = satis_day;
						select_day = ptr;
					}
					ptr = ptr->next;
				}
				select_day->Day++;

			}

	}
	ptr = head;
	while (ptr != NULL) {
		minusbudget = minusbudget + ptr->Price*(ptr->Day);
		ptr->Budget = ptr->Budget - minusbudget;
		ptr = ptr->next;
	}	//budget ���� budget -�� �� return NULL;

	return head;
}

HT_RBnode_ptr HotelMatch(HT_RBnode_ptr root, int budget) { //���꺸�� �����鼭 ���� ���꿡 ����� ȣ�� ã��
	

	HT_RBnode_ptr ptr = root;
	while (ptr != NULL) {
		
		if (ptr->Key== budget) {
			return ptr;
		}
		else if (ptr->Key < budget) {
			if (ptr->right->Key==-1) return ptr;
			ptr= ptr->right;
		}
		else {
			if (ptr->left->Key == -1)
				return HT_TREE_PREDECESSOR(ptr);
			ptr = ptr->left;
		}
	}
	return ptr;
}

