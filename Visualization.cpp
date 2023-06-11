#include <iostream>
#include <vector>
#include "Simple_window.h"
#include "GUI.h"
#include "Graph.h"
#include "qizi.h"
#include "AI.h"
#include<windows.h>
#include<Mmsystem.h>
#include "Game_window.h"
#include "config.h"
#pragma comment(lib,"winmm.lib")

using namespace Graph_lib;
using namespace std;

void Game_window::create_initial_lines()
{
	int x, y, r, i = 0;
	Point p1, p2;
	for (x = 50; x <= 950; x += 50) {
		p1 = { x, 50 };
		p2 = { x, 950 };
		boardline.add(p1, p2);
	}
	for (y = 50; y <= 950; y += 50) {
		p1 = { 50, y };
		p2 = { 950, y };
		boardline.add(p1, p2);
	}
	boardline.add({ 40, 40 }, { 40, 960 });
	boardline.add({ 40, 40 }, { 960, 40 });
	boardline.add({ 40, 960 }, { 960, 960 });
	boardline.add({ 960, 40 }, { 960, 960 });
}

void Game_window::create_initial_circles()
{
	int x, y, r;
	for (x = 200; x <= 800; x += 300) {
		for (y = 200; y <= 800; y += 300) {
			for (r = 1; r <= 8; r++) {
				c1.push_back(new Circle{ {x,y},r });
			}
		}
	}
}

void Game_window::create_initial_stones()
{
	int x, y;
	vector<Image*> temp1, temp2, temp3, temp4, temp5;
	for (y = 26; y <= 926; y += 50) {
		for (x = 26; x <= 926; x += 50) {
			temp1.push_back(new Image{ {x, y}, "./resources/blackstone.ico" });
			temp2.push_back(new Image{ {x, y}, "./resources/whitestone.ico" });
			temp3.push_back(new Image{ {x, y}, "./resources/blackstone_tri.ico" });
			temp4.push_back(new Image{ {x, y}, "./resources/whitestone_tri.ico" });
			temp5.push_back(new Image{ {x,y}, "./resources/cant.ico" });
		}
		blackstone.push_back(temp1);
		whitestone.push_back(temp2);
		blackstone_t.push_back(temp3);
		whitestone_t.push_back(temp4);
		cant.push_back(temp5);
		temp1.clear();
		temp2.clear();
		temp3.clear();
		temp4.clear();
		temp5.clear();
	}
}

void Game_window::create_initial_crossings()
{
	int x, y;
	vector<Image*> temp;
	for (y = 26; y <= 926; y += 50) {
		for (x = 26; x <= 926; x += 50) {
			if (x == 26 && y == 26) temp.push_back(new Image{ {x,y}, "./resources/right_down.ico" });
			else if (x == 26 && y == 926) temp.push_back(new Image{ {x,y}, "./resources/right_up.ico" });
			else if (x == 926 && y == 26) temp.push_back(new Image{ {x,y}, "./resources/left_down.ico" });
			else if (x == 926 && y == 926) temp.push_back(new Image{ {x,y}, "./resources/left_up.ico" });
			else if (x == 26) temp.push_back(new Image{ {x,y}, "./resources/right.ico" });
			else if (x == 926) temp.push_back(new Image{ {x,y}, "./resources/left.ico" });
			else if (y == 26) temp.push_back(new Image{ {x,y}, "./resources/down.ico" });
			else if (y == 926) temp.push_back(new Image{ {x,y}, "./resources/up.ico" });
			else temp.push_back(new Image{ {x,y}, "./resources/all.ico" });
		}
		crossings.push_back(temp);
		temp.clear();
	}
}

void Game_window::create_squares()
{
	int x, y;
	vector<Image*> temp1, temp2;
	for (y = 38; y <= 938; y += 50) {
		for (x = 38; x <= 938; x += 50) {
			temp1.push_back(new Image{ {x, y}, "./resources/black_square.bmp" });
			temp2.push_back(new Image{ {x, y}, "./resources/white_square.bmp" });
		}
		black_square.push_back(temp1);
		white_square.push_back(temp2);
		temp1.clear();
		temp2.clear();
	}
}

