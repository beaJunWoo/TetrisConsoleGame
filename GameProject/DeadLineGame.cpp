#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

//���� ũ��
#define BufferWidth 150
#define BufferHeight 70

//�׽�Ʈ��
#define TestStage STAGE1
#define TeatStage_ STAGE1_1

//�ΰ�,�޴�ũ��
#define MapX 70 
#define MapY 30
#define LogoSize 18
#define MenuSize 18
#define MenuPage 35
#define MenuTitleSize 6

//������Ʈ ũ��
#define  PlayerSizeX 3
#define  PlayerSizeY 4
#define  EnemySizeX 3
#define  EnemySizeY 4

//��ȭ�� ������
#define LogoDelay 100
#define MenuDelay 100

//���� ����
#define PistolSpeed 4
#define RifleSpeed 4
#define GunY -2

//������Ʈ �Ҵ��
#define EnemyCount 20
#define ItemCount 5 
#define playerBulletCount 10
#define enemyBulletCount 30
#define TrapCount 20

//define������������������
//define������������������

//ù ���̵� ����
int guideStartTime = 0;
int guideEndTime = 0;
bool guideMove = true;
bool guideAttack = true;
bool guideJump = true;


const char* LogoTitle[LogoSize];
const char* MenuTitle[MenuTitleSize];
const char* MenuMap[MenuPage][MenuSize];
const char* bulletShape[3][8];
const char* WeaphoneMap[3][3];

char* Bullet1_Num = (char*)malloc(sizeof(char));
char* Bullet2_Num = (char*)malloc(sizeof(char));

const float G = 9.81;
const float BombG = 8.5;

float V = 15.0f;
float time = 0.f;
int jumpTime = 0;

int keyInfoDelay[2] = { 3,0 };
bool isKeyInfo = false;

#pragma region Enum
enum Menu
{
	EXIT,
	LOGO,
	MENU,
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE4,
};
enum Stage
{
	EXIT_STAGE,
	STAGE1_1,
	STAGE1_2,
	STAGE1_3,
	STAGE1_4,
	STAGE2_1,
	STAGE2_2,
	STAGE2_3,
	STAGE2_4,
	STAGE3_1,
	STAGE3_2,
	STAGE3_3,
	STAGE3_4,
	STAGE4_1,
	STAGE4_2,
	STAGE4_3,
	STAGE4_4,
};
enum Color
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE,
};
Menu menu = TestStage; //�׽�Ʈ��
Stage stage = TeatStage_;
enum ItemEffect
{
	HEAL,
	ADD_02,    //2�� �Ѿ� �߰�
	ADD_bomb,
};
enum Direction
{
	STAND,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	L_UP,
	L_DOWN,
	R_UP,
	R_DOWN
};
enum Weapone
{
	PISTOL,
	RIFLE,
	BOMB,
};
enum Delay
{
	NOW_TIME,
	MAX_TIME
};
#pragma endregion

#pragma region DoubleBuffer
HANDLE hBuffer[2];
int screenIndex;
void InitBuffer();
void WriteBuffer(int x, int y, const char* shape, int color);
void FlipBuffer();
void ClearBuffer();
void DestroyBuffer();
#pragma endregion

int stage1_1_Map[MapY][MapX] =
{   //                    10                  20                  30                  40                  50                  60 
	//0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9
	{6,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,6,},//1
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//2
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//3
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//4
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//5
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//6
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//7
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//8
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//9
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//0	10
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//1
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//2
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//3
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//4
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//5
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//6
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//7
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//8
	{6,0,6,6,6,6,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//9
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//0	20
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,},//1
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//2
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,6,},//3
	{6,6,6,6,6,6,6,6,6,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//4
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//5
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//6
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//7
	{6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,},//8
	{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,},//9

};
int(*pMap1_1)[MapX] = stage1_1_Map;

int KeyInfoMap[10][50] = {
	{3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,6},
};
struct Player
{
	int x;
	int y;
	Color color;
	int direction;
	int speed[2];
	int bulletNum[3];//[0]=1������ ź��
	int bulletDelay[3][2];
	int downHpDelay[2];
	int hp;
	int h;
	int weaponNum;
	int moveDriction;
	bool isfloat;
	bool isJump;
	bool isDownHp;
	const char* shape[9][PlayerSizeY];
	const char* Weaphone[9][2];
	const char* die;
};
Player* player = {};

struct Bullet
{
	int x;
	int y;
	int Xcount[2];
	int Ycount[2];
	int damage;
	int direction;
	int speed;
	const char* shape[8];
	const char* destroy[8];
};
struct Gun
{
	Bullet* bullet[4] = {};
};
Gun* playerBullet[playerBulletCount] = {};
Bullet* enemyBullet[enemyBulletCount] = {};

struct Enemy
{
	int x;
	int y;
	Color color;
	int Lv;
	int hp;
	int rerodingTime[2];
	int responTime;
	bool isLeft;
	bool isDownHp;
	int downHpDelay[2];
	int moveDir[2] = { 0,0 };
	const char* shape[2][5];
	const char* die[2][5];
};
Enemy* enemy[EnemyCount] = {};

struct Item
{
	int x;
	int y;
	Color color;
	ItemEffect itemEffect;
	const char* shape[3];
};
Item* item[ItemCount] = {};

struct Trap
{
	int x;
	int y;
	int width;
	int damage;
	int color;
	int attackDelay[2];
	const char* shape;
};
Trap* trap[TrapCount] = {};

struct Bomb
{
	int x;
	int y;
	int direction;
	float time;
	float V;
	int responTime;
	float Xspeed;
	float YSpeed;
	bool isbump;
	const char* shape;
};
Bomb* bomb = {};


//Function������������������
//Function������������������
#pragma region Logo
void LogoInitialize();
void LogoProgress();
void LogoRender(int Filcker);
void LogoRelease();
#pragma endregion

#pragma region Menu
void MenuInitialize();
void MenuProgress();
void MenuRender(int Num, int& LogoPage);
void MenuRelease();
#pragma endregion

#pragma region Stage1
void Stage1_progress();
void Stage1_1();
void Stage1_2();
void Stage1_3();
void Stage1_4();
#pragma endregion
#pragma region Enemy
void EnemyRander();
void EnemyInit(int(*Map)[MapX]);
void EnemyBulletProgress(int(*Map)[MapX]);
void EnemyPorogress(int(*Map)[MapX]);
void EnemyHpDownEffect();
int ResultEnemyCount();
#pragma endregion

#pragma region Physics
void PlayerGravity(int(*Map)[MapX]);
#pragma endregion
void PlayerInit(int x, int y);
void PlayerProgress(int(*Map)[MapX]);
void PlayerRender();
void MapRender(int(*Map)[MapX]);
void PlayerHpDownEffect();
#pragma region UI
void GunUI_Init();
void GunUI_Rander();
#pragma endregion


#pragma region Bullet
void BulletShapeInit();
void PlayerBulletInit(double speed, int damage, int weaponNumber, int(*Map)[MapX]);
void PlayerBulletProgress(int(*Map)[MapX]);
#pragma endregion
//Function������������������
//Function������������������

//����������������������������������������������������������������������������������������������������������������������������������������������
//����������������������������������������������������������������������������������������������������������������������������������������������
int main()
{
	InitBuffer();
	BulletShapeInit();
	GunUI_Init();
	while (menu)
	{
		switch (menu)
		{
		case EXIT:
			break;
		case LOGO:
			LogoProgress();
			break;
		case MENU:
			MenuProgress();
			break;
		case STAGE1:
			Stage1_progress();
		default:
			break;
		}
	}
	DestroyBuffer();
	return 0;
}
//���������������������������������������������������������������������������������������������������������������������������������������������
//���������������������������������������������������������������������������������������������������������������������������������������������

#pragma region DoubleBuffer
void InitBuffer()
{
	screenIndex = 0;

	COORD size = { BufferWidth, BufferHeight };
	SMALL_RECT rect = { 0, 0, BufferWidth, BufferHeight };

	hBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[0], size);
	SetConsoleWindowInfo(hBuffer[0], TRUE, &rect);

	hBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleScreenBufferSize(hBuffer[1], size);
	SetConsoleWindowInfo(hBuffer[1], TRUE, &rect);

	CONSOLE_CURSOR_INFO Info;
	Info.dwSize = 1;
	Info.bVisible = FALSE;

	SetConsoleCursorInfo(hBuffer[0], &Info);
	SetConsoleCursorInfo(hBuffer[1], &Info);


}
void WriteBuffer(int x, int y, const char* shape, int color)
{
	COORD pos = { x * 2, y };

	SetConsoleCursorPosition(hBuffer[screenIndex], pos);
	SetConsoleTextAttribute(hBuffer[screenIndex], color);

	DWORD dw;
	WriteFile(hBuffer[screenIndex], shape, strlen(shape), &dw, NULL);


}
void FlipBuffer()
{
	SetConsoleActiveScreenBuffer(hBuffer[screenIndex]);
	screenIndex = !screenIndex;
}
void ClearBuffer()
{
	COORD pos = { 0,0 };
	DWORD dw;
	FillConsoleOutputCharacter(hBuffer[screenIndex], ' ', BufferWidth * BufferHeight, pos, &dw);
}
void DestroyBuffer()
{
	CloseHandle(hBuffer[0]);
	CloseHandle(hBuffer[1]);
}
#pragma endregion

#pragma region Logo
void LogoInitialize()
{
	LogoTitle[0] = "                                                                    dddddddd                                                            ";
	LogoTitle[1] = "DDDDDDDDDDDDD                                                       d::::::d  lllllll    iiii                                           ";
	LogoTitle[2] = "D::::::::::::DDD                                                    d::::::d  l:::::l   i::::i                                          ";
	LogoTitle[3] = "D:::::::::::::::DD                                                  d::::::d  l:::::l    iiii                                           ";
	LogoTitle[4] = "DDD:::::DDDDD:::::D                                                 d:::::d   l:::::l                                                   ";
	LogoTitle[5] = "  D:::::D    D:::::D     eeeeeeeeeeee    aaaaaaaaaaaaa      ddddddddd:::::d    l::::l  iiiiiii  nnnn  nnnnnnnn          eeeeeeeeeeee    ";
	LogoTitle[6] = "  D:::::D     D:::::D  ee::::::::::::ee  a::::::::::::a   dd::::::::::::::d    l::::l  i:::::i  n:::nn::::::::nn      ee::::::::::::ee  ";
	LogoTitle[7] = "  D:::::D     D:::::D e::::::eeeee:::::eeaaaaaaaaa:::::a d::::::::::::::::d    l::::l   i::::i  n::::::::::::::nn    e::::::eeeee:::::ee";
	LogoTitle[8] = "  D:::::D     D:::::De::::::e     e:::::e         a::::ad:::::::ddddd:::::d    l::::l   i::::i  nn:::::::::::::::n  e::::::e     e:::::e";
	LogoTitle[9] = "  D:::::D     D:::::De:::::::eeeee::::::e  aaaaaaa:::::ad::::::d    d:::::d    l::::l   i::::i    n:::::nnnn:::::n  e:::::::eeeee::::::e";
	LogoTitle[10] = "  D:::::D     D:::::De:::::::::::::::::e aa::::::::::::ad:::::d     d:::::d    l::::l   i::::i    n::::n    n::::n  e:::::::::::::::::e ";
	LogoTitle[11] = "  D:::::D     D:::::De::::::eeeeeeeeeee a::::aaaa::::::ad:::::d     d:::::d    l::::l   i::::i    n::::n    n::::n  e::::::eeeeeeeeeee  ";
	LogoTitle[12] = "  D:::::D    D:::::D e:::::::e         a::::a    a:::::ad:::::d     d:::::d    l::::l   i::::i    n::::n    n::::n  e:::::::e           ";
	LogoTitle[13] = "DDD:::::DDDDD:::::D  e::::::::e        a::::a    a:::::ad::::::ddddd::::::dd  l::::::l i::::::i   n::::n    n::::n  e::::::::e          ";
	LogoTitle[14] = "D:::::::::::::::DD    e::::::::eeeeeeeea:::::aaaa::::::a d:::::::::::::::::d  l::::::l i::::::i   n::::n    n::::n   e::::::::eeeeeeee  ";
	LogoTitle[15] = "D::::::::::::DDD       ee:::::::::::::e a::::::::::aa:::a d:::::::::ddd::::d  l::::::l i::::::i   n::::n    n::::n    ee:::::::::::::e  ";
	LogoTitle[16] = "DDDDDDDDDDDDD            eeeeeeeeeeeeee  aaaaaaaaaa  aaaa  ddddddddd   ddddd  llllllll iiiiiiii   nnnnnn    nnnnnn      eeeeeeeeeeeeee  ";

}
void LogoProgress()
{
	int LogoPage = 0;
	int Flicker = 0;
	LogoInitialize();
	InitBuffer();
	while (true)
	{
		LogoRender(Flicker);
		Flicker++;

		if (GetAsyncKeyState(VK_SPACE))
		{
			menu = MENU;
			break;
		}

		FlipBuffer();
		ClearBuffer();
		Sleep(LogoDelay);
	}
	LogoRelease();

}
void LogoRender(int Filcker)
{

	if (Filcker % 10 > 5)
	{
		WriteBuffer(35, 30, "SPACE�� ��������", RED);
	}
	for (int i = 0; i < 17; i++)
	{
		WriteBuffer(5, 5 + i, LogoTitle[i], WHITE);
	}
}
void LogoRelease()
{
	for (int i = 0; i < 12; i++)
	{
		LogoTitle[i] = nullptr;
	}
}
#pragma endregion

