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
private:
    char userid[StrSIZE], passwd[StrSIZE], name[StrSIZE];
    int level;
    
public:
    Person();
    Person(char const *u, char const *p, char const *n, int l);
    Person(std::fstream *file);
    void writeToFile(std::fstream *file);
    void print();
};

class Users {
    std::fstream file;
    std::string filename;
    std::queue<int> emp;
    int tot;
    
public:
    Users(std::string str, int flag);
    ~Users();
    Person getPerson(int index);
    size_t addPerson(Person *p);
};


#endif /* Person_hpp */