void Game_window::create_numbers()
{
	int x, y = 520;
	vector<Image*> temp1, temp2;
	for (x = 215; x <= 255; x += 20) {
		temp1.push_back(new Image{ {x, y}, "./resources/b0.ico" });
		y += 2;
		temp1.push_back(new Image{ {x, y}, "./resources/b1.ico" });
		temp1.push_back(new Image{ {x, y}, "./resources/b2.ico" });
		y -= 2;
		temp1.push_back(new Image{ {x, y}, "./resources/b3.ico" });
		temp1.push_back(new Image{ {x, y}, "./resources/b4.ico" });
		temp1.push_back(new Image{ {x, y}, "./resources/b5.ico" });
		temp1.push_back(new Image{ {x, y}, "./resources/b6.ico" });
		temp1.push_back(new Image{ {x, y}, "./resources/b7.ico" });
		temp1.push_back(new Image{ {x, y}, "./resources/b8.ico" });
		temp1.push_back(new Image{ {x, y}, "./resources/b9.ico" });
		temp2.push_back(new Image{ {x, y}, "./resources/w0.ico" });
		y += 2;
		temp2.push_back(new Image{ {x, y}, "./resources/w1.ico" });
		temp2.push_back(new Image{ {x, y}, "./resources/w2.ico" });
		y -= 2;
		temp2.push_back(new Image{ {x, y}, "./resources/w3.ico" });
		temp2.push_back(new Image{ {x, y}, "./resources/w4.ico" });
		temp2.push_back(new Image{ {x, y}, "./resources/w5.ico" });
		temp2.push_back(new Image{ {x, y}, "./resources/w6.ico" });
		temp2.push_back(new Image{ {x, y}, "./resources/w7.ico" });
		temp2.push_back(new Image{ {x, y}, "./resources/w8.ico" });
		temp2.push_back(new Image{ {x, y}, "./resources/w9.ico" });
		black_numbers.push_back(temp1);
		white_numbers.push_back(temp2);
		temp1.clear();
		temp2.clear();
	}
	x = 285;
	temp1.push_back(new Image{ {x, y}, "./resources/b5.ico" });
	temp2.push_back(new Image{ {x, y}, "./resources/w5.ico" });
	black_numbers.push_back(temp1);
	white_numbers.push_back(temp2);
}

void Game_window::start_judge()
{
	Map.map_score();
	edge = -7; //由于实际规则让7.5目，所以>0:black_edge; <=0:white_edge;
	int x, y;
	if (is_judging) {
		canvas4.detach(black_edge);
		canvas4.detach(white_edge);
		canvas4.detach(*black_numbers[0][hundreds]);
		canvas4.detach(*black_numbers[1][tens]);
		canvas4.detach(*black_numbers[2][ones]);
		canvas4.detach(*black_numbers[3][0]);
		canvas4.detach(*white_numbers[0][hundreds]);
		canvas4.detach(*white_numbers[1][tens]);
		canvas4.detach(*white_numbers[2][ones]);
		canvas4.detach(*white_numbers[3][0]);

		for (x = 0; x < 19; x++) {
			for (y = 0; y < 19; y++) {
				canvas3.detach(*black_square[y][x]);
				canvas3.detach(*white_square[y][x]);
			}
		}
		is_judging = 0;
		return;
	}
	else {
		is_judging = 1;
		for (x = 0; x < 19; x++) {
			for (y = 0; y < 19; y++) {
				if (Map.map[x + 1][y + 1].see_score() > 2){
					edge++;
					if (Map.map[x + 1][y + 1].see_node() != node::black_node) {
						canvas3.attach(*black_square[y][x]);
					}
				}
				else if (Map.map[x + 1][y + 1].see_score() < -2){
					edge--;
					if (Map.map[x + 1][y + 1].see_node() != node::white_node) {
						canvas3.attach(*white_square[y][x]);
					}
				}
			}
		}
		if (edge > 0) {
			edge--;
			hundreds = edge / 100;
			tens = (edge % 100) / 10;
			ones = edge % 10;
			canvas4.attach(black_edge);
			if(hundreds) canvas4.attach(*black_numbers[0][hundreds]);
			if(hundreds||tens)canvas4.attach(*black_numbers[1][tens]);
			canvas4.attach(*black_numbers[2][ones]);
			canvas4.attach(*black_numbers[3][0]);
			edge++;
		}
		else {
			edge = -edge;
			hundreds = edge / 100;
			tens = (edge % 100) / 10;
			ones = edge % 10;
			canvas4.attach(white_edge);
			if (hundreds) canvas4.attach(*white_numbers[0][hundreds]);
			if (hundreds || tens)canvas4.attach(*white_numbers[1][tens]);
			canvas4.attach(*white_numbers[2][ones]);
			canvas4.attach(*white_numbers[3][0]);
			edge = -edge;
		}
	}
}

