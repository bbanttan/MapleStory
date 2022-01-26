#pragma once
#include "gameNode.h"
#include "damage.h"
#include "Item.h"

//������ ���ݽ�ų���
#include "chobo.h"
#include "warrior.h"
#include "thief.h"
#include "archer.h"
#include "magic.h"

#include "Bullet.h"

#include "charEffect.h"

#define ACCNACC 0.2f	//�����ӻ��
#define JUMPACC 0.2f	//���������ӻ��
#define MAXSPD 2.0f		//�ִ�ӷ»��
#define GRAVITY 0.4f	//�߷»��
#define JUMP_POWER 8.0f //������
#define C_WIDTH 12.0f	//ĳ���� ������
#define C_HEIGHT 29.0f	//ĳ���� ����

class Map;
class MobManager;
class Character;
class Inventory;

//��������
enum CharacterState
{
	RIGHT,		//�����ʹ����϶�
	LEFT,		//���ʹ����϶�
	WALK ,		//�ȴ����϶�
	JUMP,		//�������϶�
	ATTACK,		//�������϶�
	STANDING,	//������������
	LADDERROPE,	//�޴޷�������
	DEAD		//������
};

class Character : public gameNode
{
private:
	/*               ���������                */

	float
		x,				//ĳ���� x��
		y,				//ĳ���� y��
		hp,				//ĳ���� hp
		mp,				//ĳ���� mp
		mhp,			//ĳ���� �ƽ� hp
		mmp,			//ĳ���� �ƽ� hp
		spd,			//ĳ���� ������
		gravity,		//ĳ���� �߷�
		error_hp,		//ĳ���� hp ������� ����
		error_mp,		//ĳ���� mp ������� ����
		jump_power,		//ĳ���� ������
		correctionX,	//ĳ���� �Ӹ� ������
		correctionY;	//ĳ���� �Ӹ� ������
		 
	int 
		cnt,			//�ִϸ��̼� ���͹�
		STR,			//ĳ������
		who,			//� ���͸� Ÿ���ߴ��� ����
		temp,			//���尡��� ������ �Ÿ��� ��� ����
		alpha,			//ĳ���� ���İ�
		frame,			//ĳ���� �ִϸ��̼� ������
		hitcnt,			//�ǰ������� �󸶳� ���������ΰ� ���͹�
		attackPattern;	//���� ���ݸ�� 3����

	bool 
		hit,				//���Ϳ��� �ǰݹ��� ���� ����1						
		loop,				//�ִϸ��̼� ����(ex, �������� 0-1-2-1-0)
		knock,				//���Ϳ��� �ǰݹ��� ���� ����2
		medal,				//�޴޷��ִ°� ����
		collision_portal,	//��Ż�� ��Ҵ°� ����
		left_isOnceKeyUp,	//����Ű ������ ���°� üũ
		right_isOnceKeyUp,	//����Ű ������ ���°� üũ
		left_isOnceKeyDown,	//����Ű ������ �ѹ���üũ
		left_isStayKeyDown,	//����Ű ��Ӵ����°� üũ	
		right_isOnceKeyDown,//����Ű ������ �ѹ���üũ
		right_isStayKeyDown //����Ű ��Ӵ����°� üũ		
		;

	/*------------���� ����� ��-------------*/

	/*          ��Ʈ �����          */

	RECT
		head,						//��Ʈ �Ӹ�
		body,						//��Ʈ ĳ���� ��
		collision_ropeladder;		//ĳ���Ϳ� ���� ��ٸ� ��Ʈ

	/*--------��Ʈ ����� ��----------*/


	/*          Ŭ���� �����        */

	Map* map;						//�� Ŭ���� ����	 (���漱�� �Ǿ�����)
	damage* dmg;					//������ ���� ������Ŭ����	
	Character* c;					//�ڱ��ڽ� ���� (���漱�� �Ǿ�����)
	chobo* _chobo;					//���� : �ʺ� ����
	thief* _thief;					//���� : ���� ����
	magic* _magic;					//���� : ������ ����	
	MobManager* MM;					//���Ŵ��� ���� (���漱�� �Ǿ�����)
	charEffect* eft;				//ĳ���� ��ų����Ʈ
	Bullet* _bullet;				//ǥâ, ȭ����� Ŭ���� ����
	archer* _archer;				//���� : �ü� ����
	warrior* _warrior;				//���� : ���� ����
	Inventory* _inven;
	Item* CurrentEquit;				//���繫��
	image* character_img;			//ĳ���� �����̹���
	image* character_head;			//ĳ���� �Ӹ��̹���	

	/*--------Ŭ���� ����� ��------*/

	string _job;
	
	/*          ĳ���� ���°��� enum �����         */

	CharacterState RL;		//������ ���¸� �����ϴ� �̳ѹ�
	CharacterState WJASL;	//������ ���¸� �����ϴ� �̳ѹ�

	/*--------ĳ���� ���°��� enum ����� ��---------*/

public:

	Character() {};
	~Character() {};

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void accNacc();				//�������Լ�
	virtual void Landing();				//���� �Լ�
	virtual void anime();				//ĳ���� �ִϸ��̼� �Լ�
	virtual void aggro();				//ĳ���Ϳ����� ���� ��׷��Լ�
	virtual void blow();				//ĳ���Ͱ� Ÿ�ݹ޾����� �Լ�

	
	/*              get �Լ�����               */

	float getX() { return x; }
	float getY() { return y; }
	int getSTR() { return STR; }
	int getWho() { return who; }
	int getTemp() { return temp; }
	float getMHP() { return mhp; }
	float getMMP() { return mmp; }
	RECT getRECT() { return body; }
	string getJob() { return _job; }
	void setCx(float cx) { x = cx; }
	void setCy(float cy) { y = cy; }
	float getHP() { return error_hp; }
	float getMP() { return error_mp; }
	CharacterState getRL() { return RL; }
	Item* getEquit() { return CurrentEquit; }
	void getMyAdress(Character* _c) { c = _c; }
	CharacterState getWJASL() { return WJASL; }	

	/*-------------get �Լ����� ��-------------*/

	/*              set �Լ�����               */

	void setHIT() { knock = true; }
	void setWho(int _who) { who = _who; }
	void setCharacterImage(string _wname);
	void setTemp(int _temp) { temp = _temp; }
	void setSTR(int _setSTR) { STR = _setSTR; }
	void setMapAdress(Map* _map) { map = _map; }
	void setMapAdress(MobManager* _mm) { MM = _mm; }
	void setEquit(Item* _item) { CurrentEquit = _item; }
	void setPortal_Collision() { collision_portal = true; } //��Ż�� ������ �´�������� ���������Ҷ� ĳ������ġ�� �̻��� ���°� ����
	void setInventoryAdress(Inventory* inven) { _inven = inven; }
	void setLadderRope(RECT rect) { collision_ropeladder = rect; }
	void setAddHpMp(int _addHP, int _addMP) { hp += _addHP; mp += _addMP; }
	
	/*-------------set �Լ����� ��-------------*/
};

