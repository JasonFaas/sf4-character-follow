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
#include "SF4Controller.h"
;


SF4Controller::SF4Controller(){

	_maxActions = 100;
	_actionTimes = (int *)malloc(sizeof(int)*_maxActions);
	_ximInput = (XIMXbox360Input**)malloc(sizeof(XIMXbox360Input*)*_maxActions);	
	for(int i = 0;i<_maxActions;i++)
	{
		*(_actionTimes+i) = 1;
		*(_ximInput+i) = (XIMXbox360Input*)malloc(sizeof(XIMXbox360Input));
		InputDefault(*(_ximInput+i));
	}

	_ximExe = new XIMExecute();
	_ximExe->StartWaitForAction();



}

SF4Controller::~SF4Controller()
{
	TRACE("Think the extra free starts here");
	_ximExe->EndWaitForAction();
	delete _ximExe;

	free(_actionTimes);
	for(int i = 0;i<_maxActions;i++)
		free(*(_ximInput+i));

	free(_ximInput);
	TRACE("Think the extra free stops here");
}
/*
void
SF4Controller::Attack(int btn){
	InputDefault(_ximInput);

	//ButtonHit(_ximInput,btn,true);
	SimpleMovement(_ximInput,btn,true);
	cout << XIMSendXbox360Input(_ximInput,10) <<"\n";
	//ButtonHit(_ximInput,btn,false);
	SimpleMovement(_ximInput,btn,false);
	cout << XIMSendXbox360Input(_ximInput,10) <<"\n";
	//Sleep(500);
}


void 
SF4Controller::MoveCloser(bool lOrR)
{
	InputDefault(_ximInput);
	int btn;
	if(lOrR)
		btn = 1;
	else
		btn = 3;

	SimpleMovement(_ximInput,btn,true);
	cout << XIMSendXbox360Input(_ximInput,10) <<"\n";

	SimpleMovement(_ximInput,btn,false);
	cout << XIMSendXbox360Input(_ximInput,10) <<"\n";
}

void 
SF4Controller::Throw(bool dir)
{
	int gotoDir;
	if(dir)
		gotoDir = 1;
	else
		gotoDir = 3;

	InputDefault(_ximInput);

	SimpleButtonHit(_ximInput,10,true);
	SimpleMovement(_ximInput,gotoDir,true);
	cout << XIMSendXbox360Input(_ximInput,10) <<"\n";

	SimpleButtonHit(_ximInput,10,false);
	SimpleMovement(_ximInput,gotoDir,false);
	cout << XIMSendXbox360Input(_ximInput,10) <<"\n";
}

*/
void
SF4Controller::InputDefault(XIMXbox360Input ** ximInput,int actions)
{
	for(int i = 0;i<actions;i++)
		InputDefault(*(ximInput+i));
}

void
SF4Controller::InputDefault(XIMXbox360Input * ximMe){
	ximMe->RightBumper = false;
	ximMe->RightStick = false;
	ximMe->LeftBumper = false;
	ximMe->LeftStick = false;
	ximMe->A = false;
	ximMe->B = false;
	ximMe->X = false;
	ximMe->Y = false;
	ximMe->Up = false;
	ximMe->Down = false;
	ximMe->Left = false;
	ximMe->Right = false;
	ximMe->Start = false;
	ximMe->Back = false;
	ximMe->Guide = false;
	ximMe->RightStickX = 0;
	ximMe->RightStickY = 0;
	ximMe->LeftStickX = 0;
	ximMe->LeftStickY = 0;
	ximMe->RightTrigger = 0;
	ximMe->LeftTrigger = 0;
}


void
SF4Controller::SimpleButtonHit(XIMXbox360Input * ximMe, int i, bool hitBtn)
{
	//i is specific to what action you want

	//0 = lp
	//1 = mp
	//2 = hp
	//3 = lk
	//4 = mk
	//5 = hk

	//10 = Grab
	//11 = Focus

	//15 = triplePunch
	//16 = tripleKick


	switch(i)
	{
	case 0:	ximMe->X = hitBtn;
		break;
	case 1: ximMe->Y = hitBtn;
		break;
	case 2: ximMe->LeftBumper = hitBtn;
		break;
	case 3: ximMe->A = hitBtn;
		break;
	case 4: ximMe->B = hitBtn;
		break;
	case 5: ximMe->RightBumper = hitBtn;
		break;

	case 10: ximMe->X = hitBtn;
		ximMe->A = hitBtn;
		break;
	case 11: ximMe->Y = hitBtn;
		ximMe->B = hitBtn;
		break;
	case 15: ximMe->X = hitBtn;
		ximMe->Y = hitBtn;
		ximMe->LeftBumper = hitBtn;
		break;
	case 16: ximMe->A = hitBtn;
		ximMe->B = hitBtn;
		ximMe->RightBumper = hitBtn;
		break;
	default:
		TRACE("SHould not get to bad XIM Simple Button Hit\n");
		exit(0);
	}
}

