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
#include <sstream>
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
    int parseStr(std::string str) {
        std::stringstream is(str);
        int n;
        is >> n;
        return n;
    }

    void select(std::string isbn) {
        int num = strToNum(isbn);
        auto v = iIndex.qryforVal(num);
        if (v.empty()) {
            Book bk(isbn.c_str(), "", "", "", 0, 0);
            curBookIndex = bData.addElement(&bk);
        } else {
            curBookIndex = v[0];
        }
        curBook = bData.getElement(curBookIndex);
    }
    void su(std::string username, std::string password) {
        Person tmp;
        for (int i = 0; i < pData.tot; i++) {
            pData.getElement(&tmp, i);
            if (std::string(tmp.userid) == username) {
                if (std::string(tmp.passwd) == password) {
                    curUser = tmp;
                    curUserIndex = i;
                }
                return;
            }
        }
    }
    void logout() {
        curUserIndex = -1;
        curUser = Person();
    }
    void useradd(std::string userid, std::string passwd, std::string level, std::string name) {
        Person tmp(userid.c_str(), passwd.c_str(), name.c_str(), parseStr(level));
        pData.addElement(&tmp);
    }
    void regi(std::string userid, std::string passwd, std::string name) {
        useradd(userid, passwd, "1", name);
    }
    void del(std::string userid) {
        Person tmp;
        for (int i = 0; i < pData.tot; i++) {
            pData.getElement(&tmp, i);
            if (std::string(tmp.userid) == userid) {
                pData.delElement(i);
            }
        }
    }
    void changePassword(std::string userid, std::string passwd, std::string oldpasswd = " ") {
        Person tmp;
        for (int i = 0; i < pData.tot; i++) {
            pData.getElement(&tmp, i);
            if (std::string(tmp.userid) == userid) {
                if (oldpasswd == " " || tmp.passwd == oldpasswd) {
                    memcpy(tmp.passwd, passwd.c_str(), StrSIZE);
                    pData.replaceElement(i, &tmp);
                    if (i == curUserIndex) {
                        curUser = tmp;
                    }
                } else {
                    
                }
                return;
            }
        }
    }
    void pswd(std::vector<std::string> v) {
        if (curUser.level == 7) {
            
        } else {
            
        }
    }
    void modify(std::string isbn = "\"", std::string name = "\"", std::string author = "\"", std::string keyword = "\"", double price = -1.0) {
        if (isbn != "\"") {
            auto ss = std::string(curBook.ISBN);
            if (ss != "\"") {
                iIndex.deleteVal(strToNum(ss), curBookIndex);
            }
            iIndex.insertVal(strToNum(isbn), curBookIndex);
            memcpy(curBook.ISBN, isbn.c_str(), ISBNSize);
        }
        if (name != "\"") {
            auto ss = std::string(curBook.name);
            if (ss != "\"") {
                nIndex.deleteVal(strToNum(ss), curBookIndex);
            }
            nIndex.insertVal(strToNum(name), curBookIndex);
            memcpy(curBook.name, name.c_str(), NameSize);
        
        }
        if (author != "\"") {
            auto ss = std::string(curBook.author);
            if (ss != "\"") {
                aIndex.deleteVal(strToNum(ss), curBookIndex);
            }
            aIndex.insertVal(strToNum(author), curBookIndex);
            memcpy(curBook.author, author.c_str(), NameSize);
        }
        if (keyword != "\"") {
            auto ss = std::string(curBook.keyword);
            if (ss != "\"") {
                
            }
            memcpy(curBook.keyword, keyword.c_str(), NameSize);
        }
        if (price != -1) curBook.price = price;
        bData.replaceElement(curBookIndex, &curBook);
    }
    void import(int quantity, double totalPrice) {
        curBook.stock += quantity;
        bData.replaceElement(curBookIndex, &curBook);
        Trade tmp(0, totalPrice);
        tData.addElement(&tmp);
    }
    void show(std::string isbn = "\"", std::string name = "\"", std::string author = "\"", std::string keyword = "\"") {
        std::vector<int> v;
        std::vector<Book> bookToShow;
        Book hhh;
        if (isbn != "\"") {
            v = iIndex.qryforVal(strToNum(isbn));
            for (int i : v) {
                bData.getElement(&hhh, i);
                if (hhh.ISBN == isbn) {
                    bookToShow.push_back(hhh);
                }
            }
        } else if (name != "\"") {
            v = iIndex.qryforVal(strToNum(name));
            for (int i : v) {
                bData.getElement(&hhh, i);
                if (hhh.name == name) {
                    bookToShow.push_back(hhh);
                }
            }
        } else if (author != "\"") {
            v = iIndex.qryforVal(strToNum(author));
            for (int i : v) {
                bData.getElement(&hhh, i);
                if (hhh.author == author) {
                    bookToShow.push_back(hhh);
                }
            }
        } else if (keyword != "\"") {
            v = iIndex.qryforVal(strToNum(keyword));
            for (int i : v) {
                bData.getElement(&hhh, i);
                if (hhh.keyword == keyword) {
                    bookToShow.push_back(hhh);
                }
            }
        }
        std::sort(bookToShow.begin(), bookToShow.end());
        for (auto i : bookToShow) {
            std::cout << i.ISBN << "\t" << i.name << "\t" << i.author << "\t" << i.keyword << "\t" << i.price << "\t" << i.stock << "本" << std::endl;
        }
    }
    void showfinance(int n = -1) {
        double in = 0.0, out = 0.0;
        Trade tmp;
        if (n == -1) {
            for (int i = 0; i < tData.tot; i++) {
                tData.getElement(&tmp, i);
                in += tmp.in;
                out += tmp.out;
            }
        } else {
            for (int i = tData.tot - n; i < tData.tot; i++) {
                tData.getElement(&tmp, i);
                in += tmp.in;
                out += tmp.out;
            }
        }
        std::cout << "+ " << in << " - " << out << std::endl;
    }
    void buy(std::string isbn, int quantity) {
        std::vector<int> v = iIndex.qryforVal(strToNum(isbn));
        for (int i : v) {
            Book hhh = bData.getElement(i);
            if (hhh.ISBN == isbn) {
                hhh.stock -= quantity;
                bData.replaceElement(i, &hhh);
                Trade tmp(hhh.price * quantity, 0);
                tData.addElement(&tmp);
                return;
            }
        }
    }
    
    void load(std::string f);
    void work(std::fstream *input);
    
    std::vector<std::string> split(std::stringstream *is) {
        std::string tmp;
        std::vector<std::string> ret;
        while (*is >> tmp) {
            ret.push_back(tmp);
        }
        return ret;
    }
    std::pair<int, int> nextQuote(size_t pos, std::string *s) {
        int bg = -1, ed = -1;
        for (size_t j = pos + 5; j < s->length(); j++) {
            if ((*s)[j] == '"') {
                if (bg == -1) {
                    bg = (int)j;
                } else if (ed == -1) {
                    ed = (int)j;
                } else {
                    break;
                }
            }
        }
        return {bg, ed};
    }
    void exec(std::string cmd) {
        std::stringstream is(cmd);
        std::string key;
        is >> key;
        std::vector<std::string> v;
        if (key != "modify"){
            v = split(&is);
        }
        if (key == "load") {
            load(v[1]);
        } else if (key == "exit") {
            
        } else if (key == "su") {
            su(v[1], v[2]);
        } else if (key == "logout") {
            logout();
        } else if (key == "useradd") {
            useradd(v[1], v[2], v[3], v[4]);
        } else if (key == "register") {
            regi(v[1], v[2], v[3]);
        } else if (key == "delete") {
            del(v[1]);
        } else if (key == "passwd") {
            pswd(v);
        } else if (key == "select") {
            select(v[1]);
        } else if (key == "modify") {
            std::string s = is.str();
            std::cout << s << std::endl;
            size_t pos;
            if ((pos = s.find("-ISBN")) != std::string::npos) {
                auto pr = nextQuote(pos, &s);
                auto ss = s.substr(pr.first + 1, pr.second - pr.first - 1);
                modify(ss, "\"", "\"", "\"", -1.0);
            }
            if ((pos = s.find("-name")) != std::string::npos) {
                auto pr = nextQuote(pos, &s);
                auto ss = s.substr(pr.first + 1, pr.second - pr.first - 1);
                modify("\"", ss, "\"", "\"", -1.0);
            }
            if ((pos = s.find("-author")) != std::string::npos) {
                auto pr = nextQuote(pos, &s);
                auto ss = s.substr(pr.first + 1, pr.second - pr.first - 1);
                modify("\"", "\"", ss, "\"", -1.0);
            }
            if ((pos = s.find("-keyword")) != std::string::npos) {
                auto pr = nextQuote(pos, &s);
                auto ss = s.substr(pr.first + 1, pr.second - pr.first - 1);
                modify("\"", "\"", "\"", ss, -1.0);
            }
            if ((pos = s.find("-price")) != std::string::npos) {
                auto pr = nextQuote(pos, &s);
                auto ss = s.substr(pr.first + 1, pr.second - pr.first - 1);
                std::stringstream is(ss);
                double p = -1.0;
                is >> p;
                modify("\"", "\"", "\"", "\"", p);
            }
        } else if (key == "show") {
            if (v[1] == "finance") {
                if (v.size() == 4) {
                    showfinance(parseStr(v[3]));
                } else {
                    showfinance();
                }
            }
        } else if (key == "buy") {
            buy(v[1], parseStr(v[2]));
        }
    }
    

};

#endif /* BookStore_hpp */
