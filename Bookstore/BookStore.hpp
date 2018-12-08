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

class BookStore {
    Person curUser;
    Book curBook;
    
public:
    void work(std::istream input) {
        char str[105];
        while (input.getline(str, 100)) {
            
        }
    }
    void load() {
        
    }
//    template <class T>
//    void select(DataBase<T, > db) {
    
//    }
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
