#pragma once

#include "cv.h"
#include <cxcore.h>
#include "highgui.h"

;
#include <mysql.h>
#include <iostream>
#include <my_global.h>
#pragma link "libmysql.lib" 
;

#include "..\..\..\..\GenericFunctions\FaasMySQLFunctions.h"
;

#include "..\..\..\..\GenericFunctions\ColorTheory.h"

;

class SF4DisplayCharacter{

public:
	bool _exitThread;

	SF4DisplayCharacter(bool);
	~SF4DisplayCharacter(); 

	void ProcessImage(IplImage * img);

	CvRect GetCharLocale(bool leftRight);
	int GetCharHP(bool leftRight);	
	bool DidCharTakeDamage(bool leftRight);
	bool GetAmILeft();

	bool DetectRoundOne(IplImage * img);
	void ProcessRoundOne(IplImage * img);

	
	IplImage * getCharImg(bool leftRight);
	

private:
	bool _drawScreen;
	bool _amILeft;	
	int _timeLeft;
	
	char * _leftName;
	int _leftCos;
	int _leftHP;	
	int _leftSuper;
	int _leftUltra;
	CvRect _leftLocale;

	char * _rightName;
	int _rightCos;
	int _rightHP;
	int _rightSuper;
	int _rightUltra;
	CvRect _rightLocale;

	FaasMySQLFunctions * _sqlFunc;
	ColorTheory * _ctCharDetect;
	ColorTheory * _ctHP;
	ColorTheory * _ctRoundOne;

	CvHistogram * _whiteHist;
	CvHistogram * _leftCharHist;
	CvHistogram * _rightCharHist;
	IplImage * _leftCharImg;
	IplImage * _rightCharImg;

	int _imgWidth;
	int _imgHeight;
	

	//Process Image
	void SetCharLocale(IplImage *);
	void SetCharHP(IplImage * img);

	int _xStart,_yStart,_widthHalfBox,_heightHalfBox, _xBoxes, _yBoxes;
	

	
}
