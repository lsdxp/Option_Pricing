
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cstdlib>

#include "lp_lib.h"

using namespace std;

const double ERROR = 1e-10;
int number_of_cash_flows;
vector <double> price_list;
vector <int> maturity_list;
vector <double> yield_to_maturity;
vector <double> duration;
vector <double> convexity;
double debt_obligation_amount;
double time_when_debt_is_due;
vector <double> percentage_of_cash_flow_to_meet_debt_obligation;

double function1(vector <double> cash_flow, double price, int maturity, double rate)
{   double f,temp;
    temp=0;
    for(int i=1;i<=maturity;i++)
        temp=temp+cash_flow[i]*(pow((1+rate),(maturity-i)));
        
        f=price*(pow((1+rate),maturity))-temp;
    
    return f;
    // write a function that computes f(r) in page 2 of lesson 3 of my notes
}

double derivative_function(vector <double> cash_flow, double price, int maturity, double rate)
{
    double f,temp;
    temp=0;
    for(int i=1;i<=(maturity-1);i++)
        temp=temp+cash_flow[i]*(maturity-i)*(pow((1+rate),(maturity-i-1)));
    
    f=maturity*price*(pow((1+rate),(maturity-1)))-temp;
    
    return f;
    
    // write a function that computes f'(r) in the bottom of page 2 of lesson 3
    // of my notes
}

double Newton_Raphson(vector <double> cash_flow, double price, int maturity, double rate)
{   double check=0;
    check=rate;
    rate=rate-function1(cash_flow,price,maturity,rate)/derivative_function(cash_flow,price,maturity,rate);
    if(abs(rate-check)<ERROR)
        return rate;
    return (Newton_Raphson(cash_flow,price,maturity,rate));
    // write a function that finds the (only) +ve root of f(r) of page 2 of
    // lesson 3 using Newton-Raphson method
}

double get_duration(vector <double> cash_flow, double price, int maturity, double rate)
{
    double N=0,temp=0;
    for(int i=1;i<=maturity;i++)
        temp=temp+cash_flow[i]*i*(pow((1+rate),(-i)));
    N=temp/price;
    return N;

    // write a function that computes the duration of a cash flow
}

double get_convexity(vector <double> cash_flow, double price, int maturity, double rate)
{
    double C=0,temp=0;
    for(int i=1;i<=maturity;i++)
        temp=temp+cash_flow[i]*i*(i+1)*(pow((1+rate),(-i-2)));
    C=temp/price;
    return C;
    // write a function that computes the convexity of a cash flow
}

double present_value_of_debt(double rate)
{
    double pv=0;
   // for(int i=0;i<number_of_cash_flows;i++)
     //   r+=yield_to_maturity[i];
   // r=r/number_of_cash_flows;
    pv=debt_obligation_amount/(pow((1+rate),time_when_debt_is_due));
    return pv;
    // compute PV of future debt obligation
}

void print_data(char *filename)
{
    cout << "Input File: " << filename << endl;
    cout << "We owe " << debt_obligation_amount << " in " << time_when_debt_is_due << " years" << endl;
    cout << "Number of Cash Flows: " << number_of_cash_flows << endl;
    for (int i = 0; i < number_of_cash_flows; i++)
    {
        cout << "---------------------------" << endl;
        cout << "Cash Flow #" << i+1 << endl;
        cout << "Price = " << price_list[i] << endl;
        cout << "Maturity = " << maturity_list[i] << endl;
        cout << "Yield to Maturity = " << yield_to_maturity[i] << endl;
        cout << "Duration = " << duration[i] << endl;
        cout << "Convexity = " << convexity[i] << endl;
        cout << "Percentage of Face Value that would meet the obligation = " <<
        percentage_of_cash_flow_to_meet_debt_obligation[i] << endl;
    }
    cout << "---------------------------" << endl;
}

