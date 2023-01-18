#include <iostream>
#include <random>
#include "Account.h"


using namespace std;

Account::Account()
{
	this->nID = AUTHENTIFICATION_FAIL;
	this->nBalance = AUTHENTIFICATION_FAIL;
}

void Account::create(int id, int money, string name, string passwd) { // ���� ����
	this->nID = id;
	this->nBalance = money;
	this->strAccountName = name;
	this->strPassword = passwd;
	cout << strAccountName << "�� " << this->getAcctID() << "�� ���¹�ȣ�� ���������� �����Ǿ����ϴ�. �����մϴ�." << endl;
} 


inline bool  Account::authenticate(int id) { // ���� ����
	if (this->nID == id) {
		return true;
	}
	else {
		return false;
	}
}

inline bool  Account::authenticate(int id, string passwd) { // ���� ����
	if (this->nID == id && this->strPassword == passwd) {
		return true;
	}
	else {
		return false;
	}
}



int Account::cheak(int id) { // ��뿡�� ��ü�Ҷ� ���̵� �� ���
	if (this->authenticate(id)) {
		return AUTHENTIFICATION_SUCCESS;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}

int Account::check(int id, string password) { // return �� : nBalance(�ܰ�) or ���� ���� (AUTHENTIFICATION_FAIL)
	if (this->authenticate(id,password)) {
		return this->nBalance;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}

int Account::deposit(int id, int money) { // ��� ���� �Ա�
	if (this->authenticate(id)) {
		return this->nBalance += money;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}

int Account::deposit(int id, string password, int money) { // ���� �Ա�
	if (this->authenticate(id, password)) {
		return this->nBalance += money;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}

int Account::widraw(int id, string password, int money) { // ���� ���
	if (this->authenticate(id, password)) {
		if (this->nBalance >= money) { return this->nBalance -= money; }
		return LACK_OF_BALANCE;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}

void Account::close() { // ���� ����
	cout << this->getAcctID() << "���°� �����Ǿ����ϴ�. �����մϴ�." << endl;
	this->nID = AUTHENTIFICATION_FAIL;
	this->nBalance = AUTHENTIFICATION_FAIL;
	this->strAccountName = "";
	this->strPassword = "";
}
