#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,i,j,qt;
    queue<string>RR_queue;
    queue<string>line;
    queue<int>RR_time;
    freopen("rr_input.txt","r",stdin);
    cin>>n;
    string process[n];
    int burst_time[n],priority[n],new_burst_time[n];

    for(i=0;i<n;i++){
        cin>>process[i];
    }
    for(i=0;i<n;i++){
        cin>>burst_time[i];
        new_burst_time[i]=burst_time[i];
    }
     for(i=0;i<n;i++){
        cin>>priority[i];
    }
    cin>>qt;
    for(i=0;i<n;i++){
        RR_queue.push(process[i]);
    }
    for(;;){
        string popped=RR_queue.front();
        RR_queue.pop();
        line.push(popped);
        if(burst_time[popped[1]-'0'-1]>=qt){
            RR_time.push(qt);
            burst_time[popped[1]-'0'-1]=burst_time[popped[1]-'0'-1]-qt;
        }
        else{
            RR_time.push(burst_time[popped[1]-'0'-1]);
            burst_time[popped[1]-'0'-1]=0;
        }
        if(burst_time[popped[1]-'0'-1]>0){
            RR_queue.push(popped);
        }
        if(RR_queue.size()==0){
            break;
        }
    }
    cout<<"Gant chart"<<endl;
    string new_process[line.size()];
    int new_time[RR_time.size()];
    int index=0,sum=0;
    cout<<"|";
    while(line.size()!=0){
        new_process[index]=line.front();
        cout<<"---"<<line.front()<<"---|";
        line.pop();
        index++;
    }
    cout<<endl;
    cout<<"0";
    index=0;
    while(RR_time.size()!=0){
        sum+=RR_time.front();
        new_time[index]=sum;
        cout<<"        "<<sum;
        RR_time.pop();
        index++;
    }
    cout<<endl;
    int turnAround_time[n];
    for(i=0;i<n;i++)turnAround_time[i]=0;
    for(i=index-1;i>=0;i--){
        int new_index=new_process[i][1]-'0'-1;
        if(turnAround_time[new_index]==0){
            turnAround_time[new_index]=new_time[i];
        }
    }
    double average_turnaround_time=0.0;
    double average_waiting_time=0.0;
    cout<<"Turnaround time :"<<endl;
    for(i=0;i<5;i++){
        cout<< "Process "<<process[i]<<":"<<turnAround_time[i]<<endl;
        average_turnaround_time+=turnAround_time[i];
    }
    cout<<"Waiting time "<<endl;
    for(i=0;i<n;i++){
        cout<< "Process "<<process[i]<<" :"<<turnAround_time[i]-new_burst_time[i]<<endl;
        average_waiting_time+=turnAround_time[i]-new_burst_time[i];
    }
    cout<<"Average turnarond time: "<<average_turnaround_time/5<<endl;
    cout<<"Average waiting time: "<<average_waiting_time/5<<endl;
}