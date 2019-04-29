#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "../app/app.h"
#include "widget.h"
#include "slider.h"
using namespace std;

Slider::Slider(App *app, int pos_x, int pos_y, int width, int height, Uint8 red, Uint8 green, Uint8 blue):Widget(app, pos_x, pos_y, width, height, red, green, blue)
{
	widget_type = "slider";
	image_circle_path = "images/slider-circle.png";
	image_line_path = "images/slider-line.png";
	image_circle = IMG_LoadTexture(app->renderer, image_circle_path.c_str());
	image_line = IMG_LoadTexture(app->renderer, image_line_path.c_str());
	circle_x = x;
	circle_size = 40;
	mouse_down = false;
}

void Slider::render() {
	if (visible == true) {
		if (parent != NULL) {
			Widget* p = (Widget*)parent;
			SDL_RenderSetClipRect(app->renderer, &p->rect);
		}
		SDL_Rect line_rect;
		line_rect.x = x;
		line_rect.y = y + (h / 2) - 1;
		line_rect.w = w;
		line_rect.h = 2;
	    SDL_RenderCopy(app->renderer, image_line, NULL, &line_rect);
	    SDL_Rect circle_rect;
		circle_rect.x = circle_x;
		circle_rect.y = y;
		circle_rect.w = circle_size;
		circle_rect.h = circle_size;
	    SDL_RenderCopy(app->renderer, image_circle, NULL, &circle_rect);
	    SDL_RenderSetClipRect(app->renderer, &rect);
	}
}

void Slider::handleEvent(SDL_Event* e) {
	if (e->type == SDL_MOUSEBUTTONDOWN) {
		mouse_down = true;
	}
	else if (e->type == SDL_MOUSEBUTTONUP) {
		mouse_down = false;
	}
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);
		if (mouse_x > x && mouse_x < x + w && mouse_y > y && mouse_y < y + h) {
			cb();
			if (mouse_down == true && mouse_x < x + w - circle_size) {
				circle_x = mouse_x;
			}
		}
	}
}

int Slider::getWidth()
{
	return w;
}

int Slider::getHeight()
{
	return h;
}

void Slider::close() {
	SDL_DestroyTexture(image_circle);
	SDL_DestroyTexture(image_line);
}