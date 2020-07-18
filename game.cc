#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "user_input.h"
#include "tetris.h"
#include <vector>
#include <tuple>
using namespace std;
// Override base class with your custom functionality
//data


//
class Game
{
private:
    int max_players = 0;
    vector<Tetris*> games = {nullptr,nullptr};
public:
    Game(int playing)
    {
        max_players = playing;
        for (int index = 0; index < playing; ++index) {
            games[index] = new Tetris();
        }
    }
    bool update(float fElapsedTime, tuple<vector<olc::HWButton>, vector <xinput_controller*>> t)
    {
        for (int index = 0; index < max_players; ++index) {
            bool up=false,  down=false, left=false, right=false;
            //controller
            right = (get<1>(t))[index]->B;
            left = (get<1>(t))[index]->X;
            up = (get<1>(t))[index]->Y;
            down = (get<1>(t))[index]->A;
            //cout<<(down)? "down":"nope";
            if (games[index]->update(fElapsedTime,  up,  down,  left,  right))
                return false;
        }
        return true;
        //games[index].update(float fElapsedTime, bool up, bool down, bool left, bool right);
    }

};

//game engine
class Game_Demo: public olc::PixelGameEngine
{
    private:
    int playing;
    Game* g;
    public:
    Game_Demo()
    {
        sAppName = "Demo";

    }
    ~Game_Demo()
    {
        clean_controller(playing);
    }
    //helpers ============

    tuple<vector<olc::HWButton>, vector <xinput_controller*>> get_intput()
    {
        vector <xinput_controller*> val = update_controller(playing);
 		vector<olc::HWButton> keyboard_buttons = {GetKey(olc::W),GetKey(olc::S),GetKey(olc::D),GetKey(olc::A),GetKey(olc::UP),GetKey(olc::DOWN),GetKey(olc::LEFT),GetKey(olc::RIGHT)};
        return make_tuple(keyboard_buttons, val);

    }
    void set_user_input()
    {
        setup_controllers(playing); // two players max for now

    }
    //main=============
    bool OnUserCreate() override
	{
        //playing = 1;
        //cout<<"how many playing\n";
        //cin >>playing;
        set_user_input();
        g = new Game(1);
        return true;
    }
    bool OnUserUpdate(float fElapsedTime) override
	{

        bool still_running = g->update(fElapsedTime, get_intput());
        //display g
        display_OLC_GAME_ENGINE();
        return still_running;
    }
     void display_OLC_GAME_ENGINE()
    {
        Clear(olc::BLACK);

		// Display ======================
		/*
		// Draw Field
		for (int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHeight; y++)
				screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];

		// Draw Current Piece
		for (int px = 0; px < 4; px++)
			for (int py = 0; py < 4; py++)
				if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] != L'.')
					screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;
		*/
		//not needed on screen =================
		/*
		// Draw next Piece
		for (int px = 0; px < 4; px++)
			for (int py = 0; py < 4; py++)
			{
				screen[(0 + py + 2) * nScreenWidth + (0 + px + 2 + nFieldWidth)] = L' ';
				if (tetromino[nNextPiece][Rotate(px, py, 0)] != L'.')
				{

					screen[(0 + py + 2) * nScreenWidth + (0 + px + 2 + nFieldWidth)] = nNextPiece + 65;
				}
			}
		// Draw Score
		swprintf_s(&screen[2 * nScreenWidth + nFieldWidth + 6], 16, L"SCORE: %8d", nScore);*/

		/*
		//Animate Line Completion
		if (!vLines.empty())
		{
			// Display Frame (cheekily to draw lines)
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
			this_thread::sleep_for(400ms); // Delay a bit
			for (auto& v : vLines)
				for (int px = 1; px < nFieldWidth - 1; px++)
				{
					for (int py = v; py > 0; py--)
						pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
					pField[px] = 0;
				}
			vLines.clear();
		}
		// Display Frame
		*/
		//WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
    }
};


int main()
{
	Game_Demo demo;
	if (demo.Construct(480, 320,4,4,false,true )) //1920, 1080, 1, 1,false,true //real-ish
    {
        demo.Start();
    }
	return 0;
}









