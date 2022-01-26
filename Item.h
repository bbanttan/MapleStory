#pragma once
#include "gameNode.h"

class Map;

enum ItemType
{
	WEAPON,
	CONSUME,
	ETC
};

enum ItemKind
{
	SWORD,
	BOW,
	STAFF,
	ADEA,
	DAGGER,
	ARROW
};

class Item : public gameNode
{
private:
	image* ItemImage;

	Map* _map;

	string ItemName;

	ItemType itemType;
	ItemKind itemKind;

	RECT ItemRECT;

	int
		ItemNum,
		alpha,
		slot_num,	//slot_num�� ������â���� ����
		STR,
		HP,
		MP
		;

	float x, y, y2, gra, angle;

	bool field_drop, LANDING, eatSign, eat;

public:
	virtual HRESULT init(string _iname);										 //��� ����
	virtual HRESULT init(string _iname, int _inum);								 //��Ÿ, �Һ�����
	virtual HRESULT init(string _iname, int _inum, float x, float y, Map* _m);	 //�ʵ��� ������
	virtual void release();
	virtual void update();
	virtual void render();
	void Item_Info();

	bool EatSign() { return eatSign; }
	void Eat() { eat = true; }
	bool returnEat() { return eat; }
	bool getLanding() { return LANDING; }
	int getNum() { return ItemNum; }
	int getSTR() { return STR; }

	//������Լ�
	void setX(float _x) { x = _x; }
	void setY(float _y) { y = _y; }
	float getX() { return x; }
	float getY() { return y; }

	//������â�����Լ�
	void setSlotNum(int _islot) { slot_num = _islot; }
	int getSlotNum() { return slot_num; }
	int getAddHp() { return HP; }
	int getAddMp() { return MP; }

	string getItemName() { return ItemName; }
	ItemType getItemType() { return itemType; }
	image* getImage() { return ItemImage; }
	RECT getRECT() { return ItemRECT; }

	ItemKind getItemKind() { return itemKind; }
};

