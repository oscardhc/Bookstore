//
//  Trade.hpp
//  Bookstore
//
//  Created by Haichen Dong on 2018/12/9.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#ifndef Trade_hpp
#define Trade_hpp

#include <stdio.h>

class Trade {
public:
    double in, out;
    
public:
    Trade() {
        
    }
    Trade(double _i, double _o) {
        in = _i;
        out = _o;
    }
};

#endif /* Trade_hpp */
