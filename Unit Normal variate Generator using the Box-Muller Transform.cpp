// Unit Normal variate Generator using the Box-Muller Transform
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
using namespace std;

#define pi 3.141592626535
#define Cauchy_DENSITY(x) (1/pi)*(1/(1+x*x))

float get_uniform()
{
    return (((float) random())/(pow(2.0, 31.0)-1.0));
}

float get_Cauchy()
{
    return (tan(pi*(get_uniform()-0.5)));
}

int main (int argc, char* argv[])
{
    float y, cdf_Cauchy[100];
    int no_of_trials, count[100];
    float mean=0.0;
    
    sscanf (argv[1], "%d", &no_of_trials);
    ofstream cdf_comparison_file(argv[2]);
    ofstream pdf_comparison_file(argv[3]);
    
    //initialization
    for (int i = 0; i < 100; i++) {
        count[i] = 0;
        cdf_Cauchy[i] = 0.0;
    }
    
    //simulation
    for (int i = 0; i < no_of_trials; i++) {
        y = get_Cauchy();
        mean=mean+y;
        for (int j = 0; j < 100; j++)
            if ( (y >= ((float) (j-51)/10)) && (y < ((float) (j-50)/10)) )
                count[j]++;
    }
    
    //cdf
    for (int j = 1; j < 100; j++)
        cdf_Cauchy[j] = cdf_Cauchy[j-1] +
        (Cauchy_DENSITY((float) (j-50)/10));
    
    //
    int sum = 0;
    for (int j = 0; j < 100; j++) {
        sum += count[j];
        cdf_comparison_file << ((float) (j-50)/10) << ", " << ((float) sum/no_of_trials) << ", "
        << cdf_Cauchy[j] << endl;
        pdf_comparison_file << ((float) (j-50)/10) << ", " <<
        10*((float) count[j]/no_of_trials) << ", " <<
        (Cauchy_DENSITY((float) (j-50)/10)) << endl;
    }
    cout<<"mean of"<<no_of_trials<<"-many trials is "<<mean/no_of_trials<<endl;
}