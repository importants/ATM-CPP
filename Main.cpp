#include <iostream>
using namespace std;

#include "ATMMachine.h"
int main() {
	int select; // 메뉴 선택 번호
	bool openATM = true; // 업무종료 키
	ATMMachine atm(100, 50000, "010-0000-0000", "admin");

	while (openATM) {
		atm.displayMenu();
		cout << "메뉴를 선택하세요: ";
		cin >> select;
		cout << endl;

		switch (select)
		{
		case 1: // 계좌 개설
			atm.createAccount();
			break;
		case 2: // 계좌 조회
			atm.checkMoney();
			break;
		case 3: // 계좌 입금
			atm.depositMoney();
			break;
		case 4: // 계좌 출금
			atm.widrawMoney();
			break;
		case 5: // 계좌 이체
			atm.transfer();
			break;
		case 6: // 계좌 해지
			atm.closeAccount();
			break;
		case 7: // 고객 관리
			atm.managerMode();
			break;
		case 9: // 업무 종료
			if (atm.closeATM()) { openATM = !openATM; } // 조건이 만족된다면 while문 빠져나가기
			break;
		default:
			cout << "번호 확인 후 다시 입력하세요." << endl;
			break;
		}
	}


	return 0;
}