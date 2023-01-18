#include <iostream>
#include <algorithm>
using namespace std;


#include "Statistics.h"

int Statistics:: sum(Account* pArray, int size) { // °èÁÂ ÀÜ°í ÃÑÇÕ
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += pArray[i].getBalance();
	}
	return sum;
}     

int Statistics::average(Account* pArray, int size) { // °èÁÂ ÀÜ°í Æò±Õ
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += pArray[i].getBalance();
	}
	return sum/size;
} 

int Statistics::max(Account* pArray, int size) { // °èÁÂ ÀÜ°í ÃÖ°í
	int maxBalance = 0;
	int balance = 0;
	for (int i = 0; i < size; i++) {
		balance = pArray[i].getBalance();
		if(balance >= maxBalance) maxBalance = balance;
	}
	return maxBalance;
}     

void Statistics::sort(Account* pArray, int size) { // ³»¸² Â÷¼ø Á¤·Ä
	quick_sort(pArray, size);

	for (int i = 0; i < size; i++) {
		cout << i << ".  "
			<< pArray[i].getAccountName() << "      "
			<< pArray[i].getAcctID() << "    "
			<< pArray[i].getBalance() << "¿ø"
			<< endl;
	}
}   

void Statistics::quick_sort(Account* pArray, int size) { // ³»¸² Â÷¼ø Á¤·Ä

	Account pivot = pArray[0];
	int cursor = 0;

	for (int i = 1; i < size; i++) {
		if (pivot.getBalance() < pArray[i].getBalance()) {
			cursor++;
			swap(pArray[cursor], pArray[i]);
		}
	}

	swap(pArray[0], pArray[cursor]);

	if (cursor > 0) {
		quick_sort(pArray, cursor);
	}

	if (cursor + 1 < size - 1) {
		quick_sort(pArray + cursor +1, size - cursor - 1);
	}
}

