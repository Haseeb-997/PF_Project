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

// ghost movement function
void ghost_move(float &ghost_x,float &ghost_speed,float &ghost_y,Sprite  &ghost_Sprite,int low, int high)
{
    ghost_x+=ghost_speed;
    if (ghost_x<low)
    {
        ghost_speed=2;
        ghost_Sprite.setScale(-2,2);
        ghost_x+=50;
        
    }
    if (ghost_x>high)
    {
        ghost_speed=-2;
        ghost_Sprite.setScale(2,2);
        ghost_x-=50;  
    }
     ghost_Sprite.setPosition(ghost_x,ghost_y);
}


void display_level(RenderWindow &window, char **lvl, Texture &bgTex, Sprite &bgSprite, Texture &blockTexture, Sprite &blockSprite, const int height, const int width, const int cell_size)
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
		}
	}
}

void player_gravity(char **lvl, float &offset_x, float &offset_y, float &velocityY, bool &onGround, const float &gravity, float &terminal_Velocity, float &player_x, float &player_y, const int cell_size, int &Pheight, int &Pwidth)
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
			block_check = true; // we found that player is touching the blocks in the blocked region
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
		if (bottom_left_down == '#' || bottom_mid_down == '#' || bottom_right_down == '#')
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
}

int main()
{
	RenderWindow window(VideoMode(screen_x, screen_y), "Tumble-POP", Style::Resize);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	// level specifics
	const int cell_size = 64;
	const int height = 14;
	const int width = 18;
	char **lvl;

	// level and background textures and sprites
	Texture bgTex;
	Sprite bgSprite;
	Texture blockTexture;
	Sprite blockSprite;

	bgTex.loadFromFile("Data/bg.png");
	bgSprite.setTexture(bgTex);
	bgSprite.setPosition(0, 0);

	blockTexture.loadFromFile("Data/block1.png");
	blockSprite.setTexture(blockTexture);
	 //
    // ghost loading and other  settings
    Texture ghostTexture1;
    Sprite ghostSprite1;
    
    ghostTexture1.loadFromFile("Data/gh.png");
    ghostSprite1.setTexture(ghostTexture1); 
    ghostSprite1.setScale(-2,2);
    float ghost_x1=128;
    float ghost_y1=502;
    ghostSprite1.setTextureRect(IntRect(6,7,37,34));
    float ghost_speed1=2;
    //
    Texture ghostTexture2;
    Sprite ghostSprite2;
    
    ghostTexture2.loadFromFile("Data/gh.png");
    ghostSprite2.setTexture(ghostTexture2); 
    ghostSprite2.setScale(-2,2);
    float ghost_x2=128;
    float ghost_y2=256;
    ghostSprite2.setTextureRect(IntRect(6,7,37,34));
    float ghost_speed2=2;
    //
    Texture ghostTexture3;
    Sprite ghostSprite3;
    
    ghostTexture3.loadFromFile("Data/gh.png");
    ghostSprite3.setTexture(ghostTexture3); 
    ghostSprite3.setScale(-2,2);
    float ghost_x3=800;
    float ghost_y3=256;
    ghostSprite3.setTextureRect(IntRect(6,7,37,34));
    float ghost_speed3=2;
    //
    Texture ghostTexture4;
    Sprite ghostSprite4;
    
    ghostTexture4.loadFromFile("Data/gh.png");
    ghostSprite4.setTexture(ghostTexture2); 
    ghostSprite4.setScale(-2,2);
    float ghost_x4=800;
    float ghost_y4=502;
    ghostSprite4.setTextureRect(IntRect(6,7,37,34));
    float ghost_speed4=2;


	// Music initialisation
	Music lvlMusic;

	lvlMusic.openFromFile("Data/mus.ogg");
	lvlMusic.setVolume(20);
	lvlMusic.play();
	lvlMusic.setLoop(true);

	// player data
	float player_x = 382;
	float player_y = 763;

	float speed = 5;

	const float jumpStrength = -18; // Initial jump velocity
	const float gravity = 1;		// Gravity acceleration

	bool isJumping = false; // Track if jumping

	bool up_collide = false;
	bool left_collide = false;
	bool right_collide = false;

	Texture PlayerTexture;
	Sprite PlayerSprite;

	bool onGround = false;
	bool is_facing_right = false; // to track player direction

	float offset_x = 0;
	float offset_y = 0;
	float velocityY = 0;

	float terminal_Velocity = 20;

	int PlayerHeight = 68;
	int PlayerWidth = 64;

	bool up_button = false;

	char top_left = '\0';
	char top_right = '\0';
	char top_mid = '\0';

	char left_mid = '\0';
	char right_mid = '\0';

	char bottom_left = '\0';
	char bottom_right = '\0';
	char bottom_mid = '\0';

	char bottom_left_down = '\0';
	char bottom_right_down = '\0';
	char bottom_mid_down = '\0';

	char top_right_up = '\0';
	char top_mid_up = '\0';
	char top_left_up = '\0';

	PlayerTexture.loadFromFile("Data/player.png");
	PlayerSprite.setTexture(PlayerTexture);
	PlayerSprite.setScale(2, 2);
	PlayerSprite.setPosition(player_x, player_y);

	// creating level array
	lvl = new char *[height];
	for (int i = 0; i < height; i += 1)
	{
		lvl[i] = new char[width];
	}

	// Adding level 1 blocks
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
	// adding '.' to all indexes of lvl where # is not present
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (lvl[i][j] != '#')
				lvl[i][j] = '.';

	Event ev;
	// main loop
	while (window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
			{
				window.close();
			}

			if (ev.type == Event::KeyPressed)
			{
			}
		}
		// presing escape to close
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// "Movement of the player"
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			offset_x = player_x;
			offset_x -= speed;
			left_mid = lvl[(int)(player_y + PlayerHeight / 2) / cell_size][(int)(offset_x) / cell_size];
			bottom_left = lvl[(int)(player_y + PlayerHeight) / cell_size][(int)(offset_x) / cell_size];
			if (left_mid == '#' || bottom_left == '#')
				left_collide = true;
			else
			{
				player_x = offset_x;
				is_facing_right = false;
				left_collide = false;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			offset_x = player_x;
			offset_x += speed;
			right_mid = lvl[(int)(player_y + PlayerHeight / 2) / cell_size][(int)(offset_x + PlayerWidth) / cell_size];
			bottom_right = lvl[(int)(player_y + PlayerHeight) / cell_size][(int)(offset_x + PlayerWidth) / cell_size];
			if (right_mid == '#' || bottom_right == '#')
				right_collide = true;
			else
			{
				player_x = offset_x;
				is_facing_right = true;
				right_collide = false;
			}
		}
		// Up
		if (Keyboard::isKeyPressed(Keyboard::Up) && onGround && !up_button)
		{
			velocityY = jumpStrength;
			onGround = false;
			up_button = true;
		}
		else
			up_button = false;

		window.clear();
		
		// ghost movement functio call
        ghost_move(ghost_x1,ghost_speed1,ghost_y1,ghostSprite1,64,320);
        ghost_move(ghost_x2,ghost_speed2,ghost_y2,ghostSprite2,64,320);
        ghost_move(ghost_x3,ghost_speed3,ghost_y3,ghostSprite3,840,1090);
        ghost_move(ghost_x4,ghost_speed4,ghost_y4,ghostSprite4,840,1090); 

		display_level(window, lvl, bgTex, bgSprite, blockTexture, blockSprite, height, width, cell_size);
		player_gravity(lvl, offset_x, offset_y, velocityY, onGround, gravity, terminal_Velocity, player_x, player_y, cell_size, PlayerHeight, PlayerWidth);
		if (is_facing_right)
		{
			PlayerSprite.setScale(-2, 2);
			PlayerSprite.setPosition(player_x + PlayerWidth, player_y);
		}
		else
		{
			PlayerSprite.setScale(2, 2);
			PlayerSprite.setPosition(player_x, player_y);
		}
		window.draw(PlayerSprite);
		// drawing ghosts
		window.draw(ghostSprite1);
        window.draw(ghostSprite2);
        window.draw(ghostSprite3);
        window.draw(ghostSprite4);
		window.display();
	}

	// stopping music and deleting level array
	lvlMusic.stop();
	for (int i = 0; i < height; i++)
	{
		delete[] lvl[i];
	}

	delete[] lvl;
	return 0;
}