
#pragma once

#include "cv.h"
#include <cxcore.h>
#include "highgui.h"

#include "..\..\..\..\GenericFunctions\FaasMySQLFunctions.h"
;

#include <mysql.h>
#include <iostream>
#include <my_global.h>
#pragma link "libmysql.lib" 
;

#include "..\..\..\..\GenericFunctions\StartVideo.h"
;
#include "SF4Display.h"
;
#include "SF4Controller.h"
;
#include "SF4KenController.h"
;

#define TABLE_OF_INTEREST "char_hsv_info"
#define SERVER_NAME "localhost"
#define DB_USER "root"
#define DB_USERPASS "falconoclaf"
#define DB_NAME "ssf4_characters" 
;

class SF4Central
{

public:
	SF4Central(int vidNumber, char * fileName = NULL, int frames = -1);
	~SF4Central();

	void TestVideo();

	void ResumeGame();
	void PauseGame();
	void UseController(bool);
	void ThrowHadoken();
	void ResetDetect();

private:
	int _vidNumber;
	bool _exitThread;
	bool _useController;
	bool _hadokenAction;
	int _checkFor;
	bool _charCostDet;
	StartVideo * _sv;
	FaasMySQLFunctions * _sqlFunc;	

	//Not Setup in constructor
	//TODO: Later - Maybe should be?
	SF4Display * _sfD;
	SF4DisplayCharacter * _sfDC;
	SF4KenController * _sfKenC;	

	void ImagesAndActions();
	
	void ExtraDisplay(int valInt,IplImage * img);
	int DoSomethingBasedOnOneFrame(IplImage * img);
	void ControllerAction(CvRect leftRect,CvRect rightRect);

	
	int HadokenTesting();
	int HadokenTestingIncrease();

	int * intArr;
	FILE * writeThis;
	char tempStr[1024];

}