#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "../app/app.h"
#include "widget.h"
#include "checkbox.h"
using namespace std;

Checkbox::Checkbox(App *app, int pos_x, int pos_y, int width, int height, Uint8 red, Uint8 green, Uint8 blue):Widget(app, pos_x, pos_y, width, height, red, green, blue)
{
	widget_type = "checkbox";
	image_unchecked_path = "images/checkbox-unchecked.png";
	image_checked_path = "images/checkbox-checked.png";
	image_unchecked = IMG_LoadTexture(app->renderer, image_unchecked_path.c_str());
	image_checked = IMG_LoadTexture(app->renderer, image_checked_path.c_str());
	isChecked = false;
}

void Checkbox::render() {
	if (isChecked == false) {
		renderUnchecked();
	}
	else {
		renderChecked();
	}
}

void Checkbox::renderUnchecked() {
	if (visible == true) {
		if (parent != NULL) {
			Widget* p = (Widget*)parent;
			SDL_RenderSetClipRect(app->renderer, &p->rect);
		}
		printf("y2");
	    SDL_RenderCopy(app->renderer, image_unchecked, NULL, &rect);
	    SDL_RenderSetClipRect(app->renderer, &app->rect);
	}
}

void Checkbox::renderChecked() {
	if (visible == true) {
		if (parent != NULL) {
			Widget* p = (Widget*)parent;
			SDL_RenderSetClipRect(app->renderer, &p->rect);
		}
	    SDL_RenderCopy(app->renderer, image_checked, NULL, &rect);
	    SDL_RenderSetClipRect(app->renderer, &app->rect);
	}
}

void Checkbox::handleEvent(SDL_Event* e) {
	printf("x1\n");
	if (e->type == SDL_MOUSEBUTTONDOWN) {
		int mouse_x, mouse_y;
		SDL_GetMouseState(&mouse_x, &mouse_y);
		printf("x2");
		if (mouse_x > x && mouse_x < x + w && mouse_y > y && mouse_y < y + h) {
			printf("x3\n");
			printf("%p", &cb);
			if (&cb != NULL) {
				cb();
			}
			printf("x4\n");
			if (isChecked == false) {
				isChecked = true;
			}
			else {
				isChecked = false;
			}
			printf("x5\n");
		}

	}
}

int Checkbox::getWidth()
{
	return w;
}

int Checkbox::getHeight()
{
	return h;
}

void Checkbox::close() {
	SDL_DestroyTexture(image_checked);
	SDL_DestroyTexture(image_unchecked);
}