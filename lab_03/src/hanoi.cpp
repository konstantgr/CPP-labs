#include <iostream>

using i64 = long long;
using namespace std;

void towerOfHanoi(i64 n, char from_rod,
                    char to_rod, char aux_rod) {
    if (!n) return;

    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
    cout << "Move disk " << n << " from rod " << from_rod <<
                                " to rod " << to_rod << endl;
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}
 
int main(int argc, char** argv)
{
    i64 n = 2;
    towerOfHanoi(n, 'A', 'C', 'B');
    return 0;
}
