# Choko Lait

ChokoLait (pronounced choko-light) is an include-only game engine library for C++11.  
The full game engine (with editor UI) along with the source is available at [the project's github page](https://github.com/chokomancarr/ChokoEngine).  
Note that this Lait version will not contain certain functions otherwise contained in the full ChokoEngine.

ChokoLait currently supports Windows.

## Usage

A minimal usage example is as follows.

```main.cpp
#define PLATFORM_WIN
#include "ChokoLait.h"

Font* font;

void paintFunc();

int main(int argc, char **argv) {
	ChokoLait::Init(1024, 600);
	font = new Font("C:\\arial.ttf");
	font->Align(ALIGN_TOPLEFT);
	
	while (ChokoLait::alive()) {
		ChokoLait::Update();
		ChokoLait::Paint(&paintFunc);
	}
}

void paintFunc() {
	UI::Label(10, 10, 20, "Hello, world!", font, white());
}
```

## Downloads

[Link To Github Release](https://undefin.ed)

The current version is ???.

## Something is broken

  Open an issue in the github project page. Or, alternatively, tweet to me if you want it resolved quicker.  
  Feature suggestions are welcome on Twitter.

---

[Twitter](https://twitter.com/chokomancarr)