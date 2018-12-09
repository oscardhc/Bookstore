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
#include "Block.hpp"

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
    
    Blocks blk("./blk.bi");
    freopen("hhh.out", "w", stdout);
    std::vector< std::pair<int,int> > v;
    for (int i = 1; i < 20000; i++) {
        int cur = rand();
        blk.insertVal(cur, i);
//        blk.print();
    }
    blk.print();
    return 0;
}
