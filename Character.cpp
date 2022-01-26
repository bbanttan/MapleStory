#include "stdafx.h"
#include "Character.h"
#include "Map.h"
#include "MobManager.h"
#include "Inventory.h"

HRESULT Character::init()
{
	_chobo = new chobo;
	_warrior = new warrior;
	_thief = new thief;
	_archer = new archer;
	_magic = new magic;

	eft = new charEffect;
	eft->init();

	_bullet = new Bullet;
	_bullet->init();

	dmg = new damage;
	dmg->init();

	//ĳ���� ü��, ����, ü�¸��� ������� ��������
	hp = mhp = error_hp = 50.0f;
	mp = mmp = error_mp = 200.0f;

	//�ִϸ��̼� ���͹�
	cnt = hitcnt = correctionX = correctionY = attackPattern = 0;

	//�ִϸ��̼� ����
	loop = knock = false;

	//ĳ���� ���� ���ӽ���� ��ǥ����
	x = 214.1;
	y = 1026.7;

	//
	temp = 10000;
	who = -1;

	alpha = 255;

	//�߷°� �����Ҷ� ������ 0���� �ʱ�ȭ
	gravity = jump_power = 0.0f;

	//���������ʱ�ȭ
	RL = RIGHT;
	WJASL = STANDING;

	//ĳ���� �̹����ҷ�����
	character_img = new image;
	character_img->init("�̹���/ĳ����/�ʺ���ĳ����.bmp", 456, 1460, 4, 20, true, RGB(0, 255, 0));
	character_img->setFrameY(10);
	
	IMAGEMANAGER->addFrameImage("����", "�̹���/ĳ����/����ĳ����.bmp", 456, 1460, 4, 20, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("����", "�̹���/ĳ����/����ĳ����.bmp", 456, 1460, 4, 20, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("�ü�", "�̹���/ĳ����/�ü�ĳ����.bmp", 456, 1460, 4, 20, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("������", "�̹���/ĳ����/������ĳ����.bmp", 456, 1460, 4, 20, true, RGB(0, 255, 0));
	IMAGEMANAGER->addFrameImage("�ʺ���", "�̹���/ĳ����/�ʺ���ĳ����.bmp", 456, 1460, 4, 20, true, RGB(0, 255, 0));

	character_head = new image;
	character_head->init("�̹���/ĳ����/�Ӱ�����.bmp", 320, 138, 5, 3, true, RGB(0, 255, 0));
	character_head->setFrameY(0);
	character_head->setFrameX(0);

	CurrentEquit = new Item;
	CurrentEquit->init("��");

	STR = CurrentEquit->getSTR();

	_job = "�ʺ���";

	return S_OK;
}

void Character::release()
{

}

void Character::update()
{
	left_isOnceKeyDown  = KEYMANAGER->isOnceKeyDown(VK_LEFT);
	left_isStayKeyDown  = KEYMANAGER->isStayKeyDown(VK_LEFT);
	left_isOnceKeyUp    = KEYMANAGER->isOnceKeyUp(VK_LEFT);
	right_isOnceKeyDown = KEYMANAGER->isOnceKeyDown(VK_RIGHT);
	right_isStayKeyDown = KEYMANAGER->isStayKeyDown(VK_RIGHT);
	right_isOnceKeyUp   = KEYMANAGER->isOnceKeyUp(VK_RIGHT);

	if (error_hp != hp)
	{
		error_hp += (hp - error_hp) * 0.2f;
	}
	if (error_mp != mp)
	{
		error_mp += (mp - error_mp) * 0.2f;
	}
	if (hp >= mhp) hp = mhp;
	if (hp <= 0)   hp = 0;
	if (mp >= mmp) mp = mmp;
	if (mp <= 0)   mp = 0;

	if(WJASL != ATTACK)
	{
		if (right_isOnceKeyDown && medal == false)					//������Ű �ѹ��� ����üũ�� �����϶�
		{		
			RL = RIGHT;												//������¸� RIGHT
			cnt = 0;												//�ִϸ��̼� ���͹� 0
			frame = 0;												//�ִϸ��̼� ������ 0
			loop = false;											//�ִϸ��̼� �ڵ��ݺ� FALSE
		}
		if (left_isOnceKeyDown && medal == false)					//����Ű �ѹ��� ����üũ�� �����϶�
		{		
			RL = LEFT;												//������¸� RIGHT
			cnt = 0;												//�ִϸ��̼� ���͹� 0
			frame = 0;												//�ִϸ��̼� ������ 0
			loop = false;											//�ִϸ��̼� �ڵ��ݺ� FALSE
		}

		if (right_isStayKeyDown)								    //������Ű
		{												
			if (WJASL != JUMP && medal == false)	WJASL = WALK;
		}
		if (left_isStayKeyDown)										//����Ű
		{												
			if (WJASL != JUMP && medal == false)	WJASL = WALK;
		}

		//���ĵ��� �Ǵ� ���ǵ�
		if ((right_isOnceKeyUp || left_isOnceKeyUp) && medal == false)
		{

			if (left_isStayKeyDown || right_isStayKeyDown)
			{
				if (left_isStayKeyDown)  RL = LEFT;
				if (right_isStayKeyDown) RL = RIGHT;
				WJASL = WALK;
			}
			else
			{
				cnt = 0;
				frame = 0;
				loop = false;
				WJASL = STANDING;
			}
		}

		//���� ��ٸ�(ĳ���Ϳ� ���� ��ٸ��� ��Ʈ)�� �������
		if ((body.right > collision_ropeladder.left && body.left < collision_ropeladder.right &&
			body.top < collision_ropeladder.bottom && body.bottom > collision_ropeladder.top)&&
			collision_portal == false)
		{
			//���� ��� �ۿ��ϴµ� ���� �ö󰡴ٰ� ���� ������ �ű⼭ �����⶧����
			//��ٸ��� ��Ʈ top���� ���� ��Ʈ��ü������ 0.2�� �����Ǵ� ���̸� ���� �� y�࿡ ����������
			//���� �����ʰ��ϱ����� ����
			float downkey_possible = 
				collision_ropeladder.top + (collision_ropeladder.bottom - collision_ropeladder.top) * 0.2f;
			
			//�޴޷������� ���϶�
			if (medal)
			{
				//���� ��������� gravity >= jump_power, downkey_possible < y ĳ����y���� �� �������� Ŭ�� ��, �Ʒ���������
				//�� ���� ����ϱ����� gravity = 0.0f ���� �ϰ�
				//�ݴ�δ� ���� ������� �ʱ����� gravity = -1.0f ������
				if (downkey_possible < y)		gravity = 0.0f;	 
				else if (downkey_possible > y)  gravity = -1.0f;

				if (KEYMANAGER->isStayKeyDown(VK_UP))
				{
					y -= 2;
					cnt++;	//�ִϸ��̼� ���͹�
				}
				else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
				{
					y += 2;
					cnt++;
				}
				if (KEYMANAGER->isOnceKeyDown(VK_SPACE))	//��ٸ����� �����ϰ��� �Ҷ�
				{
					if (left_isStayKeyDown)
					{
						spd = -MAXSPD;
						RL = LEFT;
						medal = false;
						jump_power = 3.0f;
					}
					if (right_isStayKeyDown)
					{
						spd = MAXSPD;
						RL = RIGHT;
						medal = false;
						jump_power = 3.0f;
					}
				}
			}

			//�޴޷������� �����϶� ��Ű�� �Ʒ�Ű�� ��������
			if (((KEYMANAGER->isStayKeyDown(VK_UP) && downkey_possible < y) || (KEYMANAGER->isStayKeyDown(VK_DOWN) && downkey_possible > y)) && medal == false)
			{
				medal = true;				//�޴޸��� true�� �����.
				spd = jump_power = 0.0f;	//����, ������ 0���� �ʱ�ȭ
				gravity = -1.0f;			//�� �ȴ���Ϸ���
				cnt = frame = 0;			//���͹�, ������ 0
				x = collision_ropeladder.left + ((collision_ropeladder.right - collision_ropeladder.left)/2);
				//��ٸ������ ĳ������ x���� ������Ų��.
			}	
		}
		else
		{
			medal = false;
		}

		//����
		if (KEYMANAGER->isStayKeyDown(VK_SPACE) && WJASL != JUMP && jump_power == 0.0f && medal == false)
		{
			jump_power = JUMP_POWER;
		}

		//gravity�� 0���� Ŀ���� ���¸� �������·� �ٲ۴�.
		if (gravity > 0.0f)
		{
			WJASL = JUMP;
		}
	}
	//����(ZŰ)
	if (KEYMANAGER->isStayKeyDown(0x5A) && WJASL != ATTACK && medal == false)
	{	
		if ((_job == "����" && mp > _warrior->getNeedMP()) || (_job == "������" && mp > _magic->getNeedMP()) ||
			(_job == "����" && mp > _thief->getNeedMP()) || (_job == "�ü�" && mp > _archer->getNeedMP()) || (_job == "�ʺ���"))
		{
			WJASL = ATTACK;
			attackPattern = RND->getInt(3) + 1;
			cnt = frame = 0;

			if (_job == "�ʺ���") _chobo->Mob_Search(c, MM);
			if (_job == "����") _warrior->Mob_Search(c, MM, map, eft);
			if (_job == "������") _magic->Mob_Search(c, MM, map, eft);
			if (_job == "����")
			{
				_thief->setSx(x);
				_thief->setSy(y - 20);
				_thief->Mob_Search(c, MM, eft);
			}
			else if (_job == "�ü�")
			{
				_archer->setSx(x);
				_archer->setSy(y - 20);
				_archer->Mob_Search(c, MM);
			}
		}
	}

	//�����Լ�
	accNacc();

	x += spd;
	if(medal == false) gravity += GRAVITY;

	//�߷� ���ܼӵ� �������ִ� ����
	if ((gravity - jump_power) >= 7.0f) { gravity = 7.0f; jump_power = 0.0f; }

	//���� �Լ�
	Landing();

	//��� �ִϸ��̼�
	anime();

	//���� ĳ���� �����
	aggro();

	//�ǰݵ��������°�
	blow();

	eft->update();

	//�����ú���Ʈ
	if (_job == "����") _warrior->update();

	//����Ŭ��
	if (_job == "������") _magic->update();

	//��Ű����
	if(_job == "����" || _job == "�ü�") _bullet->update();

	hitcnt != 0 ? hitcnt-- : hit = false;
	hitcnt != 0 ? alpha = 150 : alpha = 255;

	//������������Ʈ
	dmg->update();

	y += (gravity - jump_power)*(medal == false);

	body = RectMakeCenter(x, y, C_WIDTH, C_HEIGHT);

	if (collision_portal == true) collision_portal = false;
}

void Character::render()
{
	if (KEYMANAGER->isToggleKey('1'))
	{
		HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oPen = (HPEN)SelectObject(getMemDC(), Pen);

		Rectangle(getMemDC(), body);
		RectangleMakeCenter(getMemDC(), x, y - 37, 39, 37);

		SelectObject(getMemDC(), oPen);
		DeleteObject(Pen);
	}
	
	if ((WJASL == JUMP || WJASL == ATTACK) && medal == false)
	{
		character_head->alpha_frameRender(getMemDC(),
			x - (character_head->getFrameWidth() / 2) + ((RL==LEFT) * -(3.0f)) + ((RL == RIGHT) * (3.0f)) + correctionX,
			y - 62 + correctionY, alpha);
	}
	character_img->alpha_frameRender(getMemDC(), x - (character_img->getFrameWidth()/2), y - 49, alpha);
	if (WJASL == STANDING || WJASL == WALK || medal == true)
	{
		character_head->alpha_frameRender(getMemDC(),
			x - (character_head->getFrameWidth() / 2) + ((RL == LEFT) * -(3.0f) * ((medal==false) + (medal)*0)) + ((RL == RIGHT) * (3.0f) * ((medal==false) + (medal) * 0)),
			y - 60 + correctionY, alpha);
	}
	dmg->render();
	if(_job == "����") _warrior->render();
	if(_job == "����" || _job == "�ü�") _bullet->render();
	eft->render();
}

//���� �Լ�
void Character::accNacc()
{
	if (RL == RIGHT && right_isStayKeyDown && medal == false)
	{
		spd += ACCNACC * (((gravity > 0.0f) * JUMPACC) + ((gravity == 0.0f) * 1.0f));
		if (spd >= MAXSPD) spd = MAXSPD;
	}
	if (RL == LEFT && left_isStayKeyDown && medal == false)
	{
		spd -= ACCNACC * (((gravity > 0.0f) * JUMPACC) + ((gravity == 0.0f) * 1.0f));
		if (spd <= -MAXSPD) spd = -MAXSPD;
	}
	if (spd != 0.0f && WJASL != WALK && WJASL != JUMP)
	{
		if (spd > 0.0f)
		{
			spd -= ACCNACC * (((gravity > 0.0f) * JUMPACC) + ((gravity == 0.0f) * 2.0f));
			if (spd <= 0.0f) spd = 0.0f;
		}
		else if (spd < 0.0f)
		{
			spd += ACCNACC * (((gravity > 0.0f) * JUMPACC) + ((gravity == 0.0f) * 2.0f));
			if (spd >= 0.0f) spd = 0.0f;
		}
	}
}

//������ �Լ�
void Character::Landing()
{
	char str[128];
	sprintf_s(str, "%s����", map->getCurrentMap());

	//-2 +2 �� �����º��� �۾ƾ���. �ȱ׷� ������ �ȵ�
	if (jump_power <= gravity)
	{
		for (int i = ((int)y + (C_HEIGHT / 2)) - 4; i < ((int)y + (C_HEIGHT / 2)) + 4; ++i)
		{
			COLORREF landColor = GetPixel(IMAGEMANAGER->findImage(str)->getMemDC(), x, i);

			int r = GetRValue(landColor);
			int g = GetGValue(landColor);
			int b = GetBValue(landColor);

			if (r == 255 && g == 0 && b == 255)
			{
				if (gravity > GRAVITY)
				{
					if (WJASL != ATTACK) WJASL = STANDING;
					jump_power = 0.0f;
				}
				if (medal)	//�޴޷��ִٰ� �� ���� ������ �������
				{
					if (right_isStayKeyDown)	 RL = RIGHT;
					else if (left_isStayKeyDown) RL = LEFT;
					WJASL = STANDING;
					cnt = frame = 0;
					loop = false;
				}

				medal = false;
				gravity = 0.0f;
				y = (float)i - (C_HEIGHT / 2);

				break;
			}
		}
	}
	//��
	COLORREF wallColor = GetPixel(IMAGEMANAGER->findImage(str)->getMemDC(), x + ((RL == RIGHT)*(C_WIDTH/2)) + ((RL == LEFT)*(-C_WIDTH / 2)), y);

	if (GetRValue(wallColor) == 0 && GetGValue(wallColor) == 0 && GetBValue(wallColor) == 255)
	{
		spd = 0.0f;
		x = x + ((RL == RIGHT)*(-1)) + (RL == LEFT);
	}
}

//�ִϸ��̼�
void Character::anime()
{
	if (RL == RIGHT && medal == false)
	{
		character_head->setFrameY(0);
		//������ ���ĵ� �̹���
		if (WJASL == STANDING)
		{
			character_img->setFrameY(10);

			correctionY = 0;		 //�Ӹ� ������

			if (!(cnt % 40))
			{
				cnt = 0;
				character_img->setFrameX(frame);
				frame = frame + (loop == false) + ((loop == true) * -1);
				if (frame >= 2 || frame == 0)
				{
					loop = !loop;
				}
			}
		}
		if (WJASL == WALK)	//������ �ȴ� �̹���
		{
			character_img->setFrameY(12);

			if (!(cnt % 9))
			{
				cnt = 0;
				character_img->setFrameX(frame);

				if (frame == 0)correctionY = -1;	 //�Ӹ� ������
				if (frame == 1)correctionY = 0;		 //�Ӹ� ������
				if (frame == 2)correctionY = -1;	 //�Ӹ� ������
				if (frame == 3)correctionY = 0;		 //�Ӹ� ������

				frame++;
				
				if (frame >= 4)
				{
					frame = 0;
				}
			}
		}
		if (WJASL == JUMP) //������ �����̹���
		{
			correctionY = 0;
			correctionX = 0;
			character_img->setFrameY(18);
			character_img->setFrameX(0);
		}
		if (WJASL == ATTACK)	//������ �����̹���
		{
			if (cnt == 0 || cnt == 15 || cnt == 23 || cnt == 41)
			{
				if(cnt == 23)
				{
					//���� for���� �� ���Ұ� ���Ͱ� �����ǳ��� ������ ��Ʈ�� Ȱ��ȭ
					if (_job == "�ʺ���") _chobo->Mob_Knock(c, MM, map);
					if (_job == "����")  _warrior->setCnt(); 
					if (_job == "������")  _magic->setCnt();
					if (_job == "����")
					{
						float angle;
						for (int i = 0; i < 2; i++)
						{
							if (who != -1)
								angle = getAngle(_thief->getSx(), _thief->getSy() + 20, MM->_getvMob()[who]->getX(), MM->_getvMob()[who]->getY());
							else
								angle = 0.0f;
							angle = angle + ((-0.5 * (PI / 180)) * i);

							_bullet->Throw(_thief->getSx() - (i * 50), _thief->getSy(), angle, 1, who, c, MM, -15.0f*((1 - i) - i), _job, eft);
						}
						who = -1;
						temp = 10000;
					}
					if (_job == "�ü�")
					{
						float angle;
						for (int i = 0; i < 2; i++)
						{
							if (who != -1)
								angle = getAngle(_archer->getSx(), _archer->getSy() + 20, MM->_getvMob()[who]->getX(), MM->_getvMob()[who]->getY());
							else
								angle = 0.0f;
							angle = angle + ((-0.5 * (PI / 180)) * i);

							_bullet->Throw(_archer->getSx() - (i * 50), _archer->getSy(), angle, 1, who, c, MM, -15.0f*((1 - i) - i), _job, eft);
						}
						who = -1;
						temp = 10000;
					}
				}
				if (cnt >= 41)
				{
					WJASL = STANDING;
					if (right_isStayKeyDown) RL = RIGHT;
					if (left_isStayKeyDown)  RL = LEFT;
					loop = false;
					attackPattern = frame = cnt = correctionX = correctionY = 0;			
					return;
				}

				if (attackPattern == 1)
				{
					character_img->setFrameY(13);
					if (frame == 0 && _job != "�ü�") { correctionX = 6.5f; correctionY = 5.8f; }
					if (frame == 1 && _job != "�ü�") { correctionX = 3.5f; correctionY = 1.2f; }
					if (frame == 2 && _job != "�ü�") { eft->normal_r_1(x + (body.right-body.left)*2 + 10, y - (body.bottom - body.top) / 2 - 10); correctionX = 27.5f; correctionY = 6.8f; }

					if (frame == 0 && _job == "�ü�") { correctionY = 0.0f; }
					if (frame == 1 && _job == "�ü�") { correctionY = 3.0f; }
					if (frame == 2 && _job == "�ü�") { correctionY = 3.0f; }
				}
				else if (attackPattern == 2)
				{
					character_img->setFrameY(14);
					if (frame == 0 && _job != "�ü�") { correctionX = 3.3f; correctionY = 5.0f; }
					if (frame == 1 && _job != "�ü�") { correctionX = 9.3f; correctionY = 4.0f; }
					if (frame == 2 && _job != "�ü�") { eft->normal_r_2(x + (body.right - body.left) * 2 + 10, y - (body.bottom - body.top) / 2 + 5); correctionX = 5.3f; correctionY = 7.0f; }

					if (frame == 0 && _job == "�ü�") { correctionY = 0.0f; }
					if (frame == 1 && _job == "�ü�") { correctionY = 3.0f; }
					if (frame == 2 && _job == "�ü�") { correctionY = 3.0f; }
				}
				else if (attackPattern == 3)
				{
					character_img->setFrameY(15);
					if (frame == 0 && _job != "�ü�") { correctionX = -1.7f; correctionY = 0.0f; }
					if (frame == 1 && _job != "�ü�") { correctionX = 2.3f; correctionY = 2.0f; }
					if (frame == 2 && _job != "�ü�") { eft->normal_r_3(x + (body.right - body.left) * 2, y - (body.bottom - body.top) / 2 + 10); correctionX = 4.3f; correctionY = 5.0f; }

					if (frame == 0 && _job == "�ü�") { correctionY = 0.0f; }
					if (frame == 1 && _job == "�ü�") { correctionY = 3.0f; }
					if (frame == 2 && _job == "�ü�") { correctionY = 3.0f; }
				}

				character_img->setFrameX(frame);
				frame++;
			}
		}
	}
	else if (RL == LEFT && medal == false)	///////////////////����
	{
		character_head->setFrameY(1);
		if (WJASL == STANDING)	//���� ���ĵ� �̹���
		{
			character_img->setFrameY(0);

			correctionY = 0;

			if (!(cnt % 40))
			{
				cnt = 0;
				character_img->setFrameX(frame);
				frame = frame + (loop == false) + ((loop == true) * -1);
				if (frame >= 2 || frame == 0)
				{
					loop = !loop;
				}
			}
		}
		if (WJASL == WALK)	//���� �ȴ� �̹���
		{
			character_img->setFrameY(2);

			if (!(cnt % 9))
			{
				cnt = 0;
				character_img->setFrameX(frame);

				if (frame == 0)correctionY = -1;	 //�Ӹ� ������
				if (frame == 1)correctionY = 0;		 //�Ӹ� ������
				if (frame == 2)correctionY = -1;	 //�Ӹ� ������
				if (frame == 3)correctionY = 0;		 //�Ӹ� ������

				frame++;
				if (frame >= 4)
				{
					frame = 0;
				}
			}
		}
		if (WJASL == JUMP)	//���� ���� �̹���
		{
			correctionY = 0;
			correctionX = 0;
			character_img->setFrameY(8);
			character_img->setFrameX(0);
		}
		if (WJASL == ATTACK)	//���� �����̹���
		{
			if (cnt == 0 || cnt == 15 || cnt == 23 || cnt == 41)
			{
				if (cnt == 23)
				{
					//���� for���� �� ���Ұ� ���Ͱ� �����ǳ��� ������ ��Ʈ�� Ȱ��ȭ
					if (_job == "�ʺ���") _chobo->Mob_Knock(c, MM, map);
					if (_job == "����") _warrior->setCnt();
					if (_job == "������") _magic->setCnt();
					if (_job == "����" )
					{
						float angle;
						for (int i = 0; i < 2; i++)
						{
							if (who != -1)
								angle = getAngle(_thief->getSx(), _thief->getSy() + 20, MM->_getvMob()[who]->getX(), MM->_getvMob()[who]->getY());
							else
								angle = -180 * (PI / 180);
							angle = angle + ((-0.5 * (PI / 180)) * i);

							_bullet->Throw(_thief->getSx() + (i * 50), _thief->getSy(), angle, -1, who, c, MM, -15.0f*((1 - i) - i), _job, eft);
						}
						who = -1;
						temp = 10000;
					}
					if ( _job == "�ü�")
					{
						float angle;
						for (int i = 0; i < 2; i++)
						{
							if (who != -1)
								angle = getAngle(_archer->getSx(), _archer->getSy() + 20, MM->_getvMob()[who]->getX(), MM->_getvMob()[who]->getY());
							else
								angle = -180 * (PI / 180);
							angle = angle + ((-0.5 * (PI / 180)) * i);

							_bullet->Throw(_archer->getSx() + (i * 50), _archer->getSy(), angle, -1, who, c, MM, -15.0f*((1 - i) - i), _job, eft);
						}
						who = -1;
						temp = 10000;
					}
					
				}
				if (cnt >= 41)
				{
					WJASL = STANDING;
					if (right_isStayKeyDown) RL = RIGHT;
					if (left_isStayKeyDown)  RL = LEFT;
					loop = false;
					attackPattern = frame = cnt = correctionX = correctionY = 0;
					return;
				}

				if (attackPattern == 1)
				{
					character_img->setFrameY(3);
					if (frame == 0 && _job != "�ü�") { correctionX = -6.5f; correctionY = 5.8f; }
					if (frame == 1 && _job != "�ü�") { correctionX = -3.5f; correctionY = 1.2f; }
					if (frame == 2 && _job != "�ü�") { eft->normal_l_1(x - (body.right - body.left) * 2 - 10, y - (body.bottom - body.top) / 2 - 10); correctionX = -27.5f; correctionY = 6.8f; }

					if (frame == 0 && _job == "�ü�") { correctionY = 0.0f; }
					if (frame == 1 && _job == "�ü�") { correctionY = 3.0f; }
					if (frame == 2 && _job == "�ü�") { correctionY = 3.0f; }
				}
				else if (attackPattern == 2)
				{
					character_img->setFrameY(4);
					if (frame == 0 && _job != "�ü�") { correctionX = -3.3f; correctionY = 5.0f; }
					if (frame == 1 && _job != "�ü�") { correctionX = -9.3f; correctionY = 4.0f; }
					if (frame == 2 && _job != "�ü�") { eft->normal_l_2(x - (body.right - body.left) * 2 - 10, y - (body.bottom - body.top) / 2 + 5); correctionX = -5.3f; correctionY = 7.0f; }

					if (frame == 0 && _job == "�ü�") { correctionY = 0.0f; }
					if (frame == 1 && _job == "�ü�") { correctionY = 3.0f; }
					if (frame == 2 && _job == "�ü�") { correctionY = 3.0f; }
				}
				else if (attackPattern == 3)
				{
					character_img->setFrameY(5);
					if (frame == 0 && _job != "�ü�") { correctionX = 1.7f; correctionY = 0.0f; }
					if (frame == 1 && _job != "�ü�") { correctionX = -2.3f; correctionY = 2.0f; }
					if (frame == 2 && _job != "�ü�") { eft->normal_l_3(x - (body.right - body.left) * 2, y - (body.bottom - body.top) / 2 + 10); correctionX = -4.3f; correctionY = 5.0f; }

					if (frame == 0 && _job == "�ü�") { correctionY = 0.0f; }
					if (frame == 1 && _job == "�ü�") { correctionY = 3.0f; }
					if (frame == 2 && _job == "�ü�") { correctionY = 3.0f; }
				}

				character_img->setFrameX(frame);
				frame++;
			}
		}
	}
	if (medal)	//�޴޷�������
	{
		if ((collision_ropeladder.right - collision_ropeladder.left) >= 36.0f) character_img->setFrameY(6);
		if ((collision_ropeladder.right - collision_ropeladder.left) <= 15.0f) character_img->setFrameY(7);
		
		character_head->setFrameY(2);
		if (RL == RIGHT) correctionX = -4.0f;
		else if (RL == LEFT) correctionX = 4.0f;
		if(cnt>=15) cnt = 0;
		if (!cnt)
		{		
			character_img->setFrameX(frame);
			frame++;
			if (frame >= 2) frame = 0;	
		}	
	}
	if(medal == false) cnt++;
}

//�𽺿���
void Character::aggro()
{
	for (int i = 0; i < MM->_getvMob().size(); ++i)
	{
		if (MM->_getvMob()[i]->getAggro() == 0 || MM->_getvMob()[i]->getType() == BOSS) continue;

		//���� ĳ���ͺ��� �����ʿ� ������ ��, ���� �������� �̵��ؾ��Ҷ�, �������� �̵��ϴϱ� minX(�ּ� �̵��ݰ� ����)
		//�� ���� �������� �ʾ����� �ϴ� �״�� �������, ���ٰ� gra(�߷°�)�� ��ȭ������� �׶� minX�� ���� ��������
		//�׷��ٸ� �� ���ǿ��� (MM->_getvMob()[i]->getminX() == 0.0f || �� ���������ʴ´�.
		//�׷��ٸ� �� �����ִ� ������ �ߵ��Ǵµ� ���� minX�� 0.0�� �ƴϰ� ���� ���� x���� �ּҹݰ溸�� Ŭ�� ������ �Ѵ�.
		//�̷����ϸ� ���� x���� �ּҹݰ溸�� �۾����� (�Ѿ��) ������ �ǹǷ� ���� ��׷ΰ� �����ְ� ĳ���Ͱ� ���� ���ʿ�������
		//���� �������� �����ִ� ������ ���ټ��ִ�.(�ٽ� ��� �̰Ͷ��� ..)
		if (MM->_getvMob()[i]->getX() > x && (MM->_getvMob()[i]->getminX() == 0.0f || (MM->_getvMob()[i]->getminX()!=0.0f && MM->_getvMob()[i]->getX() > MM->_getvMob()[i]->getminX()+3.0f)))
		{
			MM->_getvMob()[i]->setRnd(x, y);
		}
		else if (MM->_getvMob()[i]->getX() < x && (MM->_getvMob()[i]->getmaxX() == 0.0f || (MM->_getvMob()[i]->getmaxX()!=0.0f && MM->_getvMob()[i]->getX() < MM->_getvMob()[i]->getmaxX()-3.0f)))
		{
			MM->_getvMob()[i]->setRnd(x, y);
		}
	}
}

void Character::blow()
{
	if (hit == false)
	{
		for (int i = 0; i < MM->_getvMob().size(); ++i)
		{
			if (MM->_getvMob()[i]->getHP() <= 0) continue;
			RECT temp;
			if ((IntersectRect(&temp, &body, &MM->_getvMob()[i]->getRECT())) || knock)
			{
				dmg->create_damage(x, y, 30, false);
				(MM->_getvMob()[i]->getX() > x) ? spd = -3.0f : spd = 3.0f;
				
				hp -= 3;
				knock = false;
				jump_power = 3.0f;
				hitcnt = 100;
				hit = true;
				break;
			}
		}
	}
	else
	{
		knock = false;
	}
}

void Character::setCharacterImage(string _wname)
{
	_job = _wname;
	character_img = IMAGEMANAGER->findImage(_wname);
	if (_wname == "�ʺ���") character_head->setFrameX(0);
	else if (_wname == "����") character_head->setFrameX(4);
	else if (_wname == "����") character_head->setFrameX(2);
	else if (_wname == "�ü�") character_head->setFrameX(3);
	else if (_wname == "������") character_head->setFrameX(1);
}
