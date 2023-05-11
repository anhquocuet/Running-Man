

#include "CommonFunc.h"
#include "BaseObject.h"
#include "gmap.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "TextObject.h"
#include "healthpoint.h"
#include "Geometric.h"

BaseObject g_background;
BaseObject g_menu;
TTF_Font* font_time;
TTF_Font* font_time_2;
ImpTimer fps_timer;
BaseObject g_endgame;

Mix_Chunk* gMusic = NULL;
Mix_Chunk* gDie = NULL;

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

			if(TTF_Init() == -1)
			{
				success = false;
			}

			font_time = TTF_OpenFont("font//joystixmonospace.ttf", 15);
			font_time_2 = TTF_OpenFont("font//joystixmonospace.ttf", 40);
			if(font_time == NULL)
			{
				success = false;
			}

			if ( SDL_Init(SDL_INIT_AUDIO) < 0 )
            	success = false;
        	else if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) success = false;
        }
        
    }

	gMusic = Mix_LoadWAV( "sound//theme.wav" );
    if( gMusic == NULL ) success = false;
    gDie = Mix_LoadWAV( "sound//dead.wav" );
    if( gDie == NULL ) success = false;

    return success;
}

bool LoadBackGround(std::string path, BaseObject& temp)
{
    bool ret = temp.LoadImg(path , g_screen );
    if ( ret == false) return false;
    return true;
}


void close()
{	
    Mix_FreeChunk( gDie ); gDie = NULL;
    Mix_FreeChunk( gMusic ); gMusic = NULL;
	//Free loaded image
	SDL_DestroyRenderer( g_screen );
	g_screen = NULL;

	//Destroy window
	SDL_DestroyWindow( g_window );
	g_window = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
    Mix_Quit();
}



bool checkpositionforrect(const int& x, const int& y, SDL_Rect rect)
{
    if (x >= rect.x && x <= rect.x + rect.w && y <= rect.y + rect.h && y >= rect.y)
    {
        return true;
    }
        return false;
}

int showMenu(SDL_Event g_event)
{
    g_menu.LoadImg("image//menu.png",g_screen);
    g_menu.Render(g_screen);

    SDL_Rect pos_arr[2];
    pos_arr[0].x = 200;
    pos_arr[0].y = 440;
    pos_arr[1].x = 200;
    pos_arr[1].y = 500;

    TextObject  text_menu[2];
    text_menu[0].SetText("PLAY GAME");
    text_menu[0].SetColor(TextObject :: BLACK_TEXT);
    text_menu[0].LoadFromRenderText(font_time_2, g_screen);
    text_menu[0].RenderText(g_screen, pos_arr[0].x , pos_arr[0].y);
    text_menu[0].Set_Rect(pos_arr[0].x , pos_arr[0].y);
    

    text_menu[1].SetText("EXIT");
    text_menu[1].SetColor(TextObject :: BLACK_TEXT);
    text_menu[1].LoadFromRenderText(font_time_2, g_screen);
    text_menu[1].RenderText(g_screen , pos_arr[1].x , pos_arr[1].y);
    text_menu[1].Set_Rect(pos_arr[1].x , pos_arr[1].y);
    
    bool selected [2] = {0,0};

    int xm = 0;
    int ym = 0;

    while (true)
    {
        while(SDL_PollEvent(&g_event))
        {
            switch(g_event.type)
            {
                case SDL_QUIT :
                    return 1;
                case SDL_MOUSEMOTION:
                {
                    xm = g_event.motion.x;
                    ym = g_event.motion.y;
                    
                    for (int i =0; i < 2 ; i++)
                    {
                        if(checkpositionforrect(xm , ym , text_menu[i].Get_Rect()))
                        {
                            if(selected[i] == false)
                            {
                                selected[i]= 1;
                                text_menu[i].SetColor(TextObject::RED_TEXT);
                                text_menu[i].LoadFromRenderText(font_time_2, g_screen);
                                text_menu[i].RenderText(g_screen, pos_arr[i].x , pos_arr[i].y);
                            }
                        }
                        else 
                        {
                            if(selected[i]==true)
                            {
                                selected[i]=0;
                                text_menu[i].SetColor(TextObject::BLACK_TEXT);
                                text_menu[i].LoadFromRenderText(font_time_2, g_screen);
                                text_menu[i].RenderText(g_screen, pos_arr[i].x , pos_arr[i].y);
                            }
                        }
                    }
                }
                break;
                case SDL_MOUSEBUTTONDOWN:
                {
                    xm = g_event.button.x;
                    ym = g_event.button.y;
                    for (int i =0; i < 2 ; i++)
                    {
                        if(checkpositionforrect(xm , ym , text_menu[i].Get_Rect()))
                        {
                            
                            // Mix_PlayChannel(-1,g_click,0);
                            SDL_Delay(1000);
                            return i;
                        }
                    }
                }
                break; 
                case SDL_KEYDOWN:
                if(g_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 1;
                }
                default: 
                break;
            }

        }
        SDL_RenderPresent(g_screen);
    }  
    return 1;
}

