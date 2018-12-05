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
Book::Book(char const *i, char const *n, char const *a, char const *d, const double p, const int s) {
    memcpy(ISBN, i, ISBNSize);
    memcpy(name, n, NameSize);
    memcpy(author, a, NameSize);
    memcpy(description, d, NameSize);
    price = p;
    stock = s;
}
Book::Book(std::fstream *file) {
    file->read(ISBN, ISBNSize);
    file->read(name, NameSize);
    file->read(author, NameSize);
    file->read(description, NameSize);
    file->read((char*)&price, sizeof(double));
    file->read((char*)&stock, sizeof(int));
}
void Book::writeToFile(std::fstream *file) {
    file->write(ISBN, ISBNSize);
    file->write(name, NameSize);
    file->write(author, NameSize);
    file->write(description, NameSize);
    file->write((char*)&price, sizeof(double));
    file->write((char*)&stock, sizeof(int));
}

Books::Books(std::string str, int flag) {
    
}
Books::~Books() {
    file.close();
}
Book Books::getBook(int index) {
    file.seekg(sizeof(int) + index * BookSize, std::ios::beg);
    auto b = Book(&file);
    return b;
}
size_t Books::addBook(Book *b) {
    int pos = tot;
    if (!q.empty()) {
        pos = q.front();
        q.pop();
    } else {
        tot++;
    }
    file.seekp(sizeof(int) + pos * BookSize, std::ios::beg);
    b->writeToFile(&file);
    return pos;
}
