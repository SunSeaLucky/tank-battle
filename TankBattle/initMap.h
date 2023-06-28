#pragma once

class Tank our, enemy_1, enemy_2;

void initMap1();
void updateMap1();
void winEndMap1();
void loseEndMap1();

void initMap2();
void updateMap2();
void winEndMap2();
void loseEndMap2();

void initMap3();
void updateMap3();
void winEndMap3();
void loseEndMap3();


//functions about map1
void initMap1() {
	mapType = 1;

	PlaySound(TEXT("Res\\Sounds\\TypicalMode\\background.wav"), NULL, SND_FILENAME | SND_ASYNC);

	IMAGE wall_1, wall_2, bird;
	loadimage(&wall_1, _T("Res/Images/TypicalMode/wall_1.png"), 25, 25);
	loadimage(&wall_2, _T("Res/Images/TypicalMode/wall_2.png"), 25, 25);
	loadimage(&bird, _T("Res/Images/TypicalMode/bird.png"), 50, 50);

	loadimage(&our.bullet.img_bullet, _T("Res/Images/TypicalMode/bullet.png"), our.bullet.width, our.bullet.height);
	loadimage(&enemy_1.bullet.img_bullet, _T("Res/Images/TypicalMode/bullet.png"), enemy_1.bullet.width, enemy_1.bullet.height);
	loadimage(&enemy_2.bullet.img_bullet, _T("Res/Images/TypicalMode/bullet.png"), enemy_2.bullet.width, enemy_2.bullet.height);
	enemy_1.x = 4 * 25, enemy_1.y = 1 * 25;
	enemy_1.direction = DOWN;
	enemy_1.enemy = 4;

	enemy_2.x = 18 * 25, enemy_2.y = 5 * 25;
	enemy_2.direction = DOWN;
	enemy_2.enemy = 4;


	loadimage(&our.tank_up, _T("Res/Images/TypicalMode/our_tank_up.png"), our.width, our.height);
	loadimage(&our.tank_down, _T("Res/Images/TypicalMode/our_tank_down.png"), our.width, our.height);
	loadimage(&our.tank_right, _T("Res/Images/TypicalMode/our_tank_right.png"), our.width, our.height);
	loadimage(&our.tank_left, _T("Res/Images/TypicalMode/our_tank_left.png"), our.width, our.height);

	loadimage(&enemy_1.tank_up, _T("Res/Images/TypicalMode/enemy_tank_up.png"), enemy_1.width, enemy_1.height);
	loadimage(&enemy_1.tank_down, _T("Res/Images/TypicalMode/enemy_tank_down.png"), enemy_1.width, enemy_1.height);
	loadimage(&enemy_1.tank_right, _T("Res/Images/TypicalMode/enemy_tank_right.png"), enemy_1.width, enemy_1.height);
	loadimage(&enemy_1.tank_left, _T("Res/Images/TypicalMode/enemy_tank_left.png"), enemy_1.width, enemy_1.height);

	loadimage(&enemy_2.tank_up, _T("Res/Images/TypicalMode/enemy_tank_up.png"), enemy_2.width, enemy_2.height);
	loadimage(&enemy_2.tank_down, _T("Res/Images/TypicalMode/enemy_tank_down.png"), enemy_2.width, enemy_2.height);
	loadimage(&enemy_2.tank_right, _T("Res/Images/TypicalMode/enemy_tank_right.png"), enemy_2.width, enemy_2.height);
	loadimage(&enemy_2.tank_left, _T("Res/Images/TypicalMode/enemy_tank_left.png"), enemy_2.width, enemy_2.height);


	int x = 0, y = 0;
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 35; j++) {
			switch (map1[i][j])
			{
			case 1:
				putimage(x, y, &wall_1);
				break;
			case 2:
				putimage(x, y, &wall_2);
				break;
			case 3:
				putimage(x, y, &bird);
				break;
			case 4:
				putimage(x, y, &our.tank_up);
				our.x = x;
				our.y = y;
				our.direction = UP;
				our.enemy = 5;
				break;
			case 5:
				putimage(x, y, &enemy_1.tank_down);
				break;
			}
			if (j < 34) x += 25;
			else if (j == 34) {
				x = 0;
				y += 25;
			}
		}
	}

	updateMap1();
}