int showEndGame(SDL_Event g_event,bool is_win)
{
    SDL_Rect pos_arr[2];

    pos_arr[0].x = SCREEN_WIDTH*0.43;
    pos_arr[0].y = SCREEN_HEIGHT*0.75;
    pos_arr[1].x = SCREEN_WIDTH*0.43;
    pos_arr[1].y = SCREEN_HEIGHT*0.85;

    TextObject text_menu[2];

    if(is_win == false)
    {
        g_endgame.LoadImg("image//gameover.png",g_screen);
        g_endgame.Render(g_screen);
    }
    else if(is_win == true)
    {
        g_endgame.LoadImg("image//youwin.png",g_screen);
        g_endgame.Render(g_screen);

    }
    
    text_menu[0].SetText("RETRY");
    text_menu[0].SetColor(TextObject :: WHITE_TEXT);
    text_menu[0].LoadFromRenderText(font_time_2,g_screen);
    text_menu[0].RenderText(g_screen, pos_arr[0].x , pos_arr[0].y);
    text_menu[0].Set_Rect(pos_arr[0].x , pos_arr[0].y);
    

    text_menu[1].SetText("EXIT");
    text_menu[1].SetColor(TextObject :: WHITE_TEXT);
    text_menu[1].LoadFromRenderText(font_time_2 , g_screen);
    text_menu[1].RenderText(g_screen , pos_arr[1].x , pos_arr[1].y);
    text_menu[1].Set_Rect(pos_arr[1].x , pos_arr[1].y);
    
    bool selected [2] = {0,0};

    int xm = 0;
    int ym = 0;

    while (true)
    {
        while(SDL_PollEvent(&g_event))
        {
            switch(g_event.type)
            {
                case SDL_QUIT :
                    return 1;
                case SDL_MOUSEMOTION:
                {
                    xm = g_event.motion.x;
                    ym = g_event.motion.y;
                    
                    for (int i =0; i < 2 ; i++)
                    {
                        if(checkpositionforrect(xm , ym , text_menu[i].Get_Rect()))
                        {
                            if(selected[i] == false)
                            {
                                selected[i]= 1;
                                text_menu[i].SetColor(TextObject::RED_TEXT);
                                text_menu[i].LoadFromRenderText(font_time_2 , g_screen);
                                text_menu[i].RenderText(g_screen, pos_arr[i].x , pos_arr[i].y);
                            }
                        }
                        else 
                        {
                            if(selected[i]==true)
                            {
                                selected[i]=0;
                                text_menu[i].SetColor(TextObject::WHITE_TEXT);
                                text_menu[i].LoadFromRenderText(font_time_2 , g_screen);
                                text_menu[i].RenderText(g_screen, pos_arr[i].x , pos_arr[i].y);
                            }
                        }
                    }
                }
                break;
                case SDL_MOUSEBUTTONDOWN:
                {
                    xm = g_event.button.x;
                    ym = g_event.button.y;
                    for (int i =0; i < 2 ; i++)
                    {
                        if(checkpositionforrect(xm , ym , text_menu[i].Get_Rect()))
                        {

                            return i;
                        }
                    }
                }
                break; 
                case SDL_KEYDOWN:
                if(g_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 1;
                }
                default: 
                break;
            }

        }
        SDL_RenderPresent(g_screen);
    }  
    return 1;
}



std::vector<ThreatsObject*> MakeThreadList()
{
	std::vector<ThreatsObject*> list_threats;

	ThreatsObject* dynamic_threats = new ThreatsObject[15];
	for(int i = 0; i < 15; i++)
	{
		ThreatsObject* p_threat = (dynamic_threats + i);
		if(p_threat != NULL)
		{
			p_threat->LoadImg("image//threat_left.png", g_screen);
			p_threat->set_clips();
			p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
			p_threat->set_x_pos(400 + i * 700);
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
			p_threat->set_x_pos(715 + i*1200);
			p_threat->set_y_pos(250);
			p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
			p_threat->set_input_left(0);
			list_threats.push_back(p_threat);
		}
	}
	return list_threats;
}

void SetFps(ImpTimer fps_timer)
{
    int real_imp_time = fps_timer.get_ticks();
    int time_one_frame = 1000/FRAME_PER_SECOND;
    if (real_imp_time<time_one_frame)
    {
        int delay_time = time_one_frame - real_imp_time;
        if (delay_time >= 0) SDL_Delay(delay_time);
    }
}

