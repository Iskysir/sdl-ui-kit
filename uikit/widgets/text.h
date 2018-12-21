#ifndef TEXT
#define TEXT

#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

class App;

class Text: public Widget
{
	public:
		//Initializes variables
		Text(App *app, string str, int pos_x, int pos_y, int width, int height, Uint8 red, Uint8 green, Uint8 blue);

		//Set color modulation
		void setTextColor( Uint8 red, Uint8 green, Uint8 blue );

		//Renders texture at given point
		void render();

		int getWidth();
		int getHeight();

		void setText(string str);
		void setFont(string font_path);
		void setFontSize(int size);

		string text;
		TTF_Font *font;
		string font_path;
		int font_size;
		int line_height;
		Uint8 text_r;
		Uint8 text_g;
		Uint8 text_b;
		SDL_Surface* surfaceMessage;
		SDL_Color color;
};

#endif // TEXT