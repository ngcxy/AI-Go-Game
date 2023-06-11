#include"AI.h"
#include<iostream>

//V3.2

bool AI_node::create_child_node(coordinate stone) {
	std::cout << depth << "\t" << children.size() << std::endl;
	std::unique_ptr<AI_node> t(new AI_node());
	t->map = map;
	if (t->map.set_chess(stone.x, stone.y, type ? (node::white_node) : (node::black_node))) {
		t->alpha = alpha;
		t->beta = beta;
		t->type = !type;
		t->depth = depth + 1;
		t->new_stone = stone;
		t->next_node = -1;
		t->min_x = ((stone.x - 2) < 1) ? 1 : stone.x - 3;
		t->max_x = ((stone.x + 2) > 19) ? 19 : stone.x + 3;
		t->min_y = ((stone.y - 2) < 1) ? 1 : stone.y - 3;
		t->max_y = ((stone.y + 2) > 19) ? 19 : stone.y + 3;
		children.push_back(std::unique_ptr<AI_node>(t.release()));
		return true;
	}
	t.reset();
	return false;
}

int AI_node::free_child() {
	int cnt = 0;
	for (auto& i : children) {
		cnt += i->free_child();
		i.reset();
		cnt++;
	}
	return cnt;
}

int AI_node::free_child_but_next() {
	int cnt = 0;
	for (int i = 0; i < children.size(); i++) {
		if (i == next_node)
			continue;
		cnt += children[i]->free_child();
		children[i].reset();
		cnt++;
	}
	return cnt;
}

coordinate AI::AI_for_next(coordinate human) {
	coordinate t;
	int pre_cnt = 0;
	root->next_node = -1;
	for (int i = 0; i < root->children.size(); i++) {
		t = root->children[i]->new_stone;
		if (t.x == human.x && t.y == human.y) {
			root->next_node = i;
			break;
		}
	}
	if (root->next_node == -1) {
		root->next_node = root->children.size();
		root->create_child_node(human);
		node_cnt++;
	}
	node_cnt -= root->free_child_but_next();
	root.reset(root->children[root->next_node].release());
	node_cnt--;
	for (int i = root->min_x; i <= root->max_x; i++)
		for (int j = root->min_y; j <= root->max_y; j++)
			if (root->map.map[i][j].see_node() == node::no_node)
				pre_cnt++;
	if (pre_cnt > 21)
		max_depth = 4;
	else if (pre_cnt > 15)
		max_depth = 5;
	else if (pre_cnt > 9)
		max_depth = 6;
	else if (pre_cnt > 7)
		max_depth = 7;
	else if (pre_cnt > 6)
		max_depth = 8;
	else
		max_depth = 8;
	root->alpha = Max_Value_Pruning(root, -INF, INF);
	node_cnt -= root->free_child_but_next();
	if (root->next_node == -1) {
		node_cnt -= root->free_child();
		root->children.clear();
		root->type = false;
		root->alpha = -(INF);
		root->beta = INF;
		root->next_node = -1;
		return { 0, 0 };
	}
	root.reset(root->children[root->next_node].release());
	node_cnt--;
	return root->new_stone;
}

coordinate AI::None_for_next() {
	int pre_cnt = 0;
	node_cnt -= root->free_child();
	root->children.clear();
	root->type = true;
	root->alpha = -(INF);
	root->beta = INF;
	root->next_node = -1;
	for (int i = root->min_x; i <= root->max_x; i++)
		for (int j = root->min_y; j <= root->max_y; j++)
			if (root->map.map[i][j].see_node() == node::no_node)
				pre_cnt++;
	if (pre_cnt > 12)
		max_depth = 4;
	else if (pre_cnt > 8)
		max_depth = 5;
	else if (pre_cnt > 6)
		max_depth = 6;
	else if (pre_cnt > 5)
		max_depth = 7;
	else
		max_depth = 8;
	root->alpha = Max_Value_Pruning(root, -INF, INF);
	node_cnt -= root->free_child_but_next();
	if (root->next_node == -1) {
		node_cnt -= root->free_child();
		root->children.clear();
		root->type = false;
		root->alpha = -(INF);
		root->beta = INF;
		root->next_node = -1;
		return { 0, 0 };
	}
	root.reset(root->children[root->next_node].release());
	node_cnt--;
	return root->new_stone;

}

