//
//  BookStore.hpp
//  Bookstore
//
//  Created by Haichen Dong on 2018/12/7.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#ifndef BookStore_hpp
#define BookStore_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "Person.hpp"
#include "Book.hpp"
#include "DataBase.hpp"
#include "Block.hpp"

class BookStore {
    Person curUser;
    Book curBook;
    Blocks iIndex, nIndex, aIndex, kIndex, pIndex;
    
public:
    BookStore() {
        iIndex.init("./isbn_index.bi");
        nIndex.init("./name_index.bi");
        aIndex.init("./author_index.bi");
        kIndex.init("./keyword_index.bi");
        pIndex.init("./price_index.bi");
    }
    
    int strToNum(std::string str) {
        int n = strlen(str.c_str()), bs = 131;
        long long ret = 0;
        for (int i = 0; i < n; i++) {
            ret = ret * bs + str.c_str()[i];
        }
        return (int)ret;
    }
    
    void work(std::istream input) {
        char str[105];
        while (input.getline(str, 100)) {
            
        }
    }
    void load() {
        
    }
    void select(std::string keyword, std::string val) {
    
    }
    void su(std::string username, std::string password) {
    }
    void useradd() {
        
    }
    void regi() {
        
    }
    void del() {
        
    }
    void pswd() {
        
    }
    void modify() {
        
    }
    void import() {
        
    }
    void show() {
        
    }
    void showfinance() {
        
    }
    void buy() {
        
    }
};

#endif /* BookStore_hpp */
