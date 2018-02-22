# Choko Lait

ChokoLait (pronounced choko-light) is an include-only game engine library for C++11.  
The full game engine (with editor UI) along with the source is available at [the project's github page](https://github.com/chokomancarr/ChokoEngine).  
Note that this Lait version will not contain certain functions otherwise contained in the full ChokoEngine.

ChokoLait currently supports Windows, Android and Linux.

## Usage

A minimal usage example is as follows.

```main.cpp
#define PLATFORM_WIN
#include "ChokoLait.h"

Font* font;

void paintFunc() {
	UI::Label(10, 10, 20, "Hello, world!", font, white());
}

int main() {
	ChokoLait::Init(1024, 600);
	font = new Font(IO::path + "/arial.ttf");
	font->Align(ALIGN_TOPLEFT);
	
	while (ChokoLait::alive()) {
		ChokoLait::Update();
		ChokoLait::Paint(&paintFunc);
	}
}
```

## Downloads

[Link To Github Release](https://undefin.ed)

The current version is ???.

## Something is broken

  Open an issue in the github project page.
  Feature suggestions/complaints/personal attacks are welcome on Twitter.

---

[Twitter](https://twitter.com/chokomancarr)