#include <iostream>
#include <string>
#include <vector>
using i64 = long long;
using namespace std;


vector<string> hanoi(i64 n, int i, int k, vector<string> res) {
    int tmp;

    if (n == 1) {
        res.push_back("Move disk 1 from pin " + to_string(i) + " to " + to_string(k));
        return res;
    }
    else {
        tmp = 6 - i - k;
        res = hanoi(n - 1, i, tmp, res);
        res.push_back("Move disk " + to_string(n) + " from pin " + to_string(i) + " to " + to_string(k));
        res = hanoi(n - 1, tmp, k, res);
        return res;
    }
}
 
int main(int argc, char** argv)
{
    i64 n = 3;
    vector<string> res;
    res = hanoi(n, 1, 2, res);

    for (auto i: res) cout << i << endl;

    return 0;
}
