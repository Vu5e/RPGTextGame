#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "conio_nt.h"
#include <cstring>
#include <limits>

using namespace std;

#define e 255
#define w 178
#define heal 053
#define t 71
#define C 128
#define T 233
#define r 193

const int screenWidth = 100;
const int screenHeight = 50;

int vRange=2;

int choice;
bool mainExit=false;
bool battle=false;
int numberOfEnemies;
void InvalidInput(int x, int y);

enum PLAYER_TYPE
{
	HITLER=0,
	OBAMA,
	PUTIN
};

enum ENEMY_TYPE
{
	CLONE1=0,
	CLONE2,
	CLONE3,
	ENEMY_TOTAL
};

struct enemyChar;

struct playerChar
{
	PLAYER_TYPE type;
	string name;
	string playerType;
	int x, y;
	int previousX, previousY;
	int mhp;
	int chp;
	int bAtt;
	int rAtt;
	int bDef;
	int rDef;
	int healingsalve;
	float criticalChance;
	float criticalDamage;
	
	void initializePlayer(PLAYER_TYPE type);
	void movePlayer(int x,int y);
	void drawPlayer();
	void playerCollision();
	void displayStats(int x, int y);
	void itemScenario(int x, int y);
	void attack(enemyChar &target);
};

playerChar player01;

const int row=20;
const int col=20;
char map[row][col];

struct enemyChar
{
	ENEMY_TYPE type;
	string name;
	int x;
	int y;
	int mhp;
	int chp;
	int bAtt;
	int rAtt;
	int bDef;
	int rDef;
	float criticalChance;
	float criticalDamage;
	
	void initializeEnemy(ENEMY_TYPE type, int x, int y);
	void displayStats(int x, int y);
	void attack(playerChar &target);
};

void InvalidInput(int x, int y)
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	GoToXY(x, y);
	cout << "Invalid Input. Please choose again.";
	GoToXY(x, y + 1);
	system("PAUSE");
}

void GameTitle()
{
	SetFontColor(GREEN);
	GoToXY(screenWidth* 0.5 - 10 ,screenHeight * 0.2);
	cout<<"====================="<<endl;
	GoToXY(screenWidth * 0.5 - 10, screenHeight * 0.2+1);
	cout<<"|  SAVE TRUMP MIND  |"<<endl;
	GoToXY(screenWidth * 0.5 - 10 ,screenHeight * 0.2 + 2);
	cout<<"====================="<<endl;
}

void GameIntro()
{
	int playerClassChoice;
	playerChar player01;
	
	GameTitle();
	GoToXY(screenWidth * 0.5 - 14, screenHeight * 0.9);
	system("pause");
	ClrScreen();
	
	GoToXY(screenWidth * 0.5 - 12 ,screenHeight * 0.2);
	cout<<"Your mission as his best friend is to save Trump."<<endl;
	GoToXY(screenWidth * 0.5 - 12,screenHeight*0.2 + 1); 
	cout<<"Welcome to the mind of Trump."<<endl;
	system("pause");
	ClrScreen();
	GoToXY(screenWidth * 0.5 - 12 ,screenHeight * 0.2);
	cout<<"Trump is surrounded by Clinton Clones and maybe herself. "<<endl;
	GoToXY(screenWidth * 0.5 - 12 ,screenHeight * 0.2 + 1);
	cout<<"Kill her to save Trump mind from becoming more crazy. "<<endl;
	GoToXY(screenWidth * 0.5 ,screenHeight * 0.2 + 3);
	cout<<"For America.............."<<endl;
	system("pause");
	ClrScreen();
	
	bool isExit=false;
	
	do
	{
		SetFontColor(BLUE);
		GoToXY(screenWidth * 0.5 - 12 ,screenHeight * 0.2);
		cout<<"Choose your character."<<endl;
		GoToXY(screenWidth * 0.5 - 12 ,screenHeight * 0.2 + 1);
		cout<<"1. HITLER"<<endl;
		GoToXY(screenWidth * 0.5 - 12 ,screenHeight * 0.2 + 2);
		cout<<"2. OBAMA"<<endl;
		GoToXY(screenWidth * 0.5 - 12 ,screenHeight * 0.2 + 3);
		cout<<"3. PUTIN"<<endl;
		
		cin>>playerClassChoice;
		
		switch(playerClassChoice)
		{
			case 1:
				choice=1;
				isExit=true;
				break;
			case 2:
				choice=2;
				isExit=true;
				break;
			case 3:
				choice=3;
				isExit=true;
				break;
			default:
				InvalidInput(screenWidth * 0.3, screenHeight * 0.4 + 2);
				system("pause");
				ClrScreen();
		}
	} while(!isExit);
	
	system("pause");
	ClrScreen();
}

