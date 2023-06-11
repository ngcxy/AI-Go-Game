#pragma once
#include<memory>
#include<vector>
#include"qizi.h"

#define INF 1000000.0

//V3.2
//围棋的最大最小树节点
class AI_node {
	friend class AI;
public:
	//构造函数
	AI_node() :
		map(MAP()), type(false), depth(0), new_stone({-1, -1}), alpha(-(INF)), beta(INF), next_node(-1), min_x(-1), max_x(-1), min_y(-1), max_y(-1) { };
	//给定坐标创建对应子节点
	bool create_child_node(coordinate stone);
	//释放子节点对应内存,返回释放的节点数
	int free_child();	
	//释放除下一步采用的子节点外全部子节点,返回释放的节点数
	int free_child_but_next();


private:
	MAP map;										//记录当前棋盘状态
	int depth;										//当前节点深度
	bool type;										//true表示白棋最大值节点，false表示黑棋最小值节点
	coordinate new_stone;							//此节点相对父节点多下的一步棋
	double alpha;									//下界
	double beta;									//上界
	int next_node;									//下一步预测值，用在children中的下标表示
	int min_x, max_x, min_y, max_y;					//搜索范围
	std::vector<std::unique_ptr<AI_node>> children;	//子节点列表
};

//alpha-beta剪枝算法实现围棋AI
class AI {
public:
	AI() :root(new AI_node()), max_depth(4), node_cnt(1), max_node(20000) { };
	coordinate AI_for_next(coordinate human);					//根据人类棋手的输入给出下一步棋
	coordinate None_for_next();									//人类棋手虚着应对
	void undo(MAP& input_map);									//人类棋手悔棋
	double Max_Value_Pruning(std::unique_ptr<AI_node>& head, double a, double b);	//最大值节点的剪枝算法
	double Min_Value_Pruning(std::unique_ptr<AI_node>& head, double a, double b);	//最小值节点的剪枝算法
	void mode(int i);											//控制节点数完成难度设置
private:
	std::unique_ptr<AI_node> root;								//当前根节点
	int max_node = 20000;										//最大节点数
	int max_depth = 4;											//最大搜索深度
	int node_cnt = 1;											//当前树中节点数
};