#include "stdafx.h"
#include "chobo.h"
#include "MobManager.h"
#include "Character.h"
#include "Map.h"

void chobo::Mob_Search(Character* c, MobManager* mm)
{
	RECT attack_scale = RectMakeCenter(c->getX(), c->getY() - 15, 145, 60);
	//���� ����� ����ã��
	for (int i = 0; i < mm->_getvMob().size(); i++)
	{
		if (mm->_getvMob()[i]->getHP() <= 0) continue;

		RECT tempRECT;
		if (IntersectRect(&tempRECT, &attack_scale, &mm->_getvMob()[i]->getRECT()))
		{
			int rich = getDistance(c->getX(), c->getY(), mm->_getvMob()[i]->getRECT().left + (mm->_getvMob()[i]->getRECT().right - mm->_getvMob()[i]->getRECT().left) / 2, mm->_getvMob()[i]->getRECT().top + (mm->_getvMob()[i]->getRECT().bottom - mm->_getvMob()[i]->getRECT().top) / 2);

			if (c->getRL() == RIGHT && (c->getX() - mm->_getvMob()[i]->getX()) < 0)	//������������ ����������
			{
				if (c->getTemp() > rich)
				{
					c->setTemp(rich);
					c->setWho(i);
				}
			}
			else if (c->getRL() == LEFT && (c->getX() - mm->_getvMob()[i]->getX()) > 0)			//���������� ����������
			{
				if (c->getTemp() > rich)
				{
					c->setTemp(rich);
					c->setWho(i);
				}
			}
		}
	}
}

//�� �Լ��� ���ݸ���� �� ������ ��ǿ� �����ϴ� �Լ��ε� who�� ������ ���� ��ȣ�� ĳ����(C)���� �������� �����ؼ�
//���Ŵ����� �¾Ҵٴ� ��ȣ�� �����ش�.
void chobo::Mob_Knock(Character* c, MobManager* mm, Map* map)
{
	if (c->getWho() != -1)
	{
		if (mm->_getvMob()[c->getWho()]->getJumpOk() == true)
		{
			mm->_getvMob()[c->getWho()]->setY(map->mapExplorer(mm->_getvMob()[c->getWho()]->getX(), mm->_getvMob()[c->getWho()]->getY(), 150.0f));
		}
		if (c->getRL() == RIGHT)
		{
			mm->_getvMob()[c->getWho()]->setHIT(M_RIGHT, 0, RND->getInt(c->getSTR()));
		}
		else if (c->getRL() == LEFT)
		{
			mm->_getvMob()[c->getWho()]->setHIT(M_LEFT, 0, RND->getInt(c->getSTR()));
		}

		c->setTemp(1000);
		c->setWho(-1);
	}
}