#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <boost/locale.hpp>
#include "../app/app.h"
#include "widget.h"
#include "textbox.h"
using namespace std;

Textbox::Textbox(App *app, string str, int pos_x, int pos_y, int width, int height, Uint8 red, Uint8 green, Uint8 blue):Widget(app, pos_x, pos_y, width, height, red, green, blue)
{
	text_r = 0;
	text_g = 0;
	text_b = 0;
	text_y = rect.y;
	font_size = 24;
	font_path = "uikit/fonts/DejaVuSans.ttf";
	font = TTF_OpenFont(font_path.c_str(), font_size);
	line_height = TTF_FontHeight(font);
	if(!font) {
	    printf("TTF_OpenFont: %s\n", TTF_GetError());
	}
	text = str;
	active = false;
	cursor = 0;
	current_line = 0;
	shift = false;
	widget_type = "textbox";
}

void Textbox::setTextColor( Uint8 red, Uint8 green, Uint8 blue )
{
	text_r = red;
	text_g = green;
	text_b = blue;
}

void Textbox::setFont(string path) {
	font_path = path;
	font = TTF_OpenFont(font_path.c_str(), font_size);
	if(!font) {
	    printf("TTF_OpenFont: %s\n", TTF_GetError());
	}
}

void Textbox::setFontSize(int size) {
	font_size = size;
	font = TTF_OpenFont(font_path.c_str(), font_size);
	if(!font) {
	    printf("TTF_OpenFont: %s\n", TTF_GetError());
	}
	line_height = TTF_FontHeight(font);

}

void Textbox::scrollDown() {
	text_y -= line_height;
}

void Textbox::scrollUp() {
	if (text_y < rect.y) {
		text_y += line_height;
	}
}

void Textbox::render()
{
	if (visible == true) {
		if (lines.size() < 1) {
			lines.push_back(text);
			cursor = (int)text.size();
			text_y = rect.y;
		}

		if (parent != NULL) {
			Widget* p = (Widget*)parent;
			SDL_Rect clip_rect;
			clip_rect.x = rect.x;
			clip_rect.y = (p->rect.y + text_y > p->rect.y) ? p->rect.y : max(p->rect.y + text_y, p->rect.y);
			clip_rect.w = rect.w;
			clip_rect.h = (clip_rect.y + rect.h < p->rect.h) ? clip_rect.y + rect.h : p->rect.h;
			SDL_RenderSetClipRect(app->renderer, &clip_rect);
		}
		else {
			SDL_Rect clip_rect;
			clip_rect.x = rect.x;
			clip_rect.y = rect.y;
			clip_rect.w = rect.w;
			clip_rect.h = rect.h;
			SDL_RenderSetClipRect(app->renderer, &clip_rect);
		}

		SDL_SetRenderDrawColor(app->renderer, r, g, b, 255);
		if (SDL_RenderFillRect(app->renderer, &rect) < 0) {
		    printf("Textbox failed: %s\n", SDL_GetError());
		}

		for (int i=0; i < (int)lines.size(); i++) {
		    
			
			SDL_Color color = {text_r,text_g,text_b, 255};
			
			SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, lines[i].c_str(), color);

			SDL_Texture* message = SDL_CreateTextureFromSurface(app->renderer, surfaceMessage);

			int text_w, text_h;
			text_w = 0;
			text_h = 0;
			TTF_SizeText(font,lines[i].c_str(),&text_w,&text_h);
			float ratio = (float)text_w / (float)text_h;
			SDL_Rect text_rect;
			text_rect.x = rect.x;
			text_rect.y = text_y + (line_height * (i));
			text_rect.h = line_height;
			text_rect.w = text_rect.h * ratio;
			if (text_rect.w > rect.w) {
				string ch = "";
				char last_ch = lines[current_line].back();
				ch.push_back(last_ch);
				lines[current_line].erase(cursor - 1, 1);
				cursor -= 1;
				lines.push_back("");
				current_line += 1;
				cursor = 0;
				lines[current_line].insert(cursor, ch);
				cursor += 1;
				if (line_height * (int)lines.size() > rect.h) {
					scrollDown();
				}
			}
			
			printf("x: %d\n", text_rect.x);
			printf("y: %d\n", text_rect.y);
			printf("w: %d\n", text_rect.w);
			printf("h: %d\n", text_rect.h);

			if(SDL_RenderCopy(app->renderer, message, NULL, &text_rect) < 0) {
				printf("Textbox failed: %s\n", SDL_GetError());
			}
			
			SDL_FreeSurface(surfaceMessage);
			SDL_DestroyTexture(message);

			if (current_line == i) {
				int w, h;
				string t = lines[i].substr(0, cursor);
				TTF_SizeText(font,t.c_str(),&w,&h);
				float t_ratio = (float)w / (float)h;
				SDL_Rect t_rect;
				t_rect.x = rect.x;
				t_rect.y = text_y + (line_height * (i));
				t_rect.h = line_height;
				t_rect.w = t_rect.h * t_ratio;
				SDL_SetRenderDrawColor(app->renderer, text_r, text_g, text_b, SDL_ALPHA_OPAQUE);
			    SDL_RenderDrawLine(app->renderer, t_rect.x + t_rect.w, t_rect.y, t_rect.x + t_rect.w, t_rect.y + t_rect.h);
			}
		}
		SDL_RenderSetClipRect(app->renderer, &app->rect);
	}
	
}

void Textbox::setText(char *str) {
	text = str;
}

void Textbox::handleEvent( SDL_Event* e ) {
	if( e->type == SDL_MOUSEBUTTONDOWN )
	{
		int mouse_x, mouse_y;
		SDL_GetMouseState( &mouse_x, &mouse_y );
		if (mouse_x > x && mouse_x < x + w && mouse_y > y && mouse_y < y + h) {
			active = !active;
		}
	}

	if (e->type == SDL_TEXTINPUT && active == true) {
		string input = boost::locale::conv::from_utf((string)e->text.text, "Latin1");
		lines[current_line].insert(cursor, input);
		cursor += 1;
	}

	if( e->type == SDL_KEYDOWN && active == true) {
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_LSHIFT]) {
		    shift = true;
		}
		else {
			shift = false;
		}

		switch (e->key.keysym.sym) {
			
			case SDLK_BACKSPACE:
				if (cursor > 0) {
					lines[current_line].erase(cursor - 1, 1);
					cursor -= 1;
				}
				else {
					if (current_line > 0) {
						lines.pop_back();
						current_line -= 1;
						cursor = lines[current_line].size();
						scrollUp();
					}
				}
				break;
			case SDLK_RETURN:
				lines.push_back("");
				current_line += 1;
				cursor = 0;
				break;
			case SDLK_LEFT:
				if (cursor > 0) {
					cursor -= 1;
				}
				else {
					if (current_line > 0) {
						current_line -= 1;
						cursor = lines[current_line].size();
					}
				}
				break;
			case SDLK_RIGHT:
				if ((unsigned int)cursor < lines[current_line].size()) {
					cursor += 1;
				}
				else {
					if ((unsigned int)current_line + 1 < lines.size()) {
						current_line += 1;
						cursor = 0;
					}
				}
				break;
			case SDLK_UP:
				if (current_line > 0) {
					current_line -= 1;
				}
				break;
			case SDLK_DOWN:
				if ((unsigned int)current_line + 1 < lines.size()) {
					current_line += 1;
				}
				break;
			default:
				break;

		}
		
	}
}