void playerChar::initializePlayer(PLAYER_TYPE _type)
{
	this->type=_type;
	x=19;
	y=2;
	
	if (_type==HITLER)
	{
		playerType="HITLER";
		mhp=125;
		chp=125;
		bAtt=17;
		rAtt=0;
		bDef=8;
		rDef=0;
		healingsalve=3;
		criticalChance=4;
		criticalDamage=3.25;
	}
	else if (_type==OBAMA)
	{
		playerType="OBAMA";
		mhp=140;
		chp=140;
		bAtt=19;
		rAtt=0;
		bDef=10;
		rDef=0;
		healingsalve=2;
		criticalChance=5;
		criticalDamage=2.25;
	}
		else if (_type==PUTIN)
	{
		playerType="PUTIN";
		mhp=150;
		chp=150;
		bAtt=20;
		rAtt=0;
		bDef=5;
		rDef=0;
		healingsalve=4;
		criticalChance=15;
		criticalDamage=4;
	}
}

void playerChar::movePlayer(int x,int y)
{
	previousX=this->x;
	previousY=this->y;
	this->x += x;
	this->y += y;
}

void playerChar::drawPlayer()
{
	int previousX, previousY;
	previousX=GetCursorPositionX();
	previousY=GetCursorPositionY();
	GoToXY(x,y);
	SetFontColor(RED);
	cout<<"P";
	GoToXY(previousX,previousY);
	SetFontColor(GREEN);
}

void initiateMap()
{	
	char tempMap[row][col]=
	{
		{w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w},
		{w,t,e,e,e,w,e,e,e,e,e,e,e,e,t,e,e,e,e,w},
		{w,e,e,e,e,w,w,w,w,t,e,w,w,w,e,e,e,e,e,w},
		{w,e,e,e,t,e,e,e,e,e,e,e,e,w,w,e,e,e,e,w},
		{w,e,e,e,e,r,w,w,t,w,w,e,w,w,w,w,e,w,e,w},
		{w,t,e,e,e,w,e,e,e,e,w,r,w,e,e,w,t,e,w,w},
		{w,e,e,w,w,w,r,e,e,e,w,e,w,e,e,w,e,e,e,w},
		{w,w,e,w,e,e,e,e,e,e,w,e,w,e,e,w,w,w,e,w},
		{w,w,t,w,e,e,e,e,e,e,w,e,w,e,e,e,e,w,e,w},
		{w,w,e,w,e,e,e,e,t,w,r,e,e,e,e,e,w,e,r,w},
		{w,w,e,w,e,e,e,e,e,e,w,e,w,t,e,e,e,w,e,w},
		{w,w,e,w,w,e,e,e,e,e,w,e,w,e,e,e,e,w,e,w},
		{w,e,r,e,w,e,e,e,e,e,w,e,w,e,e,e,e,w,e,w},
		{w,t,e,e,w,w,w,w,w,w,w,e,w,w,w,w,w,w,e,w},
		{w,w,e,t,e,e,e,heal,e,e,e,e,e,r,e,e,t,e,e,w},
		{w,w,e,e,w,w,w,w,w,e,w,w,w,w,e,e,e,e,e,w},
		{w,w,e,w,w,w,w,e,e,C,e,e,e,w,e,e,e,e,t,w},
		{w,w,e,w,w,w,w,e,r,e,e,e,e,w,e,e,t,e,e,w},
		{w,w,w,w,e,e,e,e,e,T,e,e,e,w,e,e,e,e,e,w},
		{w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w},
	};
	
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			map[i][j]=tempMap[i][j];
		}
	}
}

