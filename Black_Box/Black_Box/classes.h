#include <iostream>
#include <fstream>
#include <conio.h>
using namespace std;

class Game;

//��������� ������ ����
class Field				
{
private:	
	int *MasCell;			//������ �����
	int *CoordAtoms;		//������ �������� ���������� ����� � ������� � ��������� ����
	int N;					//����������� �������
	int otm_atoms;	//���-�� ����������� � ������� ������ ������
	static int nomer_lucha;	//���-�� ���������� �����
	static int points;		//����
public:
	Field(int a);
	~Field();
	int Ray(int i, int j);	//����� ������� �����, ��������� ���������� ������-������, ��� ����� ���������� �� char ��� ����������� ����������� �����������
	int Atom(int i, int j);	//����� ����������� �����
	int Check();
	static void New_game(int n);
	void vivod();           //�������� ����� �������
	void Game_vivod();		//������� ����� �������

	static int V;			//���-�� ������		
	friend Game;
};

//��������� ������ ����� �� �������
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

//��������� ������ ����
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
	int menu_help();					//���� "������"
	bool parameters();					//������� "���������"
	void records();						//������� "������� ��������"
	void about();						//������� "� ���������"
	void add_to_records();				//�������� ������
};