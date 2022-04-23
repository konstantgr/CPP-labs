#include <iostream>
#include <thread>

using i64 = long long;
using namespace std;

i64 pow (i64 x, i64 power) { 
  i64 result = 1;
  
  for(int i = 0; i < power; ++i) result *= x;
  return result;
}

inline constexpr std::uint32_t fnv1a(const char* str, std::uint32_t hash = 2166136261UL) {
    return *str ? fnv1a(str + 1, (hash ^ *str) * 16777619ULL) : hash;
}

/* 
Formula 1: f(x) = x ^2- x ^2+ x *4- x *5+ x + x
Formula 2: f(x) = x + x 
*/

i64 f1(i64 x) {
  return pow(x, 2) - pow(x, 2) + x * 4 - x * 5 + x + x;
}

i64 f2(i64 x) {
  return x + x;
}

i64 f3_simple(i64 x) {
  return f1(x) + f2(x) - f1(x);
}

tuple<i64, i64, i64> simple_loop (i64 iterations) {
  i64 x1 = 1, x2, x3;

  for (int i = 0; i < iterations; i++) {
    x1 = f1(x1);
    x2 = f2(1);
    x3 = f3_simple(1);
  }
  return make_tuple(x1, x2, x3);
}

tuple<i64, i64, i64> threads_loop (i64 iterations) {
  i64 x1 = 1, x2, x3;

  for (int i = 0; i < iterations; i++) {
    std::thread thr1(f1, x1);
    std::thread thr2(f2, 1);
    std::thread thr3(f3_simple, 1);
    thr1.join();
    thr2.join();
    thr3.join();
  }
  return make_tuple(x1, x2, x3);
}

int main (int argc, char** argv) {
  i64 x1, x2, x3;
  i64 iterations = stoi(argv[1]);
  string mode = argv[2];

  auto start = chrono::steady_clock::now();

  cout << mode << endl;

  switch (fnv1a(mode.c_str())) {
    case fnv1a("simple"): tie(x1, x2, x3) = simple_loop(iterations);
    case fnv1a("threads"): tie(x1, x2, x3) = threads_loop(iterations);
  }

  auto end = chrono::steady_clock::now();
  auto diff = end - start;

  cout << chrono::duration <double> (diff).count() << " s" << endl;
  cout << "x1: " << x1 << endl << "x2: " << x2 << endl << "x3: " << x3 << endl;
  return 0;
}