#pragma region Menu
void MenuInitialize()
{

	MenuTitle[0] = "888888ba                          dP dP oo                  ";
	MenuTitle[1] = "88    `8b                         88 88                     ";
	MenuTitle[2] = "88     88 .d8888b. .d8888b. .d888b88 88 dP 88d888b. .d8888b. ";
	MenuTitle[3] = "88     88 88ooood8 88'  `88 88'  `88 88 88 88'  `88 88ooood8 ";
	MenuTitle[4] = "88    .8P 88.  ... 88.  .88 88.  .88 88 88 88    88 88.  ... ";
	MenuTitle[5] = "8888888P  `88888P' `88888P8 `88888P8 88 dP dP    dP `88888P' ";

	MenuMap[0][0] = "                                                                                                                                   ";
	MenuMap[0][1] = "                                                                                                                                   ";
	MenuMap[0][2] = "                                                                                                                                   ";
	MenuMap[0][3] = "                                                                                                                                   ";
	MenuMap[0][4] = "                                                                                                                                   ";
	MenuMap[0][5] = "                                                                                                                                   ";
	MenuMap[0][6] = "                                                                                                                                   ";
	MenuMap[0][7] = "                                                                                                                                   ";
	MenuMap[0][8] = "                                                                                                                                   ";
	MenuMap[0][9] = "                                                                                                                                   ";
	MenuMap[0][10] = "                                                                                                                                   ";
	MenuMap[0][11] = "                                                                                                                                   ";
	MenuMap[0][12] = "                                                                                                                                   ";
	MenuMap[0][13] = "                                                                                                                                   ";
	MenuMap[0][14] = "                                                                                                                                   ";
	MenuMap[0][15] = "                                                                                                                                   ";
	MenuMap[0][16] = "                                                                                                                                   ";
	MenuMap[0][17] = "                                                                                                                                   ";

	MenuMap[1][0] = "                                                                                                                                   ";
	MenuMap[1][1] = "                                                                                                                                   ";
	MenuMap[1][2] = "                                                                                                                                   ";
	MenuMap[1][3] = "                                                                                                                            11111  ";
	MenuMap[1][4] = "                                                                                                                           11111111";
	MenuMap[1][5] = "                                                                                                                                   ";
	MenuMap[1][6] = "                                                                                                                                   ";
	MenuMap[1][7] = "                                                                                                                                   ";
	MenuMap[1][8] = "                                                                                                                                  1";
	MenuMap[1][9] = "                                                                                                                             111111";
	MenuMap[1][10] = "                                                                                                                            1000000";
	MenuMap[1][11] = "                                                                                                                              11100";
	MenuMap[1][12] = "                                                                                                                               1000";
	MenuMap[1][13] = "                                                                                                                                110";
	MenuMap[1][14] = "                                                                                                                                  1";
	MenuMap[1][15] = "                                                                                                                                   ";
	MenuMap[1][16] = "                                                                                                                                   ";
	MenuMap[1][17] = "                                                                                                                                   ";

	MenuMap[2][0] = "                                                                                                                                   ";
	MenuMap[2][1] = "                                                                                                                                   ";
	MenuMap[2][2] = "                                                                                                                                   ";
	MenuMap[2][3] = "                                                                                                                    11111          ";
	MenuMap[2][4] = "                                                                                                                   1111111111111111";
	MenuMap[2][5] = "                                                                                                                                   ";
	MenuMap[2][6] = "                                                                                                                                   ";
	MenuMap[2][7] = "                                                                                                                                   ";
	MenuMap[2][8] = "                                                                                                                          11111  11";
	MenuMap[2][9] = "                                                                                                                     11111111111  1";
	MenuMap[2][10] = "                                                                                                                    100000001111111";
	MenuMap[2][11] = "                                                                                                                      1110000111111";
	MenuMap[2][12] = "                                                                                                                       100000011111";
	MenuMap[2][13] = "                                                                                                                        11000000111";
	MenuMap[2][14] = "                                                                                                                          110000011";
	MenuMap[2][15] = "                                                                                                                            1111000";
	MenuMap[2][16] = "                                                                                                                                111";
	MenuMap[2][17] = "                                                                                                                                   ";

	MenuMap[3][0] = "                                                                                                                                   ";
	MenuMap[3][1] = "                                                                                                                                   ";
	MenuMap[3][2] = "                                                                                                                                   ";
	MenuMap[3][3] = "                                                                                                            11111                  ";
	MenuMap[3][4] = "                                                                                                           111111111111111111111111";
	MenuMap[3][5] = "                                                                                                                             111111";
	MenuMap[3][6] = "                                                                                                                               1111";
	MenuMap[3][7] = "                                                                                                                               1111";
	MenuMap[3][8] = "                                                                                                                  11111  111   1111";
	MenuMap[3][9] = "                                                                                                             11111111111  1111     ";
	MenuMap[3][10] = "                                                                                                            10000000111111111111111";
	MenuMap[3][11] = "                                                                                                              111000011111111111111";
	MenuMap[3][12] = "                                                                                                               10000001111111111111";
	MenuMap[3][13] = "                                                                                                                1100000011111111111";
	MenuMap[3][14] = "                                                                                                                  11000001100000001";
	MenuMap[3][15] = "                                                                                                                    111100000000000";
	MenuMap[3][16] = "                                                                                                                        11111111111";
	MenuMap[3][17] = "                                                                                                                                   ";

	MenuMap[4][0] = "                                                                                                                                 11";
	MenuMap[4][1] = "                                                                                                                                   ";
	MenuMap[4][2] = "                                                                                                                                   ";
	MenuMap[4][3] = "                                                                                                    11111                        11";
	MenuMap[4][4] = "                                                                                                   11111111111111111111111111111111";
	MenuMap[4][5] = "                                                                                                                     11111111111111";
	MenuMap[4][6] = "                                                                                                                       111111111110";
	MenuMap[4][7] = "                                                                                                                       111111111111";
	MenuMap[4][8] = "                                                                                                          11111  111   111111111111";
	MenuMap[4][9] = "                                                                                                     11111111111  1111        11111";
	MenuMap[4][10] = "                                                                                                    1000000011111111111111111111111";
	MenuMap[4][11] = "                                                                                                      11100001111111111111111111111";
	MenuMap[4][12] = "                                                                                                       1000000111111111111111111111";
	MenuMap[4][13] = "                                                                                                        110000001111111111111111111";
	MenuMap[4][14] = "                                                                                                          1100000110000000111111111";
	MenuMap[4][15] = "                                                                                                            11110000000000000000000";
	MenuMap[4][16] = "                                                                                                                1111111111111111111";
	MenuMap[4][17] = "                                                                                                                                   ";

	MenuMap[5][0] = "                                                                                                                         1111111111";
	MenuMap[5][1] = "                                                                                                                            1000001";
	MenuMap[5][2] = "                                                                                                                             11 11 ";
	MenuMap[5][3] = "                                                                                            11111                        1111111111";
	MenuMap[5][4] = "                                                                                           1111111111111111111111111111111111111111";
	MenuMap[5][5] = "                                                                                                             1111111111111111111111";
	MenuMap[5][6] = "                                                                                                               11111111111001111111";
	MenuMap[5][7] = "                                                                                                               11111111111111111111";
	MenuMap[5][8] = "                                                                                                  11111  111   11111111111111111111";
	MenuMap[5][9] = "                                                                                             11111111111  1111        1111111111111";
	MenuMap[5][10] = "                                                                                            100000001111111111111111111111110000000";
	MenuMap[5][11] = "                                                                                              1110000111111111111111111111111110000";
	MenuMap[5][12] = "                                                                                               100000011111111111111111111111110000";
	MenuMap[5][13] = "                                                                                                11000000111111111111111111111110000";
	MenuMap[5][14] = "                                                                                                  110000011000000011111111111110000";
	MenuMap[5][15] = "                                                                                                    1111000000000000000000000000000";
	MenuMap[5][16] = "                                                                                                        1111111111111111111111  1  ";
	MenuMap[5][17] = "                                                                                                                                   ";

	MenuMap[6][0] = "                                                                                                                 1111111111        ";
	MenuMap[6][1] = "                                                                                                                    1000001     111";
	MenuMap[6][2] = "                                                                                                                     11 11     1101";
	MenuMap[6][3] = "                                                                                    11111                        111111111111111111";
	MenuMap[6][4] = "                                                                                   11111111111111111111111111111111111111111111111 ";
	MenuMap[6][5] = "                                                                                                     11111111111111111111111111111 ";
	MenuMap[6][6] = "                                                                                                       111111111110011111111111111 ";
	MenuMap[6][7] = "                                                                                                       1111111111111111111111111111";
	MenuMap[6][8] = "                                                                                          11111  111   1111111111111111111111111111";
	MenuMap[6][9] = "                                                                                     11111111111  1111        11111111111111  11   ";
	MenuMap[6][10] = "                                                                                    100000001111111111111111111111110000000        ";
	MenuMap[6][11] = "                                                                                      11100001111111111111111111111111100001       ";
	MenuMap[6][12] = "                                                                                       10000001111111111111111111111111000011111111";
	MenuMap[6][13] = "                                                                                        1100000011111111111111111111111000011000111";
	MenuMap[6][14] = "                                                                                          11000001100000001111111111111000010001111";
	MenuMap[6][15] = "                                                                                            111100000000000000000000000000000000111";
	MenuMap[6][16] = "                                                                                                1111111111111111111111  1  00000111";
	MenuMap[6][17] = "                                                                                                                           11111111";

	MenuMap[7][0] = "                                                                                                         1111111111                ";
	MenuMap[7][1] = "                                                                                                            1000001     1111111111 ";
	MenuMap[7][2] = "                                                                                                             11 11     110111101111";
	MenuMap[7][3] = "                                                                            11111                        11111111111111111111111 11";
	MenuMap[7][4] = "                                                                           11111111111111111111111111111111111111111111111 11111111";
	MenuMap[7][5] = "                                                                                             11111111111111111111111111111 11111111";
	MenuMap[7][6] = "                                                                                               111111111110011111111111111  1111111";
	MenuMap[7][7] = "                                                                                               111111111111111111111111111111111111";
	MenuMap[7][8] = "                                                                                  11111  111   111111111111111111111111111111111111";
	MenuMap[7][9] = "                                                                             11111111111  1111        11111111111111  11       11  ";
	MenuMap[7][10] = "                                                                            100000001111111111111111111111110000000            11  ";
	MenuMap[7][11] = "                                                                              11100001111111111111111111111111100001           11  ";
	MenuMap[7][12] = "                                                                               1000000111111111111111111111111100001111111111111111";
	MenuMap[7][13] = "                                                                                110000001111111111111111111111100001100011100011101";
	MenuMap[7][14] = "                                                                                  1100000110000000111111111111100001000111110111111";
	MenuMap[7][15] = "                                                                                    11110000000000000000000000000000000011110111111";
	MenuMap[7][16] = "                                                                                        1111111111111111111111  1  0000011100011100";
	MenuMap[7][17] = "                                                                                                                   11111111111     ";

	MenuMap[8][0] = "                                                                                                 1111111111                        ";
	MenuMap[8][1] = "                                                                                                    1000001     1111111111         ";
	MenuMap[8][2] = "                                                                                                     11 11     110111101111        ";
	MenuMap[8][3] = "                                                                    11111                        11111111111111111111111 111  1    ";
	MenuMap[8][4] = "                                                                   11111111111111111111111111111111111111111111111 1111111111111111";
	MenuMap[8][5] = "                                                                                     11111111111111111111111111111 1111111111111111";
	MenuMap[8][6] = "                                                                                       111111111110011111111111111  111111111111111";
	MenuMap[8][7] = "                                                                                       11111111111111111111111111111111111111111111";
	MenuMap[8][8] = "                                                                          11111  111   11111111111111111111111111111111111111111111";
	MenuMap[8][9] = "                                                                     11111111111  1111        11111111111111  11       11   11 11  ";
	MenuMap[8][10] = "                                                                    100000001111111111111111111111110000000            11    1  1  ";
	MenuMap[8][11] = "                                                                      11100001111111111111111111111111100001           11   11  1  ";
	MenuMap[8][12] = "                                                                       100000011111111111111111111111110000111111111111111111111111";
	MenuMap[8][13] = "                                                                        11000000111111111111111111111110000110001110001110111011111";
	MenuMap[8][14] = "                                                                          110000011000000011111111111110000100011111011111111111111";
	MenuMap[8][15] = "                                                                            1111000000000000000000000000000000001111011111111111111";
	MenuMap[8][16] = "                                                                                1111111111111111111111  1  000001110001110000011111";
	MenuMap[8][17] = "                                                                                                           11111111111             ";

	MenuMap[9][0] = "                                                                              1111111111                                           ";
	MenuMap[9][1] = "                                                                                 1000001     1111111111                            ";
	MenuMap[9][2] = "                                                                                  11 11     110111101111                           ";
	MenuMap[9][3] = "                                                 11111                        11111111111111111111111 111  1    1                  ";
	MenuMap[9][4] = "                                                11111111111111111111111111111111111111111111111 1111111111111111111                ";
	MenuMap[9][5] = "                                                                  11111111111111111111111111111 11111111111111111111111            ";
	MenuMap[9][6] = "                                                                    111111111110011111111111111  111111111111111111111             ";
	MenuMap[9][7] = "                                                                    111111111111111111111111111111111111111111111111111            ";
	MenuMap[9][8] = "                                                       11111  111   111111111111111111111111111111111111111111111111111            ";
	MenuMap[9][9] = "                                                  11111111111  1111        11111111111111  11       11   11 11  11111  1           ";
	MenuMap[9][10] = "                                                 100000001111111111111111111111110000000            11    1  1  11                 ";
	MenuMap[9][11] = "                                                   11100001111111111111111111111111100001           11   11  1  11                 ";
	MenuMap[9][12] = "                                                    10000001111111111111111111111111000011111111111111111111111111111111           ";
	MenuMap[9][13] = "                                                     1100000011111111111111111111111000011000111000111011101111111111111           ";
	MenuMap[9][14] = "                                                       11000001100000001111111111111000010001111101111111111111111111111           ";
	MenuMap[9][15] = "                                                         111100000000000000000000000000000000111101111111111111111011001           ";
	MenuMap[9][16] = "                                                             1111111111111111111111  1  000001110001110000011111111111             ";
	MenuMap[9][17] = "                                                                                        11111111111                                ";

	MenuMap[10][0] = "                                                                  1111111111                                                      ";
	MenuMap[10][1] = "                                                                     1000001     1111111111                                       ";
	MenuMap[10][2] = "                                                                      11 11     110111101111                                      ";
	MenuMap[10][3] = "                                     11111                        11111111111111111111111 111  1    1                             ";
	MenuMap[10][4] = "                                    11111111111111111111111111111111111111111111111 1111111111111111111                           ";
	MenuMap[10][5] = "                                                      11111111111111111111111111111 11111111111111111111111                       ";
	MenuMap[10][6] = "                                                        111111111110011111111111111  111111111111111111111                        ";
	MenuMap[10][7] = "                                                        111111111111111111111111111111111111111111111111111                       ";
	MenuMap[10][8] = "                                           11111  111   111111111111111111111111111111111111111111111111111                       ";
	MenuMap[10][9] = "                                      11111111111  1111        11111111111111  11       11   11 11  11111  11                     ";
	MenuMap[10][10] = "                                     100000001111111111111111111111110000000            11    1  1  11                            ";
	MenuMap[10][11] = "                                       11100001111111111111111111111111100001           11   11  1  11        111                 ";
	MenuMap[10][12] = "                                        100000011111111111111111111111110000111111111111111111111111111111111111                  ";
	MenuMap[10][13] = "                                         11000000111111111111111111111110000110001110001110111011111111111110001                  ";
	MenuMap[10][14] = "                                           11000001100000001111111111111000010001111101111111111111111111111101                   ";
	MenuMap[10][15] = "                                             1111000000000000000000000000000000001111011111111111111110110011                     ";
	MenuMap[10][16] = "                                                 1111111111111111111111  1  000001110001110000011111111111                        ";
	MenuMap[10][17] = "                                                                            11111111111                                           ";

	MenuMap[11][0] = "                                                      1111111111                                                                  ";
	MenuMap[11][1] = "                                                         1000001     1111111111                                                   ";
	MenuMap[11][2] = "                                                          11 11     110111101111                                                  ";
	MenuMap[11][3] = "                         11111                        11111111111111111111111 111  1    1                                         ";
	MenuMap[11][4] = "                        11111111111111111111111111111111111111111111111 1111111111111111111                                       ";
	MenuMap[11][5] = "                                          11111111111111111111111111111 11111111111111111111111                                   ";
	MenuMap[11][6] = "                                            111111111110011111111111111  111111111111111111111                                    ";
	MenuMap[11][7] = "                                            111111111111111111111111111111111111111111111111111                                   ";
	MenuMap[11][8] = "                               11111  111   111111111111111111111111111111111111111111111111111                                   ";
	MenuMap[11][9] = "                          11111111111  1111        11111111111111  11       11   11 11  11111  11                                 ";
	MenuMap[11][10] = "                         100000001111111111111111111111110000000            11    1  1  11                                        ";
	MenuMap[11][11] = "                           11100001111111111111111111111111100001           11   11  1  11        111                             ";
	MenuMap[11][12] = "                            100000011111111111111111111111110000111111111111111111111111111111111111                              ";
	MenuMap[11][13] = "                             11000000111111111111111111111110000110001110001110111011111111111110001                              ";
	MenuMap[11][14] = "                               11000001100000001111111111111000010001111101111111111111111111111101                               ";
	MenuMap[11][15] = "                                 1111000000000000000000000000000000001111011111111111111110110011                                 ";
	MenuMap[11][16] = "                                     1111111111111111111111  1  000001110001110000011111111111                                    ";
	MenuMap[11][17] = "                                                                11111111111                                                       ";

	MenuMap[12][0] = "                                          1111111111                                                                              ";
	MenuMap[12][1] = "                                             1000001     1111111111                                                               ";
	MenuMap[12][2] = "                                              11 11     110111101111                                                              ";
	MenuMap[12][3] = "             11111                        11111111111111111111111 111  1    1                                                     ";
	MenuMap[12][4] = "            11111111111111111111111111111111111111111111111 1111111111111111111                                                   ";
	MenuMap[12][5] = "                              11111111111111111111111111111 11111111111111111111111                                               ";
	MenuMap[12][6] = "                                111111111110011111111111111  111111111111111111111                                                ";
	MenuMap[12][7] = "                                111111111111111111111111111111111111111111111111111                                               ";
	MenuMap[12][8] = "                   11111  111   111111111111111111111111111111111111111111111111111                                               ";
	MenuMap[12][9] = "              11111111111  1111        11111111111111  11       11   11 11  11111  11                                             ";
	MenuMap[12][10] = "             100000001111111111111111111111110000000            11    1  1  11                                                    ";
	MenuMap[12][11] = "               11100001111111111111111111111111100001           11   11  1  11        111                                         ";
	MenuMap[12][12] = "                100000011111111111111111111111110000111111111111111111111111111111111111                                          ";
	MenuMap[12][13] = "                 11000000111111111111111111111110000110001110001110111011111111111110001                                          ";
	MenuMap[12][14] = "                   11000001100000001111111111111000010001111101111111111111111111111101                                           ";
	MenuMap[12][15] = "                     1111000000000000000000000000000000001111011111111111111110110011                                             ";
	MenuMap[12][16] = "                         1111111111111111111111  1  000001110001110000011111111111                                                ";
	MenuMap[12][17] = "                                                    11111111111                                                                   ";

	MenuMap[13][0] = "                           1111111111                                                                                             ";
	MenuMap[13][1] = "                              1000001     1111111111                                                                              ";
	MenuMap[13][2] = "                               11 11     110111101111                                                                             ";
	MenuMap[13][3] = "111                        11111111111111111111111 111  1    1                                                                    ";
	MenuMap[13][4] = "11111111111111111111111111111111111111111111 1111111111111111111                                                                  ";
	MenuMap[13][5] = "               11111111111111111111111111111 11111111111111111111111                                                              ";
	MenuMap[13][6] = "                 111111111110011111111111111  111111111111111111111                                                               ";
	MenuMap[13][7] = "                 111111111111111111111111111111111111111111111111111                                                              ";
	MenuMap[13][8] = "    11111  111   111111111111111111111111111111111111111111111111111                                                              ";
	MenuMap[13][9] = "1111111111  1111        11111111111111  11       11   11 11  11111  11                                                            ";
	MenuMap[13][10] = "0000001111111111111111111111110000000            11    1  1  11                                                                   ";
	MenuMap[13][11] = "11100001111111111111111111111111100001           11   11  1  11        111                                                        ";
	MenuMap[13][12] = " 100000011111111111111111111111110000111111111111111111111111111111111111                                                         ";
	MenuMap[13][13] = "  11000000111111111111111111111110000110001110001110111011111111111110001                                                         ";
	MenuMap[13][14] = "    11000001100000001111111111111000010001111101111111111111111111111101                                                          ";
	MenuMap[13][15] = "      1111000000000000000000000000000000001111011111111111111110110011                                                            ";
	MenuMap[13][16] = "          1111111111111111111111  1  000001110001110000011111111111                                                               ";
	MenuMap[13][17] = "                                     11111111111                                                                                  ";

	MenuMap[14][0] = "                   1111111111                                                                                                     ";
	MenuMap[14][1] = "                      1000001     1111111111                                                                                      ";
	MenuMap[14][2] = "                       11 11     110111101111                                                                                     ";
	MenuMap[14][3] = "                   11111111111111111111111 111  1    1                                                                            ";
	MenuMap[14][4] = "111111111111111111111111111111111111 1111111111111111111                                                                          ";
	MenuMap[14][5] = "       11111111111111111111111111111 11111111111111111111111                                                                      ";
	MenuMap[14][6] = "         111111111110011111111111111  111111111111111111111                                                                       ";
	MenuMap[14][7] = "         111111111111111111111111111111111111111111111111111                                                                      ";
	MenuMap[14][8] = "1  111   111111111111111111111111111111111111111111111111111                                                                      ";
	MenuMap[14][9] = "11  1111        11111111111111  11       11   11 11  11111  11                                                                    ";
	MenuMap[14][10] = "11111111111111111111110000000            11    1  1  11                                                                           ";
	MenuMap[14][11] = "111111111111111111111111100001           11   11  1  11        111                                                                ";
	MenuMap[14][12] = "11111111111111111111111110000111111111111111111111111111111111111                                                                 ";
	MenuMap[14][13] = "00111111111111111111111110000110001110001110111011111111111110001                                                                 ";
	MenuMap[14][14] = "0001100000001111111111111000010001111101111111111111111111111101                                                                  ";
	MenuMap[14][15] = "11000000000000000000000000000000001111011111111111111110110011                                                                    ";
	MenuMap[14][16] = "  1111111111111111111111  1  000001110001110000011111111111                                                                       ";
	MenuMap[14][17] = "                             11111111111                                                                                          ";

	MenuMap[15][0] = "           1111111111                                                                                                             ";
	MenuMap[15][1] = "              1000001     1111111111                                                                                              ";
	MenuMap[15][2] = "               11 11     110111101111                                                                                             ";
	MenuMap[15][3] = "           11111111111111111111111 111  1    1                                                                                    ";
	MenuMap[15][4] = "1111111111111111111111111111 1111111111111111111                                                                                  ";
	MenuMap[15][5] = "1111111111111111111111111111 11111111111111111111111                                                                              ";
	MenuMap[15][6] = " 111111111110011111111111111  111111111111111111111                                                                               ";
	MenuMap[15][7] = " 111111111111111111111111111111111111111111111111111                                                                              ";
	MenuMap[15][8] = " 111111111111111111111111111111111111111111111111111                                                                              ";
	MenuMap[15][9] = "        11111111111111  11       11   11 11  11111  11                                                                            ";
	MenuMap[15][10] = "111111111111110000000            11    1  1  11                                                                                  1";
	MenuMap[15][11] = "1111111111111111100001           11   11  1  11        111                                                                     111";
	MenuMap[15][12] = "111111111111111110000111111111111111111111111111111111111                                                                   111111";
	MenuMap[15][13] = "111111111111111110000110001110001110111011111111111110001                                                                   111100";
	MenuMap[15][14] = "00001111111111111000010001111101111111111111111111111101                                                                  11110001";
	MenuMap[15][15] = "000000000000000000000000001111011111111111111110110011                                                                     1110010";
	MenuMap[15][16] = "1111111111111111  1  000001110001110000011111111111                                                                          11000";
	MenuMap[15][17] = "                     11111111111                                                                                                10";

	MenuMap[16][0] = "   1111111111                                                                                                                     ";
	MenuMap[16][1] = "      1000001     1111111111                                                                                                      ";
	MenuMap[16][2] = "       11 11     110111101111                                                                                                     ";
	MenuMap[16][3] = "   11111111111111111111111 111  1    1                                                                                            ";
	MenuMap[16][4] = "11111111111111111111 1111111111111111111                                                                                          ";
	MenuMap[16][5] = "11111111111111111111 11111111111111111111111                                                                                      ";
	MenuMap[16][6] = "11110011111111111111  111111111111111111111                                                                                       ";
	MenuMap[16][7] = "11111111111111111111111111111111111111111111                                                                                      ";
	MenuMap[16][8] = "11111111111111111111111111111111111111111111                                                                                      ";
	MenuMap[16][9] = "11111111111111  11       11   11 11  11111  11                                                                            0       ";
	MenuMap[16][10] = "1111110000000            11    1  1  11                                                                                  1        ";
	MenuMap[16][11] = "11111111100001           11   11  1  11        111                                                                     11111111111";
	MenuMap[16][12] = "1111111110000111111111111111111111111111111111111                                                                   11111111111111";
	MenuMap[16][13] = "1111111110000110001110001110111011111111111110001                                                                   11110000000111";
	MenuMap[16][14] = "111111111000010001111101111111111111111111111101                                                                  1111000111110001";
	MenuMap[16][15] = "0000000000000000001111011111111111111110110011                                                                     111001001001100";
	MenuMap[16][16] = "11111111  1  000001110001110000011111111111                                                                          1100000100110";
	MenuMap[16][17] = "             11111111111                                                                                                101000110 ";

	MenuMap[17][0] = "11111                                                                                                                             ";
	MenuMap[17][1] = "00001     1111111111                                                                                                              ";
	MenuMap[17][2] = "1 11     110111101111                                                                                                             ";
	MenuMap[17][3] = "111111111111111111 111  1    1                                                                                                    ";
	MenuMap[17][4] = "111111111111 1111111111111111111                                                                                                  ";
	MenuMap[17][5] = "111111111111 11111111111111111111111                                                                                              ";
	MenuMap[17][6] = "111111111111  111111111111111111111                                                                                               ";
	MenuMap[17][7] = "111111111111111111111111111111111111                                                                                              ";
	MenuMap[17][8] = "111111111111111111111111111111111111                                                                                              ";
	MenuMap[17][9] = "111111  11       11   11 11  11111  11                                                                            0            111";
	MenuMap[17][10] = "00000            11    1  1  11                                                                                  1          111174";
	MenuMap[17][11] = "100001           11   11  1  11        111                                                                     1111111111111111111";
	MenuMap[17][12] = "10000111111111111111111111111111111111111                                                                   1111111111111111011111";
	MenuMap[17][13] = "10000110001110001110111011111111111110001                                                                   1111000000011111011111";
	MenuMap[17][14] = "1000010001111101111111111111111111111101                                                                  111100011111000111011111";
	MenuMap[17][15] = "00000000001111011111111111111110110011                                                                     11100100100110011111111";
	MenuMap[17][16] = "  1  000001110001110000011111111111                                                                          110000010011000111111";
	MenuMap[17][17] = "     11111111111                                                                                                101000110         ";

	MenuMap[18][0] = "                                                                                                                                  ";
	MenuMap[18][1] = "  1111111111                                                                                                                      ";
	MenuMap[18][2] = " 110111101111                                                                                                                     ";
	MenuMap[18][3] = "1111111111 111  1    1                                                                                                            ";
	MenuMap[18][4] = "1111 1111111111111111111                                                                                                          ";
	MenuMap[18][5] = "1111 11111111111111111111111                                                                                                      ";
	MenuMap[18][6] = "1111  111111111111111111111                                                                                                      -";
	MenuMap[18][7] = "1111111111111111111111111111                                                                                                      ";
	MenuMap[18][8] = "1111111111111111111111111111                                                                                                      ";
	MenuMap[18][9] = "11       11   11 11  11111  11                                                                            0            1111111   1";
	MenuMap[18][10] = "         11    1  1  11                                                                                  1          11117411111111";
	MenuMap[18][11] = "         11   11  1  11        111                                                                     111111111111111111111111110";
	MenuMap[18][12] = "111111111111111111111111111111111                                                                   111111111111111101111111111110";
	MenuMap[18][13] = "001110001110111011111111111110001                                                                   111100000001111101111111111110";
	MenuMap[18][14] = "01111101111111111111111111111101                                                                  11110001111100011101111111111110";
	MenuMap[18][15] = "001111011111111111111110110011                                                                     1110010010011001111111111111110";
	MenuMap[18][16] = "001110001110000011111111111                                                                          11000001001100011111111111111";
	MenuMap[18][17] = "11111111                                                                                                101000110                 ";

	MenuMap[19][0] = "                                                                                                                                  ";
	MenuMap[19][1] = "  1111111111                                                                                                                      ";
	MenuMap[19][2] = " 110111101111                                                                                                                     ";
	MenuMap[19][3] = "1111111111 111  1    1                                                                                                            ";
	MenuMap[19][4] = "1111 1111111111111111111                                                                                                          ";
	MenuMap[19][5] = "1111 11111111111111111111111                                                                                                      ";
	MenuMap[19][6] = "1111  111111111111111111111                                                                                                      -";
	MenuMap[19][7] = "1111111111111111111111111111                                                                                                      ";
	MenuMap[19][8] = "1111111111111111111111111111                                                                                                      ";
	MenuMap[19][9] = "11       11   11 11  11111  11                                                                            0            1111111   1";
	MenuMap[19][10] = "         11    1  1  11                                                                                  1          11117411111111";
	MenuMap[19][11] = "         11   11  1  11        111                                                                     111111111111111111111111110";
	MenuMap[19][12] = "111111111111111111111111111111111                                                                   111111111111111101111111111110";
	MenuMap[19][13] = "001110001110111011111111111110001                                                                   111100000001111101111111111110";
	MenuMap[19][14] = "01111101111111111111111111111101                                                                  11110001111100011101111111111110";
	MenuMap[19][15] = "001111011111111111111110110011                                                                     1110010010011001111111111111110";
	MenuMap[19][16] = "001110001110000011111111111                                                                          11000001001100011111111111111";
	MenuMap[19][17] = "11111111                                                                                                101000110                 ";

	MenuMap[20][0] = "                                                                                                                                  ";
	MenuMap[20][1] = "1111                                                                                                                              ";
	MenuMap[20][2] = "01111                                                                                                                             ";
	MenuMap[20][3] = "11 111  1    1                                                                                                                    ";
	MenuMap[20][4] = "1111111111111111                                                                                                                  ";
	MenuMap[20][5] = "11111111111111111111                                                                                                              ";
	MenuMap[20][6] = "1111111111111111111                                                                                                      -----1111";
	MenuMap[20][7] = "11111111111111111111                                                                                                          1101";
	MenuMap[20][8] = "11111111111111111111                                                                                                      11111111";
	MenuMap[20][9] = " 11   11 11  11111  11                                                                            0            1111111   1111111  ";
	MenuMap[20][10] = " 11    1  1  11                                                                                  1          1111741111111111111111";
	MenuMap[20][11] = " 11   11  1  11        111                                                                     11111111111111111111111111011111111";
	MenuMap[20][12] = "1111111111111111111111111                                                                   11111111111111110111111111111011111111";
	MenuMap[20][13] = "1110111011111111111110001                                                                   11110000000111110111111111111011111111";
	MenuMap[20][14] = "111111111111111111111101                                                                  1111000111110001110111111111111011111111";
	MenuMap[20][15] = "1111111111111110110011                                                                     111001001001100111111111111111011111111";
	MenuMap[20][16] = "1110000011111111111                                                                          1100000100110001111111111111111111111";
	MenuMap[20][17] = "                                                                                                101000110                         ";

	MenuMap[21][0] = "                                                                                                                                  ";
	MenuMap[21][1] = "                                                                                                                                  ";
	MenuMap[21][2] = "                                                                                                                                  ";
	MenuMap[21][3] = "1    1                                                                                                                            ";
	MenuMap[21][4] = "11111111                                                                                                                          ";
	MenuMap[21][5] = "111111111111                                                                                                                      ";
	MenuMap[21][6] = "11111111111                                                                                                      -----111111111111";
	MenuMap[21][7] = "111111111111                                                                                                          110111111111";
	MenuMap[21][8] = "111111111111                                                                                                      1111111111111111";
	MenuMap[21][9] = " 11  11111  11                                                                            0            1111111   1111111  11111111";
	MenuMap[21][10] = "  1  11                                                                                  1          1111741111111111111111111111  ";
	MenuMap[21][11] = "  1  11        111                                                                     11111111111111111111111111011111111111111 1";
	MenuMap[21][12] = "11111111111111111                                                                   1111111111111111011111111111101111111111111111";
	MenuMap[21][13] = "11111111111110001                                                                   1111000000011111011111111111101111111111111111";
	MenuMap[21][14] = "1111111111111101                                                                  111100011111000111011111111111101111111111111001";
	MenuMap[21][15] = "11111110110011                                                                     11100100100110011111111111111101111111111100011";
	MenuMap[21][16] = "11111111111                                                                          110000010011000111111111111111111111111100011";
	MenuMap[21][17] = "                                                                                        101000110                             0011";

	MenuMap[22][0] = "                                                                                                                                  ";
	MenuMap[22][1] = "                                                                                                                                  ";
	MenuMap[22][2] = "                                                                                                                                  ";
	MenuMap[22][3] = "                                                                                                                                  ";
	MenuMap[22][4] = "                                                                                                                                  ";
	MenuMap[22][5] = "1111                                                                                                                              ";
	MenuMap[22][6] = "111                                                                                                      -----11111111111111      ";
	MenuMap[22][7] = "1111                                                                                                          1101111111111       ";
	MenuMap[22][8] = "1111                                                                                                      111111111111111111111111";
	MenuMap[22][9] = "11  11                                                                            0            1111111   1111111  111111111       ";
	MenuMap[22][10] = "                                                                                 1          1111741111111111111111111111  11111101";
	MenuMap[22][11] = "       111                                                                     11111111111111111111111111011111111111111 11    111";
	MenuMap[22][12] = "111111111                                                                   111111111111111101111111111110111111111111111111111111";
	MenuMap[22][13] = "111110001                                                                   111100000001111101111111111110111111111111111111100011";
	MenuMap[22][14] = "11111101                                                                  11110001111100011101111111111110111111111111100111111000";
	MenuMap[22][15] = "110011                                                                     1110010010011001111111111111110111111111110001110100110";
	MenuMap[22][16] = "111                                                                          11000001001100011111111111111111111111110001100000011";
	MenuMap[22][17] = "                                                                                101000110                             00110110001 ";

	MenuMap[23][0] = "                                                                                                                                  ";
	MenuMap[23][1] = "                                                                                                                                  ";
	MenuMap[23][2] = "                                                                                                                                  ";
	MenuMap[23][3] = "                                                                                                                                  ";
	MenuMap[23][4] = "                                                                                                                                  ";
	MenuMap[23][5] = "                                                                                                                             1    ";
	MenuMap[23][6] = "                                                                                                 -----11111111111111         1    ";
	MenuMap[23][7] = "                                                                                                      1101111111111          1    ";
	MenuMap[23][8] = "                                                                                                  1111111111111111111111111  1    ";
	MenuMap[23][9] = "                                                                          0            1111111   1111111  111111111      1   1    ";
	MenuMap[23][10] = "                                                                         1          1111741111111111111111111111  1111110111111111";
	MenuMap[23][11] = "11                                                                     11111111111111111111111111011111111111111 11    11111111111";
	MenuMap[23][12] = "1                                                                   11111111111111110111111111111011111111111111111111111111111000";
	MenuMap[23][13] = "1                                                                   11110000000111110111111111111011111111111111111110001111111000";
	MenuMap[23][14] = "                                                                  1111000111110001110111111111111011111111111110011111100011111111";
	MenuMap[23][15] = "                                                                   111001001001100111111111111111011111111111000111010011011111   ";
	MenuMap[23][16] = "                                                                     110000010011000111111111111111111111111100011000000111       ";
	MenuMap[23][17] = "                                                                        101000110                             00110110001         ";

	MenuMap[24][0] = "                                                                                                                                  ";
	MenuMap[24][1] = "                                                                                                                                  ";
	MenuMap[24][2] = "                                                                                                                                  ";
	MenuMap[24][3] = "                                                                                                                                  ";
	MenuMap[24][4] = "                                                                                                                                  ";
	MenuMap[24][5] = "                                                                                                           1                      ";
	MenuMap[24][6] = "                                                                               -----11111111111111         1                      ";
	MenuMap[24][7] = "                                                                                    1101111111111          1                      ";
	MenuMap[24][8] = "                                                                                1111111111111111111111111  1                      ";
	MenuMap[24][9] = "                                                        0            1111111   1111111  111111111      1   1                      ";
	MenuMap[24][10] = "                                                       1          1111741111111111111111111111  11111101111111111                 ";
	MenuMap[24][11] = "                                                     11111111111111111111111111011111111111111 11    111111111111                 ";
	MenuMap[24][12] = "                                                  111111111111111101111111111110111111111111111111111111111110000                 ";
	MenuMap[24][13] = "                                                  111100000001111101111111111110111111111111111111100011111110001                 ";
	MenuMap[24][14] = "                                                11110001111100011101111111111110111111111111100111111000111111111                 ";
	MenuMap[24][15] = "                                                 111001001001100111111111111111011111111111000111010011011111                     ";
	MenuMap[24][16] = "                                                   110000010011000111111111111111111111111100011000000111                         ";
	MenuMap[24][17] = "                                                      101000110                             00110110001                           ";

	MenuMap[25][0] = "                                                                                                                                  ";
	MenuMap[25][1] = "                                                                                                                                  ";
	MenuMap[25][2] = "                                                                                                                                  ";
	MenuMap[25][3] = "                                                                                                                                  ";
	MenuMap[25][4] = "                                                                                                                                  ";
	MenuMap[25][5] = "                                                                                        1                                         ";
	MenuMap[25][6] = "                                                            -----11111111111111         1                                         ";
	MenuMap[25][7] = "                                                                 1101111111111          1                                         ";
	MenuMap[25][8] = "                                                             1111111111111111111111111  1                                         ";
	MenuMap[25][9] = "                                     0            1111111   1111111  111111111      1   1                                         ";
	MenuMap[25][10] = "                                    1          1111741111111111111111111111  11111101111111111                                    ";
	MenuMap[25][11] = "                                  11111111111111111111111111011111111111111 11    111111111111                                    ";
	MenuMap[25][12] = "                               1111111111111111011111111111101111111111111111111111111111100001                                   ";
	MenuMap[25][13] = "                               111100000001111101111111111110111111111111111111100011111110001                                    ";
	MenuMap[25][14] = "                             11110001111100011101111111111110111111111111100111111000111111111                                    ";
	MenuMap[25][15] = "                              111001001001100111111111111111011111111111000111010011011111                                        ";
	MenuMap[25][16] = "                                110000010011000111111111111111111111111100011000000111                                            ";
	MenuMap[25][17] = "                                   101000110                             00110110001                                              ";

	MenuMap[26][0] = "                                                                                                                                  ";
	MenuMap[26][1] = "                                                                                                                                  ";
	MenuMap[26][2] = "                                                                                                                                  ";
	MenuMap[26][3] = "                                                                                                                                  ";
	MenuMap[26][4] = "                                                                                                                                  ";
	MenuMap[26][5] = "                                                                             1                                                    ";
	MenuMap[26][6] = "                                                 -----11111111111111         1                                                    ";
	MenuMap[26][7] = "                                                      1101111111111          1                                                    ";
	MenuMap[26][8] = "                                                  1111111111111111111111111  1                                                    ";
	MenuMap[26][9] = "                          0            1111111   1111111  111111111      1   1                                                    ";
	MenuMap[26][10] = "                         1          1111741111111111111111111111  11111101111111111                                               ";
	MenuMap[26][11] = "                       11111111111111111111111111011111111111111 11    111111111111                                               ";
	MenuMap[26][12] = "                    1111111111111111011111111111101111111111111111111111111111100001                                              ";
	MenuMap[26][13] = "                    111100000001111101111111111110111111111111111111100011111110001                                               ";
	MenuMap[26][14] = "                  11110001111100011101111111111110111111111111100111111000111111111                                               ";
	MenuMap[26][15] = "                   111001001001100111111111111111011111111111000111010011011111                                                   ";
	MenuMap[26][16] = "                     110000010011000111111111111111111111111100011000000111                                                       ";
	MenuMap[26][17] = "                        101000110                             00110110001                                                         ";

	MenuMap[27][0] = "                                                                                                                                  ";
	MenuMap[27][1] = "                                                                                                                                  ";
	MenuMap[27][2] = "                                                                                                                                  ";
	MenuMap[27][3] = "                                                                                                                                  ";
	MenuMap[27][4] = "                                                                                                                                  ";
	MenuMap[27][5] = "                                                     1                                                                            ";
	MenuMap[27][6] = "                         -----11111111111111         1                                                                            ";
	MenuMap[27][7] = "                              1101111111111          1                                                                            ";
	MenuMap[27][8] = "                          1111111111111111111111111  1                                                                            ";
	MenuMap[27][9] = "  0            1111111   1111111  111111111      1   1                                                                            ";
	MenuMap[27][10] = " 1          1111741111111111111111111111  11111101111111111                                                                       ";
	MenuMap[27][11] = "1111111111111111111111111011111111111111 11    111111111111                                                                       ";
	MenuMap[27][12] = "111111111111011111111111101111111111111111111111111111100001                                                                      ";
	MenuMap[27][13] = "00000001111101111111111110111111111111111111100011111110001                                                                       ";
	MenuMap[27][14] = "01111100011101111111111110111111111111100111111000111111111                                                                       ";
	MenuMap[27][15] = "1001001100111111111111111011111111111000111010011011111                                                                           ";
	MenuMap[27][16] = "000010011000111111111111111111111111100011000000111                                                                               ";
	MenuMap[27][17] = "101000110                             00110110001                                                                                 ";

	MenuMap[28][0] = "                                                                                                                                  ";
	MenuMap[28][1] = "                                                                                                                                  ";
	MenuMap[28][2] = "                                                                                                                                  ";
	MenuMap[28][3] = "                                                                                                                                  ";
	MenuMap[28][4] = "                                                                                                                                  ";
	MenuMap[28][5] = "                                             1                                                                                    ";
	MenuMap[28][6] = "                 -----11111111111111         1                                                                                    ";
	MenuMap[28][7] = "                      1101111111111          1                                                                                    ";
	MenuMap[28][8] = "                  1111111111111111111111111  1                                                                                    ";
	MenuMap[28][9] = "       1111111   1111111  111111111      1   1                                                                                    ";
	MenuMap[28][10] = "    1111741111111111111111111111  11111101111111111                                                                               ";
	MenuMap[28][11] = "11111111111111111011111111111111 11    111111111111                                                                               ";
	MenuMap[28][12] = "1111011111111111101111111111111111111111111111100001                                                                              ";
	MenuMap[28][13] = "111101111111111110111111111111111111100011111110001                                                                               ";
	MenuMap[28][14] = "011101111111111110111111111111100111111000111111111                                                                               ";
	MenuMap[28][15] = "00111111111111111011111111111000111010011011111                                                                                   ";
	MenuMap[28][16] = "1000111111111111111111111111100011000000111                                                                                       ";
	MenuMap[28][17] = "0                             00110110001                                                                                         ";

	MenuMap[29][0] = "                                                                                                                                  ";
	MenuMap[29][1] = "                                                                                                                                  ";
	MenuMap[29][2] = "                                                                                                                                  ";
	MenuMap[29][3] = "                                                                                                                                  ";
	MenuMap[29][4] = "                                                                                                                                  ";
	MenuMap[29][5] = "                                     1                                                                                            ";
	MenuMap[29][6] = "         -----11111111111111         1                                                                                            ";
	MenuMap[29][7] = "              1101111111111          1                                                                                            ";
	MenuMap[29][8] = "          1111111111111111111111111  1                                                                                            ";
	MenuMap[29][9] = "111111   1111111  111111111      1   1                                                                                            ";
	MenuMap[29][10] = "741111111111111111111111  11111101111111111                                                                                       ";
	MenuMap[29][11] = "111111111011111111111111 11    111111111111                                                                                       ";
	MenuMap[29][12] = "11111111101111111111111111111111111111100001                                                                                      ";
	MenuMap[29][13] = "1111111110111111111111111111100011111110001                                                                                       ";
	MenuMap[29][14] = "1111111110111111111111100111111000111111111                                                                                       ";
	MenuMap[29][15] = "111111111011111111111000111010011011111                                                                                           ";
	MenuMap[29][16] = "11111111111111111111100011000000111                                                                                               ";
	MenuMap[29][17] = "                      00110110001                                                                                                 ";

	MenuMap[30][0] = "                                                                                                                                  ";
	MenuMap[30][1] = "                                                                                                                                  ";
	MenuMap[30][2] = "                                                                                                                                  ";
	MenuMap[30][3] = "                                                                                                                                  ";
	MenuMap[30][4] = "                                                                                                                                  ";
	MenuMap[30][5] = "                             1                                                                                                    ";
	MenuMap[30][6] = " -----11111111111111         1                                                                                                    ";
	MenuMap[30][7] = "      1101111111111          1                                                                                                    ";
	MenuMap[30][8] = "  1111111111111111111111111  1                                                                                                    ";
	MenuMap[30][9] = " 1111111  111111111      1   1                                                                                                    ";
	MenuMap[30][10] = "1111111111111111  11111101111111111                                                                                               ";
	MenuMap[30][11] = "1011111111111111 11    111111111111                                                                                               ";
	MenuMap[30][12] = "101111111111111111111111111111100001                                                                                              ";
	MenuMap[30][13] = "10111111111111111111100011111110001                                                                                               ";
	MenuMap[30][14] = "10111111111111100111111000111111111                                                                                               ";
	MenuMap[30][15] = "1011111111111000111010011011111                                                                                                   ";
	MenuMap[30][16] = "111111111111100011000000111                                                                                                       ";
	MenuMap[30][17] = "              00110110001                                                                                                         ";

	MenuMap[31][0] = "                                                                                                                                  ";
	MenuMap[31][1] = "                                                                                                                                  ";
	MenuMap[31][2] = "                                                                                                                                  ";
	MenuMap[31][3] = "                                                                                                                                  ";
	MenuMap[31][4] = "                                                                                                                                  ";
	MenuMap[31][5] = "                     1                                                                                                            ";
	MenuMap[31][6] = "111111111111         1                                                                                                            ";
	MenuMap[31][7] = "01111111111          1                                                                                                            ";
	MenuMap[31][8] = "1111111111111111111  1                                                                                                            ";
	MenuMap[31][9] = "  111111111      1   1                                                                                                            ";
	MenuMap[31][10] = "11111111  11111101111111111                                                                                                       ";
	MenuMap[31][11] = "11111111 11    111111111111                                                                                                       ";
	MenuMap[31][12] = "1111111111111111111111100001                                                                                                      ";
	MenuMap[31][13] = "111111111111100011111110001                                                                                                       ";
	MenuMap[31][14] = "111111100111111000111111111                                                                                                       ";
	MenuMap[31][15] = "11111000111010011011111                                                                                                           ";
	MenuMap[31][16] = "1111100011000000111                                                                                                               ";
	MenuMap[31][17] = "      00110110001                                                                                                                 ";

	MenuMap[32][0] = "                                                                                                                                  ";
	MenuMap[32][1] = "                                                                                                                                  ";
	MenuMap[32][2] = "                                                                                                                                  ";
	MenuMap[32][3] = "                                                                                                                                  ";
	MenuMap[32][4] = "                                                                                                                                  ";
	MenuMap[32][5] = "             1                                                                                                                    ";
	MenuMap[32][6] = "1111         1                                                                                                                    ";
	MenuMap[32][7] = "111          1                                                                                                                    ";
	MenuMap[32][8] = "11111111111  1                                                                                                                    ";
	MenuMap[32][9] = "111      1   1                                                                                                                    ";
	MenuMap[32][10] = "  11111101111111111                                                                                                               ";
	MenuMap[32][11] = " 11    111111111111                                                                                                               ";
	MenuMap[32][12] = "11111111111111100001                                                                                                              ";
	MenuMap[32][13] = "1111100011111110001                                                                                                               ";
	MenuMap[32][14] = "0111111000111111111                                                                                                               ";
	MenuMap[32][15] = "111010011011111                                                                                                                   ";
	MenuMap[32][16] = "11000000111                                                                                                                       ";
	MenuMap[32][17] = "110110001                                                                                                                         ";

	MenuMap[33][0] = "                                                                                                                                  ";
	MenuMap[33][1] = "                                                                                                                                  ";
	MenuMap[33][2] = "                                                                                                                                  ";
	MenuMap[33][3] = "                                                                                                                                  ";
	MenuMap[33][4] = "                                                                                                                                  ";
	MenuMap[33][5] = "     1                                                                                                                            ";
	MenuMap[33][6] = "     1                                                                                                                            ";
	MenuMap[33][7] = "     1                                                                                                                            ";
	MenuMap[33][8] = "111  1                                                                                                                            ";
	MenuMap[33][9] = " 1   1                                                                                                                            ";
	MenuMap[33][10] = "01111111111                                                                                                                       ";
	MenuMap[33][11] = "11111111111                                                                                                                       ";
	MenuMap[33][12] = "111111100001                                                                                                                      ";
	MenuMap[33][13] = "11111110001                                                                                                                       ";
	MenuMap[33][14] = "00111111111                                                                                                                       ";
	MenuMap[33][15] = "1011111                                                                                                                           ";
	MenuMap[33][16] = "111                                                                                                                               ";
	MenuMap[33][17] = "1                                                                                                                                 ";

	MenuMap[34][0] = "                                                                                                                                  ";
	MenuMap[34][1] = "                                                                                                                                  ";
	MenuMap[34][2] = "                                                                                                                                  ";
	MenuMap[34][3] = "                                                                                                                                  ";
	MenuMap[34][4] = "                                                                                                                                  ";
	MenuMap[34][5] = "                                                                                                                                  ";
	MenuMap[34][6] = "                                                                                                                                  ";
	MenuMap[34][7] = "                                                                                                                                  ";
	MenuMap[34][8] = "                                                                                                                                  ";
	MenuMap[34][9] = "                                                                                                                                  ";
	MenuMap[34][10] = "111                                                                                                                               ";
	MenuMap[34][11] = "111                                                                                                                               ";
	MenuMap[34][12] = "0001                                                                                                                              ";
	MenuMap[34][13] = "001                                                                                                                               ";
	MenuMap[34][14] = "111                                                                                                                               ";
	MenuMap[34][15] = "                                                                                                                                  ";
	MenuMap[34][16] = "                                                                                                                                  ";
	MenuMap[34][17] = "                                                                                                                                  ";



}
void MenuProgress()
{
	int LogoPage = 0;
	int next = 0;
	int menuNum = 1;
	MenuInitialize();
	while (true)
	{
		if (menuNum == 1 && GetAsyncKeyState(VK_RIGHT)) { menuNum = 2; }
		if (menuNum == 2 && GetAsyncKeyState(VK_LEFT)) { menuNum = 1; }
		if (menuNum == 1 && GetAsyncKeyState(VK_RETURN)) { menu = STAGE1; break; }
		if (menuNum == 2 && GetAsyncKeyState(VK_RETURN)) { menu = EXIT; break; }
		MenuRender(menuNum, LogoPage);
		FlipBuffer();
		ClearBuffer();
		Sleep(MenuDelay);
	}
	MenuRelease();
}
void MenuRender(int Num, int &LogoPage)
{
	if (Num == 1)
	{
		WriteBuffer(19, 40, "��[����]", RED);
		WriteBuffer(40, 40, "[����]", WHITE);
	}
	if (Num == 2)
	{
		WriteBuffer(20, 40, "[����]", WHITE);
		WriteBuffer(39, 40, "��[����]", RED);
	}
	for (int i = 0; i < 6; i++)
	{
		WriteBuffer(1, 5 + i, MenuTitle[i], WHITE);
	}
	for (int i = 0; i < MenuSize; i++)
	{
		WriteBuffer(0, 15 + i, MenuMap[LogoPage][i], WHITE);
		if (LogoPage >= 34) { LogoPage = 0; }
	}
	LogoPage++;

}
void MenuRelease()
{
	for (int i = 0; i < MenuTitleSize; i++)
	{
		MenuTitle[i] = nullptr;
	}
}
#pragma endregion

