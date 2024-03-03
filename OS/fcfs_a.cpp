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
int main(){
    int n,i,j;
    freopen("input.txt","r",stdin);
    cin>>n;
    vector<process> processes;
    vector<track> tracks;
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
    sort(processes.begin(),processes.end(),process_comparator);
    for(i=0;i<n;i++){
        cout<<processes[i].p_name<<" ";
    }
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
    printf("|");
    for(auto r:tracks){
        printf("----%s----|",r.p_name.c_str());
    }
    cout<<endl;
    printf("%-11d",0);
    for(auto r:tracks){
        printf("%-11d",r.end_time);
    }
    cout<<endl<<endl;
}
bool process_comparator(process a,process b){
    if(a.arrival_time==b.arrival_time){
        return a.burst_time<b.burst_time;
    }
    return a.arrival_time<b.arrival_time;
}