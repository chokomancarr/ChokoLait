#define PLATFORM_WIN
#include "ChokoLait.h"
#include <mutex>

Font* font;
Texture* tex;

void paintFunc();

std::mutex mutex;

std::vector<std::string> ports;
bool connected = false;
std::thread* readthread;

string serialdata;

float posx, posy, rot;

float showx1 = 0, showx2 = 1000, showy1 = 0, showy2 = 1000;

int main(int argc, char **argv) {
	string ppath = argv[0];
	string path = ppath.substr(0, ppath.find_last_of('\\') + 1);

	ChokoLait::Init(1024, 600);

	font = new Font(path + "arimo.ttf");
	font->Align(ALIGN_TOPLEFT);
	tex = new Texture(path + "bg.png");

	ports = SerialPort::GetNames();

	while (ChokoLait::alive()) {
		std::lock_guard<std::mutex> lock(mutex);
		ChokoLait::Update();
		ChokoLait::Paint(&paintFunc);
	}
}

void readFunc() {
	char* data = new char[2]{0,0};
	while (connected) {
		if (SerialPort::Read((byte*)data, 1)) {
			std::lock_guard<std::mutex> lock(mutex);
			serialdata += string(data);
		}
	}
}

void paintFunc() {
	UI::Texture(0, 0, Display::width, Display::height, tex);

	Engine::DrawQuad(Display::height*0.05f, Display::height*0.05f, Display::height*0.9f, Display::height*0.9f, connected ? Vec4(0.1f, 0.3f, 0.1f, 0.7f): white(0.7f, 0.2f));

	if (!connected) {
		UI::Label(Display::height*0.1f, Display::height*0.07f, 16, to_string(ports.size()) + " ports available:", font, white());
		uint a = 0;
		for (auto k : ports) {
			if (Engine::Button(Display::height*0.1f, Display::height*0.07f + 30 + 30 * (a++), Display::height*0.3f, 25, white(0.7f, 0.7f), k, 14, font, black()) == MOUSE_RELEASE) {
				connected = SerialPort::Connect(k);
				if (connected) {
					readthread = new std::thread(readFunc);
				}
			}
		}

		if (Engine::Button(Display::height, Display::height*0.05f, 200, 30, white(0.7f, 0.7f), "Refresh", 20, font, black(), true) == MOUSE_RELEASE) {
			ports = SerialPort::GetNames();
		}
	}
	else {

		int pn;
		string line = "";
		do
		{
			pn = serialdata.find('\n');
			if (pn == -1) break;
			line = serialdata.substr(0, pn);
			serialdata = serialdata.substr(pn + 1);
		} while (pn > -1);

		if (line != "")
		{
			auto s = string_split(line, ' ');
			if (s.size() != 3) return;
			posx = TryParse(s[0], 0.0f);
			posy = TryParse(s[1], 0.0f);
			rot = TryParse(s[2], 0.0f);
		}

		if (Engine::Button(Display::height, Display::height*0.95f - 30, 200, 30, white(0.7f, 0.7f), "Disconnect", 20, font, black(), true) == MOUSE_RELEASE) {
			SerialPort::Disconnect();
			connected = false;
		}

		UI::Label(Display::height*1.1f, Display::height*0.7f, 16, "Position X : " + to_string(posx), font);
		UI::Label(Display::height*1.1f, Display::height*0.7f + 20, 16, "Position Y : " + to_string(posy), font);
		UI::Label(Display::height*1.1f, Display::height*0.7f + 40, 16, "Rotation   : " + to_string(rot), font);

		UI::Label(Display::height, Display::height*0.05f, 20, "X", font);
		string res = UI::EditText(Display::height + 30, Display::height*0.05f, 150, 30, 20, white(0.7f, 0.7f), to_string(showx1), font, true);
		showx1 = TryParse(res, 0.0f);
		res = UI::EditText(Display::height + 190, Display::height*0.05f, 150, 30, 20, white(0.7f, 0.7f), to_string(showx2), font, true);
		showx2 = TryParse(res, 0.0f);

		UI::Label(Display::height, Display::height*0.05f + 40, 20, "Y", font);
		res = UI::EditText(Display::height + 30, Display::height*0.05f + 40, 150, 30, 20, white(0.7f, 0.7f), to_string(showy1), font, true);
		showy1 = TryParse(res, 0.0f);
		res = UI::EditText(Display::height + 190, Display::height*0.05f + 40, 150, 30, 20, white(0.7f, 0.7f), to_string(showy2), font, true);
		showy2 = TryParse(res, 0.0f);

		Vec2 pos(Display::height*Lerp(0.05f, 0.95f, InverseLerp(showx1, showx2, posx)), Display::height*Lerp(0.05f, 0.95f, InverseLerp(showy2, showy1, posy)));
		Engine::RotateUI(rot, pos);
		Engine::DrawQuad(pos.x - 15, pos.y - 15, 30, 30, white(1, 0.6f));
		Engine::DrawLine(pos + Vec2(0, 5), pos + Vec2(0, 25), white(), 3);
		Engine::ResetUIMatrix();
	}
}
