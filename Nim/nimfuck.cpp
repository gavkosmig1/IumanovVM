#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

using namespace std;

//��������� �������

void HelloNewGame() {
	cout << "************************************************************\n"
		<< "*                     � � � �    � � �                     *\n"
		<< "*     �� ������ ����� ����� ����� ����� �� ������ ����     *\n"
		<< "*       ���������� ���, ��� ������� ��������� �����.       *\n"
		<< "*             ������� ��������� ���� � �������             *\n"
		<< "* �����_�����     (���� 9)     �����_�����_�_������_������ *\n"
		<< "*             (3 3 ��� ������������ ���� ���)              *\n"
		<< "*            ��� ������� 0 0 ��� ������ �� ����            *\n"
		<< "************************************************************\n"
		<< "�������� �����:\n";
}

void Interface(const vector<int>& map) {
	cout << "************************************************************\n"
		<< "*                     � � � �    � � �                     *\n"
		<< "*     �� ������ ����� ����� ����� ����� �� ������ ����     *\n"
		<< "*       ���������� ���, ��� ������� ��������� �����.       *\n"
		<< "* ����� ����                                  ���-�� ����� *\n";
	for (int i = 0; i < map.size(); ++i) {
		cout << "*      " << i + 1 << "            " << string(map[i], '*') << string(32 - map[i], ' ') << map[i] << "      *\n";
	} // ������� �� ����������� ������ � ���-�� ����� � ������
	cout << "*      ������� ��� ��� � ������� ��� ����� (��������,      *\n"
		<< "*              2 3 - ����� �� 2 ���� 3 �����)              *\n"
		<< "*            ��� ������� 0 0 ��� ������ �� ����            *\n"
		<< "************************************************************\n"
		<< "��� ���:\n";
}

void Win() {
	cout << "************************************************************\n"
		<< "*                       �� ��������!                       *\n"
		<< "*                 ����� ������ ����� ����,                 *\n"
		<< "*             ������� ��������� ���� � �������             *\n"
		<< "* �����_�����                  �����_�����_�_������_������ *\n"
		<< "*             (3 3 ��� ������������ ���� ���)              *\n"
		<< "*            ��� ������� 0 0 ��� ������ �� ����            *\n"
		<< "************************************************************\n"
		<< "�������� �����:\n";
}

void Lose() {
	cout << "************************************************************\n"
		<< "*                      �� ���������!                       *\n"
		<< "*                 ����� ������ ����� ����,                 *\n"
		<< "*             ������� ��������� ���� � �������             *\n"
		<< "* �����_�����                  �����_�����_�_������_������ *\n"
		<< "*             (3 3 ��� ������������ ���� ���)              *\n"
		<< "*            ��� ������� 0 0 ��� ������ �� ����            *\n"
		<< "************************************************************\n"
		<< "�������� �����:\n";
}

// �������������e �������
bool XOr(bool a, bool b) {
	return ((a || b) && !(a && b));
}

void InTurn(int& MoveRow, int& MoveCum, vector<int>& map) {
	int Tvar = 0, flag;
	vector<int> NumStr_FirstRow{ 100, 100 };
	string Cum;
	while (Tvar == 0) {
		Cum.clear();
		flag = 0;
		getline(cin, Cum);
		for (int i = 0; i < Cum.size(); ++i) {
			switch (flag) {
			case(0):
				if (Cum[i] >= '0' && Cum[i] <= '9') {
					NumStr_FirstRow[0] = (int)Cum[i] - 48;
					++flag;
				}
				break;
			case(1):
				if (Cum[i] >= '0' && Cum[i] <= '9') {
					NumStr_FirstRow[1] = (int)Cum[i] - 48;
					flag++;
				}
				break;
			default:
				break;
			}
		} // ���� � ����� �� ���������� 0, � � ������ �� 0, ���� ���� ��� ������������
		if (XOr(NumStr_FirstRow[0] <= 0, NumStr_FirstRow[1] <= 0) || (NumStr_FirstRow[0] > map.size()) || (NumStr_FirstRow[1] > map[NumStr_FirstRow[0] - 1])) {
			cout << "������������ ����, ��������� �����\n";
			NumStr_FirstRow[0] = 100;
			NumStr_FirstRow[1] = 100;
		}
		else {
			Tvar = 1;
		}
	}

	MoveRow = NumStr_FirstRow[0];
	MoveCum = NumStr_FirstRow[1];
}

