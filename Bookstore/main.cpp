//
//  main.cpp
//  Bookstore
//
//  Created by Haichen Dong on 11/28/18.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#include <iostream>
#include "DataBase.hpp"
#include "Person.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    auto a = Person("abcdef" , "123456" , "哈哈哈哈哈", 233);
    auto b = Person("hhhhhhh" , "xyzxyz" , "嘻嘻嘻嘻", 100);
    
    DataBase<Person, UserSIZE> data("./dat.bi");
    data.addElement(&a);
    data.addElement(&b);
    data.addElement(&a);
    data.addElement(&b);
    
    data.getElement(0).print();
    
    return 0;
}
