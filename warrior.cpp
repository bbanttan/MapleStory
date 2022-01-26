#include "stdafx.h"
#include "warrior.h"
#include "MobManager.h"
#include "Character.h"
#include "Map.h"
#include "charEffect.h"

void warrior::update()
{
	if (cnt != 0)
	{
		if ((cnt % 10) == 0)
		{
			if (Who_Target_Mob[s] != -1000)	//����Who_Target_Mob[]�迭�� ���� -1000 != ��, ��������������
			{								//�������� �Լ��ߵ�
				Mob_Knock(_c, _mm, _map, s);
				eft->blust_blow(_mm->_getvMob()[Who_Target_Mob[s]]->getX(), _mm->_getvMob()[Who_Target_Mob[s]]->getY()-30);
				s++;
			}
		}
		cnt--;
	}

	//�̳𶧹��� ����(20,12,24 �� 10��~ 25�� ���� 2��, 25�� ��ħ 11��~1��)���� �� �׷����� ������ �𸣰ڴٰ�
	//�ᱹ ȥ�ڸ��� ������ ��ħ ������ ��, update�Լ��� ĳ���ͳ����� ��������, �ֳ��ϸ� ������ ���ʿ��ִ³���� ���ٴ� �ణ��
	//���͹��� ������ �¾ƾ��ϱ⶧��, �׷��� �� ������ ������ ��ǿ��ٰ��� �� �Լ�(Mob_Knock)�� �־���� cnt�� 30�̵Ǵ� �Լ���
	//�� Mob_Knock�Լ� �Ʒ����ٰ� �־����� �׷��� ��� ���� ���°��� , update�� ��� �� �Լ��� ���ǿ� ������ ȣ���ϰ��ְ�,
	//���ݳ����� ��ǿ��� �̰� ȣ���ϴϱ� ���� �̻��� �ȸ¾Ƽ� ���̳����Ű���.
}

void warrior::render()
{

}

/* �켱 ������ ����Ʈ�� 3������ ���� ���ٴ� �����ϰ� �ϱ����� ũ�� �ٱ��ʿ� q for��, ���ʿ� ������.size��ŭ���� �ϴ� i for��
�� �������� 3�������� �����ϱ����� ����� who�� ���� �����մ� i�� ������ ���ϴ� r for�����ִ�.*/

void warrior::Mob_Search(Character* c, MobManager* mm, Map* map, charEffect* _eft)
{
		c->setAddHpMp(0, -need_mp);
		cnt = s = r = add_attack_scale = 0;

		_c = c;
		_mm = mm;
		_map = map;
		eft = _eft;

		Who_Target_Mob[0] = Who_Target_Mob[1] = Who_Target_Mob[2] = -1000;
		Dis_Target_Mob[0] = Dis_Target_Mob[1] = Dis_Target_Mob[2] = -1000;

		RECT attack_scale;

		eft->blust(c->getX(), c->getY());

		//���� ����� ����ã��
		for (int q = 0; q < 3; q++)
		{
			tempRich = 10000;

			//���� �ѹ��̻� ���Ҵµ� �迭���� -1000�̶�°� ��ã�Ҵٴ� ���ϱ� ����(�ڿ��ִ� ��Ʈã������ �߰���)
			if (q != 0 && Who_Target_Mob[0] == -1000) return;

			//���� ���鿡 ���� for��
			for (int i = 0; i < mm->_getvMob().size(); i++)
			{
				if (mm->_getvMob()[i]->getHP() <= 0) continue;

				//�迭���� ���� �迭�� ��ȣ�� �������� ã��for��
				for (r = 0; r < 3; r++)
				{
					if (Who_Target_Mob[r] == i)
					{
						break;
					}
				}
				//���� r�� 3�̾ƴ϶�°� ���� �迭�� �ִ³��� �ִٴ¶��̹Ƿ� i for���� ��Ƽ��
				if (r != 3) continue;

				//���� q for���� �ѹ��̻��� �������� ��Ʈ�� ������ �÷��ش�.
				if (q != 0) add_attack_scale = 200;

				attack_scale = RectMakeCenter(c->getX(), c->getY() - 15, 145 + add_attack_scale, 60);

				RECT tempRECT;
				if (IntersectRect(&tempRECT, &attack_scale, &mm->_getvMob()[i]->getRECT()))
				{
					int rich = getDistance(c->getX(), c->getY(), mm->_getvMob()[i]->getRECT().left + (mm->_getvMob()[i]->getRECT().right - mm->_getvMob()[i]->getRECT().left) / 2, mm->_getvMob()[i]->getRECT().top + (mm->_getvMob()[i]->getRECT().bottom - mm->_getvMob()[i]->getRECT().top) / 2);

					if (c->getRL() == RIGHT && (c->getX() - mm->_getvMob()[i]->getX()) < 0)	//������������ ����������
					{
						if (tempRich > rich)
						{
							tempRich = rich;
							tempWho = i;
						}
					}
					else if (c->getRL() == LEFT && (c->getX() - mm->_getvMob()[i]->getX()) > 0)			//���������� ����������
					{
						if (tempRich > rich)
						{
							tempRich = rich;
							tempWho = i;
						}
					}
				}
			}
			if (tempRich != 10000)//���� i for���� �� ������ tempRich�� 10000�� �ƴҶ� �����Ѵ�.
			{
				for (int i = 0; i < 3; i++)
				{
					if (Who_Target_Mob[i] == -1000)
					{
						Who_Target_Mob[i] = tempWho;
						Dis_Target_Mob[i] = tempRich;
						break;
					}
				}
			}
		}
}

void warrior::Mob_Knock(Character* c, MobManager* mm, Map* map, int y)
{

	if (mm->_getvMob()[Who_Target_Mob[y]]->getJumpOk() == true)
	{
		mm->_getvMob()[Who_Target_Mob[y]]->setY(map->mapExplorer(mm->_getvMob()[Who_Target_Mob[y]]->getX(), mm->_getvMob()[Who_Target_Mob[y]]->getY(), 150.0f));
	}
	if (c->getRL() == RIGHT)
	{
		mm->_getvMob()[Who_Target_Mob[y]]->setHIT(M_RIGHT, 0, RND->getInt(c->getSTR()));
	}
	else if (c->getRL() == LEFT)
	{
		mm->_getvMob()[Who_Target_Mob[y]]->setHIT(M_LEFT, 0, RND->getInt(c->getSTR()));
	}
}