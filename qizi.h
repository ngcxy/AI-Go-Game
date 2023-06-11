#pragma once
#include <vector>
#include <string>
#define MAP_LEN 19
#define MAX_STORE 100

enum class node {
	not_node = -1, no_node = 0, black_node = 1, white_node = 2    //���Ӵ���
};

struct coordinate    //����
{
	void operator++();
	bool operator==(coordinate& i);
	int x;
	int y;
};

struct step {											//�����ʷ��¼�ĸ�ʽ
	coordinate place;									//�����λ��
	node chess;											//���ӵ�����
};

struct estimate_score									//������������ר��
{
	coordinate place;
	double score;
};
int RandomData(int min, int max);
std::vector<coordinate> create_neighbors(coordinate center);			//�����������ĵ�4�����ڵ�����������
std::vector<coordinate> create_remote_neighbors(coordinate center);		//�����������ĵ�4���Խ��ߵ�����������
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
	int qi;												//���ӵ���
	int is_checked;										//�Ƿ񱻼���
	//int is_forbidden;									//�Ƿ�Ϊ�����
	double score;										//�ô������Ʒ���
};



class MAP
{
	friend class Game_window;
	friend class AI;
public:
	MAP();												//��ʼ��������������û���κ�����
	void reset_map();									//��������
	void init();
	//void display_map();
	std::vector<node> map_to_vec();						//��������Ϣ��ÿ��λ������ʲô����)����һ������ת��Ϊһ��vector���洢��map_stack��
	void vec_to_map(std::vector<node> one_map);			//������map_to_vecת���õ���һά����ת��ΪĬ�ϵĶ�ά����
	bool is_jie();										//�ж��Ƿ���
	bool set_chess(int x, int y, node chess);			//����������������
	int update_state(node chess, coordinate place);		//��������״̬������������Է������ӣ��򷵻�1�����򷵻�0
	void find_qi(int x, int y);							//Ѱ��ĳ������ĳƬ�����ӵ���������Ƭ�������ӵ��������chess_stack�У�����Χ�Ŀ�λ���������hole_stack��
	void delete_node(coordinate x);						//��������ɾ�����Ե�������
	//bool check_forbidden(coordinate x, node chess);     //�ж�ĳ����λ�ǲ��ǽ���㣬����ǽ���㣬���޸�is_forbiddenΪ1������true��������ǽ���㣬�򷵻�false�����޸�is_forbidden��ֵ
	//bool is_dead(int x, int y);						//�ж�ĳһƬ�����ǲ������壨������ֽ���ʱִ�У�
	//bool is_an_eye(coordinate x);						//�ж�ĳ����λ�ǲ�������
	//int white_or_black(coordinate x);					//�ж�ĳ����λ�ɺڷ����ǰ׷�ռ�ݣ�����Ǻڷ�ռ�ݣ��򷵻�1������ǰ׷�ռ�ݣ��򷵻�2������ڰ������ƾ����У��򷵻�0
	void who_wins();									//����ʤ����չʾ�ڰ������ķ���
	bool repetance(node chess);							//���庯��������������������һ��
	void compute_score(node chess, coordinate place, const int is_delete);	//���㣨��������ĳ�����Ӷ��������̵�Ӱ�죬�涨�����ʩ������Ӱ�죬�����ʩ�Ӹ���Ӱ�죬�����Ӵ����������ߣ���is_delete������-1��������1���󣬸ú��������������������Ӷ����̵�Ӱ��
	double map_score();									//���㵱ǰ�����ÿ��������Ʒ���
	bool see_finished() { return is_finished; };
	void finish() { is_finished = true; };				
	void output_record();
	node random_judge(node chess);						//���������������������������ڷ���׷���������node���Ͳ�������Ϊ�ڷ���ʤ���򷵻�black_node�����򷵻�white_node 
	void example1();									//��������1
	void example2();									//��������2
private:
	qizi map[MAP_LEN + 2][MAP_LEN + 2];
	bool is_finished;									//����Ƿ�����ı�־
	std::vector<coordinate> delete_list;				//�洢��ɾ�������������
	std::vector<coordinate> chess_stack, hole_stack;
	std::vector<std::vector<node>> map_stack;			//��������ΪMAX_STORE
	std::vector<step> history;							//�洢�����ʷ��¼��������û����������
	int step_num;										//����ܹ������˶��ٲ�
};
