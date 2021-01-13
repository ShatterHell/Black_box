#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

class Game;

//Интерфейс класса Поле
class Field				
{
private:	
	int *MasCell;			//Массив ячеек
	int *CoordAtoms;		//Массив хранящий координаты ячеек с атомами в матричном виде
	int N;					//Размерность массива
	int otm_atoms;	//Кол-во отмеченныйх с помощью метода атомов
	static int nomer_lucha;	//Кол-во запущенных лучей
	static int points;		//Очки
public:
	Field(int a);
	~Field();
	int Ray(int i, int j);	//Метод запуска лучей, принимает координаты ячейки-стенки, тип может поменяться на char для возвращения символьного обозначения
	int Atom(int i, int j);	//Метод обозначения атома
	int Check();
	static void New_game(int n);
	void vivod();           //Тестовый вывод матрицы
	void Game_vivod();		//Игровой вывод матрицы

	static int V;			//Кол-во атомов		
	friend Game;
};

//Интерфейс класса Игрок из таблицы
class Player
{
private:
	char *Name;
	int point;
public:
	Player();
	~Player();
	friend ofstream & operator << (ofstream & stream, Player obj);
	friend ifstream & operator >> (ifstream & stream, Player & obj);			
	friend Game;
};

//Интерфейс класса Игра
class Game
{
private:
	Player *List;
	int *Rays;
	int a,b;
	int parameter;
public:
	Game();
	~Game();
	void Start_Game();			
	int menu_help();					//Меню "Помощь"
	bool parameters();					//подменю "Параметры"
	void records();						//подменю "Таблица рекордов"
	void about();						//подменю "О программе"
	void add_to_records();				//добавить рекорд
};