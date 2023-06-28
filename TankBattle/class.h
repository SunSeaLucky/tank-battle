#pragma once
#pragma comment(lib, "Winmm.lib")

class Rectangle {
public:
	int width = 0;
	int height = 40;
};

class Bullet {
public:
	/*************
	* status:
	* 0--->flying
	* 1--->no command
	* 2--->waiting to fly
	*************/
	IMAGE img_bullet;
	int status = 1;
	int x = 0, y = 0;
	int dx = 0, dy = 0;
	int width = 5, height = 5;
	DIRECTION direction = UP;
};

class Tank {
public:
	IMAGE tank_up, tank_down, tank_right, tank_left;
	DIRECTION direction;
	class Bullet bullet;
	
	int live = 3,
		width = 50,
		height = 50,
		x = 0,
		y = 0,
		enemy=0;

	void moveTank(DIRECTION direction) {

		if (!updateLive()) {
			clearTank();
			return;
		}

		IMAGE temp;
		map1[this->y / 25][this->x / 25] = 0;
		map1[this->y / 25][this->x / 25 + 1] = 0;
		clearrectangle(this->x, this->y, this->x + 50, this->y + 50);

		switch (direction){
		case UP:
			temp = this->tank_up;
			if (this->direction == UP) {
				if (map1[this->y / 25 - 1][this->x / 25] == 0 &&
					map1[this->y / 25 - 1][this->x / 25 + 1] == 0 &&
					map1[this->y / 25 - 2][this->x / 25] != 5 &&
					map1[this->y / 25 - 2][this->x / 25 + 1] != 5 &&
					map1[this->y / 25 - 2][this->x / 25 - 1] != 5) this->y -= 25;
			}
			else this->direction = UP;
			break;
		case DOWN:
			temp = this->tank_down;
			if (this->direction == DOWN) {
				if (map1[this->y / 25 + 2][this->x / 25] == 0 &&
					map1[this->y / 25 + 2][this->x / 25 + 1] == 0 &&
					map1[this->y / 25 + 2][this->x / 25 - 1] != 5)this->y += 25;
			}
			else this->direction = DOWN;
			break;
		case RIGHT:
			temp = this->tank_right;
			if (this->direction == RIGHT) {
				if (map1[this->y / 25][this->x / 25 + 2] == 0 &&
					map1[this->y / 25 + 1][this->x / 25 + 2] == 0 &&
					map1[this->y / 25 - 1][this->x / 25 + 2] != 5) this->x += 25;
			}
			else this->direction = RIGHT;
			break;
		case LEFT:
			temp = this->tank_left;
			if (this->direction == LEFT) {
				if (map1[this->y / 25][this->x / 25 - 1] == 0 &&
					map1[this->y / 25 + 1][this->x / 25 - 1] == 0 &&
					map1[this->y / 25 - 1][this->x / 25 - 2] != 5 &&
					map1[this->y / 25][this->x / 25 - 2] != 5 &&
					map1[this->y / 25 + 1][this->x / 25 - 2] != 5) this->x -= 25;
			}
			else this->direction = LEFT;
			break;
		}

		map1[this->y / 25][this->x / 25] = (this->enemy == 5) ? 4 : 5;
		map1[this->y / 25][this->x / 25 + 1] = -this->live;
		putimage(this->x, this->y, &temp);
	}

	bool checkBulletBomb(int x, int y) {
		//init bullet's position
		int m = y / 25, n = x / 25;

		//hit wall
		if (map1[m][n] == 1) {
			if (this->enemy == 5) score += 15;
			map1[m][n] = 0;
			clearrectangle(n * 25, m * 25, n * 25 + 25, m * 25 + 25);
			return true;

		//hit tank
		}else if (map1[m - 1][n - 1] == this->enemy) {//bullet from bottom
			m--,n--;
			
		}else if (map1[m][n]== this->enemy) {//bullet from up
			
		}else if (map1[m][n - 1] == this->enemy) {//bullet from right
			n--;
			
		}else if (map1[m - 1][n] == this->enemy) {//bullet from left
			m--;
		
		//hit the strongest wall
		}else if (map1[m][n] == 2) {
			if (this->enemy == 5) score += 1;
			return true;

		//hit bird
		}else if (map1[m][n] == 3) {//bullet from up

		}
		else if (map1[m][n - 1] == 3) {//bullet from right
			n--;

		}
		else if (map1[m - 1][n] == 3) {//bullet from left
			m--;

		}else return false;


		//deal bird is hitted
		if (map1[m][n] == 3) {

			map1[m][n] = 0;

		//deal tank is hitted
		}else {

			if (map1[m][n + 1] >= 0) {
				//if destroyed enemy tank, then add destroyed tank number and update score
				if (this->enemy == 5) {
					destroyedTank++;
					score += 100;
				}
				clearrectangle(n * 25, m * 25, n * 25 + 50, m * 25 + 50);
				map1[m][n] = 0;
				map1[m][n + 1] = 0;
			}
			else map1[m][n + 1]++;

		}

		return true;
	}

	void fireBullet() {
		if (!updateLive()) {
			clearTank();
			return;
		}
		switch (this->bullet.status)
		{
		case 0://flying
			if (!checkBulletBomb(this->bullet.x, this->bullet.y)) {
				this->bullet.status = 0;
				putimage(this->bullet.x, this->bullet.y, &this->bullet.img_bullet);

				//map update interval
				Sleep(15);

				clearrectangle(this->bullet.x, this->bullet.y, this->bullet.x + this->bullet.width, this->bullet.y + this->bullet.height);
				this->bullet.x += this->bullet.dx;
				this->bullet.y += this->bullet.dy;
			}
			else this->bullet.status = 1;
			break;
		case 1://no command
			this->bullet.direction = this->direction;
			this->bullet.status = 2;
			
			break;
		case 2://waiting to fly

			if (this->enemy == 5) {
				switch (mapType)
				{
				case 1:
					mciSendString(TEXT("play Res\\Sounds\\TypicalMode\\ji.wav"), NULL, 0, NULL);
					break;
				case 2:
					mciSendString(TEXT("play Res\\Sounds\\AdventureMode\\watermelon.wav"), NULL, 0, NULL);
					break;
				case 3:
					mciSendString(TEXT("play Res\\Sounds\\SpecialMode\\ji.wav"), NULL, 0, NULL);
					break;
				}
			}
			
			
			switch (this->direction)
			{
			case UP:
				this->bullet.x = this->x + 25;
				this->bullet.y = this->y - 25;
				this->bullet.dx = 0, this->bullet.dy = -5;
				break;
			case DOWN:
				this->bullet.x = this->x + 25;
				this->bullet.y = this->y + 55;
				this->bullet.dx = 0, this->bullet.dy = 5;
				break;
			case RIGHT:
				this->bullet.x = this->x + 55;
				this->bullet.y = this->y + 25;
				this->bullet.dx = 5, this->bullet.dy = 0;
				break;
			case LEFT:
				this->bullet.x = this->x - 25;
				this->bullet.y = this->y + 22;
				this->bullet.dx = -5, this->bullet.dy = 0;
				break;
			}
			this->bullet.status = 0;
			break;
		}
	}

	bool updateLive() {
		this->live = -map1[this->y / 25][this->x / 25 + 1];
		return this->live > 0 ? true : false;
	}

	void clearTank() {
		this->x = -50, this->y = -50;
	}
};