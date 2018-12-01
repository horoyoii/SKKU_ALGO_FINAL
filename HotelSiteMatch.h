#pragma once

#include"Graph.h"

typedef struct HOTEL_SITE_MATCH *hotel_site_ptr;
typedef struct HOTEL_SITE_MATCH {
	int CityNum;      //HS_SATIS���� ä��κ�, ���� �̸�
	int Preference;		//����
	int Hotel;         //HS_SATIS���� ä��κ�, ȣ�� �̸�
	int Satisfaction;   //HS_SATIS���� ä��κ�, ������
	int Price;          //HS_SATIS���� ä��κ�, ȣ�� ����
	int Day;         //HS_DAY ���� ��
	int Budget;         //HS_DAY, �׵��ÿ��� ������ ������ ������ ������
	hotel_site_ptr next;
}HotelSite;

hotel_site_ptr HS_MATCH(node_ptr node, graph_ptr gp, int budget, int period);
hotel_site_ptr HS_SATISFACTION(node_ptr node, graph_ptr gp);
hotel_site_ptr HS_DAY(hotel_site_ptr head, int period, int sitenum);
HT_RBnode_ptr HotelMatch(HT_RBnode_ptr root, int budget);