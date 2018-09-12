#include <iostream>
#include <array>

using namespace std;

//�{�[�h
namespace BOARD
{
	//�ő啝
	constexpr int MAX{ 3 };
	constexpr int ARAAY_MIN{ 0 };
	constexpr int ARRAY_MAX{ MAX - 1 };

	//OX�̋��
	constexpr int CIRCLE{ 1 };
	constexpr int CROSS{ 2 };
	constexpr int NONE{ 0 };

	//���i�[�p�z��
	using LINE = array<int, MAX>;
	using MAP = array<LINE, MAX>;
}

//�{�[�h�N���X
class CBoard
{
public:
	CBoard();
	void Draw();
	void Input(int tarn);
	bool WinCheck();

private:
	BOARD::MAP	m_map;
};



//�R���X�g���N�^
CBoard::CBoard()
{
	int map[BOARD::MAX][BOARD::MAX]
	{
		{0,0,0},
		{0,0,0},
		{0,0,0},
	};
	memcpy(&m_map, map, sizeof(map));
}

//�\��
void CBoard::Draw()
{
	for (auto&y : m_map)
	{
		for (int &x : y)
		{
			if (x == BOARD::CIRCLE)
				cout << "[�Z]";
			if (x == BOARD::CROSS)
				cout << "[�~]";
			if (x == BOARD::NONE)
				cout << "[�@]";
		}
		cout << "\n";
	}
}

void CBoard::Input(int tarn)
{
	int x, y;
	bool check;

	cout << "���ʒu��X��Y���̏��Ő��l�œ��͂��ĉ�����\n";

	do
	{
		check = true;

		cin >> x;
		cin >> y;

		//�͈͊O
		if (x <BOARD::ARAAY_MIN || x > BOARD::ARRAY_MAX || y <BOARD::ARAAY_MIN || y > BOARD::ARRAY_MAX)
			check = false;

		//���łɎ���Ă���
		if (m_map[y][x] != BOARD::NONE)
			check = false;

		if (check == false)
			cout << "���͂�����������܂���B������x���͂��Ă�������\n";

	} while (check == false);

	//�����^�[���@�Ł~�������
	if (tarn % 2 == 0)
		m_map[y][x] = BOARD::CROSS;

	//��^�[���@�ŁZ�������
	else
		m_map[y][x] = BOARD::CIRCLE;
}

bool CBoard::WinCheck()
{
	for (int i = 0; i < 3; i++)
	{
		//��
		if (m_map[i][0] != BOARD::NONE && m_map[i][0] == m_map[i][1] && m_map[i][0] == m_map[i][2])
			return true;
		//�c
		if (m_map[0][i] != BOARD::NONE && m_map[0][i] == m_map[1][i] && m_map[0][i] == m_map[2][i])
			return true;
	}

	//�E�΂�
	if (m_map[1][1] != BOARD::NONE&&m_map[0][0] == m_map[1][1] && m_map[1][1] == m_map[2][2])
		return true;

	//���΂�
	if (m_map[1][1] != BOARD::NONE&&m_map[0][2] == m_map[1][1] && m_map[1][1] == m_map[2][0])
		return true;

	return false;
}

int main()
{
	//�{�[�h�̃N���X
	unique_ptr<CBoard> Board(new CBoard());

	int tarn = 1;
	bool win_f = false;
	while (tarn <= 9)
	{
		system("cls");

		Board->Draw();
		Board->Input(tarn);
		win_f = Board->WinCheck();

		if (win_f == true)
			break;

		tarn++;
	}

	Board->Draw();//�ŏI�I�ȃ{�[�h�̕\��

	if (tarn == 10)
	{
		cout << "�����킯\n";
	}
	else
	{
		if (tarn % 2 == 0)
			cout << "�~�̏���\n";
		else
			cout << "�Z�̏���\n";
	}

	//��ʂ������ɏ����Ȃ��悤��
	char a;
	cin >> a;

	return 0;

}