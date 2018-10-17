#pragma once

#include "stdafx.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
using namespace std;

#include "cv.h"
#include <cxcore.h>
#include "highgui.h"
;

#include "SF4Display.h"
;


SF4Display::SF4Display()
{
	_drawScreen = true;
}

SF4Display::~SF4Display()
{
}


void
SF4Display::DrawRectOutline(IplImage * img,CvRect drawRect,CvScalar rgbVal)
{
	CvPoint start;
	CvPoint stop;

	start = cvPoint(drawRect.x,drawRect.y);
	stop = cvPoint(drawRect.x+drawRect.width,drawRect.y+drawRect.height);
	cvRectangle(img,start,stop,rgbVal,5,8,0);
	
}