#pragma region Stage1
void Stage1_progress()
{
	switch (stage)
	{
	case EXIT_STAGE:
		break;
	case STAGE1_1:
		Stage1_1();
		break;
	//case STAGE1_2:
	//	Stage1_2();
	//	break;
	//case STAGE1_3:
	//	Stage1_3();
	//	break;
	//case STAGE1_4:
	//	Stage1_4();
	//	break;
	default:
		break;
	}
}
void Stage1_1()
{
	PlayerInit(5, 22);
	EnemyInit(pMap1_1);
	while (true)
	{
		PlayerProgress(pMap1_1);
		PlayerBulletProgress(pMap1_1);
		EnemyHpDownEffect();
		EnemyPorogress(pMap1_1);
		EnemyBulletProgress(pMap1_1);
		PlayerHpDownEffect();
		MapRender(pMap1_1);
		PlayerRender();
		GunUI_Rander();
		EnemyRander();

		FlipBuffer();
		ClearBuffer();
		Sleep(20);
	}
}
void Stage1_2()
{

}
void Stage1_3()
{

}
void Stage1_4()
{

}
#pragma endregion

#pragma region Player
void PlayerInit(int x, int y)
{
	player = (Player*)malloc(sizeof(Player));
	player->x = x;
	player->y = y;
	player->hp = 10;
	player->color = WHITE;

	//�������� �����ȣ
	player->weaponNum = PISTOL;

	//�Ѿ� �⺻����
	player->bulletNum[RIFLE] = 100;
	player->bulletNum[BOMB] = 10;

	player->isJump = false;
	player->isfloat = false;
	player->direction = RIGHT;

	//�߻� �����ð�
	player->bulletDelay[PISTOL][MAX_TIME] = 5;
	player->bulletDelay[PISTOL][NOW_TIME] = 0;

	player->bulletDelay[RIFLE][MAX_TIME] = 2;
	player->bulletDelay[RIFLE][NOW_TIME] = 0;

	player->bulletDelay[BOMB][MAX_TIME] = 20;
	player->bulletDelay[BOMB][NOW_TIME] = 0;

	//Hp
	player->isDownHp = false;
	player->downHpDelay[MAX_TIME] = 5;
	player->downHpDelay[NOW_TIME] = 0;

	//����
	player->moveDriction = STAND;
	player->h = player->y;
#pragma region SHAPE
	player->shape[RIGHT][0] = "  O";
	player->shape[RIGHT][1] = " (|o";
	player->shape[RIGHT][2] = "  ^";
	player->shape[RIGHT][3] = " - -";

	player->shape[R_UP][0] = "  Oo";
	player->shape[R_UP][1] = " (|��";
	player->shape[R_UP][2] = "  ^ ";
	player->shape[R_UP][3] = " - -";

	player->shape[UP][0] = " oOo";
	player->shape[UP][1] = " (|)";
	player->shape[UP][2] = "  ^ ";
	player->shape[UP][3] = " - -";

	player->shape[L_UP][0] = " oO";
	player->shape[L_UP][1] = "  |)";
	player->shape[L_UP][2] = "  ^";
	player->shape[L_UP][3] = " - -";

	player->shape[LEFT][0] = "  O ";
	player->shape[LEFT][1] = " o|)";
	player->shape[LEFT][2] = "  ^ ";
	player->shape[LEFT][3] = " - -";

	player->shape[L_DOWN][0] = "  O";
	player->shape[L_DOWN][1] = " o|)";
	player->shape[L_DOWN][2] = "  ^ ";
	player->shape[L_DOWN][3] = " - - ";

	player->shape[DOWN][0] = "  O ";
	player->shape[DOWN][1] = " o|o";
	player->shape[DOWN][2] = "  ^ ";
	player->shape[DOWN][3] = " - -";

	player->shape[R_DOWN][0] = "  O";
	player->shape[R_DOWN][1] = " (|o";
	player->shape[R_DOWN][2] = "  ^ ";
	player->shape[R_DOWN][3] = " - -";

	player->die = "��<";

	player->Weaphone[LEFT][0] = "��";
	player->Weaphone[RIGHT][0] = "����";
	player->Weaphone[UP][0] = "|";
	player->Weaphone[DOWN][0] = "|";
	player->Weaphone[R_UP][0] = "/";
	player->Weaphone[L_UP][0] = "\\";
	player->Weaphone[L_DOWN][0] = "/";
	player->Weaphone[R_DOWN][0] = "\\";

	player->Weaphone[LEFT][1] = "������";
	player->Weaphone[RIGHT][1] = "������";
	player->Weaphone[UP][1] = "��";
	player->Weaphone[DOWN][1] = "��";
	player->Weaphone[R_UP][1] = "/";
	player->Weaphone[L_UP][1] = "\\";
	player->Weaphone[L_DOWN][1] = "/";
	player->Weaphone[R_DOWN][1] = "\\";

#pragma endregion
}
void PlayerProgress(int(*Map)[MapX])
{
	player->bulletDelay[PISTOL][NOW_TIME]++;
	player->bulletDelay[RIFLE][NOW_TIME]++;
	player->bulletDelay[BOMB][NOW_TIME]++;

	if (GetAsyncKeyState(VK_LEFT) && Map[player->y][player->x - 1] < 5 && Map[player->y - 1][player->x] < 5 && Map[player->y - 2][player->x] < 5 && Map[player->y - 3][player->x] < 5)
	{
		player->x--;
		player->direction = LEFT;
		player->moveDriction = LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT) && Map[player->y][player->x + 2] < 5 && Map[player->y - 1][player->x + 1] < 5 && Map[player->y - 2][player->x + 1] < 5)
	{
		player->x++;
		player->direction = RIGHT;
		player->moveDriction = RIGHT;
	}
	if (GetAsyncKeyState(VK_UP))
	{
		player->direction = UP;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		player->direction = DOWN;
	}

	if (GetAsyncKeyState(0x31))//KeyPad1
	{
		player->weaponNum = PISTOL;
	}
	if (GetAsyncKeyState(0x32) && player->bulletNum[RIFLE] > 0)//KeyPad2
	{
		player->weaponNum = RIFLE;
	}
	if (GetAsyncKeyState(0x33) && player->bulletNum[BOMB] > 0)//KeyPad3
	{
		player->weaponNum = BOMB;
	}
	if (GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_UP)) { player->direction = R_UP; }
	if (GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_DOWN)) { player->direction = R_DOWN; }
	if (GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_UP)) { player->direction = L_UP; }
	if (GetAsyncKeyState(VK_LEFT) && GetAsyncKeyState(VK_DOWN)) { player->direction = L_DOWN; }
	if (GetAsyncKeyState(0x41))
	{
		switch (player->weaponNum)
		{
		case PISTOL:
			if (player->bulletDelay[PISTOL][MAX_TIME] <= player->bulletDelay[PISTOL][NOW_TIME])
			{
				PlayerBulletInit(PistolSpeed, 1, PISTOL, Map);
				player->bulletDelay[PISTOL][NOW_TIME] = 0;
			}

			break;
		case RIFLE:
			if (player->bulletDelay[RIFLE][MAX_TIME] <= player->bulletDelay[RIFLE][NOW_TIME])
			{
				PlayerBulletInit(RifleSpeed, 3, RIFLE, Map);
				player->bulletDelay[RIFLE][NOW_TIME] = 0;
				player->bulletNum[RIFLE]--;
			}
			if (player->bulletNum[RIFLE] == 0) { player->weaponNum = PISTOL; }
			break;
		case BOMB:
			if (player->bulletDelay[BOMB][MAX_TIME] <= player->bulletDelay[BOMB][NOW_TIME])
			{
				//PlayerBombInit();
				player->bulletNum[BOMB]--;
				player->bulletDelay[BOMB][NOW_TIME] = 0;
			}
			if (player->bulletNum[1] == 0) { player->weaponNum = PISTOL; }
		default:
			break;
		}

	}



	if (GetAsyncKeyState(VK_RIGHT) && player->isJump) { player->moveDriction = R_UP; }
	if (GetAsyncKeyState(VK_RIGHT) && player->isfloat) { player->moveDriction = R_DOWN; }
	if (GetAsyncKeyState(VK_LEFT) && player->isJump) { player->moveDriction = L_UP; }
	if (GetAsyncKeyState(VK_LEFT) && player->isfloat) { player->moveDriction = L_DOWN; }
	if (player->isJump) { player->moveDriction = UP; }
	if (player->isfloat) { player->moveDriction = DOWN; }

	if (GetAsyncKeyState(VK_SPACE) && !player->isJump && jumpTime > 5)
	{
		player->isJump = true; time = 0.f; player->h = player->y + PlayerSizeY;
	}

	if (!(GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT) || player->isJump || player->isfloat))
	{
		player->moveDriction = STAND;
	}
	PlayerGravity(Map);
}
void PlayerRender()
{
	int showGunX = 0;
	int showGunY = 0;

	for (int i = 0; i < player->hp; i++)
	{
		if (player->color == WHITE)
		{
			WriteBuffer(1 + i, 1, "��", RED);
		}
		else
		{
			WriteBuffer(1 + i, 1, "��", WHITE);
		}

	}

	for (int i = 0; i < PlayerSizeY; i++)
	{
		WriteBuffer(player->x, player->y - i, player->shape[player->direction][PlayerSizeY - i - 1], player->color);
	}
	switch (player->direction)
	{
	case RIGHT:
		showGunX = 2;
		showGunY = -2;
		break;
	case R_UP:
		showGunX = 2;
		showGunY = -3;
		break;
	case UP:
		showGunX = 1;
		showGunY = -4;
		break;
	case L_UP:
		showGunY = -3;
		break;
	case LEFT:
		if (player->weaponNum == RIFLE)
		{
			showGunX = -1;
		}
		showGunY = -2;
		break;
	case L_DOWN:
		showGunY = -1;
		break;
	case DOWN:
		showGunX = 1;
		break;
	case R_DOWN:
		showGunX = 2;
		showGunY = -1;
		break;
	default:
		break;
	}
	WriteBuffer(player->x + showGunX, player->y + showGunY, player->Weaphone[player->direction][player->weaponNum], CYAN);

}
void PlayerRelease() {
	free(player);
	player = nullptr;
}
void PlayerHpDownEffect()
{
	if (player->isDownHp)
	{
		player->color = RED;
		player->downHpDelay[NOW_TIME]++;
		if (player->downHpDelay[NOW_TIME] >= player->downHpDelay[MAX_TIME])
		{
			player->isDownHp = false;
			player->downHpDelay[NOW_TIME] = 0;
			player->color = WHITE;
		}
	}
}
void PlayerReplace(int x, int y)
{
	player->x = x;
	player->y = y;
}
void PlayerKnifeAttack()
{
	for (int i = 0; i < EnemyCount; i++)
	{
		if (enemy[i] != nullptr)
		{
			for (int j = 0; j < 3; j++)
			{
				if (enemy[i]->x == player->x + j && enemy[i]->y == player->y || enemy[i]->x == player->x - j && enemy[i]->y == player->y)
				{
					WriteBuffer(player->x, player->y + 2, "[����S]", LIGHTCYAN);
					if (GetAsyncKeyState(0x53))
					{
						enemy[i]->hp = 0;
					}
				}
			}
		}
	}
}
#pragma endregion

