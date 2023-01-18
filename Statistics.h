#pragma once
#ifndef STATISTCIS_H
#define STATISTCIS_H
#include "Account.h"

class Statistics
{
private:
	static void quick_sort(Account* pArray, int size); // �� ����
public:
	static int sum(Account* pArray, int size);     // ���� �ܰ� ����
	static int average(Account* pArray, int size); // ���� �ܰ� ���
	static int max(Account* pArray, int size);     // ���� �ܰ� �ְ�
	static void sort(Account* pArray, int size);    // ���� ���� ����
	
};

#endif // !STATISTCIS_H
