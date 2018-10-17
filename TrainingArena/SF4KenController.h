#pragma once
;
#include "..\..\..\..\GenericFunctions\XIMCore.h"
;
#include "SF4Controller.h"
;


class SF4KenController : public SF4Controller
{
public:
	SF4KenController();
	~SF4KenController();

	//Level 1 Combo
	void ForeHK(bool);
	void ForeMK(bool);
	void BackMK(bool);
	void MPtoHP();

	//Level 2 Combo
	void Hadoken(bool, int);
	void Shoryuken(bool,int);
	void CircleKicks(bool dir,int btn);
	void AirBorneCircleKicks(bool upDir, bool dir,int btn);
	void KenSuper(bool, int);
	void KenUltra(bool dir);

	void CustomHadoken(bool dir, int btn,int time1,int time2,int time3,int timeRest);

	//Level 3 Combo

private:

}
