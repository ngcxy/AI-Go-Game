#pragma once
#include<memory>
#include<vector>
#include"qizi.h"

#define INF 1000000.0

//V3.2
//Χ��������С���ڵ�
class AI_node {
	friend class AI;
public:
	//���캯��
	AI_node() :
		map(MAP()), type(false), depth(0), new_stone({-1, -1}), alpha(-(INF)), beta(INF), next_node(-1), min_x(-1), max_x(-1), min_y(-1), max_y(-1) { };
	//�������괴����Ӧ�ӽڵ�
	bool create_child_node(coordinate stone);
	//�ͷ��ӽڵ��Ӧ�ڴ�,�����ͷŵĽڵ���
	int free_child();	
	//�ͷų���һ�����õ��ӽڵ���ȫ���ӽڵ�,�����ͷŵĽڵ���
	int free_child_but_next();


private:
	MAP map;										//��¼��ǰ����״̬
	int depth;										//��ǰ�ڵ����
	bool type;										//true��ʾ�������ֵ�ڵ㣬false��ʾ������Сֵ�ڵ�
	coordinate new_stone;							//�˽ڵ���Ը��ڵ���µ�һ����
	double alpha;									//�½�
	double beta;									//�Ͻ�
	int next_node;									//��һ��Ԥ��ֵ������children�е��±��ʾ
	int min_x, max_x, min_y, max_y;					//������Χ
	std::vector<std::unique_ptr<AI_node>> children;	//�ӽڵ��б�
};

//alpha-beta��֦�㷨ʵ��Χ��AI
class AI {
public:
	AI() :root(new AI_node()), max_depth(4), node_cnt(1), max_node(20000) { };
	coordinate AI_for_next(coordinate human);					//�����������ֵ����������һ����
	coordinate None_for_next();									//������������Ӧ��
	void undo(MAP& input_map);									//�������ֻ���
	double Max_Value_Pruning(std::unique_ptr<AI_node>& head, double a, double b);	//���ֵ�ڵ�ļ�֦�㷨
	double Min_Value_Pruning(std::unique_ptr<AI_node>& head, double a, double b);	//��Сֵ�ڵ�ļ�֦�㷨
	void mode(int i);											//���ƽڵ�������Ѷ�����
private:
	std::unique_ptr<AI_node> root;								//��ǰ���ڵ�
	int max_node = 20000;										//���ڵ���
	int max_depth = 4;											//����������
	int node_cnt = 1;											//��ǰ���нڵ���
};