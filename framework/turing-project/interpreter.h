#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
using namespace std;

typedef struct
{
    string old_state;
    string old_symbol;
    string new_symbol;
    string direction;
    string new_state;
    inline void print(){
        printf("%s %s %s %s %s \n",old_state.c_str(),old_symbol.c_str(),new_symbol.c_str(),direction.c_str(),new_state.c_str());
    }
}delta;

class Turing_machine{
protected:
    set<string> Q;
    set<string> S;
    set<string> G;
    string q0;
    char B;
    set<string> F;
    int N;
    vector<delta> delta_functions;
private:
    void _print_set(set<string> strset);
    void _StringSplit(string str,const char split,set<string> &output,int mode);
    void _addDelta(string str,vector<delta> &output);
    void _set(string str);
    void _check_syntax(int &linecnt,string str);
    void _checkcheck(string token,int mode);
public:
    Turing_machine(char *path);
    void print_TM();
};

#endif