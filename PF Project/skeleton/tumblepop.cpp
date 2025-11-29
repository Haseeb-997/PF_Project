#include <iostream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;
int screen_x = 1136;
int screen_y = 896;
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

void player_gravity(char **lvl, float &offset_y, float &velocityY, bool &onGround, const float &gravity, float &terminal_Velocity, float &player_x, float &player_y, const int cell_size, int &Pheight, int &Pwidth)
{
	// ground checking while jumping starts
	offset_y = player_y;
	offset_y += velocityY;
	char bottom_left_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x) / cell_size];
	char bottom_right_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x + Pwidth) / cell_size];
	char bottom_mid_down = lvl[(int)(offset_y + Pheight) / cell_size][(int)(player_x + Pwidth / 2) / cell_size];
	if (bottom_left_down == '#' || bottom_mid_down == '#' || bottom_right_down == '#')
	{
		onGround = true;
	}
	else
	{
		player_y = offset_y;
		onGround = false;
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
	// till here ground checked
}
void move_left(char **lvl, float &player_x, float &player_y, int &Pheight, int &Pwidth, const int cell_size, int speed)
{
	int left_top_y = (int)(player_y - Pheight / 2) / cell_size;
	int left_mid_y = (int)player_y / cell_size;
	int left_bottom_y = (int)(player_y + Pheight / 2) / cell_size;
	int left_x = (int)(player_x - Pwidth / 2) / cell_size;
	char left_top = lvl[left_top_y][left_x];
	char left_mid = lvl[left_mid_y][left_x];
	char left_bottom = lvl[left_bottom_y][left_x];
	if (left_top == '#' || left_mid == '#' || left_bottom == '#')
	{
		player_x -= 0;
	}
	else
		player_x -= speed;
}
void move_right(char **lvl, float &player_x, float &player_y, int &Pheight, int &Pwidth, const int cell_size, int speed)
{
	int right_top_y = (int)(player_y - Pheight / 2) / cell_size;
	int right_mid_y = (int)player_y / cell_size;
	int right_bottom_y = (int)(player_y + Pheight / 2) / cell_size;
	int right_x = (int)(player_x + Pwidth / 2) / cell_size;
	char right_top = lvl[right_top_y][right_x];
	char right_mid = lvl[right_mid_y][right_x];
	char right_bottom = lvl[right_bottom_y][right_x];
	if (right_top == '#' || right_mid == '#' || right_bottom == '#')
	{
		player_x += 0;
	}
	else
		player_x += speed;
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

	// Music initialisation
	Music lvlMusic;

	lvlMusic.openFromFile("Data/mus.ogg");
	lvlMusic.setVolume(20);
	lvlMusic.play();
	lvlMusic.setLoop(true);

	// player data
	float player_x = 100;
	float player_y = 100;

	float speed = 5;

	const float jumpStrength = -20; // Initial jump velocity
	const float gravity = 1;		// Gravity acceleration

	bool isJumping = false; // Track if jumping

	bool up_collide = false;
	bool left_collide = false;
	bool right_collide = false;

	Texture PlayerTexture;
	Sprite PlayerSprite;

	bool onGround = false;

	float offset_x = 0;
	float offset_y = 0;
	float velocityY = 0;

	float terminal_Velocity = 20;

	int PlayerHeight = 34;
	int PlayerWidth = 32;

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
	PlayerSprite.setOrigin(PlayerWidth / 2, PlayerHeight / 2);

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
		// Left
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			PlayerSprite.setScale(2, 2);
			//move_left(lvl, player_x, player_y, PlayerHeight, PlayerWidth, cell_size, speed);
			char left_top = lvl[(int)(player_y) / cell_size][(int)(player_x - 15 - PlayerWidth / 2) / cell_size];
			char left_mid = lvl[(int)(player_y + PlayerHeight / 2) / cell_size][(int)(player_x - 15 - PlayerWidth / 2) / cell_size];
			char left_bottom = lvl[(int)(player_y + PlayerHeight) / cell_size][(int)(player_x - 15 - PlayerWidth / 2) / cell_size];

			if (left_top == '#' || left_mid == '#' || left_bottom == '#')
			{
				player_x = player_x;
			}
			else
			{
				PlayerSprite.setScale(2, 2);
				player_x -= speed;
			}
		}
		// Right
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			PlayerSprite.setScale(-2, 2);
			//move_right(lvl, player_x, player_y, PlayerHeight, PlayerWidth, cell_size, speed);
			// right side collision checking
			char right_top = lvl[(int)(player_y) / cell_size][(int)(player_x + PlayerWidth + speed) / cell_size];
			char right_mid = lvl[(int)(player_y + PlayerHeight / 2) / cell_size][(int)(player_x + PlayerWidth + speed) / cell_size];
			char right_bottom = lvl[(int)(player_y + PlayerHeight) / cell_size][(int)(player_x + PlayerWidth + speed) / cell_size];

			if (right_top == '#' || right_mid == '#' || right_bottom == '#')
			{
				player_x -= speed;
			}
			PlayerSprite.setScale(-2, 2);
			player_x += speed;
			// Walking
			
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

		display_level(window, lvl, bgTex, bgSprite, blockTexture, blockSprite, height, width, cell_size);
		player_gravity(lvl, offset_y, velocityY, onGround, gravity, terminal_Velocity, player_x, player_y, cell_size, PlayerHeight, PlayerWidth);
		PlayerSprite.setPosition(player_x, player_y);
		window.draw(PlayerSprite);

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