
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define MOVE_SPEED 8
#define NHAY 18

#define PLAYER_FRAME_NUM 11


class MainObject : public BaseObject
{
    public:
        MainObject();
        ~MainObject();

        enum WalkType
        {
            WALK_RIGHT = 0,
            WALK_LEFT = 1,
        };

        bool LoadImg(std::string path, SDL_Renderer* screen);
        void Show(SDL_Renderer* des);
        void HandelInputAction(SDL_Event events, SDL_Renderer* screen);
        void set_clips();
        void DoPlayer(Map& map_data);
        void CheckVacham(Map& map_data);
        void SetMapXY( const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y; }
        void GhimMap(Map& map_data);

        SDL_Rect GetRectFrame();
        void IncreaseMoney();

        void set_come_back_time(const int& cb_time) { come_back_time = cb_time;}
        int GetMoneyCount() const { return money_count;}

        bool get_dead() {return dead;}
        void set_dead(bool x) {dead = x;}

        bool get_win() {return win;}
        bool set_win(bool x) {win = x;}

        void reset_game();
    private:
        float x_val_;
        float y_val_;

        float x_pos_;
        float y_pos_;
        
        int width_frame_;
        int height_frame_;

        SDL_Rect frame_clip_[PLAYER_FRAME_NUM];
        Input input_type_;                // save trang thai nhan vat: up down right left
        int frame_;
        int status_; // cho biet nhan vat dang right hay left
        bool on_ground_;
        int map_x_;
        int map_y_;

        int come_back_time;
        int money_count;

        bool dead;
        bool win;
};

#endif