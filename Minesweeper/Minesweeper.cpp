#include<iostream>
#include<time.h>
#include<stdio.h>
#include<iomanip>
using namespace std;

class minesweeper
{
private:
	int num_mines = 10, nearby, flags = 0, size = 10;
	char table[10][10], mine_pos[10][10], mine = 77, star = 42, zero = 48, choice, flagged_mines = 0;
	bool Lost = false;
public:
	void Table_Maker()//this will make the table to show
	{

		for (int i = 0; i < size; i++)//output the column and row to choose from
		{
			table[i][0] = i + zero;
			table[0][i] = i + zero;
		}
		for (int j = 1; j < size; j++)//hides all positions
		{
			for (int k = 1; k < size; k++)
			{
				table[j][k] = star;
			}
		}
	}
	void square_num(int i, int j)
	{
		if (i >= 0 && i < 10 && j >= 0 && j < 10 && mine_pos[i][j] != mine)
			mine_pos[i][j]++;
	}
	void Mine_filler()
	{
		srand(time(NULL));
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				mine_pos[i][j] = 48;
		}
		int x, y;
		for (int k = 0; k < size; k++)
		{
			x = rand() % 10;
			y = rand() % 10;
			while (x == 0 || y == 0)
			{
				if (x == 0)
					x = rand() % 10;
				if (y == 0)
					y = rand() % 10;
			}
			mine_pos[x][y] = mine;
			square_num(x + 1, y + 1);
			square_num(x + 1, y);
			square_num(x + 1, y - 1);
			square_num(x, y - 1);
			square_num(x, y + 1);
			square_num(x - 1, y + 1);
			square_num(x - 1, y);
			square_num(x - 1, y - 1);
		}
	}
	void reveal(int i, int j)//shows what the selected position is
	{
		if (table[i][j] == star && mine_pos[i][j] != mine)//checking to see if position is mine
		{
			table[i][j] = mine_pos[i][j];
			if (mine_pos[i][j] == zero)//if selected square is = 0, reveals all surround squares
			{
				reveal(i + 1, j - 1);
				reveal(i + 1, j);
				reveal(i + 1, j + 1);
				reveal(i, j - 1);
				reveal(i, j + 1);
				reveal(i - 1, j - 1);
				reveal(i - 1, j);
				reveal(i - 1, j + 1);
			}
		}
	}
	void Player_input(bool& Loser)// have the player input choice
	{
		int i, j;
		cout << "Enter the letter o followed by the value of y and x to open square[y][x] \n";
		cout << "Enter the letter f followed by the value of y and x to open square[y][x] \n";
		cout << "Flags: " << flags << endl;
		cout << "Mines: " << num_mines << endl;
		cin >> choice;
		if (choice == 'o' || choice == 'O')
		{
			do
			{
				cin >> i >> j;
				if (i < 0 || i >9 || j < 0 || j >= 10)//checking to see if input is in range
				{
					cout << "The entered numbers are out of range \n";
					cout << "Please re-enter numbers: ";
				}
			} while (i <= 0 || i >= 10 || j <= 0 || j >= 10);

			if (mine_pos[i][j] == mine)
			{
				table[i][j] = mine;
				Lost = true;

				for (int k = 0; k < size; k++)
				{
					for (int l = 0; l < size; l++)
						if (mine_pos[k][l] == mine)
							table[k][l] = mine;
				}
			}
			else
				reveal(i, j);
		}
		if (choice == 'f' || choice == 'F')
		{
			Place_flag();
		}
		cout << "Flags: " << flags << endl;
		cout << "Mines: " << num_mines << endl;
	}
	void Place_flag()
	{
		int i, j;
		do
		{
			cin >> i >> j;
			if (i < 0 || i >9 || j < 0 || j >9)//checking to see if input is in range
			{
				cout << "The entered numbers are out of range \n";
				cout << "Please re-enter numbers: ";
			}
		} while (i < 0 || i >9 || j < 0 || j >9);
		if (table[i][j] == 'F')
		{
			table[i][j] = '*';
			flags--;
		}
		else
		{
			table[i][j] = 'F';
			flags++;
			if (mine_pos[i][j] == mine)
			{
				flagged_mines++;
			}
			num_mines--;
		}
	}
	void Show_all_mines()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << setw(10) << mine_pos[i][j];
			}
			cout << endl;
		}
	}
	void Show_table()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << setw(10) << table[i][j];
			}
			cout << endl;

		}
	}
	bool Check_game_win()
	{
		if (flags == 10 && flagged_mines == 10)
			return 1;
		else
		{
			return 0;
		}
	}
	void Game()
	{
		Mine_filler();
		Table_Maker();
		while (!Lost && !Check_game_win())
		{
			Show_table();
			Player_input(Lost);
			cout << endl << endl;
		}
		if (Lost)
		{
			Show_table();
			cout << "GAME OVER \n" << "YOU LOST! \n";
		}
		else
			cout << "GAME OVER \n" << "YOU WON! \n";
	}
};
void main()
{
	minesweeper easy;
	cout << "MineSweeper \n";
	easy.Game();
}
