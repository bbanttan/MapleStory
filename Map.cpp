#include "stdafx.h"
#include "Map.h"
#include "character.h"
#include "MobManager.h"
#include "ItemManager.h"

HRESULT Map::init()
{
	//������ �̸��� ���� ���̹��� ���ҽ����ֱ�
	IMAGEMANAGER->addImage("�����ǿ��", "�̹���/��/�����ǿ��.bmp", 2430, 1486, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̱�1", "�̹���/��/���̱�1.bmp", 2760, 2244, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ֹ�������", "�̹���/��/���ֹ�������.bmp", 1532, 940, false, RGB(255, 0, 255));
	
	//����
	IMAGEMANAGER->addImage("�����ǿ������", "�̹���/��/�����ǿ������.bmp", 2430, 1486, true, RGB(0, 255, 0));
	IMAGEMANAGER->addImage("���̱�1����", "�̹���/��/���̱�1����.bmp", 2760, 2244, true, RGB(0, 255, 0));
	IMAGEMANAGER->addImage("���ֹ�����������", "�̹���/��/���ֹ�����������.bmp", 1532, 940, true, RGB(0, 255, 0));

	for (int i = 0; i < 2; i++)
	{
		portal[i].img_portal = IMAGEMANAGER->addFrameImage("��Ż", "�̹���/��/��Ż.bmp", 712, 257, 8, 1, true, RGB(255, 0, 255));
		portal[i].ani_portal = new animation;
		portal[i].ani_portal->init(portal[i].img_portal->getWidth(), portal[i].img_portal->getHeight(),
			portal[i].img_portal->getFrameWidth(), portal[i].img_portal->getFrameHeight());
		portal[i].ani_portal->setDefPlayFrame(true, true);
		portal[i].ani_portal->setFPS(1);
	}
	//currentMap�� ����� ���ڿ� �ʱ�ȭ
	sprintf_s(currentMap, "%s", "�����ǿ��");
	sprintf_s(currentMapland, "%s����", "�����ǿ��");

	//currentMap�� �̸��� ���� ������ ����
	setMap(currentMap);

	//���� ��ٸ���ġ
	setropeladder(currentMap);

	return S_OK;
}

void Map::release()
{

}

