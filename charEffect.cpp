#include "stdafx.h"
#include "charEffect.h"

HRESULT charEffect::init()
{
	EFFECTMANAGER->addEffect("�����Ϲݰ���1", "�̹���/����Ʈ/�Ϲݰ���/���ʰ���1.bmp", 44, 36, 44, 36, 1.0f, 0.1f, 2);
	EFFECTMANAGER->addEffect("�����Ϲݰ���2", "�̹���/����Ʈ/�Ϲݰ���/���ʰ���2.bmp", 45, 23, 45, 23, 1.0f, 0.1f, 2);
	EFFECTMANAGER->addEffect("�����Ϲݰ���3", "�̹���/����Ʈ/�Ϲݰ���/���ʰ���3.bmp", 49, 40, 49, 40, 1.0f, 0.1f, 2);

	EFFECTMANAGER->addEffect("�������Ϲݰ���1", "�̹���/����Ʈ/�Ϲݰ���/�����ʰ���1.bmp", 44, 36, 44, 36, 1.0f, 0.1f, 2);
	EFFECTMANAGER->addEffect("�������Ϲݰ���2", "�̹���/����Ʈ/�Ϲݰ���/�����ʰ���2.bmp", 45, 23, 45, 23, 1.0f, 0.1f, 2);
	EFFECTMANAGER->addEffect("�������Ϲݰ���3", "�̹���/����Ʈ/�Ϲݰ���/�����ʰ���3.bmp", 49, 40, 49, 40, 1.0f, 0.1f, 2);

	EFFECTMANAGER->addEffect("�����ú���Ʈ", "�̹���/����Ʈ/�����ú���Ʈ/�����ú���Ʈ.bmp", 1045, 233, 209, 233, 3.0f, 0.1f, 5);
	EFFECTMANAGER->addEffect("�����ú���ƮŸ��", "�̹���/����Ʈ/�����ú���Ʈ/Ÿ��.bmp", 500, 105, 125, 105, 1.0f, 0.1f, 5);

	EFFECTMANAGER->addEffect("��Ű����_1", "�̹���/����Ʈ/��Ű����/��Ű����_1.bmp", 480, 100, 80, 100, 2.0f, 0.1f, 5);
	EFFECTMANAGER->addEffect("��Ű����_2", "�̹���/����Ʈ/��Ű����/��Ű����_2.bmp", 480, 100, 80, 100, 2.0f, 0.1f, 5);
	EFFECTMANAGER->addEffect("��Ű����Ÿ��", "�̹���/����Ʈ/��Ű����/Ÿ��.bmp", 256, 79, 64, 79, 1.0f, 0.1f, 5);

	EFFECTMANAGER->addEffect("����Ŭ��_1", "�̹���/����Ʈ/����Ŭ��/����Ŭ��_1.bmp", 201, 67, 67, 67, 1.0f, 0.1f, 5);
	EFFECTMANAGER->addEffect("����Ŭ��_2", "�̹���/����Ʈ/����Ŭ��/����Ŭ��_2.bmp", 201, 67, 67, 67, 1.0f, 0.1f, 5);
	EFFECTMANAGER->addEffect("����Ŭ��Ÿ��", "�̹���/����Ʈ/����Ŭ��/����Ŭ��Ÿ��.bmp", 505, 95, 101, 95, 1.0f, 0.1f, 1);


	return S_OK;
}

void charEffect::release()
{

}

void charEffect::update()
{
	EFFECTMANAGER->update();
}

void charEffect::render()
{
	EFFECTMANAGER->render();
}
