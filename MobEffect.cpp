#include "stdafx.h"
#include "MobEffect.h"

HRESULT MobEffect::init()
{
	EFFECTMANAGER->addEffect("�ֹ߰���1_1", "�̹���/����Ʈ/�ֹ�/����Ʈ1_1.bmp", 486, 112, 243, 112, 1.0f, 0.1f, 1);
	EFFECTMANAGER->addEffect("�ֹ߰���1_2", "�̹���/����Ʈ/�ֹ�/����Ʈ1_2.bmp", 486, 112, 243, 112, 1.0f, 0.1f, 1);

	EFFECTMANAGER->addEffect("�ֹ߰���2_1", "�̹���/����Ʈ/�ֹ�/����Ʈ2_1.bmp", 1374, 122, 229, 122, 1.0f, 0.1f, 1);	
	EFFECTMANAGER->addEffect("�ֹ߰���2_2", "�̹���/����Ʈ/�ֹ�/����Ʈ2_2.bmp", 1374, 122, 229, 122, 1.0f, 0.1f, 1);

	EFFECTMANAGER->addEffect("�ֹ߰���3", "�̹���/����Ʈ/�ֹ�/����Ʈ3.bmp", 684, 111, 114, 111, 2.0f, 0.1f, 1);

	EFFECTMANAGER->addEffect("���̾����", "�̹���/����Ʈ/�ֹ�/���̾����.bmp", 424, 120, 106, 120, 1.0f, 0.1f, 3);

	return S_OK;
}

void MobEffect::release()
{

}

void MobEffect::update()
{
	EFFECTMANAGER->update();
}

void MobEffect::render()
{
	EFFECTMANAGER->render();
}
