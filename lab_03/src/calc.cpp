#include <iostream>

using i64 = long long;
using namespace std;

enum Arithmetic { 
  plus = '+', 
  minus = '-',
  multiply = '*',
  power = '^' 
};

i64 pow (i64 x, i64 power) { 
  i64 result = 1;
  
  for(int i = 0; i < power; ++i) result *= x;
  return result;
}

i64 calc (char action, i64 x, i64 y) { 
    switch (action) {
      case Arithmetic::plus:
          return x + y;
      case Arithmetic::minus:
          return x - y;
      case Arithmetic::multiply:
          return x * y;
      case Arithmetic::power:
          return pow(x, y);
      default:
          throw invalid_argument( "received invalid action" );
    }
}


int main (int argc, char** argv) {
  char action = argv[2][0];
  i64 x = stoi(argv[1]), y = stoi(argv[3]);

  cout << calc(action, x, y) << endl;

  return 0;
}

