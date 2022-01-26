#include "stdafx.h"
#include "thief.h"
#include "MobManager.h"
#include "Character.h"
#include "charEffect.h"

void thief::Mob_Search(Character* c, MobManager* mm, charEffect* _eft)
{
	eft = _eft;

	c->setAddHpMp(0, -need_mp);

	if (c->getRL() == RIGHT) eft->seven_2(c->getX(), c->getY());
	if (c->getRL() == LEFT) eft->seven_1(c->getX(), c->getY());

	RECT attack_scale = RectMakeCenter(c->getX(), c->getY() - 15, 580, 170);
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