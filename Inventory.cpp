#include "stdafx.h"
#include "Inventory.h"
#include "Item.h"
#include "Character.h"

HRESULT Inventory::init()
{

	IMAGEMANAGER->addImage("������â", "�̹���/UI/������â/������âUI.bmp", 162, 304, true, RGB(255, 0, 255));

	_Visible = second_click = false;

	first_click_cnt = 0;
	select_slot = -100;

	x = WINSIZEX / 2 - (IMAGEMANAGER->findImage("������â")->getWidth() / 2);
	y = WINSIZEY / 2 - (IMAGEMANAGER->findImage("������â")->getHeight() / 2);

	for (int i = 0; i < 20; i++)
	{
		islot[i].itemNum = 0;
		islot[i].slot = new Item;
	}
	return S_OK;
}

void Inventory::release()
{
}

void Inventory::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		_Visible = !_Visible;
	}
	if (_Visible)
	{
		Double_Click();
	}
	first_click_cnt > 0 ? first_click_cnt-- : first_click_cnt = 0;
}

void Inventory::render()
{
	if (_Visible) 
	{
		Inventory_Visible();
	}
}

void Inventory::Inventory_Visible()
{
	IMAGEMANAGER->findImage("������â")->render(getMemDC(), CAMERA->getcamX() + x, CAMERA->getcamY() + y);
	
	for (int i = 0; i < 5; i++)
	{
		for (int e = 0; e < 4; e++)
		{	
			if (islot[(i * 4) + e].itemNum == 0) continue;

			islot[(i * 4) + e].rect = RectMake(
				(CAMERA->getcamX() + x) + 22 + (e * 35) - (IMAGEMANAGER->findImage(islot[(i * 4) + e].slot->getItemName())->getWidth() / 2),
				(CAMERA->getcamY() + y) + 94 + (i * 35) - (IMAGEMANAGER->findImage(islot[(i * 4) + e].slot->getItemName())->getHeight() / 2),
				25,25
			);

			IMAGEMANAGER->findImage(islot[(i * 4) + e].slot->getItemName())->render(getMemDC(),
				(CAMERA->getcamX() + x) + 22 + (e * 35) - (IMAGEMANAGER->findImage(islot[(i * 4) + e].slot->getItemName())->getWidth() / 2),
				(CAMERA->getcamY() + y) + 94 + (i * 35) - (IMAGEMANAGER->findImage(islot[(i * 4) + e].slot->getItemName())->getHeight() / 2)
			);	
			if (islot[(i * 4) + e].slot->getItemType() != WEAPON)
			{
				char str[128];
				sprintf_s(str, "%d", islot[(i * 4) + e].itemNum);
				TextOut(getMemDC(),
					((CAMERA->getcamX() + x) + 22 + (e * 35) - (IMAGEMANAGER->findImage(islot[(i * 4) + e].slot->getItemName())->getWidth() / 2)),
					((CAMERA->getcamY() + y) + 94 + (i * 35) - (IMAGEMANAGER->findImage(islot[(i * 4) + e].slot->getItemName())->getHeight() / 2)) + 10,
					str, strlen(str)
				);
			}		
		}
	}
}

bool Inventory::Item_add(Item* _itemInfo, int _inum)
{
	int e;

	if (getLeaveSlotNumCheck() > _inum)
	{
		for (int i = 0; i < _inum; i++)
		{
			for (e = 0; e < 20; e++)
			{
				if (islot[e].slot->getItemName() == _itemInfo->getItemName())
				{
					if (islot[e].itemNum < MAXNUM)
					{
						islot[e].itemNum++;
						e = 100; //e for�� Ż��!
					}
				}
			}
			if (e == 20)
			{
				int Leave = getLeaveSlotCheck();

				islot[Leave].slot = _itemInfo;
				islot[Leave].slot->setSlotNum(Leave);
				islot[Leave].itemNum = 
					((_itemInfo->getItemType() == CONSUME) || (_itemInfo->getItemType() == ETC )) + 
					(_itemInfo->getItemType() == WEAPON) * 200;
				
				if (_itemInfo->getItemType() == WEAPON) return true;	//����϶� �׳� ��������
			}
		}
	}
	else
	{
		return false;
		//�����ڸ��� �����
	}
}

