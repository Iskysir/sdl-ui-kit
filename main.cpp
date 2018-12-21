#include <stdio.h>
#include "uikit/app/app.h"
#include "uikit/widgets/widget.h"
#include "uikit/widgets/button.h"
#include "uikit/widgets/text.h"
#include "uikit/widgets/textbox.h"
#include "uikit/widgets/image.h"
#include <vector>

void on_press_button1() {
	printf("Button1 pressed\n");
};

void on_press_button2() {
	printf("Button2 pressed\n");
}

void on_press_button3() {
	printf("Button3 pressed\n");
}

int main( int argc, char* args[] ) {
	App app = App();
	app.init("Title", 640, 480, false);
	app.setBackgroundColor(200, 200, 200);

	Image image1 = Image(&app, "images/flower.png", 0, 0, 30, 30);
	app.addWidget(&image1);

	Button button1 = Button(&app, 280, 0, 120, 30, 75, 124, 162);
	button1.cb = on_press_button1;
	button1.setTextColor(255,255,255);
	button1.setText("Button1");
	button1.setBorderWidth(2);
	button1.setBorderColor(4, 46, 79);
	app.addWidget(&button1);
	
	Button button2 = Button(&app, 400, 0, 120, 30, 75, 124, 162);
	button2.cb = on_press_button2;
	button2.setTextColor(255,255,255);
	button2.setText("Button2");
	button2.setBorderWidth(2);
	button2.setBorderColor(4, 46, 79);
	app.addWidget(&button2);

	Button button3 = Button(&app, 520, 0, 120, 30, 75, 124, 162);
	button3.cb = on_press_button3;
	button3.setTextColor(255,255,255);
	button3.setText("Button3");
	button3.setBorderWidth(2);
	button3.setBorderColor(4, 46, 79);
	app.addWidget(&button3);

	Widget widget1 = Widget(&app, 0, 30, 640, 250, 23, 83, 128);

	app.addWidget(&widget1);

	Text text1 = Text(&app, "text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text text ", 10, 10, 620, 230, 4, 46, 79);
	widget1.addWidget(&text1);
	Textbox textbox1 = Textbox(&app, "Write here", 0, 280, 640, 210, 255, 255, 255);
	textbox1.setTextColor(0,0,0);
	app.addWidget(&textbox1);

	app.start();
	return 0;
}
