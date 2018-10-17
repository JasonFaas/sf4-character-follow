#pragma once
;
#include "..\..\..\..\GenericFunctions\XIMCore.h"
;
#include "..\..\..\..\GenericFunctions\XIMExecute.h"
;

class SF4Controller{

public:
	SF4Controller();
	~SF4Controller();  

	void Attack(int);

	void MoveCloser(bool);
	void Throw(bool);

protected:

	XIMXbox360Input ** _ximInput;
	int * _actionTimes;
	int _maxActions;
	XIMExecute * _ximExe;

	void InputDefault(XIMXbox360Input * ximMe);
	void InputDefault(XIMXbox360Input ** ximInput,int actions);

	void SimpleButtonHit(XIMXbox360Input * ximMe, int i, bool hitBtn);
	void SimpleMovement(XIMXbox360Input * ximMe, int move, bool hitBtn);

	int QuarterCircle(XIMXbox360Input ** ximMe,int * delaytimes,bool dir,int btn);
	void ShoryukenMoveAndAttack(XIMXbox360Input * ximMe,bool dir,int btn);
	void SuperQuarterCircles(XIMXbox360Input * ximMe,bool dir,int btn);

	int CustomQuarterCircle(XIMXbox360Input ** ximMe,int * delayTimes,bool dir,int btn,int time1,int time2,int time3,int timeRest);

}
