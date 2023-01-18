#pragma once
#include <iostream>
#include "Account.h"

#ifndef ATMMACHINE_H
#define ATMMACHINE_H

using std::string;

#define NEGATIVE_ATM_BLANCE -10 // ATM 잔액 부족
#define BASE_ACCOUNT_ID 100  // 계좌번호는 100번 부터 1000 사이 랜덤으로 부여


class ATMMachine
{
private:
	Account* pAcctArray; // 동적 생성된 고객계좌 배열 포인터
	int mMachineBalance; // ATM 잔고
	int nMaxAccountNum; // 동적 생성된 고객 계좌 배열 크기
	int nCurrentAccountNum; // 개설된 고객 계좌 수 

	string phoneNumber; // 관리자 전화번호			-> 만약 ATM의 잔액이 없을 시 관리자의 전화번호를 보여주게 하고 싶어 집어넣었습니다. 
	string strManagerPassword; // 관리자 비밀번호

	bool isManager(string password);// 매니저 암호 확인
	void displayReport(); // 통계 화면 처리

	int *accounts; // 랜덤으로 된 계좌 값이 겹치지 않기 위해 만들었습니다.

public:
	ATMMachine(int size, int balance, string phoneNumber, string password); // 계좌 배열크기, ATM 잔고,관리자 번호, 관리자 암호 초기화
	~ATMMachine();
	void displayMenu(); // ATM 기능 선택 화면
	void createAccount(); // 계좌 개설
	int random(); // 랜덤한 값(계좌번호) return
	bool checkNumber(int random); // 중복되는 값이 있는지 cheak하는 함수
	void closeAccount(); // 계좌 해지
	void checkMoney(); // 계좌 조회
	void depositMoney(); // 계좌 입금
	void widrawMoney(); // 계좌 출금
	void transfer(); // 계좌 이체
	bool closeATM(); // 업무 종료

	void managerMode(); // 고객 관리
};




#endif // !ATMMACHINE_H