int main( int argc, char* argv[] )
{

	if(InitData() == false) return -1;
    int time_play = 250;
	bool quit = false;
	int check_menu = showMenu(g_event);
	if(check_menu == 1) quit = true;

	Mix_PlayChannel( -1, gMusic, -1  );


	if(LoadBackGround("image//background2.png", g_background) == false) return -1;

	//Map
	GameMap game_map;
	game_map.LoadMap("map/map02.dat");
	game_map.LoadTiles(g_screen);

	// Player****
	MainObject p_player;
	p_player.LoadImg("image//right.png", g_screen);
	p_player.set_clips();

	HealthPoint player_live;
	player_live.Init(g_screen);


	std::vector<ThreatsObject*> threat_list = MakeThreadList();

	int num_die = 0;
    bool gameover = false;
	
	// Time Text
	TextObject time_game;
	time_game.SetColor(TextObject::WHITE_TEXT);

	TextObject score_game, highscore_game;
	score_game.SetColor(TextObject::WHITE_TEXT);
	highscore_game.SetColor(TextObject::RED_TEXT);
	

			//Main loop flag
		
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
				

				p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
				p_player.DoPlayer(map_data);
				p_player.Show(g_screen);

				game_map.SetMap(map_data);
				game_map.DrawMap(g_screen);

				//Draw Rectangle
				GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 47) ;
				ColorData color_data(60, 60, 60) ;
				Geometric::RenderRectangle(rectangle_size, color_data, g_screen);

				GeometricFormat outLine_size(1, 1, SCREEN_WIDTH - 1, 45) ;
				ColorData color_data2(255, 255, 255) ;

				Geometric::RenderOutline(outLine_size, color_data2, g_screen);


				player_live.Show(g_screen);

				for(int i=0; i < threat_list.size(); i++)
				{
					ThreatsObject* p_threat = threat_list.at(i);
					if(p_threat != NULL)
					{
						p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
						p_threat->ImpMoveType(g_screen);
						p_threat->DoPlayer(map_data);
						p_threat->Show(g_screen);

						SDL_Rect rect_player = p_player.GetRectFrame();
						
						SDL_Rect rect_threat = p_threat->GetRectFrame();

						bool bCol1 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);

						if(bCol1 == true || p_player.get_dead() == true)
						{
							num_die++;
							if(num_die <= 2)
							{

								p_player.SetRect(0, 0);  // Không có thì game over luôn
								p_player.set_come_back_time(20);
								SDL_Delay(500);
								player_live.Decrease();
								p_player.set_dead(false);
								player_live.Render(g_screen);
								continue;
							}
							else 
							{
								// Game Over
;
							Mix_PlayChannel(-1, gDie, 0);
							SDL_Delay(2000);
							// p_threat->Free();
							// close();
							// SDL_Quit();
                            p_player.set_dead(false);
							// quit = true;
                            gameover = true;
							// return 0;
							}
						}

					}
				}
				
				// show game time
				std::string str_time = "Time: ";
				Uint32 time_val = SDL_GetTicks() / 1000;
				Uint32 val_time = time_play - time_val;
				if(val_time <= 0)
				{	
                	quit = true;
                	break;    		
				}
				else
				{
					std::string str_val = std::to_string(val_time);
					str_time += str_val;

					time_game.SetText(str_time);
					time_game.LoadFromRenderText(font_time, g_screen);
					time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);  
				}

				//Score
				std::string strScore("Your Score: ");
				int point_val = p_player.GetMoneyCount();	

				std::string score_val = std::to_string(point_val);
				strScore += score_val;
				score_game.SetText(strScore);
				score_game.LoadFromRenderText(font_time, g_screen);
				score_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 250, 15);

				std::string strbestscore("HighScore: ");
				int highscore = SDLCommonFunc::getBestPoint();
				std::string highscore_str = std::to_string(highscore);
				if(point_val > highscore)
				{
					highscore = point_val;
					SDLCommonFunc::fixBestPoint(highscore);
				}
				
					
					strbestscore += highscore_str;
					highscore_game.SetText(strbestscore);
					highscore_game.LoadFromRenderText(font_time, g_screen);
					highscore_game.RenderText(g_screen, SCREEN_WIDTH*0.5 , 15);

				//*/

				SDL_RenderPresent(g_screen);

				SetFps(fps_timer);

				bool check_win = p_player.get_win();
                if(check_win == true)
                {
                    int check_you_win = showEndGame(g_event, true);   
                    if(check_you_win == 1) quit = true;
                    if(check_you_win == 0) 
                    {
                        p_player.reset_game();
                        time_play = 250;
                        p_player.set_win(false);
                        player_live.Increase();
                        p_player.Render(g_screen);
                        gameover = false;
                        num_die = 0;
                    }
                }
                if(gameover == true)
                {
                    int check_game_over = showEndGame(g_event, false);
                    if(check_game_over == 1) quit = true;
                    if(check_game_over == 0) 
                    {
                        p_player.reset_game();
                        time_play = 250;
                        p_player.set_win(false);
                        player_live.Increase();
                        p_player.Render(g_screen);
                        gameover = false;
                        num_die = 0;
                    }
                }
			}

	//Free resources and close SDL
	close();

	return 0;
}