#pragma region Physics
void PlayerGravity(int(*Map)[MapX])
{
	jumpTime++;
	if (player->isJump)
	{
		int pos1 = player->y;
		time += 0.2f;
		player->y = player->h - V * time + 0.5f * G * time * time;
		int pos2 = player->y;

		int gab = pos2 - pos1;
		if (gab > 0)
		{
			for (int i = 0; i < gab; i++)
			{
				if (Map[pos1 + i][player->x] > 4 || Map[pos1 + i][player->x + 1] > 4|| Map[pos1 + i][player->x + 2] > 4)
				{
					player->y = pos1 + i - 1;
					player->isJump = false;
					break;
				}
			}
		}
		if (gab < 0)
		{
			for (int i = 0; i < gab * -1; i++)
			{
				if ( Map[pos1 - i - 3][player->x + 1] > 4)
				{
					player->y = pos1 - i - 1;
					player->isJump = false;
					break;
				}
			}
		}
	}
	if (!player->isJump && Map[player->y + 1][player->x] < 4 && Map[player->y + 1][player->x + 1] < 4)
	{
		player->isfloat = true;
		time = 0.f;
		player->h = player->y;

	}
	if (player->isfloat)
	{
		
		int p1 = player->y;
		time += 0.2f;
		player->y = player->h + V * time + 0.5f * G * time * time;
		int p2 = player->y;
		int gab = p2 - p1;
		for (int i = 0; i < gab; i++)
		{
			if (Map[p1 + i][player->x] > 4 && Map[p1 + i][player->x + 1] > 4)
			{
				player->y = p1 + i - 1;
				player->isfloat = false;
				jumpTime = 0;
				break;
			}
		}

	}
}
void EnemyGravity(int(*Map)[MapX])
{
	for (int i = 0; i < EnemyCount; i++)
	{
		if (enemy[i] != nullptr)
		{
			if (Map[enemy[i]->y +EnemySizeY][enemy[i]->x] < 4)
				enemy[i]->y++;
		}
	}
}
#pragma endregion

