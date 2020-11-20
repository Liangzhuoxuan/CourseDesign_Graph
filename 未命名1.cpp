#include<bits/stdc++.h>
using namespace std;

#define dingdianshu 25
#define inf 66666
vector <int> jingguo;// 记录经过的地点
int min_sum = inf; // 记录经过路径权重之和的最小值;
int visited[25];//记录是否访问过，访问过为 1，防止成环
vector <int> memory_vector;// 记录经过的结点 

int graph_arr[26][26] =  {
//	{000, 111, 222, 333, 444, 555, 666, 777, 888, 999, 010, 011, 012, 013, 014, 015, 016, 017, 018, 019, 020, 021, 022, 023, 024, 025}
        {inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
        {inf, inf, 430, 415, inf, inf, inf, inf, inf, inf, inf, inf, inf, 50, inf, inf, 530, inf, inf, inf, inf, inf, inf, inf, 635, inf},
        {inf, 430, inf, inf, 200, inf, inf, 357, inf, inf, inf, inf, 350, inf, inf, inf, inf, inf, inf, inf, inf, 520, 400, inf, inf, inf},
        {inf, 415, inf, inf, 20, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
        {inf, inf, 200, 20, inf, 20, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
        {inf, inf, inf, inf, 20, inf, inf, inf, inf, inf, inf, inf, 78, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
        {inf, inf, inf, inf, inf, inf, inf, 20, inf, inf, inf, inf, 78, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
        {inf, inf, 357, inf, inf, inf, 20, inf, 20, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf, inf},
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

typedef struct ArcNode{
    int Num; //顶点的编号
    int weight;//边的权重
    struct ArcNode * nextarc;
}ArcNode;

typedef struct VNode{
    int head_num;//结点的编号
    ArcNode * firstarc; //指向的第一个结点
}VNode;

VNode vnode[26];

//构建邻接表
void init_linjiebiao(){
    for(int i=1;i<26;i++){
        vnode[i].head_num = i;
        int counter = 1;
        ArcNode *temp_p;
        for(int j=1;j<26;j++){
            if(graph_arr[i][j] != inf){
                if(counter == 1){
                    ArcNode *p = new ArcNode;
                    p->Num = j;
                    p->weight = graph_arr[i][j];
                    vnode[i].firstarc = p;
                    temp_p = p;
                    counter++;
                }
                else{
                    ArcNode *p2;
                    p2 = temp_p;
                    ArcNode *node = new ArcNode;
                    node->Num = j;
                    node->weight = graph_arr[i][j];
                    node->nextarc = NULL;
                    ArcNode *_p = vnode[i].firstarc;
                    // 找到要指向它的前一个结点
                    for(int k=2;k<counter;k++){
                        _p = _p->nextarc;
                    }
                    _p->nextarc = node;//接上当前的结点
                    temp_p = node;
                    counter++;
                }
            }
        }
    }

}

void check_linjiebiao(){
    //打印检验构建的邻接表
    for(int i=1;i<26;i++){
        cout << vnode[i].head_num << ' ';
        ArcNode *p = vnode[i].firstarc;
        while(p!=NULL){
            cout << p->Num << ' ';
            p = p->nextarc;
        }
        cout << endl;
    }
}



void dfs_arr(int to, int weight_sum, int _end){
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
                dfs_arr(j, graph_arr[to][j] + weight_sum, _end);
                memory_vector.pop_back();
                visited[j] = 0;//回溯
            }
        }
    }
}

void get_path_by_arr(int start, int end){
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
                dfs_arr(j, graph_arr[start][j], end); // 递归
                memory_vector.pop_back();
                visited[j] = 0;// 回溯
            }
        }
    }
}

