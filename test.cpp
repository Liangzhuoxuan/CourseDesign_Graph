#include<bits/stdc++.h>
using namespace std;

typedef struct{
	int Num; //结点的编号 
	int weight; // 边的权重 
}node;

int main(){
	map<int, vector<node>> mm;
	node n;
	n.Num = 1;
	n.weight = 1;
	vector<node> v;
	mm[1] = v;

	cout << mm[1].back() << endl;
}