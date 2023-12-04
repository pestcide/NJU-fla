#include "interpreter.h"
#include <iostream>
using namespace std;

Turing_machine::Turing_machine(char *path){
    //cout << "entered TM" << endl;
    fstream fs;
    fs.open(path);
    string s;
    while (getline(fs,s)){
        //cout << s << endl;
        if (s.empty()) continue;
        int begin=0;
        while (s[begin]==' '){
            begin++;
            if (begin==s.size())
                break;
        }
        if (begin==s.size()) continue;
        int end=0;
        while (s[end]!=';'){
            end++;
            if (end==s.size())
                break;
        }
        end--;
        string tmp=s.substr(begin,end-begin+1);
        if (tmp.empty()) continue;
        //cout << tmp << endl;
        _set(tmp);
    }
    //print_TM();
}

void Turing_machine::_StringSplit(string str,const char split,set<string> &output){
    istringstream iss(str);	
	string token;
	while (getline(iss, token, split)){
		output.emplace(token);
	}
}

void Turing_machine::_addDelta(string str,vector<delta> &output){
    istringstream iss(str);	
	string token;
    delta tmp;
    int id=0;
	while (getline(iss, token, ' ')){
        switch (id)
        {
        case 0:
            tmp.old_state=token;
            break;
        case 1:
            tmp.old_symbol=token;
        case 2:
            tmp.new_symbol=token;
        case 3:
            tmp.direction=token;
        case 4:
            tmp.new_state=token;
        default:
            break;
        }
        id++;
    }
    output.push_back(tmp);
}

void Turing_machine::_set(string str){
    if (str[0]=='#'){
        char mode=str[1];
        string tmp=str.substr(6,str.size()-7);
        istringstream iss(str.substr(5,str.size()-5));
        switch (mode){
        case 'Q':
            _StringSplit(tmp,',',Q);
            break;
        case 'S':
            _StringSplit(tmp,',',S);
            break;
        case 'G':
            _StringSplit(tmp,',',G);
            break;
        case 'F':
            _StringSplit(tmp,',',F);
            break;
        case 'q':
            q0=str.substr(6,str.size()-6);
            break;
        case 'B':
            B='_';
            break;
        case 'N':
            iss >> N;
            break;
        default:
            break;
        }
    }
    else    
        _addDelta(str,delta_functions);
}

void Turing_machine::_print_set(set<string> strset){
    set<string>::iterator it;
    for (it=strset.begin();it!=strset.end();++it){
        cout << *it << " " ;
    }
    cout << endl;
}

void Turing_machine::print_TM(){
    cout << "Q:" << endl;
    _print_set(Q);
    cout << "S:" << endl;
    _print_set(S);
    cout << "G:" << endl;
    _print_set(G);
    cout << "q0:" << endl;
    cout << q0 << endl;
    cout << "B:" << endl;
    cout << B << endl;
    cout << "F:" << endl;
    _print_set(F);
    cout << "N = " << N << endl;
    cout << "delta_functions:" << endl;
    for (int i=0;i<delta_functions.size();++i){
        delta_functions[i].print();
    }
}