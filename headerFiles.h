#pragma once



// ===============================
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#include<stdbool.h>
#include<time.h>
#include<conio.h>



// ====================================
#include"HT_RBT.h"
#include"Screen.h"
#include"MainUI.h"
#include"ReservationUI.h"
#include"CheckAllUI.h"
#include"Graph.h"
#include"RSV_RBT.h"
#include"HotelSiteMatch.h"
#include"Dummy.h"
#include"CancelUI.h"
#include"CheckUI.h"


// ====================================
#define _CRT_SECURE_NO_WARNINGS
#define LEFT 75 
#define RIGHT 77 
#define UP 72 
#define DOWN 80 

typedef enum _STAGE {
	MAIN, RESERVATION, CHECK, CANCEL, CHECKALL
	// ����ȭ��, 1) �����ϱ� 2) ���  3) ����  4) ��� ������Ȳ
}STAGE;
STAGE Stage;