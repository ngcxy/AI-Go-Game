#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include "qizi.h"
using namespace std;

int RandomData(int min, int max) {
	random_device sd;
	minstd_rand linearRan(sd());
	uniform_int_distribution<int>dis1(min, max);
	return dis1(linearRan);
}

vector<coordinate> create_neighbors(coordinate center)
{
	vector<coordinate> near_neighbors;
	near_neighbors.push_back({ center.x - 1,center.y });
	near_neighbors.push_back({ center.x + 1,center.y });
	near_neighbors.push_back({ center.x,center.y - 1 });
	near_neighbors.push_back({ center.x,center.y + 1 });          
	return near_neighbors;
}

vector<coordinate> create_remote_neighbors(coordinate center)
{
	vector<coordinate> remote_neighbors;
	remote_neighbors.push_back({ center.x - 1,center.y - 1 });
	remote_neighbors.push_back({ center.x - 1,center.y + 1 });
	remote_neighbors.push_back({ center.x + 1,center.y - 1 });
	remote_neighbors.push_back({ center.x + 1,center.y + 1 });    //�Խ������ĸ�����
	return remote_neighbors;
}

vector<estimate_score> place_data(coordinate center)
{
	vector<estimate_score> result;
	result.push_back({ center,15 });						//���ĵ㣬15��Ȩ��
	result.push_back({ {center.x - 1,center.y},6 });		//���ڵ�4���㣬6��Ȩ��
	result.push_back({ {center.x + 1,center.y},6 });
	result.push_back({ {center.x,center.y - 1},6 });
	result.push_back({ {center.x,center.y + 1},6 });
	result.push_back({ {center.x - 1,center.y - 1},5 });
	result.push_back({ {center.x + 1,center.y - 1},5 });
	result.push_back({ {center.x - 1,center.y + 1},5 });
	result.push_back({ {center.x + 1,center.y + 1},5 });
	result.push_back({ {center.x - 2,center.y},3 });
	result.push_back({ {center.x + 2,center.y},3 });
	result.push_back({ {center.x,center.y - 2},3 });
	result.push_back({ {center.x,center.y + 2},3 });
	result.push_back({ {center.x - 1,center.y - 2},2 });
	result.push_back({ {center.x - 2,center.y - 1},2 });
	result.push_back({ {center.x + 1,center.y - 2},2 });
	result.push_back({ {center.x + 2,center.y - 1},2 });
	result.push_back({ {center.x - 1,center.y + 2},2 });	
	result.push_back({ {center.x - 2,center.y + 1},2 });
	result.push_back({ {center.x + 1,center.y + 2},2 });
	result.push_back({ {center.x + 2,center.y + 1},2 });
	return result;
}

void coordinate::operator++() {
	int value = 19 * (x - 1) + y - 1;
	if (value >= 360 || value < 0) {
		x = 0;
		y = 0;
		return;
	}
	value++;
	x = (value / 19) + 1;
	y = (value % 19) + 1;
	return;
}

bool coordinate::operator==(coordinate& i) {
	return (x == i.x && y == i.y);
}

MAP::MAP()
	:is_finished(false),
	step_num(0)
{
	for (int i = 0; i < MAP_LEN + 2;i++)
		for (int j = 0; j < MAP_LEN + 2; j++)
		{
			if (i == 0 || i == MAP_LEN + 1|| j == 0 || j == MAP_LEN + 1)     //21*21����ΧһȦΪ����ʹ�����򣬳�ʼ��Ϊnot_node
				map[i][j].set_node(node::not_node);
			else
				map[i][j].set_node(node::no_node);
			map[i][j].reset();
			map[i][j].clear_score();
		}
	map_stack.push_back(map_to_vec());
	map_stack.push_back(map_to_vec());
}

void MAP::reset_map()
{
	history.clear();
	step_num = 0;
	is_finished = false;
	for (int i = 1; i < MAP_LEN + 1; i++)
	{
		for (int j = 1; j < MAP_LEN + 1; j++)
		{
			map[i][j].set_node(node::no_node);
			map[i][j].reset();
			map[i][j].clear_score();
		}
	}
	map_stack.clear();
	map_stack.push_back(map_to_vec());
	map_stack.push_back(map_to_vec());
}

void MAP::init()
{
	for (int i = 1; i < MAP_LEN + 1; i++)
		for (int j = 1; j < MAP_LEN + 1; j++)
			map[i][j].reset();
}

