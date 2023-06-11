#pragma once
#include<memory>
#include<vector>
#include"qizi.h"
#define MAX_SEARCH 20000

//���ؿ���������V1.1

class MCT_node {
	friend class MCT;
public:
	MCT_node() :type(false), fully_expanded(false), new_stone({0, 0}), white_win(0), black_win(0), map(), leaves() {};
	//����һ��Ҷ�ӽڵ㣬�ɹ��Ұ���ʤ����1���ɹ��Һ���ʤ����2�� ʧ�ܷ���0
	int create_leaf(coordinate stone);				
	//�ͷ�Ҷ�ӽڵ㣬�����ͷŵĽڵ���
	int free_leaves();								
	//�ͷų�����һ��ѡ�����Ҷ�ӽڵ㣬�������ͷŵĽڵ���
	int free_leaves_but_next(int next);				
	//ѡ���������Ϊ��һ���ڵ�
	int find_next();								
	//UCTѡ��Ҷ�ӽڵ�
	int UCT();
	//��ǰ�ڵ㿪ʼ����һ�����ؿ�������������true��ʾ����ʤ����false��ʾ����ʤ��
	bool search();

private:
	bool type;							//true��ʾ�����ж��ڵ㣬false��ʾ�����ж��ڵ�
	bool fully_expanded = false;		//�Ƿ�Ϊ��ȫչ���ڵ�
	coordinate new_stone = { 0, 0 };	//��ȸ���㣬����������
	int white_win = 0;					//���巽��ʤ����
	int black_win = 0;					//���巽��ʤ����
	MAP map;							//��ּ�¼
	std::vector<std::unique_ptr<MCT_node>> leaves;		//Ҷ�ӽڵ�
};

class MCT {
public:
	MCT() :root(std::unique_ptr<MCT_node>(new MCT_node)) {};
	//���ؿ�������������ֱ���ڵ�������MAX_NODE
	coordinate MCTS(coordinate human);

private:
	std::unique_ptr<MCT_node> root;		//��ǰ���ڵ�
};