#pragma once
#include "gameNode.h"

class charEffect : public gameNode
{

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void normal_r_1(float _x, float _y) { EFFECTMANAGER->play("�������Ϲݰ���1", _x, _y); };
	void normal_l_1(float _x, float _y) { EFFECTMANAGER->play("�����Ϲݰ���1", _x, _y); };

	void normal_r_2(float _x, float _y) { EFFECTMANAGER->play("�������Ϲݰ���2", _x, _y); };
	void normal_l_2(float _x, float _y) { EFFECTMANAGER->play("�����Ϲݰ���2", _x, _y); };

	void normal_r_3(float _x, float _y) { EFFECTMANAGER->play("�������Ϲݰ���3", _x, _y); };
	void normal_l_3(float _x, float _y) { EFFECTMANAGER->play("�����Ϲݰ���3", _x, _y); };

	void blust(float _x, float _y) { EFFECTMANAGER->play("�����ú���Ʈ", _x, _y); };
	void blust_blow(float _x, float _y) { EFFECTMANAGER->play("�����ú���ƮŸ��", _x, _y); };

	void seven_1(float _x, float _y) { EFFECTMANAGER->play("��Ű����_1", _x, _y); };
	void seven_2(float _x, float _y) { EFFECTMANAGER->play("��Ű����_2", _x, _y); };
	void seven_blow(float _x, float _y) { EFFECTMANAGER->play("��Ű����Ÿ��", _x, _y); };

	void clo_1(float _x, float _y) { EFFECTMANAGER->play("����Ŭ��_1", _x, _y); };
	void clo_2(float _x, float _y) { EFFECTMANAGER->play("����Ŭ��_2", _x, _y); };
	void clo_blow(float _x, float _y) { EFFECTMANAGER->play("����Ŭ��Ÿ��", _x, _y); };
};