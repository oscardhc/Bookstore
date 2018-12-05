//
//  main.cpp
//  Bookstore
//
//  Created by Haichen Dong on 11/28/18.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#include <iostream>
#include "Person.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    auto a = Person("abcdef" , "123456" , "哈哈哈哈哈", 233);
    auto b = Person("hhhhhhh" , "xyzxyz" , "嘻嘻嘻嘻", 100);
    
    Users x("./dat.bin", 0);
    x.addPerson(&a);
    x.addPerson(&a);
    x.addPerson(&b);
    x.addPerson(&b);
    a.print();
    
    auto c = x.getPerson(3);
    c.print();
    
    return 0;
}
