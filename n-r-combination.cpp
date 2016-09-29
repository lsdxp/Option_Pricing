// A Program that generates all (n-take-r) combinations of objects stored in
// an array.
// The implementation is inspired by the material at the following URL:
// http://stackoverflow.com/questions/9430568/generating-combinations-in-c

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int size_of_array, number_of_objects_to_be_picked;
    int *array;
    
    cout << "Array Size? ";
    cin >> size_of_array;
    cout << "#Objects to be picked from array? ";
    cin >> number_of_objects_to_be_picked;
    
    // I am just filling the array with integers... it could be a list of
    // other objects, for example.
    array = new int[size_of_array];
    for (int i = 0; i < size_of_array; i++)
        array[i] = i+1;
    
    // Create a boolean array where the first n-r items are "true" (i.e. 1)
    // the remaining r items are "false" (i.e. 0)
    vector <bool> did_i_pick_this(size_of_array);
    fill(did_i_pick_this.begin(),
         did_i_pick_this.begin() +size_of_array-number_of_objects_to_be_picked, true);
        
    
    //change did_i_pick_this into ascending order for next_permutation
    sort(begin(did_i_pick_this),end(did_i_pick_this));
   
    // I am going to use the prev_permutation STL in C++ (see
    // http://www.cplusplus.com/reference/algorithm/prev_permutation/ )
    // to generate the required combinatorial outputs
  //  int j,n=0;
   //  int a[100];
    int j=0;
    do
    {
        cout<<j++;
        cout << "{ ";
       
        
        for (int i = 0; i < size_of_array; ++i)
        {
            //if the value is false, we should print it out
            

            if (did_i_pick_this[i]==false)
                
                cout << array[i] << " ";
        }
       // n++;
        cout << "}" << endl;
    }while (next_permutation(did_i_pick_this.begin(), did_i_pick_this.end()));
    
  //  for(int i=0;i<n;i++)
  //  {  cout<<"{"<<" ";
  //      j=j-number_of_objects_to_be_picked;
  //      for(int k=0;k<number_of_objects_to_be_picked;k++)
  //  {
        
  //   cout<<a[j+k]<<" ";
  //  }
     //   cout<<"}"<<endl;
  //  }
    return 0;
}