// First Ever Game
#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

int screen_x = 1152;
int screen_y = 896;

// reset game
void reset_game(float &fire_x, float &fire_y, float ghost_y[], float ghost_x[], float skeleton_x[], float skeleton_y[], float ghost_speed[], bool is_g_alive[], Sprite ghost_sprite[], float skeleton_gravity[], float skeleton_speed[], bool is_skeleton_facing_right[], bool is_s_alive[], Sprite skeleton_sprite[], int &scores, int &player_lives, bool &speed_pu_present, bool &life_pu_present, int &p_frame_index, float &p_animation_timer, float &player_x, float &player_y, bool &onGround, float &offset_x, float &offset_y, float &velocityY, bool &reach_last_ground, bool &ignoring_tiles, bool &is_player_facing_right, bool &onGroundNow, bool &down_key, bool &hit, bool &pause, int &suction_count, int total_ghosts, int total_skeletons, int speed, int &level_no, bool &new_level, float ghost_right_x[], float ghost_left_x[], int sucked_enemies[])
{
	fire_x = 0;
	fire_y = 0;
	if (level_no == 1)
	{
		ghost_x[0] = 128, ghost_x[1] = 128, ghost_x[2] = 800, ghost_x[3] = 800, ghost_x[4] = 256, ghost_x[5] = 256, ghost_x[6] = 704, ghost_x[7] = 704;
		ghost_y[0] = 512, ghost_y[1] = 256, ghost_y[2] = 256, ghost_y[3] = 512, ghost_y[4] = 128, ghost_y[5] = 640, ghost_y[6] = 128, ghost_y[7] = 640;
		skeleton_x[0] = 200, skeleton_x[1] = 800, skeleton_x[2] = 150, skeleton_x[3] = 900;
		skeleton_y[0] = 120, skeleton_y[1] = 120, skeleton_y[2] = 370, skeleton_y[3] = 370;
		for (int i = 0; i < total_ghosts; i++)
		{
			ghost_speed[i] = 2;
			is_g_alive[i] = 1;
			ghost_sprite[i].setScale(-2, 2);
		}
		for (int i = 0; i < total_skeletons; i++)
		{
			skeleton_gravity[i] = 0;
			skeleton_speed[i] = 1.5;
			is_skeleton_facing_right[i] = 0;
			is_s_alive[i] = 1;
			skeleton_sprite[i].setScale(2, 2);
		}
	}
	else
	{

		ghost_x[0] = 128;
		ghost_x[1] = 128;
		ghost_x[2] = 800;
		ghost_x[3] = 800;
		ghost_x[4] = 256;
		ghost_x[5] = 256;
		ghost_x[6] = 704;
		ghost_x[7] = 704;

		ghost_y[1] = 512;
		ghost_y[2] = 256;
		ghost_y[0] = 256;
		ghost_y[3] = 512;
		ghost_y[4] = 128;
		ghost_y[5] = 640;
		ghost_y[6] = 128;
		ghost_y[7] = 640;

		ghost_left_x[0] = 64;
		ghost_left_x[1] = 64;
		ghost_left_x[2] = 840;
		ghost_left_x[3] = 840;
		ghost_left_x[4] = 256;
		ghost_left_x[5] = 192;
		ghost_left_x[6] = 704;
		ghost_left_x[7] = 704;

		ghost_right_x[0] = 320;
		ghost_right_x[1] = 320;
		ghost_right_x[2] = 1090;
		ghost_right_x[3] = 1090;
		ghost_right_x[4] = 512;
		ghost_right_x[5] = 448;
		ghost_right_x[6] = 896;
		ghost_right_x[7] = 960;

		for (int i = 0; i < total_ghosts; i++)
		{
			ghost_speed[i] = 2;
		}
		// ghost_speed[0] = 2;
		// ghost_speed[1] = 2;
		// ghost_speed[2] = 2;
		// ghost_speed[3] = 2;
		// ghost_speed[4] = 2;
		// ghost_speed[5] = 2;
		// ghost_speed[6] = 2;
		// ghost_speed[7] = 2;

		for (int i = 0; i < total_ghosts; i++)
		{
			is_g_alive[i] = 1;
		}
		// is_g_alive[0] = 1;
		// is_g_alive[1] = 1;
		// is_g_alive[2] = 1;
		// is_g_alive[3] = 1;
		// is_g_alive[4] = 1;
		// is_g_alive[5] = 1;
		// is_g_alive[6] = 1;
		// is_g_alive[7] = 1;
	}
	scores = 0;
	player_lives = 3;
	speed_pu_present = true;
	life_pu_present = true;
	p_frame_index = 0;
	p_animation_timer = 0.0f;
	player_x = 382;
	player_y = 763;
	speed = 5;
	onGround = false;
	offset_x = 0;
	offset_y = 0;
	velocityY = 0;
	reach_last_ground = false;
	ignoring_tiles = false;
	is_player_facing_right = false;
	onGroundNow = false;
	down_key = false;
	hit = false;
	pause = false;
	suction_count = 0;
	level_no = 1;
	new_level = true;
	for (int i = 0; i < 3; i++)
		sucked_enemies[i] = 0;
}

// Loading level
void setting_blocks_lvl1(char **lvl, int height, int width)
{

	for (int i = 0; i < width; i++)
		lvl[0][i] = '#'; // 0th row
	for (int i = 3; i < 15; i++)
		lvl[3][i] = '#'; // 3rd row
	for (int i = 8; i < 10; i++)
		lvl[4][i] = '#'; // 4rth row
	for (int i = 0; i < 5; i++)
		lvl[5][i] = '#'; // 5th row
	for (int i = 7; i < 11; i++)
		lvl[5][i] = '#'; // 5th row
	for (int i = 13; i < width; i++)
		lvl[5][i] = '#'; // 5th row
	for (int i = 6; i < 9; i++)
		lvl[i][7] = '#'; // 7th col
	for (int i = 3; i < 7; i++)
		lvl[7][i] = '#'; // 7th row
	for (int i = 11; i < 15; i++)
		lvl[7][i] = '#'; // 7th row
	for (int i = 0; i < 5; i++)
		lvl[9][i] = '#'; // 9th row
	for (int i = 7; i < 11; i++)
		lvl[9][i] = '#'; // 9th row
	for (int i = 13; i < width; i++)
		lvl[9][i] = '#'; // 9th row
	for (int i = 8; i < 10; i++)
		lvl[10][i] = '#'; // 10th row
	for (int i = 3; i < 15; i++)
		lvl[11][i] = '#'; // 11th row
	for (int i = 6; i < 9; i++)
		lvl[i][10] = '#'; // 10th col
	for (int i = 0; i < width; i++)
		lvl[height - 1][i] = '#'; // 13th row
	for (int i = 0; i < 14; i++)
		lvl[i][0] = '#'; // first column
	for (int i = 0; i < 14; i++)
		lvl[i][17] = '#'; // last column
}

void setting_blocks_lvl2(char **lvl, int height, int width)
{

	//==================slant generations=======================
	// for (int i=rand()%12+1,j=rand()%4+2,p=i+4; i<p; i++,j++)
	for (int i = 3, j = rand() % 8 + 2, p = i + 8; i < p; i++, j++)

	{
		lvl[i][j] = '+';
		lvl[i][j + 1] = '-';
	}
	// =================================border generation???//
	for (int i = 0; i < width; i++)
	{
		lvl[0][i] = '#';
		lvl[13][i] = '#';
	}
	for (int j = 0; j < height; j++)
	{
		lvl[j][0] = '#';
		lvl[j][17] = '#';
	}
	for (int i = (rand() % 6) + 3; i < (rand() % 4) + 10; i++)
	{
		lvl[11][i] = '#';
	}
	for (int i = (rand() % 6) + 3; i < (rand() % 4) + 10; i++)
	{
		lvl[6][i] = '#';
	}
	for (int i = (rand() % 4) + 1; i < (rand() % 5) + 10; i++)
	{
		lvl[2][i] = '#';
	}
	int i = (rand() % 3) + 8;
	for (int j = 1, k = 12; j < 5; k++, j++)
	{
		lvl[i][j] = '#';
		lvl[i][k] = '#';
	}
	int p = (rand() % 3) + 3;
	for (int j = 1, k = 12; j < 5; k++, j++)
	{
		lvl[p][j] = '#';
		lvl[p][k] = '#';
	}
}