//void MAP::display_map()
//{
//	for (int i = 1; i < MAP_LEN + 1; i++)
//	{
//		for (int j = 1; j < MAP_LEN + 1; j++)
//		{
//			switch (map[i][j].see_node())
//			{
//			case node::black_node:
//				cout << "1  ";
//				break;
//			case node::white_node:
//				cout << "2  ";
//				break;
//			case node::not_node:
//				cout << "X  ";
//				break;
//			default:
//				cout << "0  ";
//				break;
//			}
//		}
//		cout << "\n";
//		cout << "\n";
//	}
//}

vector<node> MAP::map_to_vec()
{
	vector<node> temp;
	for (int i = 1; i < MAP_LEN + 1; i++)
		for (int j = 1; j < MAP_LEN + 1; j++)
			temp.push_back(map[i][j].see_node());
	return temp;
}

void MAP::vec_to_map(vector<node> one_map)
{
	for (int i = 1; i < MAP_LEN + 1; i++)
		for (int j = 1; j < MAP_LEN + 1; j++)
			map[i][j].set_node(one_map[(i - 1) * MAP_LEN + j - 1]);
}

bool MAP::is_jie()
{
	for (int i = 1; i < MAP_LEN + 1; i++)
	{
		for (int j = 1; j < MAP_LEN + 1; j++)
		{
			if (map[i][j].see_node() != map_stack[map_stack.size() - 2][(i - 1) * MAP_LEN + j - 1])
				return false;
		}
	}
	return true;
}

bool MAP::set_chess(int x, int y, node chess)
{
	if (map[x][y].see_node() != node::no_node)
	{
		//cout << "you can't set here!" << endl;
		return false;
	}
	map[x][y].set_node(chess);
	int deletable = update_state(chess, { x,y });
	if (map[x][y].see_qi() == 0 && deletable == 0)
	{
		//cout << "you can't set here!" << endl;
		map[x][y].set_node(node::no_node);
		return false;
	}
	if (deletable == 1 && is_jie())
	{
		//cout << "you can't set here!" << endl;
		vec_to_map(map_stack[map_stack.size() - 1]);
		return false;
	}
	step_num++;
	step temp{ {x,y},chess };
	history.push_back(temp);
	if (map_stack.size() == MAX_STORE)
	{
		map_stack.erase(map_stack.begin());
		map_stack.push_back(map_to_vec());
	}
	else
		map_stack.push_back(map_to_vec());
	//display_map();
	return true;
}

int MAP::update_state(node chess, coordinate place)
{
	int signal = 0;
	init();
	delete_list.clear();
	vector<coordinate> neighbor = create_neighbors(place);
	neighbor.push_back(place);
	for (int i = 0; i < neighbor.size(); i++)
	{
		if ((map[neighbor[i].x][neighbor[i].y].see_node() == node::black_node || map[neighbor[i].x][neighbor[i].y].see_node() == node::white_node) && map[neighbor[i].x][neighbor[i].y].see_checked() == 0)
		{
			chess_stack.clear();
			hole_stack.clear();
			find_qi(neighbor[i].x, neighbor[i].y);
			if (hole_stack.empty() && chess != map[neighbor[i].x][neighbor[i].y].see_node())
			{
				signal = 1;
				for (int j = 0; j < chess_stack.size(); j++)
				{
					delete_list.push_back(chess_stack[j]);
					delete_node(chess_stack[j]);
				}
			}
			else
			{
				for (int k = 0; k < chess_stack.size(); k++)
					map[chess_stack[k].x][chess_stack[k].y].set_qi(hole_stack.size());
				for (int k = 0; k < hole_stack.size(); k++)
					map[hole_stack[k].x][hole_stack[k].y].reset();
			}
		}
	}
	return signal;
}

