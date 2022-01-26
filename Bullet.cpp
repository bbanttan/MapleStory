#include "stdafx.h"
#include "Bullet.h"
#include "Character.h"
#include "MobManager.h"
#include "charEffect.h"

HRESULT Bullet::init()
{
	IMAGEMANAGER->addFrameImage("����", "�̹���/����Ʈ/�Ѿ˷�/����.bmp", 96, 18, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ȭ��", "�̹���/����Ʈ/�Ѿ˷�/ȭ��.bmp", 39, 14, 1, 2, true, RGB(255, 0, 255));

	return S_OK;
}

void Bullet::release()
{

}

void Bullet::update()
{
	/* ���� ������ ����ü���͸� ���鼭 ���࿡ ����ü ����ü ������ who���� ��, ���� ��ȣ�� �浹�Ҷ� 
	���Ϳ��� ����ü�� ���������� ������ hit���� �Լ��� �ߵ���Ų��.
	�׸��� ���� ��ǥ��ų�� �ü� ��ǥ��ų�� ����� ���� ���� ����̶� ����, �ü� ���ǹ��� �ִ�.*/
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); )
	{
		if (getDistance(_viBullet->x, _viBullet->y, _viBullet->sx, _viBullet->sy) >= 300)
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			if (_viBullet->who != -1)
			{
				RECT temp;
				if (M->_getvMob()[_viBullet->who]->getHP() >= 0)
				{
					if (IntersectRect(&temp, &M->_getvMob()[_viBullet->who]->getRECT(), &_viBullet->collision))
					{					
						if (C->getRL() == RIGHT)
						{
							eft->seven_blow(_viBullet->x + 60, _viBullet->y);
							M->_getvMob()[_viBullet->who]->setHIT(M_RIGHT, _viBullet->damageY, RND->getInt(C->getSTR()));
							_viBullet = _vBullet.erase(_viBullet);

						}
						else if (C->getRL() == LEFT)
						{
							eft->seven_blow(_viBullet->x + 4, _viBullet->y);
							M->_getvMob()[_viBullet->who]->setHIT(M_LEFT, _viBullet->damageY, RND->getInt(C->getSTR()));
							_viBullet = _vBullet.erase(_viBullet);
						}
						continue;
						//���� ����������� ���͸� ���������⿡ �Ʒ������ΰ��� ++_viBullet; �� �Ͷ߸��⶧���� ��Ƽ��
					}
				}
				else
				{
					_viBullet = _vBullet.erase(_viBullet);
					continue;
				}
			}
			if (_viBullet->direction == 1) {
				if (_viBullet->job == "����") ani_Bullet_right->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
				_viBullet->collision = RectMakeCenter(_viBullet->x + 45, _viBullet->y + 15, 100, 100);
			}
			else if (_viBullet->direction == -1) {
				if(_viBullet->job == "����") ani_Bullet_left->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
				_viBullet->collision = RectMakeCenter(_viBullet->x + 15, _viBullet->y + 15, 100, 100);
			}

			_viBullet->x += cosf(_viBullet->angle) * 10;
			if (_viBullet->who != -1)
			{
				if ((M->_getvMob()[_viBullet->who]->getRECT().top > _viBullet->y)||
					M->_getvMob()[_viBullet->who]->getRECT().bottom < _viBullet->y)
				{
					_viBullet->y += -sinf(_viBullet->angle) * 10;
				}
			}

			++_viBullet;
		}
	}
}

void Bullet::render()
{
	for (int i = 0; i < _vBullet.size(); ++i)
	{
		if (KEYMANAGER->isToggleKey('1'))
		{
			HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			HPEN oPen = (HPEN)SelectObject(getMemDC(), Pen);

			Rectangle(getMemDC(), _vBullet[i].collision);

			SelectObject(getMemDC(), oPen);
			DeleteObject(Pen);
		}

		if (_vBullet[i].direction == 1) {
			if (_vBullet[i].job == "����") _vBullet[i].img_Bullet->aniRender(getMemDC(), _vBullet[i].x, _vBullet[i].y, ani_Bullet_right);
			if (_vBullet[i].job == "�ü�") _vBullet[i].img_Bullet->frameRender(getMemDC(), _vBullet[i].x, _vBullet[i].y);
		}
		if (_vBullet[i].direction == -1) {
			if (_vBullet[i].job == "����") _vBullet[i].img_Bullet->aniRender(getMemDC(), _vBullet[i].x, _vBullet[i].y, ani_Bullet_left);
			if (_vBullet[i].job == "�ü�") _vBullet[i].img_Bullet->frameRender(getMemDC(), _vBullet[i].x, _vBullet[i].y);
		}
		
	}
}