void updateMap1() {
	int systemTime = 0;
	int fresh = 0;
	while (true) {
		systemTime++;
		if (_kbhit()) {
			switch (_getch())
			{
			case 'A':
			case 'a':
				our.moveTank(LEFT);
				break;
			case 'S':
			case 's':
				our.moveTank(DOWN);
				break;
			case 'D':
			case 'd':
				our.moveTank(RIGHT);
				break;
			case 'W':
			case 'w':
				our.moveTank(UP);
				break;
			case 'J':
			case 'j':
				if (our.bullet.status == 1) our.fireBullet();
				break;
			case 'P':
			case 'p':
				system("pause");
				break;
			}
		}

		if (our.bullet.status != 1) our.fireBullet();

		enemy_1.fireBullet();
		enemy_2.fireBullet();


		int tempTime = systemTime / 60;

		if (tempTime == ((systemTime - 1) / 60 + 1)) {
			//activate enemy_tank_1
			if (map1_enemy_1_path[tempTime] != STOP) enemy_1.moveTank(map1_enemy_1_path[tempTime]);
			//activate enemy_tank_2
			if (map1_enemy_2_path[tempTime] != STOP) enemy_2.moveTank(map1_enemy_2_path[tempTime]);
		}


		if (!our.updateLive() || map1[21][12] != 3) break;

		if (!enemy_1.updateLive() && !enemy_2.updateLive()) {
			if (fresh < 3) {//rebirth enemy tank
				systemTime = 0;
				enemy_1.x = 4 * 25, enemy_1.y = 1 * 25;
				map1[1][4] = 5, map1[1][5] = -1;
				enemy_1.direction = DOWN;
				putimage(enemy_1.x, enemy_1.y, &enemy_1.tank_down);

				enemy_2.x = 18 * 25, enemy_2.y = 5 * 25;
				map1[5][18] = 5, map1[5][19] = -3;
				enemy_2.direction = DOWN;
				putimage(enemy_2.x, enemy_2.y, &enemy_2.tank_down);

				fresh++;
			}else break;
		}



	}

	if (!our.updateLive() || map1[21][12] != 3) loseEndMap1();
	else winEndMap1();

}

void winEndMap1() {
	cleardevice();
	RECT loseText = { 100,50,750,90 };
	RECT scoreText = { 100,50,750,90 };
	RECT destroyedTankText = { 100,50,750,90 };
	settextcolor(RED);
	outtextxy(140, 50, _T("YOU WIN! YOU HAVE BRUSHES!"));
	settextcolor(WHITE);

	TCHAR temp[10];

	//display score
	outtextxy(140, 100, _T("SCORE:"));
	_itot_s(score, temp, 10);
	outtextxy(600, 100, temp);

	//display destroyed tank number
	outtextxy(140, 150, _T("DESTRYOED TANKS:"));
	_itot_s(destroyedTank, temp, 10);
	outtextxy(600, 150, temp);


	//dispaly level of waste
	outtextxy(140, 200, _T("LEVEL OF WASTE:"));
	_itot_s(1000 - score / 7, temp, 10);
	outtextxy(600, 200, temp);

	// display logo
	settextstyle(20, 0, _T("castellar"));
	settextcolor(RED);
	outtextxy(200, 450, _T("TANK BATTLE POWERED BY XJU SUNSEALUCKY"));

	while (true);
}

void loseEndMap1() {
	cleardevice();
	RECT loseText = { 100,50,750,90 };
	RECT scoreText = { 100,50,750,90 };
	RECT destroyedTankText = { 100,50,750,90 };
	settextcolor(RED);
	outtextxy(140, 50, _T("YOU LOSE! GO BACK HOME BOY!"));
	settextcolor(WHITE);

	TCHAR temp[10];

	//display score
	outtextxy(140, 100, _T("SCORE:"));
	_itot_s(score, temp, 10);
	outtextxy(600, 100, temp);

	//display destroyed tank number
	outtextxy(140, 150, _T("DESTRYOED TANKS:"));
	_itot_s(destroyedTank, temp, 10);
	outtextxy(600, 150, temp);

	//dispaly level of waste
	outtextxy(140, 200, _T("LEVEL OF WASTE:"));
	_itot_s(1000 - score / 7, temp, 10);
	outtextxy(600, 200, temp);

	//display logo
	settextstyle(20, 0, _T("castellar"));
	settextcolor(RED);
	outtextxy(200, 450, _T("TANK BATTLE POWERED BY XJU SUNSEALUCKY"));

	while (true);
}


