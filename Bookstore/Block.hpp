//
//  Block.hpp
//  Bookstore
//
//  Created by Haichen Dong on 12/7/18.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "DataBase.hpp"

const int sqrSize = 105;

class Block {
    
public:
    int minVal, maxVal;
    int pre, nxt;
    int tot, key[sqrSize], id[sqrSize];
    
};

const int BlockSize = (sqrSize * 2 + 5) * sizeof(int);
const int BaseSize = 2 * sizeof(int);

class Blocks {
    int tot, lst;
    std::fstream file;
    std::string filename;
    
public:
    ~Blocks() {
        file.seekp(0, std::ios::beg);
        file.write((char*)&tot, sizeof(int));
        file.write((char*)&lst, sizeof(int));
        file.close();
    }
    Blocks(std::string _filename) {
        filename = _filename;
        file = std::fstream(filename, std::ios::app);
        file.close();
        file.clear();
        file = std::fstream(filename, std::ios::out|std::ios::in|std::ios::binary);
        file.seekg(0, std::ios::end);
        if (file.tellg() == 0) {
            file.seekp(0, std::ios::beg);
            tot = lst = 0;
            file.write((char*)&tot, sizeof(int));
            file.write((char*)&lst, sizeof(int));
        } else {
            file.seekg(0, std::ios::beg);
            file.read((char*)&tot, sizeof(int));
            file.read((char*)&lst, sizeof(int));
        }
    }
    void addBlock(Block *t) {
        tot++;
        int tmp[4] = {0};
        file.seekp(BaseSize * lst , std::ios::beg);
        file.read((char*)tmp, 4 * sizeof(int));
        tmp[3] = tot;
        file.write((char*)tmp, 4 * sizeof(int));
        file.seekp(BaseSize * (tot - 1), std::ios::beg);
        t->pre = lst;
        lst = tot;
        file.write((char*)t, BlockSize);
    }
    void insertVal(int key, int id) {
        Block tmp;
        file.seekp(BaseSize, std::ios::beg);
        for (int i = 0; i < tot; i++) {
            file.read((char*)&tmp, 4 * sizeof(int));
            
            if (tmp.minVal > key || tmp.maxVal < key) {
                file.seekp(BaseSize + tmp.nxt, std::ios::beg);
                continue;
            } else {
                
                file.seekp(-4 * sizeof(int), std::ios::cur);
                file.read((char*)&tmp, BlockSize);
                
                tmp.tot++;
                tmp.key[tmp.tot] = key;
                tmp.id[tmp.tot] = id;
                if (tmp.tot == sqrSize - 1) {
                    int midVal = 0;
                    for (int l = tmp.minVal, r = tmp.maxVal; l <= r; ) {
                        int m = (l + r) >> 1, cnt = 0;
                        for (int j = 0; j < sqrSize; j++) {
                            if (tmp.key[j] <= m) {
                                cnt++;
                            }
                        }
                        if (cnt <= sqrSize / 2) {
                            l = m + 1;
                            midVal = m;
                        } else {
                            r = m - 1;
                        }
                    }
                    Block nblk;
                    for (int j = 0; j < sqrSize; j++) {
//                        if ()
                    }
                }
                
            }
            
        }
    }
};

#endif /* Block_hpp */
