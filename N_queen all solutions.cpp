//
//  main.cpp
//  N-queen
//
//  Created by Shengdong  Liu on 9/10/15.
//  Copyright (c) 2015 Shengdong  Liu. All rights reserved.
//

// N Queens Problem via (Backtracking, which is implemented by) Recursion

#include <iostream>
#include "N_queens.h"

int main (int argc, char * const argv[])
{
    Board x;
    
    int board_size;
    sscanf (argv[1], "%d", &board_size);
    
    x.nQueens(board_size);
    
    return 0;
}
