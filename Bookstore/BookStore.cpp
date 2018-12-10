//
//  BookStore.cpp
//  Bookstore
//
//  Created by Haichen Dong on 2018/12/7.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#include "BookStore.hpp"

void BookStore::load(std::string f) {
    std::fstream cmdText(f, std::ios::in);
    work(&cmdText);
}
void BookStore::work(std::fstream *input) {
    char str[105];
    while (input->getline(str, 100)) {
        
    }
}
