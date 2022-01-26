#pragma once
#include "image.h"

//백버퍼라는 빈 비트맵 이미지를 하나 생성해둔다
static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;	

public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init();			
	virtual HRESULT init(bool managerInit);
	virtual void release();			
	virtual void update();			
	virtual void render();	

	void setMap(string strKey);

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

};

