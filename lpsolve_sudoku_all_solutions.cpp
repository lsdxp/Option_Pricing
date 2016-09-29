
// A Sudoku Solver in C++
// This is written in a "C" like syntax.  You can think about how to
// put this into an include file etc on your own.
//
// There is an ILP formulation for any 9 x 9 Sudoku Puzzle
// See the handout for the formulation -- there are 729 variables
// with a whole lot of constraints that is driven by the input
// (which is the incomplete board-layout).  You can write this
// (moderate-size) ILP automatically in C++, which is then solved
// using the API for Lpsolve.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>

#include "lp_lib.h"

using namespace std;

// Global variables for the problem 9*9*9 = 729
// See my handout for further explanations
lprec *lp;
double solution[729];

// This sets the generic ILP for the Sudoku Puzzle
// It does not use any of the pre-determined board-positions,
// that part is done after the input file is read.
void set_sudoku_ilp()
{
    // setting the problem up: 9*9*9 = 729 variables
    lp = make_lp(0,729);
    
    // This keeps the message reporting of lp_solve to a minimum
    set_verbose(lp, 3);
    
    {
        for (int i = 1; i <= 9; i++)
        {
            for (int j = 1; j <= 9; j++)
            {
                // constraint that says each (i,j) entry in the 9x9 table
                // should have one number in it
                // creating a row with 1's at the right spot (the first
                // entry has to be a zero; this is idiosynchratic of lpsolve)
                
                double row[730];
                for (int k = 0; k < 730; k++)
                    row[k] = 0;
                
                for (int k = 1; k <= 9; k++)
                { row[(81*(i-1)) + (9*(j-1)) + k] = 1;
                  //  cout<<81*(i-1)<<" "<<(9*(j-1))<<" "<<k<<endl;
                }
             //   cout<<"  row1 "<<endl;
                // adding the constraint
                add_constraint(lp, row, EQ, 1);
            }
        }
    }
    
  //  cout<<"row1 finish"<<endl;
    
    { //double row2[730];
        
        for (int i = 1; i <= 9; i++)
        {
            for (int k = 1; k <= 9; k++)
            {
                
                double row2[730];
                for (int j = 0; j < 730; j++)
                    row2[j] = 0;
                //make sure every number appears only once for each row
                for (int j= 1; j <= 9; j++)
                { row2[(81*(i-1)) + (9*(j-1)) + k] = 1;
                  //  cout<<81*(i-1)<<" "<<(9*(j-1))<<" "<<k<<endl;
                }
               // cout<<"  row2 "<<endl;
                // adding the constraint
                add_constraint(lp, row2, EQ, 1);
            }
        }
        // add_constraint(lp, row2, EQ, 1);
        // Using the above code as a guide, put the appropriate lines that
        // articulate the constraint that says each number must appear once
        // in each row in the 9x9 table; create a bunch of rows with 1's at
        // the right spot (the first entry has to be a zero; this is
        // idiosynchratic of lpsolve)
    }
  //  cout<<"row2 finish"<<endl;
    
    
    
    { //double row3[730];
        
        for (int j = 1; j <= 9; j++)
        {
            for (int k = 1; k <= 9; k++)
            {
                double row3[730];
                
                for (int i = 0; i < 730; i++)
                    row3[i] = 0;
                //make sure every number appears only once for each column
                for (int i= 1; i <= 9; i++)
                { row3[(81*(i-1)) + (9*(j-1)) + k] = 1;
                 //   cout<<81*(i-1)<<" "<<(9*(j-1))<<" "<<k<<endl;
             }
               // cout<<"  row3 "<<endl;
                // adding the constraint
                add_constraint(lp, row3, EQ, 1);
            }
        }
        
        //add_constraint(lp, row3, EQ, 1);
        // Using the above code as a guide, put the appropriate lines that
        // articulate the constraint that says each number must appear once
        // in each column in the 9x9 table; create a bunch of rows with 1's at
        // the right spot (the first entry has to be a zero; this is
        // idiosynchratic of lpsolve)
    }
    
    //cout<<"row3 finish"<<endl;
    
    
    
    
    
    
    //    for (int i = 1; i <= 9; i++)
    //    {
    //        for (int j = 1; j <= 9; j++)
    //        {
    //            // constraint that says each (i,j) entry in the 9x9 table
    //            // should have one number in it
    //            // creating a row with 1's at the right spot (the first
    //            // entry has to be a zero; this is idiosynchratic of lpsolve)
    //                 double row4[730];
    //
    //            for (int k = 0; k < 730; k++)
    //                row4[k] = 0;
    //        }
    //    }
    
    
    // making sure each number occurs once within each block
    // Block 1
    {
        for (int k = 1; k <= 9; k++)
        {
            double row4[730];
            for (int k = 0; k < 730; k++)
                row4[k] = 0;
            
            //make sure every number appears only once for each block
            for (int i= 1; i <= 3; i++)
                for (int j = 1; j <=3; j++)
                {row4[(81*(i-1)) + (9*(j-1)) + k] = 1;
                  //  cout<<81*(i-1)<<" "<<(9*(j-1))<<" "<<k<<endl;
                    
                }
          //  cout<<"  row4 "<<endl;
            add_constraint(lp, row4, EQ, 1);
            // Using the above code as a guide, put the appropriate lines that
            // articulate theconstraint that says each number must appear once
            // in each 3 x 3 block; create a bunch of rows with 1's at the right
            // spot (the first entry has to be a zero; this is idiosynchratic of
            // lpsolve)
        }
    }
  //  cout<<"row4 finish"<<endl;
    // Block 2
    {
        for (int k = 1; k <= 9; k++)
        {
            double row5[730];
            for (int k = 0; k < 730; k++)
                row5[k] = 0;
            
            for (int i= 4; i <= 6; i++)
                for (int j = 1; j <=3; j++)
                {  row5[(81*(i-1)) + (9*(j-1)) + k] = 1;
                   // cout<<81*(i-1)<<" "<<(9*(j-1))<<" "<<k<<endl;
                    
                }
            
            add_constraint(lp, row5, EQ, 1);
            // Using the above code as a guide, put the appropriate lines that
            // articulate theconstraint that says each number must appear once
            // in each 3 x 3 block; create a bunch of rows with 1's at the right
            // spot (the first entry has to be a zero; this is idiosynchratic of
            // lpsolve)
        }
    }
    
    // Block 3
    {
        for (int k = 1; k <= 9; k++)
        {
            
            double row6[730];
            
            for (int k = 0; k < 730; k++)
                row6[k] = 0;
            
            
            
            for (int i= 7; i <= 9; i++)
                for (int j = 1; j <=3; j++)
                {  row6[(81*(i-1)) + (9*(j-1)) + k] = 1;
                   // cout<<81*(i-1)<<" "<<(9*(j-1))<<" "<<k<<endl;
                    
                }
            
            
            add_constraint(lp, row6, EQ, 1);
            // Using the above code as a guide, put the appropriate lines that
            // articulate theconstraint that says each number must appear once
            // in each 3 x 3 block; create a bunch of rows with 1's at the right
            // spot (the first entry has to be a zero; this is idiosynchratic of
            // lpsolve)
        }
    }
    
    // Block 4
    {
        for (int k = 1; k <= 9; k++)
        {
            
            double row7[730];
            
            for (int k = 0; k < 730; k++)
                row7[k] = 0;
            
            
            for (int i= 1; i <= 3; i++)
                for (int j = 4; j <=6; j++)
                { row7[(81*(i-1)) + (9*(j-1)) + k] = 1;
                   // cout<<81*(i-1)<<" "<<(9*(j-1))<<" "<<k<<endl;
                    
                }
            
            add_constraint(lp, row7, EQ, 1);
            // Using the above code as a guide, put the appropriate lines that
            // articulate theconstraint that says each number must appear once
            // in each 3 x 3 block; create a bunch of rows with 1's at the right
            // spot (the first entry has to be a zero; this is idiosynchratic of
            // lpsolve)
        }
    }
    
    // Block 5
    {
        
        
        for (int k = 1; k <= 9; k++)
        {
            double row8[730];
            
            for (int k = 0; k < 730; k++)
                row8[k] = 0;
            
            
            for (int i= 4; i <= 6; i++)
                for (int j = 4; j <=6; j++)
                {row8[(81*(i-1)) + (9*(j-1)) + k] = 1;
                   // cout<<81*(i-1)<<" "<<(9*(j-1))<<" "<<k<<endl;
                    
                }
            
            add_constraint(lp, row8, EQ, 1);
            // Using the above code as a guide, put the appropriate lines that
            // articulate theconstraint that says each number must appear once
            // in each 3 x 3 block; create a bunch of rows with 1's at the right
            // spot (the first entry has to be a zero; this is idiosynchratic of
            // lpsolve)
        }
    }
    
    // Block 6
    {
        for (int k = 1; k <= 9; k++)
        {
            
            double row9[730];
            
            for (int k = 0; k < 730; k++)
                row9[k] = 0;
            
            for (int i= 7; i <= 9; i++)
                for (int j =1 ; j <=3; j++)
                { row9[(81*(i-1)) + (9*(j-1)) + k] = 1;
                   // cout<<81*(i-1)<<" "<<(9*(j-1))<<" "<<k<<endl;
                    
                }
            
            add_constraint(lp, row9, EQ, 1);
            // Using the above code as a guide, put the appropriate lines that
            // articulate theconstraint that says each number must appear once
            // in each 3 x 3 block; create a bunch of rows with 1's at the right
            // spot (the first entry has to be a zero; this is idiosynchratic of
            // lpsolve)
        }
    }
    
    // Block 7
    {
        for (int k = 1; k <= 9; k++)
        {
            
            double row10[730];
            for (int k = 0; k < 730; k++)
                row10[k] = 0;
            
            
            for (int i= 1; i <= 3; i++)
                for (int j = 7; j <=9; j++)
                { row10[(81*(i-1)) + (9*(j-1)) + k] = 1;
                  //  cout<<81*(i-1)<<" "<<(9*(j-1))<<" "<<k<<endl;
                    
                }
            
            add_constraint(lp, row10, EQ, 1);
            // Using the above code as a guide, put the appropriate lines that
            // articulate theconstraint that says each number must appear once
            // in each 3 x 3 block; create a bunch of rows with 1's at the right
            // spot (the first entry has to be a zero; this is idiosynchratic of
            // lpsolve)
        }
    }
    
    // Block 8
    {
        
        
        
        for (int k = 1; k <= 9; k++)
        {
            double rowb8[730];
            
            for (int k = 0; k < 730; k++)
                rowb8[k] = 0;
            for (int i= 4; i <= 6; i++)
                for (int j = 7; j <=9; j++)
                { rowb8[(81*(i-1)) + (9*(j-1)) + k] = 1;
                   // cout<<81*(i-1)<<" "<<(9*(j-1))<<" "<<k<<endl;
                    
                }
            
            add_constraint(lp, rowb8, EQ, 1);
            // Using the above code as a guide, put the appropriate lines that
            // articulate theconstraint that says each number must appear once
            // in each 3 x 3 block; create a bunch of rows with 1's at the right
            // spot (the first entry has to be a zero; this is idiosynchratic of
            // lpsolve)
        }
    }
    
    // Block 9
    {
        for (int k = 1; k <= 9; k++)
        {
            
            double rowb9[730];
            for (int k = 0; k < 730; k++)
                rowb9[k] = 0;
            
            for (int i= 7; i <= 9; i++)
                for (int j = 7; j <=9; j++)
                {  rowb9[(81*(i-1)) + (9*(j-1)) + k] = 1;
                   // cout<<81*(i-1)<<" "<<(9*(j-1))<<" "<<k<<endl;
                    
                }
            
            add_constraint(lp, rowb9, EQ, 1);
            // Using the above code as a guide, put the appropriate lines that
            // articulate theconstraint that says each number must appear once
            // in each 3 x 3 block; create a bunch of rows with 1's at the right
            // spot (the first entry has to be a zero; this is idiosynchratic of
            // lpsolve)
        }
    }
    
    
    
    // upper-bound each variable by 1
    for (int i = 1; i <= 729; i++)
    {
        double row[730];
        for (int j = 0; j < 730; j++)
            row[j] = 0;
        row[i] = 1;
        add_constraint(lp, row, LE, 1);
    }
    
    // it does not matter what the objective function (why?)
    // I am minimizing the sum of all variables.
    {
        double row[730];
        for (int i = 1; i < 730; i++)
            row[i] = 1;
        row[0] = 0;
        
        set_obj_fn(lp, row);
    }
    
    // set the variables to be integers
    for (int i = 1; i <= 729; i++)
        set_int(lp, i, TRUE);
}

