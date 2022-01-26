#pragma once
#include "gameNode.h"
#include "Character.h"
#include "Map.h"
#include "MobManager.h"
#include "ItemManager.h"
#include "Inventory.h"
#include "login.h"

class playGround : public gameNode
{
private:
	Map* map;
	Character* c;
	MobManager* Mm;
	damage* dmg;
	ItemManager* _itemM;
	Inventory* _inven;
	login* _log;

	RECT m;

public:
	playGround();
	~playGround();

	virtual HRESULT init();	
	virtual void release();	
	virtual void update();	
	virtual void render();	

};