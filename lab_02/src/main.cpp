#include <iostream>
#include <cmath>
using namespace std;


double f (double x) {
  return pow(x, 2) - pow(x, 2) + 4 * x - 5 * x + x + x;
}


int main (void) {
  int n;
  double res = 1;
  
  cin >> n;
  while (cin.fail()) {
        cout << "Error with input's type" << endl;
        return 30;
  }

  for (int i = 0; i < n; i++)
    res += f(res);
  cout << res << endl;

  return 30;
}
