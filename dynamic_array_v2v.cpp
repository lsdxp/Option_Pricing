//
//  main.cpp
//  dynamic_array_v2v
//
//  Created by Shengdong  Liu on 9/1/15.
//  Copyright (c) 2015 Shengdong  Liu. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, const char * argv[]) {
  
    vector<vector<int>>test;
    int n,m;
    
    cout<<"Rows?"<<endl;
    cout<<"Cols?"<<endl;
    cin>>n;
    cin>>m;
    
    for(int i=0;i<n;i++)
    {
        vector<int> temp;
        test.push_back(temp);
    }
    
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {
            int value;
            cout<<"type the value of array["<<i<<"]["<<j<<"]="<<endl;
            cin>>value;
            test[i].push_back(value);
            
        }
    
    cout<<endl;
    
    for(int i=0;i<n;i++)
    {       for(int j=0;j<m;j++)
        {
            cout<<test[i][j]<<" ";
        }
    cout<<endl;
    }2
    
    return 0;
}
