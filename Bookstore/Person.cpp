//
//  Person.cpp
//  Bookstore
//
//  Created by Haichen Dong on 12/5/18.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#include "Person.hpp"

Person::Person() {
    
}
Person::Person(char const *u, char const *p, char const *n, const int l) {
    memcpy(userid, u, StrSIZE);
    memcpy(passwd, p, StrSIZE);
    memcpy(name, n, StrSIZE);
    level = l;
}
Person::Person(std::fstream *file) {
    file->read(userid, StrSIZE);
    file->read(passwd, StrSIZE);
    file->read(name, StrSIZE);
    file->read((char*)&level, sizeof(int));
}
void Person::writeToFile(std::fstream *file) {
    file->write(userid, StrSIZE);
    file->write(passwd, StrSIZE);
    file->write(name, StrSIZE);
    file->write((char*)&level, sizeof(int));
}

void Person::print() {
    std::cout << userid << " - " << passwd << " - " << name << " - " << level << std::endl;
}

Users::Users(std::string str, int flag):filename(str) {
    if (flag) {
        file = std::fstream(filename, std::ios::in|std::ios::out|std::ios::binary);
        file.read((char*)&tot, sizeof(int));
    } else {
        tot = 0;
        file = std::fstream(filename, std::ios::out|std::ios::in|std::ios::trunc|std::ios::binary);
        file.write((char*)&tot, sizeof(int));
    }
}
Users::~Users() {
    file.close();
}
Person Users::getPerson(int index) {
    file.seekg(sizeof(int) + index * UserSIZE, std::ios::beg);
    auto p = Person(&file);
    return p;
}
size_t Users::addPerson(Person *p) {
    size_t pos = tot;
    if (!emp.empty()) {
        pos = emp.front();
        emp.pop();
    } else {
        tot++;
    }
    file.seekp(sizeof(int) + pos * UserSIZE, std::ios::beg);
    p->writeToFile(&file);
    return pos;
}