void InSettings(int& NumStr, int& FirstRow) {
	string Cum;
	vector<int> NumStr_FirstRow = { 100, 100 };
	int flag, Tvar = 0;
	while (Tvar == 0) {
		Cum.clear();
		flag = 0;
		getline(cin, Cum);
		for (int i = 0; i < Cum.size(); ++i) {
			switch (flag) {
			case(0):
				if (Cum[i] >= '0' && Cum[i] <= '9') {
					NumStr_FirstRow[0] = (int)Cum[i] - 48;
					++flag;
				}
				break;
			case(1):
				if (Cum[i] >= '0' && Cum[i] <= '9') {
					NumStr_FirstRow[1] = (int)Cum[i] - 48;
					flag++;
				}
				break;
			default:
				break;
			}
		} // ���� � ����� �� ���������� 0, � � ������ �� 0
		if (XOr(NumStr_FirstRow[0] <= 0, NumStr_FirstRow[1] <= 0) || (NumStr_FirstRow[0] > 9) || (NumStr_FirstRow[1] > 9)) {
			cout << "������������ ����, ��������� �����\n";
			NumStr_FirstRow[0] = 100;
			NumStr_FirstRow[1] = 100;
		}
		else {
			Tvar = 1;
		}
	}
	NumStr = NumStr_FirstRow[0];
	FirstRow = NumStr_FirstRow[1];
}

void NewGame(vector<int>& map, int& MoveRow, int& MoveCum) {
	int NumStr, FirstRow; // ���������� ���� ���� � ���������������� �������� ��������
	InSettings(NumStr, FirstRow);
	if ((NumStr == 0) && (FirstRow == 0)) {
		MoveRow = 0;
		MoveCum = 0;
	}
	else {
		for (int i = 0; i < NumStr; ++i) {
			map.push_back(min(FirstRow + i, 9));
		}
	}
}

void Moving(vector<int>& map, int start) {
	vector<int> result; // �������� ������ ������
	for (int i = 0; i < map.size(); ++i) {
		if (i != start) {
			result.push_back(map[i]);
		}
	}
	map = result;
}

//������� �����
void Player_move(vector<int>& map, int MoveRow, int MoveCum) {
	if (map[MoveRow - 1] == MoveCum) {
		Moving(map, MoveRow - 1);
	}
	else {
		map[MoveRow - 1] -= MoveCum;
	}
}

void Bot_move(vector<int>& map) {
	int Nim_Num = 0, losei = 0, losej = 0;
	vector<int> TechMap = map; // ��������� ������, �� ������� ����������� ����
	for (int i = 0; i < map.size(); ++i) {
		for (int j = 1; j <= map[i]; ++j) { // ����� ���� - i ������, j - ���-�� ����������
			TechMap[i] -= j; // ������ ���
			for (int k : TechMap) {
				Nim_Num ^= k;
			} // ������� ���-����� ��� ����� ����
			if (Nim_Num == 0) { // ���� ��� ����������
				if (map[i] == j) {
					Moving(map, i);
				}
				else {
					map[i] -= j;
				} // ������� ������ ��� �������� �� ��
				goto exit_excellent; // � ������� �� �������
			}
			TechMap = map; // ���� ��� �� �������, �������� ��������� ������
			Nim_Num = 0;
		}
	} // ���� ���������� ��� �� �������
	losei = 1 + rand() % map.size(); // ��������� ������
	losej = 1 + rand() % map[losei]; // ��������� ����� �����
	if (map[losei] == losej) {
		Moving(map, losei);
	}
	else {
		map[losei] -= losej; // ��������� ���
	}
exit_excellent:;
}

int main() { //������
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");
	vector<int> map;
	int MoveRow = 1, MoveCum = 1;
	HelloNewGame();
	NewGame(map, MoveRow, MoveCum);

	if ((MoveRow == 0) || (MoveCum == 0)) {
		goto exit;
	}
	Interface(map);
	InTurn(MoveRow, MoveCum, map);

	while ((MoveRow != 0) || (MoveCum != 0)) { // ���� ����� �� ������� ���� ������ 0 0
		Player_move(map, MoveRow, MoveCum);
		if (map.empty()) { // ����� �������
			Win();
			NewGame(map, MoveRow, MoveCum);
			if ((MoveRow == 0) || (MoveCum == 0)) {
				goto exit;
			}
			Interface(map);
		}
		else {
			Bot_move(map);
			if (map.empty()) { // ��� �������
				Lose();
				NewGame(map, MoveRow, MoveCum);
				if ((MoveRow == 0) || (MoveCum == 0)) {
					goto exit;
				}
				Interface(map);
			}
			else { // ����� ���� ������������
				Interface(map);
			}
		}
		InTurn(MoveRow, MoveCum, map);
	}
exit:;
}