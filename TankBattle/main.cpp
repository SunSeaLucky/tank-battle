#include <graphics.h>
#include <windows.h>
#include <conio.h>
#include "const.h"
#include "class.h"
#include "initMap.h"


void initMainUI();

int main() {

	initMainUI();

	return 0;
}

void initMainUI() {

	initgraph(graphWidth, graphHeight);
	//init game cover
	IMAGE logo, background,school_logo;
	loadimage(&logo, _T("Res/Images/logo.png"));
	loadimage(&background, _T("Res/Images/background.png"), graphWidth, graphHeight);
	loadimage(&school_logo, _T("Res/Images/school_logo.png"), 80, 80);
	putimage(0, 0, &background);
	putimage((graphWidth - logo.getwidth()) / 2, 30, &logo);
	putimage(60, 10, &school_logo, SRCPAINT);

	setbkmode(TRANSPARENT);//set transpanrent background color
	settextcolor(RED);
	settextstyle(80, 0, _T("Times New Roman"));
	outtextxy(200, 10, _T("TANK BATTLE"));
	settextcolor(WHITE);
	settextstyle(40, 0, _T("castellar"));

	class Rectangle typical, adventure, special;
	typical.width = 12 * 25;//12 characters
	adventure.width = 14 * 25;
	special.width = 12 * 25;
	
	RECT typicalPos = { (graphWidth - typical.width) / 2, 30 + logo.getheight() + 80,(graphWidth + typical.width) / 2,30 + logo.getheight() + 120 };
	RECT adventurelPos = { (graphWidth - adventure.width) / 2, 30 + logo.getheight() + 150,(graphWidth + adventure.width) / 2,30 + logo.getheight() + 190 };
	RECT specialPos = { (graphWidth - special.width) / 2, 30 + logo.getheight() + 220,(graphWidth + special.width) / 2,30 + logo.getheight() + 260 };

	drawtext(_T("TYPICAL MODE"), &typicalPos, DT_CENTER);
	drawtext(_T("ADVENTURE MODE"), &adventurelPos, DT_CENTER);
	drawtext(_T("SPECIAL MODE"), &specialPos, DT_CENTER);

	settextstyle(30, 0, _T("castellar"));
	outtextxy(200, 380, _T("USE A S D W TO MOVE, J TO FIRE"));
	settextstyle(20, 0, _T("castellar"));
	outtextxy(200, 450, _T("TANK BATTLE POWERED BY XJU SUNSEALUCKY"));
	settextstyle(40, 0, _T("castellar"));

	ExMessage m;
	while (true) {
		m = getmessage();

		switch (m.message) {
		//update every line's underline
		case WM_MOUSEMOVE:
			if ((m.x >= typicalPos.left) && (m.y >= typicalPos.top) && (m.x <= typicalPos.right) && (m.y <= typicalPos.bottom)) {
				line(typicalPos.left - 5, typicalPos.bottom + 5, typicalPos.right + 5, typicalPos.bottom + 5);
			}else if ((m.x >= adventurelPos.left) && (m.y >= adventurelPos.top) && (m.x <= adventurelPos.right) && (m.y <= adventurelPos.bottom)) {
				line(adventurelPos.left - 5, adventurelPos.bottom + 5, adventurelPos.right + 5, adventurelPos.bottom + 5);
			}else if ((m.x >= specialPos.left) && (m.y >= specialPos.top) && (m.x <= specialPos.right) && (m.y <= specialPos.bottom)) {
				line(specialPos.left - 5, specialPos.bottom + 5, specialPos.right + 5, specialPos.bottom + 5);
			}else {
				clearrectangle(typicalPos.left - 5, typicalPos.bottom + 5, typicalPos.right + 5, typicalPos.bottom + 5);
				clearrectangle(adventurelPos.left - 5, adventurelPos.bottom + 5, adventurelPos.right + 5, adventurelPos.bottom + 5);
				clearrectangle(specialPos.left - 5, specialPos.bottom + 5, specialPos.right + 5, specialPos.bottom + 5);
			}
			break;
		//judge which button is clicked
		case WM_LBUTTONDOWN:
			if ((m.x >= typicalPos.left) && (m.y >= typicalPos.top) && (m.x <= typicalPos.right) && (m.y <= typicalPos.bottom)) {
				cleardevice();
				initMap1();
				return;
			}else if ((m.x >= adventurelPos.left) && (m.y >= adventurelPos.top) && (m.x <= adventurelPos.right) && (m.y <= adventurelPos.bottom)) {
				cleardevice();
				initMap2();
				return;
			}else if ((m.x >= specialPos.left) && (m.y >= specialPos.top) && (m.x <= specialPos.right) && (m.y <= specialPos.bottom)) {
				cleardevice();
				initMap3();
				return;
			}
			break;
		default:
			break;
		}
	}
}