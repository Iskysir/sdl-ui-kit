#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "widget.h"
#include "../app/app.h"
#include "../widgets/text.h"
#include "../widgets/textbox.h"
#include "../widgets/button.h"
#include "../widgets/image.h"


Widget::Widget(App *app_p, int pos_x, int pos_y, int width, int height, Uint8 red, Uint8 green, Uint8 blue) {
	x = pos_x;
	y = pos_y;
	w = width;
	h = height;
	r = red;
	g = green;
	b = blue;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	app = app_p;
	px = 0;
	py = 0;
	p_width = 0;
	p_height = 0;
	percentage_active = false;
	borderWidth = 0;
	border_r = 0;
	border_g = 0;
	border_b = 0;
	widget_type = "widget";
	visible = true;
}

void Widget::addWidget(void * widget) {
	Widget *w = (Widget*)widget;
	w->parent = this;
	w->rect.x += rect.x;
	w->rect.y += rect.y;
	widgets.push_back(widget);
}

void Widget::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	r = red;
	g = green;
	b = blue;
}

void Widget::setBorderColor(Uint8 red, Uint8 green, Uint8 blue) {
	border_r = red;
	border_g = green;
	border_b = blue;
}

void Widget::setBorderWidth(int width) {
	borderWidth = width;
}

void Widget::render()
{
	if (visible == true) {
		if (parent != NULL) {
			Widget* p = (Widget*)parent;
			SDL_RenderSetClipRect(app->renderer, &p->rect);
		}
		if (percentage_active) {
			x = (px * app->window_w) / 100;
			y = (py * app->window_h) / 100;
			w = (p_width * app->window_w) / 100;
			h = (p_height * app->window_h) / 100;
			rect.x = x;
			rect.y = y;
			rect.w = w;
			rect.h = h;
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
		SDL_RenderSetClipRect(app->renderer, &app->rect);
		renderChildren();
	}
}

void Widget::renderChildren()
{
	for (unsigned int i=0; i < widgets.size(); i++) {
		Widget *w = (Widget*)widgets[i];

		if (w->widget_type == "widget") {
			w->render();
		}
		else if (w->widget_type == "button") {
			Button *b = (Button*)widgets[i];
			b->render();
		}
		else if (w->widget_type == "text") {
			Text *t = (Text*)widgets[i];
			t->render();
		}
		else if (w->widget_type == "textbox") {
			Textbox *tb = (Textbox*)widgets[i];
			tb->render();
		}
		else if (w->widget_type == "image") {
			Image *im = (Image*)widgets[i];
			im->render();
		}

	}
}

void Widget::setGeometryByPercentage(float x, float y, float width, float height)
{
	percentage_active = true;
	px = x;
	py = y;
	p_width = width;
	p_height = height;
}

void Widget::handleEvent( SDL_Event* e )
{
	if( e->type == SDL_MOUSEBUTTONDOWN )
	{
		int mouse_x, mouse_y;
		SDL_GetMouseState( &mouse_x, &mouse_y );
		if (mouse_x > x && mouse_x < x + w && mouse_y > y && mouse_y < y + h) {
			printf("click event\n");
		}
	}

	if(e->type == SDL_MOUSEWHEEL) {
		int mouse_x, mouse_y;
		SDL_GetMouseState( &mouse_x, &mouse_y );
		if (mouse_x > x && mouse_x < x + w && mouse_y > y && mouse_y < y + h) {
			if(e->wheel.y > 0) {
				scrollUp();
			}
			else if(e->wheel.y < 0) {
				scrollDown();
			}
		}
	}

	for (unsigned int i=0; i < widgets.size(); i++) {
		Widget *w = (Widget*)widgets[i];

		if (w->widget_type == "widget") {
			w->handleEvent(e);
		}
		else if (w->widget_type == "button") {
			Button *b = (Button*)widgets[i];
			b->handleEvent(e);
		}
		else if (w->widget_type == "text") {
			Text *t = (Text*)widgets[i];
			t->handleEvent(e);
		}
		else if (w->widget_type == "textbox") {
			Textbox *tb = (Textbox*)widgets[i];
			tb->handleEvent(e);
		}
		else if (w->widget_type == "image") {
			Image *im = (Image*)widgets[i];
			im->handleEvent(e);
		}

	}
}

void Widget::scrollDown() {
	for (unsigned int i=0; i < widgets.size(); i++) {
		Widget *w = (Widget*)widgets[i];
		w->rect.y -= 5;
	}
}

void Widget::scrollUp() {
	for (unsigned int i=0; i < widgets.size(); i++) {
		Widget *w = (Widget*)widgets[i];
		w->rect.y += 5;
	}
}

int Widget::getWidth()
{
	return w;
}

int Widget::getHeight()
{
	return h;
}