void AI::undo(MAP& input_map) {
	root->map = input_map;
	root->depth -= 2;
	root->type = false;
	root->alpha = -(INF);
	root->beta = INF;
	root->next_node = -1;
	node_cnt -= root->free_child();
	root->children.clear();
	return;
}

double AI::Max_Value_Pruning(std::unique_ptr<AI_node>& head, double a, double b) {
	if (head->depth == root->depth + max_depth || node_cnt > max_node)
		return -(head->map.map_score());
	double value = -(INF), t;
	int size = head->children.size();
	coordinate c{head->min_x, head->min_y - 1};
	head->next_node = -1;
	head->alpha = a;
	head->beta = b;
	for (int i = 0; i < head->children.size(); i++) {
		c = head->children[i]->new_stone;
		t = Min_Value_Pruning(head->children[i], head->alpha, head->beta);
		if (t > value)
			value = t;
		if (value >= head->beta) {
			head->alpha = value;
			return value;
		}
		if (value > head->alpha) {
			head->next_node = i;
			head->alpha = value;
		}
	}
	for(int j = c.y + 1; j <= head->max_y; j++)
		if (head->create_child_node({ c.x, j })) {
			node_cnt++;
			t = Min_Value_Pruning(head->children[size++], head->alpha, head->beta);
			if (t > value)
				value = t;
			if (value >= head->beta) {
				head->alpha = value;
				return value;
			}
			if (value > head->alpha) {
				head->next_node = size - 1;
				head->alpha = value;
			}
		}
	for (int i = c.x + 1; i <= head->max_x; i++)
		for (int j = head->min_y; j <= head->max_y; j++)
			if (head->create_child_node({ i, j })) {
				node_cnt++;
				t = Min_Value_Pruning(head->children[size++], head->alpha, head->beta);
				if (t > value)
					value = t;
				if (value >= head->beta) {
					head->alpha = value;
					return value;
				}
				if (value > head->alpha) {
					head->next_node = size - 1;
					head->alpha = value;
				}
			}
	while (head->children.empty()) {
		if (head->min_x == 1 && head->max_x == 19 && head->min_y == 1 && head->max_y == 19)
			return -(head->map.map_score());
		if (head->min_x > 1) {
			head->min_x--;
			for (int j = head->min_y; j <= head->max_y; j++)
				if (head->create_child_node({ head->min_x, j })) {
					node_cnt++;
					t = Min_Value_Pruning(head->children[size++], head->alpha, head->beta);
					if (t > value)
						value = t;
					if (value >= head->beta) {
						head->alpha = value;
						return value;
					}
					if (value > head->alpha) {
						head->next_node = size - 1;
						head->alpha = value;
					}
				}
		}
		if (head->max_x < 19) {
			head->max_x++;
			for (int j = head->min_y; j <= head->max_y; j++)
				if (head->create_child_node({ head->max_x, j })) {
					node_cnt++;
					t = Min_Value_Pruning(head->children[size++], head->alpha, head->beta);
					if (t > value)
						value = t;
					if (value >= head->beta) {
						head->alpha = value;
						return value;
					}
					if (value > head->alpha) {
						head->next_node = size - 1;
						head->alpha = value;
					}
				}	
		}
		if (head->min_y > 1) {
			head->min_y--;
			for (int i = head->min_x; i <= head->max_x; i++)
				if (head->create_child_node({ i, head->min_y })) {
					node_cnt++;
					t = Min_Value_Pruning(head->children[size++], head->alpha, head->beta);
					if (t > value)
						value = t;
					if (value >= head->beta) {
						head->alpha = value;
						return value;
					}
					if (value > head->alpha) {
						head->next_node = size - 1;
						head->alpha = value;
					}
				}
		}
		if (head->max_y < 19) {
			head->max_y++;
			for (int i = head->min_x; i <= head->max_x; i++)
				if (head->create_child_node({ i, head->max_y })) {
					node_cnt++;
					t = Min_Value_Pruning(head->children[size++], head->alpha, head->beta);
					if (t > value)
						value = t;
					if (value >= head->beta) {
						head->alpha = value;
						return value;
					}
					if (value > head->alpha) {
						head->next_node = size - 1;
						head->alpha = value;
					}
				}
		}
	}
	return value;
}

