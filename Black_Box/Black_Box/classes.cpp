#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <math.h>
#include <cstdlib>
#include "classes.h"
using namespace std;

int Field::V=0;																		//Игра начинается с одного атома
int Field::nomer_lucha=0;
int Field::points=0;

//Реализация класса Поле
Field::Field (int a)																//принимает размер поля(изменяемый в настр.)
{
	V++;
	nomer_lucha=0;
	otm_atoms=0;
	N=a;
	points+=(N*2+(N-4)*2)*V*5;
	MasCell=new int[N*N];
	CoordAtoms=new int[V*2];
	int i,j;																		//Переменные цикла для матрицы ячеек
	int k;																			//Переменные цикла для записи координат атомов

	for (i=0; i<N; i++)
	{
		for (j=0; j<N; j++)
		{
			if (i!=0 && i!=N-1 && j!=0 && j!=N-1)
				MasCell[i*N+j]=0;													//Значения ячеек от 0-5, -1 - ячейка с атомом, -2 – луч не встречает атом и не рассеивается, то есть проходит всю дистанцию от одной стенки к другой(с отклонениями или без, для стен), -3 – луч встречает атом(значения стены), -4 – луч рассеивается(значение стены), -5 - неопределённая ячейка стены
			else
				MasCell[i*N+j]=-5;
		}
	}

	for (k=0; k<V; k++)															//V-кол-во атомов на поле
	{	
		CoordAtoms[k*2+0]= 1 + rand() % (N-2);												//N-размерность массива,
		CoordAtoms[k*2+1]= 1 + rand() % (N-2);

		i=CoordAtoms[k*2+0];
		j=CoordAtoms[k*2+1];
		if (MasCell[i*N+j]==-1)
			k--;
		else
			MasCell[i*N+j]=-1;
	}
}
Field::~Field()
{
	delete[]MasCell;
	delete[]CoordAtoms;
}
int Field::Ray(int i, int j)				
{
	int a=i,b=j;
	int napravlenie;							//1-вниз, 2-вправо, 3-вверх, 4-влево
	points-=N+V*2;
	//действия до первого шага
	if (a==0)
	{
		for (int k=0; k<V; k++)
		{
			if (a+1==CoordAtoms[k*2+0] && b==CoordAtoms[k*2+1])
			{
				MasCell[i*N+j]=-3;
				return -3;
			}
		}
		for (int k=0; k<V; k++)
		{
			if ((a+1==CoordAtoms[k*2+0] && b+1==CoordAtoms[k*2+1]) || (a+1==CoordAtoms[k*2+0] && b-1==CoordAtoms[k*2+1]))
			{
				MasCell[i*N+j]=-4;
				return -4;
			}
		}
		napravlenie=1;
	}
	else if (b==0)
	{
		for (int k=0; k<V; k++)
		{
			if (a==CoordAtoms[k*2+0] && b+1==CoordAtoms[k*2+1])
			{
				MasCell[i*N+j]=-3;
				return -3;
			}
		}
		for (int k=0; k<V; k++)
		{
			if ((a+1==CoordAtoms[k*2+0] && b+1==CoordAtoms[k*2+1]) || (a-1==CoordAtoms[k*2+0] && b+1==CoordAtoms[k*2+1]))
			{
				MasCell[i*N+j]=-4;
				return -4;
			}
		}
		napravlenie=2;
	}
	else if (a==N-1)
	{
		for (int k=0; k<V; k++)
		{
			if (a-1==CoordAtoms[k*2+0] && b==CoordAtoms[k*2+1])
			{
				MasCell[i*N+j]=-3;
				return -3;
			}
		}
		for (int k=0; k<V; k++)
		{
			if ((a-1==CoordAtoms[k*2+0] && b-1==CoordAtoms[k*2+1]) || (a-1==CoordAtoms[k*2+0] && b+1==CoordAtoms[k*2+1]))
			{
				MasCell[i*N+j]=-4;
				return -4;
			}
		}
		napravlenie=3;
	}
	else if (b==N-1)
	{
		for (int k=0; k<V; k++)
		{
			if (a==CoordAtoms[k*2+0] && b-1==CoordAtoms[k*2+1])
			{
				MasCell[i*N+j]=-3;
				return -3;
			}
		}
		for (int k=0; k<V; k++)
		{
			if ((a-1==CoordAtoms[k*2+0] && b-1==CoordAtoms[k*2+1]) || (a+1==CoordAtoms[k*2+0] && b-1==CoordAtoms[k*2+1]))
			{
				MasCell[i*N+j]=-4;
				return -4;
			}
		}
		napravlenie=4;
	}
	//действия после первого шага
	do {
		for (int k=0; k<V; k++)
		{
			for (int l=0; l<V; l++)
			{
				if ((a+1==CoordAtoms[k*2+0] && b==CoordAtoms[k*2+1]) || (a-1==CoordAtoms[k*2+0] && b==CoordAtoms[k*2+1]) || (a==CoordAtoms[k*2+0] && b+1==CoordAtoms[k*2+1]) || (a==CoordAtoms[k*2+0] && b-1==CoordAtoms[k*2+1]))
				{
					MasCell[i*N+j]=-3;
					return -3;
				}
				else if (a+1==CoordAtoms[k*2+0] && b+1==CoordAtoms[k*2+1])																											//2
				{
					if ((a+1==CoordAtoms[k*2+0] && b+1==CoordAtoms[k*2+1] && a+1==CoordAtoms[l*2+0] && b-1==CoordAtoms[l*2+1]) || (a+1==CoordAtoms[k*2+0] && b+1==CoordAtoms[k*2+1] && a-1==CoordAtoms[l*2+0] && b+1==CoordAtoms[l*2+1]))			//2&&3 || 2&&6
					{
						MasCell[i*N+j]=-4;														
						return -4;
					}
					if (napravlenie==1)
						napravlenie=4;
					else if (napravlenie==2)
						napravlenie=3;
				}
				else if (a+1==CoordAtoms[k*2+0] && b-1==CoordAtoms[k*2+1])																											//3
				{
					if ((a+1==CoordAtoms[k*2+0] && b-1==CoordAtoms[k*2+1] && a+1==CoordAtoms[l*2+0] && b+1==CoordAtoms[l*2+1]) || (a+1==CoordAtoms[k*2+0] && b-1==CoordAtoms[k*2+1] && a-1==CoordAtoms[l*2+0] && b-1==CoordAtoms[l*2+1]))			//3&&2 || 3&&7
					{
						MasCell[i*N+j]=-4;
						return -4;
					}
					if (napravlenie==1)
						napravlenie=2;
					else if (napravlenie==4)
						napravlenie=3;
				}
				else if (a-1==CoordAtoms[k*2+0] && b+1==CoordAtoms[k*2+1])																											//6
				{
					if ((a-1==CoordAtoms[k*2+0] && b+1==CoordAtoms[k*2+1] && a+1==CoordAtoms[l*2+0] && b+1==CoordAtoms[l*2+1]) || (a-1==CoordAtoms[k*2+0] && b+1==CoordAtoms[k*2+1] && a-1==CoordAtoms[l*2+0] && b-1==CoordAtoms[l*2+1]))			//6&&2 || 6&&7
					{
						MasCell[i*N+j]=-4;
						return -4;
					}
					if (napravlenie==3)
						napravlenie=4;
					else if (napravlenie==2)
						napravlenie=1;
				}
				else if (a-1==CoordAtoms[k*2+0] && b-1==CoordAtoms[k*2+1])																											//7
				{
					if ((a-1==CoordAtoms[k*2+0] && b-1==CoordAtoms[k*2+1] && a+1==CoordAtoms[l*2+0] && b-1==CoordAtoms[l*2+1]) || (a-1==CoordAtoms[k*2+0] && b-1==CoordAtoms[k*2+1] && a-1==CoordAtoms[l*2+0] && b+1==CoordAtoms[l*2+1]))			//7&&3 || 7&&6
					{
						MasCell[i*N+j]=-4;
						return -4;
					}
					if (napravlenie==3)
						napravlenie=2;
					else if (napravlenie==4)
						napravlenie=1;
				}
			}
		}
		switch (napravlenie)
		{
		case 1:
			{
			a++;
			break;
			}
		case 2:
			{
			b++;
			break;
			}
		case 3:
			{
			a--;
			break;
			}
		case 4:
			{
			b--;
			break;
			}
		}
    } while (MasCell[a*N+b]!=-5 && MasCell[a*N+b]!=-2 && MasCell[a*N+b]!=-3 && MasCell[a*N+b]!=-4);    
	nomer_lucha++;
	MasCell[i*N+j]=nomer_lucha;
	MasCell[a*N+b]=nomer_lucha;
	return -2;
}
int Field::Atom(int i, int j)
{
	if (MasCell[i*N+j]!=-6)
	{
		MasCell[i*N+j]=-6;																		//Ячейка отведённая для проверки
		otm_atoms++;
	}
	else 
	{
		MasCell[i*N+j]=0;
		otm_atoms--;
	}
	
	return -6;
}
int Field::Check()
{
	if (otm_atoms!=V)
		return -1;
	int ugadanno=0;
	for (int i=0; i<N ; i++)
	{
		for (int j=0; j<N; j++)
		{
			if (MasCell[i*N+j]==-6)
			{
				for (int k=0; k<V; k++)															//V-кол-во атомов на поле
				{	
					if (CoordAtoms[k*2+0]==i && CoordAtoms[k*2+1]==j)							//N-размерность массива,
					{
						MasCell[i*N+j]=-7;
						ugadanno++;
					}
				}
			}
			if (MasCell[i*N+j]==-6)
				MasCell[i*N+j]=-8;
		}
	}
	if (ugadanno==V)
		return 1;
	else 
	{
		for (int k=0; k<V; k++)
			MasCell[CoordAtoms[k*2+0]*(N)+CoordAtoms[k*2+1]]=-7;
		V=0;
		otm_atoms=0;
		return 0;
	}
}
void Field::New_game(int n)
{
	V=0;
	points=(n*2+(n-4)*2)*(V)*5;
}
void Field::vivod()
{
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			cout << " " << setw(2) << MasCell[i*N+j];
		}
		cout << endl;
	}
	for (int i=0; i<V; i++)
	{
		cout << " " << CoordAtoms[i*2+0] << " " << CoordAtoms[i*2+1] << endl;
	}
}
void Field::Game_vivod()
{
	cout << "    ";
	for (int k=0; k<N; k++)
		cout << setw(3) << k;
	cout << "\n";
	for (int k=0; k<N; k++)
		cout << "___";
	if (V-otm_atoms==1)
		cout << "___  " << V-otm_atoms << "-атом необходимо отметить\n";
	else if (V-otm_atoms>1 && V-otm_atoms<5)
		cout << "___  " << V-otm_atoms << "-атома необходимо отметить\n";
	else
		cout << "___  " << V-otm_atoms << "-атомов необходимо отметить\n";
	for (int i=0; i<N; i++)
	{
		cout << " " << setw(2) << i << "|";
		for (int j=0; j<N; j++)
		{
			MasCell[(N-1)*N+(N-1)]=-9;
			MasCell[0*N+0]=-10;
			if (MasCell[i*N+j]==-3)				//поглощён
				cout << setw(3) << "П";
			else if (MasCell[i*N+j]==-4)		//рассеян
				cout << setw(3) << "Р";
			else if (MasCell[i*N+j]==-5)		//стенка
				cout << setw(3) << "#";
			else if (MasCell[i*N+j]==-6)		//отмечен как атом для проверки
				cout << setw(3) << "+";
			else if (MasCell[i*N+j]==-7)		//правильно угаданный атом
				cout << setw(3) << "*";
			else if (MasCell[i*N+j]==-8)		//неправильно угаданный атом
				cout << setw(3) << "X";
			else if (MasCell[i*N+j]==-9)		//меню "Помощь"
				cout << setw(3) << "?";
			else if (MasCell[i*N+j]==-10)		//проверка
				cout << setw(3) << "!";
			else if (MasCell[i*N+j]==-1)		//все остальные ячейки
				cout << setw(3) << "0";
			else
				cout << setw(3) << MasCell[i*N+j];
			if (i==1 && j==N-1)
				cout << "  Очки:";
			if (i==2 && j==N-1)
				cout << "  " << points;
		}
		cout << "\n";
	}
	cout << endl;
}

