#include "simulator.h"
#include <iostream>
using namespace std;

simulator::simulator(char *path,char *input,bool verbose):Turing_machine(path,verbose){
    _input=input;
    verbose_started=verbose;
    //cout << _input << endl;
}

void simulator::_check_input(){
    for (int i=0;i<_input.size();++i)
    {
        if (!_inS(_input[i])) 
        {
            cerr << "illegal input string" << endl;
            if (verbose_started){
                cerr << "Input: " << _input << endl;
                cerr << "==================== ERR ====================" << endl;
                cerr << "error: Symbol \"" << _input[i] << "\" in input is not defined in the set of input symbols" << endl;
                cerr << "Input: " << _input << endl;
                cerr << "       ";
                for (int rijk=0;rijk<i;++rijk)
                    cerr << " ";
                cerr << "^" << endl;
                cerr << "==================== END ====================" << endl;
            }
            exit(1);
        }
    }
    if (verbose_started){
        cout << "Input: " << _input << endl;
        cout << "==================== RUN ====================" << endl;
    }
}

bool simulator::_inS(char t){
    string tmp="";
    tmp.push_back(t);
    return S.count(tmp);
}

void simulator::run(){
    _check_input();
    _init();
    _transform();
}

void simulator::_init(){
    step=0;
    state=q0;
    acc=false;
    tape.resize(N,"_");
    tape[0]=_input;
    head.resize(N,0);
    zero_pos.resize(N,0);
}

int simulator::_find_delta(){
    string _old_state=state;
    string _old_symbol;
    for (int i=0;i<N;++i)
        _old_symbol.push_back(tape[i][head[i]+zero_pos[i]]);
    for (int i=0;i<delta_functions.size();++i)
    {
        if (_old_state==delta_functions[i].old_state&&_old_symbol==delta_functions[i].old_symbol)
            return i;
    }
    return -1;
}

void simulator::_write_over(int delta_idx){
    string new_symbol=delta_functions[delta_idx].new_symbol;
    for (int i=0;i<N;++i){
        if (new_symbol[i]!='*')
            tape[i][head[i]+zero_pos[i]]=new_symbol[i];
    }
}

void simulator::_update_state(int delta_idx){
    state=delta_functions[delta_idx].new_state;
    if (F.count(state)) acc=true;
}

void simulator::_move_head(int delta_idx){
    string direction=delta_functions[delta_idx].direction;
    char direct;
    for (int i=0;i<N;++i){
        direct=direction[i];
        if (direct=='l'){
            head[i]--;
            if (head[i]+zero_pos[i]<0){
                tape[i].insert(0,1,'_');
                zero_pos[i]++;
            }
        }
        if (direct=='r'){
            head[i]++;
            if (head[i]+zero_pos[i]>=tape[i].size()){
                tape[i].push_back('_');
            }
        }
        else{
            continue;
        }
    }
}

void simulator::_transform(){
    int delta_idx=_find_delta();
    while (delta_idx!=-1){
        step++;
        _write_over(delta_idx);
        _update_state(delta_idx);
        _move_head(delta_idx);
        delta_idx=_find_delta();
    }
}

void simulator::nomal_print()
{
    if (acc)
        cout << "(ACCEPTED) ";
    else
        cout << "(UNACCEPTED) ";
    string output=tape[0];
    while (output.size()>0&&output.back()=='_') output.pop_back();
    while (output.size()>0&&output[0]=='_') {
        if (output.size()==1) output.pop_back();
        else output=output.substr(1);
    }
    cout << output << endl;
}