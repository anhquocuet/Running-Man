#include "MainObject.h"

MainObject::MainObject()
{
    frame_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = -1;
    input_type_.right_ = 0;
    input_type_.left_ = 0;
    input_type_.up_ = 0;
    input_type_.down_ = 0;
    input_type_.jump_ = 0;
    on_ground_ = false;
    map_x_ = 0;
    map_y_ = 0;
    come_back_time = 0;
    money_count = 0;
    dead = false;
    win = NULL;

} 

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if(ret == true) 
    {
        width_frame_ = rect_.w/PLAYER_FRAME_NUM;
        height_frame_ = rect_.h;
    }

    return ret;
}

SDL_Rect MainObject::GetRectFrame()
 {
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
 }

void MainObject::set_clips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        for (int i = 0; i < PLAYER_FRAME_NUM; i++)
        {
            frame_clip_[i].x = i*width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }           
}

void MainObject::Show(SDL_Renderer* des)
{
    if (on_ground_ == true)
    {
        if (status_ == WALK_LEFT)
        {
            LoadImg("image//left.png", des);
        }
        else 
        {
            LoadImg("image//right.png", des);
        }
    }
    else
    {
        if (status_ == WALK_LEFT)
        {
            LoadImg("image//jumpleft.png", des);
        }
        else
        {
            LoadImg("image//jumpright.png", des);
        }
    }
    
    if(input_type_.left_ == 1 || input_type_.right_ ==1)
    {
        frame_++;
    } 
    else 
    {
        frame_ = 0;
    }

    if(frame_ >= 8)
    {
        frame_ = 0;
    }

    if(come_back_time == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;

        SDL_Rect* current_clip = &frame_clip_[frame_];

        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

        SDL_RenderCopy(des, p_object_, current_clip, &renderQuad); 
    }
}

void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen)
{
    if(events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
            case SDLK_RIGHT:
                {
                    status_ = WALK_RIGHT;
                    input_type_.right_ = 1;
                    input_type_.left_ = 0;

                    if(on_ground_ == true)
                    {
                        LoadImg("image//right.png", screen);
                    }
                    else 
                    {
                        LoadImg("image//jumpright.png", screen);
                    }
                }
                break;
            case SDLK_LEFT:
                {
                    status_ = WALK_LEFT;
                    input_type_.left_ = 1;
                    input_type_.right_ = 0;

                    if(on_ground_ == true)
                    {
                        LoadImg("image//left.png", screen);
                    }
                    else 
                    {
                        LoadImg("image//jumpleft.png", screen);
                    }
                }
                break;
            case SDLK_SPACE:
                {
                    input_type_.jump_ = 1;
                }
            
        }
    }
    else if(events.type == SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
            case SDLK_RIGHT:
                {
                    input_type_.right_ = 0;
                }
                break;
            case SDLK_LEFT:
                {
                    input_type_.left_ = 0;
                }
                break;
        }
    }

}

void MainObject::DoPlayer(Map& map_data)
{
    if(come_back_time == 0)
    {
        x_val_ = 0;
    y_val_ += GRAVITY_SPEED;

    if(y_val_ >= MAX_FALL_SPEED) {
        y_val_ = MAX_FALL_SPEED;
    }

    if(input_type_.right_ == 1)
    {
        x_val_ += MOVE_SPEED;
    }

    if(input_type_.left_ == 1)
    {
        x_val_ -= MOVE_SPEED;
    }

    if(input_type_.jump_ == 1)
    {
        if(on_ground_ == true)
        {
            y_val_ = - NHAY;
        }

        on_ground_ = false;
        input_type_.jump_ = 0 ;
    }

    CheckVacham(map_data);
    GhimMap(map_data);
    }

    if(come_back_time > 0)
    {
        come_back_time--;

        if(come_back_time == 0)
        {   
            on_ground_ = false; // de khi die thi player se roi trang thai jump
            x_pos_ -= 128;
            y_pos_ = 0;
            x_val_ = 0;
            y_val_ = 0;
        }
                   
    }
}

void MainObject::GhimMap(Map& map_data)
{
    map_data.start_x_ = x_pos_ - (SCREEN_WIDTH/2);
    if(map_data.start_x_ < 0)
    {
        map_data.start_x_ = 0;
    }
    else if(map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
    {
        map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
    }


}

void MainObject::CheckVacham(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

 // check theo chieu ngang
    int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_)/TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_-1)/TILE_SIZE;

    y1 = (y_pos_)/TILE_SIZE;
    y2 = (y_pos_ + height_min - 1)/TILE_SIZE;

    /*              x1,y1*************x2,y1
                    *                   *
                    *                   *
                    *                   *
                    *                   *
                    *                   *
                    *                   *
                    x1,y2**************x2,y2
    */

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x_val_ > 0) // nhan vat dang di chuyen
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

            if (val1 == STATE_MONEY || val2 == STATE_MONEY)
            {
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseMoney();
            }
            else
            {
                if (val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    x_pos_ = x2*TILE_SIZE;
                    x_pos_ -= width_frame_ + 1;
                    x_val_ = 0;
                }
            }
        }
        else if (x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if (val1 == STATE_MONEY || val2 == STATE_MONEY)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y2][x1] = 0;
                IncreaseMoney();
            }
            else
            {
                if (val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    x_pos_ = (x1 + 1)*TILE_SIZE;
                    x_val_ = 0;
                }
            }
            
        }
    }

  // check theo chieu doc
    int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;

    x1 = x_pos_ / TILE_SIZE;
    x2 = (x_pos_ + width_min) / TILE_SIZE;

    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ -1) / TILE_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (y_val_ > 0)
        {

            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if (val1 == STATE_MONEY || val2 == STATE_MONEY)
            {
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
                IncreaseMoney();
            }
            else
            {
                if (val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    y_pos_ = y2*TILE_SIZE;
                    y_pos_ -= (height_frame_+1);
                    y_val_ = 0;

                    on_ground_ = true;
                   
                }
            }
        }
        else if (y_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
            if (val1 == STATE_MONEY || val2 == STATE_MONEY)
            {
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
                IncreaseMoney();
            }
            else
            {
                if (val1 != BLANK_TILE || val2 != BLANK_TILE)
                {
                    y_pos_ = (y1 + 1)*TILE_SIZE;
                    y_val_ = 0;
                }
            }
            
        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if(x_pos_ < 0)    // di chuyen ra mep map 
    {
        x_pos_ = 0;
    }
    else if(x_pos_ + width_frame_ > map_data.max_x_)
    {
        x_pos_ = map_data.max_x_ - width_frame_ - 1;
    }

    //endgame
    if(y_pos_ > SCREEN_HEIGHT)
    {
        dead =true;
    }

    if(x_pos_ > 400 * 64 - 64)
    {
        set_win(true);
    }
 }

void MainObject::IncreaseMoney()
{
    money_count++;
}

void MainObject::reset_game()
{
    frame_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    money_count = 0;
}


 

 