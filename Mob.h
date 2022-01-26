#pragma once
#include "gameNode.h"
#include "Hpbar.h"
#include "MobEffect.h"
#include "Junior_fireball.h"

class Character;
class ItemManager;

enum MobType
{
	NORMAL,
	BOSS
};

enum MobState
{
	M_RIGHT,
	M_LEFT,
	M_STANDING,
	M_MOVE,
	M_JUMP,
	M_HIT,
	M_ATTACK,
	M_DEAD
};

class Mob : public gameNode
{
protected:

	MobEffect* eft;
	Junior_fireball* junior_fire;

	Character* cha;

	ItemManager* _itemManager;

	image* Mobimage;

	Hpbar* _hpbar;

	float x, y;			//���� x,y ��
	float spawnX, spawnY;
	string mobName;
	int hp, mhp;		//ü��
	int spd;			//�� �̵��ӵ�
	int cnt;			//�ִϸ��̼� ���͹�
	int random_state;	//��������
	int frameX, frameY;	//�ִϸ��̼� ������
	int dead_cnt;		//�����׾����� �ٽ� �������Ǵ� ���͹�
	int alpha;			//�����İ�
	MobType type;		//�Ϲݸ�, ������
	int aggro;			//ĳ���Ͱ� �������� ��׷� (�Ϲݸ�������)
	bool jump_ok;		//��������
	bool ani_update;	//�ִϸ��̼� �������� ���κ��̶�� ��ȣ
	bool hit;
	bool _hpbarVisible;
	bool pause;
	float gra;			//�����ϴ� ���� �߷�on
	float jump_power;	//�����ϴ� ���� on
	float knockback;	//�� �˹�
	float minX, maxX;	//�ּҷ� �̵������� X�ݰ�� �ִ� X�ݰ�	
	float plusDamageY;	
	float spdKnockback;

	int rnd_update;		//���ο���� �� Ȯ��
	int rnd_stand;		//���������� Ȯ��
	int rnd_right;		//���������� �� Ȯ��
	int rnd_left;		//�������� �� Ȯ��
	int rnd_jump;		//������ Ȯ��
	int damage;
	int isExist;

	float TEST;

	RECT MobRect;

	MobState M_rl;		//���� ���¹������
	MobState M_smja;	//���� ��������

public:
	Mob() {};
	~Mob() {};

	virtual HRESULT init(const char* imageName, POINT pos);
	virtual void release();
	virtual void update();
	virtual void render();

	float getX() { return x; }
	float getY() { return y; }
	void setX(float setx) { x = setx; }
	void setY(float sety) { y = sety; }
	void setSpawnY(float sety) { spawnY = sety; }
	void setGRA() { gra = 0.0f; }
	MobState getRL() { return M_rl; }
	MobState getSMJA() { return M_smja; }
	MobType getType() { return type; }
	float getGRA() { return gra; }
	int getAggro() { return aggro; }
	float getminX() { return minX; }
	float getmaxX() { return maxX; }
	void setminX() { minX = x; }
	void setmaxX() { maxX = x; }
	void set_aniUpdate() { ani_update = true; rnd_update = 100; }
	float getJP() { return jump_power; }
	void setJP() { jump_power = 0.0f; cnt = frameX = 0; }
	void setRnd(float infoX, float infoY);
	void setRL(MobState setrl);
	void setHIT(MobState direction, float _plusDamgeY, int _damage);
	bool getHit() { return hit; }
	int getHP() { return hp; }
	void setFalseHit() { hit = false; }
	RECT getRECT() { return MobRect; }
	image* getImage() { return Mobimage; }
	bool getJumpOk() { return jump_ok; }
	float getPlusDamageY() { return plusDamageY; }
	void setPlusDamageY(float _setY) { plusDamageY = _setY; }
	void setCharAdress(Character* c) { cha = c; }
	void setItemManagerAdress(ItemManager* _iM) { _itemManager = _iM; }
	int getDMG() { return damage; }
	float getspdKnockback() { return spdKnockback; }
	void setExist(bool _set) { isExist = _set; }
	bool getExist() { return isExist; }
};