//Реализация класса Игрок из таблицы
Player::Player()
{
	Name=new char[15];
	strcpy(Name,"Noname");
	point=0;
}
Player::~Player()
{
	delete[]Name;
}
ofstream & operator << (ofstream& stream, Player obj)
{
	stream << obj.point << " " << obj.Name << "\n";
	return stream;
}
ifstream & operator >> (ifstream & stream, Player & obj)
{
	stream >> ws >> obj.point >> obj.Name;
	return stream;
}

//Реализация класса Игра
Game::Game()
{
	a=0,b=0;

	List=new Player[10];
	ifstream fin;
	fin.open("Records.txt", ios::_Nocreate);
	for (int i=0; i<10; i++)
	{
		fin >> List[i];
	}
	fin.close();
	
	fin.open("Parameters.txt", ios::_Nocreate);
	fin >> parameter;
	fin.close();

	Rays=new int[(parameter+2)*(parameter+2)];
}
Game::~Game()
{
	delete[]Rays;
}
void Game::Start_Game()
{
	int Res;
	int Menu;
	char Load_or_not;
	Field *field=new Field(parameter+2);
	field->Game_vivod();
	cout << "\n Хотите ли вы загрузить предыдущую игру? Y/N";
	Load_or_not = getch();
	switch (Load_or_not)
	{
	case 'Y':
	case 'y':
	case 'Н':
	case 'н':
		{
			delete field;
			ifstream fin;
			fin.open("Save.txt", ios::_Nocreate);
			fin >> Field::V;
			Field::V-=1;
			Field *field=new Field(parameter+2);
			fin >> field->nomer_lucha;
			fin >> field->otm_atoms;
			fin >> field->points;
			for (int k=0; k<Field::V; k++)
			{
				fin >> field->CoordAtoms[k*2+0];
				fin >> field->CoordAtoms[k*2+1];
			}
			for (int i=0; i<(parameter+2); i++)
				for (int j=0; j<(parameter+2); j++)
				{
					fin >> field->MasCell[i*(parameter+2)+j];
				}
			fin.close();
			system("cls");
			field->Game_vivod();
			break;
		}
	case 'N':
	case 'n':
	case 'Т':
	case 'т':
		break;
	}
	
	do {
	if (Field::V==parameter*parameter)
	{
		cout << "\nОтлично вы нашли все атомы и прошли все раунды\n Поздравляю!!! \n";
		Game::add_to_records();
		Menu=Game::menu_help();
		if (Menu==2)
		{
			delete field;
			Field::New_game(parameter+2);
			Field *field=new Field(parameter+2);
		}
		if (Menu==3)
		{
			delete field;
			Field::New_game(parameter+2);
			Field *field=new Field(parameter+2);
		}
		if (Menu==6)
		{
			ofstream fout;
			fout.open("Save.txt", ios::_Nocreate | ios::trunc);
				if (!fout.eof())
				{
					fout << Field::V << "\n";
					fout << field->nomer_lucha << "\n";
					fout << field->otm_atoms << "\n";
					fout << field->points << "\n";
					for (int k=0; k<Field::V; k++)
					{
						fout << field->CoordAtoms[k*2+0] << " ";
						fout << field->CoordAtoms[k*2+1] << "\n";
					}
					for (int i=0; i<(parameter+2); i++)
					{
						for (int j=0; j<(parameter+2); j++)
						{
							fout << setw(3) << field->MasCell[i*(parameter+2)+j];
						}
						fout << "\n";
					}
				}
				fout.close();
		}
		SetConsoleTitle("Black Box");
	}
	if (!(Field::V==parameter*parameter))
	{
		cout << "\n Введите (0,0) для проверки: ";
		cout << "\n Введите (" << (parameter+2)-1 << "," << (parameter+2)-1 << ") для перехода в меню \"Помощь\": ";
		cout << "\n Вводите координаты стенки или атома : ";
		cin >> a >> b;
	}
	if (a>(parameter+2) || b>(parameter+2) || a<0 || b<0)
	{
		system("cls");
		field->Game_vivod();
		continue;
	}
	else if (a!=0 && a!=(parameter+2)-1 && b!=0 && b!=(parameter+2)-1)
		field->Atom(a,b);
	else if (a==0 && b==0)
	{
		Res=field->Check();
		system("cls");
		field->Game_vivod();
		if (Res==-1)
		{
			cout << "\nПожалуйста обозначьте именно " << Field::V << " атомов\n" ;
			system("pause");
		}
		if (Res==1)
		{
			cout << "\nОтлично вы нашли все атомы! \nЧтобы перейти на следующий раунд нажмите любую клавишу!\n";
			system("pause");
			delete field;
			Field *field=new Field(parameter+2);
			for (int h=0; h<(parameter+2); h++)
				for (int g=0; g<(parameter+2); g++)
				{
					Rays[h*(parameter+2)+g]=0;
				}
		}
		if (Res==0)
		{
			cout << "\nВы ошиблись!! Можете начать игру сначала!!" << endl;
			Game::add_to_records();
			delete field;
			Field::New_game(parameter+2);
			Field *field=new Field(parameter+2);
		}
	}
	else if (a==(parameter+2)-1 && b==(parameter+2)-1)
	{
		Menu=Game::menu_help();
		if (Menu==2)
		{
			delete field;
			Field::New_game(parameter+2);
			Field *field=new Field(parameter+2);
		}
		if (Menu==3)
		{
			delete field;
			Field::New_game(parameter+2);
			Field *field=new Field(parameter+2);
		}
		if (Menu==6)
		{
			ofstream fout;
			fout.open("Save.txt", ios::_Nocreate | ios::trunc);
				if (!fout.eof())
				{
					fout << Field::V << "\n";
					fout << field->nomer_lucha << "\n";
					fout << field->otm_atoms << "\n";
					fout << field->points << "\n";
					for (int k=0; k<Field::V; k++)
					{
						fout << field->CoordAtoms[k*2+0] << " ";
						fout << field->CoordAtoms[k*2+1] << "\n";
					}
					for (int i=0; i<(parameter+2); i++)
					{
						for (int j=0; j<(parameter+2); j++)
						{
							fout << setw(3) << field->MasCell[i*(parameter+2)+j];
						}
						fout << "\n";
					}
				}
				fout.close();
		}
		SetConsoleTitle("Black Box");
	}
	else if (Rays[a*(parameter+2)+b]==1)
	{
		system("cls");
		field->Game_vivod();
		continue;
	}
	else if (!(a!=0 && a!=(parameter+2)-1 && b!=0 && b!=(parameter+2)-1))
	{
		field->Ray(a,b);
		for (int i=0; i<parameter+2; i++)
		{
			for (int j=0; j<parameter+2; j++)
			{
				if (Rays[i*(parameter+2)+j]==1 && a==i && b==j)
					continue;
				else
				{
					Rays[a*(parameter+2)+b]=1;
				}
			}
		}
	}
	system("cls");
	field->Game_vivod();
	} while (!(a==parameter+2 && b==parameter+2));
}
int Game::menu_help()
{
	char c;
	int res;
	SetConsoleTitle("Help");
	do {
		system("cls");
		cout << " ______   _        _______  _______  _          ______   _______          \n" <<
				"(  ___ \\ ( \\      (  ___  )(  ____ \\| \\    /\\  (  ___ \\ (  ___  )|\\     /|\n" <<
				"| (   ) )| (      | (   ) || (    \\/|  \\  / /  | (   ) )| (   ) |( \\   / )\n" <<
				"| (__/ / | |      | (___) || |      |  (_/ /   | (__/ / | |   | | \\ (_) / \n" <<
				"|  __ (  | |      |  ___  || |      |   _ (    |  __ (  | |   | |  ) _ (  \n" <<
				"| (  \\ \\ | |      | (   ) || |      |  ( \\ \\   | (  \\ \\ | |   | | / ( ) \\ \n" <<
				"| )___) )| (____/\\| )   ( || (____/\\|  /  \\ \\  | )___) )| (___) |( /   \\ )\n" <<
				"|/ \\___/ (_______/|/     \\|(_______/|_/    \\/  |/ \\___/ (_______)|/     \\|\n\n";
                                                                          
		cout << setw(48) << right << "1. Вернуться в игру" << endl;
		cout << setw(46) << right << "2. Начать сначала" << endl;
		cout << setw(41) << right << "3. Параметры" << endl;
		cout << setw(48) << right << "4. Таблица рекордов" << endl;
		cout << setw(39) << right << "5. Правила" << endl;
		cout << setw(37) << right << "6. Выход" << endl;
		
		c = getch( );
		switch (c)
		{
		case '1':										//вернуться в игру
			{
				return 1;
				break;
			}
		case '2':										//начать сначала
			{
				return 2;
				break;
			}
		case '3':										//параметры
			{
				res=Game::parameters();
				if (res==1)
					return 3;
				else
				break;
			}
		case '4':										//таблица рекордов
			{
				Game::records();
				break;
			}
		case '5':										//о программе
			{
				Game::about();
				break;
			}
		case '6':										//выход
			{
				a=parameter+2;
				b=parameter+2;
				
				ofstream fout;
				fout.open("Records.txt", ios::_Nocreate | ios_base::trunc);
				for (int j=0; j<10; j++)
				{
					fout << List[j];
				}
				fout.close();
				
				fout.open("Parameters.txt", ios::_Nocreate | ios::trunc);
				fout << parameter;
				fout.close();
				return 6;
				break;
			}
		}
	} while (1!=0);
}
bool Game::parameters()
{
	system("cls");
	cout << "\n\n" << setw(41) << "ПАРАМЕТРЫ" << endl;
	cout << "\n\n    Выберите размер игрового поля (от 5x5 до 18x18), сейчас - " << parameter << "x" << parameter << endl;
	cout << "    Для выхода из параметров введите 0 (Ну или любое число, кроме 5-18)";
	cout << "\n    Введите одну цифру\n    ";
	int c;
	cin >> c;
	if (c >= 5 || c<=18)
	{
		parameter=c;
		cout << "\nРазмер изменён на " << parameter << "x" << parameter << endl;
		return 1;
	}
	return 0;
	system("pause");
}
void Game::about()
{
	system("cls");
	cout << "\n\n" << setw(40) << "ПРАВИЛА" << endl;
	
	ifstream fin;
	char rules;
	fin.open("Rules.txt", ios::_Nocreate);
	while (!fin.eof())
	{
		fin.get(rules);
		cout << rules;
	}
	fin.close();
	system("pause");
}
void Game::records()
{
	system("cls");
	cout << "\n\n" << setw(46) << "ТАБЛИЦА РЕКОРДОВ" << endl;
	cout << "\n";
	for (int i=0; i<10; i++)
	{
		cout << setw(31) << List[i].point << setfill('-') << setw(15) << List[i].Name << setfill(' ') << "\n";
	}
	cout << "\n    Для отчистки таблицы нажмите 'X' ";
	cout << "\n    Для выхода нажмите любую клавишу, кроме 'X' ";
	cout << "    " << endl;
	char clear=getch();
	switch (clear)
	{
	case 'X':
	case 'x':
	case 'Ч':
	case 'ч':
		{
			delete[]List;
			Player *List=new Player[10];
		}
	}
}
void Game::add_to_records()
{
	for (int i=0; i<10; i++)
	{
		if (Field::points>List[i].point)
		{   
			char prom_Name[15];
			cout << "\nВведите своё имя для таблицы рекордов: \n";
			cin >> prom_Name;
			int prom_point=Field::points;
			int a=i;
			for (int j=8; j>=i; j--)
			{
					List[j+1].point=List[j].point;
					strcpy(List[j+1].Name,List[j].Name);
			}
			List[a].point=prom_point;
			strcpy(List[a].Name,prom_Name);
			break;
		}
	}
}