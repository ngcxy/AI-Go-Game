#pragma once
#include<memory>
#include<vector>
#include"qizi.h"
#define MAX_SEARCH 20000

//蒙特卡洛树搜索V1.1

class MCT_node {
	friend class MCT;
public:
	MCT_node() :type(false), fully_expanded(false), new_stone({0, 0}), white_win(0), black_win(0), map(), leaves() {};
	//创建一个叶子节点，成功且白棋胜返回1，成功且黑棋胜返回2， 失败返回0
	int create_leaf(coordinate stone);				
	//释放叶子节点，返回释放的节点数
	int free_leaves();								
	//释放除了下一步选择外的叶子节点，返回已释放的节点数
	int free_leaves_but_next(int next);				
	//选择次数最多的为下一步节点
	int find_next();								
	//UCT选择叶子节点
	int UCT();
	//当前节点开始进行一次蒙特卡洛搜索，返回true表示白棋胜利，false表示黑棋胜利
	bool search();

private:
	bool type;							//true表示白棋行动节点，false表示黑棋行动节点
	bool fully_expanded = false;		//是否为完全展开节点
	coordinate new_stone = { 0, 0 };	//相比父结点，新增点坐标
	int white_win = 0;					//白棋方获胜次数
	int black_win = 0;					//黑棋方获胜次数
	MAP map;							//棋局记录
	std::vector<std::unique_ptr<MCT_node>> leaves;		//叶子节点
};

class MCT {
public:
	MCT() :root(std::unique_ptr<MCT_node>(new MCT_node)) {};
	//蒙特卡洛搜索，进行直到节点数大于MAX_NODE
	coordinate MCTS(coordinate human);

private:
	std::unique_ptr<MCT_node> root;		//当前根节点
};