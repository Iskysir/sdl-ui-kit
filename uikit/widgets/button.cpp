#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "../app/app.h"
#include "widget.h"
#include "button.h"
using namespace std;

Button::Button(App *app, int pos_x, int pos_y, int width, int height, Uint8 red, Uint8 green, Uint8 blue):Widget(app, pos_x, pos_y, width, height, red, green, blue)
{

	text_r = 255;
	text_g = 255;
	text_b = 255;
	text = "Button";
	font_path = "uikit/fonts/DejaVuSans.ttf";
	font_size = 24;
	font = TTF_OpenFont(font_path.c_str(), font_size);
	line_height = TTF_FontHeight(font);
	widget_type = "button";
}

void Button::setTextColor( Uint8 red, Uint8 green, Uint8 blue )
{
	text_r = red;
	text_g = green;
	text_b = blue;
}

void Button::setFont(string path) {
	font_path = path;
	font = TTF_OpenFont(font_path.c_str(), font_size);
	if(!font) {
	    printf("TTF_OpenFont: %s\n", TTF_GetError());
	}
}

void Button::setFontSize(int size) {
	font_size = size;
	font = TTF_OpenFont(font_path.c_str(), font_size);
	if(!font) {
	    printf("TTF_OpenFont: %s\n", TTF_GetError());
	}
	line_height = TTF_FontHeight(font);

}

void Button::render()
{
	if (visible == true) {
		if (parent != NULL) {
			Widget* p = (Widget*)parent;
			SDL_RenderSetClipRect(app->renderer, &p->rect);
		}
		SDL_SetRenderDrawColor(app->renderer, border_r, border_g, border_b, 255);
		if (SDL_RenderFillRect(app->renderer, &rect) < 0) {
		    printf("Widget failed: %s\n", SDL_GetError());
		}
		SDL_Rect inner_rect;
		inner_rect.x = rect.x + borderWidth;
		inner_rect.y = rect.y + borderWidth;
		inner_rect.w = rect.w - (borderWidth * 2);
		inner_rect.h = rect.h - (borderWidth * 2);
		SDL_SetRenderDrawColor(app->renderer, r, g, b, 255);
		if (SDL_RenderFillRect(app->renderer, &inner_rect) < 0) {
		    printf("Widget failed: %s\n", SDL_GetError());
		}
		
		SDL_Color color = {text_r, text_g, text_b,0};
		
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text.c_str(), color);

		SDL_Texture* message = SDL_CreateTextureFromSurface(app->renderer, surfaceMessage);

		int text_w, text_h;
		text_w = 0;
		text_h = 0;
		TTF_SizeText(font, text.c_str(),&text_w,&text_h);
		float ratio = (float)text_w / (float)text_h;
		SDL_Rect text_rect;
		text_rect.x = rect.x;
		text_rect.y = rect.y;
		text_rect.h = line_height;
		text_rect.w = text_rect.h * ratio;
		
		SDL_RenderSetClipRect(app->renderer, &rect);
		if(SDL_RenderCopy(app->renderer, message, NULL, &text_rect) < 0) {
			printf("Textbox failed: %s\n", SDL_GetError());
		}
		
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(message);
		SDL_RenderSetClipRect(app->renderer, &app->rect);
	}
}

void Button::handleEvent( SDL_Event* e )
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

int Button::getWidth()
{
	return w;
}

int Button::getHeight()
{
	return h;
}

void Button::setText(string str) {
	text = str;
}