void displayMap()
{

	for(int j=(player01.y-vRange-2 < 0 ? 0 : player01.y-vRange-2);j <= (player01.y+vRange-2 > row-2 ? row-2 : player01.y+vRange-2);j++)
	{

		for(int i=(player01.x-vRange-2 < 0 ? 0 : player01.x-vRange-2);i <= (player01.x+vRange-2 > col-2 ? col-2 : player01.x+vRange-2);i++)
		{
			GoToXY(i+1,j+1);
			cout<<map[j][i];
			SetFontColor(GRAY);	
		}
		cout<<endl;
	}
}

void playerChar::itemScenario(int x, int y)
{
	int playerChat;
	bool isExit=false;
	int random=rand()%2+1;
	
	do
	{
	cout<<"Found some Mango, eat it?" << endl;
	cout<<"1. Eat the mango" << endl;
	cout<<"2. Leave it" << endl;
	
	cin>>playerChat;
	
		switch(playerChat)
		{
			case 1:
				ClrScreen();
				displayMap();
				cout<<"You ate the Mango, health regained" << endl;
				system("pause");
				playerChar::chp+=7;
				if(playerChar::chp>playerChar::mhp)
				{
					playerChar::chp=playerChar::mhp;
				}
				map[y-1][x-1]=e;
				if(random==1)
				{
					ClrScreen();
					displayMap();
					cout<<"Found Healing Salve."<<endl;
					playerChar::healingsalve+=1;
					system("pause");
				}
				isExit=true;
				ClrScreen();
				displayMap();
				break;
			case 2:
				ClrScreen();
				displayMap();
				cout<<"Left the mango there." << endl;
				system("pause");
				isExit=true;
				ClrScreen();
				displayMap();
				break;
			default:
				InvalidInput(screenWidth * 0.5, screenHeight * 0.6 + 2);
				system("pause");
				ClrScreen();
		}
	}while(!isExit);
}

void playerChar::playerCollision()
{
	if(map[y-1][x-1]==(char)w)
	{
		x=previousX;
		y=previousY;
	}
	if(map[y-1][x-1]==(char)C)
	{
		SetFontColor(RED);
		cout<<"For Trump, fightttt...!"<<endl;
		battle=true;
		system("pause");
	}
	if(map[y-1][x-1]==(char)r)
	{
		int hploss = rand()%30+20;
		
			cout << "Damn the Clinton TRAPS!!" << endl;
			cout << "LOSE : "<< hploss <<"!!" << endl;
			player01.chp -= hploss;
			map[y-1][x-1]=(char)e;
	}
	if(map[y-1][x-1]==(char)t)
	{
		SetFontColor(BLUE);
		cout<<"For America, chargeeee...!"<<endl;
		battle=true;
		system("pause");
	}
	if(map[y-1][x-1]==(char)heal)
	{
		SetFontColor(CYAN);
		x=previousX;
		y=previousY;
		playerChar::itemScenario(8,15);
		map[y-1][x-1]=(char)e;
	}
	if(map[y-1][x-1]==(char)T)
	{
		cout<<"You saved Trump."<<endl;
		mainExit = true;
		system("pause");
	}
}

