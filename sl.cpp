#include <bits/stdc++.h>
using namespace std;

bool compare(pair<int, int> a, pair<int, int> b){
	return a.second > b.second;
}

int getSLevel(vector<pair<int,int>> &sl, int i, vector<vector<int>> &dag){
    int n = sl.size();
    if(sl[i].second != -1){
	return sl[i].second;
	}
	
    int maxi = 0;
    int child_cnt = 0;
    for(int j = 0; j<n; j++){
        if(i!=j && dag[i][j]!=0){
            child_cnt++;
            maxi = max(getSLevel(sl, j, dag), maxi);
        }
    }
    
    
    if(child_cnt == 0){
        return dag[i][i];
    }else{
    	return maxi + dag[i][i];
    }
}

int main() {
	fstream file;
	file.open("./input.txt");

    int n, e, p;
    cout<<"Enter number of tasks in the dag:\n";
    file>>n;
    cout<<"Enter the number of edges in the dag:\n";
    file>>e;
    cout<<"Enter the number of processors\n";

    vector<vector<int>> dag(n, vector<int>(n, 0));
    cout<<"Enter the dag:\n";
    for(int i = 0; i<e; i++){
        int src, dest, comm_time;
        file>>src>>dest>>comm_time;
        
        dag[src-1][dest-1] = comm_time;
    }
    
    cout<<"Enter the execution times of the tasks\n";
    for(int i = 0; i<n; i++){
        int exec_time;
        file>>exec_time;
        dag[i][i] = exec_time;
    }

    vector<pair<int, int>> sl(n, {-1,-1});
    int cnt = 0;
    
    for(int i = 0; i<n; i++){
	    sl[i] = {i, getSLevel(sl, i, dag)};
	    cout<<endl;
    }
    
    sort(sl.begin(), sl.end(), compare);
    for(auto x: sl)
    	cout<<x.first+1<<" ";

	cout<<endl;
	return 0;
}
