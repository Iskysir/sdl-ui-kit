#specify the compiler
CC=g++

# specify options for the compiler
CFLAGS=-Wall -g -std=c++11

LFLAGS=-lSDL2 -lSDL2_ttf -lSDL2_image -lboost_locale

all: main

main: main.o 
	$(CC) $(CFLAGS) -o main main.cpp uikit/app/app.cpp uikit/widgets/widget.cpp uikit/widgets/button.cpp uikit/widgets/text.cpp uikit/widgets/textbox.cpp uikit/widgets/image.cpp uikit/widgets/checkbox.cpp uikit/widgets/slider.cpp $(LFLAGS)

clean:
	rm -rf *o main
	