//functions about map2
void initMap2() {

	mapType = 2;
	
	PlaySound(TEXT("Res\\Sounds\\AdventureMode\\backgroundMusicHuaQiangBuyWatermelon.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	IMAGE wall_1, wall_2, bird;
	
	loadimage(&wall_1, _T("Res/Images/AdventureMode/wall_1.png"), 25, 25);
	loadimage(&wall_2, _T("Res/Images/AdventureMode/wall_2.png"), 25, 25);
	loadimage(&bird, _T("Res/Images/AdventureMode/bird.png"), 50, 50);
	

	our.bullet.width = 15;
	our.bullet.height = 15;
	enemy_1.bullet.width = 15;
	enemy_1.bullet.height = 15;
	enemy_2.bullet.width = 15;
	enemy_2.bullet.height = 15;
	loadimage(&our.bullet.img_bullet, _T("Res/Images/AdventureMode/bullet.png"), our.bullet.width, our.bullet.height);
	loadimage(&enemy_1.bullet.img_bullet, _T("Res/Images/AdventureMode/bullet.png"), enemy_1.bullet.width, enemy_1.bullet.height);
	loadimage(&enemy_2.bullet.img_bullet, _T("Res/Images/AdventureMode/bullet.png"), enemy_2.bullet.width, enemy_2.bullet.height);
	enemy_1.x = 4 * 25, enemy_1.y = 1 * 25;
	enemy_1.direction = DOWN;
	enemy_1.enemy = 4;

	enemy_2.x = 18 * 25, enemy_2.y = 5 * 25;
	enemy_2.direction = DOWN;
	enemy_2.enemy = 4;


	loadimage(&our.tank_up, _T("Res/Images/AdventureMode/our_tank_up.png"), our.width, our.height);
	loadimage(&our.tank_down, _T("Res/Images/AdventureMode/our_tank_down.png"), our.width, our.height);
	loadimage(&our.tank_right, _T("Res/Images/AdventureMode/our_tank_right.png"), our.width, our.height);
	loadimage(&our.tank_left, _T("Res/Images/AdventureMode/our_tank_left.png"), our.width, our.height);

	loadimage(&enemy_1.tank_up, _T("Res/Images/AdventureMode/enemy_tank_up.png"), enemy_1.width, enemy_1.height);
	loadimage(&enemy_1.tank_down, _T("Res/Images/AdventureMode/enemy_tank_down.png"), enemy_1.width, enemy_1.height);
	loadimage(&enemy_1.tank_right, _T("Res/Images/AdventureMode/enemy_tank_right.png"), enemy_1.width, enemy_1.height);
	loadimage(&enemy_1.tank_left, _T("Res/Images/AdventureMode/enemy_tank_left.png"), enemy_1.width, enemy_1.height);

	loadimage(&enemy_2.tank_up, _T("Res/Images/AdventureMode/enemy_tank_up.png"), enemy_2.width, enemy_2.height);
	loadimage(&enemy_2.tank_down, _T("Res/Images/AdventureMode/enemy_tank_down.png"), enemy_2.width, enemy_2.height);
	loadimage(&enemy_2.tank_right, _T("Res/Images/AdventureMode/enemy_tank_right.png"), enemy_2.width, enemy_2.height);
	loadimage(&enemy_2.tank_left, _T("Res/Images/AdventureMode/enemy_tank_left.png"), enemy_2.width, enemy_2.height);


	int x = 0, y = 0;
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 35; j++) {
			switch (map1[i][j])
			{
			case 1:
				putimage(x, y, &wall_1);
				break;
			case 2:
				putimage(x, y, &wall_2);
				break;
			case 3:
				putimage(x, y, &bird);
				break;
			case 4:
				putimage(x, y, &our.tank_up);
				our.x = x;
				our.y = y;
				our.direction = UP;
				our.enemy = 5;
				break;
			case 5:
				putimage(x, y, &enemy_1.tank_down);
				break;
			}
			if (j < 34) x += 25;
			else if (j == 34) {
				x = 0;
				y += 25;
			}
		}
	}

	updateMap2();
}

