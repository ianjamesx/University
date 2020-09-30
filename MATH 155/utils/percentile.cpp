#include <iostream>
#include <cmath>
using namespace std;

void getPercentileValue();
void getPercentile();
void getQuartiles();

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