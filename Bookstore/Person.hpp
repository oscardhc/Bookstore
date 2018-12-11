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
    Person():level(0) {};
    Person(char const *u, char const *p, char const *n, int l) {
        memcpy(userid, u, StrSIZE);
        memcpy(passwd, p, StrSIZE);
        memcpy(name, n, StrSIZE);
        level = l;
    }
    void print() {
        std::cout << userid << " - " << passwd << " - " << name << " - " << level << std::endl;
    }
};

#endif /* Person_hpp */
