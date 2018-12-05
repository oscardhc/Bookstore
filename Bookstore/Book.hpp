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
    char ISBN[ISBNSize], name[NameSize], author[NameSize], description[NameSize];
    double price;
    int stock;
    
public:
    Book();
    Book(char const *i, char const *n, char const *a, char const *d, const double p, const int s);
    Book(std::fstream *file);
    void writeToFile(std::fstream *file);
};

class Books {
    std::fstream file;
    std::string filename;
    int tot;
    std::queue<int> q;
    
public:
    Books(std::string str, int flag);
    ~Books();
    Book getBook(int index);
    size_t addBook(Book *b);
};

#endif /* Book_hpp */