void load_level(int level_no, Texture &bgTex, Sprite &bgSprite, char **lvl, const int height, const int width, const int &total_ghosts, float ghost_x[], float ghost_y[], float ghost_speed[], float ghost_left_x[], float ghost_right_x[], bool is_g_alive[])
{
	// -----storing '.' in the lvl array-----
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			lvl[i][j] = '.';
	if (level_no == 1)
	{
		bgTex.loadFromFile("Data/bg.png");
		bgSprite.setTexture(bgTex);
		bgSprite.setPosition(0, 0);

		setting_blocks_lvl1(lvl, height, width);

		ghost_x[0] = 128;
		ghost_x[1] = 128;
		ghost_x[2] = 800;
		ghost_x[3] = 800;
		ghost_x[4] = 256;
		ghost_x[5] = 256;
		ghost_x[6] = 704;
		ghost_x[7] = 704;

		ghost_y[1] = 512;
		ghost_y[2] = 256;
		ghost_y[0] = 256;
		ghost_y[3] = 512;
		ghost_y[4] = 128;
		ghost_y[5] = 640;
		ghost_y[6] = 128;
		ghost_y[7] = 640;

		ghost_left_x[0] = 64;
		ghost_left_x[1] = 64;
		ghost_left_x[2] = 840;
		ghost_left_x[3] = 840;
		ghost_left_x[4] = 256;
		ghost_left_x[5] = 192;
		ghost_left_x[6] = 704;
		ghost_left_x[7] = 704;

		ghost_right_x[0] = 320;
		ghost_right_x[1] = 320;
		ghost_right_x[2] = 1090;
		ghost_right_x[3] = 1090;
		ghost_right_x[4] = 512;
		ghost_right_x[5] = 448;
		ghost_right_x[6] = 896;
		ghost_right_x[7] = 960;

		for (int i = 0; i < total_ghosts; i++)
		{
			ghost_speed[i] = 2;
		}
		// ghost_speed[0] = 2;
		// ghost_speed[1] = 2;
		// ghost_speed[2] = 2;
		// ghost_speed[3] = 2;
		// ghost_speed[4] = 2;
		// ghost_speed[5] = 2;
		// ghost_speed[6] = 2;
		// ghost_speed[7] = 2;

		for (int i = 0; i < total_ghosts; i++)
		{
			is_g_alive[i] = 1;
		}
		// is_g_alive[0] = 1;
		// is_g_alive[1] = 1;
		// is_g_alive[2] = 1;
		// is_g_alive[3] = 1;
		// is_g_alive[4] = 1;
		// is_g_alive[5] = 1;
		// is_g_alive[6] = 1;
		// is_g_alive[7] = 1;
	}
	else
	{
		bgTex.loadFromFile("Data/lvl2.png");
		bgSprite.setTexture(bgTex);
		bgSprite.setPosition(0, 0);

		setting_blocks_lvl2(lvl, height, width);

		ghost_x[0] = 128;
		ghost_x[1] = 128;
		ghost_x[2] = 800;
		ghost_x[3] = 800;
		ghost_x[4] = 256;
		ghost_x[5] = 256;
		ghost_x[6] = 704;
		ghost_x[7] = 704;

		ghost_y[1] = 512;
		ghost_y[2] = 256;
		ghost_y[0] = 256;
		ghost_y[3] = 512;
		ghost_y[4] = 128;
		ghost_y[5] = 640;
		ghost_y[6] = 128;
		ghost_y[7] = 640;

		ghost_left_x[0] = 64;
		ghost_left_x[1] = 64;
		ghost_left_x[2] = 840;
		ghost_left_x[3] = 840;
		ghost_left_x[4] = 256;
		ghost_left_x[5] = 192;
		ghost_left_x[6] = 704;
		ghost_left_x[7] = 704;

		ghost_right_x[0] = 320;
		ghost_right_x[1] = 320;
		ghost_right_x[2] = 1090;
		ghost_right_x[3] = 1090;
		ghost_right_x[4] = 512;
		ghost_right_x[5] = 448;
		ghost_right_x[6] = 896;
		ghost_right_x[7] = 960;

		for (int i = 0; i < total_ghosts; i++)
		{
			ghost_speed[i] = 2;
		}
		// ghost_speed[0] = 2;
		// ghost_speed[1] = 2;
		// ghost_speed[2] = 2;
		// ghost_speed[3] = 2;
		// ghost_speed[4] = 2;
		// ghost_speed[5] = 2;
		// ghost_speed[6] = 2;
		// ghost_speed[7] = 2;

		for (int i = 0; i < total_ghosts; i++)
		{
			is_g_alive[i] = 1;
		}
		// is_g_alive[0] = 1;
		// is_g_alive[1] = 1;
		// is_g_alive[2] = 1;
		// is_g_alive[3] = 1;
		// is_g_alive[4] = 1;
		// is_g_alive[5] = 1;
		// is_g_alive[6] = 1;
		// is_g_alive[7] = 1;
	}
}

// -----ALL DISPLAYING FUNCTIONS-----
void display_selection_screen(RenderWindow &window, Sprite &g_Select_Sprite, Sprite &y_Select_Sprite, bool &player_Green, Text &selectText, Text &EnterT)
{
	g_Select_Sprite.setPosition(300, 400);
	y_Select_Sprite.setPosition(700, 400);
	g_Select_Sprite.setScale(4.5, 4.5);
	y_Select_Sprite.setScale(4.5, 4.5);

	selectText.setString("SELECT YOUR PLAYER");
	selectText.setCharacterSize(40);
	selectText.setFillColor(Color::White);
	selectText.setPosition(240, 200);

	EnterT.setString("PRESS ENTER TO SELECT");
	EnterT.setCharacterSize(20);
	EnterT.setFillColor(Color::White);
	EnterT.setPosition(360, 860);

	if (player_Green)
		g_Select_Sprite.setScale(5.5, 5.5);
	else
		y_Select_Sprite.setScale(5.5, 5.5);

	window.clear();
	window.draw(g_Select_Sprite);
	window.draw(y_Select_Sprite);
	window.draw(selectText);
	window.draw(EnterT);
	window.display();
}

void main_menu(RenderWindow &window, Text &menuT, Text &playgameT, Text &select_the_playerT, Text &controlT, int menuarrInd, Text &EnterT, Text &NewgameT)
{
	menuT.setString("MAIN MENU");
	menuT.setCharacterSize(100);
	menuT.setFillColor(Color::White);
	menuT.setPosition(150, 100);

	NewgameT.setString("NEW GAME");
	NewgameT.setCharacterSize(65);
	NewgameT.setPosition(100, 260);

	playgameT.setString("PLAY GAME");
	playgameT.setCharacterSize(65);
	playgameT.setPosition(100, 410);

	select_the_playerT.setString("PLAYER\n\tSELECTION");
	select_the_playerT.setCharacterSize(65);
	select_the_playerT.setPosition(100, 560);

	controlT.setString("CONTROLS");
	controlT.setCharacterSize(65);
	controlT.setPosition(100, 770);

	EnterT.setString("PRESS ESC TO EXIT                      PRESS ENTER TO GO");
	EnterT.setCharacterSize(20);
	EnterT.setPosition(0, 860);

	Text menuarr[4] = {NewgameT, playgameT, select_the_playerT, controlT};
	for (int i = 0; i < 4; i++)
	{
		if (i == menuarrInd)
			menuarr[i].setFillColor(Color::Cyan);
		else
			menuarr[i].setFillColor(Color::White);
	}

	window.clear();
	window.draw(menuT);
	window.draw(EnterT);
	for (int i = 0; i < 4; i++)
		window.draw(menuarr[i]);
	window.display();
}

