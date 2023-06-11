#pragma once
#include <vector>
#include "AI.h"
using namespace Graph_lib;

enum class AI_dif {
	easy = 1, medium = 2, hard = 3
};

class Game_window : public Window {
	friend class config;
public:
	Game_window();

private:
	bool se;
	bool bgm;
	AI_dif difficulty;
	AI* ai;
	int ai_opponent; //pve:1, pvp:0
	int last_move_x, last_move_y;
	int last_crossing_x, last_crossing_y;
	int player;	//black:0, white:1
	int is_judging;
	int is_doublechecking;
	int checkmode; //0:yes/no  1:agree/disagree
	int checking_event;
	int doublecheck_result;
	int hundreds, tens, ones;
	int edge;
	int end = 0;
	MAP Map;
	Canvas canvas1;
	Canvas canvas2;
	Canvas canvas3;
	Canvas canvas4;
	Image black_turn;
	Image white_turn;
	Image opening;
	Image baduk; // 1000 * 1000
	Image menu_bg1;
	Image menu_bg2;
	Image menu_bg3;
	Image no_win;
	Image black_win;
	Image white_win;
	vector<vector<Image*>> black_square;
	vector<vector<Image*>> white_square;
	vector<vector<Image*>> blackstone;
	vector<vector<Image*>> blackstone_t;
	vector<vector<Image*>> whitestone;
	vector<vector<Image*>> whitestone_t;
	vector<Circle*> c1;
	vector<vector<Image*>> crossings;
	vector<vector<Image*>> cant;
	vector<vector<Image*>> black_numbers;
	vector<vector<Image*>> white_numbers;
	Lines boardline;
	Image start_button_pve;
	Image start_button_pve_pressed;
	Image start_button_pvp;
	Image start_button_pvp_pressed;
	Image quit_button;
	Image quit_button_pressed;
	Image config_button;
	Image config_button_pressed;

	Image black_edge;
	Image white_edge;
	
	Image check_pass;
	Image check_resign;
	Image check_back;
	Image ask_count;
	Image ask_repent;
	Image yes;
	Image yes_pressed;
	Image no;
	Image no_pressed;
	Image agree;
	Image agree_pressed;
	Image disagree;
	Image disagree_pressed;

	Image askcount;
	Image askcount_pressed;
	Image pass;
	Image pass_pressed;
	Image back;
	Image back_pressed;
	Image judge;
	Image judge_pressed;
	Image resign;
	Image resign_pressed;
	Image repent;
	Image repent_pressed;

	void start_pve();
	void start_pvp();
	void start_judge();
	void start_config();
	void start_askcount();
	void start_repent();
	void start_pass();
	void start_back();
	void start_resign();
	void create_initial_lines();
	void create_initial_circles();
	void create_initial_stones();
	void create_initial_crossings();
	void create_squares();
	void create_numbers();
	void check_event();
	void clear_board();
	void game_mouse_cb(const Mouse_event& evt);
	void menu_mouse_cb(const Mouse_event& evt);
	void gaming_menu_mouse_cb(const Mouse_event& evt);
};

