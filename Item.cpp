#include "stdafx.h"
#include "Item.h"
#include "Map.h"

HRESULT Item::init(string _iname)
{
	ItemName = _iname;

	ItemNum = 200;

	alpha = 255;

	field_drop = false;

	Item_Info();

	return S_OK;
}

HRESULT Item::init(string _iname, int _inum)
{
	ItemName = _iname;

	ItemNum = _inum;

	alpha = 255;

	field_drop = false;

	Item_Info();

	return S_OK;
}

HRESULT Item::init(string _iname, int _inum, float _x, float _y, Map* _m)
{
	ItemName = _iname;

	ItemNum = _inum;

	alpha = 255;

	field_drop = LANDING = true;

	x = _x;
	y = _y;

	angle = 0.0f;

	_map = _m;

	Item_Info();

	return S_OK;
}

void Item::release()
{

}

void Item::update()
{
	if (LANDING)
	{
		if (field_drop)	//�򱸷�(������ �ѷ����� �Ҹ�)
		{
			if (gra >= 5.0f)
			{
				char mapname[128];
				sprintf_s(mapname, "%s����", _map->getCurrentMap());

				for (int i = y - 3; i < y + 3; i++)
				{
					COLORREF mapland = GetPixel(IMAGEMANAGER->findImage(mapname)->getMemDC(), x, i);

					if (GetRValue(mapland) == 255 && GetGValue(mapland) == 0 && GetBValue(mapland) == 255)
					{
						LANDING = false;
						y = i - (IMAGEMANAGER->findImage(ItemName)->getHeight()/2);
						break;
					}
				}
			}
			y += (gra += 0.2f) - 5.0f;
			ItemRECT = RectMakeCenter(x, y, 32, 32);
		}
	}
	else
	{
		//�յ� ���ٴ�
		if (eat == false)
		{
			angle += 5.0f;
			y2 = y + -sinf(angle * (PI / 180)) * 2;
			ItemRECT = RectMakeCenter(x, y2, 32, 32);
		}
		else
		{
			alpha -= 5;
			if (alpha <= 0) eatSign = true;
			ItemRECT = RectMakeCenter(x, y, 32, 32);
		}
	}
}

void Item::render()
{
	IMAGEMANAGER->findImage(ItemName)->alphaRender(getMemDC(), ItemRECT.left, ItemRECT.top, alpha);
	if (KEYMANAGER->isToggleKey('1'))
	{
		HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oPen = (HPEN)SelectObject(getMemDC(), Pen);

		Rectangle(getMemDC(), ItemRECT);

		SelectObject(getMemDC(), oPen);
		DeleteObject(Pen);
	}
}

void Item::Item_Info()	//������ ����
{
	ItemImage = IMAGEMANAGER->findImage(ItemName);

	eat = eatSign = false;

	if (ItemName == "�޼�")
	{
		
	}
	else if (ItemName == "�Թ����ǰ�")
	{
		itemType = ETC;
	}
	else if (ItemName == "�׺�")
	{
		itemType = ETC;
	}
	else if (ItemName == "ǥâ")
	{
		itemType = ETC;
		itemKind = DAGGER;
	}
	else if (ItemName == "ȭ��")
	{
		itemType = ETC;
		itemKind = ARROW;
	}
	else if (ItemName == "��Ǫ")
	{
		itemKind = SWORD;
		itemType = WEAPON;
		STR = 80;
	}
	else if (ItemName == "���Ͼ�")
	{
		itemKind = ADEA;
		itemType = WEAPON;
		STR = 400;
	}
	else if (ItemName == "������")
	{
		itemKind = BOW;
		itemType = WEAPON;
		STR = 40;
	}
	else if (ItemName == "��񳪹�������")
	{
		itemKind = STAFF;
		itemType = WEAPON;
		STR = 80;
	}
	else if (ItemName == "��")
	{
		itemKind = SWORD;
		itemType = WEAPON;
		STR = 100;
	}
	else if (ItemName == "�Ķ�����")
	{
		itemType = CONSUME;
		HP = 0;
		MP = 200;
	}
}
