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
#include <climits>
#include <algorithm>
#include <vector>
#include <cstring>

const int sqrSize = 200;

class Block {
    
public:
    int minVal, maxVal;
    int nxt;
    int tot, key[sqrSize], id[sqrSize];
    
    void reset() {
        tot = 0;
        minVal = INT_MAX;
        maxVal = INT_MIN;
    }
    
};

const int BlockSize = (4 + sqrSize * 2) * sizeof(int);
const int BaseSize = 1 * sizeof(int);

class Blocks {
    int tot;
    std::fstream file;
    std::string filename;
    
public:
    ~Blocks() {
        file.seekp(0, std::ios::beg);
        file.write((char*)&tot, sizeof(int));
        file.close();
    }
    Blocks() {
        
    }
    void init (std::string _filename) {
        filename = _filename;
        file = std::fstream(filename, std::ios::app);
        file.close();
        file.clear();
        file = std::fstream(filename, std::ios::out|std::ios::in|std::ios::binary);
        file.seekg(0, std::ios::end);
        if (file.tellg() == 0) {
            file.seekp(0, std::ios::beg);
            tot = 1;
            Block blk;
            blk.reset();
            file.write((char*)&tot, sizeof(int));
            file.write((char*)&blk, BlockSize);
        } else {
            file.seekg(0, std::ios::beg);
            file.read((char*)&tot, sizeof(int));
        }
    }
    void print() {
        Block tmp;
        int cur = 0;
        for (int i = 0; i < tot; i++) {
            file.seekg(BaseSize + cur * BlockSize, std::ios::beg);
            file.read((char*)&tmp, BlockSize);
            
            printf("BLOCK %d (%d) tot:%d max:%d min:%d nx:%d\n", cur, i, tmp.tot, tmp.maxVal, tmp.minVal, tmp.nxt);
            for (int j = 0; j < tmp.tot; j++) {
                printf("            %d %d\n", tmp.key[j], tmp.id[j]);
            }
            
            cur = tmp.nxt;
        }
    }
    void addBlock(Block *t) {
        file.seekp(BaseSize + tot * BlockSize , std::ios::beg);
        file.write((char*)t, BlockSize);
        tot++;
    }
    void insertVal(int key, int id) {
        Block tmp;
        int cur = 0;
        for (int i = 0; i < tot; i++) {
            file.seekg(BaseSize + cur * BlockSize, std::ios::beg);
            file.read((char*)&tmp, 4 * sizeof(int));
            
            if (tmp.tot > 0 && tmp.maxVal < key && i < tot - 1) {
                cur = tmp.nxt;
                continue;
            } else {
                file.seekp(-4 * sizeof(int), std::ios::cur);
                file.read((char*)&tmp, BlockSize);
                tmp.tot++;
                tmp.key[tmp.tot - 1] = key;
                tmp.id[tmp.tot - 1] = id;
                tmp.maxVal = std::max(tmp.maxVal, key);
                tmp.minVal = std::min(tmp.minVal, key);
                if (tmp.tot == sqrSize) {
                    int midVal = 0, midary[sqrSize] = {0};
                    memcpy(midary, tmp.key, sqrSize * sizeof(int));
                    std::nth_element(midary, midary + sqrSize / 2, midary + sqrSize);
                    midVal = midary[sqrSize / 2];
                    if (tmp.minVal == tmp.maxVal - 1) {
                        midVal = tmp.minVal;
                    }
                    int flag = tmp.minVal == tmp.maxVal;
                    Block blk;
                    tmp.reset();
                    blk.reset();
                    for (int j = 0; j < sqrSize; j++) {
                        if ((!flag && tmp.key[j] <= midVal) || (flag && j < sqrSize / 2)) {
                            tmp.key[tmp.tot] = tmp.key[j];
                            tmp.id[tmp.tot] = tmp.id[j];
                            tmp.minVal = std::min(tmp.minVal, tmp.key[j]);
                            tmp.maxVal = std::max(tmp.maxVal, tmp.key[j]);
                            tmp.tot++;
                        } else {
                            blk.key[blk.tot] = tmp.key[j];
                            blk.id[blk.tot] = tmp.id[j];
                            blk.minVal = std::min(blk.minVal, tmp.key[j]);
                            blk.maxVal = std::max(blk.maxVal, tmp.key[j]);
                            blk.tot++;
                        }
                    }
                    blk.nxt = tmp.nxt;
                    tmp.nxt = tot;
                    
                    file.seekp(-BlockSize, std::ios::cur);
                    file.write((char*)&tmp, BlockSize);
                    
                    addBlock(&blk);
                } else {
                    file.seekg(BaseSize + cur * BlockSize, std::ios::beg);
                    file.write((char*)&tmp, BlockSize);
                }
                
                break;
            }
        }
    }
    std::vector<int> qryforVal(int key) {
        Block tmp;
		std::vector<int> ret;
        int cur = 0;
        for (int i = 0; i < tot; i++, cur = tmp.nxt) {
            file.seekg(BaseSize + cur * BlockSize, std::ios::beg);
            file.read((char*)&tmp, 4 * sizeof(int));
            if (tmp.tot > 0 && tmp.minVal <= key && tmp.maxVal >= key) {
				file.seekg(BaseSize + cur * BlockSize, std::ios::beg);
				file.read((char*)&tmp, BlockSize);
                
				for (int j = 0; j < tmp.tot; j++) {
					if (tmp.key[j] == key) {
						ret.push_back(tmp.id[j]);
					}
				}
				if (i == tot - 1 || tmp.maxVal > key) {
					return ret;
				}
            }
        }
        return ret;
    }
    void deleteVal(int key, int id) {
        Block tmp;
        int cur = 0;
        for (int i = 0; i < tot; i++, cur = tmp.nxt) {
            file.seekg(BaseSize + cur * BlockSize, std::ios::beg);
            file.read((char*)&tmp, 4 * sizeof(int));
            if (tmp.tot > 0 && tmp.minVal <= key && tmp.maxVal >= key) {
                file.seekg(-4 * sizeof(int), std::ios::cur);
                file.read((char*)&tmp, BlockSize);
                for (int j = 0; j < tmp.tot; j++) {
                    if (tmp.key[j] == key && tmp.id[j] == id) {
                        if (tmp.tot == 1) {
                            tmp.tot--;
                        } else if (tmp.tot > 1) {
                            tmp.tot--;
                            std::swap(tmp.key[j], tmp.key[tmp.tot]);
                            std::swap(tmp.id[j], tmp.id[tmp.tot]);
                        }
                        file.seekg(-BlockSize, std::ios::cur);
                        file.write((char*)&tmp, BlockSize);
                        return;
                    }
                }
                if (i == tot - 1 || tmp.maxVal > key) {
                    return;
                }
            }
        }
        return;
    }
};

#endif /* Block_hpp */