void Game_window::start_config()
{
	config a(this);
	gui_main(a);
}

//event0
void Game_window::start_askcount()
{
	if (doublecheck_result || ai_opponent) {
		is_judging = 0;
		start_judge();
		end = 1;
		if (edge >= 0) canvas4.attach(black_win);
		else canvas4.attach(white_win);
	}
	else {
		checking_event = 0;
		is_doublechecking = 1;
		checkmode = 1;
		canvas4.attach(ask_count);
		canvas4.attach(agree);
		canvas4.attach(disagree);
	}
}

//event1
void Game_window::start_repent()
{
	if (doublecheck_result || ai_opponent) {
		int x, y;
		auto c = node::black_node;
		if (player) c = node::white_node;
		if (Map.repetance(c)) {
			for (y = 0; y < 19; y++) {
				for (x = 0; x < 19; x++) {
					canvas3.detach(*blackstone[y][x]);
					canvas3.detach(*whitestone[y][x]);
					if (Map.map[x + 1][y + 1].see_node() == node::black_node) canvas3.attach(*blackstone[y][x]);
					else if (Map.map[x + 1][y + 1].see_node() == node::white_node) canvas3.attach(*whitestone[y][x]);
				}
			}
			canvas3.detach(*blackstone_t[last_move_y][last_move_x]);
			canvas3.detach(*whitestone_t[last_move_y][last_move_x]);
		}
		if (ai_opponent) ai->undo(Map);
		doublecheck_result = 0;
	}
	else {
		checking_event = 1;
		is_doublechecking = 1;
		checkmode = 1;
		canvas4.attach(ask_repent);
		canvas4.attach(agree);
		canvas4.attach(disagree);
	}
	redraw();
}