void enemyChar::initializeEnemy(ENEMY_TYPE type, int x, int y)
{
	this->type=type;
	this->x=x;
	this->y=y;
	
	if(type==CLONE1)
	{
		name="Clinton Clone 1";
		mhp=80;
		chp=80;
		bAtt=8;
		rAtt=0;
		bDef=2;
		rDef=0;
		criticalChance=1.5;
		criticalDamage=1.5;
	}
	else if(type==CLONE2)
	{
		name="Clinton Clone 2";
		mhp=60;
		chp=60;
		bAtt=6;
		rAtt=0;
		bDef=2;
		rDef=0;
		criticalChance=2;
		criticalDamage=1.5;
	}
	else if(type==CLONE3)
	{
		name="Clinton Clone 3";
		mhp=90;
		chp=90;
		bAtt=10;
		rAtt=0;
		bDef=4;
		rDef=0;
		criticalChance=2.5;
		criticalDamage=1.5;
	}
}


void playerChar::displayStats(int x, int y)
{
	GoToXY(x, y);
	cout<<"Name: "<<name<<endl;
	GoToXY(x, y+1);
	cout<<"Class: "<<playerType<<endl;
	GoToXY(x, y+2);
	cout<<"Health: "<<chp<<"/"<<mhp<<endl;
	GoToXY(x, y+3);
	cout<<"Attack: "<<bAtt<<"+"<<rAtt<<endl;
	GoToXY(x, y+4);
	cout<<"Defense: "<<bDef<<"+"<<rDef<<endl;
	GoToXY(x, y+5);
	cout<<"Critical Chance: "<<criticalChance<<"%"<<endl;
	GoToXY(x, y+6);
	cout<<"Healing Salve: "<<healingsalve<<endl;
}

void enemyChar::displayStats(int x, int y)
{
	GoToXY(x, y);
	cout<<"Name: "<<name<<endl;
	GoToXY(x, y+1);
	cout<<"Health: "<<chp<<"/"<<mhp<<endl;
	GoToXY(x, y+2);
	cout<<"Attack: "<<bAtt<<"+"<<rAtt<<endl;
	GoToXY(x, y+3);
	cout<<"Defense: "<<bDef<<"+"<<rDef<<endl;
	GoToXY(x, y+4);
	cout<<"Critical Chance: "<<criticalChance<<"%"<<endl;
}

void playerChar::attack(enemyChar &target)
{
	int random = rand() % 100 + 1;
	int totalDamage;

	if (criticalChance >= random)
	{
		GoToXY(1, screenHeight * 0.5+4);
		ClrLine();
		cout<<"You dealt critical damage!"<<endl;
		totalDamage = bAtt * criticalDamage + rAtt - (target.bDef+target.rDef);
	}
	else
	{
		totalDamage = bAtt + rAtt - (target.bDef+target.rDef);
	}

	if (totalDamage <= 0)
	{
		totalDamage = 1;
	}

	target.chp -= totalDamage;
}

void enemyChar::attack(playerChar &target)
{
	int random = rand() % 100 + 1;
	int totalDamage;

	if (criticalChance >= random)
	{
		GoToXY(1, screenHeight * 0.5+5);
		ClrLine();
		cout<<"The enemy dealt critical damage!"<<endl;
		totalDamage = bAtt * criticalDamage + rAtt - (target.bDef+target.rDef);
	}
	else
	{
		totalDamage = bAtt + rAtt - (target.bDef+target.rDef);
	}

	if (totalDamage <= 0)
	{
		totalDamage = 1;
	}

	target.chp -= totalDamage;
}