void updateMap2() {
	int systemTime = 0;
	int fresh = 0;
	while (true) {
		systemTime++;
		if (_kbhit()) {
			switch (_getch())
			{
			case 'A':
			case 'a':
				our.moveTank(LEFT);
				break;
			case 'S':
			case 's':
				our.moveTank(DOWN);
				break;
			case 'D':
			case 'd':
				our.moveTank(RIGHT);
				break;
			case 'W':
			case 'w':
				our.moveTank(UP);
				break;
			case 'J':
			case 'j':
				if (our.bullet.status == 1) our.fireBullet();
				break;
			case 'P':
			case 'p':
				system("pause");
				break;
			}
		}

		if (our.bullet.status != 1) our.fireBullet();

		enemy_1.fireBullet();
		enemy_2.fireBullet();


		int tempTime = systemTime / 60;

		if (tempTime == ((systemTime - 1) / 60 + 1)) {
			//activate enemy_tank_1
			if (map1_enemy_1_path[tempTime] != STOP) enemy_1.moveTank(map1_enemy_1_path[tempTime]);
			//activate enemy_tank_2
			if (map1_enemy_2_path[tempTime] != STOP) enemy_2.moveTank(map1_enemy_2_path[tempTime]);
		}


		if (!our.updateLive() || map1[21][12] != 3) break;

		if (!enemy_1.updateLive() && !enemy_2.updateLive()) {
			if (fresh < 3) {//rebirth enemy tank
				systemTime = 0;
				enemy_1.x = 4 * 25, enemy_1.y = 1 * 25;
				map1[1][4] = 5, map1[1][5] = -1;
				enemy_1.direction = DOWN;
				putimage(enemy_1.x, enemy_1.y, &enemy_1.tank_down);

				enemy_2.x = 18 * 25, enemy_2.y = 5 * 25;
				map1[5][18] = 5, map1[5][19] = -3;
				enemy_2.direction = DOWN;
				putimage(enemy_2.x, enemy_2.y, &enemy_2.tank_down);

				fresh++;
			}
			else break;
		}



	}

	if (!our.updateLive() || map1[21][12] != 3) loseEndMap2();
	else winEndMap2();

}

void winEndMap2() {
	PlaySound(TEXT("Res\\Sounds\\AdventureMode\\win.wav"), NULL, SND_FILENAME | SND_ASYNC);
	cleardevice();
	RECT loseText = { 100,50,750,90 };
	RECT scoreText = { 100,50,750,90 };
	RECT destroyedTankText = { 100,50,750,90 };
	settextcolor(RED);
	outtextxy(140, 50, _T("SUCCESS! YOU PROTECT STALL!"));
	settextcolor(WHITE);

	TCHAR temp[10];

	//display score
	outtextxy(140, 100, _T("SCORE:"));
	_itot_s(score, temp, 10);
	outtextxy(600, 100, temp);

	//display destroyed tank number
	outtextxy(140, 150, _T("DESTRYOED HUA QIANG:"));
	_itot_s(destroyedTank, temp, 10);
	outtextxy(600, 150, temp);


	//dispaly level of waste
	outtextxy(140, 200, _T("LEVEL OF WASTE:"));
	_itot_s(1000 - score / 7, temp, 10);
	outtextxy(600, 200, temp);

	// display logo
	settextstyle(20, 0, _T("castellar"));
	settextcolor(RED);
	outtextxy(200, 450, _T("TANK BATTLE POWERED BY XJU SUNSEALUCKY"));


	while (true);
}

void loseEndMap2() {
	PlaySound(TEXT("Res\\Sounds\\AdventureMode\\lose.wav"), NULL, SND_FILENAME | SND_ASYNC);
	cleardevice();
	RECT loseText = { 100,50,750,90 };
	RECT scoreText = { 100,50,750,90 };
	RECT destroyedTankText = { 100,50,750,90 };
	settextcolor(RED);
	outtextxy(140, 50, _T("FAIL! YOU WAS KILLED!"));
	settextcolor(WHITE);

	TCHAR temp[10];

	//display score
	outtextxy(140, 100, _T("SCORE:"));
	_itot_s(score, temp, 10);
	outtextxy(600, 100, temp);

	//display destroyed tank number
	outtextxy(140, 150, _T("DESTRYOED QIANG:"));
	_itot_s(destroyedTank, temp, 10);
	outtextxy(600, 150, temp);

	//dispaly level of waste
	outtextxy(140, 200, _T("LEVEL OF WASTE:"));
	_itot_s(1000 - score / 7, temp, 10);
	outtextxy(600, 200, temp);

	//display logo
	settextstyle(20, 0, _T("castellar"));
	settextcolor(RED);
	outtextxy(200, 450, _T("TANK BATTLE POWERED BY XJU SUNSEALUCKY"));


	while (true);
}


