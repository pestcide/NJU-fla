#include "interpreter.h"
#include <iostream>
#define STATE 1
#define SYMBOL_ 2
#define SYMBOL 3 
using namespace std;

void Turing_machine::syntaxerror() {
    cerr << "syntax error" << endl;
    if (verbose_started) {
        cerr << "error in line " << line_num  << endl;
        cerr << verbose_string << endl;
    }
    exit(1);
}

inline bool check(int mode,char t)
{
    bool alpha=(t>='a'&&t<='z')||(t>='A'&&t<='Z');
    bool number=(t>='0'&&t<='9');
    bool underline=(t=='_');
    bool special=(t==' '||t==','||t==';'||t=='{'||t=='}'||t=='*');
    if (mode==1||mode==4||mode==6) return alpha||number||underline;
    if (mode==2) return !(underline||special);
    if (mode==3) return !special;
}

inline bool check_for_state(string token)
{
    for (int i=0;i<token.size();++i)
    {
        if (!check(STATE,token[i])) return false;
    }
    return true;
}

inline bool check_for_symbol_(string token){
    if (token.size()!=1) return false;
    return check(SYMBOL_,token[0]);
}

inline bool check_for_symbol(string token){
    if (token.size()!=1) return false;
    return check(SYMBOL,token[0]);
}

void Turing_machine::_checkcheck(string token,int mode){
    switch (mode)
    {
    case STATE:
        if (!check_for_state(token)) syntaxerror();
        break;
    case SYMBOL_:
        if (!check_for_symbol_(token)) syntaxerror();
        break;
    case SYMBOL:
        if (!check_for_symbol(token)) syntaxerror();
    default:
        break;
    }
}

Turing_machine::Turing_machine(char *path,bool verbose){
    //cout << "entered TM" << endl;
    verbose_started=verbose;
    fstream fs;
    fs.open(path);
    string s;
    int linecnt=0;
    while (getline(fs,s)){
        if (verbose_started) {
            line_num++;
            verbose_string=s;
        }
        //cout << s << endl;
        //除去字符串前部空格以及';'后面字符
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

        //除去字符串尾部空格
        while (tmp.back()==' ') tmp.pop_back();

        if (tmp.empty()) continue;
        //cout << tmp << endl;
        _check_syntax(linecnt,tmp);
        _set(tmp);
    }
    //print_TM();
}

void Turing_machine::_check_syntax(int &linecnt,string str){
    if (linecnt<8)
        linecnt++;
    if (linecnt==1){
        if (str[0]!='#'||str[1]!='Q'||str[3]!='='||str[5]!='{'||str.back()!='}') syntaxerror();   
    }
    if (linecnt==2){
        if (str[0]!='#'||str[1]!='S'||str[3]!='='||str[5]!='{'||str.back()!='}') syntaxerror();   
    }
    if (linecnt==3){
        if (str[0]!='#'||str[1]!='G'||str[3]!='='||str[5]!='{'||str.back()!='}') syntaxerror();   
    }
    if (linecnt==4){
        if (str[0]!='#'||str[1]!='q'||str[2]!='0'||str[4]!='=') syntaxerror();
    }
    if (linecnt==5){
        if (str[0]!='#'||str[1]!='B'||str[3]!='=') syntaxerror();
    }
    if (linecnt==6){
        if (str[0]!='#'||str[1]!='F'||str[3]!='='||str[5]!='{'||str.back()!='}') syntaxerror();
    }
    if (linecnt==7){
        if (str[0]!='#'||str[1]!='N'||str[3]!='=') syntaxerror();
    }
}

void Turing_machine::_StringSplit(string str,const char split,set<string> &output,int mode){
    istringstream iss(str);	
	string token;
	while (getline(iss, token, split)){
        _checkcheck(token,mode);
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
            break;
        case 2:
            tmp.new_symbol=token;
            break;
        case 3:
            tmp.direction=token;
            break;
        case 4:
            tmp.new_state=token;
            break;
        default:
            break;
        }
        id++;
    }
    if (id!=5)
        syntaxerror();
    output.push_back(tmp);
}

void Turing_machine::_set(string str){
    if (str[0]=='#'){
        char mode=str[1];
        string tmp=str.substr(6,str.size()-7);
        istringstream iss(str.substr(5,str.size()-5));
        switch (mode){
        case 'Q':
            _StringSplit(tmp,',',Q,STATE);
            break;
        case 'S':
            _StringSplit(tmp,',',S,SYMBOL_);
            break;
        case 'G':
            _StringSplit(tmp,',',G,SYMBOL);
            break;
        case 'F':
            _StringSplit(tmp,',',F,STATE);
            break;
        case 'q':
            q0=str.substr(6,str.size()-6);
            _checkcheck(q0,STATE);
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