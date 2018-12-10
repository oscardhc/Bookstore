//
//  main.cpp
//  Bookstore
//
//  Created by Haichen Dong on 11/28/18.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#include <iostream>
#include "BookStore.hpp"

int main(int argc, const char * argv[]) {
    
    BookStore a;
    std::string cmd = "modify -keyword=\"嘻嘻|123|4 5|哈哈哈\"";
    a.exec(cmd);
    
    
//    auto a = Person("abcdef" , "123456" , "哈哈哈哈哈", 233);
//    auto b = Person("hhhhhhh" , "xyzxyz" , "嘻嘻嘻嘻", 100);
    
//    DataBase<Person, UserSIZE> data("./dat.bi");
//    data.addElement(&a);
//    data.addElement(&b);
//    data.addElement(&a);
//    data.addElement(&b);
//    
//    data.getElement(0).print();
    
//    Blocks blk;
//    blk.init("./blk.bi");
//    freopen("hhh.out", "w", stdout);
//    for (int i = 1; i < 40000; i++) {
//        int cur = rand() % 10000;
//        blk.insertVal(cur, i);
//    }
//    blk.print();
//
//    auto v = blk.qryforVal(3);
//    
//    for (int i = 0; i < v.size(); i++) {
//        printf(" > %d %d\n", i, v[i]);
//    }
    
    return 0;
}
