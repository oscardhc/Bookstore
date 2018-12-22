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
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Person.hpp"
#include "Book.hpp"
#include "DataBase.hpp"
#include "Block.hpp"
#include "Trade.hpp"
#include "Operation.hpp"
//#include "BFIndex.hpp"

class Parser {

public:
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
    std::vector<std::string> splitKeyword(std::string *s) {
        std::vector<std::string> ret;
        size_t ls = 0;
        for (size_t j = 0; j < s->length(); j++) {
            if ((*s)[j] == '|') {
                ret.push_back(s->substr(ls, j - ls));
                ls = j + 1;
            }
        }
        ret.push_back(s->substr(ls, s->length() - ls));
        return ret;
    }

}parser;

class BookStore {
private:
    Person curUser;
    int curUserIndex;
    Book curBook;
    int curBookIndex;
    Blocks iIndex, nIndex, aIndex, kIndex, pIndex;
    DataBase<Book, sizeof(Book)> bData;
    DataBase<Person, sizeof(Person)> pData;
    DataBase<Trade, sizeof(Trade)> tData;
    DataBase<Operation, sizeof(Operation)> rData;

public:
    BookStore() {
        std::cout << std::fixed << std::setprecision(2);
        curBookIndex = -1;
        iIndex.init("./isbn_index.bi");
        nIndex.init("./name_index.bi");
        aIndex.init("./author_index.bi");
        kIndex.init("./keyword_index.bi");
        pIndex.init("./price_index.bi");
        bData.init("./book_data.bi");
        pData.init("./person_data.bi");
        tData.init("./trade_data.bi");
        if (pData.tot == 0) {
            curUser.level = 233;
            useradd("root", "sjtu", "7", "yyu");
        }
        rData.init("./report_data.bi");
    }