// This subroutine reads the incomplete board-information from the
// input file and sets the appropriate constraints before the ILP
// is solved.


int value_just_read1[9][9];

void read_input_data(char* argv[])
{
    
    
    
    // reading the input filename from commandline
    ifstream input_filename(argv[1]);
    
    if (input_filename.is_open()) {
        
        cout << "Input File Name: " << argv[1] << endl;
        cout << endl << "Initial Board Position" << endl;
        for (int i = 1; i <= 9; i++)
        {
            
            for (int j = 1; j <= 9; j++)
            {
                double r[730];
                for (int k = 0; k < 730; k++)
                    r[k] = 0;
                int value_just_read;
                input_filename >> value_just_read;
                value_just_read1[i-1][j-1]=value_just_read;
                
                // check if we have a legitimate integer between 1 and 9
                if ((value_just_read >= 1) && (value_just_read <= 9))
                {
                    // printing initial value of the puzzle with some formatting
                    cout << value_just_read << " ";
                    r[(81*(i-1)) + (9*(j-1)) + value_just_read] = 1;
                    add_constraint(lp, r, EQ, 1);
                    // add appropriate constraints that bind the value of the
                    // appropriate variables based on the incomplete information
                    // that was read from the input file
                }
                else {
                    // printing initial value of the puzzle with some formatting
                    cout << "X ";
                }
                
                
                
                
            }
            
            cout << endl;
        }
    }
    else {
        cout << "Input file missing" << endl;
        exit(0);
    }
    
    
}

