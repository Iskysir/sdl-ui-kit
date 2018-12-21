#ifndef IMAGE
#define IMAGE

#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

class App;

class Image: public Widget {
	public:
		//Initializes variables
		Image(App *app, string image_path, int pos_x, int pos_y, int width, int height, Uint8 red = 255, Uint8 green = 255, Uint8 blue = 255);

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		void handleEvent( SDL_Event* e );

		//Renders texture at given point
		void render();

		int getWidth();
		int getHeight();
		void close();

		void (*cb)();

		string path;
		SDL_Texture* image;
};

#endif // IMAGE