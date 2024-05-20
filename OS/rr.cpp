#include<bits/stdc++.h>
using namespace std;
struct process{
    string p_name;
    int burst_time;
    int priority;
    int arrival_time;
    int ta_time;
    int waiting_time;
    int remaining_time;
};
struct track{
    string p_name;
    int start_time;
    int end_time;
};
void time_calc(vector<track> tracks,vector<process> &processes);
void read_input(vector<process> &processes);
void gantt_chart(vector <track>tracks);
bool process_comparator(process a,process b);
void arrived(vector<process> &processes,vector<process> &arrived_process,int time);
void check_prempt(vector<process> &arrived_process,vector<process> &temp,vector<track> &tracks, int &time);
bool in_arrived(vector<process> arrived_process , process p);
int n;
int round_time;
int main(){
    int i;
    vector<process> processes;
    vector<track> tracks;
    vector<process> temp;
    
    vector<process> arrived_process;
    process curr_process;
    read_input(processes);
    temp=processes;
   queue<process> rounds;
    int time=0;
 sort(temp.begin(),temp.end(),process_comparator);
for(auto x: temp)rounds.push(x);
   while(!rounds.empty()){
    track y;
    auto p = rounds.front();
    rounds.pop();
    y.p_name=p.p_name;
    y.start_time=time;
    if(p.remaining_time>round_time){
        p.remaining_time-=round_time;
        time+=round_time;
        rounds.push(p);
        cout<<"hello"<<endl;
    }
    else{
        time+=p.remaining_time;
        p.remaining_time=0;
    }
    y.end_time=time;
    tracks.push_back(y);
       
   }
   gantt_chart(tracks);
   cout<<endl;
    time_calc(tracks,processes);   

}
void read_input(vector<process> &processes){
    int i;
    freopen("rrinput.txt","r",stdin);
    cin>>n;
    cin>>round_time;
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
        a.remaining_time=a.burst_time;
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
                break;
            }
        }
        }
    }
   double  avg_wt=0,avg_ta=0;
    cout<<"Turnaround Time: "<<endl;
    for(auto x : processes){
        cout<<x.p_name<<": "<<x.ta_time<<endl;
        avg_ta+=x.ta_time;
    }
    cout<<"Waiting Time: "<<endl;
    for(auto x : processes){
        cout<<x.p_name<<": "<<x.waiting_time<<endl;
        avg_wt+=x.waiting_time;
    }
    cout<<"Average Turnaround time: "<<avg_ta/n<<endl;
    cout<<"Average Waiting time: "<<avg_wt/n<<endl;
}
bool process_comparator(process a,process b){
      if(a.arrival_time==b.arrival_time && a.burst_time==b.burst_time){
        return a.p_name[1]<b.p_name[1];
    }
    return a.arrival_time<b.arrival_time;
}