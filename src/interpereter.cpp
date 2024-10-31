#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include "core/FuckCore.h"

using namespace std;
using namespace BrainFuck;

int main(int argc,char** argv) {
    FuckCore core;

    if(argc==1) {
        while(true) {
            cout<<">>>";
            cout.flush();


            string input_string;
            if(getline(cin,input_string)) {
                if(input_string=="exit") {
                    return 0;
                }
                else {
                    // cin.ignore(numeric_limits< streamsize >::max(), '\n');
                    core.run_simple_string(input_string);
                }
            }
            else {
                break;
            }
        }

    }
    else if(argc == 2) {
        ifstream ifile(argv[1]);
        if(!ifile) {
            perror(argv[1]);
            return 1;
        }
        else {
            stringstream ss;
            ss<<ifile.rdbuf();
            core.run_simple_string(ss.str());
            cout<<'\n';
        }
    }
    return 0;
}
