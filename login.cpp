#include "stdafx.h"
#include "login.h"

HRESULT login::init()
{
	IMAGEMANAGER->addImage("����ȭ��", "�̹���/UI/����ȭ��/�α���â.bmp", 800, 600, false, NULL);
	IMAGEMANAGER->addImage("����â", "�̹���/UI/����ȭ��/������.bmp", 464, 302, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("���ӽ��۹�ư", "�̹���/UI/����ȭ��/���ӽ��۹�ư.bmp", 420, 52, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Ȯ�ι�ư", "�̹���/UI/����ȭ��/Ȯ�ι�ư.bmp", 249, 26, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->findImage("���ӽ��۹�ư")->setFrameX(0);
	IMAGEMANAGER->findImage("Ȯ�ι�ư")->setFrameX(0);

	next = 0;

	return S_OK;
}

void login::release()
{
}

void login::update()
{
	if (next == 0)
	{
		RECT start_button = RectMake(330, 350, 140, 52);
		if (PtInRect(&start_button, PointMake(_ptMouse.x, _ptMouse.y)))
		{
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				next = 1;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				IMAGEMANAGER->findImage("���ӽ��۹�ư")->setFrameX(2);
			}		
			else
			{
				IMAGEMANAGER->findImage("���ӽ��۹�ư")->setFrameX(1);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("���ӽ��۹�ư")->setFrameX(0);
		}
	}
	if (next == 1)
	{
		RECT ok_button = RectMake(355, 400, 83, 26);
		if (PtInRect(&ok_button, PointMake(_ptMouse.x, _ptMouse.y)))
		{
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
			{
				next = 2;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				IMAGEMANAGER->findImage("Ȯ�ι�ư")->setFrameX(2);
			}		
			else
			{
				IMAGEMANAGER->findImage("Ȯ�ι�ư")->setFrameX(1);
			}
		}
		else
		{
			IMAGEMANAGER->findImage("Ȯ�ι�ư")->setFrameX(0);
		}
	}
}

void login::render()
{
	IMAGEMANAGER->findImage("����ȭ��")->render(getMemDC());
	IMAGEMANAGER->findImage("���ӽ��۹�ư")->frameRender(getMemDC(), 330, 350);
	if (next == 1)
	{
		IMAGEMANAGER->findImage("����â")->render(getMemDC(), 168, 150);
		IMAGEMANAGER->findImage("Ȯ�ι�ư")->frameRender(getMemDC(), 355, 400);
	}
}
