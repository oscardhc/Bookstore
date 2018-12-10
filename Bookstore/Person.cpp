//
//  Person.cpp
//  Bookstore
//
//  Created by Haichen Dong on 12/5/18.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#include "Person.hpp"

Person::Person(char const *u, char const *p, char const *n, const int l) {
    memcpy(userid, u, StrSIZE);
    memcpy(passwd, p, StrSIZE);
    memcpy(name, n, StrSIZE);
    level = l;
}

void Person::print() {
    std::cout << userid << " - " << passwd << " - " << name << " - " << level << std::endl;
}
