//
//  BFIndex.hpp
//  Bookstore
//
//  Created by Haichen Dong on 2018/12/12.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#ifndef BFIndex_hpp
#define BFIndex_hpp

#include <stdio.h>
#include "DataBase.hpp"
#include <climits>
#include <algorithm>
#include <vector>
#include <cstring>
#include <iostream>

const int sqrSize = 900;

const int BlockSize = (4 + sqrSize * 2) * sizeof(int);
const int BaseSize = 1 * sizeof(int);

class Pair {
public:
    int key, id;
    Pair(int _k = 0, int _i = -1) : key(_k), id(_i) {}
};

class Blocks {
    DataBase<Pair, sizeof(Pair)> db;
    
public:
    ~Blocks() {
    }
    Blocks() {
        
    }
    void init (std::string _filename) {
        db.init(_filename);
    }

    void insertVal(int key, int id) {
        Pair tmp(key, id);
        db.addElement(&tmp);
    }
    std::vector<int> qryforVal(int key) {
        Pair tmp;
        std::vector<int> ret;
        for (int i = db.tot - 1; i >= 0; i--) {
            db.getElement(&tmp, i, sizeof(int));
            if (tmp.key == key) {
                db.getElement(&tmp, i);
                if (tmp.id != -1) {
                    ret.push_back(tmp.id);
                }
            }
        }
        return ret;
    }
    void deleteVal(int key, int id) {
        Pair tmp;
        for (int i = db.tot - 1; i >= 0; i--) {
            db.getElement(&tmp, i);
            if (tmp.key == key && tmp.id == key) {
                db.delElement(i);
            }
        }
    }
};

#endif /* BFIndex_hpp */
