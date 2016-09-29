#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cstdlib>



using namespace std;



double power1(double x, int n)
{

if (n == 0)
 return 1.0;
if (n == 0) return 1.0;
    return x*power1(x,n-1);
}

int main()
{
    double c;
 c=power1(2.0,5.0);
    cout<<c<<endl;;
    
}