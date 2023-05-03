

#include "CommonFunc.h"
#include "BaseObject.h"
#include "gmap.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
BaseObject g_background;
BaseObject g_menu;

// Khoi dong thong so cho mtrg SDL
bool InitData()
{
    bool success = true;

    int ret = SDL_Init(SDL_INIT_VIDEO);
    if ( ret < 0 ) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    g_window = SDL_CreateWindow("Running Man Game", SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
        success = false;
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL)
             success = false;
        else
        {
            SDL_SetRenderDrawColor(g_screen, 255, 255 ,255 ,255);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                success = false;
        }
        
    }

    return success;
}

bool LoadBackGround()
{
    bool ret = g_background.LoadImg( "image//background2.png", g_screen );
    if ( ret == false) return false;
    return true;
}

void close()
{
	//Free loaded image
	SDL_DestroyRenderer( g_screen );
	g_screen = NULL;

	//Destroy window
	SDL_DestroyWindow( g_window );
	g_window = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

std::vector<ThreatsObject*> MakeThreadList()
{
	std::vector<ThreatsObject*> list_threats;

	ThreatsObject* dynamic_threats = new ThreatsObject[20];
	for(int i = 0; i < 20; i++)
	{
		ThreatsObject* p_threat = (dynamic_threats + i);
		if(p_threat != NULL)
		{
			p_threat->LoadImg("image//threat_left.png", g_screen);
			p_threat->set_clips();
			p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
			p_threat->set_x_pos(1000 + i * 500);
			p_threat->set_y_pos(200);

			int pos1 = p_threat->get_x_pos() - 60;
			int pos2 = p_threat->get_x_pos() + 60;
			p_threat->SetAnimationPos(pos1, pos2);
			p_threat->set_input_left(1);
			list_threats.push_back(p_threat);
		}
	}

	ThreatsObject* threats_objs = new ThreatsObject[20];
	for(int i = 0; i < 20; i++)
	{
		ThreatsObject* p_threat = (threats_objs + i);
		if(p_threat != NULL)
		{
			p_threat->LoadImg("image//threat_level.png", g_screen);
			p_threat->set_clips();
			p_threat->set_x_pos(700 + i*1200);
			p_threat->set_y_pos(250);
			p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
			p_threat->set_input_left(0);
			list_threats.push_back(p_threat);
		}
	}
	return list_threats;
}

int main( int argc, char* argv[] )
{
	ImpTimer fps_timer;
	if(InitData() == false) return -1;

	if(LoadBackGround() == false) return -1;

	GameMap game_map;
	game_map.LoadMap("map/map01.dat");
	game_map.LoadTiles(g_screen);

	MainObject p_player;
	p_player.LoadImg("image//player_right.png", g_screen);
	p_player.set_clips();

	std::vector<ThreatsObject*> threat_list = MakeThreadList();
	

			//Main loop flag
			bool quit = false;

			// //Event handler
			// SDL_Event event;

			//While application is running
			while( !quit )
			{
				fps_timer.start();
				//Handle events on queue
				while( SDL_PollEvent( &g_event ) != 0 )
				{
					//User requests quit
					if( g_event.type == SDL_QUIT )
					{
						quit = true;
					}

					p_player.HandelInputAction(g_event, g_screen);
				}

				SDL_SetRenderDrawColor(g_screen, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(g_screen);

				g_background.Render(g_screen, NULL);
				
				Map map_data = game_map.getMap();
				
				p_player.HandleBullet(g_screen);
				p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
				p_player.DoPlayer(map_data);
				p_player.Show(g_screen);

				game_map.SetMap(map_data);
				game_map.DrawMap(g_screen);

				for(int i=0; i < threat_list.size(); i++)
				{
					ThreatsObject* p_threat = threat_list.at(i);
					if(p_threat != NULL)
					{
						p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
						p_threat->ImpMoveType(g_screen);
						p_threat->DoPlayer(map_data);
						p_threat->Show(g_screen);

					}
				}

				SDL_RenderPresent(g_screen);

				int real_imp_time = fps_timer.get_ticks();
				int time_one_frame = 1000/FRAME_PER_SECOND; // ms  (thoi gian chay 1 frame)

				if(real_imp_time < time_one_frame)
				{
					int delay_time = time_one_frame - real_imp_time;
					SDL_Delay(delay_time);
				}
			}

	//Free resources and close SDL
	close();

	return 0;
}
