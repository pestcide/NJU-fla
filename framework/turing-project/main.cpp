#include <iostream>
#include <getopt.h> //included for `getopt_long`
#include <stdio.h>
#include <stdlib.h> //included for `EXIT_SUCCESS|EXIT_FAILURE`
#include "interpreter.h"
#include "simulator.h"
using namespace std;

static const struct option longopts[]{
    {"help",no_argument,NULL,'h'},
    {"verbose",no_argument,NULL,'v'},
    {NULL,0,NULL,0}
};

static void print_help(){
    cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
}

static void verbose_test(){
    cout << "verbose mode start" << endl;
}

int main(int argc, char* argv[]){
    
    if(argc == 1){
        print_help();
        return 1;
    }
    // cout<<"This is for testing"<<endl;
    // return 0;
    int optional=0;
    int optc;
    while ((optc=getopt_long(argc,argv,"hv",longopts,NULL))!=-1){
        switch(optc){
            case 'h':
                optional++;
                print_help();
                exit(EXIT_SUCCESS);
                break;
            case 'v':
                optional++;
                verbose_test();
                exit(EXIT_SUCCESS);
                break;
        }
    }
    if (argc==optional+3){
        tm_path=argv[optional+1];
        input=argv[optional+2];
        // cout << tm_path << endl;
        // cout << input << endl;
    }
    else{
        print_help();
        return 1;
    }
}