double AI::Min_Value_Pruning(std::unique_ptr<AI_node>& head, double a, double b) {
	if (head->depth == root->depth + max_depth || node_cnt > max_node)
		return -(head->map.map_score());
	double value = INF, t;
	int size = head->children.size();
	coordinate c{ head->min_x, head->min_y - 1 };
	head->next_node = -1;
	head->alpha = a;
	head->beta = b;
	for (int i = 0; i < head->children.size(); i++) {
		c = head->children[i]->new_stone;
		t = Max_Value_Pruning(head->children[i], head->alpha, head->beta);
		if (t < value)
			value = t;
		if (value <= head->alpha) {
			head->beta = value;
			return value;
		}
		if (value < head->beta) {
			head->next_node = i;
			head->beta = value;
		}
	}
	for (int j = c.y + 1; j <= head->max_y; j++)
		if (head->create_child_node({ c.x, j })) {
			node_cnt++;
			t = Max_Value_Pruning(head->children[size++], head->alpha, head->beta);
			if (t < value)
				value = t;
			if (value <= head->alpha) {
				head->beta = value;
				return value;
			}
			if (value < head->beta) {
				head->next_node = size - 1;
				head->beta = value;
			}
		}
	for (int i = c.x + 1; i <= head->max_x; i++)
		for (int j = head->min_y; j <= head->max_y; j++)
			if (head->create_child_node({ i, j })) {
				node_cnt++;
				t = Max_Value_Pruning(head->children[size++], head->alpha, head->beta);
				if (t < value)
					value = t;
				if (value <= head->alpha) {
					head->beta = value;
					return value;
				}
				if (value < head->beta) {
					head->next_node = size - 1;
					head->beta = value;
				}
			}
	while (head->children.empty()) {
		if (head->min_x == 1 && head->max_x == 19 && head->min_y == 1 && head->max_y == 19)
			return -(head->map.map_score());
		if (head->min_x > 1) {
			head->min_x--;
			for (int j = head->min_y; j <= head->max_y; j++)
				if (head->create_child_node({ head->min_x, j })) {
					node_cnt++;
					t = Max_Value_Pruning(head->children[size++], head->alpha, head->beta);
					if (t < value)
						value = t;
					if (value <= head->alpha) {
						head->beta = value;
						return value;
					}
					if (value < head->beta) {
						head->next_node = size - 1;
						head->beta = value;
					}
				}
		}
		if (head->max_x < 19) {
			head->max_x++;
			for (int j = head->min_y; j <= head->max_y; j++)
				if (head->create_child_node({ head->max_x, j })) {
					node_cnt++;
					t = Max_Value_Pruning(head->children[size++], head->alpha, head->beta);
					if (t < value)
						value = t;
					if (value <= head->alpha) {
						head->beta = value;
						return value;
					}
					if (value < head->beta) {
						head->next_node = size - 1;
						head->beta = value;
					}
				}
		}
		if (head->min_y > 1) {
			head->min_y--;
			for (int i = head->min_x; i <= head->max_x; i++)
				if (head->create_child_node({ i, head->min_y })) {
					node_cnt++;
					t = Max_Value_Pruning(head->children[size++], head->alpha, head->beta);
					if (t < value)
						value = t;
					if (value <= head->alpha) {
						head->beta = value;
						return value;
					}
					if (value < head->beta) {
						head->next_node = size - 1;
						head->beta = value;
					}
				}
		}
		if (head->max_y < 19) {
			head->max_y++;
			for (int i = head->min_x; i <= head->max_x; i++)
				if (head->create_child_node({ i, head->max_y })) {
					node_cnt++;
					t = Max_Value_Pruning(head->children[size++], head->alpha, head->beta);
					if (t < value)
						value = t;
					if (value <= head->alpha) {
						head->beta = value;
						return value;
					}
					if (value < head->beta) {
						head->next_node = size - 1;
						head->beta = value;
					}
				}
		}
	}
	return value;
}

void AI::mode(int i) {
	max_node = i * 10000;
	return;
}