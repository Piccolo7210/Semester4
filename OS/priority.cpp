#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,i,j;
    freopen("pr_input.txt","r",stdin);
    cin>>n;
    string process[n];
    int burst_time[n],priority[n];
    for(i=0;i<n;i++){
        cin>>process[i];
    }
    for(i=0;i<n;i++){
        cin>>burst_time[i];
    }
     for(i=0;i<n;i++){
        cin>>priority[i];
    }
    int turnAround_time[n];
   
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(priority[j]<priority[j+1]){
                int temp=priority[j];
                priority[j]=priority[j+1];
                priority[j+1]=temp;
                temp=burst_time[j];
                burst_time[j]=burst_time[j+1];
                burst_time[j+1]=temp;
                string t=process[j];
                process[j]=process[j+1];
                process[j+1]=t;
            }
        }
    }
    turnAround_time[0]=burst_time[0];
    for(i=1;i<=n;i++){
        turnAround_time[i]=turnAround_time[i-1]+burst_time[i];
    }
    cout<<"Gant Chart:"<<endl;
    cout<<"|";
    for(i=0;i<n;i++){
        cout<<"---"<<process[i]<<"---|";
    }
    cout<<endl;
    cout<<"0        ";
    for(i=0;i<n;i++){
        cout<<turnAround_time[i]<<"        ";
    }
    cout<<endl;
    double average_turnaround_time=0;
    cout<<"Turnaround time: "<<endl;
    for(i=0;i<n;i++){
        cout<<"process "<<process[i]<<" "<<turnAround_time[i]<<endl;
        average_turnaround_time+=turnAround_time[i];
    }
    int waiting_time[n];
    double average_waiting_time=0;
    cout<<"Waiting time: "<<endl;
    for(i=0;i<n;i++){
        cout<<"Process "<<process[i]<<": "<<turnAround_time[i]-burst_time[i]<<endl;
     average_waiting_time+=turnAround_time[i]-burst_time[i];
    }
    cout<<"Average turnaround time="<<average_turnaround_time/n<<endl;
    cout<<"Average waiting time="<<average_waiting_time/n<<endl;
}