void Inventory::Double_Click()
{
	if (first_click_cnt == 0)
	{
		for (int i = 0; i < 20; i++)
		{	//�����۽����� �ѹ� ��������
			if (PtInRect(&islot[i].rect, PointMake(CAMERA->getcamX() + _ptMouse.x, CAMERA->getcamY() + _ptMouse.y)) &&
				KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && 
				(islot[i].slot->getItemType() == WEAPON || islot[i].slot->getItemType() == CONSUME))
			{
				first_click_cnt = 30;
				select_slot = islot[i].slot->getSlotNum();
				break;
			}
		}
	}
	if (first_click_cnt > 0 && first_click_cnt <= 30)	//�ι���������
	{
		if (PtInRect(&islot[select_slot].rect, PointMake(CAMERA->getcamX() + _ptMouse.x, CAMERA->getcamY() + _ptMouse.y)) &&
			KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (islot[select_slot].slot->getItemType() == WEAPON)
			{
				Item* tempItem;
				tempItem = new Item;

				tempItem = islot[select_slot].slot;

				string _job;

				if (islot[select_slot].slot->getItemName() == "��")					_job = "�ʺ���";
				else if (islot[select_slot].slot->getItemName() == "��Ǫ")			_job = "����";
				else if (islot[select_slot].slot->getItemName() == "���Ͼ�")			_job = "����";
				else if (islot[select_slot].slot->getItemName() == "������")			_job = "�ü�";
				else if (islot[select_slot].slot->getItemName() == "��񳪹�������") _job = "������";

				c->setCharacterImage(_job);
				c->setSTR(islot[select_slot].slot->getSTR());
				setItemDelete(select_slot);
				Item_add(c->getEquit(), 200);
				c->setEquit(tempItem);
			}
			if (islot[select_slot].slot->getItemType() == CONSUME)
			{
				c->setAddHpMp(islot[select_slot].slot->getAddHp(), islot[select_slot].slot->getAddMp());
				setMinusNum(islot[select_slot].slot->getItemName(), 1);
			}
			return;
		}
	}
	else
	{
		select_slot = -100;
	}
}


int Inventory::getLeaveSlotCheck() //�����ִ� ����üũ
{
	for (int i = 0; i < 20; i++)
	{
		if (islot[i].itemNum == 0) return i;
	}
	return -1;
}

int Inventory::getLeaveSlotNumCheck() //���� �� ���� ����üũ 200 * 20 = 4000 �� ��������
{
	int sum = 0;
	for (int i = 0; i < 20; i++)
	{
		sum += islot[i].itemNum;
	}
	return (4000 - sum);
}

int Inventory::getSameItemCheck(string _iname) // �������ִ��� üũ
{
	for (int i = 0; i < 20; i++)
	{
		if (islot[i].slot->getItemName() == _iname)
		{
			return i;
		}
	}
	return -1;
}

bool Inventory::getDAGGERItemCheck() // ���� ������ ���������ִ°�
{
	for (int i = 0; i < 20; i++)
	{
		if (islot[i].slot->getItemKind() == DAGGER)
		{
			return true;
		}
	}
	return false;
}
bool Inventory::getARROWItemCheck() // ���� ������ ���������ִ°�
{
	for (int i = 0; i < 20; i++)
	{
		if (islot[i].slot->getItemKind() == ARROW)
		{
			return true;
		}
	}
	return false;
}
void Inventory::setMinusNum(string _iname, int _num) // ���� ������ ���������ִ°�
{
	for (int o = 0; o < _num; o++)
	{
		for (int i = 0; i < 20; i++)
		{
			if (islot[i].slot->getItemName() == _iname)
			{
				islot[i].itemNum--;
				break;
			}
		}
	}
	return;
}

void Inventory::setItemDelete(int _slotnum) // �����ۻ���
{
	islot[_slotnum].itemNum = 0;
}