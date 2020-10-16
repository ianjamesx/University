#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <unistd.h>
using namespace std;

struct process {
    int index;
    int cpuburst;
    int arrival;
    int priority;

    int completion;
    float turnaround;
    float wait;
};

//run a process, update process and process timeline
void run(process&, vector<int>&);

//some utility functions
void takeInputs(vector<process>&, int, bool, bool);
void printProcs(vector<process>);
void printeTimeline(vector<int>);
bool finishedAll(vector<process>);

void getTurnWait(vector <process>&);

float avgWait(vector <process>&);
float avgTurn(vector <process>&);

//all of our algorithms for process scheduling, return:
//  the list of processes with the completion time
//  the timeline of which process was ran at which time stamp
void fcfs(vector<process>&, vector<int>&);
void sjf(vector<process>&, vector<int>&);
void srt(vector<process>&, vector<int>&);
void rr(vector<process>&, vector<int>&);
void ps(vector<process>&, vector<int>&);

int main(){

    //user inputs number of processes
    int proc_count;

    cout << "How many processes in table? (e.g. 5): ";
    cin >> proc_count;
    
    cout << "-----------------------\nAlgorithms:\n\n";

    //user selects which algorithm to use
    int algo;
    cout << "First come, first serve (1)\n";
    cout << "Shortest Job First (2)\n";
    cout << "Shortest Remaining Time (3)\n";
    cout << "Round Robin (4)\n";
    cout << "Priority Scheduling (5)\n\n";

    cout << "Choose a scheduling algorithm (enter number associated with it): ";
    cin >> algo;

    //determine if arrival times and priorites are needed
    bool arrivals, priorites;
    if(algo == 1) arrivals = priorites = false;
    if(algo == 2) arrivals = priorites = false;
    if(algo == 3){
        arrivals = true;
        priorites = false;
    }
    if(algo == 4) arrivals = priorites = false;
    if(algo == 5) arrivals = priorites = true;

    vector<process> p;
    vector<int> timeline;

    //take inputs needed for algo
    takeInputs(p, proc_count, arrivals, priorites);

    //make a copy of p so we can hold onto their cpu burst
    vector<process> p2 = p;

    //run algo
    if(algo == 1) fcfs(p, timeline);
    if(algo == 2) sjf(p, timeline);
    if(algo == 3) srt(p, timeline);
    if(algo == 4) rr(p, timeline);
    if(algo == 5) ps(p, timeline);

    //copy their original cpu times over from p2
    //also need to increment the completion times by 1
    int i;
    for(i = 0; i < p.size(); i++){
        p[i].cpuburst = p2[i].cpuburst;
        p[i].completion++;
    }

    cout << "------------------------------------\nResults:\n";

    //get average turnaround, waits
    getTurnWait(p);

    //print all

    printProcs(p);
    cout << endl;
    cout << "Average Turnaround: " << avgTurn(p) << endl;
    cout << "Average Wait: " << avgWait(p) << endl;
    
    printeTimeline(timeline);

    return 0;
}

void run(process &p, vector<int> &timeline){

    //if trying to run a finished process, throw error
    if(p.cpuburst == 0){
        cout << "ERROR: trying to run finished process\n";
        return;
    }

    //if were trying to run before arrival, throw error
    if(p.arrival > timeline.size()){
        cout << "ERROR: process has not arrived\n";
        return;
    }

    p.cpuburst--;
    if(p.cpuburst == 0){
        p.completion = timeline.size(); //may be error
    }
    timeline.push_back(p.index);
}

//take inputs (arrivals and priorities depend on algorithm, not used in some)
void takeInputs(vector<process> &p, int proc_count, bool arrivals, bool priorites){
    int i;
    //first, push new processes for each in proc count (init attributes incase they are not entered)
    for(i = 0; i < proc_count; i++){
        process curr;
        curr.index = i;
        curr.cpuburst = 0;
        curr.arrival = 0;
        curr.priority = 0;
        p.push_back(curr);
    }

    cout << "Enter CPU time for each process\n";
    for(i = 0; i < proc_count; i++){
        cout << "CPU time for P" << i << ": ";
        cin >> p[i].cpuburst;
    }

    if(arrivals){
        cout << "Enter arrival time for each process (if not applicable, enter all 0s)\n";
        for(i = 0; i < proc_count; i++){
            cout << "Arrival time for P" << i << ": ";
            cin >> p[i].arrival;
        }
    }

    if(priorites){
        cout << "Enter priority for each process (if not applicable, enter all 0s)\n";
        for(i = 0; i < proc_count; i++){
            cout << "priority for P" << i << ": ";
            cin >> p[i].priority;
        }
    }
}

