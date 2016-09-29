/*
 *  alice_and_bob.h
 *  Loosing as little as possible
 *
 *
 */
#ifndef ALICE_AND_BOB
#define ALICE_AND_BOB

#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class I_have_nothing_apropos_for_this_class
{
private:
    double alice_probability, bob_probability;
    
    // private member function: uniform RV generator
    double get_uniform()
    {
        return (((float) random())/(pow(2.0, 31.0)-1.0));
        // write the appropriate code here
    }
    
double j=0.0;
    int a[1000][1000];
    int f[1000][1000];
    // private member function: nCi (i.e. n-take-i)
    int take(int n, int i)
    {
        int v=0;
        if (f[n][i]==1)
        {
            return (a[n][i]);
        }

//        if ((n-1)==i)
//            { j=((double)n/double((n-i)));
//                return j*1;
//            }
//            else
//            {   j=((double)n/double((n-i)));
//                return j*take(n-1,i);
//            }
        //if(i>(n/2))
           // return take(n,n-i);
        if(i==0)
            return 1;
        if(n==i)
            return 1;
        else if (i==0)
            return 1;
        else
        {
            
            v=(take(n-1,i)+take(n-1,i-1));
            a[n][i]=v;
            //we calculated this value
            //so we flag it to be 1
            f[n][i]=1;
            return v;
        }
        
    }
    
        
//        int size_of_array, number_of_objects_to_be_picked;
//        int *array;
//        
//      //  cout << "Array Size? ";
//        size_of_array=n;
//      //  cout << "#Objects to be picked from array? ";
//       number_of_objects_to_be_picked=i;
//        
//        // I am just filling the array with integers... it could be a list of
//        // other objects, for example.
//        array = new int[size_of_array];
//        for (int i = 0; i < size_of_array; i++)
//            array[i] = i+1;
//        
//        // Create a boolean array where the first r items are "true" (i.e. 1)
//        // the remaining n-r items are "false" (i.e. 0)
//        vector <bool> did_i_pick_this(size_of_array);
//        
//        fill(did_i_pick_this.begin(),
//             did_i_pick_this.begin() + number_of_objects_to_be_picked, true);
//        
//        int j=1;
//        // I am going to use the prev_permutation STL in C++ (see
//        // http://www.cplusplus.com/reference/algorithm/prev_permutation/ )
//        // to generate the required combinatorial outputs
//        do
//        {
//            j++;
//           // cout << "{ ";
////            for (int i = 0; i < size_of_array; ++i)
////            {
////                if (did_i_pick_this[i])
////                    cout << array[i] << " ";
////            }
//           // cout << "}" << endl;
//        } while (prev_permutation(did_i_pick_this.begin(), did_i_pick_this.end())); 
//        
//        return j ;
        // write a **RECURSIVE** implementation of n-take-i.
        // If you made it non-recurisive (i.e. n!/((n-i)!i!)) -- it
        // will take too long for large sizes
   // }
    
    // this routine implements the probability that Alice has more
    // heads than Bob after n-many coin tosses
    double theoretical_value(double q, double p, int n)
    {
        double value1=0.0;
        
        
        for(int r=0;r<n;r++)
    {
        double value2=0.0;
        for(int s=r+1;s<=n;s++)
        {
        //    if(s>(n/2))
       
        //value2=value2+pow(q,s)*pow(1-q,n-s)*take(n,n-s);
          //  else
                value2=value2+pow(q,s)*pow(1-q,n-s)*take(n,s);
                
    
        }
       // cout<<value2<<endl;
      //  if(r>(n/2))
        //value1=value1+pow(p,r)*pow(1-p,n-r)*take(n,n-r)*value2;
        //else
             value1=value1+pow(p,r)*pow(1-p,n-r)*take(n,r)*value2;
            
    }
        return value1;
    }
        // implement equation 1.1 of Addona-Wagon-Wilf paper
    
    
public:
    // public function:
    void set_probability(double alice_p, double bob_p)
    {
        alice_probability = alice_p;
        bob_probability = bob_p;
    }
    
    // probability of Alice winning the game.
    double simulated_value(int number_of_coin_tosses_in_each_game, int no_of_trials)
    {
        int no_of_wins_for_alice = 0;
        for (int i = 0; i < no_of_trials; i++)
        {
            int number_of_heads_for_alice = 0;
            int number_of_heads_for_bob = 0;
            for (int j = 0; j < number_of_coin_tosses_in_each_game; j++)
            {
                if (get_uniform() < alice_probability)
                    number_of_heads_for_alice++;
                if (get_uniform() < bob_probability)
                    number_of_heads_for_bob++;
            }
            if (number_of_heads_for_alice > number_of_heads_for_bob)
                no_of_wins_for_alice++;
        }
        return (((double) no_of_wins_for_alice)/((double) no_of_trials));
    }
    
    int search_result()
    {
        
        
      int result=0;
        double a=0,b=0,c=0;
        double max=0.0;
        int max_result=0;
        a=theoretical_value(alice_probability, bob_probability, 1);
        for(int n=1;n<50;n++)
        {
            b=theoretical_value(alice_probability, bob_probability, n+1);
            {
                if(a>b&a>c&max<a)
            {
                max=a;
                result=n;
               // break;
            }
            }
            c=a;
            a=b;
        
        }
//        return result;
        
        //cout<<"simulated value"<<simulated_value(result, 1000000)<<endl;
        
     //   cout<<"theoretical_value :"<<theoretical_value(alice_probability, bob_probability, result)<<endl;
      
       int result_sim=0;
        double max_sim_result=0;
        a=simulated_value(1,100000);
        max_sim_result=a;
        for(int n=1;n<50;n++)
        {
            b=simulated_value(n+1,100000);
            {if(a>b&a>c&max_sim_result<a)
            {
                max_sim_result=a;
                result_sim=n+1;
                cout<<"simulated value :"<<max_sim_result<<endl;

               // cout << "The optimal number of coin tosses in each game by simulation is " <<result_sim<< endl;
                //break;
            }
            }
            c=a;
            a=b;
//           // cout<<"simulated value :"<<a<<endl;
//         //   cout << "The optimal number of coin tosses in each game by simulation is " <<result_sim<< endl;
//
        
      }
        cout<<"simulated value :"<<simulated_value(result, 100000)<<endl;
        cout << "The optimal number of coin tosses in each game by simulation is " <<result_sim<< endl;

        cout<<"theoretical_value :"<<theoretical_value(alice_probability, bob_probability, result)<<endl;


        return result;
        
        
        // implememt a discrete-search procedure for the optimal n-value. 
        // start with n = 1 and find the discrete-value of n that has 
        // the largest probability for Alice winning.  Why would this work?
        // See Theorem 2.2 of the paper for the reason!
    }
    
};
#endif







