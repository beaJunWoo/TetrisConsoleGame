#pragma once
#include "Scenes.h"
#include "Map.h"
#include "BlockManager.h"
#include "Score.h"
#include "ScenesManager.h"
#include "DataBase.h"
class Stage:public Scenes
{
	Map* map;
	BlockManager* blockManager;
	Score* score;
	DataBase* dataBase;

	int DataInsertDelay;
	int NickNameSelectX;
	int NickNameSelectY;

	string NickName;

	vector<const char*>Alphabet[3];
public:
	void SetDataBase(DataBase* dataBase) { this->dataBase = dataBase; }

	void SaveNickName();

	virtual void Initalize()override;
	virtual void Progress()override;
	virtual void Render()override;
	virtual void Release()override;
};

