#pragma once

#include "stdafx.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
using namespace std;
;
#include "..\..\..\..\GenericFunctions\XIMCore.h"
;
#include "SF4KenController.h"
;

SF4KenController::SF4KenController()
{

}

SF4KenController::~SF4KenController()
{

}

//Ken Moves
/*
void
SF4KenController::Shoryuken(bool dir,int btn)
{
	ShoryukenMoveAndAttack(_ximInput,dir,btn);
}*/

void
SF4KenController::CustomHadoken(bool dir, int btn,int time1,int time2,int time3,int timeRest)
{
	int actions = CustomQuarterCircle(_ximInput,_actionTimes,dir,btn,time1,time2,time3,timeRest);
	if(!_ximExe->ExecuteActions(_ximInput,_actionTimes,actions))
		TRACE("Action did not happen, not done with the last action yet...\n\n");
	


}


void
SF4KenController::Hadoken(bool dir, int btn)
{
	int actions = QuarterCircle(_ximInput,_actionTimes,dir,btn);
	if(!_ximExe->ExecuteActions(_ximInput,_actionTimes,actions))
		TRACE("Action did not happen, not done with the last action yet...\n\n");
	

}
/*
void
SF4KenController::KenSuper(bool dir, int btn)
{
	SuperQuarterCircles(_ximInput,dir,btn);
}

void
SF4KenController::KenUltra(bool dir)
{
	SuperQuarterCircles(_ximInput,dir,15);
}

void
SF4KenController::CircleKicks(bool dir,int btn)
{
	InputDefault(_ximInput);

	QuarterCircle(_ximInput,!dir,btn);
}

void
SF4KenController::AirBorneCircleKicks(bool upDir, bool dir,int btn)
{
	InputDefault(_ximInput);

	int upDirection;
	if(upDir)
		upDirection = 0;
	else if(dir)
		upDirection = 10;
	else
		upDirection = 13;


	SimpleMovement(_ximInput,upDirection,true);
	cout << XIMSendXbox360Input(_ximInput,400) <<"\n";
	//Escape Circle kicks with upDirection=10+ && delay 75

	SimpleMovement(_ximInput,upDirection,false);
	cout << XIMSendXbox360Input(_ximInput,5) <<"\n";


	QuarterCircle(_ximInput,!dir,btn);
}


void 
SF4KenController::ForeHK(bool dir)
{
	int gotoDir;
	if(!dir)
		gotoDir = 3;
	else
		gotoDir = 1;

	InputDefault(_ximInput);
	XIMSendXbox360Input(_ximInput,10);

	SimpleButtonHit(_ximInput,5,true);
	SimpleMovement(_ximInput,gotoDir,true);
	cout << XIMSendXbox360Input(_ximInput,5) <<"\n";

	SimpleButtonHit(_ximInput,5,false);
	SimpleMovement(_ximInput,gotoDir,false);
	cout << XIMSendXbox360Input(_ximInput,30) <<"\n";

}



void 
SF4KenController::ForeMK(bool dir)
{
	BackMK(!dir);
}
void 
SF4KenController::BackMK(bool dir)
{
	int gotoDir;
	if(dir)
		gotoDir = 3;
	else
		gotoDir = 1;

	InputDefault(_ximInput);
	XIMSendXbox360Input(_ximInput,10);

	SimpleButtonHit(_ximInput,4,true);
	SimpleMovement(_ximInput,gotoDir,true);
	cout << XIMSendXbox360Input(_ximInput,20) <<"\n";

	SimpleButtonHit(_ximInput,4,false);
	SimpleMovement(_ximInput,gotoDir,false);
	cout << XIMSendXbox360Input(_ximInput,10) <<"\n";

}

void
SF4KenController::MPtoHP()
{

	InputDefault(_ximInput);
	//XIMSendXbox360Input(_ximInput,10);

	SimpleButtonHit(_ximInput,1,true);
	cout << XIMSendXbox360Input(_ximInput,5) <<"\n";

	SimpleButtonHit(_ximInput,1,false);
	SimpleButtonHit(_ximInput,2,true);
	cout << XIMSendXbox360Input(_ximInput,5) <<"\n";

	SimpleButtonHit(_ximInput,2,false);
	cout << XIMSendXbox360Input(_ximInput,15) <<"\n";

}
*/