
#include "stdafx.h"

#include "SF4Central.h"
;

SF4Central::SF4Central(int vidNumber, char * fileName, int frames)
{
	_vidNumber = vidNumber;
	TRACE("Here 1\n");
	_sqlFunc = new FaasMySQLFunctions();	
	TRACE("Here 2\n");
	_sv = new StartVideo(_vidNumber,fileName,frames);
	TRACE("Here 3\n");
	_exitThread = false;
	_useController = false;
	_sfKenC = NULL;
	_hadokenAction = NULL;


	intArr = (int *)malloc(sizeof(int)*3);
	*(intArr+0) = 1;
	*(intArr+1) = 1;
	*(intArr+2) = 1;

	_checkFor = -1;


	writeThis = fopen("hitTimes.txt","w");
	
}

SF4Central::~SF4Central()
{	
	fclose(writeThis);
	free(intArr);
	delete _sv;
	delete _sqlFunc;
	delete _sfKenC;
}

void
SF4Central::TestVideo()
{
	_sv->Start();

	

	IplImage* frame;
	do
	{
		frame = _sv->GetIplImage();
	}
	while(!_sv->DisplayIplImage(frame));

	_sv->End();
}

void
SF4Central::PauseGame()
{
	_exitThread = true;
}

void
SF4Central::UseController(bool useControl)
{
	_useController = useControl;
}

void
SF4Central::ResetDetect()
{
	_charCostDet = false;
}

void
SF4Central::ThrowHadoken()
{
	_hadokenAction = true;
}

void
SF4Central::ResumeGame()
{
	//Setting up for Images and Actions
	TRACE("Setting up SF4Display\n");
	_sfD = new SF4Display();
	_sfDC = new SF4DisplayCharacter(true);

	TRACE("Setting up SF4Controller\n");
	_sfKenC = new SF4KenController();

	TRACE("Starting up Video\n");
	_sv->Start();
	//End Setup

	//This is this action
	ImagesAndActions();

	//Tear down
	_sv->End();
	delete _sfD;
	delete _sfDC;
}

void
SF4Central::ImagesAndActions()
{

	IplImage* frame;
	int retInt = 0;
	bool escExit = false;
	_charCostDet = false;

	TRACE("Starting actual do-while loop\n\n");
	do
	{
		frame = _sv->GetIplImage();
		if(_charCostDet)
		{
			_sfDC->ProcessImage(frame);
			retInt = DoSomethingBasedOnOneFrame(frame);
			ExtraDisplay(retInt,frame);
		}
		else
		{
			if(_sfDC->DetectRoundOne(frame))
			{
				//TODO: delete this, just part of the test
				while(!_sv->DisplayIplImage(frame)){}

				_sfDC->ProcessRoundOne(frame);				
				_charCostDet = true;
			}
		}

		escExit = _sv->DisplayIplImage(frame);
	}
	while(!escExit && !_exitThread && retInt >= 0);
}

void
SF4Central::ExtraDisplay(int valInt,IplImage * img)
{
	if(valInt == 0)
	{
		return;
	}
	else if(valInt == 1)
	{
		cvRectangle(img,cvPoint(10,10),cvPoint(300,300),CV_RGB(0,255,0),CV_FILLED,8,0);
			for(int i = 0;i<11;i++)
				_sv->DisplayIplImage(img);
			for(int i = 0;i<11*2;i++)
			{
				img = _sv->GetIplImage();
				cvRectangle(img,cvPoint(10,10),cvPoint(300,300),CV_RGB(0,200,200),CV_FILLED,8,0);
				_sv->DisplayIplImage(img);
				Sleep(100);
			}
	}	

}