void battlePhase(playerChar &player, enemyChar &opponent)
{
	int battleChoice;
	int enemyAttack;
	string playerAction;
	string enemyAction;
	string totalAction;
	do
	{
		
	if(opponent.chp>0)
		{
			enemyAttack = rand() % 3+1;
		}
		else
		{
			cout<<"\nYou have successfully defeated the enemy!"<<endl;
			system("pause");
			battle=false;
			map[opponent.y-1][opponent.x-1]=e;
			ClrScreen();
			displayMap();
			continue;
		}
		
	if(player.chp<=0)
		{
			cout<<"\nYou were defeated in battle..."<<endl;
			system("pause");
			battle=false;
			ClrScreen();
			displayMap();
			continue;
		}
		
		bool isExit=false;
		do
		{
			ClrScreen();
			player.displayStats(screenWidth * 0.1, screenHeight * 0.1);
			opponent.displayStats(screenWidth * 0.5, screenHeight * 0.1);
			GoToXY(screenWidth * 0.1, screenHeight * 0.5);
			cout<<"Take an action."<<endl;
			GoToXY(screenWidth * 0.1, screenHeight * 0.5+1);
			cout<<"1. Attack"<<endl;
			GoToXY(screenWidth * 0.1, screenHeight * 0.5+2);
			cout<<"2. Defense"<<endl;
			GoToXY(screenWidth * 0.1, screenHeight * 0.5+3);
			cout<<"3. Attack + Defense"<<endl; 
			GoToXY(screenWidth * 0.1, screenHeight * 0.5+4);
			cout<<"4. Take Healing Salve"<<endl;
			
			GoToXY(screenWidth * 0.1, screenHeight * 0.5+5);
			
			cin>>battleChoice;
			
			cout<<endl;
			
			switch(battleChoice)
			{
				case 1:
					player.rAtt+=3;
					GoToXY(1, screenHeight * 0.5);
					ClrLine();
					cout<<"You attack the enemy."<<endl;
					isExit=true;
					break;
				case 2:
					player.rDef+=3;
					GoToXY(1, screenHeight * 0.5);
					ClrLine();
					cout<<"You took defense."<<endl;
					isExit=true;
					break;
				case 3:
					player.rAtt+=1;
					player.rDef+=1;
					GoToXY(1, screenHeight * 0.5);
					ClrLine();
					cout<<"You attack while defending."<<endl;
					isExit=true;
					break;
				case 4:
					if(player.healingsalve>0)
					{
						player.healingsalve-=1;
						player.chp+=20;
						if(player.chp>=player.mhp)
						{
							player.chp=player.mhp;
						}
						GoToXY(1, screenHeight * 0.5);
						ClrLine();
						cout<<"Consumed healing salve and healed yourself."<<endl;
						isExit=true;
						break;
					}
					else
					{
						GoToXY(1, screenHeight * 0.5);
						ClrLine();
						cout<<"Healing Salve = 0"<<endl;
						isExit=true;
						break;
					}
				default:
					InvalidInput(screenWidth * 0.5, screenHeight * 0.6 + 2);
					system("pause");
					ClrScreen();
			}
		}while(!isExit);
		
		GoToXY(1, screenHeight * 0.5+1);
		ClrLine();
		
		if(enemyAttack==1)
		{
			opponent.rAtt+=3;
			cout<<"Enemy attacked you."<<endl;
		}
		else if(enemyAttack==2)
		{
			opponent.rDef+=3;
			cout<<"Enemy took cover."<<endl;
		}
		else
		{
			opponent.rAtt+=1;
			opponent.rDef+=1;
			cout<<"Attack while defending." << endl;
		}
		
		GoToXY(1, screenHeight * 0.5+2);
		ClrLine();
		
		if(battleChoice==enemyAttack)
		{
			cout<<"Received damage together!"<<endl;
			player.attack(opponent);
			opponent.attack(player);
		}
		if(battleChoice==1&&enemyAttack==2)
		{
			cout<<"You received damage!"<<endl;
			opponent.attack(player);
		}
		if(battleChoice==1&&enemyAttack==3)
		{
			cout<<"Enemy received damage!"<<endl;
			player.attack(opponent);
		}
		if(battleChoice==2&&enemyAttack==1)
		{
			cout<<"Enemy received damage!"<<endl;
			player.attack(opponent);
		}
		if(battleChoice==2&&enemyAttack==3)
		{
			cout<<"You received damage!"<<endl;
			opponent.attack(player);
		}
		if(battleChoice==3&&enemyAttack==1)
		{
			cout<<"You took a hit!"<<endl;
			opponent.attack(player);
		}
		if(battleChoice==3&&enemyAttack==2)
		{
			cout<<"Enemy received damage!"<<endl;
			player.attack(opponent);
		}
		if(battleChoice==4&&enemyAttack==2)
		{
			cout<<"Received damage while healing yourself!"<<endl;
			opponent.attack(player);
		}
		if(battleChoice==4&&enemyAttack==1||battleChoice==4&&enemyAttack==3)
		{
			cout<<"You took healing salve completely!"<<endl;
		}
		
		GoToXY(1, screenHeight * 0.1);
		ClrLine();
		GoToXY(1, screenHeight * 0.1+1);
		ClrLine();
		GoToXY(1, screenHeight * 0.1+2);
		ClrLine();
		GoToXY(1, screenHeight * 0.1+3);
		ClrLine();
		GoToXY(1, screenHeight * 0.1+4);
		ClrLine();
		GoToXY(1, screenHeight * 0.1+5);
		ClrLine();
		GoToXY(1, screenHeight * 0.1+6);
		ClrLine();
		GoToXY(1, screenHeight * 0.1+7);
		ClrLine();
		GoToXY(1, screenHeight * 0.1);
		player.displayStats(screenWidth * 0.1, screenHeight * 0.1);
		opponent.displayStats(screenWidth * 0.5, screenHeight * 0.1);
		GoToXY(1, screenHeight * 0.5+7);

		system("pause");
		
		player.rAtt=0;
		player.rDef=0;
		opponent.rAtt=0;
		opponent.rDef=0;
	}while(battle);
	player.rAtt=0;
	player.rDef=0;
	opponent.rAtt=0;
	opponent.rDef=0;
}

