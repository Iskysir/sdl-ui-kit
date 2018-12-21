#ifndef BUTTON
#define BUTTON

#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

class App;

class Button: public Widget {
	public:
		//Initializes variables
		Button(App *app, int pos_x, int pos_y, int width, int height, Uint8 red, Uint8 green, Uint8 blue);

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		void handleEvent( SDL_Event* e );

		//Renders texture at given point
		virtual void render();

		int getWidth();
		int getHeight();
		void setTextColor(Uint8 red, Uint8 green, Uint8 blue);
		void setText(string str);
		void setFont(string font_path);
		void setFontSize(int size);

		void (*cb)();

		Uint8 text_r;
		Uint8 text_g;
		Uint8 text_b;
		string text;
		TTF_Font *font;
		string font_path;
		int font_size;
		int line_height;
		
};

#endif // BUTTON