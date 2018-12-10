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
//    BookStore a;
//    a.run();
    Blocks idx;
    idx.init("./hhh.bi");
    for (int i = 0; i < 10000; i++) {
        idx.insertVal(1, i);
    }
    
    return 0;
}
