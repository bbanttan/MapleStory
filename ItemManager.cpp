#include "stdafx.h"
#include "ItemManager.h"
#include "Map.h"
#include "Character.h"
#include "Inventory.h"

HRESULT ItemManager::init()
{
	//��Ÿ
	IMAGEMANAGER->addImage("�׺�", "�̹���/������/�������/�׺�.bmp", 26, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Թ����ǰ�", "�̹���/������/�Թ���/�Թ����ǰ�.bmp", 30, 27, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޼�", "�̹���/������/����/�޼�.bmp", 25, 24, true, RGB(255, 0, 255));

	//����
	IMAGEMANAGER->addImage("��", "�̹���/������/�ʺ���/��.bmp", 31, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ǫ", "�̹���/������/����/��Ǫ.bmp", 34, 31, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���Ͼ�", "�̹���/������/����/���Ͼ�.bmp", 26, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "�̹���/������/�ü�/������.bmp", 30, 31, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��񳪹�������", "�̹���/������/������/��񳪹�������.bmp", 33, 32, true, RGB(255, 0, 255));

	//ǥâ, ȭ��
	IMAGEMANAGER->addImage("����������", "�̹���/������/����/����.bmp", 25, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ȭ��", "�̹���/������/�ü�/ȭ��.bmp", 32, 32, true, RGB(255, 0, 255));

	//����
	IMAGEMANAGER->addImage("�Ķ�����", "�̹���/������/����/�Ķ�����.bmp", 27, 27, true, RGB(255, 0, 255));

	return S_OK;
}

void ItemManager::release()
{

}

void ItemManager::update()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); )
	{
		if ((*_viItem)->EatSign())
		{
			_viItem = _vItem.erase(_viItem);
		}
		else
		{
			(*_viItem)->update();

			if (KEYMANAGER->isOnceKeyDown('A') && (*_viItem)->getLanding() == false && (*_viItem)->returnEat() == false)
			{
				if (_inven->getLeaveSlotNumCheck() > (*_viItem)->getNum())
				{
					RECT temp;
					if (IntersectRect(&temp, &c->getRECT(), &(*_viItem)->getRECT()))
					{
						(*_viItem)->Eat();	//�Ծ��ٴ� ��ȣ�� ������Ŭ�������� ����
						_inven->Item_add((*_viItem), (*_viItem)->getNum());
					}
				}
			}
			if ((*_viItem)->returnEat())
			{
				(*_viItem)->setX((*_viItem)->getX() + ((c->getX() - (*_viItem)->getX())) * 0.05f);
				(*_viItem)->setY((*_viItem)->getY() + ((c->getY() - (*_viItem)->getY())) * 0.05f);
			}
			++_viItem;
		}
	}
}

void ItemManager::render()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render();
	}
}

void ItemManager::Item_all_clear()
{
	_vItem.clear();
}
