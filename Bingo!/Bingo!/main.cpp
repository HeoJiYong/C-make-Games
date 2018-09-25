/*
����: ���� ���� �����
������: ������
���� ��¥: 2018-09-25
*/

#include <iostream>
#include <ctime>
#include <Windows.h>

using namespace std;

enum AI_MODE {EASY = 1, HARD};	// AI ���̵�

enum LINE// ���� ���� 12��
{
	LN_H1, LN_H2, LN_H3, LN_H4, LN_H5,	// ���� ���� ����
	LN_V1, LN_V2, LN_V3, LN_V4, LN_V5,	// ���� ���� ����
	LN_LT, LN_RT	// �밢�� ���� ����
};

const int STAR = -1;	// * ǥ�ø� ���� ���� STAR

int main(void)
{
	// ����, AI ������
	int iNumber[25];
	int AINumber[25];

	// ����, AI ������ �ʱ�ȭ
	for (int i = 0; i < 25; i++)
		AINumber[i] = iNumber[i] = i + 1;

	srand((unsigned)time(NULL));

	// AI ���̵� ����
	int mode;
	while (true)
	{
		system("cls");
		mode;
		cout << "AI ���̵� ����(1:EASY, 2:HARD): ";
		cin >> mode;
		if (mode == 1 || mode == 2)
			break;
	}

	// �������� ������ ���� �ش�
	int idx1, idx2, temp;
	for (int i = 0; i < 100; i++)
	{
		// ������ ������
		idx1 = rand() % 25;
		idx2 = rand() % 25;
		temp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = temp;

		// AI�� ������
		idx1 = rand() % 25;
		idx2 = rand() % 25;
		temp = AINumber[idx1];
		AINumber[idx1] = AINumber[idx2];
		AINumber[idx2] = temp;
	}

	bool finish = false; //�ݺ��� ����

	int bingoLine = 0, AIbingoLine = 0;	// user�� AI�� ���� ��

	bool userSelect = true; // user�Է� �Ǻ�
	
	while (!finish)
	{
		system("cls");

		// ���� ���� ���
		cout << "================User===============" << endl;
		for (int i = 0; i < 25; i++)
		{
			if (iNumber[i] == STAR)
				cout << '*' << '\t';
			else
				cout << iNumber[i] << '\t';

			if ((i + 1) % 5 == 0)
				cout << '\n';
		}

		cout << "User Bingo Line: " << bingoLine << endl << endl;
		if (bingoLine >= 5)

		{
			cout << "User �¸�!" << endl;
			break;
		}

		// AI ���� ���
		cout << "=================AI================" << endl;
		for (int i = 0; i < 25; i++)
		{
			if (AINumber[i] == STAR)
				cout << '*' << '\t';
			else
				cout << AINumber[i] << '\t';

			if ((i + 1) % 5 == 0)
				cout << '\n';
		}

		cout << "AI Bingo Line: " << AIbingoLine << endl << endl;
		if (AIbingoLine >= 5)
		{
			cout << "AI �¸�!" << endl;
			break;
		}
		
		int input;	// ���� �Է� ����
		
		if (userSelect) // user ����
		{
			// ���� �Է�
			cout << "���ڸ� �Է��ϼ���(0 ����)> ";
			cin >> input;

			// ��������
			if (input == 0)
				finish = true;

			// ���� ó��
			if (input < 1 || input > 25)
				continue;

			// ������ �ѹ� ���� �� �� AI�� ����
			userSelect = false;
		}
		else // AI ����
		{
			if (mode == EASY)	// �������� ���� ������ �����ϰ� ����
			{
				int count = 0;
				int arr[25];
				for (int i = 0; i < 25; i++)
				{
					if (AINumber[i] != STAR)
						arr[count++] = AINumber[i];
				}
				input = arr[rand() % count];
			}
				
			if (mode == HARD)	// ���� ���� ���ɼ��� ���� ���ο��� ����
			{
				int count = 0;
				int max_star = 0;	// 5�� �����߿��� ���� ���� ���� ����
				int line = 0;		// max_star�� ���� (enum LINE���� ����)

				for (int i = 0; i < 5; i++)
				{
					count = 0;
					for (int j = 0; j < 5; j++)
					{
						// ���� ���� üũ
						if (AINumber[i * 5 + j] == STAR)
						{
							++count;
						}

						if (max_star <= count && count < 5)
						{
							line = i;
							max_star = count;
						}
					}
				}

				for (int i = 0; i < 5; i++)
				{
					count = 0;
					for (int j = 0; j < 5; j++)
					{
						// ���� ���� üũ
						if (AINumber[i + j * 5] == STAR)
						{
							++count;
						}

						if (max_star < count && count < 5)
						{
							line = i + 5;
							max_star = count;
						}
					}
				}

				// ���� -> ������ �밢�� üũ
				count = 0;
				for (int i = 0; i < 25; i += 6)
				{
					if (AINumber[i] == STAR)
					{
						++count;
					}
				}
				if (max_star < count && count < 5)
				{
					line = LN_LT;
					max_star = count;
				}

				// ������ -> ���� �밢�� üũ
				count = 0;
				for (int i = 4; i <= 20; i += 4)
				{
					if (AINumber[i] == STAR)
					{
						++count;
					}
				}
				if (max_star < count && count < 5)
				{
					line = LN_RT;
					max_star = count;
				}

				if (line <= LN_H5) // ���� ���� �ִ� �� ���
				{
					for (int i = 0; i < 5; i++)
					{
						if (AINumber[line * 5 + i] != STAR)
						{
							input = AINumber[line * 5 + i];
							break;
						}
					}
				}
				else if (line <= LN_V5) // ���� ���� �ִ��� ���
				{
					for (int i = 0; i < 5; i++)
					{
						if (AINumber[(line - 5) + i * 5] != STAR)
						{
							input = AINumber[(line - 5) + 5 * i];
							break;
						}
					}
				}
				else if (line == LN_LT) // ���� -> ������ �밢���� �ִ��� ���
				{
					for (int i = 0; i < 25; i += 6)
					{
						if (AINumber[i] != STAR)
						{
							input = AINumber[i];
							break;
						}
					}
				}
				else    // ������ -> ���� �밢���� �ִ��� ���
				{
					for (int i = 4; i <= 20; i += 4)
					{
						if (AINumber[i] != STAR)
						{
							input = AINumber[i];
							break;
						}
					}
				}

			}
			
			userSelect = true; // AI�� ���� �� user�� ����
			cout << "AI ����: " << input << endl;
			Sleep(2000);
		}
			
		// ���� �ߺ� üũ
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

		// AI �ߺ� üũ
		bAcc = true;
		for (int i = 0; i < 25; i++)
		{
			if (input == AINumber[i])
			{
				// ���ڸ� ã���� �ߺ��� �ƴϹǷ�
				bAcc = false;
				// *�� �ٲٱ� ���� STAR�� �����Ѵ�
				AINumber[i] = STAR;
				// �� �̻� ã�� �ʿ䰡 �����Ƿ� break
				break;
			}
		}

		// ���� üũ
		int star, AIstar;
		bingoLine = 0, AIbingoLine = 0;
		
		// ���� ���� üũ
		for (int i = 0; i < 5; i++)
		{
			// ���� ���� üũ
			star = 0;
			for (int j = 0; j < 5; j++)
			{
				if (iNumber[i * 5 + j] == STAR)
					star++;
			}

			if (star == 5)
				bingoLine++;

			// AI ���� üũ
			AIstar = 0;
			for (int j = 0; j < 5; j++)
			{
				if (AINumber[i * 5 + j] == STAR)
					AIstar++;
			}

			if (AIstar == 5)
				AIbingoLine++;
		}

		// ���� ���� üũ
		for (int i = 0; i < 5; i++)
		{
			// ���� ���� üũ
			star = 0;
			for (int j = 0; j < 5; j++)
			{
				if (iNumber[i + j * 5] == STAR)
					star++;
			}

			if (star == 5)
				bingoLine++;

			// AI ���� üũ
			AIstar = 0;
			for (int j = 0; j < 5; j++)
			{
				if (AINumber[i + j * 5] == STAR)
					AIstar++;
			}

			if (AIstar == 5)
				AIbingoLine++;
		}

		// �밢��(�»�� -> ���ϴ�) ���� üũ
		star = 0, AIstar = 0;
		for (int i = 0; i < 25; i+= 6)
		{
			// ���� ���� üũ
			if (iNumber[i] == STAR)
				star++;

			if (star == 5)
				bingoLine++;

			// AI ����üũ
			if (AINumber[i] == STAR)
				AIstar++;

			if (AIstar == 5)
				AIbingoLine++;
		}

		// �밢��(���� -> ���ϴ�) ���� üũ
		star = 0, AIstar = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			// ���� ���� üũ
			if (iNumber[i] == STAR)
				star++;

			if (star == 5)
				bingoLine++;

			// AI ���� üũ
			if (AINumber[i] == STAR)
				AIstar++;

			if (AIstar == 5)
				AIbingoLine++;
		}
		
	}

	return 0;
}