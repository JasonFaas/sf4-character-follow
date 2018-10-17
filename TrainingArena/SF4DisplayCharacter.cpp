
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


#include "SF4DisplayCharacter.h"
;


SF4DisplayCharacter::SF4DisplayCharacter(bool amILeft){
	
	_drawScreen = true;
	_amILeft = amILeft;
	_timeLeft = -1;
TRACE("HERE 12\n");
	_leftName = NULL;
	_leftCos = -1;
	_leftHP = -1;	
	_leftSuper = -1;
	_leftUltra = -1;
	_leftLocale = cvRect(10,10,50,50);

	_rightName = NULL;
	_rightCos = -1;
	_rightHP = -1;
	_rightSuper = -1;
	_rightUltra = -1;
	_rightLocale = cvRect(100,100,60,60);

	_imgWidth = -1;
	_imgHeight = -1;
TRACE("HERE 11\n");

	_ctCharDetect = new ColorTheory();
	_ctHP = new ColorTheory();
	_ctRoundOne = new ColorTheory();


	IplImage * _whiteImg = cvCreateImage(cvSize(65,200),8,3);
	cvSet(_whiteImg,CV_RGB(255,255,255),NULL);
	_whiteHist = _ctRoundOne->FaasBGRHistogram(_whiteImg);

	_leftCharImg = NULL;
	_rightCharImg = NULL;

	_xBoxes = 13;
	_yBoxes = 3;
	_xStart = 5;
	_yStart = 5;	

	
	if(_xBoxes%2==0||_yBoxes%2==0)
	{
		TRACE("Must be odd");
		exit(0);
	}
	TRACE("HERE 10\n");
	//TODO: Lots of constants that are not set
	//TODO: Need to NULL set them for freeing
}

SF4DisplayCharacter::~SF4DisplayCharacter(){

	delete _ctCharDetect;
	delete _ctHP;
	delete _ctRoundOne;
	

	if(_leftCharImg!=NULL)
	{
		cvReleaseImage(&_leftCharImg);
		cvReleaseImage(&_rightCharImg);
		cvReleaseHist(&_leftCharHist);
		cvReleaseHist(&_rightCharHist);
	}
}

bool
SF4DisplayCharacter::GetAmILeft()
{
	return _amILeft;
}

void
SF4DisplayCharacter::ProcessImage(IplImage * img)
{
	//TODO: Write function that is state-independent
	//Currently only works on Training
	SetCharLocale(img);
	SetCharHP(img);
}


void
SF4DisplayCharacter::SetCharHP(IplImage * img)
{
	//TODO: Rewrite SetCharHP
	/*
	int xStart=396;
	int yStart=55;
	int xLength=636-xStart;
	int yLength=75-yStart;
	int vals[] = {50,70,100,255,100,255};

	cvSetImageROI(img,cvRect(xStart,yStart,xLength,yLength));
	
	CvHistogram* hist = _ctHP->FaasHSVHistogram(img);	
	
	int newHP = _ctHP->FaasGetHistogramCntOfParams(vals,hist);
	
	cvReleaseHist(&hist);
	cvResetImageROI(img);

	_rightHP = newHP;
*/
}


void
SF4DisplayCharacter::ProcessRoundOne(IplImage * img)
{	
	//Getting Character image	
	if(_leftCharImg!=NULL)
	{
		cvReleaseImage(&_leftCharImg);
		cvReleaseImage(&_rightCharImg);
		cvReleaseHist(&_leftCharHist);
		cvReleaseHist(&_rightCharHist);
	}
	_leftCharImg = cvCloneImage(img);
	cvSetImageROI(_leftCharImg,cvRect(85,165,170,250));

	_rightCharImg = cvCloneImage(img);
	cvSetImageROI(_rightCharImg,cvRect(460,165,170,250));

	//Setup Scaling Img and Hist
	_imgWidth = img->width;
	_imgHeight = img->height;

	_widthHalfBox = (int)((_imgWidth-5-_xStart)/(_xBoxes/2+1)/2);
	_heightHalfBox = (int)((_imgHeight-5-_yStart)/(_yBoxes/2+1)/2);

	//Hist
	IplImage * temp = cvCreateImage(cvSize(_widthHalfBox*2,_heightHalfBox*2),8,_leftCharImg->nChannels);

	cvResize(_leftCharImg,temp);
	_leftCharHist = _ctCharDetect->FaasBGRHistogram(temp);
	
	cvResize(_rightCharImg,temp);
	_rightCharHist = _ctCharDetect->FaasBGRHistogram(temp);
}