void MAP::find_qi(int x, int y)
{
	coordinate	temp;
	map[x][y].checked();
	temp.x = x;
	temp.y = y;
	chess_stack.push_back(temp);
	if (map[x + 1][y].see_node() == map[x][y].see_node() && map[x + 1][y].see_checked() == 0)
		find_qi(x + 1, y);
	else if (map[x + 1][y].see_node() == node::no_node && map[x + 1][y].see_checked() == 0)
	{
		temp.x = x + 1;
		temp.y = y;
		hole_stack.push_back(temp);
		map[x + 1][y].checked();
	}
	if (map[x - 1][y].see_node() == map[x][y].see_node() && map[x - 1][y].see_checked() == 0)
		find_qi(x - 1, y);
	else if (map[x - 1][y].see_node() == node::no_node && map[x - 1][y].see_checked() == 0)
	{
		temp.x = x - 1;
		temp.y = y;
		hole_stack.push_back(temp);
		map[x - 1][y].checked();
	}
	if (map[x][y + 1].see_node() == map[x][y].see_node() && map[x][y + 1].see_checked() == 0)
		find_qi(x, y + 1);
	else if (map[x][y + 1].see_node() == node::no_node && map[x][y + 1].see_checked() == 0)
	{
		temp.x = x;
		temp.y = y + 1;
		hole_stack.push_back(temp);
		map[x][y + 1].checked();
	}
	if (map[x][y - 1].see_node() == map[x][y].see_node() && map[x][y - 1].see_checked() == 0)
		find_qi(x, y - 1);
	else if (map[x][y - 1].see_node() == node::no_node && map[x][y - 1].see_checked() == 0)
	{
		temp.x = x;
		temp.y = y - 1;
		hole_stack.push_back(temp);
		map[x][y - 1].checked();
	}
}

void MAP::delete_node(coordinate x)
{
	map[x.x][x.y].set_node(node::no_node);
	map[x.x][x.y].reset();
}

//bool MAP::check_forbidden(coordinate x, node chess)
//{
//	map[x.x][x.y].set_node(chess);
//	int deletable = update_state(chess,x);
//	if (map[x.x][x.y].see_qi() == 0 && deletable == 0)
//	{
//		map[x.x][x.y].set_node(node::no_node);
//		map[x.x][x.y].forbidden();
//		return true;
//	}
//	if (is_jie())
//	{
//		vec_to_map(map_stack[map_stack.size() - 1]);
//		map[x.x][x.y].forbidden();
//		return true;
//	}
//	vec_to_map(map_stack[map_stack.size() - 1]);
//	return false;
//}

//bool MAP::is_dead(int x, int y)
//{
//	for (int i = 0; i < hole_stack.size(); i++)
//		map[hole_stack[i].x][hole_stack[i].y].reset();
//	chess_stack.clear();
//	hole_stack.clear();
//	find_qi(x, y);
//	int eyes = 0;
//	int alive = 0;
//	for (int i = 0; i < hole_stack.size(); i++)
//	{
//		if (is_an_eye(hole_stack[i]))
//		{
//			eyes++;
//			if (eyes == 2)
//				return false;
//		}
//		else
//		{
//			vector<coordinate> neighbor = create_neighbors({ hole_stack[i].x,hole_stack[i].y });
//			int count = 0;
//			for (int j = 0; j < neighbor.size(); j++)
//			{
//				if (map[neighbor[j].x][neighbor[j].y].see_node() == node::no_node)
//					count++;
//			}
//			if (count >= 2)
//			{
//				alive++;
//				if (alive == 1)
//					return false;
//			}
//		}
//	}
//	return true;
//}

//bool MAP::is_an_eye(coordinate x)
//{
//	vector<coordinate> near_neighbors = create_neighbors(x);
//	vector<coordinate> remote_neighbors = create_remote_neighbors(x);
//	bool is_edge = false;
//	int near = 0;
//	int remote = 0;
//	for (int i = 0; i < near_neighbors.size(); i++)
//	{
//		if (map[x.x][x.y].see_node() == map[near_neighbors[i].x][near_neighbors[i].y].see_node())
//			near++;
//		else if (map[near_neighbors[i].x][near_neighbors[i].y].see_node() == node::not_node)
//		{
//			near++;
//			is_edge = true;
//		}
//	}
//	if (near != 4)
//		return false;
//	for (int i = 0; i < remote_neighbors.size(); i++)
//	{
//		if (map[x.x][x.y].see_node() == map[remote_neighbors[i].x][remote_neighbors[i].y].see_node() || map[remote_neighbors[i].x][remote_neighbors[i].y].see_node() == node::not_node)
//			remote++;
//	}
//	if (remote < 3 || (remote == 3 && is_edge))
//		return false;
//	return true;
//}