//event2
void Game_window::start_pass()
{
	if (doublecheck_result) {
		if (player) {
			canvas3.detach(*blackstone_t[last_move_y][last_move_x]);
			canvas4.detach(white_turn);
			canvas4.attach(black_turn);
			player = 0;
		}
		else {
			canvas3.detach(*whitestone_t[last_move_y][last_move_x]);
			canvas4.detach(black_turn);
			canvas4.attach(white_turn);
			player = 1;
			if (ai_opponent) {
				auto ai_choice = ai->None_for_next();
				int ai_x = ai_choice.x - 1;
				int ai_y = ai_choice.y - 1;
				auto ai_chess = node::white_node;
				Map.set_chess(ai_x + 1, ai_y + 1, ai_chess);
				canvas3.detach(*blackstone_t[last_move_y][last_move_x]);
				last_move_x = ai_x;
				last_move_y = ai_y;
				canvas3.attach(*whitestone[ai_y][ai_x]);
				canvas3.attach(*whitestone_t[ai_y][ai_x]);
				player = 0;
				if (!Map.delete_list.empty()) {
					for (int n = 0; n < Map.delete_list.size(); n++) {
						int x = Map.delete_list[n].x - 1;
						int y = Map.delete_list[n].y - 1;
						canvas3.detach(*blackstone[y][x]);
						canvas3.detach(*whitestone[y][x]);
					}
					PlaySound(TEXT("./resources/remove.wav"), NULL, SND_FILENAME | SND_ASYNC);
				}
				else PlaySound(TEXT("./resources/move.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
		}
	}
	else {
		checking_event = 2;
		is_doublechecking = 1;
		checkmode = 0;
		canvas4.attach(check_pass);
		canvas4.attach(yes);
		canvas4.attach(no);
	}
	redraw();
}

//event3
void Game_window::start_back()
{
	if (doublecheck_result) {
		int x, y;
		Map.reset_map();
		for (y = 0; y < 19; y++) {
			for (x = 0; x < 19; x++) {
				canvas3.detach(*blackstone[y][x]);
				canvas3.detach(*whitestone[y][x]);
			}
		}
		player = 0;
		canvas3.detach(*blackstone_t[last_move_y][last_move_x]);
		canvas3.detach(*whitestone_t[last_move_y][last_move_x]);
		attach(canvas1);
		attach(canvas2);
	}
	else {
		checking_event = 3;
		is_doublechecking = 1;
		checkmode = 0;
		canvas4.attach(check_back);
		canvas4.attach(yes);
		canvas4.attach(no);
	}
	redraw();
}

//event4
void Game_window::start_resign()
{
	if (doublecheck_result) {
		int x, y;
		end = 1;
		if (player)canvas4.attach(black_win);
		else canvas4.attach(white_win);
	}
	else {
		checking_event = 4;
		is_doublechecking = 1;
		checkmode = 0;
		canvas4.attach(check_resign);
		canvas4.attach(yes);
		canvas4.attach(no);
	}
	redraw();
}

void Game_window::check_event()
{
	canvas4.detach(ask_count);
	canvas4.detach(ask_repent);
	canvas4.detach(check_pass);
	canvas4.detach(check_back);
	canvas4.detach(check_resign);
	canvas4.detach(yes_pressed);
	canvas4.detach(no_pressed);
	canvas4.detach(yes);
	canvas4.detach(no);
	canvas4.detach(agree_pressed);
	canvas4.detach(disagree_pressed);
	canvas4.detach(agree);
	canvas4.detach(disagree);
	switch (checking_event) {
	case 0:
		if (doublecheck_result) start_askcount();
		break;
	case 1:
		if (doublecheck_result) start_repent();
		break;
	case 2:
		if (doublecheck_result) start_pass();
		break;
	case 3:
		if (doublecheck_result) start_back();
		break;
	case 4:
		if (doublecheck_result) start_resign();
		break;
	default:
		Exit();
	}
	doublecheck_result = 0;
	checking_event = 0;
	checkmode = 0;
	is_doublechecking = 0;
}

void Game_window::menu_mouse_cb(const Mouse_event& evt)
{
	Point p;
	int x, y;
	if (evt.type == Mouse_event::move) {
		p = evt.pos;
		x = p.x;
		y = p.y;
		if (x > 200 && x < 400) {
			canvas2.detach(start_button_pve_pressed);
			canvas2.detach(start_button_pvp_pressed);
			canvas2.detach(config_button_pressed);
			canvas2.detach(quit_button_pressed);
			if (y > 450 && y < 520) {
				canvas2.attach(start_button_pve_pressed);
			}
			else if (y > 550 && y < 620) {
				canvas2.attach(start_button_pvp_pressed);
			}
			else if (y > 650 && y < 720) {
				canvas2.attach(config_button_pressed);
			}
			else if (y > 750 && y < 820) {
				canvas2.attach(quit_button_pressed);
			}
			else {
				redraw();
				return;
			}
			redraw();
		}
		else {
			canvas2.detach(start_button_pve_pressed);
			canvas2.detach(start_button_pvp_pressed);
			canvas2.detach(config_button_pressed);
			canvas2.detach(quit_button_pressed);
			redraw();
		}
	}
	else if (evt.type == Mouse_event::push) {
		p = evt.pos;
		x = p.x;
		y = p.y;
		if (x > 200 && x < 400) {
			if (y > 450 && y < 520) {
				start_pve();
			}
			else if (y > 550 && y < 620) {
				start_pvp();
			}
			else if (y > 650 && y < 720) {
				start_config();
			}
			else if (y > 750 && y < 820) {
				Exit();
			}
		}
	}
	else return;
}

void Game_window::game_mouse_cb(const Mouse_event& evt)
{
	Point p;
	int x, y;
	if (is_judging) return;
	else if (evt.type == Mouse_event::push) {
		p = evt.pos;
		x = p.x;
		y = p.y;
		x -= 25;
		x /= 50;
		y -= 25;
		y /= 50;	//x,y -> [x, y]

		if (player == 0) {
			auto i = node::black_node;
			if (Map.set_chess(x + 1, y + 1, i)) {
				canvas3.detach(*whitestone_t[last_move_y][last_move_x]);
				last_move_x = x;
				last_move_y = y;
				canvas3.attach(*blackstone[y][x]);
				canvas3.attach(*blackstone_t[y][x]);
				player = 1;
				canvas3.detach(*crossings[last_crossing_y][last_crossing_x]);
				canvas4.detach(black_turn);
				canvas4.attach(white_turn);
			}
			else if (Map.map[x + 1][y + 1].see_node() == node::no_node) {
				canvas3.detach(*crossings[y][x]);
				canvas3.attach(*cant[y][x]);
				redraw();
				if(se) PlaySound(TEXT("./resources/cantmove.wav"), NULL, SND_FILENAME | SND_ASYNC);
				canvas3.detach(*cant[y][x]);
				canvas3.attach(*crossings[y][x]);
				return;
			}
			else return;
		}
		else {
			auto i = node::white_node;
			if (Map.set_chess(x + 1, y + 1, i)) {
				canvas3.detach(*blackstone_t[last_move_y][last_move_x]);
				last_move_x = x;
				last_move_y = y;
				canvas3.attach(*whitestone[y][x]);
				canvas3.attach(*whitestone_t[y][x]);
				player = 0;
				canvas3.detach(*crossings[y][x]);
				canvas4.detach(white_turn);
				canvas4.attach(black_turn);
			}
			else if (Map.map[x + 1][y + 1].see_node() == node::no_node) {
				canvas3.detach(*crossings[y][x]);
				canvas3.attach(*cant[y][x]);
				redraw();
				if(se) PlaySound(TEXT("./resources/cantmove.wav"), NULL, SND_FILENAME | SND_ASYNC);
				canvas3.detach(*cant[y][x]);
				canvas3.attach(*crossings[y][x]);
				return;
			}
			else return;
		}

		if (!Map.delete_list.empty()) {
			for (int n = 0; n < Map.delete_list.size(); n++) {
				x = Map.delete_list[n].x - 1;
				y = Map.delete_list[n].y - 1;
				canvas3.detach(*blackstone[y][x]);
				canvas3.detach(*whitestone[y][x]);
			}
			if(se) PlaySound(TEXT("./resources/remove.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else if(se) PlaySound(TEXT("./resources/move.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	else if (evt.type == Mouse_event::move) {
		p = evt.pos;
		x = p.x;
		y = p.y;
		if (x >= 975 || y >= 975) canvas3.detach(*crossings[last_crossing_y][last_crossing_x]);
		else {
			x -= 25;
			x /= 50;
			y -= 25;
			y /= 50;	//x,y -> [x, y]
			if (last_crossing_x != x || last_crossing_y != y) {
				canvas3.detach(*crossings[last_crossing_y][last_crossing_x]);
				last_crossing_x = x;
				last_crossing_y = y;
				if(Map.map[x+1][y+1].see_node() == node::no_node) canvas3.attach(*crossings[y][x]);
			}
			else return;
		}
	}
	else if (evt.type == Mouse_event::release) {
		if (ai_opponent && player)
		{
			coordinate ai_choice;
			ai_choice = ai->AI_for_next({ last_move_x + 1, last_move_y + 1 });
			int ai_x = ai_choice.x - 1;
			int ai_y = ai_choice.y - 1;
			if (ai_x == -1 && ai_y == -1) {
				canvas3.detach(*blackstone_t[last_move_y][last_move_x]);
			}
			else{
				auto ai_chess = node::white_node;
				Map.set_chess(ai_x + 1, ai_y + 1, ai_chess);
				canvas3.detach(*blackstone_t[last_move_y][last_move_x]);
				last_move_x = ai_x;
				last_move_y = ai_y;
				canvas3.attach(*whitestone[ai_y][ai_x]);
				canvas3.attach(*whitestone_t[ai_y][ai_x]);
				if (!Map.delete_list.empty()) {
					for (int n = 0; n < Map.delete_list.size(); n++) {
						x = Map.delete_list[n].x - 1;
						y = Map.delete_list[n].y - 1;
						canvas3.detach(*blackstone[y][x]);
						canvas3.detach(*whitestone[y][x]);
					}
					if(se) PlaySound(TEXT("./resources/remove.wav"), NULL, SND_FILENAME | SND_ASYNC);
				}
				else if(se) PlaySound(TEXT("./resources/move.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			player = 0;
			canvas4.detach(white_turn);
			canvas4.attach(black_turn);
		}
	}
	else return;
	redraw();
}

void Game_window::gaming_menu_mouse_cb(const Mouse_event& evt)
{
	Point p;
	int x, y;
	if (evt.type == Mouse_event::move) {
		p = evt.pos;
		x = p.x;
		y = p.y;
		if (is_doublechecking && y > 480 && y < 550) {
			canvas4.detach(yes_pressed);
			canvas4.detach(agree_pressed);
			canvas4.detach(no_pressed);
			canvas4.detach(disagree_pressed);
			if (x > 150 && x < 250) {
				if (checkmode == 0) canvas4.attach(yes_pressed);
				else canvas4.attach(agree_pressed);
			}
			else if (x > 350 && x < 450) {
				if (checkmode == 0) canvas4.attach(no_pressed);
				else canvas4.attach(disagree_pressed);
			}
			else {
				redraw();
				return;
			}
			redraw();
		}
		else if (x > 100 && x < 250) {
			canvas4.detach(judge_pressed);
			canvas4.detach(repent_pressed);
			canvas4.detach(askcount_pressed);
			canvas4.detach(pass_pressed);
			canvas4.detach(resign_pressed);
			canvas4.detach(back_pressed);
			if (y > 600 && y < 670) canvas4.attach(judge_pressed);
			else if (y > 700 && y < 770) canvas4.attach(repent_pressed);
			else if (y > 800 && y < 870) canvas4.attach(askcount_pressed);
			else {
				redraw();
				return;
			}
			redraw();
		}
		else if (x > 350 && x < 500) {
			canvas4.detach(judge_pressed);
			canvas4.detach(repent_pressed);
			canvas4.detach(askcount_pressed);
			canvas4.detach(pass_pressed);
			canvas4.detach(resign_pressed);
			canvas4.detach(back_pressed);
			if (y > 600 && y < 670) canvas4.attach(pass_pressed);
			else if (y > 700 && y < 770) canvas4.attach(resign_pressed);
			else if (y > 800 && y < 870) canvas4.attach(back_pressed);
			else {
				redraw();
				return;
			}
			redraw();
		}
		else {
			canvas4.detach(judge_pressed);
			canvas4.detach(repent_pressed);
			canvas4.detach(askcount_pressed);
			canvas4.detach(pass_pressed);
			canvas4.detach(resign_pressed);
			canvas4.detach(back_pressed);
			canvas4.detach(yes_pressed);
			canvas4.detach(agree_pressed);
			canvas4.detach(no_pressed);
			canvas4.detach(disagree_pressed);
			redraw();
		}
	}
	else if (evt.type == Mouse_event::push) {
		p = evt.pos;
		x = p.x;
		y = p.y;
		if (is_doublechecking && y > 480 && y < 550) {
			if (x > 150 && x < 250) {
				if (checkmode == 0) {
					canvas4.detach(yes_pressed);
					canvas4.detach(yes);
					canvas4.detach(no);
				}
				else {
					canvas4.detach(agree_pressed);
					canvas4.detach(agree);
					canvas4.detach(disagree);
				}
				doublecheck_result = 1;
				check_event();
			}
			else if (x > 350 && x < 450) {
				if (checkmode == 0) {
					canvas4.detach(no_pressed);
					canvas4.detach(yes);
					canvas4.detach(no);
				}
				else {
					canvas4.detach(disagree_pressed);
					canvas4.detach(agree);
					canvas4.detach(disagree);
				}
				doublecheck_result = 0;
				check_event();
			}
		}
		else if (x > 100 && x < 250) {
			if (!end && y > 600 && y < 670) start_judge();
			else if (!end && y > 700 && y < 770) start_repent();
			else if (!end &&y > 800 && y < 870) start_askcount();
			else {
				redraw();
				return;
			}
		}
		else if (x > 350 && x < 500) {
			if (!end && y > 600 && y < 670) start_pass();
			else if (!end && y > 700 && y < 770) start_resign();
			else if (y > 800 && y < 870) start_back();
			else {
				redraw();
				return;
			}
		}
		else return;
	}
	else return;
}

void Game_window::clear_board()
{
	int x, y;
	for (y = 0; y < 19; y++) {
		for (x = 0; x < 19; x++) {
			canvas3.detach(*blackstone[y][x]);
			canvas3.detach(*whitestone[y][x]);
			canvas3.detach(*blackstone_t[y][x]);
			canvas3.detach(*whitestone_t[y][x]);
		}
	}
	is_judging = 1;
	start_judge();
	canvas4.detach(black_win);
	canvas4.detach(white_win);
	edge = 0;
}

void Game_window::start_pve()
{
	clear_board();
	detach(canvas2);
	detach(canvas1);
	ai = new AI;
	ai->mode(int(difficulty));
	ai_opponent = 1;
	end = 0;
	redraw();
}

void Game_window::start_pvp()
{
	clear_board();
	detach(canvas2);
	detach(canvas1);
	ai_opponent = 0;
	end = 0;
	redraw();
}

int main()
{
	Game_window go;
	gui_main(go);
}
