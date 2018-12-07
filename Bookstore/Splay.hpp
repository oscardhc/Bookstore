//
//  Splay.hpp
//  Bookstore
//
//  Created by Haichen Dong on 12/6/18.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#ifndef Splay_hpp
#define Splay_hpp

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <queue>
#include "DataBase.hpp"

class Node {
public:
    int val, id, idx;
    int lson, rson;
    
public:
    Node():val(0), lson(0), rson(0) {
        
    }
    Node(const int v, const int i):val(v), id(i) {
    }
};

const int NodeSize = sizeof(int) * 4;

class Splay : DataBase<Node, NodeSize> {
    
public:
    void rotate(int index) {
        Node cur = getElement(index);
        Node lson = getElement(cur.lson);
        Node rson = getElement(cur.rson);
        
        
        
    }
};

#endif /* Splay_hpp */