#pragma region GameFunction
void MapRender(int(*Map)[MapX])
{
	for (int y = 0; y < MapY; y++)
	{
		for (int x = 0; x < MapX; x++)
		{
			switch (Map[y][x])
			{
			case 2:
				WriteBuffer(x, y, "|", LIGHTGREEN);
				break;
			case 3:
				WriteBuffer(x, y, "|", LIGHTMAGENTA);
				break;
			case 5:
				WriteBuffer(x, y, "��", LIGHTGRAY);
				break;
			case 6:
				WriteBuffer(x, y, "��", LIGHTGRAY);
				break;
			case 7:
				WriteBuffer(x, y, "��", LIGHTGRAY);
				break;
			default:
				break;
			}
		}
	}
}
#pragma endregion

#pragma region Bullet
void BulletShapeInit()
{
	bulletShape[PISTOL][RIGHT] = "--";
	bulletShape[PISTOL][R_UP] = "/";
	bulletShape[PISTOL][UP] = "|";
	bulletShape[PISTOL][L_UP] = "\\";
	bulletShape[PISTOL][LEFT] = "--";
	bulletShape[PISTOL][L_DOWN] = "/";
	bulletShape[PISTOL][DOWN] = "|";
	bulletShape[PISTOL][R_DOWN] = "\\";

	bulletShape[RIFLE][RIGHT] = ">";
	bulletShape[RIFLE][R_UP] = "��";
	bulletShape[RIFLE][UP] = "��";
	bulletShape[RIFLE][L_UP] = "����";
	bulletShape[RIFLE][LEFT] = "<";
	bulletShape[RIFLE][L_DOWN] = "��";
	bulletShape[RIFLE][DOWN] = "\\/";
	bulletShape[RIFLE][R_DOWN] = "����";
}
void PlayerBulletInit(double speed, int damage, int weaponNumber, int(*Map)[MapX])
{
	for (int i = 0; i < playerBulletCount; i++)
	{
		if (playerBullet[i] == nullptr)
		{
			playerBullet[i] = (Gun*)malloc(sizeof(Gun));
			for (int j = 0; j < 4; j++)
			{
				playerBullet[i]->bullet[j] = (Bullet*)malloc(sizeof(Bullet));
				switch (player->direction)
				{
				case RIGHT:
					playerBullet[i]->bullet[j]->x = player->x + 3 + j;
					playerBullet[i]->bullet[j]->y = player->y + GunY;
					break;
				case R_UP:
					playerBullet[i]->bullet[j]->x = player->x + 2 + j;
					playerBullet[i]->bullet[j]->y = player->y - 1 + GunY - j;
					break;
				case UP:
					playerBullet[i]->bullet[j]->x = player->x+1;
					playerBullet[i]->bullet[j]->y = player->y - 2 + GunY - j;
					break;
				case L_UP:
					playerBullet[i]->bullet[j]->x = player->x  - j;
					playerBullet[i]->bullet[j]->y = player->y - 1+ GunY - j;
					break;
				case LEFT:
					playerBullet[i]->bullet[j]->x = player->x - 1 - j;
					playerBullet[i]->bullet[j]->y = player->y + GunY;
					break;
				case L_DOWN:
					playerBullet[i]->bullet[j]->x = player->x - 1 - j;
					playerBullet[i]->bullet[j]->y = player->y + 1 + j;
					break;
				case DOWN:
					playerBullet[i]->bullet[j]->x = player->x+1;
					playerBullet[i]->bullet[j]->y = player->y + 1  + j;
					break;
				case R_DOWN:
					playerBullet[i]->bullet[j]->x = player->x + 2 + j;
					playerBullet[i]->bullet[j]->y = player->y + 1 + j;
					break;
				default:
					playerBullet[i]->bullet[j]->x = player->x + 1 + j;
					playerBullet[i]->bullet[j]->y = player->y + GunY;
					break;
				}

				for (int k = 0; k < 8; k++)
				{
					playerBullet[i]->bullet[j]->shape[k] = bulletShape[weaponNumber][k];
				}
				playerBullet[i]->bullet[j]->damage = damage;
				playerBullet[i]->bullet[j]->destroy[0] = " :";
				playerBullet[i]->bullet[j]->destroy[1] = "'.";
				playerBullet[i]->bullet[j]->destroy[2] = "''";
				playerBullet[i]->bullet[j]->destroy[3] = ".'";
				playerBullet[i]->bullet[j]->destroy[4] = ": ";
				playerBullet[i]->bullet[j]->destroy[5] = "'.";
				playerBullet[i]->bullet[j]->destroy[6] = "..";
				playerBullet[i]->bullet[j]->destroy[7] = ".'";
				playerBullet[i]->bullet[j]->direction = player->direction;
				playerBullet[i]->bullet[j]->speed = speed;

				for (int k = 0; k < EnemyCount; k++)
				{
					if (enemy[k] != nullptr)
					{
						if (playerBullet[i]->bullet[j]->x == enemy[k]->x && playerBullet[i]->bullet[j]->y == enemy[k]->y)
						{
							enemy[k]->isDownHp = true;
							enemy[k]->hp--;
						}
					}
				}

				if (Map[(int)playerBullet[i]->bullet[j]->y][(int)playerBullet[i]->bullet[j]->x] > 5)
				{
					free(playerBullet[i]); playerBullet[i] = nullptr;
					break;
				}
			}
			break;
		}
	}
}
void PlayerBulletProgress(int(*Map)[MapX])
{
	for (int i = 0; i < playerBulletCount; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (playerBullet[i] != nullptr)
			{
				WriteBuffer(playerBullet[i]->bullet[j]->x, playerBullet[i]->bullet[j]->y, playerBullet[i]->bullet[j]->shape[playerBullet[i]->bullet[j]->direction], YELLOW);
				switch (playerBullet[i]->bullet[j]->direction)
				{
				case RIGHT:
					playerBullet[i]->bullet[j]->x += playerBullet[i]->bullet[j]->speed;
					break;
				case R_UP:
					playerBullet[i]->bullet[j]->x += playerBullet[i]->bullet[j]->speed;
					playerBullet[i]->bullet[j]->y -= playerBullet[i]->bullet[j]->speed;
					break;
				case UP:
					playerBullet[i]->bullet[j]->y -= playerBullet[i]->bullet[j]->speed;
					break;
				case L_UP:
					playerBullet[i]->bullet[j]->x -= playerBullet[i]->bullet[j]->speed;
					playerBullet[i]->bullet[j]->y -= playerBullet[i]->bullet[j]->speed;
					break;
				case LEFT:
					playerBullet[i]->bullet[j]->x -= playerBullet[i]->bullet[j]->speed;
					break;
				case L_DOWN:
					playerBullet[i]->bullet[j]->x -= playerBullet[i]->bullet[j]->speed;
					playerBullet[i]->bullet[j]->y += playerBullet[i]->bullet[j]->speed;
					break;
				case DOWN:
					playerBullet[i]->bullet[j]->y += playerBullet[i]->bullet[j]->speed;
					break;
				case R_DOWN:
					playerBullet[i]->bullet[j]->x += playerBullet[i]->bullet[j]->speed;
					playerBullet[i]->bullet[j]->y += playerBullet[i]->bullet[j]->speed;
					break;
				default:
					playerBullet[i]->bullet[j]->x += playerBullet[i]->bullet[j]->speed;
					break;
				}
				if (playerBullet[i]->bullet[j]->x < 0 || playerBullet[i]->bullet[j]->x>MapX || playerBullet[i]->bullet[j]->y < 0 || playerBullet[i]->bullet[j]->y>MapY)
				{
					for (int k = 0; k < 4; k++)
					{
						free(playerBullet[i]->bullet[k]);
						playerBullet[i]->bullet[j] = nullptr;
					}
					free(playerBullet[i]);
					playerBullet[i] = nullptr;
				}
				else if (Map[playerBullet[i]->bullet[j]->y][playerBullet[i]->bullet[j]->x] > 5)
				{
					switch (playerBullet[i]->bullet[j]->direction)
					{
					case RIGHT:
						WriteBuffer(playerBullet[i]->bullet[j]->x - 1, playerBullet[i]->bullet[j]->y, playerBullet[i]->bullet[j]->destroy[0], RED);
						break;
					case R_UP:
						WriteBuffer(playerBullet[i]->bullet[j]->x - 1, playerBullet[i]->bullet[j]->y + 1, playerBullet[i]->bullet[j]->destroy[1], RED);
						break;
					case UP:
						WriteBuffer(playerBullet[i]->bullet[j]->x, playerBullet[i]->bullet[j]->y + 1, playerBullet[i]->bullet[j]->destroy[2], RED);
						break;
					case L_UP:
						WriteBuffer(playerBullet[i]->bullet[j]->x + 1, playerBullet[i]->bullet[j]->y + 1, playerBullet[i]->bullet[j]->destroy[3], RED);
						break;
					case LEFT:
						WriteBuffer(playerBullet[i]->bullet[j]->x + 1, playerBullet[i]->bullet[j]->y, playerBullet[i]->bullet[j]->destroy[4], RED);
						break;
					case L_DOWN:
						WriteBuffer(playerBullet[i]->bullet[j]->x + 1, playerBullet[i]->bullet[j]->y - 1, playerBullet[i]->bullet[j]->destroy[5], RED);
						break;
					case DOWN:
						WriteBuffer(playerBullet[i]->bullet[j]->x, playerBullet[i]->bullet[j]->y - 1, playerBullet[i]->bullet[j]->destroy[6], RED);
						break;
					case R_DOWN:
						WriteBuffer(playerBullet[i]->bullet[j]->x - 1, playerBullet[i]->bullet[j]->y - 1, playerBullet[i]->bullet[j]->destroy[7], RED);
						break;
					}
					for (int k = 0; k < 4; k++)
					{
						free(playerBullet[i]->bullet[k]);
						playerBullet[i]->bullet[j] = nullptr;
					}
					free(playerBullet[i]);
					playerBullet[i] = nullptr;
					continue;
				}
				for (int s = 0; s < 4; s++)
				{
					for (int k = 0; k < EnemyCount; k++)
					{
						if (enemy[k] != nullptr && playerBullet[i] != nullptr)
						{
							if (playerBullet[i]->bullet[j]->x > enemy[k]->x && playerBullet[i]->bullet[j]->x < enemy[k]->x + EnemySizeX && playerBullet[i]->bullet[j]->y > enemy[k]->y  && playerBullet[i]->bullet[j]->y < enemy[k]->y+EnemySizeY && enemy[k]->hp > 0)
							{
								enemy[k]->isDownHp = true;
								enemy[k]->hp -= playerBullet[i]->bullet[j]->damage;
								for (int k = 0; k < 4; k++)
								{
									free(playerBullet[i]->bullet[k]);
									playerBullet[i]->bullet[j] = nullptr;
								}
								free(playerBullet[i]);
								playerBullet[i] = nullptr;
							}
						}
					}
				}
			}
		}

	}
}
void EnemyBulletInit(Enemy* enemy)
{
	for (int i = 0; i < enemyBulletCount; i++)
	{
		if (enemyBullet[i] == nullptr)
		{
			enemyBullet[i] = (Bullet*)malloc(sizeof(Bullet));
			enemyBullet[i]->destroy[0] = " :";
			enemyBullet[i]->destroy[1] = "'.";
			enemyBullet[i]->destroy[2] = "''";
			enemyBullet[i]->destroy[3] = ".'";
			enemyBullet[i]->destroy[4] = ": ";
			enemyBullet[i]->destroy[5] = "'.";
			enemyBullet[i]->destroy[6] = "..";
			enemyBullet[i]->destroy[7] = ".'";
			if (enemy->Lv == 1)
			{
				enemyBullet[i]->shape[0] = "&";
				enemyBullet[i]->damage = 1;
				enemyBullet[i]->Xcount[0] = 2;
				enemyBullet[i]->Xcount[1] = 0;
				enemyBullet[i]->Ycount[0] = 2;
				enemyBullet[i]->Ycount[1] = 0;
				enemyBullet[i]->speed = 1;
			}
			else if (enemy->Lv == 2)
			{
				enemyBullet[i]->shape[0] = "��";
				enemyBullet[i]->damage = 3;
				enemyBullet[i]->Xcount[0] = 2;
				enemyBullet[i]->Xcount[1] = 0;
				enemyBullet[i]->Ycount[0] = 2;
				enemyBullet[i]->Ycount[1] = 0;
				enemyBullet[i]->speed = 1;
			}
			else if (enemy->Lv == 3)
			{
				enemyBullet[i]->shape[0] = "+";
				enemyBullet[i]->damage = 3;
			}

			int x = player->x - enemy->x;
			int y = player->y-PlayerSizeY+1 - enemy->y;
			if (y == 0 && x > 0)
			{
				enemyBullet[i]->direction = 0;
				enemyBullet[i]->x = enemy->x + 1 - 3;
				enemyBullet[i]->y = enemy->y ;
			}
			else if (x > 0 && y < 0)
			{
				enemyBullet[i]->direction = 1;
				enemyBullet[i]->x = enemy->x + 1 ;
				enemyBullet[i]->y = enemy->y - 1 ;
			}
			else if (x == 0 && y < 0)
			{
				enemyBullet[i]->direction = 2;
				enemyBullet[i]->x = enemy->x ;
				enemyBullet[i]->y = enemy->y - 1;
			}
			else if (x < 0 && y < 0)
			{
				enemyBullet[i]->direction = 3;
				enemyBullet[i]->x = enemy->x - 1 ;
				enemyBullet[i]->y = enemy->y - 1;
			}
			else if (y == 0 && x < 0)
			{
				enemyBullet[i]->direction = 4;
				enemyBullet[i]->x = enemy->x - 1;
				enemyBullet[i]->y = enemy->y ;
			}
			else if (x < 0 && y>0)
			{
				enemyBullet[i]->direction = 5;
				enemyBullet[i]->x = enemy->x - 1;
				enemyBullet[i]->y = enemy->y + 1 ;
			}
			else if (x == 0 && y > 0)
			{
				enemyBullet[i]->direction = 6;
				enemyBullet[i]->x = enemy->x ;
				enemyBullet[i]->y = enemy->y + 1 ;
			}
			else if (x > 0 && y > 0)
			{
				enemyBullet[i]->direction = 7;
				enemyBullet[i]->x = enemy->x + 1;
				enemyBullet[i]->y = enemy->y + 1 ;
			}
			else
			{
				enemyBullet[i]->direction = 0;
				enemyBullet[i]->x = enemy->x + 1;
				enemyBullet[i]->y = enemy->y ;
			}
			break;
		}
	}
}
#pragma endregion