//int MAP::white_or_black(coordinate x)
//{
//	int row = x.x;
//	int col = x.y;
//	int black = 0;
//	int white = 0;
//	if (row == 1 || row == MAP_LEN)
//	{
//		black++;
//		white++;
//	}
//	if (col == 1 || col == MAP_LEN)
//	{
//		black++;
//		white++;
//	}
//	for (int i = row - 1; i >= 1; i--)
//	{
//		if (map[i][col].see_node() == node::black_node)
//		{
//			black++;
//			break;
//		}
//		if (map[i][col].see_node() == node::white_node)
//		{
//			white++;
//			break;
//		}
//	}
//	for (int i = row + 1; i <= MAP_LEN; i++)
//	{
//		if (map[i][col].see_node() == node::black_node)
//		{
//			black++;
//			break;
//		}
//		if (map[i][col].see_node() == node::white_node)
//		{
//			white++;
//			break;
//		}
//	}
//	for (int i = col - 1; i >= 1; i--)
//	{
//		if (map[row][i].see_node() == node::black_node)
//		{
//			black++;
//			break;
//		}
//		if (map[row][i].see_node() == node::white_node)
//		{
//			white++;
//			break;
//		}
//	}
//	for (int i = col + 1; i <= MAP_LEN; i++)
//	{
//		if (map[row][i].see_node() == node::black_node)
//		{
//			black++;
//			break;
//		}
//		if (map[row][i].see_node() == node::white_node)
//		{
//			white++;
//			break;
//		}
//	}
//	if (white == 4)
//		return 2;
//	else if (black == 4)
//		return 1;
//	else
//		return 0;
//}

void MAP::who_wins()
{
	map_score();
	double white_score = 7.5;
	double black_score = 0;
	for (int i = 1; i < MAP_LEN + 1; i++)
	{
		for (int j = 1; j < MAP_LEN + 1; j++)
		{
			if (map[i][j].see_score() > 0)
				black_score = black_score + 1;
			else if (map[i][j].see_score() < 0)
				white_score = white_score + 1;
		}
	}
	output_record();
}

bool MAP::repetance(node chess)
{
	int len = history.size();
	int i = len - 1;
	bool signal = false;
	while (i >= 0)
	{
		if (history[i].chess == chess)
		{
			signal = true;
			break;
		}
		i--;
	}
	if (!signal)
		return false;
	for (int j = len - i; j > 0; j--)
	{
		history.pop_back();
		map_stack.pop_back();
		step_num--;
	}
	vec_to_map(map_stack[map_stack.size() - 1]);
	//display_map();
}

void MAP::compute_score(node chess, coordinate place, const int is_delete)
{
	if (chess == node::no_node)
		return;
	vector<estimate_score> data = place_data(place);
	if (chess == node::black_node)
	{
		for (int i = 0; i < data.size();i++)
		{
			if (data[i].place.x < 1 || data[i].place.x > MAP_LEN || data[i].place.y < 1 || data[i].place.y > MAP_LEN)
				continue;
			map[data[i].place.x][data[i].place.y].add_score(data[i].score * is_delete);
		}
	}
	if (chess == node::white_node)
	{
		for (int i = 0; i < data.size();i++)
		{
			if (data[i].place.x < 1 || data[i].place.x > MAP_LEN || data[i].place.y < 1 || data[i].place.y > MAP_LEN)	//���Խ��
				continue;
			map[data[i].place.x][data[i].place.y].add_score(data[i].score * is_delete * (-1));
		}
	}
}

double MAP::map_score()
{
	for (int i = 1; i < MAP_LEN + 1; i++)
		for (int j = 1; j < MAP_LEN + 1; j++)
			map[i][j].clear_score();					//��ַ�������
	for (int i = 1; i < MAP_LEN + 1; i++)
		for (int j = 1; j < MAP_LEN + 1; j++)
			compute_score(map[i][j].see_node(), { i,j }, 1);
	double total_score = 0;
	for (int i = 1; i < MAP_LEN + 1; i++)
		for (int j = 1; j < MAP_LEN + 1; j++)
			total_score = total_score + map[i][j].see_score();
	return total_score;
}

void MAP::output_record()
{
	ofstream battle_record("battle_record.txt");
	battle_record << "record:\n";
	for (int i = 0; i < history.size(); i++)
	{
		battle_record << i << ":\t";
		battle_record << history[i].place.x << "\t";
		battle_record << history[i].place.y << "\t";
		if (history[i].chess == node::black_node)
			battle_record << "����" << "\n";
		else
			battle_record << "����" << "\n";
	}
	battle_record.close();
}

