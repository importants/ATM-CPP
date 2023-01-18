#include <iostream>
#include <random> // ������ ���¹�ȣ�� ����� ���� ���
using namespace std;


#include "ATMMachine.h"
#include "Account.h"
#include "Statistics.h"

ATMMachine::ATMMachine(int size, int balance, string phoneNumber, string password): nMaxAccountNum(size), mMachineBalance(balance), strManagerPassword(password), phoneNumber(phoneNumber)
{
	this->pAcctArray = new Account[this->nMaxAccountNum];  // �� ���� ���� ���� ����
	this->nCurrentAccountNum = 0;
	this->accounts = new int[this->nMaxAccountNum]; // ���¹�ȣ �迭 ���� ���� ����
}

ATMMachine::~ATMMachine()
{
	// ������� ���¸� Ȯ���� �� �ְ� �߽��ϴ�. (������ ���� ����)
	/*
	cout << "���� ATM�� ����� ����" << endl;
	for (int i = 0; i < this->nCurrentAccountNum; i++) {
		cout << accounts[i] << " ";
	}
	cout << endl;
	*/

	// ���� �޸� ���� ���� ����
	delete[] pAcctArray; 
	delete[] accounts; // ���¹�ȣ�� �ߺ��� ���� �ʱ� ���� �迭
	cout << "�ȳ��� ������"<< endl;
}

void ATMMachine::displayMenu() { // ATM ��� ���� ȭ��
	cout << "                             " << endl;
	cout << "-----------------------------" << endl;
	cout << "-       TUKOREA BANK        -" << endl;
	cout << "-----------------------------" << endl;
	cout << "1. ���� ����" << endl;
	cout << "2. ���� ��ȸ" << endl;
	cout << "3. ���� �Ա�" << endl;
	cout << "4. ���� ���" << endl;
	cout << "5. ���� ��ü" << endl;
	cout << "6. ���� ����" << endl;
	cout << "7. �� ����" << endl;
	cout << "9. ���� ����" << endl;
};
void ATMMachine::createAccount() {  // ���� ����
	int nID;
	int nBalance;
	string name;
	string password;

	if (nCurrentAccountNum != nMaxAccountNum) {	
		//		-> account�� create()�� �Ű����� nID�� �ֱ� ������ ���� ���� ���⼭ ���� ����־����ϴ�.
		
		nBalance = 0;
		if (nCurrentAccountNum == 0) { 
			nID = random();
			this->accounts[0] = nID;
		}
		else {
			// ���°��� ��ġ�� �ʱ� ���� �ڵ带 �����߽��ϴ�.
			while (1) {
				nID = random();
				if (!checkNumber(nID))
					continue;

				this->accounts[nCurrentAccountNum] = nID;
					
				break;
			}
		}

		cout << "----------- ���� --------------" << endl;
		cout << "�̸� �Է�: ";
		cin >> name;
		cout << "��ȣ �Է�: ";
		cin >> password;

		pAcctArray[nCurrentAccountNum++].create(nID, nBalance, name, password);
	}
	else {
		cout << "���� ���¸� ������ ������ �����ϴ�.";
	}

}

void ATMMachine::checkMoney() { // ���� ��ȸ
	int nID;
	int accountMoney = AUTHENTIFICATION_FAIL;// �ʱⰪ
	string password;
	cout << "----------- ��ȸ --------------" << endl;
	cout << "���¹�ȣ �Է�: ";
	cin >> nID;
	cout << "��й�ȣ �Է�: ";
	cin >> password;

	for (int i = 0; i < this->nCurrentAccountNum; i++) {
		accountMoney = this->pAcctArray[i].check(nID, password);
		if (accountMoney >= 0) {
			cout << "���� �ܾ�: " << accountMoney << endl;
			break;
		}
	}

	if (accountMoney == AUTHENTIFICATION_FAIL) {
		cout << "������ ���°� �����ϴ�. ���¸� Ȯ�����ֽʽÿ�." << endl;
	}
}

