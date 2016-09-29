//
//  main.cpp
//  commandlinetest
//

//

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char * argv[]) {
    // insert code here...
    int first_command_line_variable;
    sscanf(argv[1], "%d", &first_command_line_variable);
    
    double second_command_line_variable;
    sscanf(argv[2], "%lf", &second_command_line_variable);
    
    cout<<"The value of the first command line variable is:"<<first_command_line_variable<<endl;
    cout<<"The value of the second command line variable is:"<<second_command_line_variable<<endl;
    
    
    ifstream input_file(argv[3]);
    
    double value_just_read_from_file;
    vector<double> P;
    
    if (input_file.is_open())
    {
        while (input_file>>value_just_read_from_file) {
            P.push_back(value_just_read_from_file);
        }
    
    cout<<"The name of file contains P is:"<<argv[3]<<endl;
    
    cout<<"Vector P has "<<P.size()<<" entries and they are:"<<endl;
    
    for(int i=0;i<P.size();i++)
        cout<<P[i]<<"\t";
    
        cout<<endl;
    }
    else
        cout<<"Input file:"<<argv[3]<<"does not exist in PWD"<<endl;
        
        
    
    
    
    return 0;
}