void
SF4Controller::SimpleMovement(XIMXbox360Input * ximMe, int move, bool hitDpad)
{
	//i is specific to what action you want

	//0 = Up
	//1 = Right
	//2 = Down
	//3 = Left


	//10 = Up&Right
	//11 = Down&Right
	//12 = Down&Left
	//13 = Up&Left

	switch(move)
	{
	case 0:	ximMe->Up = hitDpad;
		break;
	case 1: ximMe->Right = hitDpad;
		break;
	case 2: ximMe->Down = hitDpad;
		break;
	case 3: ximMe->Left = hitDpad;
		break;

	case 10: ximMe->Up = hitDpad;
		ximMe->Right = hitDpad;
		break;
	case 11: ximMe->Down = hitDpad;
		ximMe->Right = hitDpad;
		break;
	case 12: ximMe->Down = hitDpad;
		ximMe->Left = hitDpad;
		break;
	case 13: ximMe->Up = hitDpad;
		ximMe->Left = hitDpad;
		break;
	default:
		TRACE("SHould not get to bad XIM Simple Movement\n");
		exit(0);
	}
}
/*

void
SF4Controller::ShoryukenMoveAndAttack(XIMXbox360Input * ximMe,bool dir,int btn)
{
	InputDefault(ximMe);


	int gotoDir;
	if(dir)	
		gotoDir = 1;
	else
		gotoDir = 3;

	SimpleMovement(ximMe,gotoDir,true);
	cout << XIMSendXbox360Input(ximMe,15) <<"\n";

	SimpleMovement(ximMe,gotoDir,false);
	SimpleMovement(ximMe,2,true);
	cout << XIMSendXbox360Input(ximMe,15) <<"\n";

	SimpleMovement(ximMe,gotoDir,true);
	SimpleButtonHit(ximMe,btn,true);
	cout << XIMSendXbox360Input(ximMe,15) <<"\n";

	SimpleButtonHit(ximMe,btn,false);
	SimpleMovement(ximMe,gotoDir,false);
	SimpleMovement(ximMe,2,false);
	cout << XIMSendXbox360Input(ximMe,250) <<"\n";

}
*/
int
SF4Controller::CustomQuarterCircle(XIMXbox360Input ** ximMe,int * delayTimes,bool dir,int btn,int time1,int time2,int time3,int timeRest)
{
	//InputDefault(ximMe);
	int curXIM = 0;

	int gotoDir;
	if(dir)	
		gotoDir = 1;
	else
		gotoDir = 3;

	//TODO: Later - Remove 2 with "DOWN"
	InputDefault(*(ximMe+curXIM));
	SimpleMovement(*(ximMe+curXIM),2,true);
	*(delayTimes+curXIM) = time1;
	curXIM++;

	InputDefault(*(ximMe+curXIM));
	SimpleMovement(*(ximMe+curXIM),2,true);
	SimpleMovement(*(ximMe+curXIM),gotoDir,true);
	*(delayTimes+curXIM) = time2;
	curXIM++;

	InputDefault(*(ximMe+curXIM));
	SimpleMovement(*(ximMe+curXIM),gotoDir,true);
	SimpleButtonHit(*(ximMe+curXIM),btn,true);
	*(delayTimes+curXIM) = time3;
	curXIM++;

	InputDefault(*(ximMe+curXIM));
	*(delayTimes+curXIM) = timeRest;
	curXIM++;

	return curXIM;
}


int
SF4Controller::QuarterCircle(XIMXbox360Input ** ximMe,int * delayTimes,bool dir,int btn)
{
	//Good times, can be optimized a few more milliseconds, but fewer than 5*3
	return CustomQuarterCircle(ximMe,delayTimes,dir,btn,20,25,20,100);
}

/*
void
SF4Controller::SuperQuarterCircles(XIMXbox360Input * ximMe,bool dir,int btn)
{
	InputDefault(ximMe);

	int gotoDir;
	if(dir)	
		gotoDir = 1;
	else
		gotoDir = 3;

	SimpleMovement(ximMe,2,true);
	cout << XIMSendXbox360Input(ximMe,15) <<"\n";

	SimpleMovement(ximMe,gotoDir,true);
	cout << XIMSendXbox360Input(ximMe,15) <<"\n";

	SimpleMovement(ximMe,2,false);
	cout << XIMSendXbox360Input(ximMe,15) <<"\n";

	SimpleMovement(ximMe,gotoDir,false);
	SimpleMovement(ximMe,2,true);
	cout << XIMSendXbox360Input(ximMe,15) <<"\n";

	SimpleMovement(ximMe,gotoDir,true);
	cout << XIMSendXbox360Input(ximMe,15) <<"\n";

	SimpleMovement(ximMe,2,false);
	SimpleButtonHit(ximMe,btn,true);
	cout << XIMSendXbox360Input(ximMe,15) <<"\n";

	SimpleButtonHit(ximMe,btn,false);
	SimpleMovement(ximMe,gotoDir,false);
	cout << XIMSendXbox360Input(ximMe,250) <<"\n";
}
*/