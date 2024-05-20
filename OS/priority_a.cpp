#include<bits/stdc++.h>
using namespace std;
struct process{
    string p_name;
    int burst_time;
    int priority;
    int arrival_time;
    int ta_time;
    int waiting_time;

};
struct track{
    int start_time;
    int end_time;
    string p_name;
};
void time_calc(vector<track> tracks,vector<process> &processes);
void read_input(vector<process> &processes,int &n);
void gantt_chart(vector <track>tracks);
bool process_comparator(process a,process b);
void arrived_prio_sort(vector<process> &arrived_process,vector<process> temp,int time);
bool priority_comparator(process a,process b);
int main(){
   int i,j,n,time=0;
    vector<process> processes;
    vector<track> tracks;
     track y;
    vector<process> arrived_process;
    process curr_process;
    vector<process> temp;
    read_input(processes,n);;
    temp=processes;
    sort(temp.begin(),temp.end(),process_comparator);
   
    while(!temp.empty()){
        arrived_prio_sort(arrived_process,temp,time);
        if(arrived_process.empty()){
            y.p_name="NP";
            y.start_time=time;
            time=temp.front().arrival_time;
            y.end_time=time;
            tracks.push_back(y);
        }
        else{
            curr_process=arrived_process.front();
            y.p_name=curr_process.p_name;
            y.start_time=time;
            time+=curr_process.burst_time;
            y.end_time=time;
            tracks.push_back(y);
            auto it=temp.begin();
            while(it!=temp.end()){
                if((*it).p_name==curr_process.p_name){
                    temp.erase(it);
                   // cout<<(*it).p_name<<"  "<<endl;
                    break;

                }
                it++;
            }
        }
    }
    time_calc(tracks,processes);
    gantt_chart(tracks);
    cout<<endl<<endl;
     cout<<"Average TurnAround Time: "<<endl;
    double avg_tat=0;
    for(i=0;i<n;i++){
        avg_tat+=processes[i].ta_time;
    }
    cout<<avg_tat/n*1.00<<endl;
    cout<<"Average Waiting Time: "<<endl;
    double avg_wat=0;
    for(i=0;i<n;i++){
        avg_wat+=processes[i].waiting_time;
    }
    cout<<avg_wat/n*1.00<<endl;
}
bool process_comparator(process a,process b){
      if(a.arrival_time==b.arrival_time){
        if(a.priority=b.priority)
        return a.p_name[1]<b.p_name[1];
        return a.priority<b.priority;
    }
    return a.arrival_time<b.arrival_time;
}
void arrived_prio_sort(vector<process> &arrived_process,vector<process> temp,int time){
    arrived_process.clear();
    for(auto t:temp){
        if(t.arrival_time>time){
            break;
        }
        arrived_process.push_back(t);
    }
    sort(arrived_process.begin(),arrived_process.end(),priority_comparator);
}
void read_input(vector<process> &processes, int &n){
        int i;
    freopen("input.txt","r",stdin);
    cin>>n;
    process a;
    for(i=0;i<n;i++){
        string s;
        cin>>s;
        a.p_name=s;
        int x;
        cin>>x;
        a.burst_time=x;
        cin>>x;
        a.priority=x;
        cin>>x;
        a.arrival_time=x;
        a.ta_time=0;
        a.waiting_time=0;
        processes.push_back(a);
    }
}
void gantt_chart(vector <track>tracks){
    printf("|");
    for(auto x: tracks)printf("----%s----|",x.p_name.c_str());
    cout<<endl;
    printf("%-11d",0);
    for(auto x: tracks)printf("%-11d",x.end_time);
}
void time_calc(vector<track> tracks,vector<process> &processes){
    for(auto x : tracks ){
        if(x.p_name!="NP"){
            for(auto &p : processes){
                if(x.p_name==p.p_name){
                p.ta_time=x.end_time-p.arrival_time;
                p.waiting_time=p.ta_time-p.burst_time;
                //cout<<p.p_name<<" :"<<p.ta_time<<endl;
            }
        }
        }
    }
}
bool priority_comparator(process a,process b){
    if(a.priority==b.priority){
        return a.p_name[1]<b.p_name[1];
    }
    return a.priority<b.priority;
}