#pragma region UI
void GunUI_Init()
{
	WeaphoneMap[0][0] = "���������������� ";
	WeaphoneMap[0][1] = "������������ �� ";
	WeaphoneMap[0][2] = "     ������";

	WeaphoneMap[1][0] = "������������������������������������ ";
	WeaphoneMap[1][1] = "������������������  ���������� �� ";
	WeaphoneMap[1][2] = "        ��������   ������ ";

	WeaphoneMap[2][0] = "           ��         ";
	WeaphoneMap[2][1] = "                     ";
	WeaphoneMap[2][2] = "           ź        ";

}
void GunUI_Rander()
{
	_itoa(player->bulletNum[RIFLE], Bullet1_Num, 10);
	_itoa(player->bulletNum[BOMB], Bullet2_Num, 10);

	if (player->weaponNum == PISTOL)
	{
		for (int i = 0; i < 3; i++)
		{
			WriteBuffer(1, 30 + i, WeaphoneMap[0][i], CYAN);
		}

		for (int i = 0; i < 3; i++)
		{
			WriteBuffer(7, 30 + i, WeaphoneMap[1][i], WHITE);

		}
		for (int i = 0; i < 3; i++)
		{
			WriteBuffer(13, 30 + i, WeaphoneMap[2][i], WHITE);
		}
		WriteBuffer(2, 33, "[1]", CYAN);
		WriteBuffer(8, 33, "[2]", WHITE);
		WriteBuffer(2, 34, "��", CYAN);
		WriteBuffer(8, 34, Bullet1_Num, WHITE);
		WriteBuffer(10, 34, "��", WHITE);
		WriteBuffer(14, 33, "[3]", WHITE);
		WriteBuffer(14, 34, Bullet2_Num, WHITE);

	}
	if (player->weaponNum == RIFLE)
	{

		for (int i = 0; i < 3; i++)
		{
			WriteBuffer(1, 30 + i, WeaphoneMap[0][i], WHITE);
		}
		for (int i = 0; i < 3; i++)
		{
			WriteBuffer(7, 30 + i, WeaphoneMap[1][i], CYAN);
		}
		for (int i = 0; i < 3; i++)
		{
			WriteBuffer(13, 30 + i, WeaphoneMap[2][i], WHITE);
		}
		WriteBuffer(2, 33, "[1]", WHITE);
		WriteBuffer(8, 33, "[2]", CYAN);
		WriteBuffer(2, 34, "��", WHITE);
		WriteBuffer(8, 34, Bullet1_Num, CYAN);
		WriteBuffer(10, 34, "��", CYAN);
		WriteBuffer(14, 33, "[3]", WHITE);
		WriteBuffer(14, 34, Bullet2_Num, WHITE);

	}
	if (player->weaponNum == BOMB)
	{

		for (int i = 0; i < 3; i++)
		{
			WriteBuffer(1, 30 + i, WeaphoneMap[0][i], WHITE);
		}
		for (int i = 0; i < 3; i++)
		{
			WriteBuffer(7, 30 + i, WeaphoneMap[1][i], WHITE);
		}
		for (int i = 0; i < 3; i++)
		{
			WriteBuffer(13, 30 + i, WeaphoneMap[2][i], CYAN);

		}
		WriteBuffer(2, 33, "[1]", WHITE);
		WriteBuffer(8, 33, "[2]", WHITE);
		WriteBuffer(2, 34, "��", WHITE);
		WriteBuffer(8, 34, Bullet1_Num, WHITE);
		WriteBuffer(10, 34, "��", WHITE);
		WriteBuffer(14, 33, "[3]", CYAN);
		WriteBuffer(14, 34, Bullet2_Num, CYAN);
	}
}
void NextPointer_Init(int x, int y)
{
	if (ResultEnemyCount() == 0)
	{
		WriteBuffer(x, y, "                . ", YELLOW);
		WriteBuffer(x, y + 1, " .. ............;;.", YELLOW);
		WriteBuffer(x, y + 2, " ..::::::::::::;;;;.", YELLOW);
		WriteBuffer(x, y + 3, ". . ::::::::::::;;:'", YELLOW);
		WriteBuffer(x, y + 4, "                :'", YELLOW);
	}

}
#pragma endregion

