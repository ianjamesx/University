//boilerplate includes from previous CUDA project
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <utility>
#include <set>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct record {
  double x;
  double y;
  double z;
};

struct centroid {
    int member_count;
    record center;
    record member_sum;
};

void printRecord(record r){
    cout << fixed << "(" << r.x << ", " << r.y << ", " << r.z << ")" << endl;
}

void printCentroid(centroid c){
    cout << "Center: ";
    printRecord(c.center);

    cout << "Member Sum: ";
    printRecord(c.member_sum);

    cout << "Member count: " << c.member_count << endl;

}

void readfile(string path, vector<record> &records){
    
    ifstream infile;
    infile.open(path);
    double x, y, z;
    while (infile >> x >> y >> z){
        record curr;
        curr.x = x;
        curr.y = y;
        curr.z = z;
        records.push_back(curr);
    }
}

void initCentroid(centroid &c){
    c.member_count = 0;
    c.member_sum.x = 0;
    c.member_sum.y = 0;
    c.member_sum.z = 0;

    c.center.x = 0;
    c.center.y = 0;
    c.center.z = 0;
}

void centroidCenter(centroid &c){
    c.center.x = c.member_sum.x / (c.member_count * 1.0);
    c.center.y = c.member_sum.y / (c.member_count * 1.0);
    c.center.z = c.member_sum.z / (c.member_count * 1.0);
}

void addToMemberSum(centroid &c, record r){
    c.member_sum.x += r.x;
    c.member_sum.y += r.y;
    c.member_sum.z += r.z;
}

void removeFromMemberSum(centroid &c, record r){
    c.member_sum.x -= r.x;
    c.member_sum.y -= r.y;
    c.member_sum.z -= r.z;
}

double normalizerecord(record r){
    double total = 0.0;
    total += (r.x * r.x) + (r.y * r.y) + (r.z * r.z);
    return sqrt(total);
}

//distance between two location records
double vectordistance(record r1, record r2){
    double x = r1.x - r2.x;
    double y = r1.y - r2.y;
    double z = r1.z - r2.z;
    double dist = (x * x) + (y * y) + (z * z);
    return sqrt(dist);
}

void printAllRecords(vector<record> data){
    int i;
    for(i = 0; i < data.size(); i++){
        printRecord(data[i]);
    }
}

void init(int n, int k, vector<record> data, vector<int> &assignments,  vector<centroid> &centroids){
  
    int i;

    //default all centroids to 0 (so we don't get errs with adding members later)
    for(i = 0; i < k; i++){
        initCentroid(centroids[i]);
        //centroidCenter(centroids[i]);
    }

    //defaulting all feature vectors to cluster 0
    for(i = 0; i < n; i++){
        assignments[i] = 0;
        addToMemberSum(centroids[0], data[i]);
    }

    centroids[0].member_count = n;
    //centroidCenter(centroids[0]);

}

void altinit(int n, int k, vector<record> data, vector<int> &assignments,  vector<centroid> &centroids){
  
    int i;

    //default all centroids to 0 (so we don't get errs with adding members later)
    for(i = 0; i < k; i++){
        initCentroid(centroids[i]);
        //centroidCenter(centroids[i]);
    }

    int range = ceil(n / k);
    int rangecounter = 0;
    int rangecurr = 0;

    //defaulting all feature vectors to cluster 0
    for(i = 0; i < n; i++){

        if(rangecounter > range){
            rangecounter = 0;
            rangecurr++;
        }

        assignments[i] = rangecurr;
        addToMemberSum(centroids[rangecurr], data[i]);
        centroids[rangecurr].member_count++;

        rangecounter++;
    }

    //cout << "ON INIT" << endl;
    for(i = 0; i < k; i++){
        centroidCenter(centroids[i]);
        //printCentroid(centroids[i]);
        //printRecord(centroids[i].center);
    }

    //cout << "-------------------" << endl;

}

int getNearestCentroid(int k, record data, vector<centroid> centroids){

    int cmin = 0;
    int i;

    double dmin = INT_MAX;//((1 << 32) - 1); //shift to max int
    double d;

    for(i = 0; i < k; i++){
        d = vectordistance(data, centroids[i].center);
        if(d < dmin){
            dmin = d;
            cmin = i;
        }
    }

    return cmin;
}

int main(int argc, char **argv){

    //using our data set of ~8000 location points for our test
    //3-dimmensional features (x,y,z ECF coordinates)
    //all locational points are from same group of ~50 projectiles at different times
    vector<record> data;
    readfile("locations.big", data);

    //define everything
    int k = 225;
    int n = data.size();

    vector<int> assignments(n); //define assignments as their own list rather than appending to the struct
    vector<centroid> centroids(k);

    altinit(n, k, data, assignments, centroids);
    //printAllRecords(data);

    bool converged = false;
    while(!converged){

        cout << "Not converged, finding centroids..." << endl;

        converged = true;
        int cmin, i;
        for(i = 0; i < n; i++){
            cmin = getNearestCentroid(k, data[i], centroids);

            if(cmin != assignments[i]){

                converged = false;
                int prevCenIndex = assignments[i];

                //update membership count, sum
                removeFromMemberSum(centroids[prevCenIndex], data[i]);
                addToMemberSum(centroids[cmin], data[i]);
                centroids[prevCenIndex].member_count--;
                centroids[cmin].member_count++;

                assignments[i] = cmin;
            }

        }

        //update center of centroids
        for(i = 0; i < k; i++){
            centroidCenter(centroids[i]);
        }

    }

    int i;
    for(i = 0; i < n; i++){
        //cout << assignments[i] << endl;
    }

    return 0;
}