void ATMMachine::depositMoney() { // �����Ա�
	int nID;
	int depositMoney;
	int accountMoney = AUTHENTIFICATION_FAIL;
	string password;


	cout << "----------- �Ա� --------------" << endl;
	cout << "���¹�ȣ �Է�: ";
	cin >> nID;
	cout << "��й�ȣ �Է�: ";
	cin >> password;
	cout << "�Աݾ� �Է�: ";
	cin >> depositMoney;

	for (int i = 0; i < this->nCurrentAccountNum; i++) {
		accountMoney = this->pAcctArray[i].deposit(nID, password, depositMoney);
		if (accountMoney >= 0) {
			cout << "���� �ܾ�: " << accountMoney << endl;
			this->mMachineBalance += depositMoney;
			break;
		}
	}

	if (accountMoney == AUTHENTIFICATION_FAIL) {
		cout << "������ ���°� �����ϴ�. ���¸� Ȯ�����ֽʽÿ�." << endl;
	}

}

void ATMMachine::widrawMoney() { // �������
	int nID;
	int widrawMoney;
	int accountMoney = AUTHENTIFICATION_FAIL;
	string password;

	cout << "----------- ��� --------------" << endl;
	cout << "���¹�ȣ �Է�: ";
	cin >> nID;
	cout << "��й�ȣ �Է�: ";
	cin >> password;
	cout << "��ݾ� �Է�: ";
	cin >> widrawMoney;

	if (this->mMachineBalance >= widrawMoney) {

		for (int i = 0; i < this->nCurrentAccountNum; i++) {
			accountMoney = this->pAcctArray[i].widraw(nID, password, widrawMoney);
			if (accountMoney >= 0) {
				cout << "���� �ܾ�: " << accountMoney << endl;
				this->mMachineBalance -= widrawMoney;
				break;
			}
		}

		if (accountMoney == AUTHENTIFICATION_FAIL) {
			cout << "������ ���°� �����ϴ�. ���¸� Ȯ�����ֽʽÿ�." << endl;
		}
		else if (accountMoney == LACK_OF_BALANCE) {
			cout << "����� �ܾ��� �����մϴ�." << endl;
		}
	}
	else {
		cout << "ATM�� ����� �� �ִ� ������ �����ϴ�. �����ڿ��� �����Ͻñ� �ٶ��ϴ�.\n" << "������ ��ȭ��ȣ: " << this->phoneNumber << endl;
	}
}

//MARK: �߰� ���1
void ATMMachine::transfer() { // ���� ��ü
	int nID;
	int transferID; // ������� ���̵�
	int transferMoney; // ����ݾ�
	int transferIndex; // ��� ���� �ε���
	bool isEnabled = false;
	int accountMoney = AUTHENTIFICATION_FAIL;
	string password;

	cout << "----------- ��ü --------------" << endl;
	cout << "���¹�ȣ �Է�: ";
	cin >> nID;
	cout << "��й�ȣ �Է�: ";
	cin >> password;
	cout << "��ü���� �Է�: ";
	cin >> transferID;
	for (int i = 0; i < this->nCurrentAccountNum; i++) {
		if (AUTHENTIFICATION_FAIL != this->pAcctArray[i].cheak(transferID)) {
			isEnabled = true;
			transferIndex = i; // �迭 �ε����� �ٷ� ã�� ���� �ļ�
			break;
		}
	}

	cout << "��ü�ݾ� �Է�: ";
	cin >> transferMoney;

	if (this->mMachineBalance >= transferMoney) {

		if (isEnabled) { // ��� ���°� ���� ��
			for (int i = 0; i < this->nCurrentAccountNum; i++) {

				accountMoney = this->pAcctArray[i].widraw(nID, password, transferMoney);
				if (accountMoney >= 0) {
					cout << "���� �ܾ�: " << accountMoney << endl;
					this->mMachineBalance -= transferMoney;
					
					if (AUTHENTIFICATION_FAIL != this->pAcctArray[transferIndex].deposit(transferID, transferMoney)) {
						cout << "----------- ��ü���� --------------" << endl;
					}
					else {
						cout << "----------- ��ü���� --------------" << endl;
					}
					break;
				}
			}

			if (accountMoney == AUTHENTIFICATION_FAIL) {
				cout << "������ ���°� �����ϴ�. ���¸� Ȯ�����ֽʽÿ�." << endl;
			}
			else if (accountMoney == LACK_OF_BALANCE) {
				cout << "����� �ܾ��� �����մϴ�." << endl;
			}
		}
		else { // ��� ���°� ���� ��
			cout << "��ü�� ���¹�ȣ�� �����ϴ�. �ٽ� Ȯ�����ֽʽÿ�." << endl;
		}
	}
	else {
		cout << "ATM�� ����� �� �ִ� ������ �����ϴ�. �����ڿ��� �����Ͻñ� �ٶ��ϴ�.\n" << "������ ��ȭ��ȣ: " << this->phoneNumber << endl;
	}
}

