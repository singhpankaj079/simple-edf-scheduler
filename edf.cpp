#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back
#define mp make_pair

struct rijs{
	int i,j,t;
 };
 struct njs {
	int extime, deadline, i, j;
};

struct compareRijs{
   bool operator()(const rijs &a, const rijs &b){
   	 return a.t>b.t;
   }
};
struct compareNjs{
	bool operator()(const njs &a, const njs &b){
		return a.deadline>b.deadline;
	}
};


  int findLcm(vector<pair<int,int> > &a, int n){
  	bool found;
  	for (int i=a[1].second;;i++){
       found = true;
       for (int j=1;j<=n;j++){
       	if (i%a[j].second!=0)found=false;
       }
       if (found)return i;
  	}
  }
  int main(){

   freopen("input.txt","r" , stdin);

   // to store execution times and periods of the tasks
   vector< pair<int, int> > tasks(11);

   int n, hyperPeriod;
   njs t2;

   // input the number of tasks to be scheduled
   cin>>n;

   // to keep track of the next job which is going to be released sorted on the basis of release time
   priority_queue <rijs, vector<rijs>, compareRijs> rij;

   // to keep track of the deadline and remaining execution time of a job sorted on the basis of deadline(ascending)
   priority_queue <njs, vector<njs>, compareNjs> nj;

   for (int i=1;i<=n;i++){
     // enter execution and period of every task assuming deadline is equal to the period of each task
   	cin>>tasks[i].first>>tasks[i].second;
   }



  int j=1;
  hyperPeriod = findLcm(tasks, n);
  for (int i=1;i<=n;i++){
        j=1;
       while(tasks[i].second*(j-1)<hyperPeriod){
        rijs temp;
        temp.i = i;
        temp.j = j;
        temp.t = (j-1)*tasks[i].second;
        rij.push(temp);
        j++;
       }
  }

    rijs t1;


    for (int t=0;t<hyperPeriod;t++){
       t1 = rij.top();
        while(!rij.empty() && t1.t<=t){
       	rij.pop();
        t2.i = t1.i;
        t2.j = t1.j;
        t2.extime = tasks[t1.i].first;
        t2.deadline = (t1.j)*tasks[t1.i].second;
        nj.push(t2);
        if (rij.empty())break;
        t1 = rij.top();
       }

       if (!nj.empty()){
        t2 = nj.top();
       nj.pop();
       } else {
           cout<<t<<" cpu idle"<<endl;
           continue;}
       if (t2.deadline<t){cout<<"Schedule not feasible"; return 0;}

       cout<<"at time t = "<<t<<" T("<<t2.i<<","<<t2.j<<")"<<endl;
       t2.extime--;
       if (t2.extime>0) {nj.push(t2);}

    }

	return 0;
}