// struct Body_seg
// {
// 	int x;
// 	int y;
// };
// struct Player
// {
// 	int x = 0;
// 	int y = 0;
// 	int consumed = 0;
// 	int score = 0;
// 	olc::Key current_direction = olc::E;
// 	vector<Body_seg> body;
// };

// struct Food
// {
// 	int x = 10;
// 	int y = 10;
// 	bool food = False;
// };
// class IsometricDemo : public olc::PixelGameEngine
// {
// public:
// 	IsometricDemo()
// 	{
// 		sAppName = "Coding Quickie: Isometric Tiles";
// 	}

// private:

// 	// Number of tiles in world
// 	olc::vi2d vWorldSize = { 14, 10 };

// 	// Size of single tile graphic
// 	olc::vi2d vTileSize = { 20, 20 };

// 	// Where to place tile (0,0) on screen (in tile size steps)
// 	olc::vi2d vOrigin = { 5, 1 };

// 	// Sprite that holds all imagery
// 	olc::Sprite *sprIsom = nullptr;
// 	olc::Sprite *sprfood = nullptr;
// 	// Pointer to create 2D world array
// 	int *pWorld = nullptr;
// 	Player player;
// 	Food food;
// 	double speed =7.0; // squares/sec
// 	double x=0;
// 	double y=0;

// public:
// 	bool OnUserCreate() override
// 	{
// 		// Load sprites used in demonstration
// 		sprIsom = new olc::Sprite("resources/square.png");
// 		sprfood = new olc::Sprite("resources/food.png");
// 		// Create empty world
// 		pWorld = new int[vWorldSize.x * vWorldSize.y]{ 0 };
// 		return true;
// 	}

// 	bool OnUserUpdate(float fElapsedTime) override
// 	{

// 		Clear(olc::BLACK);
// 		auto dir_W = GetKey(olc::A);
// 		auto dir_E = GetKey(olc::D);
// 		auto dir_S = GetKey(olc::S);
// 		auto dir_N = GetKey(olc::W);
// 		bool eating = False;
// 		//end game
// 		if (player.x < 0 || player.y < 0 || player.x >23 || player.y>23)
// 		{
// 			return false;
// 		}
// 		//food
// 		if (!food.food)
// 		{
// 			food.x = rand() % 24;
// 			food.y = rand() % 24;
// 			food.food = True;
// 		}
// 		DrawPartialSprite(food.x* vTileSize.x, food.y*vTileSize.y, sprfood, 0, 0, vTileSize.x, vTileSize.y, 1);
// 		if (food.x == player.x && food.y == player.y)
// 		{
// 			food.food = false;
// 			++player.consumed;
// 			++player.score;
// 			Body_seg s;
// 			if (!player.body.empty())
// 			{
// 			s.x = (*(--player.body.end())).x;
// 			s.y = (*--player.body.end()).y;
// 			}else
// 			{
// 				s.x = player.x;
// 				s.y = player.y;
// 			}
// 			eating = True;
// 			player.body.push_back(s);
// 		}

// 		if (dir_W.bHeld|| dir_W.bPressed)
// 		{
// 			// cout << "w";
// 			player.current_direction = olc::W;
// 			// 	olc::vi2d vCell = { vMouse.x / vTileSize.x, vMouse.y / vTileSize.y };
// 		}
// 		else if (dir_E.bHeld|| dir_E.bPressed)
// 		{
// 			// cout << "e";
// 			// ++player.x;
// 			player.current_direction = olc::E;
// 			// 	olc::vi2d vCell = { vMouse.x / vTileSize.x, vMouse.y / vTileSize.y };
// 		}
// 		else if (dir_S.bHeld|| dir_S.bPressed)
// 		{
// 			// cout << "s";

