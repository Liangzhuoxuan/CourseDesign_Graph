#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector> 
#include<string>
#include<map>
using namespace std;

#define dingdianshu 25
#define inf 66666
vector <int> jingguo;// 记录经过的地点
int min_sum = inf; // 记录经过路径权重之和的最小值; 
int visited[25];//记录是否访问过，访问过为 1，防止成环 
vector <int> memory_vector;// 记录经过的结点 

int graph_arr[26][26] =  {
//	{000, 001, 002, 003, 004, 005, 006, 007, 008, 009, 010, 011, 012, 013, 014, 015, 016, 017, 018, 019, 020, 021, 022, 023, 024, 025}
	{inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
	{inf, inf, 430, 415, inf, inf, inf, inf, inf, inf, inf, inf, inf, 50, inf, inf, 530, inf, inf, inf, inf, inf, inf, inf, 635, inf},
	{inf, 430, inf, inf, 200, inf, inf, 357, inf, inf, inf, inf, 350, inf, inf, inf, inf, inf, inf, inf, inf, 520, 400, inf, inf, inf},
	{inf, 415, inf, inf, 20, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
	{inf, inf, 200, 20, inf, 20, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
	{inf, inf, inf, inf, 20, inf, inf, inf, inf, inf, inf, inf, 78, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
	{inf, inf, inf, inf, inf, inf, inf, 20, inf, inf, inf, inf, 78, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
	{inf, inf, inf, inf, inf, inf, 20, inf, 20, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
	{inf, inf, inf, inf, inf, inf, inf, 20, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 100, inf, inf, inf, inf},
	{inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 80, 400, inf, inf, 300, inf, inf, inf, inf, inf, inf, inf, inf, inf, 90, inf},
	{inf, inf, inf, inf, inf, inf, inf, inf, inf, 80, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 200},
	{inf, inf, inf, inf, inf, inf, inf, inf, inf, 400, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 40},
	{inf, inf, 350, inf, inf, 78, 78, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
	{inf, 50, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
	{inf, inf, inf, inf, inf, inf, inf, inf, inf, 300, inf, inf, inf, inf, inf, inf, 240, inf, inf, inf, 220, inf, inf, inf, inf, inf},
	{inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 200, 100, inf, inf, inf, 185, 190, inf, inf},
	{inf, 530, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 240, inf, inf, inf, inf, 130, 80, inf, inf, inf, inf, inf},
	{inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 200, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
	{inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 100, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
	{inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 130, inf, inf, inf, inf, inf, inf, inf, inf, inf},
	{inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 220, inf, 80, inf, inf, inf, inf, inf, inf, inf, inf, inf},
	{inf, inf, 520, inf, inf, inf, inf, inf, 100, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 300, inf, inf, inf},
	{inf, inf, 400, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 185, inf, inf, inf, inf, inf, 300, inf, 120, inf, inf},
	{inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 190, inf, inf, inf, inf, inf, inf, 120, inf, inf, inf},
	{inf, 635, inf, inf, inf, inf, inf, inf, inf, 90, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
	{inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, 200, 40, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
	};

typedef struct {
	int Num; //结点的编号 
	int weight; // 边的权重 
}node;





void get_AdjList(){

}

void dfs(int to, int weight_sum, int _end){
	//递归出口其子节点为终点 
	if(to == _end){
		if (weight_sum < min_sum){
			min_sum = weight_sum;
			jingguo = memory_vector;
		}
		return ;
	}
	
	for(int j=1;j<26;j++){
		if(graph_arr[to][j] != inf){
			if(!visited[j]){
				visited[j] = 1;//标记 
				memory_vector.push_back(j);
				dfs(j, graph_arr[to][j] + weight_sum, _end);
				memory_vector.pop_back();
				visited[j] = 0;//回溯 
			}
		}
	}
}

void get_path(int start, int end){
	//如果两个点相邻，直接出来 
	if(graph_arr[start][end] != inf){
		min_sum = graph_arr[start][end];
		jingguo.push_back(end);
		return;
	}
	
	//深度优先，穷举所有的可能 
	for(int j=1;j<26;j++){
		if(graph_arr[start][j] != inf){	
			//如果没有走过这个点	
			if(!visited[j]){
				visited[j] = 1; // 走了这个点了，标记 
				memory_vector.push_back(j);
				dfs(j, graph_arr[start][j], end); // 递归 
				memory_vector.pop_back();
				visited[j] = 0;// 回溯 
			}
		}
	}	
}

int main(){
	// map<vector<int>, vector<int>> mm;
	while(true){
		memset(visited, 0, sizeof(visited));
		min_sum = inf;
		memory_vector.clear();
		jingguo.clear();
		cout << "请输入你想要看的功能的编号\n(1)查看综合楼到其余各处的最短路径\n(2)查看任意两个地点之间的最短路径\n";
		cout << "(3)你来输入起点、终点、必经点和必避点, 我帮你找最短路径" << endl;
		int switch_ = 0;
		cout << "请输入你想要看的功能的编号1，2 or 3: " << endl;
		scanf("%d", &switch_);
		int a, b;
		if(switch_ == 2){
			cout << "请输入两个地点 a, b的编号:";
			scanf("%d %d", &a, &b);
			get_path(a, b);
			// 输出经过的路径 
			cout << a << "->";
			for(int k=0;k<=jingguo.size()-1;k++){
				if(k!=jingguo.size()-1)
					cout << jingguo[k] << "->";
				else
					cout << jingguo[k] << endl;
			}
				
			cout << min_sum <<endl;
		}
	}
	
	return 0;
}