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

const size_t StrSIZE = 90;
const size_t UserSIZE = StrSIZE * 3 + sizeof(int);

class Person {
private:
    char userid[StrSIZE], passwd[StrSIZE], name[StrSIZE];
    int level;
    
public:
    Person() {
    
    }
    Person(char const *u, char const *p, char const *n, int l) {
        memcpy(userid, u, StrSIZE);
        memcpy(passwd, p, StrSIZE);
        memcpy(name, n, StrSIZE);
        level = l;
    }
    Person(std::fstream &file) {
        file.read(userid, StrSIZE);
        file.read(passwd, StrSIZE);
        file.read(name, StrSIZE);
        file.read((char*)&level, sizeof(int));
    }
    inline void writeToFile(std::fstream &file) {
        file.write(userid, StrSIZE);
        file.write(passwd, StrSIZE);
        file.write(name, StrSIZE);
        file.write((char*)&level, sizeof(int));
    }
    
    inline void print() {
        std::cout << userid << " - " << passwd << " - " << name << " - " << level << std::endl;
    }
};

class Users {
    std::fstream file;
    std::string filename;
    std::queue<int> emp;
    int tot;
    
public:
    Users(std::string str, int flag):filename(str) {
        if (flag) {
            file = std::fstream(filename, std::ios::in|std::ios::out|std::ios::binary);
            file.read((char*)&tot, sizeof(int));
        } else {
            tot = 0;
            file = std::fstream(filename, std::ios::out|std::ios::in|std::ios::trunc|std::ios::binary);
            file.write((char*)&tot, sizeof(int));
        }
    }
    ~Users() {
        file.close();
    }
    Person getPerson(int index) {
        file.seekg(sizeof(int) + index * UserSIZE, std::ios::beg);
        auto p = Person(file);
        return p;
    }
    size_t addPerson(Person *p) {
        size_t pos = tot;
        if (!emp.empty()) {
            pos = emp.front();
            emp.pop();
        } else {
            tot++;
        }
        p->writeToFile(file);
        return pos;
    }
};


#endif /* Person_hpp */