// 			// ++player.y;
// 			player.current_direction = olc::S;
// 			// 	olc::vi2d vCell = { vMouse.x / vTileSize.x, vMouse.y / vTileSize.y };
// 		}
// 		else if (dir_N.bHeld|| dir_N.bPressed)
// 		{
// 			// cout << "n";
// 			// --player.y;
// 			player.current_direction = olc::N;
// 			// 	olc::vi2d vCell = { vMouse.x / vTileSize.x, vMouse.y / vTileSize.y };
// 		}
// 		int prev_x = player.x;
// 		int prev_y = player.y;
// 		if (player.current_direction == olc::W)
// 		{
// 			x = x- (speed*fElapsedTime);
// 			player.x = x;
// 		}
// 		else if (player.current_direction == olc::E)
// 		{
// 			// cout << "e";
// 			x = x + (speed*fElapsedTime);
// 			player.x = x;
// 		}
// 		else if (player.current_direction == olc::S)
// 		{
// 			// cout << "s";
// 			y = y+ (speed*fElapsedTime);
// 			player.y = y;
// 		}
// 		else if (player.current_direction == olc::N)
// 		{
// 			// cout << "n";
// 			y = y - (speed*fElapsedTime);
// 			player.y = y;
// 		}
// 		if (prev_x !=player.x || prev_y !=player.y )
// 		{
// 			//update
// 		DrawPartialSprite(player.x* vTileSize.x, player.y*vTileSize.y, sprIsom, 0, 0, vTileSize.x, vTileSize.y);

// 		int size = player.body.size() ;
// 		// if (size > 0)
// 		// {
// 		for (int i = 0; i < size ; ++i)
// 		{
// 			int t1 = player.body[i].x;
// 			int t2 = player.body[i].y;
// 			player.body[i].x = prev_x;
// 			player.body[i].y = prev_y;
// 			DrawPartialSprite(player.body[i].x * vTileSize.x,player.body[i].y*vTileSize.y, sprIsom, 0, 0, vTileSize.x, vTileSize.y);
// 			prev_x = t1;
// 			prev_y = t2;
// 		}
// 		}
// 		else
// 		{
// 			DrawPartialSprite(player.x* vTileSize.x, player.y*vTileSize.y, sprIsom, 0, 0, vTileSize.x, vTileSize.y);

// 			int size = player.body.size() ;
// 			for (int i = 0; i < size ; ++i)
// 			{
// 				DrawPartialSprite(player.body[i].x * vTileSize.x,player.body[i].y*vTileSize.y, sprIsom, 0, 0, vTileSize.x, vTileSize.y);

// 			}
// 		}
// 		int size = player.body.size() ;
// 		for (int i = 0; i < size && !eating; ++i)
// 		{
// 			// DrawPartialSprite(player.body[i].x * vTileSize.x,player.body[i].y*vTileSize.y, sprIsom, 0, 0, vTileSize.x, vTileSize.y);
// 			if (player.x == player.body[i].x  && player.body[i].y ==player.y)
// 			{
// 				cout <<player.x <<player.body[i].x  <<"'"<< player.body[i].y <<player.y;
// 				return false;
// 			}
// 		}


// 		olc::vi2d vMouse = { GetMouseX(), GetMouseY() };

// 	// 	// Work out active cell
// 		olc::vi2d vCell = { vMouse.x / vTileSize.x, vMouse.y / vTileSize.y };
// 	// 	// Work out selected cell by transforming screen cell
// 		olc::vi2d vSelected =
// 		{
// 			(vCell.y - vOrigin.y) + (vCell.x - vOrigin.x),
// 			(vCell.y - vOrigin.y) - (vCell.x - vOrigin.x)
// 		};
// 	// 	// Labmda function to convert "world" coordinate into screen space
// 		auto ToScreen = [&](int x, int y)
// 		{
// 			return olc::vi2d
// 			{
// 				(vOrigin.x * vTileSize.x) + (x - y) * (vTileSize.x / 2),
// 				(vOrigin.y * vTileSize.y) + (x + y) * (vTileSize.y / 2)
// 			};
// 		};

// 	// 	// Draw Hovered Cell Boundary
// 		DrawRect(vCell.x * vTileSize.x, vCell.y * vTileSize.y, vTileSize.x, vTileSize.y, olc::RED);

// 	// 	// Draw Debug Info
// 		// DrawString(4, 4, "Mouse   : " + std::to_string(vMouse.x) + ", " + std::to_string(vMouse.y), olc::WHITE);
// 		DrawString(4, 4, "player   : " + std::to_string(player.x) + ", " + std::to_string(player.y), olc::WHITE);
// 		DrawString(4, 14, "score    : " + std::to_string(player.consumed) + ", " + std::to_string(player.score), olc::WHITE);
// 		// DrawString(4, 24, "Selected: " + std::to_string(vSelected.x) + ", " + std::to_string(vSelected.y), olc::WHITE);
// 		return true;
// 	}
// };


