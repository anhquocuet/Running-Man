#ifndef HEALTH_POINT_H_
#define HEALTH_POINT_H_

#include "BaseObject.h"

class HealthPoint : public BaseObject
{
    public:
        HealthPoint();
        ~HealthPoint();
        void SetNum(const int& num) {live_num = num;}
        void AddPos(const int& xPos);
        void Show(SDL_Renderer* screen);
        void Init(SDL_Renderer* screen);

        void Increase();
        void Decrease();

    private:
        int live_num;
        std::vector<int> pos_list_;


};

#endif