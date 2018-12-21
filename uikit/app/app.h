class Widget;
class Text;
class Button;
class Textbox;
class Image;
#ifndef APP
#define APP

#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
using namespace std;

class App
{
	public:
		void init(string window_title, int width, int height, bool maximize);
		void start();

		//Set color modulation
		void setBackgroundColor( Uint8 red, Uint8 green, Uint8 blue );
		void setWindowSize(int width, int height);
		void setTitle(string window_title);
		void addWidget(void* widget);
		void addButton(Button button);
		void addText(Text text);
		void addTextbox(Textbox textbox);
		void addImage(Image image);

		void close();

		//Renders texture at given point
		void render();

		int getWidth();
		int getHeight();

		void (*cb)();
		int w;
		int h;
		Uint8 r;
		Uint8 g;
		Uint8 b;
		SDL_Rect rect;
		bool quit;
		SDL_Event e;
		std::vector<void*> widgets;
		std::vector<Button> buttons;
		std::vector<Text> texts;
		std::vector<Textbox> textboxes;
		std::vector<Image> images;
		std::vector<std::vector<int> > widget_ids;
		int window_w;
		int window_h;
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Surface *screen_surface;
		bool start_maximized;
		string title;
};

#endif// APP