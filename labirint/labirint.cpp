#include "simplesfml.hpp"
#include<cstring>
#include<cmath>
char map[250][250];
char maps[2][250][260] = { {
  "###################",
  "#    #   #   #    #",
  "#  #   #   # 1 ##  ",
  "#  # 1 #   #   ##  ",
  "#  #   #   #   ##  ",
  "#  #   # 1 #   ##  ",
  "#  #   # b #   ## 8",
  "#@ #        2  o ##",
  "###################",
  ""
},
	{"#########################",
	 "#@   #                  #",
	 "#    #    #  b 1     2  #",
	 "#    # 1  #     1    2  #",
	 "#        1#          2  #",
	 "#    #  o #          2 8#",
	 "#########################",
	 ""
    }
};
int n,  m;
int len = 50;
int bots[100][5];
int cob = 0;
bool c;
bool sc = false;
int cb;
int ctbem = 34;
int bpatb_y;
int bpatb_x;
int lvl = 0,clvl=2;
bool w;
int ctbe = -1;
int dirb = 0;
bool bp = true;
bool b = true;
int hero_x = -1, hero_y = -1;
int fhero_x, fhero_y;
int live = 3;
void initMap() {
	cob = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (map[i][j] == '1') {
				bots[cob][0] = i;
				bots[cob][1] = j;
				bots[cob][2] = 0;
				bots[cob][3] = 1;
				map[i][j] = ' ';
				++cob;
			}
			else
				if (map[i][j] == '2') {
					bots[cob][1] = j;
					bots[cob][0] = i;
					bots[cob][2] = 0;
					bots[cob][3] = 2;
					//1=up&down//2=right &left
					map[i][j] = ' ';
					++cob;
				}
				else
					if (map[i][j] == '@') {
						hero_y = i;
						hero_x = j;
						fhero_x = j;
						fhero_y = i;
						map[i][j] = ' ';
					}
		}
	}
}
void drawMap(RenderWindow& window)  {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == '#') {
				setFillColor(250, 150, 142);
				rectangle(window, len, len, j* len, i* len);
			}
			if (map[i][j] == '8'){
				setFillColor(252, 252, 252);
				rectangle(window,len*0.8,len*0.8,j*len+0.1*len, i * len+0.1*len);
			}
			if (map[i][j] == 'o') {
				setFillColor(248, 5, 5);
				circle(window, len * 0.8, j * len + 0.1 * len, i * len + 0.1 * len);
			}
			if (map[i][j] == 'b') {
				setFillColor(104, 106, 72);
				circle(window, len * 0.7, j * len + 0.15 * len, i * len + 0.15 * len);
			}
			if (map[i][j] == 'B') {
				setFillColor(104, 106, 72);
				circle(window, len * 0.7, j * len + 0.15 * len, i * len + 0.15 * len);
				setFillColor(221,0,5);
				circle(window, len * 0.3, j * len + 0.350 * len, i * len + 0.350 * len);
			}
		}
	}
}
void drawHero(RenderWindow& window) {
	setFillColor(17, 217, 22);
	figure(window, len * 0.9, 10, hero_x * len+len*0.05, hero_y * len+len*0.05);
}
void drawBot(RenderWindow& window) {
	for (int i = 0; i < cob; ++i) {
		if (bots[i][3] != 0) {
			setFillColor(29, 63, 201);
			circle(window, len * 0.9, bots[i][1] * len + 0.05 * len, bots[i][0] * len + 0.05 * len);
		}
	}
}
void moveHero(int dih) {
	if (dih == -1 && map[hero_y-1][hero_x] != '#') {
		hero_y--;
	}
	if (dih == 1 && map[hero_y+1][hero_x] != '#') {
		hero_y++;
	}
	if (dih == -2 && map[hero_y][hero_x-1] != '#') {
		hero_x--;
	}
	if (dih == 2 && map[hero_y][hero_x+1] != '#') {
		hero_x++;
	}
}
void moveBot() {
	for (int i = 0; i < cob; ++i) {
		int& bot_y = bots[i][0];
		int& bot_x = bots[i][1];
		int& di = bots[i][2];
		int vt = bots[i][3];
		if (vt != 0) {
			if (vt == 1) {
				if (map[bot_y - 1][bot_x] == '#') {
					di = 0;
					bot_y++;
				}
				else
					if (map[bot_y + 1][bot_x] == '#') {
						di = 1;
						bot_y--;
					}
					else {
						if (di == 1)bot_y--;
						else bot_y++;
					}
			}
			if (vt == 2) {
				if (map[bot_y][bot_x - 1] == '#') {
					di = 0;
					bot_x++;
				}
				else
					if (map[bot_y][bot_x + 1] == '#') {
						di = 1;
						bot_x--;
					}
					else {
						if (di == 1)bot_x--;
						else bot_x++;
					}
			}
		}
	}
}
void botCheck() {
	for (int i = 0; i < cob; i++){
		if (bots[i][3] != 0) {
			if (hero_x == bots[i][1] && hero_y == bots[i][0]) {
				hero_x = fhero_x;
				hero_y = fhero_y;
				--live;
			}
		}
	}
}
void endCheck() {
	if (live == 0) {
		c = false;
    }
}
void liveCheck() {
	if (map[hero_y][hero_x] == 'o') {
		++live;
		map[hero_y][hero_x] = ' ';
	}
}
void bombPick() {
	if (map[hero_y][hero_x] == 'b') {
		++cb;
		map[hero_y][hero_x] = ' ';
	}
}
void bombThrow() {
	if (dirb == -1 && map[hero_y - 1][hero_x] != '#') {
		map[hero_y - 1][hero_x]='B';
		bpatb_x = hero_x;
		bpatb_y = hero_y-1;
		bp = true;
		--cb;
		ctbe = ctbem;
	}
	else
		if (dirb == 1 && map[hero_y + 1][hero_x] != '#') {
			map[hero_y +1][hero_x] = 'B';
			bpatb_x = hero_x;
			bpatb_y = hero_y+1;
			bp = true;
			--cb;
			ctbe = ctbem;
		}
		else
			if (dirb == 2 && map[hero_y][hero_x+1] != '#') {
				map[hero_y][hero_x+1] = 'B';
				bpatb_x = hero_x + 1;
				bpatb_y = hero_y;
				bp = true;
				--cb;
				ctbe = ctbem;
			}
			else
				if (dirb == -2 && map[hero_y][hero_x - 1] != '#') {
					map[hero_y][hero_x - 1] = 'B';
					bpatb_x = hero_x - 1;
					bpatb_y = hero_y;
					bp = true;
					--cb;
					ctbe = ctbem;
				}
}
bool checkBot(int y, int x) {
	if (fabs(bpatb_x - x) < 2 && fabs(bpatb_y - y) < 2)return false;
	return true;
}
void bombExplode() {
	if (bpatb_y != 0 && bpatb_x != 0 && bpatb_y != n-1 && bpatb_x != m-1)map[bpatb_y][bpatb_x] = ' ';
	if (bpatb_y +1 != 0 && bpatb_x != 0 && bpatb_y+1 != n - 1 && bpatb_x != m - 1)map[bpatb_y +1][bpatb_x] = ' ';
	if (bpatb_y -1 != 0 && bpatb_x != 0 && bpatb_y-1 != n - 1 && bpatb_x != m - 1)map[bpatb_y -1][bpatb_x] = ' ';
	if (bpatb_y != 0 && bpatb_x +1 != 0 && bpatb_y != n - 1 && bpatb_x+1 != m - 1)map[bpatb_y][bpatb_x +1] = ' ';
	if (bpatb_y != 0 && bpatb_x - 1 != 0 && bpatb_y != n - 1 && bpatb_x-1 != m - 1)map[bpatb_y][bpatb_x - 1] = ' ';
	if (bpatb_y -1 != 0 && bpatb_x -1 != 0 && bpatb_y-1 != n - 1 && bpatb_x-1 != m - 1)map[bpatb_y - 1][bpatb_x - 1] = ' ';
	if (bpatb_y +1 != 0 && bpatb_x -1 != 0 && bpatb_y +1!= n - 1 && bpatb_x-1 != m - 1)map[bpatb_y + 1][bpatb_x - 1] = ' ';
	if (bpatb_y -1 != 0 && bpatb_x +1 != 0 && bpatb_y -1!= n - 1 && bpatb_x+1 != m - 1)map[bpatb_y - 1][bpatb_x + 1] = ' ';
	if (bpatb_y +1 != 0 && bpatb_x +1!= 0 && bpatb_y+1 != n - 1 && bpatb_x+1 != m - 1)map[bpatb_y + 1][bpatb_x + 1] = ' ';
	for (int i = 0; i < cob; ++i) {
		if (checkBot(bots[i][0], bots[i][1]) == false)bots[i][3] = 0;
	}
	if (!checkBot(hero_y, hero_x)) {
	  --live;
	  hero_x = fhero_x;
	  hero_y = fhero_y;
	}
}
void winCheck() {
	if (map[hero_y][hero_x] == '8') {
		w = false;
	}
}
void loadMap(int lvl) {
	int i;
	for (i = 0; maps[lvl][i][0] != '\0'; i++)
		strcpy_s(map[i], maps[lvl][i]);
	map[i][0]='\0';
}
int getDirB(RenderWindow& w) {
	while (true) {
		Event event;
		while (w.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up) {
					return -1;
				}
				else
					if (event.key.code == sf::Keyboard::Down) {
						return 1;
					}
					else
						if (event.key.code == sf::Keyboard::Right) {
							return 2;
						}
						else
							if (event.key.code == sf::Keyboard::Left) {
								return -2;
							}
			}
		}
	}
}
void sizeCalcN(char map[250][250], int &n) {
	for (n = 0; map[n][0] != '\0'; ++n);
}
void sizeCalcM(char map[250][250],int &m) {
	m = strlen(map[0]);
}
int main(){
	RenderWindow window(VideoMode(1250,650), "Start!");
	window.setKeyRepeatEnabled(false);

	while (lvl < clvl && window.isOpen()) {
		n = 0;
		m = 0;
		loadMap(lvl);
		sizeCalcN(map, n);
		sizeCalcM(map, m);
		initMap();
		bool f = true;
		w = true;
		c = true;
		while (w && c){
			int dih = 0;
			Event event; 
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
				/*if (event.type == sf::Event::Resized) {
				window.setSize(n*len,m*len);
				}*/
				if (b == true) {
					if (event.type == Event::LostFocus)
						f = false;

					if (event.type == Event::GainedFocus)
						f = true;
				}
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::Escape) {
						if (b == true) {
							b = false;
						}
						else b = true;
					}
					if (event.key.code == sf::Keyboard::B && cb>0 && ctbe==-1) {
						bp = false;
						dirb=getDirB(window);
					}
					if (event.key.code == sf::Keyboard::Up) {
						dih = -1;
					}
					else
						if (event.key.code == sf::Keyboard::Down) {
							dih = 1;
						}
						else
							if (event.key.code == sf::Keyboard::Right) {
								dih = 2;
							}
							else
								if (event.key.code == sf::Keyboard::Left) {
									dih = -2;
								}
				}
			}
			if (f && b) {
				if (ctbe==0) {
					bombExplode();
					ctbe = -1;
				}
				if (!bp) {
					bombThrow();
				}
				if (ctbe<ctbem+1 && ctbe>0) {
					--ctbe;
				}
				setBackgroundColor(0, 0, 0);
				clear(window);
				drawMap(window);
				drawHero(window);
				moveBot();
				moveHero(dih);
				botCheck();
				winCheck();
				endCheck();
				bombPick();
				liveCheck();
				drawBot(window);
				window.display();
				pause(150);
			}
		}
		if (!w) {
			++lvl;
		}
		if (!c && lvl > 0) {
			--lvl;
			live = 3;
		}
	}
	return 0;
}
