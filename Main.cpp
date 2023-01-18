#include <iostream>
using namespace std;

#include "ATMMachine.h"
int main() {
	int select; // �޴� ���� ��ȣ
	bool openATM = true; // �������� Ű
	ATMMachine atm(100, 50000, "010-0000-0000", "admin");

	while (openATM) {
		atm.displayMenu();
		cout << "�޴��� �����ϼ���: ";
		cin >> select;
		cout << endl;

		switch (select)
		{
		case 1: // ���� ����
			atm.createAccount();
			break;
		case 2: // ���� ��ȸ
			atm.checkMoney();
			break;
		case 3: // ���� �Ա�
			atm.depositMoney();
			break;
		case 4: // ���� ���
			atm.widrawMoney();
			break;
		case 5: // ���� ��ü
			atm.transfer();
			break;
		case 6: // ���� ����
			atm.closeAccount();
			break;
		case 7: // �� ����
			atm.managerMode();
			break;
		case 9: // ���� ����
			if (atm.closeATM()) { openATM = !openATM; } // ������ �����ȴٸ� while�� ����������
			break;
		default:
			cout << "��ȣ Ȯ�� �� �ٽ� �Է��ϼ���." << endl;
			break;
		}
	}


	return 0;
}