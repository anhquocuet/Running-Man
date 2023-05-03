#ifndef COMMONFUNC_H_INCLUDED_
#define COMMONFUNC_H_INCLUDED_

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

//    Screen

const int SCREEN_BPP = 32;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int FRAME_PER_SECOND = 26;


#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define STATE_MONEY 4
#define BLANK_TILE 0

typedef struct 
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
}Input;
typedef struct 
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
}Map;

// namespace SDLCommonFunc{
//     int getBestPoint();
//     void fixBestPoint(int newPoint);
// }


#endif 
