#include<bits/stdc++.h>
using namespace std;

#define dingdianshu 25
#define inf 66666
vector <int> jingguo;// ��¼�����ĵص�
int min_sum = inf; // ��¼����·��Ȩ��֮�͵���Сֵ;
int visited[25];//��¼�Ƿ���ʹ������ʹ�Ϊ 1����ֹ�ɻ�
vector <int> memory_vector;// ��¼�����Ľ�� 

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
    int Num; //����ı��
    int weight;//�ߵ�Ȩ��
    struct ArcNode * nextarc;
}ArcNode;

typedef struct VNode{
    int head_num;//���ı��
    ArcNode * firstarc; //ָ��ĵ�һ�����
}VNode;

VNode vnode[26];

//�����ڽӱ�
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
                    // �ҵ�Ҫָ������ǰһ�����
                    for(int k=2;k<counter;k++){
                        _p = _p->nextarc;
                    }
                    _p->nextarc = node;//���ϵ�ǰ�Ľ��
                    temp_p = node;
                    counter++;
                }
            }
        }
    }

}

void check_linjiebiao(){
    //��ӡ���鹹�����ڽӱ�
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
    //�ݹ�������ӽڵ�Ϊ�յ�
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
                visited[j] = 1;//���
                memory_vector.push_back(j);
                dfs_arr(j, graph_arr[to][j] + weight_sum, _end);
                memory_vector.pop_back();
                visited[j] = 0;//����
            }
        }
    }
}

void get_path_by_arr(int start, int end){
    //������������ڣ�ֱ�ӳ���
    if(graph_arr[start][end] != inf){
        min_sum = graph_arr[start][end];
        jingguo.push_back(end);
        return;
    }

    //������ȣ�������еĿ���
    for(int j=1;j<26;j++){
        if(graph_arr[start][j] != inf){
            //���û���߹������
            if(!visited[j]){
                visited[j] = 1; // ����������ˣ����
                memory_vector.push_back(j);
                dfs_arr(j, graph_arr[start][j], end); // �ݹ�
                memory_vector.pop_back();
                visited[j] = 0;// ����
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
    //�ж��Ƿ���ֱ������
//    int temp = vnode[start].head_num;
    ArcNode *node = vnode[start].firstarc;
    ArcNode *p = new ArcNode;
    p = node;
    bool flag = false;
    while(p!=NULL){ //while(p)���У�while(p!=NULL)���У����� 
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
	/*��ʼ����������ʼ�����е�ȫ�ֱ���*/
	memset(visited, 0, sizeof(visited));
    min_sum = inf;
    memory_vector.clear();
    jingguo.clear();
}

void print_path_info(int a, int b, int method){
	if(method)
		cout << "ʹ���ڽӾ���õ��Ľ��Ϊ" << endl;
	else
		cout << "ʹ���ڽӱ�õ��Ľ��Ϊ" << endl;
	
	// ���������·��
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
	//������ȱ�������ͼ 
	queue<int> myQueue;
	myQueue.push(1); // ��ʼ�����
	while(!myQueue.empty()){
		int row = myQueue.front();
		myQueue.pop();
		int min_index = inf; //��¼Ȩ�غ���С���±� 
		int mmin = inf; //��¼��ǰ��С��Ȩ�� 
		for(int i=1;i<26;i++){
			//�����ͨ 
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
    init_linjiebiao(); //��ʼ���ڽӱ�
//    check_linjiebiao(); //��ӡ�ڽӱ�
    while(true){
        cout << "����������Ҫ���Ĺ��ܵı��\n(1)�鿴�ۺ�¥��������������·��\n(2)�鿴���������ص�֮������·��\n";
        cout << "(3)����������㡢�յ㡢�ؾ���ͱرܵ�, �Ұ��������·��" << endl;
        int switch_ = 0;
        cout << "����������Ҫ���Ĺ��ܵı��1��2 or 3: " << endl;
        scanf("%d", &switch_);
        int a, b;
        if(switch_ == 2){
        	cout << "��ѡ��"
            cout << "�����������ص� a, b�ı��:";
            scanf("%d %d", &a, &b);
            //ʹ���ڽӱ� 
            get_path_by_adjList(a, b);
            print_path_info(a, b, 0)
            initalize(); // ��ȫ�ֱ�����ʼ��һ��
            //ʹ���ڽӾ��� 
			get_path_by_arr(a, b);
			print_path_info(a, b, 1);
            
        }
        else if(switch_ == 1){
        	int ans;
        	ans = ;
        	cout << "���ۺ�¥��" << ans << "�ľ������" << endl;
        	cout << "��̵ľ���Ϊ" << min_sum << endl; 
		}
		else{
			;
		}
    }

    return 0;
}
