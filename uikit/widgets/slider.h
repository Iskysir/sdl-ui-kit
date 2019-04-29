#ifndef SLIDER
#define SLIDER

#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

class App;

class Slider: public Widget {
	public:
		//Initializes variables
		Slider(App *app, int pos_x, int pos_y, int width, int height, Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);

		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		void handleEvent(SDL_Event* e);

		//Renders texture at given point
		void render();

		int getWidth();
		int getHeight();
		void close();

		void (*cb)();

		string image_circle_path;
		string image_line_path;
		SDL_Texture* image_circle;
		SDL_Texture* image_line;
		int circle_x;
		int circle_size;
		bool mouse_down;
};

#endif // SLIDER