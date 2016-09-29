 //
//  main.cpp
//  dynamic_array_p2p
//
//  Created by Shengdong  Liu on 9/1/15.
//  Copyright (c) 2015 Shengdong  Liu. All rights reserved.
//

#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    int n,m;
    
    cout<<"Rows?"<<endl;
    
    cout<<"Cols?"<<endl;
    cin>>n;
     cin>>m;
    
    double **array=new double*[n];
    
    for(int i=0;i<n;i++)
        
        array[i]=new double[m];
    
    cout<<"The value of array is:"<<array<<endl;
    cout<<"The content of array is:"<<*array<<endl;
    
    for(int i=0;i<n;i++)
        
        cout<<"The value of array["<<i<<"] is:"<<array[i]<<endl;
    
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
        {  cout<<"Type in the value of array["<<i<<"]["<<j<<"]";
            cin>>array[i][j];
        }
    
    cout<<"Printing the value of array"<<endl;
    for(int i=0;i<n;i++)
    {    for(int j=0;j<m;j++)
        {
            cout<<array[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
    
    for(int i=0;i<n;i++)
        cout<<"the content of array["<<i<<"]:"<<*array[i]<<endl;
    
    
    cout<<(*array[1])++<<endl;
    
 
    return 0;
}