//functions about map3
void initMap3() {

	mapType = 3;
	
	PlaySound(TEXT("Res\\Sounds\\SpecialMode\\backgroundmusic.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	
	IMAGE wall_1, wall_2, bird;
	loadimage(&wall_1, _T("Res/Images/SpecialMode/wall_1.png"), 25, 25);
	loadimage(&wall_2, _T("Res/Images/SpecialMode/wall_2.png"), 25, 25);
	loadimage(&bird, _T("Res/Images/SpecialMode/bird.png"), 50, 50);

	our.bullet.width = 15;
	our.bullet.height = 15;
	enemy_1.bullet.width = 15;
	enemy_1.bullet.height = 15;
	enemy_2.bullet.width = 15;
	enemy_2.bullet.height = 15;
	loadimage(&our.bullet.img_bullet, _T("Res/Images/SpecialMode/bullet.png"), our.bullet.width, our.bullet.height);
	loadimage(&enemy_1.bullet.img_bullet, _T("Res/Images/SpecialMode/bullet.png"), enemy_1.bullet.width, enemy_1.bullet.height);
	loadimage(&enemy_2.bullet.img_bullet, _T("Res/Images/SpecialMode/bullet.png"), enemy_2.bullet.width, enemy_2.bullet.height);
	enemy_1.x = 4 * 25, enemy_1.y = 1 * 25;
	enemy_1.direction = DOWN;
	enemy_1.enemy = 4;

	enemy_2.x = 18 * 25, enemy_2.y = 5 * 25;
	enemy_2.direction = DOWN;
	enemy_2.enemy = 4;


	loadimage(&our.tank_up, _T("Res/Images/SpecialMode/our_tank_up.png"), our.width, our.height);
	loadimage(&our.tank_down, _T("Res/Images/SpecialMode/our_tank_down.png"), our.width, our.height);
	loadimage(&our.tank_right, _T("Res/Images/SpecialMode/our_tank_right.png"), our.width, our.height);
	loadimage(&our.tank_left, _T("Res/Images/SpecialMode/our_tank_left.png"), our.width, our.height);

	loadimage(&enemy_1.tank_up, _T("Res/Images/SpecialMode/enemy_tank_up.png"), enemy_1.width, enemy_1.height);
	loadimage(&enemy_1.tank_down, _T("Res/Images/SpecialMode/enemy_tank_down.png"), enemy_1.width, enemy_1.height);
	loadimage(&enemy_1.tank_right, _T("Res/Images/SpecialMode/enemy_tank_right.png"), enemy_1.width, enemy_1.height);
	loadimage(&enemy_1.tank_left, _T("Res/Images/SpecialMode/enemy_tank_left.png"), enemy_1.width, enemy_1.height);

	loadimage(&enemy_2.tank_up, _T("Res/Images/SpecialMode/enemy_tank_up.png"), enemy_2.width, enemy_2.height);
	loadimage(&enemy_2.tank_down, _T("Res/Images/SpecialMode/enemy_tank_down.png"), enemy_2.width, enemy_2.height);
	loadimage(&enemy_2.tank_right, _T("Res/Images/SpecialMode/enemy_tank_right.png"), enemy_2.width, enemy_2.height);
	loadimage(&enemy_2.tank_left, _T("Res/Images/SpecialMode/enemy_tank_left.png"), enemy_2.width, enemy_2.height);


	int x = 0, y = 0;
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 35; j++) {
			switch (map1[i][j])
			{
			case 1:
				putimage(x, y, &wall_1);
				break;
			case 2:
				putimage(x, y, &wall_2);
				break;
			case 3:
				putimage(x, y, &bird);
				break;
			case 4:
				putimage(x, y, &our.tank_up);
				our.x = x;
				our.y = y;
				our.direction = UP;
				our.enemy = 5;
				break;
			case 5:
				putimage(x, y, &enemy_1.tank_down);
				break;
			}
			if (j < 34) x += 25;
			else if (j == 34) {
				x = 0;
				y += 25;
			}
		}
	}

	updateMap3();
}

