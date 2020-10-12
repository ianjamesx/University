#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <unistd.h>
using namespace std;

struct process {
    int index;
    int cpuburst;
    int arrival;
    int priority;

    int completion;
};
/*
struct inputs {
    int proc_count;
    int *cpubursts;
    int *arrivals;
    int *priorites;
};

struct outputs {
    vector<int> completions;
    vector<int> timestamps;
};

//need an ordering struct for sorting by keys (as well as a comparison function)
struct ordering {
    int cpuburst;
    int index;
};

bool compareOrderings(const ordering &a, const ordering &b){
    return a.cpuburst < b.cpuburst;
}*/

void run(process&, vector<int>&);

void takeInputs(vector<process>&, int, bool, bool);

void printProcs(vector<process>);

void printeTimeline(vector<int>);

bool finishedAll(vector<process>);

//return at timeline of all processes ran over time
void fcfs(vector<process>&, vector<int>&);
void sjf(vector<process>&, vector<int>&);
void srt(vector<process>&, vector<int>&);
void rr(vector<process>&, vector<int>&);
void ps();

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

    //run algo
    rr(p, timeline);

    printProcs(p);
    printeTimeline(timeline);

    /*
    if(algo == 3) out = srt(in);
    if(algo == 4) out = rr(in);
    if(algo == 5) out = ps(in);
*/
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
    int i;
    for(i = 0; i < p.size(); i++){
        cout << p[i].index << "\t" << p[i].cpuburst << "\t" << p[i].arrival << endl;
    }
}

void printeTimeline(vector<int> timeline){
    int i;
    for(i = 0; i < timeline.size(); i++){
        cout << timeline[i] << " ";
    }
}

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