void get_data(char* argv[])
{
    ifstream input_file(argv[1]);
    
    double value_just_read_from_file;
    vector <double> P; //vector of numbers
    
    // The input file name is "Data.txt"
    // It contains the numbers P_1 P_2 ... P_M
    
    if (input_file.is_open()) // If "Data.txt" exists in the local directory
    {
        while(input_file >> value_just_read_from_file) // As long as your are not at the "end-of-file"
        {
            P.push_back(value_just_read_from_file);
        }
    }
    else
        cout << "Input file Data.txt does not exist in PWD" << endl;
  //  time_when_debt_is_due=P.pop_back();
    //debt_obligation_amount=P.pop_back();
    //cout<<P[1];
    number_of_cash_flows=P[0];
    int j=2;
    for(int i=0;i<number_of_cash_flows;i++)
    {
            price_list.push_back(P[j-1]);
            maturity_list.push_back(P[j]);
            vector<double> cash_flow;
        cash_flow.push_back(0);
           // yield_to_maturity.push_back(P[j+1]/P[j-1]);
            for(int k=0;k<P[j];k++)
                cash_flow.push_back(P[j+1+k]);
        yield_to_maturity.push_back(Newton_Raphson(cash_flow, price_list[i], maturity_list[i], 0.067));
        duration.push_back( get_duration(cash_flow, price_list[i], maturity_list[i], yield_to_maturity[i]));
        convexity.push_back( get_convexity(cash_flow, price_list[i], maturity_list[i], yield_to_maturity[i]));
        
        
        j=j+P[j]+2;
    }
    time_when_debt_is_due=P[j];
    debt_obligation_amount=P[j-1];
    for(int i=0;i<number_of_cash_flows;i++)
        percentage_of_cash_flow_to_meet_debt_obligation.push_back(present_value_of_debt(yield_to_maturity[i])/price_list[i]);
    // write the code that reads the data from the file identified
    // on the command-line.
}

void get_optimal_portfolio()
{
    lprec *lp;
   double solution[number_of_cash_flows];
    
  //  REAL solution[2];
//    
//    // setting the problem up: 2 real variables
 //  lp = make_lp(0,2);
//    
//    // first constraint x1 + 2x2 <= 6
 //   {
//        double row[] = {0, 1, 2};
//       add_constraint(lp, row, LE, 6);
//   }
//    // second constraint 4x1 + 3x2 <= 12
//    {
//        double row[] = {0, 4, 3};
//        add_constraint(lp, row, LE, 12);
//    }
//    // objective function 7x1+5x2... since the regular lp_solve
//    // call minimizes the cost, and I am interested in maximizing
//    // I have to flip the signs of the coeeficients... I have to
//    // flip the sign of the optimal value back to get the maximum
//    // optimal value.
//    {
//        double row[] = {0, -7, -5};
//        set_obj_fn(lp, row);
//    }
//    
//    // solve the lp
//    solve(lp);
//    
//    // print optimal value
//    cout << "Optimal Value is: " << -1*get_objective(lp) << endl;
//    
//    // print the optimizing values of the variables
//    get_variables(lp, solution);
//    cout << "Optimal solution:" << endl;
//    for (int i = 0; i < 2; i++)
//        cout << "x[" << i+1 << "] = " << solution[i] << endl;
//    
//    // delete the lp to release memory
//    delete_lp(lp);
  
   // ------------------------------------------------------------------------------------------
    
    // setting the problem up: 5 real variables
   lp = make_lp(0,number_of_cash_flows);
    
     //first constraint x1 + 2x2 <= 6
    {
        double row[number_of_cash_flows+1];
        row[0]=0;
        //double row[]={0,2,5};
        for(int i=1;i<=number_of_cash_flows;i++)
            row[i]=percentage_of_cash_flow_to_meet_debt_obligation[i-1]*duration[i-1];
        add_constraint(lp, row, EQ, time_when_debt_is_due);
    }
    
   
    // objective function 7x1+5x2... since the regular lp_solve
    // call minimizes the cost, and I am interested in maximizing
    // I have to flip the signs of the coeeficients... I have to
    // flip the sign of the optimal value back to get the maximum
    // optimal value.
    {
        double row[number_of_cash_flows];
        row[0]=0;
        for(int i=1;i<=number_of_cash_flows;i++)
            row[i]=-percentage_of_cash_flow_to_meet_debt_obligation[i]*convexity[i];

        
        set_obj_fn(lp, row);
    }
    
    // solve the lp
    solve(lp);
    
    // print optimal value
    cout << "Optimal Value is: " << -1*get_objective(lp) << endl;
    
    // print the optimizing values of the variables
    get_variables(lp, solution);
    cout << "Optimal solution:" << endl;
    for (int i = 0; i < number_of_cash_flows; i++)
        cout << "x[" << i+1 << "] = " << solution[i] << endl;
    
    // delete the lp to release memory
    delete_lp(lp);
    
    //return(0);
    
//-------------------------------
    
    
    // write the lp_solve specific material that
    // computes the optimal_portfolio
    
}

int main (int argc, char* argv[])
{
    if (argc == 1) {
        cout << "Input filename missing" << endl;
    }
    else 
    {
        get_data(argv);
        
        print_data(argv[1]);
        
        get_optimal_portfolio();
    }
    return (0);
}
