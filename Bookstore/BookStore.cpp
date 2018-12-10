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
    char str[205];
    if (input->good()) {
        curUser = pData.getElement(0);
        curUserIndex = 0;
        while (input->getline(str, 200)) {
            try {
                exec(std::string(str));
            } catch(int) {
                return;
            }
        }
    } else {
        curUser = Person();
        curUserIndex = -1;
        while (std::cin.getline(str, 200)) {
            try {
                exec(std::string(str));
            } catch(int) {
                return;
            }
        }
    }
    
}