void
SF4Central::ControllerAction(CvRect myRect,CvRect theirRect)
{
	bool amILeft = _sfDC->GetAmILeft();
	CvPoint screenSize = {720,480};
	
	if(abs(theirRect.x-myRect.x)<=screenSize.x/3)
	{
		//Actually doing a circle kick
		_sfKenC->Hadoken(!myRect.x<theirRect.x,4);
	}
	else
	{
		_sfKenC->Hadoken(myRect.x<theirRect.x,1);
	}

	//TRACE("Running into the fight\n");
	/*
	if(retInt>0)
	sfKenC->AirBorneCircleKicks(false,false,4);

	else
	sfKenC->AirBorneCircleKicks(false,true,5);

	if(retInt>0)
	sfKenC->Shoryuken(false,2);

	else
	sfKenC->Shoryuken(true,0);
	*/	
	/*
	if(retInt>0)
	sfKenC->KenUltra(false);

	else
	sfKenC->KenUltra(true);


	}
	else
	{
	if(retInt<0)
	sfKenC->MoveCloser(false);
	else
	sfKenC->MoveCloser(true);

	}

	//sfKenC->ForeHK(true);

	//sfKenC->Throw(false);




	*/

}



int
SF4Central::DoSomethingBasedOnOneFrame(IplImage * img)
{
	bool amILeft = _sfDC->GetAmILeft();
	CvRect myRect = _sfDC->GetCharLocale(amILeft);
	CvRect theirRect = _sfDC->GetCharLocale(!amILeft);

	if(_useController)
		ControllerAction(myRect,theirRect);
	else if(_hadokenAction && _checkFor == -1 && *(intArr+2) > -1)
	{
		//TODO: Later - will remove all this HadokenTesting

		TRACE("Trying to Hadoken with %i:%i:%i\n",*(intArr+0),*(intArr+1),*(intArr+2));
		sprintf(tempStr,"Hadoken with %i:%i:%i\n",*(intArr+0),*(intArr+1),*(intArr+2));
		fwrite(tempStr,strlen(tempStr),1,writeThis);

		_sfKenC->CustomHadoken(myRect.x<theirRect.x,1,*(intArr+0),*(intArr+1),*(intArr+2),200);
		//_sfKenC->Hadoken(myRect.x<theirRect.x,1);

		
		if(HadokenTestingIncrease() == -1)
			return -1;
		
		_checkFor = 90;
		
		_hadokenAction = false;
	}
	else if(_checkFor>=0)
	{
		int retInt = HadokenTesting();
		if(retInt == 1)
			return 1;
		else if(retInt == 2)
		{
			cvRectangle(img,cvPoint(10,10),cvPoint(100,100),CV_RGB(255,0,0),CV_FILLED,8,0);
		}
	}

	//Draw boxes around characters
	_sfD->DrawRectOutline(img,myRect,CV_RGB(255,0,0));
	_sfD->DrawRectOutline(img,theirRect,CV_RGB(0,0,255));

	return 0;
}

int
SF4Central::HadokenTestingIncrease()
{

	(*(intArr+0))+=10;
		if(*(intArr+0)>25)
		{
			*(intArr+0) = 1;
			(*(intArr+1))+=10;
		}
		if(*(intArr+1)>25)
		{
			*(intArr+1) = 1;
			(*(intArr+2))+=10;
		}
		if(*(intArr+2)>25)
		{
			*(intArr+2) = -1;
			return -1;
		}
		return 0;
		
}


int
SF4Central::HadokenTesting()
{
	if(_checkFor > 1 && _sfDC->GetCharHP(false)<1500)
	{
		TRACE("Hadoken Hit\n\n");
		TRACE("Sleeping for health refresh\n");
		fwrite("\t\t\t\tHadoken Hit\n",strlen("\t\t\t\tHadoken Hit\n"),1,writeThis);

		Sleep(1000);
		_checkFor = -1;
		return 1;
	}
	else if(_checkFor > 1)
	{		
		_checkFor--;
		return 2;
	}
	else if(_checkFor == 1)
	{
		TRACE("Hadoken did not Hit\n");
		fwrite("Hadoken did not Hit\n",strlen("Hadoken did not Hit\n"),1,writeThis);
		_checkFor = -1;
	}

	return 0;
}
