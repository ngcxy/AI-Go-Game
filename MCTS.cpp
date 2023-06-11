#include"MCTS.h"
#include<iostream>

//ÃÉÌØ¿¨ÂåÊ÷ËÑË÷V1.0

int MCT_node::create_leaf(coordinate stone) {
	std::unique_ptr<MCT_node> t(new MCT_node());
	t->map = map;
	if (t->map.set_chess(stone.x, stone.y, type ? (node::white_node) : (node::black_node))) {
		t->type = !type;
		t->new_stone = stone;
		if (t->map.random_judge(node::white_node) == node::white_node) {
			t->white_win++;
			white_win++;
			leaves.push_back(std::unique_ptr<MCT_node>(t.release()));
			return 1;
		}
		else {
			t->black_win++;
			black_win++;
			leaves.push_back(std::unique_ptr<MCT_node>(t.release()));
			return -1;
		}
	}
	t.reset();
	return 0;
}

int MCT_node::free_leaves() {
	int cnt = 0;
	for (auto& i : leaves) {
		cnt += i->free_leaves();
		i.reset();
		cnt++;
	}
	return cnt;
}

int MCT_node::free_leaves_but_next(int next) {
	int cnt = 0;
	for (int i = 0; i < leaves.size(); i++) {
		if (i == next)
			continue;
		cnt += leaves[i]->free_leaves();
		leaves[i].reset();
		cnt++;
	}
	return cnt;
}

int MCT_node::find_next() {
	if (leaves.empty())
		return -1;
	int index = 0, cnt = leaves[0]->black_win + leaves[0]->white_win, t;
	for (int i = 1; i < leaves.size(); i++)
		if ((t = (leaves[i]->black_win + leaves[i]->white_win)) > cnt) {
			index = i;
			cnt = t;
		}
	return index;
}

int MCT_node::UCT() {
	if (leaves.empty())
		return -1;
	int index = 0;
	double value = -1, t;
	if (type) {
		for (int i = 0; i < leaves.size(); i++) {
			t = (double)leaves[i]->white_win / (leaves[i]->black_win + leaves[i]->white_win) + 0.8 * sqrt(log(white_win + black_win) / (leaves[i]->black_win + leaves[i]->white_win));
			if (t > value) {
				index = i;
				value = t;
			}
		}
	}
	else {
		for (int i = 0; i < leaves.size(); i++) {
			t = (double)leaves[i]->black_win / (leaves[i]->black_win + leaves[i]->white_win) + 0.8 * sqrt(log(white_win + black_win) / (leaves[i]->black_win + leaves[i]->white_win));
			if (t > value) {
				index = i;
				value = t;
			}
		}
	}
	return index;
}

bool MCT_node::search() {
	int choice;
	if (fully_expanded) {
		choice = UCT();
		if (choice == -1)
			return !type;
		if (leaves[choice]->search()) {
			white_win++;
			return true;
		}
		else {
			black_win++;
			return false;
		}
	}
	coordinate coor = { 1, 1 };
	int i;
	if (!leaves.empty()) {
		coor = leaves[leaves.size() - 1]->new_stone;
		++coor;
	}
	for (; coor.x; ++coor) {
		i = create_leaf(coor);
		if (!i)
			continue;
		else if (i == 1)
			return true;
		else
			return false;
	}
	fully_expanded = true;
	choice = UCT();
	if (choice == -1)
		return !type;
	if (leaves[choice]->search()) {
		white_win++;
		return true;
	}
	else {
		black_win++;
		return false;
	}
}

coordinate MCT::MCTS(coordinate human) {
	int next = -1;
	int t;
	for (int i = 0; i < root->leaves.size(); i++) {
		if (human == root->leaves[i]->new_stone) {
			next = i;
			break;
		}
	}
	if (next == -1) {
		next = root->leaves.size();
		t = root->create_leaf(human);
		if (t == 1)
			root->white_win++;
		else
			root->black_win++;
	}
	root->free_leaves_but_next(next);
	root.reset(root->leaves[next].release());
	for (int i = 0; i < MAX_SEARCH; i++)
		root->search();
	next = root->find_next();
	if (next == -1) {
		root->type = false;
		root->fully_expanded = false;
		root->new_stone = { 0, 0 };
		root->white_win = 0;
		root->black_win = 0;
		return { 0, 0 };
	}
	root->free_leaves_but_next(next);
	root.reset(root->leaves[next].release());
	return root->new_stone;
}
