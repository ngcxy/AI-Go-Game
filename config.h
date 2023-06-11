#pragma once
#include "GUI.h"
#include "Graph.h"
#include "window.h"
#include "Game_window.h"
#include<windows.h>
#pragma comment(lib,"winmm.lib")

using namespace Graph_lib;

class Game_window;

class config : public Window {
public:
	config(Game_window* game);
private:
	Game_window* current;
	Canvas canvas;
	Image bg;
	Image easy;
	Image easy_pressed;
	Image medium;
	Image medium_pressed;
	Image hard;
	Image hard_pressed;
	Image se_open;
	Image se_open_pressed;
	Image se_close;
	Image se_close_pressed;
	Image bgm_open;
	Image bgm_open_pressed;
	Image bgm_close;
	Image bgm_close_pressed;
	void config_mouse_cb(const Mouse_event& evt);
};

config::config(Game_window* game)
	:Window{ {1050, 400},500, 350, "Config"},
	canvas{ {0, 0}, 500, 350 },
	bg{ {0, 0}, "./resources/config/bg.bmp" },
	easy{ {150, 90}, "./resources/config/easy1.bmp" },
	easy_pressed{ {150, 90}, "./resources/config/easy2.bmp" },
	medium{ {250, 90}, "./resources/config/medium1.bmp" },
	medium_pressed{ {250, 90}, "./resources/config/medium2.bmp" },
	hard{ {350, 90}, "./resources/config/hard1.bmp" },
	hard_pressed{ {350, 90}, "./resources/config/hard2.bmp"},
	se_open{ {200, 190}, "./resources/config/se_open1.bmp" },
	se_open_pressed{ {200, 190}, "./resources/config/se_open2.bmp" },
	se_close{ {300, 190}, "./resources/config/se_close1.bmp" },
	se_close_pressed{ {300, 190}, "./resources/config/se_close2.bmp" },
	bgm_open{ {200, 290}, "./resources/config/bgm_open1.bmp" },
	bgm_open_pressed{ {200, 290}, "./resources/config/bgm_open2.bmp" },
	bgm_close{ {300, 290}, "./resources/config/bgm_close1.bmp" },
	bgm_close_pressed{ {300, 290}, "./resources/config/bgm_close2.bmp" }
{
	current = game;
	attach(canvas);
	canvas.attach(bg);
	canvas.attach(easy);
	canvas.attach(medium);
	canvas.attach(hard);
	canvas.attach(se_close);
	canvas.attach(se_open);
	canvas.attach(bgm_open);
	canvas.attach(bgm_close);
	if (game->difficulty == AI_dif::easy) canvas.attach(easy_pressed);
	else if(game->difficulty == AI_dif::medium) canvas.attach(medium_pressed);
	else canvas.attach(hard_pressed);
	if (game->se) canvas.attach(se_open_pressed);
	else canvas.attach(se_close_pressed);
	if (game->bgm) canvas.attach(bgm_open_pressed);
	else canvas.attach(bgm_close_pressed);
	canvas.set_mouse_callback([this](const Mouse_event& evt) {config_mouse_cb(evt); });
}

void config::config_mouse_cb(const Mouse_event& evt)
{
	Point p;
	int x, y;
	if (evt.type == Mouse_event::move) {
		p = evt.pos;
		x = p.x;
		y = p.y;
		if (y > 90 && y < 135) {
			canvas.detach(easy_pressed);
			canvas.detach(medium_pressed);
			canvas.detach(hard_pressed);
			if (x > 155 && x < 245) canvas.attach(easy_pressed);
			else if (x > 255 && x < 345) canvas.attach(medium_pressed);
			else if (x > 355 && x < 445) canvas.attach(hard_pressed);
			else {
				if (current->difficulty == AI_dif::easy) canvas.attach(easy_pressed);
				else if (current->difficulty == AI_dif::medium) canvas.attach(medium_pressed);
				else canvas.attach(hard_pressed);
				redraw();
				return;
			}
		}
		else if (y > 190 && y < 240) {
			canvas.detach(se_open_pressed);
			canvas.detach(se_close_pressed);
			if (x > 200 && x < 250) canvas.attach(se_open_pressed);
			else if (x > 300 && x < 350) canvas.attach(se_close_pressed);
			else {
				if (current->se) canvas.attach(se_open_pressed);
				else canvas.attach(se_close_pressed);
				redraw();
				return;
			}
		}
		else if (y > 290 && y < 340) {
			canvas.detach(bgm_open_pressed);
			canvas.detach(bgm_close_pressed);
			if (x > 200 && x < 250) canvas.attach(bgm_open_pressed);
			else if (x > 300 && x < 350) canvas.attach(bgm_close_pressed);
			else {
				if (current->bgm) canvas.attach(bgm_open_pressed);
				else canvas.attach(bgm_close_pressed);
				redraw();
				return;
			}
		}
		else {
			canvas.detach(easy_pressed);
			canvas.detach(medium_pressed);
			canvas.detach(hard_pressed);
			canvas.detach(se_open_pressed);
			canvas.detach(se_close_pressed);
			canvas.detach(bgm_open_pressed);
			canvas.detach(bgm_close_pressed);
			if (current->difficulty == AI_dif::easy) canvas.attach(easy_pressed);
			else if (current->difficulty == AI_dif::medium) canvas.attach(medium_pressed);
			else canvas.attach(hard_pressed);
			if (current->se) canvas.attach(se_open_pressed);
			else canvas.attach(se_close_pressed);
			if (current->bgm) canvas.attach(bgm_open_pressed);
			else canvas.attach(bgm_close_pressed);
		}
	}
	else if (evt.type == Mouse_event::push) {
		p = evt.pos;
		x = p.x;
		y = p.y;
		if (y > 90 && y < 135) {
			if (x > 155 && x < 245) {
				current->difficulty = AI_dif::easy;
				canvas.attach(easy_pressed);
			}
			else if (x > 255 && x < 345) {
				current->difficulty = AI_dif::medium;
				canvas.attach(medium_pressed);
			}
			else if (x > 355 && x < 445) {
				current->difficulty = AI_dif::hard;
				canvas.attach(hard_pressed);
			}
			else {
				redraw();
				return;
			}
		}
		else if (y > 190 && y < 240) {
			if (x > 200 && x < 250) {
				current->se = true;
				canvas.attach(se_open_pressed);
			}
			else if (x > 300 && x < 350) {
				current->se = false;
				canvas.attach(se_close_pressed);
			}
			else {
				redraw();
				return;
			}
		}
		else if (y > 290 && y < 340) {
			if (x > 200 && x < 250) {
				current->bgm = true;
				canvas.attach(bgm_open_pressed);
				mciSendString(L"open .\\resources\\bgm.mp3 alias bgm", NULL, 0, NULL);
				mciSendString(L"play bgm repeat", NULL, 0, NULL);
			}
			else if (x > 300 && x < 350) {
				current->bgm = false;
				canvas.attach(bgm_close_pressed);
				mciSendString(L"open .\\resources\\bgm.mp3 alias bgm", NULL, 0, NULL);
				mciSendString(L"close bgm", NULL, 0, NULL);
			}
			else {
				redraw();
				return;
			}
		}
		else {
			redraw();
			return;
		}
	}
	redraw();
}