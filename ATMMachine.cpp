#include <iostream>
#include <random> // 랜덤한 계좌번호를 만들기 위한 헤더
using namespace std;


#include "ATMMachine.h"
#include "Account.h"
#include "Statistics.h"

ATMMachine::ATMMachine(int size, int balance, string phoneNumber, string password): nMaxAccountNum(size), mMachineBalance(balance), strManagerPassword(password), phoneNumber(phoneNumber)
{
	this->pAcctArray = new Account[this->nMaxAccountNum];  // 고객 계좌 동적 공간 생성
	this->nCurrentAccountNum = 0;
	this->accounts = new int[this->nMaxAccountNum]; // 계좌번호 배열 동적 공간 생성
}

ATMMachine::~ATMMachine()
{
	// 만들어진 계좌를 확인할 수 있게 했습니다. (해제된 계좌 제외)
	/*
	cout << "오늘 ATM을 사용한 계좌" << endl;
	for (int i = 0; i < this->nCurrentAccountNum; i++) {
		cout << accounts[i] << " ";
	}
	cout << endl;
	*/

	// 동적 메모리 공간 연결 해제
	delete[] pAcctArray; 
	delete[] accounts; // 계좌번호가 중복이 되지 않기 위한 배열
	cout << "안녕히 가세요"<< endl;
}

void ATMMachine::displayMenu() { // ATM 기능 선택 화면
	cout << "                             " << endl;
	cout << "-----------------------------" << endl;
	cout << "-       TUKOREA BANK        -" << endl;
	cout << "-----------------------------" << endl;
	cout << "1. 계좌 개설" << endl;
	cout << "2. 계좌 조회" << endl;
	cout << "3. 계좌 입금" << endl;
	cout << "4. 계좌 출금" << endl;
	cout << "5. 계좌 이체" << endl;
	cout << "6. 계좌 해지" << endl;
	cout << "7. 고객 관리" << endl;
	cout << "9. 업무 종료" << endl;
};
void ATMMachine::createAccount() {  // 계좌 개설
	int nID;
	int nBalance;
	string name;
	string password;

	if (nCurrentAccountNum != nMaxAccountNum) {	
		//		-> account의 create()의 매개변수 nID가 있기 때문에 랜덤 값을 여기서 만들어서 집어넣었습니다.
		
		nBalance = 0;
		if (nCurrentAccountNum == 0) { 
			nID = random();
			this->accounts[0] = nID;
		}
		else {
			// 계좌값이 겹치지 않기 위해 코드를 구성했습니다.
			while (1) {
				nID = random();
				if (!checkNumber(nID))
					continue;

				this->accounts[nCurrentAccountNum] = nID;
					
				break;
			}
		}

		cout << "----------- 개설 --------------" << endl;
		cout << "이름 입력: ";
		cin >> name;
		cout << "암호 입력: ";
		cin >> password;

		pAcctArray[nCurrentAccountNum++].create(nID, nBalance, name, password);
	}
	else {
		cout << "현재 계좌를 생성할 공간이 없습니다.";
	}

}

void ATMMachine::checkMoney() { // 계좌 조회
	int nID;
	int accountMoney = AUTHENTIFICATION_FAIL;// 초기값
	string password;
	cout << "----------- 조회 --------------" << endl;
	cout << "계좌번호 입력: ";
	cin >> nID;
	cout << "비밀번호 입력: ";
	cin >> password;

	for (int i = 0; i < this->nCurrentAccountNum; i++) {
		accountMoney = this->pAcctArray[i].check(nID, password);
		if (accountMoney >= 0) {
			cout << "현재 잔액: " << accountMoney << endl;
			break;
		}
	}

	if (accountMoney == AUTHENTIFICATION_FAIL) {
		cout << "고객님의 계좌가 없습니다. 계좌를 확인해주십시오." << endl;
	}
}

void ATMMachine::depositMoney() { // 계좌입금
	int nID;
	int depositMoney;
	int accountMoney = AUTHENTIFICATION_FAIL;
	string password;


	cout << "----------- 입금 --------------" << endl;
	cout << "계좌번호 입력: ";
	cin >> nID;
	cout << "비밀번호 입력: ";
	cin >> password;
	cout << "입금액 입력: ";
	cin >> depositMoney;

	for (int i = 0; i < this->nCurrentAccountNum; i++) {
		accountMoney = this->pAcctArray[i].deposit(nID, password, depositMoney);
		if (accountMoney >= 0) {
			cout << "현재 잔액: " << accountMoney << endl;
			this->mMachineBalance += depositMoney;
			break;
		}
	}

	if (accountMoney == AUTHENTIFICATION_FAIL) {
		cout << "고객님의 계좌가 없습니다. 계좌를 확인해주십시오." << endl;
	}

}

void ATMMachine::widrawMoney() { // 계좌출금
	int nID;
	int widrawMoney;
	int accountMoney = AUTHENTIFICATION_FAIL;
	string password;

	cout << "----------- 출금 --------------" << endl;
	cout << "계좌번호 입력: ";
	cin >> nID;
	cout << "비밀번호 입력: ";
	cin >> password;
	cout << "출금액 입력: ";
	cin >> widrawMoney;

	if (this->mMachineBalance >= widrawMoney) {

		for (int i = 0; i < this->nCurrentAccountNum; i++) {
			accountMoney = this->pAcctArray[i].widraw(nID, password, widrawMoney);
			if (accountMoney >= 0) {
				cout << "현재 잔액: " << accountMoney << endl;
				this->mMachineBalance -= widrawMoney;
				break;
			}
		}

		if (accountMoney == AUTHENTIFICATION_FAIL) {
			cout << "고객님의 계좌가 없습니다. 계좌를 확인해주십시오." << endl;
		}
		else if (accountMoney == LACK_OF_BALANCE) {
			cout << "출금할 잔액이 부족합니다." << endl;
		}
	}
	else {
		cout << "ATM에 출금할 수 있는 현금이 없습니다. 관리자에게 연락하시기 바랍니다.\n" << "관리자 전화번호: " << this->phoneNumber << endl;
	}
}