// The ILP formulation is solved using the API for Lpsolve
// Pay attention to how the solution is interpretted...
void solve_the_puzzle()
{
    // tracking the number of solutions
    int number_of_solutions = 0;
    
    while (0 == solve(lp))
    {
        number_of_solutions++;
        // get the optimal assignment
        get_variables(lp, solution);
        
        // print the solution
        cout << endl << "Solution: " << number_of_solutions << endl;
        {
            for(int i=1;i<=9;i++)
            {
                for(int j=1;j<=9;j++)
                {   for(int k=1;k<=9;k++)
                    {
                        if(solution[(81*(i-1)) + (9*(j-1))+k-1]==1)
                        {  cout <<k*solution[(81*(i-1)) + (9*(j-1))+k-1]<<" ";
                        break;
                        }
                    }
     
                    
                }
                cout<<endl;
            }
            // Figure out a way to look at the 729-long 0/1 vector solution
            // to the ILP and print the appropriate integer value to be
            // inserted into each square of the solution to the Sudoku puzzle
        }
      
        
        
        // eliminate the current solution and try again;
        // that is, figure out what needs to put in row[] and what
        // constant_for_constraint should be, such that adding the
        // extra-constraint as shown below will remove the previously
        // found solution from the set of feasible solutions -- that is,
        // if the new ILP has a solution, it will be different from the
        // old one.
        double rowall[730];
        double constant_for_constraint;
        // do your magic here!
        constant_for_constraint=80.1;
        for(int m=0;m<730;m++)
            rowall[m]=0;
        
        //add the solution as a constraint so that the lp will not give the same solution
        for(int i=1;i<=9;i++)
            for(int j=1;j<=9;j++)
                for(int k=1;k<=9;k++)
                {
                    if(solution[(81*(i-1)) + (9*(j-1))+k-1]==1)
                    {  rowall[(81*(i-1)) + (9*(j-1))+k]=1;
                        break;
                    }
                }
      

        add_constraint(lp, rowall, LE, constant_for_constraint);
        
    }
    // exit the while loop when there is no solution
    
    delete_lp(lp);

}

int main (int argc, char* argv[])
{
    // formulate the non-input related part of the puzzle
    set_sudoku_ilp();
    
    // read the incomplete input information, and set appropriate constraints
    read_input_data(argv);
    
    // solve the puzzle and print the solution
    solve_the_puzzle();
    
    return(0);
}