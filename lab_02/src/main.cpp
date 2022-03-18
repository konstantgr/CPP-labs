#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;
using namespace std::chrono;

 
double f (double x) {
  return pow(x, 2) - pow(x, 2) + 4 * x - 5 * x + x + x;
}


int main (void) {
  int n;
  double res, fin;
 
 
  while (true) {
    cin >> n;

    while (cin.fail()) {
          cout << "Error with input's type" << endl;
          return 30;
    }
    
    auto start = high_resolution_clock::now();
 
    res = 1;
    for (int i = 0; i < n; i++)
      fin = f(res);
    cout << res << endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
 
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

  }
  return 30;
}

