#include <iostream>
#include <array>

using namespace std;

//ボード
namespace BOARD
{
	//最大幅
	constexpr int MAX{ 3 };
	constexpr int ARAAY_MIN{ 0 };
	constexpr int ARRAY_MAX{ MAX - 1 };

	//OXの区別
	constexpr int CIRCLE{ 1 };
	constexpr int CROSS{ 2 };
	constexpr int NONE{ 0 };

	//情報格納用配列
	using LINE = array<int, MAX>;
	using MAP = array<LINE, MAX>;
}

//ボードクラス
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



//コンストラクタ
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

//表示
void CBoard::Draw()
{
	for (auto&y : m_map)
	{
		for (int &x : y)
		{
			if (x == BOARD::CIRCLE)
				cout << "[〇]";
			if (x == BOARD::CROSS)
				cout << "[×]";
			if (x == BOARD::NONE)
				cout << "[　]";
		}
		cout << "\n";
	}
}

void CBoard::Input(int tarn)
{
	int x, y;
	bool check;

	cout << "取る位置をX軸Y軸の順で数値で入力して下さい\n";

	do
	{
		check = true;

		cin >> x;
		cin >> y;

		//範囲外
		if (x <BOARD::ARAAY_MIN || x > BOARD::ARRAY_MAX || y <BOARD::ARAAY_MIN || y > BOARD::ARRAY_MAX)
			check = false;

		//すでに取られている
		if (m_map[y][x] != BOARD::NONE)
			check = false;

		if (check == false)
			cout << "入力が正しくありません。もう一度入力してください\n";

	} while (check == false);

	//偶数ターン　で×をいれる
	if (tarn % 2 == 0)
		m_map[y][x] = BOARD::CROSS;

	//奇数ターン　で〇をいれる
	else
		m_map[y][x] = BOARD::CIRCLE;
}

bool CBoard::WinCheck()
{
	for (int i = 0; i < 3; i++)
	{
		//横
		if (m_map[i][0] != BOARD::NONE && m_map[i][0] == m_map[i][1] && m_map[i][0] == m_map[i][2])
			return true;
		//縦
		if (m_map[0][i] != BOARD::NONE && m_map[0][i] == m_map[1][i] && m_map[0][i] == m_map[2][i])
			return true;
	}

	//右斜め
	if (m_map[1][1] != BOARD::NONE&&m_map[0][0] == m_map[1][1] && m_map[1][1] == m_map[2][2])
		return true;

	//左斜め
	if (m_map[1][1] != BOARD::NONE&&m_map[0][2] == m_map[1][1] && m_map[1][1] == m_map[2][0])
		return true;

	return false;
}

int main()
{
	//ボードのクラス
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

	Board->Draw();//最終的なボードの表示

	if (tarn == 10)
	{
		cout << "引きわけ\n";
	}
	else
	{
		if (tarn % 2 == 0)
			cout << "×の勝利\n";
		else
			cout << "〇の勝利\n";
	}

	//画面がすぐに消えないように
	char a;
	cin >> a;

	return 0;

}