void dfs_AdjList(int to, int weight_sum, int _end){
    if(to == _end){
        if (weight_sum < min_sum){
            min_sum = weight_sum;
            jingguo = memory_vector; // deepcopy
        }
        return ;
    }
    ArcNode *p = vnode[to].firstarc;
    while (p!=NULL){
        int number = p->Num;
        if(!visited[number]){
            visited[number] = 1;
            int weight = p->weight;
            memory_vector.push_back(number);
            dfs_AdjList(number, weight+weight_sum, _end);
            memory_vector.pop_back();
            visited[number] = 0;
        }
        p = p->nextarc;
    }


}

void get_path_by_adjList(int start, int end){
    //判断是否是直接相连
//    int temp = vnode[start].head_num;
    ArcNode *node = vnode[start].firstarc;
    ArcNode *p = new ArcNode;
    p = node;
    bool flag = false;
    while(p!=NULL){ //while(p)不行，while(p!=NULL)才行，吐了 
        if(p->Num == end){
            flag = true;
            jingguo.push_back(p->Num);
            min_sum = p->weight; 
            break;
        }
        p = p->nextarc;
    }
    if(flag)
        return ;

    ArcNode *p1 = vnode[start].firstarc;
    while(p1!=NULL){
    	int number = p1->Num;
	    if(!visited[number]){
	        visited[number] = 1;
	        int weight = p1->weight;
	        memory_vector.push_back(number);
	        dfs_AdjList(number, weight, end);
	        memory_vector.pop_back();
	        visited[number] = 0;
	    }
    	p1 = p1->nextarc;
    }

}

void initalize(){
	/*初始化函数，初始化所有的全局变量*/
	memset(visited, 0, sizeof(visited));
    min_sum = inf;
    memory_vector.clear();
    jingguo.clear();
}

void print_path_info(int a, int b, int method){
	if(method)
		cout << "使用邻接矩阵得到的结果为" << endl;
	else
		cout << "使用邻接表得到的结果为" << endl;
	
	// 输出经过的路径
    cout << a << "->";
    for(int k=0;k<=jingguo.size()-1;k++){
        if(k!=jingguo.size()-1)
            cout << jingguo[k] << "->";
        else
            cout << jingguo[k] << endl;
    }
    
    cout << min_sum << endl;
}

int get_ans_from_zhonghelou(){
	//广度优先遍历无向图 
	queue<int> myQueue;
	myQueue.push(1); // 起始点入队
	while(!myQueue.empty()){
		int row = myQueue.front();
		myQueue.pop();
		int min_index = inf; //记录权重和最小的下标 
		int mmin = inf; //记录当前最小的权重 
		for(int i=1;i<26;i++){
			//如果连通 
			if(graph_arr[row][i] != inf){
				myQueue.push(i);
				int weight = graph_arr[row][i];
				if(weight < mmin){
					mmin = weight;
					min_index = i;
				}
				 
			}
		}
		
	}
}

int main(){
    init_linjiebiao(); //初始化邻接表
//    check_linjiebiao(); //打印邻接表
    while(true){
        cout << "请输入你想要看的功能的编号\n(1)查看综合楼到其余各处的最短路径\n(2)查看任意两个地点之间的最短路径\n";
        cout << "(3)你来输入起点、终点、必经点和必避点, 我帮你找最短路径" << endl;
        int switch_ = 0;
        cout << "请输入你想要看的功能的编号1，2 or 3: " << endl;
        scanf("%d", &switch_);
        int a, b;
        if(switch_ == 2){
        	cout << "请选择"
            cout << "请输入两个地点 a, b的编号:";
            scanf("%d %d", &a, &b);
            //使用邻接表 
            get_path_by_adjList(a, b);
            print_path_info(a, b, 0)
            initalize(); // 把全局变量初始化一遍
            //使用邻接矩阵 
			get_path_by_arr(a, b);
			print_path_info(a, b, 1);
            
        }
        else if(switch_ == 1){
        	int ans;
        	ans = ;
        	cout << "从综合楼到" << ans << "的距离最短" << endl;
        	cout << "最短的距离为" << min_sum << endl; 
		}
		else{
			;
		}
    }

    return 0;
}
