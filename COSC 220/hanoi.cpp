// C++ recursive function to
// solve tower of hanoi puzzle
#include <iostream>
using namespace std;

void towerOfHanoi(int n, char start, char target, char aux){
    if (n == 1){
        cout << "Move disk 1 from rod " << start << " to rod " << target << endl;
        return;
    }

    towerOfHanoi(n - 1, start, aux, target);

    cout << "Move disk " << n << " from rod " << start << " to rod " << target << endl;

    towerOfHanoi(n - 1, aux, target, start);
}

// Driver code
int main(){
    towerOfHanoi(4, 'A', 'C', 'B'); // A, B and C are names of rods
    return 0;
}

// This is code is contributed by ra
