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
void read_input(vector<process> &processes);
void gantt_chart(vector <track>tracks);
bool process_burst_comparator(process a,process b);
bool process_comparator(process a,process b);
void arrived(vector<process> &processes,vector<process> &arrived_process,int time);
void check_prempt(vector<process> &arrived_process,vector<process> &temp,vector<track> &tracks, int &time);
bool in_arrived(vector<process> arrived_process , process p);
int n;
int main(){
    int i;
    vector<process> processes;
    vector<track> tracks;
    vector<process> temp;
    track y;
    vector<process> arrived_process;
    process curr_process;
    read_input(processes);
    temp=processes;
    int time=0,remaining_p=n;
    sort(temp.begin(),temp.end(),process_comparator);
    // for(int i=0;i<temp.size();i++){
    //      cout<<"Process name : "<< temp[i].p_name<<endl;
    // }
   while(!temp.empty()){
    arrived(temp,arrived_process,time);
    //if(arrived_process.size()!=0)sort(arrived_process.begin(),arrived_process.end(),process_burst_comparator);
    if(arrived_process.empty()){
        y.start_time=time;
        y.end_time=temp[0].arrival_time;
        y.p_name="NP";
        tracks.push_back(y);
        time=temp[0].arrival_time;
        // cout<<"Hello"<<endl;
    }
    else{
        check_prempt(arrived_process,temp,tracks,time);
    }
   }
   gantt_chart(tracks);
    

}
void read_input(vector<process> &processes){
    int i;
    freopen("input2.txt","r",stdin);
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
                //cout<<p.p_name<<" :"<<p.ta_time<<endl;
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
    }
}
bool process_comparator(process a,process b){
      if(a.arrival_time==b.arrival_time && a.remaining_time==b.remaining_time){
        return a.p_name[1]<b.p_name[1];
    }
    return a.arrival_time<b.arrival_time;
}
bool process_burst_comparator(process a,process b){
     return a.remaining_time<b.remaining_time;
}
void arrived(vector<process> &temp,vector<process> &arrived_process,int time){
    process p;
    for(int i=0;i<temp.size();i++){
            if(time>=temp[i].arrival_time && temp[i].remaining_time>0 && !in_arrived(arrived_process,temp[i])){
                p=temp[i];
                arrived_process.push_back(p);
            }
    }
}
void check_prempt(vector<process> &arrived_process,vector<process> &temp,vector<track> &tracks, int &time){
    track y;
    sort(arrived_process.begin(),arrived_process.end(),process_burst_comparator);
        for(int i=0;i<temp.size();i++){
            if(!in_arrived(arrived_process,temp[i]) && arrived_process[0].remaining_time+time> temp[i].arrival_time && ((arrived_process[0].burst_time-(temp[i].arrival_time-time))>temp[i].burst_time  )&& temp[i].p_name!= arrived_process[0].p_name)
            {
                // cout<<"prempted Process name : "<< temp[i].p_name<<endl;
                // cout<<"leaving at : "<<temp[i].arrival_time<<endl;
            arrived_process.push_back(temp[i]);
            // for(int i=0;i<arrived_process.size();i++){
            //     cout<<arrived_process[i].p_name<<"  "<<arrived_process[i].remaining_time<<endl;
            // }
            //cout<<endl;
            y.p_name=arrived_process[0].p_name;
            y.start_time=time;
            y.end_time=temp[i].arrival_time;
            tracks.push_back(y);
            arrived_process[0].remaining_time=arrived_process[0].burst_time-(temp[i].arrival_time-time);
            //cout<<"P3 remaining time : "<<arrived_process[0].burst_time-(temp[i].arrival_time-time)<<endl;
            time=temp[i].arrival_time;
            return;
            }
        }
            time+=arrived_process[0].remaining_time;
            arrived_process[0].remaining_time=0;
            cout<<arrived_process[0].p_name<<" : "<<arrived_process[0].remaining_time;
            cout<<"Time : "<<time<<endl;
            y.p_name=arrived_process[0].p_name;
            y.start_time=time;
            y.end_time=time+arrived_process[0].remaining_time;
            tracks.push_back(y);
            auto it = arrived_process.begin();
            auto it2=temp.begin();
            while(it2!=temp.end()){
                if((*it2).p_name==arrived_process[0].p_name){
                    cout<<(*it2).p_name<<"  Deleted. "<<endl;
                    temp.erase(it2);
                    break;

                }
                it2++;
            }
            arrived_process.erase(it);
        }
bool in_arrived(vector<process> arrived_process , process p){
    for(int i=0;i<arrived_process.size();i++){
        if(arrived_process[i].p_name==p.p_name)return true;
    }
    return false;
}