#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "user_input.h"


using namespace std;
// Override base class with your custom functionality
//data


//


//game
class Game_Demo: public olc::PixelGameEngine
{
    private:
    int playing;
    public:
    Game_Demo()
    {
        sAppName = "Demo";

    }
    ~Game_Demo()
    {
        clean_controller(playing);
    }
    bool OnUserCreate() override
	{
        playing = 1;
        setup_controllers(playing);
        return true;
    }
    bool OnUserUpdate(float fElapsedTime) override
	{

        auto controllers = update(playing);
		if (all_players_connected(playing))
		{

			for (int index = 0; index < playing; ++index) {
				if (controllers[index]->A)
				{

					std::cout << index << " player jumps \n";
				}
			}

		}
		else
		{
		    //pause game
			std::cout << "reconnect controller";
		}
		clean_controller_input(controllers);






        return true;
    }
};


int main()
{
    cout<<"hello\n";
	Game_Demo demo;
	if (demo.Construct( 1920, 1080, 1, 1,false,true))
		demo.Start();
    // Game_Demo gd;
    // gd.Start();
    cout<<"exit\n";
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


