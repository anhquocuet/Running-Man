
#ifndef G_MAP_H_
#define G_MAP_H_

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILES 20
class TileMat : public BaseObject
{
    public:
        TileMat() {;} 
        ~TileMat() {;}

};

class GameMap
{
    public:
        GameMap() {;}
        ~GameMap() {;}

    void LoadMap(char* name); // load file text
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() {return game_map_;};
    void SetMap(Map& map_data) {game_map_ = map_data;}
    private:
        Map game_map_;
        TileMat tile_mat[MAX_TILES];
};

#endif