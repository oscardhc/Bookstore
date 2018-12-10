//
//  Person.hpp
//  Bookstore
//
//  Created by Haichen Dong on 12/5/18.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#ifndef Person_hpp
#define Person_hpp

#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#include <iostream>
#include <queue>

const size_t StrSIZE = 35;
const size_t UserSIZE = StrSIZE * 3 + sizeof(int);

class Person {
public:
    char userid[StrSIZE], passwd[StrSIZE], name[StrSIZE];
    int level;
    
public:
    Person();
    Person(char const *u, char const *p, char const *n, int l);
    void print();
};

#endif /* Person_hpp */
