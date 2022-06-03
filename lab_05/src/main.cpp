#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <map>
#include <utility>
#include <sstream>
#include <thread>
#include <cmath>
#include <chrono>
#include <vector>
#include <thread>
#include <functional>

using namespace std;


inline constexpr std::uint32_t hashstring(const char* str, std::uint32_t hash = 2166136261UL) {
    return *str ? hashstring(str + 1, (hash ^ *str) * 16777619ULL) : hash;
}
 
 
class BinaryAction {
   public:
      virtual string getOutput() = 0;

    protected:
        double a, b;
        string c, d;
};


class UnaryAction {
   public:
      virtual string getOutput() = 0;

    protected:
        string a;
};

 
class PlusAction: public BinaryAction {
    public:
        PlusAction(double a_in, double b_in) { a = a_in; b = b_in; }
        string getOutput() { 
            return to_string(a + b); 
        }
};


class MinusAction: public BinaryAction {
   public:
           MinusAction(double a_in, double b_in) { a = a_in; b = b_in; }

      string getOutput() { 
         return to_string(a - b); 
      }
};


class MulAction: public BinaryAction {
   public:
   MulAction(double a_in, double b_in) { a = a_in; b = b_in; }

      string getOutput() { 
         return to_string(a * b); 
      }
};


class DivAction: public BinaryAction {
   public:
   DivAction(double a_in, double b_in) { a = a_in; b = b_in; }
      string getOutput() { 
         
         return (b != 0) ? to_string(a * b) : "Division by zero" ; 
      }
};


class ToFileAction: public BinaryAction {
   public:
   ToFileAction(string c_in, string d_in) { c = c_in; d = d_in; }
      string getOutput() { 
         write_to_file(c, d);
         return "String has written to file" ; 
      }

    private:
        void write_to_file(string filename, string s) {
            ofstream file;

            file.open(filename);
            file << s << endl;
            file.close();
        }
};


class CliAction: public UnaryAction {
   public:
   CliAction(string a_in) { a = a_in; }
      string getOutput() {
        cout << "--- " << a << " --- ";
        return "String has written to CLI"; 
      }
};


class Loop {
    int cnt;

    public: 
        Loop(int i) { cnt = i; }

        void run(PlusAction action) {
            for (int i = 0; i < cnt; i++) {
                cout << action.getOutput() << endl;
            }
        }

        void run(MinusAction action) {
            for (int i = 0; i < cnt; i++) {
                cout << action.getOutput() << endl;
            }
        }

        void run(MulAction action) {
            for (int i = 0; i < cnt; i++) {
                cout << action.getOutput() << endl;
            }
        }

        void run(DivAction action) {
            for (int i = 0; i < cnt; i++) {
                cout << action.getOutput() << endl;
            }
        }

        void run(CliAction action) {
            for (int i = 0; i < cnt; i++) {
                cout << action.getOutput() << endl;
            }
        }
};


class LoLanguage {
public:
    string source_code = "";
    queue <string> actions; 

    LoLanguage(string filename) {
        string line_tmp;
        ifstream file(filename);

        if (file.is_open()) {
            while (getline(file, line_tmp)) {
                source_code += line_tmp + "\n";
                if (line_tmp != "")
                    actions.push(line_tmp);
            }
            file.close();
        }
    }

    pair<string, string> splitAction(string s, string delimeter = " -> ") {
        string act, input;

        act = s.substr(0, s.find(delimeter));
        input = s.substr(s.find(delimeter) + delimeter.length(), s.length());

        return make_pair(act, input);
    }

    void do_all_actions() {
        pair<string, string> action_pair;

        while (!actions.empty()) {
            action_pair = splitAction(actions.front());
            if (action_pair.first.find("loop") == 0) {
                // cout << stoi(splitAction(action_pair.first, " ").second) << endl;
                for (int i = 0; i < stoi(splitAction(action_pair.first, " ").second); i++) {
                    do_action(action_pair.second);
                }
            }
            else
                do_action(actions.front());
            actions.pop();
        }
    }

    void threadFunction(string s, int thread_num) {
        cout << "[" << thread_num << "]" << " started" << endl;
        auto begin = chrono::high_resolution_clock::now();
        
        do_action(s, thread_num);

        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        cout << "[" << thread_num << "]" << " ended in " << elapsed.count() * 1e-9 << "s" << endl;
    }

    void loopThreadFunction(string s, int thread_num) {
        pair<string, string> action_pair;

        cout << "[" << thread_num << "]" << " started" << endl;
        auto begin = chrono::high_resolution_clock::now();
        
        action_pair = splitAction(s);
        for (int i = 0; i < stoi(splitAction(action_pair.first, " ").second); i++) {
            do_action(action_pair.second, thread_num);
        }

        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        cout << "[" << thread_num << "]" << " ended in " << elapsed.count() * 1e-9 << "s" << endl;
    }

    void do_all_actions_parallel() {
        vector<thread> threads;
        pair<string, string> action_pair;

        void (LoLanguage::*func)(string, int);

        int cnt = 0;
        while (!actions.empty()) {
            func = &LoLanguage::threadFunction;

            action_pair = splitAction(actions.front());
            if (action_pair.first.find("loop") == 0) {
                func = &LoLanguage::loopThreadFunction;
                threads.push_back(thread(func, *this, actions.front(), cnt)); // do_action(actions.front());
            }
            else
                threads.push_back(thread(func, *this, actions.front(), cnt)); // do_action(actions.front());

            cnt += 1;
            actions.pop();
        }

        for (int t = 0; t < threads.size(); t++) {
            threads[t].join();
        }
    }

    void do_action(string action, int thread=0) { 
        pair<string, string> action_pair = splitAction(action);
        string flag = action_pair.first;
        string input = action_pair.second;
        string a, b;

        if (thread)
            cout << "[" << thread << "]" << endl;

        switch (hashstring(flag.c_str())) {
            case hashstring("+"): {
                action_pair = splitAction(input, " ");
                a = action_pair.first;
                b = action_pair.second;
                PlusAction A(stod(a), stod(b));
                cout << A.getOutput() << endl;
                break;
            }
            case hashstring("-"): {
                action_pair = splitAction(input, " ");
                a = action_pair.first;
                b = action_pair.second;
                MinusAction A(stod(a), stod(b));
                cout << A.getOutput() << endl;
                break;
            }
            case hashstring("*"): {
                action_pair = splitAction(input, " ");
                a = action_pair.first;
                b = action_pair.second;
                MulAction A(stod(a), stod(b));
                cout << A.getOutput() << endl;
                break;
            }
            case hashstring("/"): {
                action_pair = splitAction(input, " ");
                a = action_pair.first;
                b = action_pair.second;
                DivAction A(stod(a), stod(b));
                cout << A.getOutput() << endl;
                break;
            }
            case hashstring("to_file"): {
                action_pair = splitAction(input, "<==");
                a = action_pair.first;
                b = action_pair.second;
                ToFileAction A(a, b);
                cout << A.getOutput() << endl;
                break;
            }
            case hashstring("to_cli"): {
                CliAction A(input);
                cout << A.getOutput() << endl;
                break;
            }
        }
    }
};


int main(void) {

    double a = 0.1;
    double b = 0.2;
    MulAction A(a, b);

    Loop loop(10);
    loop.run(A);
    cout << "=======" << endl;

    LoLanguage lang = LoLanguage("src/code.txt");
    lang.do_all_actions_parallel();

    string line;

    while (getline(cin, line)) {
        lang.do_action(line);
        if (line == "exit") { break; }

    }

   return 0;
}
