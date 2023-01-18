#pragma once
#include <iostream>

#ifndef ACCOUNT_H
#define ACCOUNT_H

using std::string;

#define AUTHENTIFICATION_FAIL -1  // 계정 인증 실패
#define AUTHENTIFICATION_SUCCESS 1 // 계정 인증 성공
#define LACK_OF_BALANCE -2 // 잔액 부족 -> 만약 출금 시 계좌 내 잔액이 부족할 경우, return 값을 사용하기 위해 집어넣었습니다.

class Account
{
private:
	int nID; // 계좌 번호
	int nBalance; // 잔고 (초기값 = 0)
	string strAccountName; // 고객 명
	string strPassword; // 계좌 비밀번호

	inline bool authenticate(int id, string passwd); // 인증 성공: true(1), 인증 실패: false(0)
	inline bool authenticate(int id); // 상대에게 이체할때 아이디만 알 경우 인증

public:
	Account();
	void create(int id, int money, string name, string passwd); // 계좌 개설
	void close(); // 계좌 혜지
	int deposit(int id, int money); // 상대 계좌 입금
	int deposit(int id, string password, int money); // 계좌 입금
	int widraw(int id, string password, int money); // 계좌 출금 
	int cheak(int id); // 상대 계좌 체크
	int check(int id, string password); // return 값 : nBalance(잔고) or 인증 실패 (AUTHENTIFICATION_FAIL)
	int getAcctID() { return nID; } // 계좌번호 읽어오기
	int getBalance() { return nBalance; };// 잔고 반환
	string getAccountName() { return strAccountName; }; // 고객 명 반환
};


#endif // !ACCOUNT_H
