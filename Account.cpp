#include <iostream>
#include <random>
#include "Account.h"


using namespace std;

Account::Account()
{
	this->nID = AUTHENTIFICATION_FAIL;
	this->nBalance = AUTHENTIFICATION_FAIL;
}

void Account::create(int id, int money, string name, string passwd) { // 계좌 개설
	this->nID = id;
	this->nBalance = money;
	this->strAccountName = name;
	this->strPassword = passwd;
	cout << strAccountName << "님 " << this->getAcctID() << "번 계좌번호가 정상적으로 개설되었습니다. 감사합니다." << endl;
} 


inline bool  Account::authenticate(int id) { // 계좌 해지
	if (this->nID == id) {
		return true;
	}
	else {
		return false;
	}
}

inline bool  Account::authenticate(int id, string passwd) { // 계좌 해지
	if (this->nID == id && this->strPassword == passwd) {
		return true;
	}
	else {
		return false;
	}
}



int Account::cheak(int id) { // 상대에게 이체할때 아이디만 알 경우
	if (this->authenticate(id)) {
		return AUTHENTIFICATION_SUCCESS;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}

int Account::check(int id, string password) { // return 값 : nBalance(잔고) or 인증 실패 (AUTHENTIFICATION_FAIL)
	if (this->authenticate(id,password)) {
		return this->nBalance;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}

int Account::deposit(int id, int money) { // 상대 계좌 입금
	if (this->authenticate(id)) {
		return this->nBalance += money;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}

int Account::deposit(int id, string password, int money) { // 계좌 입금
	if (this->authenticate(id, password)) {
		return this->nBalance += money;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}

int Account::widraw(int id, string password, int money) { // 계좌 출금
	if (this->authenticate(id, password)) {
		if (this->nBalance >= money) { return this->nBalance -= money; }
		return LACK_OF_BALANCE;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
}

void Account::close() { // 계좌 해지
	cout << this->getAcctID() << "계좌가 해지되었습니다. 감사합니다." << endl;
	this->nID = AUTHENTIFICATION_FAIL;
	this->nBalance = AUTHENTIFICATION_FAIL;
	this->strAccountName = "";
	this->strPassword = "";
}