node MAP::random_judge(node chess)
{
	//MAP test_map;
	vector<coordinate> able_to_set;	/
	//test_map.vec_to_map(map);
	map_stack.push_back(map_to_vec());
	for (int i = 1; i < MAP_LEN + 1; i++)
	{
		for (int j = 1; j < MAP_LEN + 1; j++)
		{
			if (map[i][j].see_node() == node::no_node)
				able_to_set.push_back({ i,j });
		}
	}	 
	while (1)
	{
		if (able_to_set.empty())
			break;
		if (chess == node::black_node)
			chess = node::white_node;
		else
			chess = node::black_node;
		bool sig = false;
		while (!sig && !able_to_set.empty())
		{
			int ran = RandomData(0, able_to_set.size() - 1);
			map[able_to_set[ran].x][able_to_set[ran].y].set_node(chess);
			int deletable = update_state(chess, able_to_set[ran]);
			if (map[able_to_set[ran].x][able_to_set[ran].y].see_qi() == 0 && deletable == 0)
				map[able_to_set[ran].x][able_to_set[ran].y].set_node(node::no_node);
			else
				sig = true;
			//sig = test_map.set_chess(able_to_set[ran].x, able_to_set[ran].y, chess);
			able_to_set.erase(able_to_set.begin() + ran);
		}
	}
	double white_score = 3.75;
	double black_score = 0;
	for (int i = 1; i < MAP_LEN + 1; i++)
	{
		for (int j = 1; j < MAP_LEN + 1; j++)
		{
			if (map[i][j].see_node() == node::black_node)
				black_score = black_score + 1;
			else if (map[i][j].see_node() == node::white_node)
				white_score = white_score + 1;
		}
	}
	vec_to_map(map_stack[map_stack.size() - 1]);
	map_stack.pop_back();
	if (black_score > white_score)
		return node::black_node;
	else
		return node::white_node;
}

void MAP::example1()
{
	for (int i = 10; i <= 14; i++)
	{
		set_chess(10, i, node::black_node);
		set_chess(14, i, node::black_node);
	}
	set_chess(11, 10, node::black_node);
	set_chess(12, 10, node::black_node);
	set_chess(13, 10, node::black_node);
	set_chess(11, 14, node::black_node);
	set_chess(12, 14, node::black_node);
	set_chess(13, 14, node::black_node);
	for (int i = 11; i <= 13; i++)
	{
		set_chess(11, i, node::white_node);
		set_chess(13, i, node::white_node);
	}
	set_chess(12, 11, node::white_node);
	set_chess(12, 13, node::white_node);
	//display_map();
	who_wins();
}

