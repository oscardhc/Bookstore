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

class Node {
    int val, id;
    Node *lson, *rson;
    
public:
    Node():val(0), lson(nullptr), rson(nullptr) {
        
    }
    Node(const int v, const int i):val(v), id(i) {
    }
    Node(std::fstream *file) {
        file->read((char*)&val, sizeof(int));
        file->read((char*)&id, sizeof(int));
        file->read((char*)&lson, sizeof(int));
        file->read((char*)&rson, sizeof(int));
    }
    void writeToFile(std::fstream *file) {
        file->write((char*)&val, sizeof(int));
        file->write((char*)&id, sizeof(int));
        file->write((char*)&lson, sizeof(int));
        file->write((char*)&rson, sizeof(int));
    }
};

const int NodeSize = sizeof(Node);

class Splay {
    std::fstream file;
    std::string filename;
    int tot;
    std::queue<int> q;
    
public:
    Splay(std::string str, int flag) {
        if (flag) {
            file = std::fstream(filename, std::ios::in|std::ios::out|std::ios::binary);
            file.read((char*)&tot, sizeof(int));
        } else {
            tot = 0;
            file = std::fstream(filename, std::ios::trunc|std::ios::in|std::ios::out|std::ios::binary);
            file.write((char*)&tot, sizeof(int));
        }
    }
    ~Splay() {
        file.close();
    }
    Node getNode(int index) {
        file.seekg(sizeof(int) + index * NodeSize, std::ios::beg);
        return Node(&file);
    }
    int addNode(Node *n) {
        int pos = tot;
        if (!q.empty()) {
            pos = q.front();
            q.pop();
        } else {
            tot++;
        }
        file.seekp(sizeof(int) + pos * NodeSize, std::ios::beg);
        n->writeToFile(&file);
        return pos;
    }
};

#endif /* Splay_hpp */
