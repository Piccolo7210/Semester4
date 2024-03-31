#include<bits/stdc++.h>
using namespace std;
int c_time;
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
void arrived_sorted(vector<process> &arrived_process,vector<process> temp,int time);
bool process_burst_comparator(process a,process b);
bool check_time(vector<process> &temp,process p);

int main(){
   int i,j,n;
    vector<process> processes;
    vector<track> tracks;
    vector<process> temp;
    track y;
    vector<process> arrived_process;
    process curr_process;
    read_input(processes,n);;
    temp=processes;
    sort(temp.begin(),temp.end(),process_comparator);
    c_time=0;
    while(!temp.empty()){
        arrived_sorted(arrived_process,temp,c_time);
        if(arrived_process.empty()){
            y.p_name="NP";
            y.start_time=c_time;
            c_time=temp.front().arrival_time;
            y.end_time=c_time;
            tracks.push_back(y);
        }
        else{
            auto it= arrived_process.begin();
            curr_process=arrived_process.front();
            bool flag=check_time(temp,curr_process);
            if(flag){

            }
            else{
            y.p_name=curr_process.p_name;
            y.start_time=c_time;
            c_time+=curr_process.burst_time;
        
            y.end_time=c_time;
            tracks.push_back(y);
            }
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
        return a.p_name[1]<b.p_name[1];
    }
    return a.arrival_time<b.arrival_time;
}

void arrived_sorted(vector<process> &arrived_process,vector<process> temp,int time){
    arrived_process.clear();
    for(auto t:temp){
        if(t.arrival_time>time){
            break;
        }
        arrived_process.push_back(t);
    }
    sort(arrived_process.begin(),arrived_process.end(),process_burst_comparator);
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
bool process_burst_comparator(process a,process b){
      if(a.arrival_time<= c_time && b.arrival_time <= c_time){
        return a.burst_time<b.burst_time;
    }
    return a.burst_time<b.burst_time;
}
bool check_time(vector<process> &temp,process p){
    for(int i=0;i<temp.size();i++){
        if(temp[i].p_name!= p.p_name && (c_time+p.burst_time>temp[i].arrival_time)){
            return true;
        }
    }
}