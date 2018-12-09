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
#include "Trade.hpp"

class BookStore {
    Person curUser;
    int curUserIndex;
    Book curBook;
    int curBookIndex;
    Blocks iIndex, nIndex, aIndex, kIndex, pIndex;
    DataBase<Book, sizeof(Book)> bData;
    DataBase<Person, sizeof(Person)> pData;
    DataBase<Trade, sizeof(Trade)> tData;
    
public:
    BookStore() {
        iIndex.init("./isbn_index.bi");
        nIndex.init("./name_index.bi");
        aIndex.init("./author_index.bi");
        kIndex.init("./keyword_index.bi");
        pIndex.init("./price_index.bi");
        bData.init("./book_data.bi");
        pData.init("./person_data.bi");
        tData.init("./trade_data.bi");
    }
    
    int strToNum(std::string str) {
        int n = (int)strlen(str.c_str()), bs = 131;
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
    void select(std::string isbn) {
        int num = strToNum(isbn);
        auto v = iIndex.qryforVal(num);
        if (v.empty()) {
            Book bk(isbn.c_str(), "", "", "", 0, 0);
            bData.addElement(&bk);
        } else {
            curBookIndex = v[0];
            curBook = bData.getElement(curBookIndex);
        }
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
    void modify(std::string isbn = "\"", std::string name = "\"", std::string author = "\"", std::string keyword = "\"", double price = -1.0) {
        if (isbn != "\"") memcpy(curBook.ISBN, isbn.c_str(), ISBNSize);
        if (name != "\"") memcpy(curBook.name, name.c_str(), NameSize);
        if (author != "\"") memcpy(curBook.author, author.c_str(), NameSize);
        if (keyword != "\"") memcpy(curBook.keyword, keyword.c_str(), NameSize);
        if (price != -1) curBook.price = price;
        bData.replaceElement(curBookIndex, &curBook);
    }
    void import(int quantity, double totalPrice) {
        curBook.stock += quantity;
        Trade tmp(0, totalPrice);
        tData.addElement(&tmp);
    }
    void show(std::string isbn = "\"", std::string name = "\"", std::string author = "\"", std::string keyword = "\"") {
        std::vector<int> v;
        if (isbn != "\"") {
            v = iIndex.qryforVal(<#int key#>);
        } else if (name != "\"") {
            
        } else if (author != "\"") {
            
        } else if (keyword != "\"") {
            
        }
    }
    void showfinance() {
        
    }
    void buy() {
        
    }
};

#endif /* BookStore_hpp */
