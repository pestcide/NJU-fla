#ifndef _SIMULATOR_H
#define _SIMULATOR_H
#include "interpreter.h"
#include <string>
#include <vector>
using namespace std;

class simulator:private Turing_machine
{
private:
    string _input;
    bool verbose_started=false;
    int step;
    string state;
    bool acc;
    vector<string> tape;
    vector<int> head;//磁头读取的index
    vector<int> zero_pos;//纸带在string上的0位置
    //string上的实际位置为head+zero_pos

    void _check_input();
    bool _inS(char t);
    void _init();

    bool _symbol_equal(string old_symbol,string new_symbol,int symbol_size);
    //!\brief return matched_delta's idx in deltas, return -1 if no one is found
    int _find_delta();
    //!\param delta_idx: matched_delta's idx
    void _write_over(int delta_idx);
    //!\param delta_idx: matched_delta's idx
    void _update_state(int delta_idx);
    //!\param delta_idx: matched_delta's idx
    void _move_head(int delta_idx);
    void _transform();
    void _print_tape(int num);
public:
    simulator(char *path,char *input,bool verbose);
    void run();
    void nomal_print();
    void verbose_print();
};
#endif