// displaying the backgroung image and the blocks
void display_level(RenderWindow &window, char **lvl, Sprite &bgSprite, Sprite &blockSprite, const int height, const int width, const int cell_size, Sprite &slant_upsprite, Sprite &slant_downsprite)
{
	window.draw(bgSprite);

	for (int i = 0; i < height; i += 1)
	{
		for (int j = 0; j < width; j += 1)
		{

			if (lvl[i][j] == '#')
			{
				blockSprite.setPosition(j * cell_size, i * cell_size);
				window.draw(blockSprite);
			}
			if (lvl[i][j] == '+')
			{
				slant_upsprite.setPosition(j * cell_size, i * cell_size);
				window.draw(slant_upsprite);
			}
			if (lvl[i][j] == '-')
			{
				slant_downsprite.setPosition(j * cell_size, i * cell_size);
				window.draw(slant_downsprite);
			}
		}
	}
}

void display_tumblepop_image(RenderWindow &window, Sprite &Title_Sprite)
{
	window.draw(Title_Sprite);
}

void display_health_image(RenderWindow &window, Sprite &p1_Sprite, Sprite &p2_Sprite, bool player_Green)
{
	if (player_Green)
	{
		p1_Sprite.setPosition(126, 70);
		p1_Sprite.setScale(3, 3);
		window.draw(p1_Sprite);
	}
	else
	{
		p2_Sprite.setPosition(126, 70);
		p2_Sprite.setScale(3, 3);
		window.draw(p2_Sprite);
	}
}

void display_player(RenderWindow &window, bool player_Green, bool is_player_facing_right, Sprite GreenplayerFrame[], Sprite YellowplayerFrame[], int p_frame_index, float player_x, float player_y, int PlayerWidth, bool onGroundNow, Sprite &p1_j_sprite, Sprite &p2_j_sprite, bool &down_key, Sprite &p1_d_sprite, Sprite &p2_d_sprite)
{
	if (!down_key)
	{
		if (onGroundNow)
		{
			if (player_Green)
			{
				GreenplayerFrame[p_frame_index].setScale(is_player_facing_right ? -2 : 2, 2);
				GreenplayerFrame[p_frame_index].setPosition(player_x + (is_player_facing_right ? PlayerWidth : 0), player_y);
				window.draw(GreenplayerFrame[p_frame_index]);
			}
			else
			{
				YellowplayerFrame[p_frame_index].setScale(is_player_facing_right ? -2 : 2, 2);
				YellowplayerFrame[p_frame_index].setPosition(player_x + (is_player_facing_right ? PlayerWidth : 0), player_y);
				window.draw(YellowplayerFrame[p_frame_index]);
			}
		}
		else
		{
			if (player_Green)
			{
				p1_j_sprite.setScale(is_player_facing_right ? -2 : 2, 2);
				p1_j_sprite.setPosition(player_x + (is_player_facing_right ? PlayerWidth : 0), player_y);
				window.draw(p1_j_sprite);
			}
			else
			{
				p2_j_sprite.setScale(is_player_facing_right ? -2 : 2, 2);
				p2_j_sprite.setPosition(player_x + (is_player_facing_right ? PlayerWidth : 0), player_y);
				window.draw(p2_j_sprite);
			}
		}
	}
	else
	{
		if (player_Green)
		{
			p1_d_sprite.setScale(is_player_facing_right ? -2 : 2, 2);
			p1_d_sprite.setPosition(player_x + (is_player_facing_right ? PlayerWidth : 0), player_y);
			window.draw(p1_d_sprite);
		}
		else
		{
			p2_d_sprite.setScale(is_player_facing_right ? -2 : 2, 2);
			p2_d_sprite.setPosition(player_x + (is_player_facing_right ? PlayerWidth : 0), player_y);
			window.draw(p2_d_sprite);
		}
		down_key = false;
	}
}

void display_fire(RenderWindow &window, bool is_player_facing_right, Sprite &fire_Sprite, float &fire_x, float &fire_y, bool player_Green)
{
	float scale = (player_Green) ? 2.0f : 2.4f;
	fire_Sprite.setScale(is_player_facing_right ? -scale : scale, scale);
	fire_Sprite.setPosition(fire_x, fire_y);
	window.draw(fire_Sprite);
}

void display_controls(RenderWindow &window, Sprite controls_Sprite[3], Text &BackspaceT)
{
	BackspaceT.setString("PRESS BACKSPACE TO GO BACK TO THE MENU");
	BackspaceT.setCharacterSize(20);
	BackspaceT.setFillColor(Color::White);
	BackspaceT.setPosition(175, 860);

	for (int i = 0; i < 3; i++)
	{
		controls_Sprite[i].setScale(2, 2);
		if (i == 0)
			controls_Sprite[i].setPosition(413, 168);
		else if (i == 1)
			controls_Sprite[i].setPosition(413, 368);
		else if (i == 2)
			controls_Sprite[i].setPosition(413, 568);
		window.draw(controls_Sprite[i]);
	}
	window.draw(BackspaceT);
}

void display_loose(RenderWindow &window, Text &looseT, Text &BackspaceT)
{
	looseT.setString(" 0 LIVES\n\nYOU LOOSE");
	looseT.setCharacterSize(130);
	looseT.setFillColor(Color::White);
	looseT.setPosition(0, 248);

	BackspaceT.setString("PRESS BACKSPACE TO GO BACK TO THE MENU");
	BackspaceT.setCharacterSize(20);
	BackspaceT.setFillColor(Color::White);
	BackspaceT.setPosition(175, 860);

	window.draw(BackspaceT);
	window.draw(looseT);
}

void display_quit(RenderWindow &window, Text &quitText, Text &BackspaceT)
{
	quitText.setString("YOU QUIT FROM THE GAME");
	quitText.setCharacterSize(51);
	quitText.setFillColor(Color::White);
	quitText.setPosition(10, 448);

	BackspaceT.setString("PRESS BACKSPACE TO GO BACK TO THE MENU");
	BackspaceT.setCharacterSize(20);
	BackspaceT.setFillColor(Color::White);
	BackspaceT.setPosition(190, 860);

	window.draw(BackspaceT);
	window.draw(quitText);
}

void display_win(RenderWindow &window, Text &BackspaceT, Text &winText)
{
	winText.setString("YOU WIN");
	winText.setCharacterSize(130);
	winText.setFillColor(Color::White);
	winText.setPosition(130, 340);

	BackspaceT.setString("PRESS BACKSPACE TO GO BACK TO THE MENU\n\n  OR ENTER TO MOVE TO THE NEXT LEVEL");
	BackspaceT.setCharacterSize(20);
	BackspaceT.setFillColor(Color::White);
	BackspaceT.setPosition(190, 830);

	window.draw(BackspaceT);
	window.draw(winText);
}

void display_enemies(RenderWindow &window, Sprite skeleton_sprite[], int total_skeletons, Sprite ghost_sprite[], int total_ghosts, bool is_s_alive[], bool is_g_alive[])
{
	for (int i = 0; i < total_skeletons; i++)
	{
		if (is_s_alive[i])
			window.draw(skeleton_sprite[i]);
	}
	for (int i = 0; i < total_ghosts; i++)
	{
		if (is_g_alive[i])
			window.draw(ghost_sprite[i]);
	}
}

