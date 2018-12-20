//
//  Operation.hpp
//  Bookstore
//
//  Created by Haichen Dong on 2018/12/17.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#ifndef Operation_hpp
#define Operation_hpp

#include <stdio.h>

class Operation {
public:
    int useridx;
    char cmd[200];
    Operation() {
        
    }
    Operation(const int idx, char const *c) {
        useridx = idx;
        memcpy(cmd, c, 200);
    }
};

#endif /* Operation_hpp */
