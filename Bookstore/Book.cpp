//
//  Book.cpp
//  Bookstore
//
//  Created by Haichen Dong on 12/5/18.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#include "Book.hpp"

Book::Book() {
    
}
Book::Book(char const *i, char const *n, char const *a, char const *k, const double p, const int s) {
    memcpy(ISBN, i, ISBNSize);
    memcpy(name, n, NameSize);
    memcpy(author, a, NameSize);
    memcpy(keyword, k, NameSize);
    price = p;
    stock = s;
}