void display_powerups(RenderWindow &window, Text &scoresText, Text &livesText, int scores, int player_lives, bool speed_pu_present, bool life_pu_present, Sprite &speed_sprite, Sprite &life_sprite)
{
	scoresText.setString("scores:" + to_string(scores));
	livesText.setString("Lives: " + to_string(player_lives));
	window.draw(scoresText);
	window.draw(livesText);

	// displaying power ups
	if (speed_pu_present)
		window.draw(speed_sprite);
	if (life_pu_present)
		window.draw(life_sprite);
}

void display_pause(RenderWindow &window, Text &PauseT)
{
	PauseT.setString("PAUSE");
	PauseT.setCharacterSize(100);
	PauseT.setFillColor(Color::Black);
	PauseT.setPosition(330, 320);

	window.draw(PauseT);
}

// -----ALL OTHER FUNCTIONS-----

void move_player(char **lvl, float &offset_x, float &player_x, float speed, bool player_Green, float &player_y, int PlayerHeight, const int cell_size, int PlayerWidth, bool is_player_facing_right)
{
	char mid, bottom;
	if (is_player_facing_right)
	{
		offset_x = player_x;
		offset_x += speed * (player_Green ? 1.5 : 1);
		mid = lvl[(int)(player_y + PlayerHeight / 2) / cell_size][(int)(offset_x + PlayerWidth) / cell_size];
		bottom = lvl[(int)(player_y + PlayerHeight) / cell_size][(int)(offset_x + PlayerWidth) / cell_size];
		if (!(mid == '#' || bottom == '#'))
		{
			player_x = offset_x;
		}
	}
	else
	{
		offset_x = player_x;
		offset_x -= speed * (player_Green ? 1.5 : 1);
		mid = lvl[(int)(player_y + PlayerHeight / 2) / cell_size][(int)(offset_x) / cell_size];
		bottom = lvl[(int)(player_y + PlayerHeight) / cell_size][(int)(offset_x) / cell_size];
		if (!(mid == '#' || bottom == '#'))
		{
			player_x = offset_x;
		}
	}
}

void ghost_move(float g_x[], float g_speed[], float g_y[], Sprite g_Sprite[], float low[], float high[], int ghosts)
{
	for (int i = 0; i < ghosts; i++)
	{
		g_x[i] += g_speed[i];
		if (g_x[i] < low[i])
		{
			g_speed[i] = 2;
			g_Sprite[i].setScale(-2, 2);
			g_x[i] += 64;
		}
		if (g_x[i] > high[i])
		{
			g_speed[i] = -2;
			g_Sprite[i].setScale(2, 2);
			g_x[i] -= 20;
		}
		g_Sprite[i].setPosition(g_x[i], g_y[i]);
	}
}

void skeleton_move(bool &is_skeleton_facing_right, char **lvl, float &skeleton_x, float &skeleton_y, float &skeleton_speed, Sprite &skeleton_sprite, float &skeleton_gravity)
{
	float future_x = skeleton_x;
	float future_y = skeleton_y;
	int cell_size = 64;
	const int sk_width = 64;
	const int sk_height = 76;
	if (is_skeleton_facing_right == true)
		future_x += skeleton_speed;

	else
		future_x -= skeleton_speed;

	// first goal walls
	char left_mid = lvl[(int)(future_y + sk_height / 2) / cell_size][(int)(future_x - sk_width) / cell_size];
	char right_mid = lvl[(int)(future_y + sk_height / 2) / cell_size][(int)(future_x + sk_width) / cell_size];

	if (right_mid == '#')
	{
		is_skeleton_facing_right = false;
		skeleton_sprite.setScale(2, 2);
	}

	else if (left_mid == '#')

	{
		is_skeleton_facing_right = true;
		skeleton_sprite.setScale(-2, 2);
	}
	else
		skeleton_x = future_x;

	// skeleton gravity work

	future_y += skeleton_gravity;

	char bottom_left = lvl[(int)(future_y + sk_height) / cell_size][(int)(skeleton_x) / cell_size];
	char bottom_right = lvl[(int)(future_y + sk_height) / cell_size][(int)((skeleton_x)) / cell_size];
	char bottom_mid = lvl[(int)(future_y + sk_height) / cell_size][(int)((skeleton_x + sk_width / 2)) / cell_size];
	if (bottom_mid == '#' || bottom_right == '#' || bottom_left == '#')
	{
		future_y = ((float)(future_y + sk_height) / cell_size) * cell_size - sk_height;

		skeleton_gravity = 0;
	}
	else
	{
		skeleton_gravity += 0.5f;
	}

	skeleton_y = future_y;
	if (skeleton_x >= 512 && skeleton_x <= 530 && skeleton_y >= 750 && skeleton_y <= 800)
	{
		// teleport the skeleton to the top
		skeleton_x = 512;
		skeleton_y = 128;
	}
	skeleton_sprite.setPosition(skeleton_x, skeleton_y);
}

void player_animation(float &p_animation_timer, float p_animation_speed, int &p_frame_index)
{
	p_animation_timer += p_animation_speed;
	if (p_animation_timer >= 1.0f)
	{
		p_animation_timer = 0.0f;
		p_frame_index++;
		if (p_frame_index > 4)
			p_frame_index = 0;
	}
}

void player_gravity(char **lvl, float &offset_x, float &offset_y, float &velocityY, bool &onGround, const float &gravity, float &terminal_Velocity, float &player_x, float &player_y, const int cell_size, int &Pheight, int &Pwidth, bool &ignoring_tiles)
{

	offset_y = player_y;
	offset_y += velocityY;
	if (velocityY < 0) // moving up
	{
		// calculating row and cols
		int row = (int)offset_y / cell_size;
		int col_right = (int)(offset_x + Pwidth) / cell_size;
		int col_left = (int)(offset_x) / cell_size;
		// rows at which there isn't jumping
		bool hard_row = (row == 9 || row == 11);
		// mid col and rows                        column:   0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 of row: 9
		bool hard_col = (col_right > 6 && col_left < 11); // # # # # # . . # # # #  .  .  #  #  #  #  #
		// using these rows and col to set the blocked region (no jumping zone)
		bool blocked_region = (hard_row && hard_col);
		bool block_check = false;
		int col = (col_left < 7 ? col_right : col_left);
		if (hard_row && lvl[row][col] == '#')
			block_check = true;			   // we found that player is touching the blocks in the blocked region
		if (block_check && blocked_region) // check both blocked region and block check
			velocityY = 0;
		else
		{
			if (offset_y >= 0) // offset_y sometimes become negetive bcz of jumpstrength
			{
				player_y = offset_y;
				onGround = false;
			}
			else
				velocityY = 0;
		}
	}

	else
	{
		char bottom_left_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x) / cell_size];
		char bottom_right_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)((player_x) + Pwidth) / cell_size];
		char bottom_mid_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)((player_x) + Pwidth / 2) / cell_size];
		if ((bottom_left_down == '#' || bottom_mid_down == '#' || bottom_right_down == '#') && !ignoring_tiles)
		{
			onGround = true;
		}
		else
		{
			player_y = offset_y;
			onGround = false;
		}
	}
	if (!onGround)
	{
		velocityY += gravity;
		if (velocityY >= terminal_Velocity)
			velocityY = terminal_Velocity;
	}
	else
	{
		velocityY = 0;
	}

	if (ignoring_tiles)
	{
		char bottom_left_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x) / cell_size];
		char bottom_right_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)((player_x) + Pwidth) / cell_size];
		char bottom_mid_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)((player_x) + Pwidth / 2) / cell_size];
		if (bottom_left_down == '.' || bottom_mid_down == '.' || bottom_right_down == '.')
		{
			ignoring_tiles = false;
		}
	}
}