void ATMMachine::closeAccount() {  // ���� ����
	int nID;
	int accountMoney = AUTHENTIFICATION_FAIL;// �ʱⰪ
	string password;
	cout << "----------- ��ȸ --------------" << endl;
	cout << "���¹�ȣ �Է�: ";
	cin >> nID;
	cout << "��й�ȣ �Է�: ";
	cin >> password;

	for (int i = 0; i < this->nCurrentAccountNum; i++) {
		accountMoney = this->pAcctArray[i].check(nID, password);
		if (accountMoney == 0) {
			this->pAcctArray[i].close();
			this->nCurrentAccountNum--;
			break;
		}
		else if (accountMoney > 0) {
			cout << nID << "���¸� ������ �� �����ϴ�. �ܾ�: " << accountMoney << endl;
		}
	}

	if (accountMoney == AUTHENTIFICATION_FAIL) {
		cout << "������ ���°� �����ϴ�. ���¸� Ȯ�����ֽʽÿ�." << endl;
	}
}

//MARK:�߰����2
void ATMMachine::managerMode() { // �� ����
	string strManagerPassword;
	cout << "----------- ���� --------------" << endl;
	cout << "������ ��й�ȣ �Է�: ";
	cin >> strManagerPassword;

	if (this->isManager(strManagerPassword)) {
		cout << "�������Դϴ�." << endl << endl;
		cout << "-------------------------------" << endl;
		this->displayReport(); // ���ȭ�� ó��
		cout << "-------------------------------" << endl;
		cout << "------ �� ���� ��� ---------" << endl;
		cout << "-------------------------------" << endl;
		Statistics::sort(this->pAcctArray, this->nCurrentAccountNum);
	}
	else {
		cout << "�����ڰ� �ƴմϴ�." << endl;

	}
}

bool ATMMachine::isManager(string password) {
	if(this->strManagerPassword == password)
		return 1;
	else 
		return 0;
}

void ATMMachine::displayReport() {
	cout << "ATM  ���� �ܰ�:   " 
		<< this->mMachineBalance << endl;
	cout << "�� �ܰ� �Ѿ�:   " 
		<< Statistics::sum(this->pAcctArray,this->nCurrentAccountNum) 
		<< "  (�� " << this->nCurrentAccountNum << "��)" << endl;
	cout << "�� �ܰ� ���:   " 
		<< Statistics::average(this->pAcctArray, this->nCurrentAccountNum) << endl;
	cout << "�� �ܰ� �ְ�:   " 
		<< Statistics::max(this->pAcctArray, this->nCurrentAccountNum) << endl;
}

bool ATMMachine::closeATM() { // ATM ��������
	return true;
}

// ���� ������ ���¿� ������ �� �ο� ( �ߺ� x )
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