//
//  Book.hpp
//  Bookstore
//
//  Created by Haichen Dong on 12/5/18.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#ifndef Book_hpp
#define Book_hpp

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <string>
#include <queue>

const int ISBNSize = 22;
const int NameSize = 65;
const int BookSize = ISBNSize + NameSize * 3 + sizeof(double) + sizeof(int);

class Book {
public:
    char ISBN[ISBNSize], name[NameSize], author[NameSize], keyword[NameSize];
    double price;
    int stock;
    Book(char const *i = "\"", char const *n = "\"", char const *a = "\"", char const *k = "\"", const double p = -1.0, const int s = 0) {
        memcpy(ISBN, i, ISBNSize);
        memcpy(name, n, NameSize);
        memcpy(author, a, NameSize);
        memcpy(keyword, k, NameSize);
        price = p;
        stock = s;
    }
    bool operator < (const Book &a) const {
        return std::string(ISBN) < std::string(a.ISBN);
    }
};

#endif /* Book_hpp */
