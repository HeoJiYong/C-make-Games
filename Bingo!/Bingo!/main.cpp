/*
����: ���� ���� �����
������: ������
���� ��¥: 2018-09-20
*/

#include <iostream>
#include <ctime>

using namespace std;

const int STAR = -1;

int main(void)
{
	// 1 ~ 25�� ������ �ʱ�ȭ
	int iNumber[25] = {};

	for (int i = 0; i < 25; i++)
		iNumber[i] = i + 1;

	srand((unsigned)time(NULL));

	// �������� ������ ���� �ش�
	int idx1, idx2, temp;
	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;
		temp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = temp;
	}

	bool finish = false;
	while (!finish)
	{
		system("cls");
		// ���� ���
		for (int i = 0; i < 25; i++)
		{
			if (iNumber[i] == STAR)
				cout << '*' << '\t';
			else
				cout << iNumber[i] << '\t';

			if ((i + 1) % 5 == 0)
				cout << '\n';
		}

		cout << "���ڸ� �Է��ϼ���(0 ����)> ";
		int input;
		cin >> input;

		// ��������
		if (input == 0)
			finish = true;

		// ���� ó��
		if (input < 1 || input > 25)
			continue;

		// �ߺ� üũ
		bool bAcc = true;
		for (int i = 0; i < 25; i++)
		{
			if (input == iNumber[i])
			{
				// ���ڸ� ã���� �ߺ��� �ƴϹǷ�
				bAcc = false;
				// *�� �ٲٱ� ���� STAR�� �����Ѵ�
				iNumber[i] = STAR;
				// �� �̻� ã�� �ʿ䰡 �����Ƿ� break
				break;
			}
		}

	}

	return 0;
}