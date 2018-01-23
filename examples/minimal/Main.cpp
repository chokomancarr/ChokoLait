/*
Defines the platform we are using. One and only one of the following must be defined.
 PLATFORM_WIN
 PLATFORM_MAC
 PLATFORM_LNX
 PLATFORM_ADR
 PLATFORM_IOS
*/
#define PLATFORM_WIN

/*
Include the main header. Engine headers will be included automatically.
*/
#include "ChokoLait.h"

/*
Must be called if Assets (In this case, Font and Texture) are initialized before Init().
Can be omitted otherwise.
*/
CHOKOLAIT_INIT_VARS;

/*
Asset declarations.
*/
Font font ("D:\\arimo.ttf");
Texture tex ("D:\\cat.png");

/*
Function to be called during Paint() loop.
*/
void paintFunc();

/*
main entry point
*/
int main(int argc, char **argv) {
	/*
	Initializes the window.
	*/
	ChokoLait::Init(1024, 600);
	
	font.Align(ALIGN_TOPLEFT);
	
	/*
	alive() checks if the application has not exited. Use while(1) if the application should never exit until return.
	*/
	while (ChokoLait::alive()) {
		
		/*
		Update() must be called in the main loop. Function is optional.
		*/
		ChokoLait::Update(nullptr);
		/*
		Paint() draws any 3d/2d elements in the Scene. Function is optional.
		*/
		ChokoLait::Paint(&paintFunc);
	}
}

void paintFunc() {
	/*
	Draws a full-screen texture.
	*/
	UI::Texture(0, 0, Display::width, Display::height, &tex);
	/*
	Draws a label at (10, 10) with a font size of 20.
	*/
	UI::Label(10, 10, 20, "Hello, world!", &font, white());
	
	/*
	Draws a rotating square at the cursor's position.
	*/
	Engine::RotateUI(Time::time * 90, Vec2(Input::mousePos.x, Input::mousePos.y));
	Engine::DrawQuad(Input::mousePos.x - 20, Input::mousePos.y - 20, 40, 40, red());
	Engine::ResetUIMatrix();
}