IplImage *
SF4DisplayCharacter::getCharImg(bool leftRight)
{
	if(leftRight)
		return _leftCharImg;
	else
		return _rightCharImg;
}


void
SF4DisplayCharacter::SetCharLocale(IplImage * img)
{
	int leftLocale[] = {-1,-1};
	float leftHistCmp = -1;
	int rightLocale[] = {-1,-1};
	float rightHistCmp = -1;
	
	float tempHistCmp = 0;
	CvHistogram* hist;

	for(int i = 0;i<_xBoxes;i++)
	{
		for(int k = 0;k<_yBoxes;k++)
		{
			cvSetImageROI(img,cvRect(_xStart+i*_widthHalfBox,_yStart+k*_heightHalfBox,_widthHalfBox*2,_heightHalfBox*2));
			hist = _ctCharDetect->FaasBGRHistogram(img);

			tempHistCmp = cvCompareHist(hist,_leftCharHist,CV_COMP_CHISQR);
			if( tempHistCmp < leftHistCmp || leftHistCmp == -1)
			{
				leftHistCmp = tempHistCmp;
				leftLocale[0] = i;
				leftLocale[1] = k;
			}

			tempHistCmp = cvCompareHist(hist,_rightCharHist,CV_COMP_CHISQR);
			if(tempHistCmp < rightHistCmp || rightHistCmp == -1)
			{
				rightHistCmp = tempHistCmp;
				rightLocale[0] = i;
				rightLocale[1] = k;
			}

			cvResetImageROI(img);
			cvReleaseHist(&hist);
		}
	}

	_leftLocale = cvRect(_xStart+leftLocale[0]*_widthHalfBox,_yStart+leftLocale[1]*_heightHalfBox,_widthHalfBox*2,_heightHalfBox*2);
	_rightLocale = cvRect(_xStart+rightLocale[0]*_widthHalfBox,_yStart+rightLocale[1]*_heightHalfBox,_widthHalfBox*2,_heightHalfBox*2);
}



CvRect
SF4DisplayCharacter::GetCharLocale(bool leftRight)
{
	if(leftRight)
		return _leftLocale;
	else
		return _rightLocale;
}

int
SF4DisplayCharacter::GetCharHP(bool leftRight)
{
	if(leftRight)
		return _leftHP;
	else
		return _rightHP;
}

bool
SF4DisplayCharacter::DidCharTakeDamage(bool leftRight)
{
	return false;
	/*
	if(leftRight)
		if(_leftHP > 500)
			return false;
		else
			return true;
	else
		if(_rightHP > 500)
			return false;
		else
			return true;
	*/
}





bool
SF4DisplayCharacter::DetectRoundOne(IplImage * img)
{
	cvSetImageROI(img,cvRect(325,150,65,200));	
	CvHistogram * curHist = _ctRoundOne->FaasBGRHistogram(img);

	//TODO: Also add a check for full yellow in for both characters
	if(cvCompareHist(curHist,_whiteHist,CV_COMP_CHISQR) < 4000)
	{

		cvReleaseHist(&curHist);
		cvResetImageROI(img);
	
		return true;
	}

	cvReleaseHist(&curHist);
	cvResetImageROI(img);
	
	return false;


}