#pragma region Enemy
void EnemyRander()
{
	for (int i = 0; i < EnemyCount; i++)
	{
		if (enemy[i] != nullptr && enemy[i]->hp > 0)
		{
			char* hp = (char*)malloc(sizeof(char));
			_itoa(enemy[i]->hp, hp, 10);
			WriteBuffer(enemy[i]->x, enemy[i]->y - 5, hp, WHITE);
			if (enemy[i]->isLeft)
			{
				for (int j = 0; j < 4; j++)
				{
					WriteBuffer(enemy[i]->x, enemy[i]->y +j, enemy[i]->shape[0][j], enemy[i]->color);
				}

			}
			else
			{
				for (int j = 0; j < 4; j++)
				{
					WriteBuffer(enemy[i]->x, enemy[i]->y +j, enemy[i]->shape[1][j], enemy[i]->color);
				}
			}

		}
		if (enemy[i] != nullptr && enemy[i]->hp <= 0)
		{

			for (int j = 0; j < 4; j++)
			{
				switch (player->direction)
				{
				case 0:
				case 1:
				case 2:
				case 7:
					WriteBuffer(enemy[i]->x, enemy[i]->y +j, enemy[i]->die[0][j], enemy[i]->color);
					break;
				case 3:
				case 4:
				case 5:
				case 6:
				default:
					WriteBuffer(enemy[i]->x, enemy[i]->y + j, enemy[i]->die[1][j], enemy[i]->color);
					break;
				}
			}

			enemy[i]->responTime--;
			if (enemy[i]->responTime <= 0)
			{
				free(enemy[i]);
				enemy[i] = nullptr;
			}
		}
	}
}
void EnemyInit(int(*Map)[MapX])
{
	for (int y = 0; y < MapY; y++)
	{
		for (int x = 0; x < MapX; x++)
		{
			if (Map[y][x] == 1)
			{
				for (int i = 0; i < EnemyCount; i++)
				{
					if (enemy[i] == nullptr)
					{
						enemy[i] = (Enemy*)malloc(sizeof(Enemy));
						enemy[i]->x = x;
						enemy[i]->y = y;

						enemy[i]->Lv = 1;
						enemy[i]->rerodingTime[1] = 0;
						enemy[i]->responTime = 30;
						
						enemy[i]->shape[0][0] = "��@ ";
						enemy[i]->shape[0][1] = " o|)";
						enemy[i]->shape[0][2] = "  ^ ";
						enemy[i]->shape[0][3] = " - -";

						enemy[i]->shape[1][0] = " @��";
						enemy[i]->shape[1][1] = "(|o";
						enemy[i]->shape[1][2] = " ^ ";
						enemy[i]->shape[1][3] = "- -";

						enemy[i]->die[0][0] = "";
						enemy[i]->die[0][1] = "-   o ��";
						enemy[i]->die[0][2] = "  > �� @";
						enemy[i]->die[0][3] = "-";

						enemy[i]->die[1][0] = "";
						enemy[i]->die[1][1] = "�� o    -";
						enemy[i]->die[1][2] = "@ �� < ";
						enemy[i]->die[1][3] = "       -";

						enemy[i]->hp = 5;
						enemy[i]->rerodingTime[0] = 50;
						enemy[i]->color = LIGHTMAGENTA;
						
						enemy[i]->isLeft = false;
						enemy[i]->isDownHp = false;
						enemy[i]->downHpDelay[0] = 3;
						enemy[i]->downHpDelay[1] = 0;
						Map[y][x] = 0;
						break;
					}
				}
			}
			if (Map[y][x] == 2)
			{
				for (int i = 0; i < EnemyCount; i++)
				{
					if (enemy[i] == nullptr)
					{
						enemy[i] = (Enemy*)malloc(sizeof(Enemy));
						enemy[i]->x = x;
						enemy[i]->y = y;

						enemy[i]->Lv = 2;
						enemy[i]->rerodingTime[MAX_TIME] = 50;
						enemy[i]->rerodingTime[NOW_TIME] = 0;
						enemy[i]->responTime = 30;
						enemy[i]->shape[0][0] = "*@ ";
						enemy[i]->shape[0][1] = "��o|)";
						enemy[i]->shape[0][2] = "  ^ ";
						enemy[i]->shape[0][3] = " - -";

						enemy[i]->shape[1][0] = " @ *";
						enemy[i]->shape[1][1] = "(|o��";
						enemy[i]->shape[1][2] = " ^ ";
						enemy[i]->shape[1][3] = "- -";

						enemy[i]->die[0][0] = "";
						enemy[i]->die[0][1] = "-   o ��*";
						enemy[i]->die[0][2] = "  > �� @";
						enemy[i]->die[0][3] = "-";

						enemy[i]->die[1][0] = "";
						enemy[i]->die[1][1] = "*�� o  -";
						enemy[i]->die[1][2] = "@ �� < ";
						enemy[i]->die[1][3] = "       -";

						enemy[i]->rerodingTime[0] = 20;
						enemy[i]->color = RED;
						enemy[i]->hp = 12;
						
						enemy[i]->color = RED;

						enemy[i]->isLeft = false;
						enemy[i]->isDownHp = false;
						enemy[i]->downHpDelay[0] = 3;
						enemy[i]->downHpDelay[1] = 0;
						Map[y][x] = 0;
						break;
					}
				}
			}
		}
	}

	
	
}
void EnemyBulletProgress(int(*Map)[MapX])
{
	if (player != nullptr)
	{

		for (int i = 0; i < EnemyCount; i++)
		{
			if (enemy[i] != nullptr && enemy[i]->hp > 0)
			{

				if (enemy[i]->rerodingTime[0] <= enemy[i]->rerodingTime[1])
				{
					EnemyBulletInit(enemy[i]);
					enemy[i]->rerodingTime[1] = 0;
				}
				else
					enemy[i]->rerodingTime[1]++;
			}
		}

		for (int i = 0; i < enemyBulletCount; i++)
		{
			if (enemyBullet[i] != nullptr)
			{
				if (enemyBullet[i]->x < 0 || enemyBullet[i]->x>100 || enemyBullet[i]->y < 0 || enemyBullet[i]->y>30)
				{
					free(enemyBullet[i]);
					enemyBullet[i] = nullptr;
				}
				else if (Map[enemyBullet[i]->y][enemyBullet[i]->x] > 5 || (enemyBullet[i]->x >= player->x && enemyBullet[i]->x<player->x+PlayerSizeX&& enemyBullet[i]->y > player->y-PlayerSizeY && enemyBullet[i]->y<=player->y))
				{
					if (enemyBullet[i]->x >= player->x && enemyBullet[i]->x<player->x + PlayerSizeX && enemyBullet[i]->y > player->y - PlayerSizeY && enemyBullet[i]->y <= player->y)
					{
						player->hp -= enemyBullet[i]->damage;
						WriteBuffer(player->x + 1, player->y - 6, "�ƾ�!", WHITE);
						player->isDownHp = true;
					}
					switch (enemyBullet[i]->direction)
					{
					case 0:
						WriteBuffer(enemyBullet[i]->x - 1, enemyBullet[i]->y, enemyBullet[i]->destroy[0], WHITE);
						break;
					case 1:
						WriteBuffer(enemyBullet[i]->x - 1, enemyBullet[i]->y + 1, enemyBullet[i]->destroy[1], WHITE);
						break;
					case 2:
						WriteBuffer(enemyBullet[i]->x, enemyBullet[i]->y + 1, enemyBullet[i]->destroy[2], WHITE);
						break;
					case 3:
						WriteBuffer(enemyBullet[i]->x + 1, enemyBullet[i]->y + 1, enemyBullet[i]->destroy[3], WHITE);
						break;
					case 4:
						WriteBuffer(enemyBullet[i]->x + 1, enemyBullet[i]->y, enemyBullet[i]->destroy[4], WHITE);
						break;
					case 5:
						WriteBuffer(enemyBullet[i]->x + 1, enemyBullet[i]->y - 1, enemyBullet[i]->destroy[5], WHITE);
						break;
					case 6:
						WriteBuffer(enemyBullet[i]->x, enemyBullet[i]->y - 1, enemyBullet[i]->destroy[6], WHITE);
						break;
					case 7:
						WriteBuffer(enemyBullet[i]->x - 1, enemyBullet[i]->y - 1, enemyBullet[i]->destroy[7], WHITE);
						break;
					}
					free(enemyBullet[i]);
					enemyBullet[i] = nullptr;
				}
				else
				{
					WriteBuffer(enemyBullet[i]->x, enemyBullet[i]->y, enemyBullet[i]->shape[0], WHITE);
					switch (enemyBullet[i]->direction)
					{
					case 0:
						enemyBullet[i]->x++;
						break;
					case 1:
						enemyBullet[i]->Xcount[1] += enemyBullet[i]->speed;
						enemyBullet[i]->Ycount[1] += enemyBullet[i]->speed;
						if (enemyBullet[i]->Xcount[0] <= enemyBullet[i]->Xcount[1])
						{
							enemyBullet[i]->Xcount[1] = 0;
							enemyBullet[i]->x += enemyBullet[i]->speed;
						}
						if (enemyBullet[i]->Ycount[0] <= enemyBullet[i]->Ycount[1])
						{
							enemyBullet[i]->Ycount[1] = 0;
							enemyBullet[i]->y -= enemyBullet[i]->speed;
						}
						break;
					case 2:
						enemyBullet[i]->y -= enemyBullet[i]->speed;
						break;
					case 3:
						enemyBullet[i]->Xcount[1]++;
						enemyBullet[i]->Ycount[1]++;
						if (enemyBullet[i]->Xcount[0] <= enemyBullet[i]->Xcount[1])
						{
							enemyBullet[i]->Xcount[1] = 0;
							enemyBullet[i]->x -= enemyBullet[i]->speed;
						}
						if (enemyBullet[i]->Ycount[0] <= enemyBullet[i]->Ycount[1])
						{
							enemyBullet[i]->Ycount[1] = 0;
							enemyBullet[i]->y -= enemyBullet[i]->speed;
						}
						break;
					case 4:
						enemyBullet[i]->x -= enemyBullet[i]->speed;
						break;
					case 5:
						enemyBullet[i]->Xcount[1]++;
						enemyBullet[i]->Ycount[1]++;
						if (enemyBullet[i]->Xcount[0] <= enemyBullet[i]->Xcount[1])
						{
							enemyBullet[i]->Xcount[1] = 0;
							enemyBullet[i]->x -= enemyBullet[i]->speed;
						}
						if (enemyBullet[i]->Ycount[0] <= enemyBullet[i]->Ycount[1])
						{
							enemyBullet[i]->Ycount[1] = 0;
							enemyBullet[i]->y += enemyBullet[i]->speed;
						}
						break;
					case 6:
						enemyBullet[i]->y += enemyBullet[i]->speed;
						break;
					case 7:
						enemyBullet[i]->Xcount[1]++;
						enemyBullet[i]->Ycount[1]++;
						if (enemyBullet[i]->Xcount[0] <= enemyBullet[i]->Xcount[1])
						{
							enemyBullet[i]->Xcount[1] = 0;
							enemyBullet[i]->x += enemyBullet[i]->speed;
						}
						if (enemyBullet[i]->Ycount[0] <= enemyBullet[i]->Ycount[1])
						{
							enemyBullet[i]->Ycount[1] = 0;
							enemyBullet[i]->y += enemyBullet[i]->speed;
						}
						break;
					default:
						break;
					}
				}
			}
		}

	}
}
void EnemyPorogress(int(*Map)[MapX])
{
	for (int i = 0; i < EnemyCount; i++)
	{
		if (enemy[i] != nullptr && enemy[i]->hp > 0)
		{
			if (rand() % 1000 < 1 && Map[enemy[i]->y][enemy[i]->x + 1] < 5 && Map[enemy[i]->y][enemy[i]->x + 1] != 4)
			{
				enemy[i]->moveDir[0] = rand() % 4;
			}
			else if (rand() % 100 < 2 && rand() % 100 >= 1)
			{
				enemy[i]->moveDir[0] = -(rand() % 4);
			}
			else if (rand() % 100 < 3 && rand() % 100 >= 2)
			{
				if (enemy[i]->x < player->x)
				{
					enemy[i]->moveDir[0] = rand() % 4;
				}
				else if (Map[enemy[i]->y][enemy[i]->x - 1] < 5)
				{
					enemy[i]->moveDir[0] = -(rand() % 4);
				}
			}
			if (enemy[i]->moveDir[0] != enemy[i]->moveDir[1])
			{
				if (enemy[i]->moveDir[0] > enemy[i]->moveDir[1] && Map[enemy[i]->y][enemy[i]->x + 1] < 5 && Map[enemy[i]->y][enemy[i]->x + 1] != 4)
				{
					enemy[i]->moveDir[1]++;
					enemy[i]->x++;
					enemy[i]->isLeft = false;
				}
				if (enemy[i]->moveDir[0] < enemy[i]->moveDir[1] && Map[enemy[i]->y][enemy[i]->x - 1] < 5 && Map[enemy[i]->y][enemy[i]->x - 1] != 4)
				{
					enemy[i]->moveDir[1]--;
					enemy[i]->x--;
					enemy[i]->isLeft = true;
				}
			}
			else
			{
				enemy[i]->moveDir[0] = 0;
				enemy[i]->moveDir[1] = 0;
			}
			for (int j = 0; j < EnemyCount; j++)
			{
				if (enemy[j] != nullptr && j != i && enemy[i]->x == enemy[j]->x && (enemy[i]->y == enemy[j]->y || enemy[i]->x + 1 == enemy[j]->x - 1 && enemy[i]->y == enemy[j]->y))
				{
					if (Map[enemy[i]->y][enemy[i]->x + 1] != 4)
					{
						enemy[j]->x++;
					}
					if (Map[enemy[i]->y][enemy[i]->x - 1] != 4)
					{
						enemy[i]->x--;
					}
				}
			}
		}
	}
	EnemyGravity(Map);
}
void EnemyHpDownEffect()
{
	for (int i = 0; i < EnemyCount; i++)
	{
		if (enemy[i] != nullptr)
		{
			if (enemy[i]->isDownHp)
			{
				switch (enemy[i]->Lv)
				{
				case 1:
					enemy[i]->color = WHITE;
					enemy[i]->downHpDelay[1]++;
					if (enemy[i]->downHpDelay[1] > enemy[i]->downHpDelay[0])
					{
						enemy[i]->isDownHp = false;
						enemy[i]->downHpDelay[1] = 0;
						enemy[i]->color = LIGHTMAGENTA;
					}
					break;
				case 2:
					enemy[i]->color = WHITE;
					enemy[i]->downHpDelay[1]++;
					if (enemy[i]->downHpDelay[1] > enemy[i]->downHpDelay[0])
					{
						enemy[i]->isDownHp = false;
						enemy[i]->downHpDelay[1] = 0;
						enemy[i]->color = RED;
					}
					break;
				default:
					break;
				}

			}
		}
	}
}
int ResultEnemyCount()
{
	int Count = 0;
	for (int i = 0; i < EnemyCount; i++)
	{
		if (enemy[i] != nullptr)
		{
			Count++;
		}
	}
	return Count;
}
#pragma endregion

