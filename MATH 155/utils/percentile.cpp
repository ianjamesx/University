#include <iostream>
#include <cmath>
using namespace std;

void getPercentileValue();
void getPercentile();
void getQuartiles();
void interQuartileRange(int);
void findOutliers(int);

int main(){
    
    getQuartiles();
    return 0;
}

void getQuartiles(){

    int n;

    cout << "enter number of values in dataset: ";
    cin >> n;

    cout << "First quartile: " << ceil(n * .25) << endl;
    cout << "Second quartile: " << ceil(n * .5) << endl;
    cout << "Third quartile: " << ceil(n * .75) << endl;

    interQuartileRange(n);
    findOutliers(n);

}

void findOutliers(int n){
    //lower outelier bound: Q1 - 1.5IQR
    //uppper outlier bound: Q3 + 1.5IQR
    //if any data is less than lower outelier boundary or greater than the upper boundary, it is outlier

    float iqr = (ceil(n * .75) - ceil(n * .25));

    cout << "Lower outlier bound (value): " << ceil(n * .25) - (1.5 * iqr) << endl;
    cout << "Upper outlier bound (value): " << ceil(n * .75) + (1.5 * iqr) << endl;
}

void interQuartileRange(int n){

    cout << "IQR: " << (ceil(n * .75) - ceil(n * .25)) << endl;

}

void getPercentile(){

    int n;
    int valsless;

    cout << "enter number of values in dataset: ";
    cin >> n;

    cout << "enter number of values less than value you want percentile for: ";
    cin >> valsless;

    float value = ceil(((n * .5) / valsless) * 100);
    cout << "Your value is in the " << value << " percentile" << endl;

}


void getPercentileValue(){

    int n;
    int percentile;

    cout << "enter number of values in dataset: ";
    cin >> n;

    cout << "enter percentile you want: ";
    cin >> percentile;

    float value = ceil((percentile / 100.0) * n);
    cout << "The " << percentile << "th percentile value is the " << value << "th value" << endl;

}