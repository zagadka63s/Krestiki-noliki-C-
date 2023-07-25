#include <iostream>
#include <string>
#include <locale>
#include <iomanip>
using namespace std;

// Определяем размер игрового поля 

const int ROWS = 3;
const int COLS = 3;

// Создадим функция для иниализация игрового поля

void initializeBoard(char board[ROWS][COLS])
{
	// теперь нужен цикл для прохода по каждой ячейке массива и заполняем ее пробелами
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			board[i][j] = ' ';
		}
	}
}

// Создаем функция для отображения нашего игрового поля на экран
void displayBoard(const char board[ROWS][COLS]) {
	system("clear"); // Для Windows используйте "cls" вместо "clear"

	cout << "   1   2   3\n";
	cout << "  ---+---+---\n";

	for (int i = 0; i < ROWS; i++) {
		cout << i + 1 << " ";

		for (int j = 0; j < COLS; j++) {
			std::cout << "| " << board[i][j] << " ";
		}

		cout << "|\n";
		cout << "  ---+---+---\n";
	}
}


// Теперь создаем функцию для регистрации игроков 

void registerPlayers(string& player1, string& player2)
{
	cout << "Введите имя первого игрока : " << endl;
	cin >> player1;
	cout << "Введите имя второго игрока : " << endl;
	cin >> player2;
}


// Функция для обработки хода игроков 
void makeMove(char board[ROWS][COLS], int row, int col, char playerSymbol)
{
	// Теперь нам нужна проверка, что выбранная ячейка свободна ( не занята другим символом)
	if (board[row][col]== ' ')
	{
		// Теперь размещаем символ ( крестик или нолик ) в выбранной ячейке
		board[row][col] = playerSymbol;
	}
	else
	{
		cout << "Эта ячейка уже занята ! Попробуйте другой ход \n";
	}
}

// Функция для проверки на победу или ничью

bool checkWinOrDraw(const char board[ROWS][COLS], char playerSymbol)
{
	// Проверяем наличие победителя по горизонтали , вертикали и диагонали
	for (int i = 0; i < ROWS; i++)
	{
		if (board[i][0] == playerSymbol && board[i][1] == playerSymbol && board[i][2] == playerSymbol)
		{
			return true; // Победа по горизонтали
		}
		if (board[0][i] == playerSymbol && board[1][i] == playerSymbol && board[2][i]==playerSymbol)
		{
			return true; // Победа по вертикали
		}
	}
	if (board[0][0] == playerSymbol && board [1][1]==playerSymbol && board[2][2] == playerSymbol)
	{
		return true; // Победа по диагонали ( слева-направо)
	}
	if (board[0][2] == playerSymbol && board[1][1] == playerSymbol && board[2][0]==playerSymbol)
	{
		return true; // Победа по диагонали ( справа- налево)
	}

	// проверка наличие пустых ячеек для определения ничьей
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (board[i][j] == ' ')
			{
				return false; // Есть пустые ячейки, игра продолжается 
			}
		}
	}

	return true;
}


int main()
{
	setlocale(LC_ALL, "russian");

	// Создаем игровое поле с помощью двумерного массива

	char board[ROWS][COLS];

	initializeBoard(board);

	// Регистрируем игроков
	string player1, player2;
	registerPlayers(player1, player2);


	char currentPlayerSymbol = 'X'; // Игрок, кто начинает будет использовать Крестик
	int row, col;

	// Основной игровой цикл

	while (true)
	{
		// Отображаем игровое поле
		displayBoard(board);

		// Просим текущего игрока сделать ход
		cout << " Ход игрока " << (currentPlayerSymbol == 'X' ? player1 : player2) << " (" << currentPlayerSymbol << ")\n";

		// Запрашиваем у игрока координаты для хода
		cout << "Введите номер строки (1 , 2 , или 3): ";
		cin >> row;
		row--; // Приводим номер строки к индексу массива ( от 0 до 2)

		cout << "Введите номер столбца ( 1, 2 или 3) : ";
		cin >> col;
		col--; // Приводим номер столбца к индексу массива ( от 0 до 2)

		// проверяем что введеные координаты находяться в допустимых пределах
		if (row >=0 && row < ROWS && col >= 0 && col < COLS)
		{
			// Вызываем функция для обработки хода текущего игрока
			makeMove(board, row, col, currentPlayerSymbol);

			// Проверяе на победу или ничю
			if (checkWinOrDraw(board,currentPlayerSymbol))
			{
				// Отображаем игрокое поле перед объялвением победы или ничьи
				displayBoard(board);

				// выводим сообщение о победе текущего игрока
				cout << "Поздравляем, игрок " << (currentPlayerSymbol == 'X' ? player1 : player2) << " (" << currentPlayerSymbol << ") победил!\n";


				break; // Выходим из игрового цикла

			}
			// Переключаем символ текущего игрока для следующего хода
			currentPlayerSymbol = (currentPlayerSymbol == 'X' ? 'O' : 'X');
		}
		else {
			cout << "Недопустимые координаты! Попробуйте снова .\n";
		}

	}
	return 0;
}