void Map::update()
{
	CAMERA->setMapChange(0.02f);

	//ĳ���Ϳ� ��ٸ����� �浹üũ
	for (int i = 0; i < 10; i++)
	{
		if (rpld[i].isExist == false) break;
		RECT temp;
		if (IntersectRect(&temp, &C->getRECT(), &rpld[i].rect))
		{
			C->setLadderRope(rpld[i].rect);
		}
	}
	//ĳ���Ϳ� ��Ż �浹üũ
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		for (int i = 0; i < 2; i++)
		{
			if (portal[i].isExist == false) break;
			RECT temp;
			if (IntersectRect(&temp, &C->getRECT(), &portal[i].rect))
			{
				C->setPortal_Collision();
				C->setCx(portal[i].msg_x);
				C->setCy(portal[i].msg_y);

				CAMERA->setMapChange(1.0f);

				sprintf_s(currentMap, "%s", portal[i].map);
				sprintf_s(currentMapland, "%s����", portal[i].map);
				setMap(portal[i].map);
				setropeladder(currentMap);
				
				Mb->setMonster(currentMap);
				_itemManager->Item_all_clear();
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if (portal[i].isExist == false) break;
		portal[i].ani_portal->frameUpdate(TIMEMANAGER->getElapsedTime() * 10);
	}
}

void Map::render()
{
	//������� getMemDC�� ���� ���ۿ� ä���.
	IMAGEMANAGER->findImage(currentMap)->render(getMemDC());

	for (int i = 0; i < 2; i++)
	{
		if (portal[i].isExist == false) break;
		portal[i].img_portal->aniRender(getMemDC(), portal[i].x, portal[i].y, portal[i].ani_portal);
	}
	
	if (KEYMANAGER->isToggleKey('1'))
	{
		IMAGEMANAGER->findImage(currentMapland)->render(getMemDC());
		for (int i = 0; i < 10; i++)
		{
			if (rpld[i].isExist == false) break;
			HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			HPEN oPen = (HPEN)SelectObject(getMemDC(), Pen);
			Rectangle(getMemDC(), rpld[i].rect);
			SelectObject(getMemDC(), oPen);
			DeleteObject(Pen);
		}
	}
	if (KEYMANAGER->isToggleKey('1'))
	{
		for (int i = 0; i < 2; i++)
		{
			if (portal[i].isExist == false) break;
			HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
			HPEN oPen = (HPEN)SelectObject(getMemDC(), Pen);
			Rectangle(getMemDC(), portal[i].rect);		
			SelectObject(getMemDC(), oPen);
			DeleteObject(Pen);
		}
	}	
}

void Map::setropeladder(string map)
{
	for (int i = 0; i < 10; i++)
	{
		rpld[i].isExist = false;
	}
	for (int i = 0; i < 2; i++)
	{
		portal[i].isExist = false;
	}

	//��ٸ� ���� ��ġ
	if (map == "�����ǿ��")
	{

		int infoArrX[] = { 743.0f, 1508.0f };		//��ٸ� x�� ��ġ
		int infoArrY[] = { 580.0f, 583.0f };		//��ٸ� y�� ��ġ
		int infoArrW[] = { 36.0f, 36.0f };			//��ٸ� width�� ����
		int infoArrH[] = { 343.9f, 241.1f };		//��ٸ� height�� ����

		for (int i = 0; i < 2; i++)				//�����ǿ�� ��ٸ����� 2���ϱ� 2���� ����
		{
			rpld[i].isExist = true;
			rpld[i].x = infoArrX[i];
			rpld[i].y = infoArrY[i];
			rpld[i].rect = RectMake(rpld[i].x, rpld[i].y, infoArrW[i], infoArrH[i]);
		}

		//��Ż��ġ
		portal[0].isExist = true;
		portal[0].x = 2129.4f;
		portal[0].y = 1024.6f;
		portal[0].msg_x = 252.4f;
		portal[0].msg_y = 264.4f;
		sprintf_s(portal[0].map, "%s", "���̱�1");
		portal[0].rect = RectMake(portal[0].x, portal[0].y, 89, 257);

		portal[0].ani_portal->start(); //�ִϸ��̼� ���
	}
	if (map == "���̱�1")
	{
		int infoArrX[] = { 249.9f , 1052.6f , 1085.1f, 1139.1f, 1013.6f, 1100.1f, 2009.2f, 1978.8f, 1991.8f, 2359.1f };
		int infoArrY[] = { 334.9f , 403.9f , 587.4f, 759.8f, 999.1f, 1183.7f, 1090.1f, 1256.7f, 1506.6f, 1881.3f };
		int infoArrW[] = { 36.0f, 14.0f, 36.0f, 14.0, 36.0f, 14.0f, 36.0f, 14.0f, 14.0f, 36.0f };
		int infoArrH[] = { 237.9f, 168.9f, 178.0f, 192.8f, 178.0f, 192.8f, 130.0f, 192.8f, 192.8f, 188.9f };

		for (int i = 0; i < 10; i++)
		{
			rpld[i].isExist = true;
			rpld[i].x = infoArrX[i];
			rpld[i].y = infoArrY[i];
			rpld[i].rect = RectMake(rpld[i].x, rpld[i].y, infoArrW[i], infoArrH[i]);
		}

		int portalinfoX[] = { 224.9f , 2602.8f };
		int portalinfoY[] = { 82.0f , 1621.8f };
		int portalinfoMSGX[] = { 2152.0f , 57.5f };	//ĳ���͸� ���� ���۽�ų�ų�
		int portalinfoMSGY[] = { 1195.3f , 128.0f };	//ĳ���͸� ���� ���۽�ų�ų�
		char mapMSG[2][128] = { "�����ǿ��", "���ֹ�������" };

		for (int i = 0; i < 2; i++)
		{
			portal[i].isExist = true;
			portal[i].x = portalinfoX[i];
			portal[i].y = portalinfoY[i];
			portal[i].msg_x = portalinfoMSGX[i];
			portal[i].msg_y = portalinfoMSGY[i];
			sprintf_s(portal[i].map, "%s", mapMSG[i]);
			portal[i].rect = RectMake(portal[i].x, portal[i].y, 89, 257);
			portal[i].ani_portal->start(); //�ִϸ��̼� ���
		}
	}
	if (map == "���ֹ�������")
	{
		int infoArrX[] = { 175.0f , 101.0f , 1076.5f };
		int infoArrY[] = { 277.1f , 423.0f , 422.0f };
		int infoArrW[] = { 37.0f , 9.0f , 9.0f };
		int infoArrH[] = { 233.9f , 253.9f , 253.9f };

		for (int i = 0; i < 10; i++)
		{
			rpld[i].isExist = true;
			rpld[i].x = infoArrX[i];
			rpld[i].y = infoArrY[i];
			rpld[i].rect = RectMake(rpld[i].x, rpld[i].y, infoArrW[i], infoArrH[i]);
		}

		int portalinfoX[] = { 33.0f };
		int portalinfoY[] = { 5.0f };
		int portalinfoMSGX[] = { 2655.8f };	//ĳ���͸� ���� ���۽�ų�ų�
		int portalinfoMSGY[] = { 1756.9f };	//ĳ���͸� ���� ���۽�ų�ų�
		char mapMSG[128] = { "���̱�1" };

		portal[0].isExist = true;
		portal[0].x = portalinfoX[0];
		portal[0].y = portalinfoY[0];
		portal[0].msg_x = portalinfoMSGX[0];
		portal[0].msg_y = portalinfoMSGY[0];
		sprintf_s(portal[0].map, "%s", mapMSG);
		portal[0].rect = RectMake(portal[0].x, portal[0].y, 89, 257);
		portal[0].ani_portal->start(); //�ִϸ��̼� ���
	}
}

float Map::mapExplorer(float Ex, float Ey, float Rich)
{
	for (int i = Ey-10; i < Ey + Rich; i++)
	{
		COLORREF mapColor = GetPixel(IMAGEMANAGER->findImage(currentMapland)->getMemDC(), Ex, i);

		if (GetRValue(mapColor) == 255 && GetGValue(mapColor) == 0 && GetBValue(mapColor) == 255)
		{
			return (float)i;
		}
	}
}