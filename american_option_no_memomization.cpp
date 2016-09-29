#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
using namespace std;

double up_factor, uptick_prob, downtick_prob, notick_prob, risk_free_rate, strike_price;
double initial_stock_price, expiration_time, volatility, R;
int no_of_divisions;

double max(double a, double b) {
    return (b < a )? a:b;
}


double american_call_option(int k, int i, double current_stock_price)
{
    
    if (k == no_of_divisions)
    {             return max(0.0, (current_stock_price - strike_price));;
    }
    else
    {
        return max((current_stock_price - strike_price),
                   (uptick_prob*american_call_option(k+1, i+1, current_stock_price*up_factor) +
                    (downtick_prob)*american_call_option(k+1, i-1, current_stock_price/up_factor)+(notick_prob)*american_call_option(k+1, i, current_stock_price))/R);;
    }
    // fill this part for the 10th programming assignment
}

double american_put_option(int k, int i, double current_stock_price)
{
    
    
    if (k == no_of_divisions)
    {
        
      
        return max(0.0, (strike_price - current_stock_price));
    }
    
    // return max(0.0, (strike_price - current_stock_price));
    else
    {
        
        return max((strike_price - current_stock_price),
                   (uptick_prob*american_put_option(k+1, i+1, current_stock_price*up_factor) +
                    (downtick_prob)*american_put_option(k+1, i-1, current_stock_price/up_factor)+(notick_prob)*american_put_option(k+1, i, current_stock_price))/R);
    }
    
    
    //     return max((strike_price - current_stock_price),
    //                   (uptick_prob*american_put_option(k+1, i+1, current_stock_price*up_factor) +
    //                    (downtick_prob)*american_put_option(k+1, i-1, current_stock_price/up_factor)+(notick_prob)*american_put_option(k+1, i, current_stock_price))/R);
    
    // fill this part for the 10th programming assignment
}

int main (int argc, char* argv[])
{
    
    sscanf (argv[1], "%lf", &expiration_time);
    sscanf (argv[2], "%d", &no_of_divisions);
    sscanf (argv[3], "%lf", &risk_free_rate);
    sscanf (argv[4], "%lf", &volatility);
    sscanf (argv[5], "%lf", &initial_stock_price);
    sscanf (argv[6], "%lf", &strike_price);
    
    R = exp(risk_free_rate*expiration_time/((float) no_of_divisions));
    up_factor = exp(volatility*sqrt((2*expiration_time)/((float) no_of_divisions)));
    uptick_prob = pow((sqrt(R) - 1/sqrt(up_factor))/(sqrt(up_factor)-1/sqrt(up_factor)),2);
    downtick_prob = pow((sqrt(up_factor) - sqrt(R))/(sqrt(up_factor)-1/sqrt(up_factor)),2);
    notick_prob = 1 - uptick_prob - downtick_prob;
    
    cout << "Recursive Trinomial American Option Pricing" << endl;
    cout << "Expiration Time (Years) = " << expiration_time << endl;
    cout << "Number of Divisions = " << no_of_divisions << endl;
    cout << "Risk Free Interest Rate = " << risk_free_rate << endl;
    cout << "Volatility (%age of stock value) = " << volatility*100 << endl;
    cout << "Initial Stock Price = " << initial_stock_price << endl;
    cout << "Strike Price = " << strike_price << endl;
    cout << "--------------------------------------" << endl;
    cout << "R = " << R << endl;
    cout << "Up Factor = " << up_factor << endl;
    cout << "Uptick Probability = " << uptick_prob << endl;
    cout << "Downtick Probability = " << downtick_prob << endl;
    cout << "Notick Probability = " << notick_prob << endl;
    cout << "--------------------------------------" << endl;
    cout << "Trinomial Price of an American Call Option = " << american_call_option(0, 0,initial_stock_price) << endl;
    cout << "Trinomial Price of an American Put Option = " << american_put_option(0, 0, initial_stock_price) << endl;
}