//MARK: 추가 기능1
void ATMMachine::transfer() { // 계좌 이체
	int nID;
	int transferID; // 입출계좌 아이디
	int transferMoney; // 입출금액
	int transferIndex; // 상대 계좌 인덱스
	bool isEnabled = false;
	int accountMoney = AUTHENTIFICATION_FAIL;
	string password;

	cout << "----------- 이체 --------------" << endl;
	cout << "계좌번호 입력: ";
	cin >> nID;
	cout << "비밀번호 입력: ";
	cin >> password;
	cout << "이체계좌 입력: ";
	cin >> transferID;
	for (int i = 0; i < this->nCurrentAccountNum; i++) {
		if (AUTHENTIFICATION_FAIL != this->pAcctArray[i].cheak(transferID)) {
			isEnabled = true;
			transferIndex = i; // 배열 인덱스로 바로 찾기 위한 꼼수
			break;
		}
	}

	cout << "이체금액 입력: ";
	cin >> transferMoney;

	if (this->mMachineBalance >= transferMoney) {

		if (isEnabled) { // 상대 계좌가 있을 시
			for (int i = 0; i < this->nCurrentAccountNum; i++) {

				accountMoney = this->pAcctArray[i].widraw(nID, password, transferMoney);
				if (accountMoney >= 0) {
					cout << "현재 잔액: " << accountMoney << endl;
					this->mMachineBalance -= transferMoney;
					
					if (AUTHENTIFICATION_FAIL != this->pAcctArray[transferIndex].deposit(transferID, transferMoney)) {
						cout << "----------- 이체성공 --------------" << endl;
					}
					else {
						cout << "----------- 이체실패 --------------" << endl;
					}
					break;
				}
			}

			if (accountMoney == AUTHENTIFICATION_FAIL) {
				cout << "고객님의 계좌가 없습니다. 계좌를 확인해주십시오." << endl;
			}
			else if (accountMoney == LACK_OF_BALANCE) {
				cout << "출금할 잔액이 부족합니다." << endl;
			}
		}
		else { // 상대 계좌가 없을 시
			cout << "이체할 계좌번호가 없습니다. 다시 확인해주십시오." << endl;
		}
	}
	else {
		cout << "ATM에 출금할 수 있는 현금이 없습니다. 관리자에게 연락하시기 바랍니다.\n" << "관리자 전화번호: " << this->phoneNumber << endl;
	}
}

void ATMMachine::closeAccount() {  // 계좌 해지
	int nID;
	int accountMoney = AUTHENTIFICATION_FAIL;// 초기값
	string password;
	cout << "----------- 조회 --------------" << endl;
	cout << "계좌번호 입력: ";
	cin >> nID;
	cout << "비밀번호 입력: ";
	cin >> password;

	for (int i = 0; i < this->nCurrentAccountNum; i++) {
		accountMoney = this->pAcctArray[i].check(nID, password);
		if (accountMoney == 0) {
			this->pAcctArray[i].close();
			this->nCurrentAccountNum--;
			break;
		}
		else if (accountMoney > 0) {
			cout << nID << "계좌를 해지할 수 없습니다. 잔액: " << accountMoney << endl;
		}
	}

	if (accountMoney == AUTHENTIFICATION_FAIL) {
		cout << "고객님의 계좌가 없습니다. 계좌를 확인해주십시오." << endl;
	}
}

//MARK:추가기능2
void ATMMachine::managerMode() { // 고객 관리
	string strManagerPassword;
	cout << "----------- 관리 --------------" << endl;
	cout << "관리자 비밀번호 입력: ";
	cin >> strManagerPassword;

	if (this->isManager(strManagerPassword)) {
		cout << "관리자입니다." << endl << endl;
		cout << "-------------------------------" << endl;
		this->displayReport(); // 통계화면 처리
		cout << "-------------------------------" << endl;
		cout << "------ 고객 계좌 목록 ---------" << endl;
		cout << "-------------------------------" << endl;
		Statistics::sort(this->pAcctArray, this->nCurrentAccountNum);
	}
	else {
		cout << "관리자가 아닙니다." << endl;

	}
}

bool ATMMachine::isManager(string password) {
	if(this->strManagerPassword == password)
		return 1;
	else 
		return 0;
}

void ATMMachine::displayReport() {
	cout << "ATM  현재 잔고:   " 
		<< this->mMachineBalance << endl;
	cout << "고객 잔고 총액:   " 
		<< Statistics::sum(this->pAcctArray,this->nCurrentAccountNum) 
		<< "  (총 " << this->nCurrentAccountNum << "명)" << endl;
	cout << "고객 잔고 평균:   " 
		<< Statistics::average(this->pAcctArray, this->nCurrentAccountNum) << endl;
	cout << "고객 잔고 최고:   " 
		<< Statistics::max(this->pAcctArray, this->nCurrentAccountNum) << endl;
}

bool ATMMachine::closeATM() { // ATM 업무종료
	return true;
}

// 새로 생성된 계좌에 랜덤한 값 부여 ( 중복 x )
int ATMMachine::random() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(BASE_ACCOUNT_ID, 1000);
	return dis(gen);
}

bool ATMMachine::checkNumber(int random) {
	for (int i = 0; i < this->nCurrentAccountNum; i++) {
		if (random == this->accounts[i])
			return false;
	}
	return true;
}