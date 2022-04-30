#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

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

i64 f1(i64 x) {
  return pow(x, 2) - pow(x, 2) + x * 4 - x * 5 + x + x;
}

i64 f2(i64 x) {
  return x + x;
}

i64 f3(i64 x) {
  return f1(x) + f2(x) - f1(x);
}

void thread_function(int n, float x, i64 (*func)(i64)) {
    for (int i = 0; i < n; i++) { func(x); }
}

tuple<i64, i64, i64> simple_loop (i64 iterations) {
  i64 x1 = 1, x2, x3;

  for (int i = 0; i < iterations; i++) {
    x1 = f1(x1);
    x2 = f2(1);
    x3 = f3(1);
  }
  return make_tuple(x1, x2, x3);
}

tuple<i64, i64, i64> threads_loop (i64 iterations) {
  i64 x = 1;
  i64 n_threads = 4;

  std::vector<std::thread> threads_f1, threads_f2, threads_f3;

  for (int t = 0; t < n_threads; t++) {
      threads_f1.push_back(std::thread(thread_function, iterations / n_threads, x, f1));
      threads_f2.push_back(std::thread(thread_function, iterations / n_threads, x, f2));
      threads_f3.push_back(std::thread(thread_function, iterations / n_threads, x, f3));
  }
  
  for (int t = 0; t < n_threads; t++) {
      threads_f1[t].join();
      threads_f2[t].join();
      threads_f3[t].join();
  }

  return make_tuple(x, x, x);
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
  
  return 0;
}
