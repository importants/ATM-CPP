#pragma once
#include <iostream>
#include "Account.h"

#ifndef ATMMACHINE_H
#define ATMMACHINE_H

using std::string;

#define NEGATIVE_ATM_BLANCE -10 // ATM �ܾ� ����
#define BASE_ACCOUNT_ID 100  // ���¹�ȣ�� 100�� ���� 1000 ���� �������� �ο�


class ATMMachine
{
private:
	Account* pAcctArray; // ���� ������ ������ �迭 ������
	int mMachineBalance; // ATM �ܰ�
	int nMaxAccountNum; // ���� ������ �� ���� �迭 ũ��
	int nCurrentAccountNum; // ������ �� ���� �� 

	string phoneNumber; // ������ ��ȭ��ȣ			-> ���� ATM�� �ܾ��� ���� �� �������� ��ȭ��ȣ�� �����ְ� �ϰ� �;� ����־����ϴ�. 
	string strManagerPassword; // ������ ��й�ȣ

	bool isManager(string password);// �Ŵ��� ��ȣ Ȯ��
	void displayReport(); // ��� ȭ�� ó��

	int *accounts; // �������� �� ���� ���� ��ġ�� �ʱ� ���� ��������ϴ�.

public:
	ATMMachine(int size, int balance, string phoneNumber, string password); // ���� �迭ũ��, ATM �ܰ�,������ ��ȣ, ������ ��ȣ �ʱ�ȭ
	~ATMMachine();
	void displayMenu(); // ATM ��� ���� ȭ��
	void createAccount(); // ���� ����
	int random(); // ������ ��(���¹�ȣ) return
	bool checkNumber(int random); // �ߺ��Ǵ� ���� �ִ��� cheak�ϴ� �Լ�
	void closeAccount(); // ���� ����
	void checkMoney(); // ���� ��ȸ
	void depositMoney(); // ���� �Ա�
	void widrawMoney(); // ���� ���
	void transfer(); // ���� ��ü
	bool closeATM(); // ���� ����

	void managerMode(); // �� ����
};




#endif // !ATMMACHINE_H
