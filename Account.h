#pragma once
#include <iostream>

#ifndef ACCOUNT_H
#define ACCOUNT_H

using std::string;

#define AUTHENTIFICATION_FAIL -1  // ���� ���� ����
#define AUTHENTIFICATION_SUCCESS 1 // ���� ���� ����
#define LACK_OF_BALANCE -2 // �ܾ� ���� -> ���� ��� �� ���� �� �ܾ��� ������ ���, return ���� ����ϱ� ���� ����־����ϴ�.

class Account
{
private:
	int nID; // ���� ��ȣ
	int nBalance; // �ܰ� (�ʱⰪ = 0)
	string strAccountName; // �� ��
	string strPassword; // ���� ��й�ȣ

	inline bool authenticate(int id, string passwd); // ���� ����: true(1), ���� ����: false(0)
	inline bool authenticate(int id); // ��뿡�� ��ü�Ҷ� ���̵� �� ��� ����

public:
	Account();
	void create(int id, int money, string name, string passwd); // ���� ����
	void close(); // ���� ����
	int deposit(int id, int money); // ��� ���� �Ա�
	int deposit(int id, string password, int money); // ���� �Ա�
	int widraw(int id, string password, int money); // ���� ��� 
	int cheak(int id); // ��� ���� üũ
	int check(int id, string password); // return �� : nBalance(�ܰ�) or ���� ���� (AUTHENTIFICATION_FAIL)
	int getAcctID() { return nID; } // ���¹�ȣ �о����
	int getBalance() { return nBalance; };// �ܰ� ��ȯ
	string getAccountName() { return strAccountName; }; // �� �� ��ȯ
};


#endif // !ACCOUNT_H
