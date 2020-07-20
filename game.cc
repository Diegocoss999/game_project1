#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "user_input.h"
#include "tetris.h"
#include <vector>
#include <tuple>
#include <map>
using namespace std;
// Override base class with your custom functionality
//data


//
int screen_resolution_x = 1080;
int screen_resolution_y = 1920;
class Game
{
private:
    int max_players = 0;
    vector<Tetris*> games = {nullptr,nullptr};

    //" ABCDEFG=#"[pField[y * nFieldWidth + x]];
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
        //cout<<"gupdate";
        vector<olc::HWButton> keyboard =(get<0>(t));
        //{GetKey(olc::W),GetKey(olc::S),GetKey(olc::A),GetKey(olc::D),GetKey(olc::UP),GetKey(olc::DOWN),GetKey(olc::LEFT),GetKey(olc::RIGHT)};
        vector <xinput_controller*> controllers = (get<1>(t));
        for (int index = 0; index < max_players; ++index) {
            bool z=false,  down=false, left=false, right=false;
            //controller
            //cout << "update";
            z = (controllers[index]->Y || keyboard[0 + index*4].bPressed)?true:false;
            down = (controllers[index]->A || keyboard[1+ index*4].bPressed)?true:false;
            left = (controllers[index]->X || keyboard[2+ index*4].bPressed)?true:false;
            right = (controllers[index]->B || keyboard[3+ index*4].bPressed)?true:false;
            //cout << "update";
            if (games[index]->update(fElapsedTime,  z,  down,  left,  right))
                return false;
        }
        return true;
        //games[index].update(float fElapsedTime, bool up, bool down, bool left, bool right);
    }
    int get_score(int player)
    {
        return games[(player < max_players && player >=0)?player:0]->get_score();
        /*vector<int> f[playing];
        for (int index = 0; index < max_players; ++index)
        {
            f[index] = games[index].get_field();
        }
        return f;*/
    }
    vector<wchar_t*> get_fields()
    {
        vector<wchar_t*> f;
        for (int index = 0; index < max_players; ++index)
        {
            f.push_back( games[index]->get_field());
        }
        return f;
    }
};

//game engine
class Game_Demo: public olc::PixelGameEngine
{
    private:
    int playing ;
    Game* g;
    map<char,olc::vf2d> tileset_map = {{' ', olc::vf2d(150,150)},{'A', olc::vf2d(0,0)},{'B', olc::vf2d(30,0)},{'C', olc::vf2d(60,0)},{'D', olc::vf2d(0,30)},{'E', olc::vf2d(30,30)},{'F', olc::vf2d(60,30)},{'G', olc::vf2d(0,60)},{'=', olc::vf2d(30,60)},{'#', olc::vf2d(60,60)}};
    //graphix
    olc::Sprite *a1,*a2,*a3,*a4,*tileset;
    olc::Decal *tileset_d;
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
        //cout<<"gd_input";
        vector <xinput_controller*> val = update_controller(playing);
        //cout<<"error";
 		vector<olc::HWButton> keyboard_buttons = {GetKey(olc::W),GetKey(olc::S),GetKey(olc::A),GetKey(olc::D),GetKey(olc::UP),GetKey(olc::DOWN),GetKey(olc::LEFT),GetKey(olc::RIGHT)};
        //cout<<"gd_input_end";
        return make_tuple(keyboard_buttons, val);

    }
    void set_user_input()
    {
        setup_controllers(playing); // two players max for now

    }
    //main=============
    bool OnUserCreate() override
	{
 		/*
 		a1 = new olc::Sprite("resources/pixel_art1.png");
 		a2 = new olc::Sprite("resources/pixel_art2.png");
 		a3 = new olc::Sprite("resources/pixel_art3.png");
 		a4 = new olc::Sprite("resources/pixel_art4.png");
 		*/
 		playing = 1;
 		tileset = new olc::Sprite("resources/tileset.png");
 		tileset_d = new olc::Decal(tileset);
        set_user_input();

        g = new Game(playing);
        return true;
    }
    bool OnUserUpdate(float fElapsedTime) override
	{
        //cout<<"gupdate";
        bool still_running = g->update(fElapsedTime, get_intput());
        //cout<<"update";
        //display g
        display_OLC_GAME_ENGINE();
        return still_running;
    }
     void display_OLC_GAME_ENGINE()
    {
        Clear(olc::BLACK);
        //DrawSprite(0, 0, tileset,  2);
        //olc::vf2d pos = olc::vf2d(0,0);
        //olc::vf2d tileset_pos =olc::vf2d(0,0);
        olc::vf2d tileset_size = olc::vf2d(30,30);
        //DrawPartialDecal(pos, tileset_d, tileset_pos,tileset_size);
        int block_size = 30;
        /*
        for (int y = 0; y < screen_resolution_y/block_size; ++y)
        {
            for (int x = 0; x < screen_resolution_x/block_size; ++x)
            {

                olc::vf2d pos = olc::vf2d(y*block_size,x*block_size);
                //DrawPartialDecal(pos, tileset_d, tileset_pos,tileset_size);
            }
        }
        */
        {
            auto fs = g->get_fields();
            auto f = fs[0];
            //cout<<f;
            //cout<<"nope";
            for (int y = 0; y < 18; ++y)//screen_resolution_y/block_size
            {
                for (int x = 0; x < 12; ++x)
                {
                    //char wchar_t wide = f[y*18 + x];
                    char character = (f[y*12 + x] >= 0 && f[y*12 + x] < 256 )? static_cast<char>(f[y*12 + x]): ' ';

                    olc::vf2d pos = olc::vf2d(x*block_size+100,y*block_size+150);
                    DrawPartialDecal(pos, tileset_d, tileset_map[character],tileset_size);
                }
            }
        }
        //cout<<"error";
        if (playing == 2)
        {
            auto fs = g->get_fields();
            //cout<< "nope";
            auto f = fs[1];
            //cout<<f;
            //cout<<"nope";
            for (int y = 0; y < 18; ++y)//screen_resolution_y/block_size
            {
                for (int x = 0; x < 12; ++x)
                {
                    //char wchar_t wide = f[y*18 + x];
                    char character = (f[y*12 + x] >= 0 && f[y*12 + x] < 256 )? static_cast<char>(f[y*12 + x]): ' ';

                    olc::vf2d pos = olc::vf2d(x*block_size+500,y*block_size+150);



                    DrawPartialDecal(pos, tileset_d, tileset_map[character],tileset_size);
                }
            }
        }

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
		DrawString(4, 14, "score    : " + std::to_string(g->get_score(0)) + ", " + std::to_string(g->get_score(1)), olc::WHITE, 5);
    }
};


int main()
{
	Game_Demo demo;
	if (demo.Construct( screen_resolution_y, screen_resolution_x, 1,1,false, false )) //1920, 1080, 1, 1,false,true //real-ish//480, 320,4,4,false,true//1280, 720,4,4,false,true
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


