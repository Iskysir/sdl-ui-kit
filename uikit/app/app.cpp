#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "app.h"
#include "../widgets/widget.h"
#include "../widgets/text.h"
#include "../widgets/textbox.h"
#include "../widgets/button.h"
#include "../widgets/image.h"
#include "../widgets/checkbox.h"
#include "../widgets/slider.h"
using namespace std;

void App::init(string window_title, int width, int height, bool maximize) {
	title = window_title;
	window_w = width;
	window_h = height;
	rect.x = 0;
	rect.y = 0;
	rect.w = window_w;
	rect.h = window_h;
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_w, window_h, SDL_WINDOW_RESIZABLE );
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	quit = false;
	start_maximized = maximize;

	if (start_maximized == true) {
		SDL_MaximizeWindow(window);
	}
	
	screen_surface = SDL_GetWindowSurface(window);

	if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    SDL_RenderSetClipRect(renderer, &rect);
    SDL_StartTextInput();
    IMG_Init(IMG_INIT_PNG);
}

void App::start() {
	while (!quit) {

		//Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }

            switch( e.window.event )
	        {
	            //Get new dimensions and repaint on window size change
	            case SDL_WINDOWEVENT_SIZE_CHANGED:
		            SDL_GetWindowSize(window, &window_w, &window_h);
		            rect.x = 0;
					rect.y = 0;
					rect.w = window_w;
					rect.h = window_h;
					break;
	        }

		    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
		    {
		        int x, y;
		        SDL_GetMouseState( &x, &y );
		    }

		    for (unsigned int i=0; i < widgets.size(); i++) {
				Widget *w = (Widget*)widgets[i];

				if (w->widget_type == "widget") {
					w->handleEvent(&e);
				}
				if (w->widget_type == "button") {
					Button *b = (Button*)widgets[i];
					b->handleEvent(&e);
				}
				if (w->widget_type == "text") {
					Text *t = (Text*)widgets[i];
					t->handleEvent(&e);
				}
				if (w->widget_type == "textbox") {
					Textbox *tb = (Textbox*)widgets[i];
					tb->handleEvent(&e);
				}
				if (w->widget_type == "image") {
					Image *im = (Image*)widgets[i];
					im->handleEvent(&e);
				}
				if (w->widget_type == "checkbox") {
					Checkbox *chk = (Checkbox*)widgets[i];
					chk->handleEvent(&e);
				}
				if (w->widget_type == "slider") {
					Slider *sl = (Slider*)widgets[i];
					sl->handleEvent(&e);
				}

			}
	        
        }

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		render();

		/*
		for (unsigned int i=0; i < widget_ids.size(); i++) {
		    if (widget_ids[i][0] == 0) {
	    		widgets[widget_ids[i][1]].render();
	    	}
	    	else if (widget_ids[i][0] == 1) {
	    		buttons[widget_ids[i][1]].render();
	    	}
	    	else if (widget_ids[i][0] == 2) {
	    		texts[widget_ids[i][1]].render();
	    	}
	    	else if (widget_ids[i][0] == 3) {
	    		textboxes[widget_ids[i][1]].render();
	    	}
	    	else if (widget_ids[i][0] == 4) {
	    		images[widget_ids[i][1]].render();
	    	}
		}
		*/

		SDL_RenderPresent(renderer);
    }

    close();
}

void App::setWindowSize(int width, int height) {
	SDL_SetWindowSize(window, width, height);
}

void App::setTitle(string window_title) {
	title = window_title;
	SDL_SetWindowTitle(window, title.c_str());

}

void App::addWidget(void * widget) {
	Widget *w = (Widget*)widget;
	w->parent = NULL;
	widgets.push_back(widget);
}

void App::addButton(Button button) {
	std::vector<int> b;
	b.push_back(1);
	b.push_back(buttons.size());
	widget_ids.push_back(b);
	buttons.push_back(button);
}

void App::addText(Text text) {
	std::vector<int> t;
	t.push_back(2);
	t.push_back(texts.size());
	widget_ids.push_back(t);
	texts.push_back(text);
}

void App::addTextbox(Textbox textbox) {
	std::vector<int> tb;
	tb.push_back(3);
	tb.push_back(textboxes.size());
	widget_ids.push_back(tb);
	textboxes.push_back(textbox);
}

void App::addImage(Image image) {
	std::vector<int> im;
	im.push_back(4);
	im.push_back(images.size());
	widget_ids.push_back(im);
	images.push_back(image);
}

void App::setBackgroundColor( Uint8 red, Uint8 green, Uint8 blue )
{
	r = red;
	g = green;
	b = blue;
}

void App::render()
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	if (SDL_RenderFillRect(renderer, &rect) < 0) {
	    printf("Button failed: %s\n", SDL_GetError());
	}

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
		else if (w->widget_type == "checkbox") {
			Checkbox *chk = (Checkbox*)widgets[i];
			chk->render();
		}
		else if (w->widget_type == "slider") {
			Slider *sl = (Slider*)widgets[i];
			sl->render();
		}

	}
}

int App::getWidth()
{
	return w;
}

int App::getHeight()
{
	return h;
}

void App::close() {
	for (unsigned int i=0; i < images.size(); i++) {
		images[i].close();
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
}
