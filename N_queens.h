//
//  N_queens.h
//  N-queen
//
//  Created by Shengdong  Liu on 9/11/15.
//  Copyright (c) 2015 Shengdong  Liu. All rights reserved.
//

#ifndef N_queens
#define N_queens

using namespace std;

class Board
{
    //define the number of solutions
    int m=1;
    
    // private data member: size of the board
    int size;
    
    // pointer-to-pointer initialization of the board
    int **chess_board;
    
    // private member function:  returns 'false' if
    // the (row, col) position is not safe.
    bool is_this_position_safe(int row, int col)
    {
        //       for(int i=0;i<size-1;i++)
        //            for(int j=0;j<size-1;j++)
        //            {   double x,y,z,p;
        //                x=i/j;
        //                y=row/col;
        //                z=i/(size-1-j);
        //                p=(row/(size-1-col));
        //                if(x==y||z==p)
        //                {  if(chess_board[i][j]==1)
        //                        return false;
        //                }
        //                if(i==row&&(chess_board[i][j]==1))
        //                   return false;
        //                if(j==col&&(chess_board[i][j]==1))
        //                   return false;
        
        //check the threaten in rows
        for(int i=0;i<size;i++)
        {
            if(chess_board[i][col])
                return false;
        }
        
        //check the threaten in columns
        for(int j=0;j<size;j++)
        {
            if(chess_board[row][j])
                return false;
        }
        
        //check the threaten in right-down diagnoal direction
        for(int i=row,j=col;i<size&&j<size;i++,j++)
        {
            if(chess_board[i][j])
                return false;
        }
        
        //check the threaten in right-up diagnoal direction
        for(int i=row,j=col;i<size&&j>=0;i++,j--)
        {
            if(chess_board[i][j])
                return false;
        }
        
        //check the threaten in left-down diagnoal direction
        for(int i=row,j=col;i>=0&&j<size;i--,j++)
        {
            if(chess_board[i][j])
                return false;
        }
        //check the threaten in left-up diagnoal direction
        for(int i=row,j=col;i>=0&&j>=0;i--,j--)
        {
            if(chess_board[i][j])
                return false;
        }
        
        
        
        return true;
        
        //        int x, y;
        //        for (y = 0; y < col; y++)
        //        {
        //            if (chess_board[row][y])
        //                return false;
        //        }
        //        for (x = row, y = col; x >= 0 && y >= 0; x--, y--)
        //        {
        //            if (chess_board[x][y])
        //                return false;
        //        }
        //
        //        for (x = row, y = col; y >= 0 && x < size; x++, y--)
        //        {
        //            if (chess_board[x][y])
        //                return false;
        //        }
        //
        //        return true;
        //
        
        // write the appropriate code on your own that returns
        // "true" if the (row,col) position is safe.  If it is
        // unsafe (i.e. some other queen can threaten this position)
        // return "false"
    };
    
    // private member function: initializes the (n x n) chessboard
    void initialize(int n)
    {
        size=n;
        
        // write the appropriate code that uses the pointer-to-pointer
        // method to initialize the (n x n) chessboard.  Once initialized,
        // put zeros in all entries.  Later on, if you placed a queen in
        // the (i,j)-th position, then chessboard[i][j] will be 1.
        
        //use pointers to pointers to build 2-D arrays
        chess_board=new int*[size];
        
        for(int i=0;i<size;i++)
            
            chess_board[i]=new int[size];
        
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++)
            {  //cout<<"Type in the value of array["<<i<<"]["<<j<<"]";
                chess_board[i][j]=0;
            }
        
        
    };
    
    // private member function: prints the board position
    void print_board()
    {
        //print out the value of the chess_board array
        for(int k=0;k<size;k++)
            cout<<"--";
        cout<<endl;
        for(int i=0;i<size;i++)
        {    cout<<" ";
            for(int j=0;j<size;j++)
            {
                if (chess_board[i][j]==1)
                    cout<<"Q ";
                else
                    cout<<"- ";
            }
            cout<<endl;
            
        }
        for(int k=0;k<size;k++)
            cout<<"--";
        cout<<endl;
        std::cout << size << "-Queens Problem Solution" << std::endl;
        // write the appropriate code here to print out the solved
        // board as shown in the assignment description
        
    }
    
    // private member function: recursive backtracking
    bool solve(int col)
    {    //int row;
        
        //if col reaches the end, output the value of array
        if (col > (size-1))
        {     cout<<"Solutions:"<<m<<endl;
             m++;
             print_board();
            //return true;
        }
        
        else
        {
            
            //search position through row
            for(int row=0;row<size;row++)
            {
                
                //check if we can put queen at this place
                //if not we continue the loop,if it is okay,we
                //check whether the position is fit for next column
                if(is_this_position_safe(row, col))
                {
                    chess_board[row][col]=1;
                    
                    if (solve(col+1))
                    {
                        return true;
                    }
                    else
                    {
                        chess_board[row][col]=0;
                        
                        ////
                    }
                    
                    //chess_board[row][col]=0;
                    
                    
                    // implement the recursive backtracking procedure described in
                    // pseudocode format in figure 1 of the description of the first
                    // programming assignment
                }
                
            }
            
            
            
            
        }
        //if(row==size)
        // return true;
        
        return false;
        
    }
    
    
public:
    // Solves the n-Queens problem by (recursive) backtracking
    void nQueens(int n)
    {
        initialize(n);
        //solve the problem from 0
        solve(0);
            //print_board();
        //if there are solutions, print out the summary
        //if not, print out no.
          if (m>1)
         std::cout << "There are "<<m-1<<" different solutions to the " << n << "-Queens Problem" << std::endl;
        //  print_board();
        else
            std::cout << "There is no solution to the " << n << "-Queens Problem" << std::endl;
    }
};

#endif
