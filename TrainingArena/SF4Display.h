#pragma once

#include "cv.h"
#include <cxcore.h>
#include "highgui.h"
;
#include "SF4DisplayCharacter.h"
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

class SF4Display{

public:
	SF4Display();
	~SF4Display();

	void DrawRectOutline(IplImage * img,CvRect leftRect,CvScalar rgbVal);

private:
	bool _drawScreen;
}
