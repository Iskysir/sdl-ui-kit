#ifndef CHECKBOX
#define CHECKBOX

#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

class App;

class Checkbox: public Widget {
	public:
		//Initializes variables
		Checkbox(App *app, int pos_x, int pos_y, int width, int height, Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		void handleEvent( SDL_Event* e );

		//Renders texture at given point
		void renderChecked();
		void renderUnchecked();
		void render();

		int getWidth();
		int getHeight();
		void close();

		void (*cb)();

		string image_unchecked_path;
		string image_checked_path;
		SDL_Texture* image_unchecked;
		SDL_Texture* image_checked;
		bool isChecked;
};

#endif // CHECKBOX