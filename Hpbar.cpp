#include "stdafx.h"
#include "Hpbar.h"

HRESULT Hpbar::init()
{
	_hpfront = IMAGEMANAGER->addImage("��ü�¹�", "�̹���/ü�¹�/ü�¹پ�.bmp", 60, 5, true, RGB(255, 0, 255));
	_hpbehind = IMAGEMANAGER->addImage("��ü�¹�", "�̹���/ü�¹�/ü�¹ٵ�.bmp", 66, 11, true, RGB(255, 0, 255));

	return S_OK;
}

void Hpbar::release()
{

}

void Hpbar::update()
{
	
}

void Hpbar::render()
{
	_hpbehind->render(getMemDC(), x, y, 0, 0, 66, 11);
	_hpfront->render(getMemDC(), x+3, y+3, 0, 0, ((float)hp / (float)mhp) * 60, 5);
}
