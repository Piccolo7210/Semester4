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