#ifndef TEXTBOX
#define TEXTBOX

#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
using namespace std;

class App;

class Textbox: public Widget
{
	public:
		//Initializes variables
		Textbox(App *app, string str, int pos_x, int pos_y, int width, int height, Uint8 red, Uint8 green, Uint8 blue);

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );
		void setTextColor( Uint8 red, Uint8 green, Uint8 blue );

		//Renders texture at given point
		void render();

		void handleEvent( SDL_Event* e );

		int getWidth();
		int getHeight();

		void setText(char * str);
		void setFont(string path);
		void setFontSize(int size);
		void scrollDown();
		void scrollUp();

		Uint8 text_r;
		Uint8 text_g;
		Uint8 text_b;
		int text_y;
		int font_size;
		int line_height;
		string text;
		string font_path;
		TTF_Font *font;
		bool active;
		vector<string> lines;
		int cursor;
		int current_line;
		bool shift;
		SDL_Rect text_rect;
};

#endif // TEXTBOX