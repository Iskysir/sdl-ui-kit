#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "../app/app.h"
#include "widget.h"
#include "text.h"
using namespace std;

Text::Text(App *app, string str, int pos_x, int pos_y, int width, int height, Uint8 red, Uint8 green, Uint8 blue):Widget(app, pos_x, pos_y, width, height, red, green, blue)
{
	text = str;
	text_r = 0;
	text_g = 0;
	text_b = 0;
	font_path = "uikit/fonts/DejaVuSans.ttf";
	font_size = 24;
	font = TTF_OpenFont(font_path.c_str(), font_size);
	line_height = TTF_FontHeight(font);
	widget_type = "text";
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	surfaceMessage = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, rect.w);
}

void Text::setText(string str)
{
	text = str;
	SDL_FreeSurface(surfaceMessage);
	surfaceMessage = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, rect.w);
}

void Text::setTextColor(Uint8 red, Uint8 green, Uint8 blue )
{
	text_r = red;
	text_g = green;
	text_b = blue;
}

void Text::setFont(string path) {
	font_path = path;
	font = TTF_OpenFont(font_path.c_str(), font_size);
	if(!font) {
	    printf("TTF_OpenFont: %s\n", TTF_GetError());
	}
}

void Text::setFontSize(int size) {
	font_size = size;
	font = TTF_OpenFont(font_path.c_str(), font_size);
	if(!font) {
	    printf("TTF_OpenFont: %s\n", TTF_GetError());
	}
	line_height = TTF_FontHeight(font);

}

void Text::render()
{
	if (parent != NULL) {
		Widget* p = (Widget*)parent;
		SDL_Rect clip_rect;
		clip_rect.x = rect.x;
		clip_rect.y = (p->rect.y + rect.y > p->rect.y) ? p->rect.y : max(p->rect.y + rect.y, p->rect.y);
		clip_rect.w = rect.w;
		clip_rect.h = (clip_rect.y + rect.h < p->rect.h) ? clip_rect.y + rect.h : p->rect.h;
		SDL_RenderSetClipRect(app->renderer, &clip_rect);
	}
	if (percentage_active) {
		rect.x = (px * app->window_w) / 100;
		rect.y = (py * app->window_h) / 100;
		rect.w = (p_width * app->window_w) / 100;
		rect.h = (p_height * app->window_h) / 100;
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
		
	if (text != "") {

		SDL_Texture* message = SDL_CreateTextureFromSurface(app->renderer, surfaceMessage);

		int text_w, text_h;
		text_w = 0;
		text_h = 0;
		SDL_QueryTexture(message, NULL, NULL, &text_w, &text_h);
		SDL_Rect text_rect;
		text_rect.x = rect.x;
		text_rect.y = rect.y;
		text_rect.w = text_w;
		text_rect.h = text_h;

		if(SDL_RenderCopy(app->renderer, message, NULL, &text_rect) < 0) {
			printf("Text failed: %s\n", SDL_GetError());
		}
		
		
		SDL_DestroyTexture(message);
	}
	
	SDL_RenderSetClipRect(app->renderer, &app->rect);
}

int Text::getWidth()
{
	return w;
}

int Text::getHeight()
{
	return h;
}