void MAP::example2()
{
	map[1][2].set_node(node::white_node);
	map[1][4].set_node(node::white_node);
	map[1][6].set_node(node::white_node);
	map[1][7].set_node(node::black_node);
	map[1][9].set_node(node::black_node);
	map[1][14].set_node(node::black_node);
	map[1][16].set_node(node::black_node);
	map[2][1].set_node(node::white_node);
	map[2][3].set_node(node::white_node);
	map[2][4].set_node(node::white_node);
	map[2][6].set_node(node::white_node);
	map[2][7].set_node(node::white_node);
	map[2][8].set_node(node::black_node);
	map[2][10].set_node(node::black_node);
	map[2][14].set_node(node::white_node);
	map[2][15].set_node(node::black_node);
	map[2][16].set_node(node::white_node);
	map[2][17].set_node(node::white_node);
	map[2][18].set_node(node::black_node);
	map[3][6].set_node(node::white_node);
	map[3][7].set_node(node::white_node);
	map[3][8].set_node(node::white_node);
	map[3][14].set_node(node::white_node);
	map[3][17].set_node(node::white_node);
	map[3][9].set_node(node::black_node);
	map[3][10].set_node(node::black_node);
	map[3][12].set_node(node::black_node);
	map[3][13].set_node(node::black_node);
	map[3][15].set_node(node::black_node);
	map[3][16].set_node(node::black_node);
	map[4][3].set_node(node::white_node);
	map[4][4].set_node(node::white_node);
	map[4][6].set_node(node::white_node);
	map[4][8].set_node(node::white_node);
	map[4][17].set_node(node::white_node);
	map[4][18].set_node(node::white_node);
	map[4][7].set_node(node::black_node);
	map[4][9].set_node(node::black_node);
	map[4][11].set_node(node::black_node);
	map[4][12].set_node(node::black_node);
	map[4][14].set_node(node::black_node);
	map[4][16].set_node(node::black_node);
	map[5][2].set_node(node::white_node);
	map[5][3].set_node(node::white_node);
	map[5][4].set_node(node::white_node);
	map[5][5].set_node(node::white_node);
	map[5][6].set_node(node::white_node);
	map[5][10].set_node(node::white_node);
	map[5][12].set_node(node::white_node);
	map[5][18].set_node(node::white_node);
	map[5][10].set_node(node::black_node);
	map[5][11].set_node(node::black_node);
	map[5][13].set_node(node::black_node);
	map[5][14].set_node(node::black_node);
	map[5][16].set_node(node::black_node);
	map[5][17].set_node(node::black_node);
	map[6][6].set_node(node::white_node);
	map[6][7].set_node(node::white_node);
	map[6][9].set_node(node::white_node);
	map[6][10].set_node(node::white_node);
	map[6][11].set_node(node::white_node);
	map[6][12].set_node(node::white_node);
	map[6][13].set_node(node::white_node);
	map[6][14].set_node(node::white_node);
	map[6][17].set_node(node::white_node);
	map[6][18].set_node(node::white_node);
	map[6][16].set_node(node::black_node);
	map[6][19].set_node(node::black_node);
	map[7][1].set_node(node::white_node);
	map[7][2].set_node(node::white_node);
	map[7][3].set_node(node::white_node);
	map[7][4].set_node(node::white_node);
	map[7][5].set_node(node::white_node);
	map[7][8].set_node(node::white_node);
	map[7][9].set_node(node::white_node);
	map[7][12].set_node(node::white_node);
	map[7][6].set_node(node::black_node);
	map[7][7].set_node(node::black_node);
	map[7][10].set_node(node::black_node);
	map[7][11].set_node(node::black_node);
	map[7][16].set_node(node::black_node);
	map[7][17].set_node(node::black_node);
	map[7][18].set_node(node::black_node);
	//display_map();
	who_wins();
}
//int main()
//{
//	MAP test_map;
//	test_map.example2();
//	int black = 0;
//	for (int i = 0; i < 100; i++)
//	{
//		node result = test_map.random_judge(node::black_node);
//		if (result == node::black_node)
//			black++;
//	}
//	cout << black << endl;
//	return 0;
//}
//�������Ѿ����޸ģ����ϣ��ʹ��ԭ�ȵ��������������ݲ�����
//�������ź����书�ܣ���˫���������Ż�������һ������ʱ����ֽ���
//���û����Խ��������ڷǷ�λ��ʱ������������Ҫ����û���������
//int main()
//{
//	��������������[1,19]),�����������ӵ�λ��
//	MAP test_map;
//	node i = node::black_node;   //�ڷ�����
//	int judge = 0;
//	while (!test_map.see_finished())
//	{
//		int choice;
//		coordinate place;
//		bool is_successful = false;
//		if (i == node::black_node)
//			cout << "�ڷ����壬��ѡ�������1�����壬2�����ţ�3�����䣬4�����壬5���Է����壩��";
//		else
//			cout << "�׷����壬��ѡ�������1�����壬2�����ţ�3�����䣬4�����壬5���Է����壩��";
//		cin >> choice;
//		switch (choice)
//		{
//		case 1:
//			while (!is_successful)
//			{
//				cout << "���������������(x,y)��";
//				cin >> place.x;
//				cin >> place.y;
//				is_successful = test_map.set_chess(place.x, place.y, i);
//			}
//			judge = 0;
//			break;
//		case 2:
//			judge++;
//			break;
//		case 3:
//			test_map.finish();
//			if (i == node::black_node)
//				cout << "�׷�ʤ��";
//			else
//				cout << "�ڷ�ʤ��";
//			break;
//		case 4:
//			test_map.repetance(i);
//			continue;
//			break;
//		default:
//			node j;
//			if (i == node::black_node)
//				j = node::white_node;
//			else
//				j = node::black_node;
//			test_map.repetance(j);
//			i = j;
//			continue;
//		}
//		if (judge == 2)						//�������ţ���ֽ���
//		{
//			test_map.finish();
//			test_map.who_wins();
//		}
//		if (i == node::black_node)
//			i = node::white_node;
//		else
//			i = node::black_node;
//	}
//	return 0;
//}
