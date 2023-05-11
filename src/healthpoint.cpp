#include "healthpoint.h"

HealthPoint::HealthPoint()
{
    live_num = 0;
}

HealthPoint::~HealthPoint()
{

}

void HealthPoint::AddPos(const int& xPos)
{
    pos_list_.push_back(xPos);
}

void HealthPoint::Init(SDL_Renderer* screen)
{
    LoadImg("image//heart.png", screen);
    live_num = 3;
    if(pos_list_.size() > 0)
    {
        pos_list_.clear();
    }
    AddPos(40);
    AddPos(80);
    AddPos(120);
}

void HealthPoint::Show(SDL_Renderer* screen)
{
    for(int i = 0; i < pos_list_.size(); i++)
    {
        rect_.x = pos_list_.at(i);
        rect_.y = 10;
        Render(screen);
    }
}

void HealthPoint::Decrease()
{
    live_num--;
    pos_list_.pop_back();

}

void HealthPoint::Increase()
{
    // live_num = 3;
    for(int i = 0; i < 2; i++)
    {   
        if(pos_list_.size() < 3)
        {
            int last_pos = pos_list_.back();
            last_pos += 40;
            pos_list_.push_back(last_pos);
        }
    } 
}