// is player hits the power ups and is fire hits the enemy
// a --> player, b --> power ups and a --> fire, b --> enemy
bool isColliding(float a_x, float a_y, float a_w, float a_h, float b_x, float b_y, float b_w, float b_h)
{
	return !(a_x + a_w < b_x || a_x > b_x + b_w || a_y + a_h < b_y || a_y > b_y + b_h);
}

// player collision with enemies and resetting
void enemies_collision(bool is_player_facing_right, float &player_x, float &player_y, float enemy_x, float enemy_y, int speed, int &lives)
{
	float tem_player_x = (player_x);
	float tem_enemy_x = (enemy_x);
	///------------------------------------------------faces are discussed
	if ((is_player_facing_right == true) && (speed > 0)) // both right
		tem_player_x += 64;
	if ((is_player_facing_right == false) && (speed < 0)) // both left
		tem_player_x -= 20;
	if ((is_player_facing_right == true) && (speed < 0)) // player right  and enemy left
		tem_player_x;
	if ((is_player_facing_right == false) && (speed > 0)) // player left and enemy right
		tem_player_x += 40;

	float x_dis = abs(tem_player_x - tem_enemy_x);
	float y_dis = abs(player_y - enemy_y);

	// now checking the collision
	if (x_dis <= 40 && y_dis <= 40)
	{

		lives = lives - 1;
		player_x = 66;
		player_y = 762;
	}
}