bool restartGame()
{
	int playerChat;
	bool isExit=false;
	
	do
	{
		ClrScreen();
		displayMap();
		cout<<"Do you want to play again?"<<endl;
		cout<<"1. Yes"<<endl;
		cout<<"2. No"<<endl;
		
		cin>>playerChat;
		
		switch(playerChat)
		{
			case 1:
				ClrScreen();
				return true;
				break;
			case 2:
				ClrScreen();
				return false;
				break;
			default:
				InvalidInput(screenWidth * 0.5, screenHeight * 0.6 + 2);
				system("pause");
				ClrScreen();
				break;
		}
	}while(!isExit);
}

int main()
{
	do
	{	
		srand(time(NULL));
		
		SetWindowSize(screenWidth, screenHeight);
		
		GameIntro();
	
		if (choice==1)
		{
			player01.initializePlayer(HITLER);
			vRange=2;
		}
		else if(choice==2)
		{
			vRange=3;
			player01.initializePlayer(OBAMA);
		}
		else
		{
			player01.initializePlayer(PUTIN);
			vRange=2;
		}
		initiateMap();
		
		mainExit = false;
		
		do
		{	
			if(!(numberOfEnemies>0||player01.chp<=0||battle==true))
			{
				if(GetAsyncKeyState(VK_UP))
				{
					player01.movePlayer(0,-1);
				}
				else if(GetAsyncKeyState(VK_DOWN))
				{
					player01.movePlayer(0,1);
				}
				else if(GetAsyncKeyState(VK_LEFT))
				{
					player01.movePlayer(-1,0);
				}
				else if(GetAsyncKeyState(VK_RIGHT))
				{
					player01.movePlayer(1,0);
				}
			}
			
			displayMap();
			
			player01.playerCollision();
			
			
			if(battle)
			{
				int random = rand() % ENEMY_TOTAL;
				enemyChar newEnemy;
				newEnemy.initializeEnemy((ENEMY_TYPE)random, player01.x, player01.y);
				battlePhase(player01, newEnemy);
			}
			
			player01.drawPlayer();
			
			player01.displayStats(1, screenHeight * 0.5);
	
			if(player01.chp<=0)
			{
				mainExit=true;
			}
			
			GoToXY(1, screenHeight * 0.9);
			system("pause");
			ClrScreen();
		}while(!mainExit);
	}while(restartGame());
	
	
	system("pause");
	return 0;
}
