#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "../app/app.h"
#include "widget.h"
#include "image.h"
using namespace std;

Image::Image(App *app, string image_path, int pos_x, int pos_y, int width, int height, Uint8 red, Uint8 green, Uint8 blue):Widget(app, pos_x, pos_y, width, height, red, green, blue)
{
	path = image_path;
	widget_type = "image";
	image = IMG_LoadTexture(app->renderer, path.c_str());
    
}

void Image::render() {
	if (parent != NULL) {
		Widget* p = (Widget*)parent;
		SDL_RenderSetClipRect(app->renderer, &p->rect);
	}
    SDL_RenderCopy(app->renderer, image, NULL, &rect);
    SDL_RenderSetClipRect(app->renderer, &app->rect);
}

void Image::handleEvent( SDL_Event* e )
{
	if( e->type == SDL_MOUSEBUTTONDOWN )
	{
		int mouse_x, mouse_y;
		SDL_GetMouseState( &mouse_x, &mouse_y );
		if (mouse_x > x && mouse_x < x + w && mouse_y > y && mouse_y < y + h) {
			cb();
		}
	}
}

int Image::getWidth()
{
	return w;
}

int Image::getHeight()
{
	return h;
}

void Image::close() {
	SDL_DestroyTexture(image);
}