    void select(std::string isbn) {
        if (curUser.level < 3) {
            std::cout << "Invalid" << std::endl;
            return;
        }
        int num = parser.strToNum(isbn);
        auto v = iIndex.qryforVal(num);
        if (v.empty()) {
            Book bk(isbn.c_str(), "", "", "", 0, 0);
            curBookIndex = bData.addElement(&bk);
            iIndex.insertVal(parser.strToNum(isbn), curBookIndex);
        } else {
            curBookIndex = v[0];
        }
        curBook = bData.getElement(curBookIndex);
    }
    void su(std::vector<std::string> v) {
        Person tmp;
        for (int i = 0; i < pData.tot; i++) {
            pData.getElement(&tmp, i);
            if (std::string(tmp.userid) == v[0]) {
                if (tmp.level < curUser.level || std::string(tmp.passwd) == v[1]) {
                    curUser = tmp;
                    curUserIndex = i;
                } else {
                    std::cout << "Invalid" << std::endl;
                }
                return;
            }
        }
        std::cout << "Invalid" << std::endl;
        return;
    }
    void logout() {
        if (curUser.level < 1) {
            std::cout << "Invalid" << std::endl;
            return;
        }
        curUserIndex = -1;
        curUser = Person();
    }
    void useradd(std::string userid, std::string passwd, std::string level, std::string name) {
        if (curUser.level < 3 || curUser.level <= parser.parseStr(level)) {
            std::cout << "Invalid" << std::endl;
            return;
        }
        Person tmp;
        for (int i = 0; i < pData.tot; i++) {
            pData.getElement(&tmp, i);
            if (std::string(tmp.userid) == userid) {
                std::cout << "Invalid" << std::endl;
                return;
            }
        }
        tmp = Person(userid.c_str(), passwd.c_str(), name.c_str(), parser.parseStr(level));
        pData.addElement(&tmp);
    }
    void regi(std::string userid, std::string passwd, std::string name) {
        Person tmp;
        tmp = Person(userid.c_str(), passwd.c_str(), name.c_str(), 1);
        pData.addElement(&tmp);
    }
    void del(std::string userid) {
        if (curUser.level < 7) {
            std::cout << "Invalid" << std::endl;
            return;
        }
        Person tmp;
        for (int i = 0; i < pData.tot; i++) {
            pData.getElement(&tmp, i);
            if (std::string(tmp.userid) == userid) {
                pData.delElement(i);
                return;
            }
        }
        std::cout << "Invalid" << std::endl;
        return;
    }
    void changePassword(std::string userid, std::string passwd, std::string oldpasswd = " ") {
        if (curUser.level < 1) {
            std::cout << "Invalid" << std::endl;
            return;
        }
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
                    std::cout << "Invalid" << std::endl;
                    return;
                }
                return;
            }
        }
        std::cout << "Invalid" << std::endl;
        return;
    }
    void pswd(std::vector<std::string> v) {
        if (curUser.level < 1) {
            std::cout << "Invalid" << std::endl;
            return;
        }
        if (curUser.level == 7) {
            if (v.size() == 2) changePassword(v[0], v[1]);
            else {
                std::cout << "Invalid" << std::endl;
                return;
            }
        } else {
            if (v.size() == 3) changePassword(v[0], v[2], v[1]);
            else {
                std::cout << "Invalid" << std::endl;
                return;
            }
        }
    }
    void modify(std::string isbn = "\"", std::string name = "\"", std::string author = "\"", std::string keyword = "\"", double price = -1.0) {
        if (curUser.level < 3) {
            std::cout << "Invalid" << std::endl;
            return;
        }
        if (curBookIndex == -1) {
            std::cout << "Invalid" << std::endl;
            return;
        }
        if (isbn != "\"") {
            auto ss = std::string(curBook.ISBN);
            auto v = iIndex.qryforVal(parser.strToNum(isbn));
            if (!v.empty()) {
                std::cout << "Invalid" << std::endl;
                return;
            }
            if (ss != "\"") {
                iIndex.deleteVal(parser.strToNum(ss), curBookIndex);
            }
            iIndex.insertVal(parser.strToNum(isbn), curBookIndex);
            memcpy(curBook.ISBN, isbn.c_str(), ISBNSize);
        }
        if (name != "\"") {
            auto ss = std::string(curBook.name);
            if (ss != "\"") {
                nIndex.deleteVal(parser.strToNum(ss), curBookIndex);
            }
            nIndex.insertVal(parser.strToNum(name), curBookIndex);
            memcpy(curBook.name, name.c_str(), NameSize);

        }
        if (author != "\"") {
            auto ss = std::string(curBook.author);
            if (ss != "\"") {
                aIndex.deleteVal(parser.strToNum(ss), curBookIndex);
            }
            aIndex.insertVal(parser.strToNum(author), curBookIndex);
            memcpy(curBook.author, author.c_str(), NameSize);
        }
        if (keyword != "\"") {
            auto ss = std::string(curBook.keyword);
            if (ss != "\"") {
                auto v1 = parser.splitKeyword(&ss);
                for (auto i : v1) {
                    kIndex.deleteVal(parser.strToNum(i), curBookIndex);
                }
            }
            auto v2 = parser.splitKeyword(&keyword);
            for (auto i : v2) {
                kIndex.insertVal(parser.strToNum(i), curBookIndex);
            }
            memcpy(curBook.keyword, keyword.c_str(), NameSize);
        }
        if (price != -1) {

            if (curBook.price != -1) {
                pIndex.deleteVal((int)(curBook.price * 10000000), curBookIndex);
            }
            pIndex.insertVal((int)(price * 10000000), curBookIndex);

            curBook.price = price;
        }
        bData.replaceElement(curBookIndex, &curBook);
    }
    void import(int quantity, double totalPrice) {
        if (curUser.level < 3) {
            std::cout << "Invalid" << std::endl;
            return;
        }
        if (curBookIndex == -1) {
            std::cout << "Invalid" << std::endl;
            return;
        }
        curBook.stock += quantity;
        bData.replaceElement(curBookIndex, &curBook);
        Trade tmp(0, totalPrice);
        tData.addElement(&tmp);
    }
    void show(std::string isbn = "\"", std::string name = "\"", std::string author = "\"", std::string keyword = "\"") {
        if (curUser.level < 1) {
            std::cout << "Invalid" << std::endl;
            return;
        }

        std::vector<int> v;
        std::vector<Book> bookToShow;

        Book hhh;
        if (isbn != "\"") {
            v = iIndex.qryforVal(parser.strToNum(isbn));
            for (int i : v) {
                bData.getElement(&hhh, i);
                if (hhh.ISBN == isbn) {
                    bookToShow.push_back(hhh);
                }
            }
        } else if (name != "\"") {
            v = nIndex.qryforVal(parser.strToNum(name));

            for (int i : v) {
                bData.getElement(&hhh, i);
                if (hhh.name == name) {
                    bookToShow.push_back(hhh);
                }
            }
        } else if (author != "\"") {
            v = aIndex.qryforVal(parser.strToNum(author));
            for (int i : v) {
                bData.getElement(&hhh, i);
                if (hhh.author == author) {
                    bookToShow.push_back(hhh);
                }
            }
        } else if (keyword != "\"") {
            v = kIndex.qryforVal(parser.strToNum(keyword));
            for (int i : v) {
                bData.getElement(&hhh, i);
                if (std::string(hhh.keyword).find(keyword) != std::string::npos) {
                    bookToShow.push_back(hhh);
                }
            }
        } else {
            for (int i = 0; i < bData.tot; i++) {
                Book tmp = bData.getElement(i);
                if (std::string(tmp.ISBN) != "\"") {
                    bookToShow.push_back(tmp);
                }
            }
        }
        std::sort(bookToShow.begin(), bookToShow.end());
        for (auto i : bookToShow) {
            std::cout << i.ISBN << "\t" << i.name << "\t" << i.author << "\t" << i.keyword << "\t" << i.price << "\t" << i.stock << "本" << std::endl;
        }
    }
    void showfinance(int n = -1) {
        if (curUser.level < 7) {
            std::cout << "Invalid" << std::endl;
            return;
        }
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
        if (curUser.level < 1) {
            std::cout << "Invalid" << std::endl;
            return;
        }
        std::vector<int> v = iIndex.qryforVal(parser.strToNum(isbn));
        for (int i : v) {
            Book hhh = bData.getElement(i);
            if (hhh.ISBN == isbn) {
                    if (hhh.stock >= quantity) {
                    hhh.stock -= quantity;
                    bData.replaceElement(i, &hhh);
                    Trade tmp(hhh.price * quantity, 0);
                    tData.addElement(&tmp);
                } else {
                    std::cout << "Invalid" << std::endl;
                    return;
                }
                return;
            }
        }
    }
    void report(std::string userid = " ") {
        std::cout << "-------------------- REPORT EMPOLYEE -------------------" << std::endl;
        Operation tmp;
        Person usr;
        for (int i = 0; i < rData.tot; i++) {
            rData.getElement(&tmp, i);
            pData.getElement(&usr, tmp.useridx);
            if (userid == " " || std::string(usr.userid) == userid) {
                std::cout << tmp.cmd << " by " << usr.name << "(" << usr.userid << ")" << std::endl;
            }
        }
        std::cout << "--------------------------------------------------------" << std::endl;
    }
    void reportFinace() {
        std::cout << "-------------------- REPORT FINANCE --------------------" << std::endl;
        Trade tmp;
        for (int i = 0; i < tData.tot; i++) {
            tData.getElement(&tmp, i);
            std::cout << "+" << tmp.in << "    -" << tmp.out << std::endl;
        }
        std::cout << "--------------------------------------------------------" << std::endl;
    }

    void load(std::string f);
    void work(std::fstream *input);
    void exec(std::string cmd) {
//        std::cout << cmd << std::endl;
        Operation tmpopr(curUserIndex, cmd.c_str());
        rData.addElement(&tmpopr);
        std::stringstream is(cmd);
        std::string key;
        is >> key;
        std::vector<std::string> v;

        if (key != "modify"){
            v = parser.split(&is);
        }
        if (key == "load") {
            if (v.size() == 1) load(v[0]);
            else {
                std::cout << "Invalid" << std::endl;
                return;
            }
        } else if (key == "exit") {
            throw 1;
        } else if (key == "su") {
            if (v.size() > 0) su(v);
            else {
                std::cout << "Invalid" << std::endl;
                return;
            }
        } else if (key == "logout") {
            logout();
        } else if (key == "useradd") {
            if (v.size() == 4) useradd(v[0], v[1], v[2], v[3]);
            else {
                std::cout << "Invalid" << std::endl;
                return;
            }
        } else if (key == "register") {
            if (v.size() == 3) regi(v[0], v[1], v[2]);
            else {
                std::cout << "Invalid" << std::endl;
                return;
            }
        } else if (key == "delete") {
            if (v.size() == 1) del(v[0]);
            else {
                std::cout << "Invalid" << std::endl;
                return;
            }
        } else if (key == "passwd") {
            pswd(v);
        } else if (key == "select") {
            if (v.size()) select(v[0]);
            else {
                std::cout << "Invalid" << std::endl;
                return;
            }
        } else if (key == "modify") {
            std::string s = is.str();
            size_t pos;
            if ((pos = s.find("-ISBN")) != std::string::npos) {
                std::string ss = "";
                for (size_t j = pos + 6; j < s.length(); j++) {
                    if (s[j] >= '0' && s[j] <= '9') {
                        ss.push_back(s[j]);
                    } else break;
                }
                modify(ss, "\"", "\"", "\"", -1.0);
            }
            if ((pos = s.find("-name")) != std::string::npos) {
                auto pr = parser.nextQuote(pos, &s);
                auto ss = s.substr(pr.first + 1, pr.second - pr.first - 1);
                modify("\"", ss, "\"", "\"", -1.0);
            }
            if ((pos = s.find("-author")) != std::string::npos) {
                auto pr = parser.nextQuote(pos, &s);
                auto ss = s.substr(pr.first + 1, pr.second - pr.first - 1);
                modify("\"", "\"", ss, "\"", -1.0);
            }
            if ((pos = s.find("-keyword")) != std::string::npos) {
                auto pr = parser.nextQuote(pos, &s);
                auto ss = s.substr(pr.first + 1, pr.second - pr.first - 1);
                modify("\"", "\"", "\"", ss, -1.0);
            }
            if ((pos = s.find("-price")) != std::string::npos) {
                auto ss = s.substr(pos + 7, 100);
                std::stringstream is(ss);
                double p = -1.0;
                is >> p;
                modify("\"", "\"", "\"", "\"", p);
            }
        } else if (key == "import") {
            if (v.size() != 2) {
                std::cout << "Invalid" << std::endl;
                return;
            }
            std::stringstream is(v[0] + " " + v[1]);
            int q = -1;
            double p = -1.0;
            is >> q >> p;
            import(q, p);
        } else if (key == "show") {
            if (v.size() > 0 && v[0] == "finance") {
                if (v.size() == 2) {
                    showfinance(parser.parseStr(v[1]));
                } else {
                    showfinance();
                }
            } else {
                std::string s = is.str();
                size_t pos;
                if ((pos = s.find("-ISBN")) != std::string::npos) {
                    std::string ss = "";
                    for (size_t j = pos + 6; j < s.length(); j++) {
                        if (s[j] >= '0' && s[j] <= '9') {
                            ss.push_back(s[j]);
                        } else break;
                    }
                    show(ss, "\"", "\"", "\"");
                } else if ((pos = s.find("-name")) != std::string::npos) {
                    auto pr = parser.nextQuote(pos, &s);
                    auto ss = s.substr(pr.first + 1, pr.second - pr.first - 1);
                    show("\"", ss, "\"", "\"");
                } else if ((pos = s.find("-author")) != std::string::npos) {
                    auto pr = parser.nextQuote(pos, &s);
                    auto ss = s.substr(pr.first + 1, pr.second - pr.first - 1);
                    show("\"", "\"", ss, "\"");
                } else if ((pos = s.find("-keyword")) != std::string::npos) {
                    auto pr = parser.nextQuote(pos, &s);
                    auto ss = s.substr(pr.first + 1, pr.second - pr.first - 1);
                    show("\"", "\"", "\"", ss);
                } else {
                    show("\"", "\"", "\"", "\"");
                }
            }
        } else if (key == "buy") {
            if (v.size() != 2) {
                std::cout << "Invalid" << std::endl;
                return;
            }
            buy(v[0], parser.parseStr(v[1]));
        } else if (key == "report") {
            if (v.size() == 1 && v[0] == "myself") {
                report(curUser.userid);
            } else if (v.size() == 1 && v[0] == "employee") {
                report();
            } else if (v.size() == 1 && v[0] == "finance") {
                reportFinace();
            } else {
                
            }
        } else if (key == "log") {
            report();
            reportFinace();
        } else {
            std::cout << "Invalid" << std::endl;
            return;
        }
    }
    void run() {
        std::fstream f("./command.txt", std::ios::in);
        work(&f);
    }
};

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

#endif /* BookStore_hpp */