void updateMap3() {
	int systemTime = 0;
	int fresh = 0;
	while (true) {
		systemTime++;
		if (_kbhit()) {
			switch (_getch())
			{
			case 'A':
			case 'a':
				our.moveTank(LEFT);
				break;
			case 'S':
			case 's':
				our.moveTank(DOWN);
				break;
			case 'D':
			case 'd':
				our.moveTank(RIGHT);
				break;
			case 'W':
			case 'w':
				our.moveTank(UP);
				break;
			case 'J':
			case 'j':
				if (our.bullet.status == 1) our.fireBullet();
				break;
			case 'P':
			case 'p':
				system("pause");
				break;
			}
		}

		if (our.bullet.status != 1) our.fireBullet();

		enemy_1.fireBullet();
		enemy_2.fireBullet();


		int tempTime = systemTime / 60;

		if (tempTime == ((systemTime - 1) / 60 + 1)) {
			//activate enemy_tank_1
			if (map1_enemy_1_path[tempTime] != STOP) enemy_1.moveTank(map1_enemy_1_path[tempTime]);
			//activate enemy_tank_2
			if (map1_enemy_2_path[tempTime] != STOP) enemy_2.moveTank(map1_enemy_2_path[tempTime]);
		}


		if (!our.updateLive() || map1[21][12] != 3) break;

		if (!enemy_1.updateLive() && !enemy_2.updateLive()) {
			if (fresh < 3) {//rebirth enemy tank
				systemTime = 0;
				enemy_1.x = 4 * 25, enemy_1.y = 1 * 25;
				map1[1][4] = 5, map1[1][5] = -1;
				enemy_1.direction = DOWN;
				putimage(enemy_1.x, enemy_1.y, &enemy_1.tank_down);

				enemy_2.x = 18 * 25, enemy_2.y = 5 * 25;
				map1[5][18] = 5, map1[5][19] = -3;
				enemy_2.direction = DOWN;
				putimage(enemy_2.x, enemy_2.y, &enemy_2.tank_down);

				fresh++;
			}
			else break;
		}



	}

	if (!our.updateLive() || map1[21][12] != 3) loseEndMap3();
	else winEndMap3();

}

void winEndMap3() {
	PlaySound(TEXT("Res\\Sounds\\SpecialMode\\trueIsYou.wav"), NULL, SND_FILENAME | SND_ASYNC);
	cleardevice();
	RECT loseText = { 100,50,750,90 };
	RECT scoreText = { 100,50,750,90 };
	RECT destroyedTankText = { 100,50,750,90 };
	settextcolor(RED);
	outtextxy(140, 50, _T("YOU WIN! YOU HAVE BRUSHES!"));
	settextcolor(WHITE);

	TCHAR temp[10];

	//display score
	outtextxy(140, 100, _T("SCORE:"));
	_itot_s(score, temp, 10);
	outtextxy(600, 100, temp);

	//display destroyed tank number
	outtextxy(140, 150, _T("DESTRYOED TANKS:"));
	_itot_s(destroyedTank, temp, 10);
	outtextxy(600, 150, temp);


	//dispaly level of waste
	outtextxy(140, 200, _T("LEVEL OF WASTE:"));
	_itot_s(1000 - score / 7, temp, 10);
	outtextxy(600, 200, temp);

	// display logo
	settextstyle(20, 0, _T("castellar"));
	settextcolor(RED);
	outtextxy(200, 450, _T("TANK BATTLE POWERED BY XJU SUNSEALUCKY"));
	

	while (true);
}

void loseEndMap3() {
	PlaySound(TEXT("Res\\Sounds\\SpecialMode\\trueIsYou.wav"), NULL, SND_FILENAME | SND_ASYNC);
	cleardevice();
	RECT loseText = { 100,50,750,90 };
	RECT scoreText = { 100,50,750,90 };
	RECT destroyedTankText = { 100,50,750,90 };
	settextcolor(RED);
	outtextxy(140, 50, _T("YOU LOSE! GO BACK HOME BOY!"));
	settextcolor(WHITE);

	TCHAR temp[10];

	//display score
	outtextxy(140, 100, _T("SCORE:"));
	_itot_s(score, temp, 10);
	outtextxy(600, 100, temp);

	//display destroyed tank number
	outtextxy(140, 150, _T("DESTRYOED TANKS:"));
	_itot_s(destroyedTank, temp, 10);
	outtextxy(600, 150, temp);

	//dispaly level of waste
	outtextxy(140, 200, _T("LEVEL OF WASTE:"));
	_itot_s(1000 - score / 7, temp, 10);
	outtextxy(600, 200, temp);

	//display logo
	settextstyle(20, 0, _T("castellar"));
	settextcolor(RED);
	outtextxy(200, 450, _T("TANK BATTLE POWERED BY XJU SUNSEALUCKY"));

	
	while (true);
}