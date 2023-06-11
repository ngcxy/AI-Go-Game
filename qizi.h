#pragma once
#include <vector>
#include <string>
#define MAP_LEN 19
#define MAX_STORE 100

enum class node {
	not_node = -1, no_node = 0, black_node = 1, white_node = 2    //棋子代码
};

struct coordinate    //坐标
{
	void operator++();
	bool operator==(coordinate& i);
	int x;
	int y;
};

struct step {											//棋局历史记录的格式
	coordinate place;									//下棋的位置
	node chess;											//棋子的种类
};

struct estimate_score									//形势评估函数专用
{
	coordinate place;
	double score;
};
int RandomData(int min, int max);
std::vector<coordinate> create_neighbors(coordinate center);			//产生包含中心点4个相邻点的坐标的容器
std::vector<coordinate> create_remote_neighbors(coordinate center);		//产生包含中心点4个对角线点的坐标的容器
std::vector<estimate_score> place_data(coordinate center);


class qizi
{
public:
	void set_node(node x) { chess = x; };
	node see_node() const { return chess; };
	void checked() { is_checked = 1; };
	int see_checked() { return is_checked; };
	//int see_forbidden() { return is_forbidden; };
	//void forbidden() { is_forbidden = 1; };
	void reset() { qi = 0; is_checked = 0; };
	void set_qi(int x) { qi = x; };
	int see_qi() { return qi; };
	void add_score(double data) { score = score + data; };
	double see_score() { return score; };
	void clear_score() { score = 0; };
private:
	node chess; 
	int qi;												//棋子的气
	int is_checked;										//是否被检查过
	//int is_forbidden;									//是否为禁入点
	double score;										//该处的形势分数
};



class MAP
{
	friend class Game_window;
	friend class AI;
public:
	MAP();												//初始化函数，棋盘上没有任何棋子
	void reset_map();									//重置棋盘
	void init();
	//void display_map();
	std::vector<node> map_to_vec();						//将棋盘信息（每个位置上由什么棋子)按照一定规则转化为一个vector，存储在map_stack中
	void vec_to_map(std::vector<node> one_map);			//将函数map_to_vec转化得到的一维棋盘转化为默认的二维棋盘
	bool is_jie();										//判断是否打劫
	bool set_chess(int x, int y, node chess);			//用于在棋盘上下棋
	int update_state(node chess, coordinate place);		//更新棋盘状态，若可以提掉对方的棋子，则返回1，否则返回0
	void find_qi(int x, int y);							//寻找某个（或某片）棋子的气，将整片关联棋子的坐标存入chess_stack中，其周围的空位的坐标存入hole_stack中
	void delete_node(coordinate x);						//从棋盘中删除被吃掉的棋子
	//bool check_forbidden(coordinate x, node chess);     //判断某个空位是不是禁入点，如果是禁入点，则修改is_forbidden为1，返回true；如果不是禁入点，则返回false，不修改is_forbidden的值
	//bool is_dead(int x, int y);						//判断某一片棋子是不是死棋（仅在棋局结束时执行）
	//bool is_an_eye(coordinate x);						//判断某个空位是不是棋眼
	//int white_or_black(coordinate x);					//判断某个空位由黑方还是白方占据，如果是黑方占据，则返回1，如果是白方占据，则返回2，如果黑白两方势均力敌，则返回0
	void who_wins();									//计算胜负并展示黑白两方的分数
	bool repetance(node chess);							//悔棋函数，参数代表申请悔棋的一方
	void compute_score(node chess, coordinate place, const int is_delete);	//计算（或消除）某个棋子对整个棋盘的影响，规定黑棋会施加正的影响，白棋会施加负的影响，当棋子从棋盘上提走（将is_delete参数置-1，否则置1）后，该函数将会消除被提走棋子对棋盘的影响
	double map_score();									//计算当前棋局上每个点的形势分数
	bool see_finished() { return is_finished; };
	void finish() { is_finished = true; };				
	void output_record();
	node random_judge(node chess);						//输入参数：计算机所属的势力（黑方或白方），返回node类型参数，若为黑方获胜，则返回black_node，否则返回white_node 
	void example1();									//测试用例1
	void example2();									//测试用例2
private:
	qizi map[MAP_LEN + 2][MAP_LEN + 2];
	bool is_finished;									//棋局是否结束的标志
	std::vector<coordinate> delete_list;				//存储被删除点坐标的容器
	std::vector<coordinate> chess_stack, hole_stack;
	std::vector<std::vector<node>> map_stack;			//容量上限为MAX_STORE
	std::vector<step> history;							//存储棋局历史记录的容器，没有容量上限
	int step_num;										//棋局总共进行了多少步
};
