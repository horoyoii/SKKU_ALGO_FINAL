#pragma once
#include"RSV_RBT.h"

#define Administratorpassword "admin" //������ ��й�ȣ admin

void	CheckAllUI(RSV_node_ptr Head);
void RSV_Inorder(RSV_node_ptr head);
void ShowReserveInfo(RSV_node_ptr head, int IdxPos, int IdyPos);
int Administratorlogin();