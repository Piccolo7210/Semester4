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
bool process_comparator(process a,process b);
void read_input(vector<process> &processes,int &n);
void gantt_chart(vector <track>tracks);
void time_calc(vector<track> tracks,vector<process> &processes);
int main(){
    int n,i;
    
    vector<process> processes;
    vector<track> tracks;
    read_input(processes,n);
    sort(processes.begin(),processes.end(),process_comparator);
    cout<<endl;
    int time=0;
    for(auto &p : processes){
        if(time<p.arrival_time){
            track y;
            y.p_name="NP";
            y.start_time=time;
            y.end_time=p.arrival_time;
            time=p.arrival_time;
            tracks.push_back(y);
            y.p_name=p.p_name;
            y.start_time=time;
            y.end_time=time+p.burst_time;
            time+=p.burst_time;
            p.ta_time=time-p.arrival_time;
            p.waiting_time=p.ta_time-p.burst_time;
            tracks.push_back(y);
        }
        else{
            track y;
            y.p_name=p.p_name;
            y.start_time=time;
            y.end_time=time+p.burst_time;
            time+=p.burst_time;
            p.ta_time=time-y.start_time;
            p.waiting_time=p.ta_time-p.burst_time;
            tracks.push_back(y);
        }
    }
   gantt_chart(tracks);
       cout<<endl<<endl;
    cout<<"Average TurnAround Time: "<<endl;
    double avg_tat=0;
    for(i=0;i<n;i++){
        avg_tat+=processes[i].ta_time;
    }
    cout<<avg_tat/n<<endl;
    cout<<"Average Waiting Time: "<<endl;
    double avg_wat=0;
    for(i=0;i<n;i++){
        avg_wat+=processes[i].waiting_time;
    }
    cout<<avg_wat/n<<endl;
}
bool process_comparator(process a,process b){
    if(a.arrival_time==b.arrival_time){
        return a.p_name[1]<b.p_name[1];
    }
    return a.arrival_time<b.arrival_time;
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