int main()
{
	RenderWindow window(VideoMode(screen_x, screen_y), "Tumble-POP", Style::Default);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	// level specifics
	const int cell_size = 64;
	const int height = 14;
	const int width = 18;
	char **lvl;
	srand(time(0));
	int level_no = 1;
	Texture slant_uptex, slantdown_tex;
	Sprite slant_upsprite, slant_downsprite;

	slant_uptex.loadFromFile("Data/slantup.png");
	slant_upsprite.setTexture(slant_uptex);

	slantdown_tex.loadFromFile("Data/slantdown.png");
	slant_downsprite.setTexture(slantdown_tex);

	// ----------All images----------
	// -----level and background textures and sprites-----
	Texture bgTex;
	Sprite bgSprite;
	bgTex.loadFromFile("Data/bg.png");
	bgSprite.setTexture(bgTex);
	bgSprite.setPosition(0, 0);

	Texture blockTexture;
	Sprite blockSprite;
	blockTexture.loadFromFile("Data/block1.png");
	blockSprite.setTexture(blockTexture);

	// -----Spritesheet loading-----
	Texture SpriteSheet;
	SpriteSheet.loadFromFile("../Assets/Sprites.png");

	// -----Player selection image-----
	Sprite g_Select_Sprite;
	g_Select_Sprite.setTexture(SpriteSheet);
	g_Select_Sprite.setTextureRect(IntRect(940, 82, 38, 46));

	Sprite y_Select_Sprite;
	y_Select_Sprite.setTexture(SpriteSheet);
	y_Select_Sprite.setTextureRect(IntRect(940, 271, 38, 46));

	// -----fire-----
	Sprite fire_Sprite;
	fire_Sprite.setTexture(SpriteSheet);
	fire_Sprite.setTextureRect(IntRect(349, 174, 48, 29));
	float FireWidth = 96.0f;
	float FireHeight = 58.0f;
	float fire_x = 0;
	float fire_y = 0;

	// -----Ghostsheet loading-----
	Texture ghostSheet;
	ghostSheet.loadFromFile("Data/Ghost.png");
	const int total_ghosts = 8;

	// -----ghost images-----
	// x coordinates of ghosts
	float ghost_x[total_ghosts]; // = {128, 128, 800, 800, 256, 256, 704, 704};
	// y coordinates of ghosts
	float ghost_y[total_ghosts]; //= {512, 256, 256, 512, 128, 640, 128, 640};
	// speed of ghosts
	float ghost_speed[total_ghosts]; // = {2, 2, 2, 2, 2, 2, 2, 2};
	// left and right limits of ghosts
	float ghost_left_x[total_ghosts];  //= {64, 64, 840, 840, 256, 192, 704, 704};
	float ghost_right_x[total_ghosts]; // = {320, 320, 1090, 1090, 512, 448, 896, 960};
	// creating ghost sprites
	// // -----ghost images-----
	// // x coordinates of ghosts
	// float ghost_x[total_ghosts] = {128, 128, 800, 800, 256, 256, 704, 704};
	// // y coordinates of ghosts
	// float ghost_y[total_ghosts] = {512, 256, 256, 512, 128, 640, 128, 640};
	// // speed of ghosts
	// float ghost_speed[total_ghosts] = {2, 2, 2, 2, 2, 2, 2, 2};
	// // left and right limits of ghosts
	// float ghost_left_x[total_ghosts] = {64, 64, 840, 840, 256, 192, 704, 704};
	// float ghost_right_x[total_ghosts] = {320, 320, 1090, 1090, 512, 448, 896, 960};
	// // creating ghost sprites
	Sprite ghost_sprite[total_ghosts];
	for (int i = 0; i < total_ghosts; i++)
	{
		ghost_sprite[i].setTexture(ghostSheet);
		ghost_sprite[i].setTextureRect(IntRect(8, 8, 35, 30));
		ghost_sprite[i].setScale(-2, 2);
		ghost_sprite[i].setPosition(ghost_x[i], ghost_y[i]);
	}
	// kia wo mer gya he?
	bool is_g_alive[total_ghosts]; // = {1, 1, 1, 1, 1, 1, 1, 1};
	bool all_g_die = false;

	// -----Skeletonsheet loading-----
	Texture skeletonSheet;
	skeletonSheet.loadFromFile("Data/Skeleton.png");
	const int total_skeletons = 4;

	// -----skeleton images-----
	// x coordinates of skeletons
	float skeleton_x[total_skeletons] = {200, 800, 150, 900};
	// y coordinates of skeletons
	float skeleton_y[total_skeletons] = {120, 120, 370, 370};
	float skeleton_gravity[total_skeletons] = {0, 0, 0, 0};
	float skeleton_speed[total_skeletons] = {1.5, 1.5, 1.5, 1.5};
	// left and right limits of skeletons
	float skeleton_left_x[total_skeletons] = {210, 670, 210, 750};
	float skeleton_right_x[total_skeletons] = {400, 926, 400, 926};
	// creating skeleton sprites
	Sprite skeleton_sprite[total_skeletons];
	for (int i = 0; i < total_skeletons; i++)
	{
		skeleton_sprite[i].setTexture(skeletonSheet);
		skeleton_sprite[i].setTextureRect(IntRect(8, 34, 32, 38));
		skeleton_sprite[i].setScale(2, 2);
		skeleton_sprite[i].setPosition(skeleton_x[i], skeleton_y[i]);
	}
	bool is_skeleton_facing_right[total_skeletons] = {0, 0, 0, 0};
	// kia wo mer gya he?
	bool is_s_alive[total_skeletons] = {1, 1, 1, 1};
	bool all_s_die = false;

	// -----The title image-----
	Texture Title_Texture;
	Sprite Title_Sprite;
	Title_Texture.loadFromFile("Data/Title.jpg");
	Title_Sprite.setTexture(Title_Texture);
	Title_Sprite.setPosition(0, 0);

	// -----The controls image-----
	Texture controls_Texture;
	controls_Texture.loadFromFile("Data/controls.png");
	Sprite controls_Sprite[3];
	for (int i = 0; i < 3; i++)
	{
		controls_Sprite[i].setTexture(controls_Texture);
		if (i == 0)
			controls_Sprite[i].setTextureRect(IntRect(18, 12, 163, 83));
		else if (i == 1)
			controls_Sprite[i].setTextureRect(IntRect(18, 94, 163, 83));
		else if (i == 2)
			controls_Sprite[i].setTextureRect(IntRect(182, 47, 163, 95));
	}

	// -----loading font-----
	Font gamefont;
	gamefont.loadFromFile("Data/font.ttf");
	// setting text appers in selection
	Text selectText, menuText, select_the_playerText, controlText, quitText, playgameText, EnterText, BackspaceText, looseText, NewgameText, PauseText, WinText, gletter, sletter, _0letter;
	selectText.setFont(gamefont);
	menuText.setFont(gamefont);
	playgameText.setFont(gamefont);
	select_the_playerText.setFont(gamefont);
	controlText.setFont(gamefont);
	quitText.setFont(gamefont);
	EnterText.setFont(gamefont);
	BackspaceText.setFont(gamefont);
	looseText.setFont(gamefont);
	NewgameText.setFont(gamefont);
	PauseText.setFont(gamefont);
	WinText.setFont(gamefont);
	gletter.setFont(gamefont);
	sletter.setFont(gamefont);
	_0letter.setFont(gamefont);

	// score n lives
	int scores = 0;
	int player_lives = 3;
	Text scoresText;
	scoresText.setFont(gamefont);
	scoresText.setCharacterSize(20);
	scoresText.setFillColor(Color::White);
	scoresText.setPosition(900, 80);

	Text livesText;
	livesText.setFont(gamefont);
	livesText.setCharacterSize(20);
	livesText.setFillColor(Color::White);
	livesText.setPosition(185, 80);

	//---------the power ups
	// *****************power up for speed ************
	Sprite speed_sprite;
	float speed_x = 704;
	float speed_y = 384;

	speed_sprite.setTexture(SpriteSheet);
	speed_sprite.setTextureRect(IntRect(21, 389, 21, 21));
	speed_sprite.setScale(2, 2);
	speed_sprite.setPosition(speed_x, speed_y);
	bool speed_pu_present = true;

	// ******************power up for life
	Sprite life_sprite;
	float life_x = 576;
	float life_y = 128;

	life_sprite.setTexture(SpriteSheet);
	life_sprite.setTextureRect(IntRect(490, 386, 24, 24));
	life_sprite.setScale(2, 2);
	life_sprite.setPosition(life_x, life_y);
	bool life_pu_present = true;

	// ------Loading Green player------
	Sprite p1_Sprite[8];
	for (int i = 0; i < 8; i++)
	{
		p1_Sprite[i].setTexture(SpriteSheet);
		// Walking animation frames
		if (i == 0)
			p1_Sprite[i].setTextureRect(IntRect(16, 43, 31, 39));
		else if (i == 1)
			p1_Sprite[i].setTextureRect(IntRect(51, 43, 31, 39));
		else if (i == 2)
			p1_Sprite[i].setTextureRect(IntRect(84, 43, 31, 39));
		else if (i == 3)
			p1_Sprite[i].setTextureRect(IntRect(117, 43, 31, 39));
		else if (i == 4)
			p1_Sprite[i].setTextureRect(IntRect(150, 43, 31, 39));
		// showing Health image
		else if (i == 5)
			p1_Sprite[i].setTextureRect(IntRect(17, 18, 15, 14));
		// jumping sprite
		else if (i == 6)
			p1_Sprite[i].setTextureRect(IntRect(422, 39, 31, 41));
		// falling sprite
		else if (i == 7)
			p1_Sprite[i].setTextureRect(IntRect(525, 31, 31, 42));
	}
	// ------Loading Yellow player------
	Sprite p2_Sprite[8];
	for (int i = 0; i < 8; i++)
	{
		p2_Sprite[i].setTexture(SpriteSheet);
		if (i == 0)
			p2_Sprite[i].setTextureRect(IntRect(16, 232, 31, 39));
		else if (i == 1)
			p2_Sprite[i].setTextureRect(IntRect(51, 232, 31, 39));
		else if (i == 2)
			p2_Sprite[i].setTextureRect(IntRect(84, 232, 31, 39));
		else if (i == 3)
			p2_Sprite[i].setTextureRect(IntRect(117, 232, 31, 39));
		else if (i == 4)
			p2_Sprite[i].setTextureRect(IntRect(150, 232, 31, 39));
		// showing Health image
		else if (i == 5)
			p2_Sprite[i].setTextureRect(IntRect(17, 207, 15, 14));
		// jumping sprite
		else if (i == 6)
			p2_Sprite[i].setTextureRect(IntRect(422, 228, 31, 41));
		// falling sprite
		else if (i == 7)
			p2_Sprite[i].setTextureRect(IntRect(525, 220, 31, 42));
	}

	// -----arrays of both players sprites for animation walking----
	Sprite GreenplayerFrame[5] = {p1_Sprite[0], p1_Sprite[1], p1_Sprite[2], p1_Sprite[3], p1_Sprite[4]};
	Sprite YellowplayerFrame[5] = {p2_Sprite[0], p2_Sprite[1], p2_Sprite[2], p2_Sprite[3], p2_Sprite[4]};
	int p_frame_index = 0;
	float p_animation_timer = 0.0f;
	// -----speed of animation-----
	const float p_animation_speed = 0.15f;

	// true -> green , false -> yellow
	bool player_Green = false;
	// selection index
	int menuarrInd = 0;
	// game pause
	bool pause = false;

	// So there are many states or windows to show the title means Tumblepop image, then menu, then selection, then controls, then game, then gameover
	const int TITLE = 1;
	const int MENU = 2;
	const int SELECT = 3;
	const int CONTROL = 4;
	const int GAME = 5;
	const int LOOSE = 6;
	const int QUIT = 7;
	const int NEWGAME = 8;
	const int WIN = 9;
	// The first is the title
	int current_Window = TITLE;

	// Suction
	const int max_sucked_enemies = 3;
	int suction_count = 0;
	// store 1 and 2 for skeleton and ghosts respectively
	int sucked_enemies[max_sucked_enemies] = {};
	int last_sucked;
	// -----Music initialisation-----
	Music Music;

	Music.openFromFile("Data/mus.ogg");
	Music.setVolume(20);
	Music.play();
	Music.setLoop(true);

	// -----player data-----
	float player_x = 382;
	float player_y = 763;
	float speed = 5;
	const float jumpStrength = -18; // Initial jump velocity
	const float gravity = 1;		// Gravity acceleration
	bool onGround = false;
	float offset_x = 0;
	float offset_y = 0;
	float velocityY = 0;
	float terminal_Velocity = 20;
	int PlayerHeight = 68;
	int PlayerWidth = 64;

	// for clampling the player when it reaches Last ground (down key press)
	bool reach_last_ground = false;
	// ignore the tiles for some time when down key is pressed
	bool ignoring_tiles = false;
	// to track player direction
	bool is_player_facing_right = false;
	// we made this instesd of using onGround because when up key presses player moves up, and durig all this motion we want to show different sprite and on landing the default sprite
	bool onGroundNow = false;
	// down key different sprite
	bool down_key = false;
	// is hit happen? with power ups or fire and enemy
	bool hit = false;
	// load level only for once
	bool new_level = true;

	// creating level array
	lvl = new char *[height];
	for (int i = 0; i < height; i += 1)
	{
		lvl[i] = new char[width];
	}
	// -----storing '.' in the lvl array-----
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			lvl[i][j] = '.';

	Event ev;
	// -----main loop-----
	while (window.isOpen())
	{
		// load level
		if (new_level)
		{
			load_level(level_no, bgTex, bgSprite, lvl, height, width, total_ghosts, ghost_x, ghost_y, ghost_speed, ghost_left_x, ghost_right_x, is_g_alive);
			new_level = false;
		}
		// Whenever we press a key, click the mouse, or resize the window, the OS drops an Event into the part of game window. That part can hold many letters at a time.
		// Event ev; --> ev is a variable (container) which holds the data of one specific event
		// pollEvent() --> a function that goes to that part and check the last event, it make a copy of that event and stores into the ev.
		// this function return 0 or 1, 0 when no event, 1 when an event
		// In each frame we wnat to pull all the events that occurs so that while loop is important
		while (window.pollEvent(ev))
		{
			// ev.type --> what type of event is it?
			if (ev.type == Event::Closed)
			{
				window.close();
			}
			// the event is of the type "a key is pressed"
			if (ev.type == Event::KeyPressed)
			{
				// we want some keys of event to occur only once so we added such tasks into this loop
				// in the below we are only changes the states (windows)
				if (current_Window == TITLE) // if the window is title, on Enter moves to the menu
				{
					// which kind of key is pressed
					if (ev.key.code == Keyboard::Enter)
						current_Window = MENU;
				}
				else if (current_Window == MENU) // if the window is menu
				{
					// computing the indexes of the Text in the menu
					if (ev.key.code == Keyboard::Down)
						menuarrInd = (menuarrInd + 1) % 4;
					else if (ev.key.code == Keyboard::Up)
						menuarrInd = (menuarrInd + 3) % 4;
					else if (ev.key.code == Keyboard::Escape)
						window.close();
					else if (ev.key.code == Keyboard::Enter)
					{
						if (menuarrInd == 0) // moves to the new game
							current_Window = NEWGAME;
						if (menuarrInd == 1)
							current_Window = GAME;
						if (menuarrInd == 2)
							current_Window = SELECT;
						if (menuarrInd == 3)
							current_Window = CONTROL;
					}
				}
				else if (current_Window == SELECT)
				{
					if (ev.key.code == Keyboard::Right)
						player_Green = false;
					else if (ev.key.code == Keyboard::Left)
						player_Green = true;
					else if (ev.key.code == Keyboard::Enter)
					{
						current_Window = MENU;
					}
				}
				else if (current_Window == CONTROL)
				{
					if (ev.key.code == Keyboard::BackSpace)
						current_Window = MENU;
				}
				else if (current_Window == GAME)
				{
					// quit from the game go to the menu
					if (ev.key.code == Keyboard::Q)
						current_Window = QUIT;
					// pause
					else if (ev.key.code == Keyboard::P)
					{
						pause = !pause;
					}
					// removing one enemy from the bag
					else if (ev.key.code == Keyboard::X && !pause)
					{
						if (suction_count > 0)
						{
							last_sucked = suction_count - 1;
							if (sucked_enemies[last_sucked] == 1)
								scores += 75; // skeleton
							else if (sucked_enemies[last_sucked] == 2)
								scores += 50; // ghost
							suction_count--;
							sucked_enemies[last_sucked] = 0;
						}
					}
					// removing all enemies from the bag
					else if (ev.key.code == Keyboard::Y && !pause)
					{
						for (int i = 0; i < 3; i++)
						{
							if (sucked_enemies[i] == 1)
								scores += 75;
							else if (sucked_enemies[i] == 2)
								scores += 50;
							sucked_enemies[i] = 0;
						}
						suction_count = 0;
					}
				}
				else if (current_Window == LOOSE)
				{
					if (ev.key.code == Keyboard::BackSpace)
						current_Window = MENU;
				}
				else if (current_Window == QUIT)
				{
					if (ev.key.code == Keyboard::BackSpace)
						current_Window = MENU;
				}
				else if (current_Window == WIN)
				{
					if (ev.key.code == Keyboard::BackSpace)
						current_Window = MENU;
					if (ev.key.code == Keyboard::Enter)
					{
						level_no = 2;
						new_level = true;
						scores = 0;
						player_lives = 3;
						speed_pu_present = true;
						life_pu_present = true;
						player_x = 382;
						player_y = 763;
						speed = 5;
						suction_count = 0;

						current_Window = GAME;
					}
				}
			}
		}
		// we do not add game functions to the pollEvent loop bcz these all are longlasting means we want such functions to occur infinitely not just for one
		// for example move player and enemies
		if (current_Window == NEWGAME)
		{
			// reset all variables and arrays
			level_no = 1;
			new_level = true;
			reset_game(fire_x, fire_y, ghost_y, ghost_x, skeleton_x, skeleton_y, ghost_speed, is_g_alive, ghost_sprite, skeleton_gravity, skeleton_speed, is_skeleton_facing_right, is_s_alive, skeleton_sprite, scores, player_lives, speed_pu_present, life_pu_present, p_frame_index, p_animation_timer, player_x, player_y, onGround, offset_x, offset_y, velocityY, reach_last_ground, ignoring_tiles, is_player_facing_right, onGroundNow, down_key, hit, pause, suction_count, total_ghosts, total_skeletons, speed, level_no, new_level, ghost_right_x, ghost_left_x, sucked_enemies);
			current_Window = GAME;
		}
		else if (current_Window == GAME)
		{
			if (player_lives < 1)
				current_Window = LOOSE;
			// -----Movement of the player-----
			// pause
			if (!pause)
			{
				// player movement
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					is_player_facing_right = false;
					move_player(lvl, offset_x, player_x, speed, player_Green, player_y, PlayerHeight, cell_size, PlayerWidth, is_player_facing_right);
				}
				if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					is_player_facing_right = true;
					move_player(lvl, offset_x, player_x, speed, player_Green, player_y, PlayerHeight, cell_size, PlayerWidth, is_player_facing_right);
				}
				if (Keyboard::isKeyPressed(Keyboard::Up) && onGround)
				{
					velocityY = jumpStrength;
				}

				// checking weather the player is on Last Platform
				if ((int)(player_y + PlayerHeight) / cell_size >= 12)
				{
					reach_last_ground = true;
				}
				else
					reach_last_ground = false;

				// checking if player is in the blocked region (where down movement doesn't ocuur)
				int col = (int)(player_x + PlayerWidth / 2) / cell_size;
				int row = (int)(player_y + PlayerHeight / 2) / cell_size;
				if (!((row == 2 || row == 4) && col >= 7 && col <= 10))
				{
					// down movement
					if (Keyboard::isKeyPressed(Keyboard::Down) && !reach_last_ground)
					{
						velocityY = 10;
						ignoring_tiles = true;
						down_key = true;
					}
				}
				// -----VACUUM LOGIC-----
				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
					float new_f_width = (player_Green) ? FireWidth : FireWidth * 1.2;
					float new_f_height = (player_Green) ? FireHeight : FireHeight * 1.2;
					fire_y = player_y + ((player_Green) ? 15 : 10);
					// Use this for collision only, why this so lemme explain
					// So, our function isColliding recieves whatever the number we sent, whether it is flipping or not
					// when it is not flipping, default left facing, the x is top left and function also recieves top left and it looks like correct collision
					// but when it is flipped the x becomes top right and junction also recieves top right and collision become weired
					// so we must sent the top left x of both fire and of enemy
					float fire_top_left;
					if (is_player_facing_right)
					{ //                                    top left of fire
					  //                                    |
						// Top left of the player--> ****** |
						//                           *    * **********
						//                           *    * **********
						//                           ******
						fire_top_left = player_x + PlayerWidth;
						fire_x = fire_top_left + new_f_width;
					}
					else
					{ //                                   Top left of the player
					  //                                   |
						//                                 ******
						// top left of fire --> ********** *    *
						//                      ********** *    *
						//                                 ******
						fire_top_left = player_x - new_f_width;
						fire_x = fire_top_left;
					}
					// Skeletons
					for (int i = 0; i < total_skeletons; i++)
					{
						float skeleton_top_left;
						// same the upper logic goes for enemies
						if (skeleton_speed[i] > 0) // facing right
							skeleton_top_left = skeleton_x[i] - 64;
						else
							skeleton_top_left = skeleton_x[i];

						hit = isColliding(fire_top_left, fire_y, new_f_width, new_f_height, skeleton_top_left, skeleton_y[i], 64, 76);
						if (hit && is_s_alive[i] && (suction_count < max_sucked_enemies))
						{
							is_s_alive[i] = 0;
							skeleton_speed[i] = 0; // stop movement
							// fill in the array
							sucked_enemies[suction_count] = 1;
							suction_count++;
						}
					}
					// Ghosts
					for (int i = 0; i < total_ghosts; i++)
					{
						float ghost_top_left;
						// same the upper logic goes for enemies
						if (ghost_speed[i] > 0) // facing right
							ghost_top_left = ghost_x[i] - 70;
						else
							ghost_top_left = ghost_x[i];

						hit = isColliding(fire_top_left, fire_y, new_f_width, new_f_height, ghost_top_left, ghost_y[i], 70, 64);
						if (hit && is_g_alive[i] && (suction_count < max_sucked_enemies))
						{
							is_g_alive[i] = 0;
							ghost_speed[i] = 0; // stop movement
							// fill in the array
							sucked_enemies[suction_count] = 2;
							suction_count++;
						}
					}
				}
				// Animation of the player
				if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Left))
				{
					player_animation(p_animation_timer, p_animation_speed, p_frame_index);
				}
				// enemy skeleton move
				// skeleton special charecteristixs
				for (int i = 0; i < total_skeletons; i++)
				{
					skeleton_move(is_skeleton_facing_right[i], lvl, skeleton_x[i], skeleton_y[i], skeleton_speed[i], skeleton_sprite[i], skeleton_gravity[i]);
				}
				// ghost move calling for  different functions
				ghost_move(ghost_x, ghost_speed, ghost_y, ghost_sprite, ghost_left_x, ghost_right_x, total_ghosts);
			}
			// pause finish

			// player collision with power ups
			if (isColliding(player_x, player_y, PlayerWidth, PlayerHeight, speed_x, speed_y, 30, 30) && speed_pu_present)
			{
				speed *= 2;
				speed_pu_present = false;
				speed_sprite.setPosition(speed_x, speed_y);
			}
			if (isColliding(player_x, player_y, PlayerWidth, PlayerHeight, life_x, life_y, 30, 30) && life_pu_present)
			{
				player_lives++;
				life_pu_present = false;
				life_sprite.setPosition(life_x, life_y);
			}
			for (int i = 0; i < total_ghosts; i++)
			{
				// ghost_move(ghost_x[i],ghost_speed[i],ghost_y[i],ghost_sprite[i],ghost_left_x,ghost_right_x);
				if (is_g_alive[i])
					enemies_collision(is_player_facing_right, player_x, player_y, ghost_x[i], ghost_y[i], ghost_speed[i], player_lives);
			}
			// skeleton collision function call
			for (int i = 0; i < total_skeletons; i++)
			{
				if (is_s_alive[i])
					enemies_collision(is_player_facing_right, player_x, player_y, skeleton_x[i], skeleton_y[i], skeleton_speed[i], player_lives);
			}
			// gravity of the player
			player_gravity(lvl, offset_x, offset_y, velocityY, onGround, gravity, terminal_Velocity, player_x, player_y, cell_size, PlayerHeight, PlayerWidth, ignoring_tiles);
			for (int i = 0; i < total_ghosts; i++)
			{
				if (is_g_alive[i])
				{
					all_g_die = false;
					break;
				}
				else
					all_g_die = true;
			}
			for (int i = 0; i < total_skeletons; i++)
			{
				if (is_s_alive[i])
				{
					all_s_die = false;
					break;
				}
				else
					all_s_die = true;
			}
			if (all_g_die && all_s_die)
			{
				current_Window = WIN;
			}
		}

		window.clear();

		// now displayig all the stuff
		if (current_Window == TITLE)
		{
			display_tumblepop_image(window, Title_Sprite);
		}
		else if (current_Window == MENU)
		{
			main_menu(window, menuText, playgameText, select_the_playerText, controlText, menuarrInd, EnterText, NewgameText);
		}
		else if (current_Window == SELECT)
		{
			display_selection_screen(window, g_Select_Sprite, y_Select_Sprite, player_Green, selectText, EnterText);
		}
		else if (current_Window == CONTROL)
		{
			display_controls(window, controls_Sprite, BackspaceText);
		}
		else if (current_Window == GAME)
		{
			display_level(window, lvl, bgSprite, blockSprite, height, width, cell_size, slant_upsprite, slant_downsprite);
			if (Keyboard::isKeyPressed(Keyboard::Space) && !pause)
				display_fire(window, is_player_facing_right, fire_Sprite, fire_x, fire_y, player_Green);
			int foot_y = (int)(player_y + PlayerHeight + 2) / cell_size;
			char bL = lvl[foot_y][(int)player_x / cell_size];
			char bM = lvl[foot_y][(int)(player_x + PlayerWidth / 2) / cell_size];
			char bR = lvl[foot_y][(int)(player_x + PlayerWidth) / cell_size];
			onGroundNow = (bL == '#' || bM == '#' || bR == '#');
			display_player(window, player_Green, is_player_facing_right, GreenplayerFrame, YellowplayerFrame, p_frame_index, player_x, player_y, PlayerWidth, onGroundNow, p1_Sprite[6], p2_Sprite[6], down_key, p1_Sprite[7], p2_Sprite[7]);
			display_health_image(window, p1_Sprite[5], p2_Sprite[5], player_Green);
			display_enemies(window, skeleton_sprite, total_skeletons, ghost_sprite, total_ghosts, is_s_alive, is_g_alive);
			display_powerups(window, scoresText, livesText, scores, player_lives, speed_pu_present, life_pu_present, speed_sprite, life_sprite);
			for (int i = 0; i < max_sucked_enemies; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (sucked_enemies[j] == 1)
					{
						sletter.setString("S");
						sletter.setCharacterSize(70);
						sletter.setFillColor(Color::Red);
						if (j == 0) sletter.setPosition(450, 10);
						else if (j == 1) sletter.setPosition(550, 10);
						else if (j == 2) sletter.setPosition(650, 10);
						window.draw(sletter);
					}
					else if (sucked_enemies[j] == 2)
					{
						gletter.setString("G");
						gletter.setCharacterSize(70);
						gletter.setFillColor(Color::Red);
						if (j == 0) gletter.setPosition(450, 10);
						else if (j == 1) gletter.setPosition(550, 10);
						else if (j == 2) gletter.setPosition(650, 10);
						window.draw(gletter);
					}
					else 
					{
						_0letter.setString("0");
						_0letter.setCharacterSize(70);
						_0letter.setFillColor(Color::Red);
						if (j == 0) _0letter.setPosition(450, 10);
						else if (j == 1) _0letter.setPosition(550, 10);
						else if (j == 2) _0letter.setPosition(650, 10);
						window.draw(_0letter);
					}
				}
			}
		}
		else if (current_Window == LOOSE)
		{
			display_loose(window, looseText, BackspaceText);
		}
		else if (current_Window == QUIT)
		{
			display_quit(window, quitText, BackspaceText);
		}
		else if (current_Window == WIN)
		{
			display_win(window, BackspaceText, WinText);
		}
		if (pause)
			display_pause(window, PauseText);
		window.display();
	}

	// stopping music and deleting level array
	Music.stop();
	for (int i = 0; i < height; i++)
	{
		delete[] lvl[i];
	}

	delete[] lvl;
	return 0;
}