#pragma once
#include "animation.h"

class image
{
public:

	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,	
		LOAD_FILE,		
		LOAD_EMPTY,		
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;	
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float x;			
		float y;
		int width;			
		int height;			
		int currentFrameX;	
		int currentFrameY;	
		int maxFrameX;		
		int maxFrameY;		
		int frameWidth;		
		int frameHeight;	
		BYTE loadType;	

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}

	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;	
	CHAR*			_fileName;		
	BOOL			_trans;			
	COLORREF		_transColor;	

	BLENDFUNCTION	_blendFunc;		
	LPIMAGE_INFO	_blendImage;	
public:

	image();
	~image();

	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const char* fileName, float x, float y,
		int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	HRESULT init(const char* fileName, int width, int height, 
		int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	void release();
	void setTransColor(BOOL trans, COLORREF transColor);


	void render(HDC hdc);
	
	void render(HDC hdc, int destX, int destY);
	
	void render(HDC hdc, int destX, int destY, int sourX, int sourY,
		int sourWidth, int sourHeight);

	void frameRender(HDC hdc, int destX, int destY);

	void alpha_frameRender(HDC hdc, int destX, int destY, BYTE alpha);

	void alpha_frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

	void frameRender(HDC hdc, int destX, int destY,
		int currentFrameX, int currentFrameY);


	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void aniRender(HDC hdc, int destX, int destY, animation* ani);

	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	inline HDC getMemDC() { return _imageInfo->hMemDC; }


	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ?
			_imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ?
			_imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;

		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;

		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}


	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }

	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }

};