#pragma region Guide
void GuideMove()
{
	if (guideMove)
	{
		guideStartTime++;
	}
	if (guideStartTime >= 20 && guideMove)
	{
		WriteBuffer(player->x - 1, player->y - 7, "    [��]     ����Ű�� �÷��̾ ", WHITE);
		WriteBuffer(player->x - 1, player->y - 6, "[��][��][��]     ������������", WHITE);
		if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT))
		{
			guideEndTime++;
		}
		if (guideEndTime >= 20 && guideMove)
		{
			guideStartTime = 0;
			guideEndTime = 0;
			guideMove = false;
		}
	}
}
void GuideAttack()
{
	if (guideAttack && !guideMove)
	{
		guideStartTime++;
	}
	if (guideStartTime >= 20 && guideAttack && !guideMove)
	{
		WriteBuffer(player->x - 1, player->y - 7, "�Ѿ˷� ���� �����غ�����!", WHITE);
		WriteBuffer(player->x - 1, player->y - 6, "[��] +A or A ", WHITE);
		if (GetAsyncKeyState(0x41))
		{
			guideEndTime++;
		}
		if (guideEndTime >= 20 && guideAttack && !guideMove)
		{
			guideStartTime = 0;
			guideEndTime = 0;
			guideAttack = false;
		}
	}
}
void GuideJump()
{
	if (28 < player->x && player->x < 36 && guideJump && !guideAttack)
	{
		guideStartTime++;
	}
	if (guideStartTime >= 10 && guideJump && !guideAttack)
	{
		WriteBuffer(player->x - 1, player->y - 7, "[space]�� �����غ�����", WHITE);
		if (GetAsyncKeyState(VK_SPACE))
		{
			guideEndTime++;
		}
		if (guideEndTime >= 20 && guideJump && !guideAttack)
		{
			guideStartTime = 0;
			guideEndTime = 0;
			guideJump = false;
		}
	}

}
#pragma endregion

//void CreateBoss1(int x, int y)
//{
//	boos = (Boos*)malloc(sizeof(boos));
//	boos->x = x;
//	boos->y = y;
//	boos->shape[0] = "                  |";
//	boos->shape[1] = "             ___|_|_";
//	boos->shape[2] = "============|      _/";
//	boos->shape[3] = "_____==|\\___/=====\\___";
//	boos->shape[4] = "|______________________|";
//	boos->shape[5] = "(=========/ \=========)";
//	boos->shape[6] = " ������������������   ������������������";
//}

void CreatePlayerBomb()
{
	if (bomb == nullptr && player->bulletNum[1] > 0)
	{
		bomb = (Bomb*)malloc(sizeof(Bomb));
		bomb->x = player->x;
		bomb->y = player->y - 3;
		bomb->time = 0.f;
		bomb->responTime = 0;
		bomb->shape = "��";
		bomb->direction = player->direction;
		bomb->Xspeed = 0;
		bomb->YSpeed = 0;
		bomb->V = 2.0f;

		switch (bomb->direction)
		{
		case 0:
		case 1:
		case 7:
			bomb->Xspeed += 2;
			break;
		case 2:
			bomb->V = 5.0f;
			break;
		case 3:
		case 4:
		case 5:
			bomb->Xspeed -= 2;
			break;
		case 6:
			break;
		default:
			break;
		}
		bomb->isbump = false;
	}
}
void AttackBomb(int(*Map)[MapX])
{
	if (bomb != nullptr)
	{
		if (!bomb->isbump)
		{
			bomb->x += bomb->Xspeed;
			bomb->y += bomb->YSpeed;

			int pos1 = bomb->y;
			bomb->time += 0.15;
			bomb->y = bomb->y - bomb->V * bomb->time + 0.5f * BombG * bomb->time * bomb->time;
			int pos2 = bomb->y;
			int gab = pos2 - pos1;
			WriteBuffer(bomb->x, bomb->y, bomb->shape, WHITE);
			if (gab > 0)
			{
				for (int i = 0; i < gab; i++)
				{
					if (Map[bomb->y - i][bomb->x] > 5 || Map[bomb->y - i][bomb->x + 1] > 5 || Map[bomb->y - i][bomb->x - 1] > 5)
					{
						bomb->y = bomb->y - i;
						bomb->isbump = true;
						break;
					}
				}
			}
			else
			{
				for (int i = 0; i < gab * -1; i++)
				{
					if (Map[bomb->y + i][bomb->x] > 5 || Map[bomb->y - i][bomb->x] > 5 || Map[bomb->y - i][bomb->x - 1] > 5)
					{
						bomb->y = bomb->y + i;
						bomb->isbump = true;
						break;
					}
				}
			}

		}
		if (bomb->isbump)
		{

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					WriteBuffer(bomb->x - 5 + i, bomb->y - 7 + j, "��", RED);
					if (player->x == (bomb->x - 5 + i) && player->y - 3 == (bomb->y - 7 + j))
					{
						if (bomb->responTime == 0)
						{
							player->hp -= 5;
						}

					}
					if (Map[bomb->y - 7 + j][bomb->x - 5 + i] == 7)
					{
						Map[bomb->y - 7 + j][bomb->x - 5 + i] = 0;
					}
					for (int k = 0; k < EnemyCount; k++)
					{
						if (enemy[k] != nullptr)
						{
							if (enemy[k]->x == (bomb->x - 5 + i) && enemy[k]->y - 3 == (bomb->y - 7 + j))
							{
								if (bomb->responTime == 0)
								{
									enemy[k]->hp -= 30;
								}
							}
						}
					}
				}
			}
			bomb->responTime++;
			if (bomb->responTime >= 10)
			{
				free(bomb);
				bomb = nullptr;
			}
		}


	}
}
#pragma region GameFunction
void ShowMap(int(*Map)[MapX])
{
	for (int y = 0; y < MapY; y++)
	{
		for (int x = 0; x < MapX; x++)
		{
			switch (Map[y][x])
			{
			case 2:
				WriteBuffer(x, y, "|", LIGHTGREEN);
				break;
			case 3:
				WriteBuffer(x, y, "|", LIGHTMAGENTA);
				break;
			case 5:
				WriteBuffer(x, y, "��", LIGHTGRAY);
				break;
			case 6:
				WriteBuffer(x, y, "��", LIGHTGRAY);
				break;
			case 7:
				WriteBuffer(x, y, "��", LIGHTGRAY);
				break;
			default:
				break;
			}
		}
	}
}

void Weaphone_MapInitialize()
{
	WeaphoneMap[0][0] = "���������������� ";
	WeaphoneMap[0][1] = "������������ �� ";
	WeaphoneMap[0][2] = "     ������";

	WeaphoneMap[1][0] = "������������������������������������ ";
	WeaphoneMap[1][1] = "������������������  ���������� �� ";
	WeaphoneMap[1][2] = "        ��������   ������ ";

	WeaphoneMap[2][0] = "           ��         ";
	WeaphoneMap[2][1] = "                     ";
	WeaphoneMap[2][2] = "           ź        ";

}
void ItemInit(int x, int y, int ItemNumber)  // ��ǥ,���ϴ� �����۹�ȣ
{
	for (int i = 0; i < ItemCount; i++)
	{
		if (item[i] == nullptr)
		{
			item[i] = (Item*)malloc(sizeof(Item));

			item[i]->x = x;
			item[i]->y = y;

			switch (ItemNumber)
			{
			case HEAL:

				item[i]->color = RED;
				item[i]->shape[0] = " ____";
				item[i]->shape[1] = "��+����";
				item[i]->shape[2] = "����������";
				item[i]->itemEffect = HEAL;
				break;
			case ADD_02:
				item[i]->color = YELLOW;
				item[i]->shape[0] = " ____";
				item[i]->shape[1] = "��+�覢";
				item[i]->shape[2] = "����������";
				item[i]->itemEffect = ADD_02;
				break;
			case ADD_bomb:
				item[i]->color = BLUE;
				item[i]->shape[0] = " ____";
				item[i]->shape[1] = "��+�ݦ�";
				item[i]->shape[2] = "����������";
				item[i]->itemEffect = ADD_bomb;
				break;
			default:
				break;
			}
			break;
		}
	}
}
void ItemProgress()
{
	for (int i = 0; i < ItemCount; i++)
	{
		if (item[i] != nullptr)
		{
			for (int j = 0; j < 3; j++)
			{
				WriteBuffer(item[i]->x, item[i]->y - j, item[i]->shape[2 - j], item[i]->color);

			}
			if ((item[i]->x == player->x || item[i]->x == player->x - 1 || item[i]->x == player->x + 1) && (item[i]->y == player->y || item[i]->y + 1 == player->y || item[i]->y - 1 == player->y))
			{
				switch (item[i]->itemEffect)
				{
				case HEAL:
					player->hp++;
					break;
				case ADD_02:
					if (player->bulletNum[0] >= 200)
					{
						player->bulletNum[0] = 200;
					}
					else
					{
						player->bulletNum[0] += 50;
					}
					break;
				case ADD_bomb:
					if (player->bulletNum[1] >= 20)
					{
						player->bulletNum[1] = 20;
					}
					else
					{
						player->bulletNum[1] += 5;
					}
				default:
					break;
				}
				free(item[i]);
				item[i] = nullptr;
			}
		}
	}
}
void TrapInit(int x, int y, int width, int damage, int delay, int color, const char* shape)
{
	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		if (trap[i] == nullptr)
		{
			trap[i] = (Trap*)malloc(sizeof(Trap));
			trap[i]->x = x + count;
			trap[i]->y = y;
			trap[i]->width = width;
			trap[i]->damage = damage;
			trap[i]->attackDelay[0] = delay;
			trap[i]->attackDelay[1] = 0;
			trap[i]->shape = shape;
			trap[i]->color = color;
			count++;
		}
		if (count >= width) { break; }
	}
}
void TrapRander()
{
	for (int i = 0; i < 10; i++)
	{
		if (trap[i] != nullptr)
		{

			WriteBuffer(trap[i]->x, trap[i]->y, trap[i]->shape, trap[i]->color);
			if ((trap[i]->x == player->x && trap[i]->y == player->y) || (trap[i]->x == player->x + 1 && trap[i]->y == player->y))
			{
				trap[i]->attackDelay[1]++;
				if (trap[i]->attackDelay[1] >= trap[i]->attackDelay[0])
				{
					trap[i]->attackDelay[1] = 0;
					player->isDownHp = true;
					player->hp--;
				}
			}
		}
	}
}
void ShowKeyInfo()
{

	if (GetAsyncKeyState(VK_F1))
	{
		isKeyInfo = true;
	}
	if (isKeyInfo)
	{
		keyInfoDelay[1]++;
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 50; x++)
			{
				switch (KeyInfoMap[y][x])
				{
				case 0:
					WriteBuffer(x + 8, y + 3, "  ", WHITE);
					break;
				case 1:
					WriteBuffer(x + 8, y + 3, "����", WHITE);
					break;
				case 2:
					WriteBuffer(x + 8, y + 3, " ��", WHITE);
					break;
				case 3:
					WriteBuffer(x + 8, y + 3, "����", WHITE);
					break;
				case 4:
					WriteBuffer(x + 8, y + 3, "����", WHITE);
					break;
				case 5:
					WriteBuffer(x + 8, y + 3, "����", WHITE);
					break;
				case 6:
					WriteBuffer(x + 8, y + 3, "����", WHITE);
					break;
				case 7:
					WriteBuffer(x + 8, y + 3, "�� ", WHITE);
					break;
				default:
					break;
				}
				WriteBuffer(0, 3, "     ��", LIGHTMAGENTA);
				WriteBuffer(0, 5, "���� �÷��̾�HP", LIGHTMAGENTA);
				WriteBuffer(0, 34, "     ��", LIGHTMAGENTA);
				WriteBuffer(0, 36, "���� �������� ����", LIGHTMAGENTA);
				WriteBuffer(12, 5, "- �̵� -", BROWN);
				WriteBuffer(10, 7, "      [��]         ", BROWN);
				WriteBuffer(10, 9, "  [��][��][��]    ����[SPACE]   ", BROWN);
				WriteBuffer(30, 5, "- ���� -", BROWN);
				WriteBuffer(31, 8, "[A]", BROWN);
				WriteBuffer(40, 5, "- ���� ���� -", BROWN);
				WriteBuffer(41, 8, "[1][2][3]", BROWN);
				WriteBuffer(51, 10, "â �ݱ�[F2]", BROWN);
			}
		}
		while (isKeyInfo && keyInfoDelay[1] >= keyInfoDelay[0])
		{
			if (GetAsyncKeyState(VK_F2))
			{
				isKeyInfo = false;
				keyInfoDelay[1] = 0;
				break;
			}
		}

	}
	else
	{
		WriteBuffer(30, 1, "����[F1]", BROWN);
	}

}
void TrapRelease()
{
	for (int i = 0; i < TrapCount; i++)
	{
		if (trap[i] != nullptr)
		{
			free(trap[i]);
			trap[i] = nullptr;
		}
	}
}
#pragma endregion