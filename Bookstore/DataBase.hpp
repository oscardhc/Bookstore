//
//  DataBase.hpp
//  Bookstore
//
//  Created by Haichen Dong on 12/6/18.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#ifndef DataBase_hpp
#define DataBase_hpp

#include <stdio.h>
#include <fstream>

const int StackSize = 100;

template <class T, int DataSize>
class DataBase {
    int BaseSize = (StackSize + 2) * sizeof(int);
    
public:
    int tot, stot;
    
private:
    std::fstream file;
    std::string filename;
    int stack[StackSize];
    
public:
    DataBase() {
        
    }
    void init(std::string f) {
        filename = f;
        file = std::fstream(filename, std::ios::app);
        file.close();
        file.clear();
        file = std::fstream(filename, std::ios::in|std::ios::out|std::ios::binary);
        file.seekg(0, std::ios::end);
        if (file.tellg() == 0) {
            file.seekg(0, std::ios::beg);
            tot = stot = 0;
            file.write((char*)&tot, sizeof(int));
            file.write((char*)&stot, sizeof(int));
            file.write((char*)stack, StackSize * sizeof(int));
        } else {
            file.seekg(0, std::ios::beg);
            file.read((char*)&tot, sizeof(int));
            file.read((char*)&stot, sizeof(int));
            file.read((char*)stack, StackSize * sizeof(int));
        }
    }
    
    ~DataBase() {
        file.seekg(0, std::ios::beg);
        file.write((char*)&tot, sizeof(int));
        file.write((char*)&stot, sizeof(int));
        file.write((char*)stack, StackSize * sizeof(int));
        file.close();
    }
    
    T getElement(int index) {
        file.seekg(BaseSize + DataSize * index, std::ios::beg);
        T ret;
        file.read((char*)&ret, DataSize);
        return ret;
    }
    
    void getElement(T *t, int index, int sizeToRead = DataSize) {
        file.seekg(BaseSize + DataSize * index, std::ios::beg);
        file.read((char*)t, sizeToRead);
    }
    
    void delElement(int index) {
        T tmp = T();
        file.seekg(BaseSize + DataSize * index, std::ios::beg);
        file.write((char*)&tmp, DataSize);
        if (stot < StackSize - 1) {
            stack[++stot] = index;
        }
    }
    
    int addElement(T *t) {
        int pos = tot;
        if (stot) {
            pos = stack[stot - 1];
            stot--;
        } else {
            tot++;
        }
        file.seekp(BaseSize + DataSize * pos, std::ios::beg);
        file.write((char*)t, DataSize);
        return pos;
    }
    
    void replaceElement(int index, T *t) {
        file.seekp(BaseSize + DataSize * index, std::ios::beg);
        file.write((char*)t, DataSize);
    }
};

#endif /* DataBase_hpp */
