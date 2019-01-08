class App;
#ifndef WIDGET
#define WIDGET
#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
using namespace std;
class Widget
{
	public:
		//Initializes variables
		Widget(App *app_p, int pos_x, int pos_y, int width, int height, Uint8 red, Uint8 green, Uint8 blue);

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		void handleEvent( SDL_Event* e );

		//Renders texture at given point
		virtual void render();

		void setGeometryByPercentage(float x, float y, float width, float height);
		int getWidth();
		int getHeight();
		void setBorderWidth(int width);
		void setBorderColor(Uint8 red, Uint8 green, Uint8 blue);
		void addWidget(void* widget);
		void renderChildren();
		void scrollUp();
		void scrollDown();

		void (*cb)();
		int x;
		int y;
		int w;
		int h;
		Uint8 r;
		Uint8 g;
		Uint8 b;
		Uint8 border_r;
		Uint8 border_g;
		Uint8 border_b;
		SDL_Rect rect;
		App *app;
		bool percentage_active;
		float px;
		float py;
		float p_width;
		float p_height;
		int borderWidth;
		string widget_type;
		void* parent;
		vector<void*> widgets;
		bool visible;
};

#endif// WIDGET