Game_window::Game_window()
	: Window{ {0,0}, 1600, 1000, "Go" },
	canvas1{ {0,0}, 1000, 1000 },
	canvas2{ {1000, 0}, 600, 1000 },
	canvas3{ {0,0}, 1000, 1000 },
	canvas4{ {1000, 0}, 600, 1000 },
	baduk{ {0,0},"./resources/baduk.bmp" },
	opening{ {0,0}, "./resources/opening.bmp" },
	menu_bg1{ {0,0}, "./resources/menu_bg1.bmp" },
	menu_bg2{ {0, 0}, "./resources/menu_bg2.bmp" },
	menu_bg3{ {0,0}, "./resources/menu_bg3.bmp" },
	no_win{ {0,200}, "./resources/no_win.bmp" },
	black_win{ {0,200}, "./resources/black_win.bmp" },
	white_win{ {0,200}, "./resources/white_win.bmp" },
	black_turn{ {250, 125}, "./resources/blackstone.ico" },
	white_turn{ {320, 125}, "./resources/whitestone.ico" },
	start_button_pve{ {200, 450}, "./resources/pve1.bmp" },
	start_button_pve_pressed{ {200, 450}, "./resources/pve2.bmp" },
	start_button_pvp{ {200, 550}, "./resources/pvp1.bmp" },
	start_button_pvp_pressed{ {200, 550}, "./resources/pvp2.bmp" },
	config_button{ {200, 650}, "./resources/config1.bmp" },
	config_button_pressed{ {200, 650}, "./resources/config2.bmp" },
	quit_button{ {200, 750}, "./resources/quit1.bmp" },
	quit_button_pressed{ {200, 750}, "./resources/quit2.bmp" },
	judge{ {100, 600}, "./resources/judge1.bmp" },
	judge_pressed{ {100, 600}, "./resources/judge2.bmp" },
	repent{ {100, 700}, "./resources/repent1.bmp" },
	repent_pressed{ {100, 700}, "./resources/repent2.bmp" },
	askcount{ {100, 800}, "./resources/askcount1.bmp" },
	askcount_pressed{ {100, 800}, "./resources/askcount2.bmp" },
	pass{ {350, 600}, "./resources/pass1.bmp" },
	pass_pressed{ {350, 600}, "./resources/pass2.bmp" },
	resign{ {350, 700}, "./resources/resign1.bmp" },
	resign_pressed{ {350, 700}, "./resources/resign2.bmp" },
	back{ {350, 800}, "./resources/back1.bmp" },
	back_pressed{ {350, 800}, "./resources/back2.bmp" },
	check_pass{ {100,400}, "./resources/check_pass.bmp" },
	check_resign{ {100,400}, "./resources/check_resign.bmp" },
	check_back{ {100,400}, "./resources/check_back.bmp" },
	ask_count{ {100,400}, "./resources/askcount.bmp" },
	ask_repent{ {100,400}, "./resources/askrepent.bmp" },

	black_edge{ {100,400}, "./resources/black_edge.bmp" },
	white_edge{ {100,400}, "./resources/white_edge.bmp" },
	yes{ {100, 480}, "./resources/yes1.bmp" },
	yes_pressed{ {100, 480}, "./resources/yes2.bmp" },
	agree{ {100,480}, "./resources/agree1.bmp" },
	agree_pressed{ {100,480}, "./resources/agree2.bmp" },
	no{ {300, 480}, "./resources/no1.bmp" },
	no_pressed{ {300,480}, "./resources/no2.bmp" },
	disagree{ {300,480},"./resources/disagree1.bmp" },
	disagree_pressed{ {300, 480}, "./resources/disagree2.bmp" }
{
	attach(canvas3);
	attach(canvas1);
	attach(canvas4);
	attach(canvas2);
	canvas4.attach(menu_bg3);
	canvas4.attach(black_turn);
	canvas4.attach(no_win);
	canvas4.attach(judge);
	canvas4.attach(repent);
	canvas4.attach(askcount);
	canvas4.attach(pass);
	canvas4.attach(resign);
	canvas4.attach(back);
	canvas2.attach(menu_bg1);
	canvas2.attach(start_button_pve);
	canvas2.attach(start_button_pvp);
	canvas2.attach(config_button);
	canvas2.attach(quit_button);
	canvas1.attach(opening);
	create_initial_lines();
	create_initial_circles();
	create_initial_stones();
	create_initial_crossings();
	create_squares();
	create_numbers();
	mciSendString(L"open .\\resources\\bgm.mp3 alias bgm", NULL, 0, NULL);
	mciSendString(L"play bgm repeat", NULL, 0, NULL);
	canvas3.attach(baduk);
	canvas3.attach(boardline);
	for (int i = 0; i < c1.size(); i++) canvas3.attach(*c1[i]);
	ai = new AI;
	se = true;
	bgm = true;
	difficulty = AI_dif::easy;
	hundreds = 0;
	tens = 0;
	ones = 0;
	is_judging = 0;
	is_doublechecking = 0;
	doublecheck_result = 0;
	last_crossing_x = 0;
	last_crossing_y = 0;
	last_move_x = 0;
	last_move_y = 0;
	redraw();
	player = 0;
	canvas2.set_mouse_callback([this](const Mouse_event& evt) {menu_mouse_cb(evt); });
	canvas3.set_mouse_callback([this](const Mouse_event& evt) {game_mouse_cb(evt); });
	canvas4.set_mouse_callback([this](const Mouse_event& evt) {gaming_menu_mouse_cb(evt); });
}