void printProcs(vector<process> p){

    //cout << setw(5);

    int i;
    cout << "Pid" << setw(8) <<  "CPU" << setw(10) << "Arrival" << setw(10) << "Priority" << setw(11) << "CT" << setw(10) << "TT" << setw(10) << "Wait\n";

    for(i = 0; i < p.size(); i++){
        cout << p[i].index << setw(10) << p[i].cpuburst << setw(10) << p[i].arrival << setw(10) << p[i].priority << setw(10) << 
                p[i].completion << setw(10) << p[i].turnaround << setw(10) << p[i].wait << endl;
    }
}

void printeTimeline(vector<int> timeline){
    int i, j;
    cout << "\nTimeline:\n(time): (Pid)\n";
    for(i = 0; i < timeline.size(); i++){

        //print currPID once for all instances found, mark on number number line 
        cout << i << ": " << timeline[i] << "\n";
    }
    cout << endl;
}

//see if there are any process that are unfinished (return true if all finished, false if not)
bool finishedAll(vector<process> p){

    int i;
    for(i = 0; i < p.size(); i++){
        //if we find a processed thats not done yet, not finished
        if(p[i].cpuburst > 0){
            return false;
        }
    }
    return true;
}

void fcfs(vector<process> &p, vector<int> &timeline){
    
    int i;
    //simply iterate over processes, execute one after the other
    for(i = 0; i < p.size(); i++){
        while(p[i].cpuburst > 0){
            run(p[i], timeline);
        }
    }

}

void sjf(vector<process> &p, vector<int> &timeline){

    int i, j;
    for(i = 0; i < p.size(); i++){

        //get next shortest job
        int shortest = 0;
        for(j = 0; j < p.size(); j++){

            //if we have an unfinished job with a cpuburst less than shortest one
            if(p[j].cpuburst > 0 && (p[j].cpuburst < p[shortest].cpuburst)){
                shortest = j;
            }

        }

        //run shortest job in entirety (as arrival times are not considered here)
        while(p[shortest].cpuburst > 0){
            run(p[shortest], timeline);
        }

    }

}

void srt(vector<process> &p, vector<int> &timeline){

    //iterate until all jobs finished
    while(!finishedAll(p)){

        int i;

        //init shortest to first unfinished process we find
        int shortest;
        for(i = 0; i < p.size(); i++){
            if(p[i].cpuburst > 0){
                shortest = i;
                break;
            }
        }

        for(i = 0; i < p.size(); i++){

            //if process has yet to arrive, skip it
            if(p[i].arrival > timeline.size()) continue;

            //if process complete, also skip
            if(p[i].cpuburst == 0) continue;

            //if we have an unfinished job with a cpuburst less than shortest one
            if(p[i].cpuburst < p[shortest].cpuburst){
                shortest = i;
            }

        }

        //printProcs(p);
        //cout << "-----------------\n";

        run(p[shortest], timeline);
        //sleep(1);
        
    }

}

void rr(vector<process> &p, vector<int> &timeline){
    int curr = 0;
    while(!finishedAll(p)){
        if(p[curr].cpuburst > 0){
            run(p[curr], timeline);
        }
        curr++;
        if(curr > p.size()){
            curr = 0;
        }
    }
}

void ps(vector<process> &p, vector<int> &timeline){

    int i;

    while(!finishedAll(p)){

        //init our first process to whichever process has yet to finished (alike in srt())
        int priority;
        for(i = 0; i < p.size(); i++){
            if(p[i].cpuburst > 0){
                priority = i;
                break;
            }
        }

        //chose next process (assuming it has arrived) with highest priority
        for(i = 0; i < p.size(); i++){

            //if process has yet to arrive, skip it
            if(p[i].arrival > timeline.size()) continue;

            //if process complete, also skip
            if(p[i].cpuburst == 0) continue;

            //if we have an unfinished job with a cpuburst less than shortest one
            if(p[i].priority < p[priority].priority){
                priority = i;
            }

        }

        run(p[priority], timeline);

    }

}

void getTurnWait(vector<process> &p){
    int i;
    for(i = 0; i < p.size(); i++){
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].wait = p[i].turnaround - p[i].cpuburst;
    }
}

float avgTurn(vector<process> &p){
    int i;
    float total = 0;
    for(i = 0; i < p.size(); i++){
        total += p[i].turnaround;
    }
    return (total * 1.0 / p.size());
}

float avgWait(vector<process> &p){
    int i;
    float total = 0;
    for(i = 0; i < p.size(); i++){
        total += p[i].wait;
    }
    return (total * 1.0 / p.size());
}