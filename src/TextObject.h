#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_

#include "BaseObject.h"

class TextObject
{
    public:
        TextObject();
        ~TextObject();

        enum TextColor
        {
            RED_TEXT = 0,
            WHITE_TEXT = 1,
            BLACK_TEXT = 2,
        };

        bool LoadFromFile(std::string path);
        bool LoadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
        void Free();

        void SetColor(Uint8 red, Uint8 green, Uint8 blue);
        void SetColor(int type);

        void RenderText(SDL_Renderer* screen,
                        int xp, int yp, 
                        SDL_Rect* clip = NULL, 
                        double angle = 0.0, 
                        SDL_Point* center = NULL, 
                        SDL_RendererFlip flip = SDL_FLIP_NONE);

        int GetWidth() const { return width_;}
        int GetHeight() const { return height_;}

        void SetText(const std::string& text) { str_val_ = text;}
        std::string GetText() const { return str_val_;}
        void Set_Rect(int x, int y)
        {
            rect_.x = x;
            rect_.y = y;
            rect_.h = height_;
            rect_.w = width_;
        }
        SDL_Rect Get_Rect() {return rect_;}


    private:
        std::string str_val_; // noi dung text
        SDL_Color text_color_;
        SDL_Texture* texture_;
        int width_;
        int height_;
        SDL_Rect rect_;
};


#endif