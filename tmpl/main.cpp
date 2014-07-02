//
//  main.cpp
//  tmpltest1
//
//  Created by Mo on 3/07/2014.
//  Copyright (c) 2014 Mo. All rights reserved.
//

#include <iostream>
#include "multi_array.h"
//#include "iostream.h"

using namespace std;

_sizetype dims[4]={4, 3, 56, 2};
//multi_array<int, 4> ia4(4, 3, 56, 2); c'tor removed

int main()
{
    multi_array<int, 4> ia4(dims);

    cout<<sizeof(dims)<<endl;
    
    ia4[0][0][0][0]=99;
    
    cout<<ia4<<endl;
    cout<<ia4[0]<<endl;
    cout<<ia4[0][0]<<endl;
    cout<<ia4[0][0][0]<<endl;
    cout<<ia4[0][0][0][0]<<endl;
    
    return 0;
}

/*
 int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

 */
