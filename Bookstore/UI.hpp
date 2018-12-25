//
//  UI.hpp
//  Bookstore
//
//  Created by Haichen Dong on 2018/12/24.
//  Copyright © 2018 Haichen Dong. All rights reserved.
//

#ifndef UI_hpp
#define UI_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "Person.hpp"

std::string levelMap[10];
std::string helpText[20];
std::string command[20];
std::string argText[20];

class UI {
    char str[205];
    
public:
    UI() {
        levelMap[0] = "  GUEST ";
        levelMap[1] = "CUSTOMER";
        levelMap[3] = "  STAFF ";
        levelMap[7] = "  BOSS  ";
        helpText[ 1] = " load [destination]                          从[destination]文件中读取每行一个的命令并由权限7开始逐个执行";
        helpText[ 2] = " su [user‐id] [passwd]                       登录到某用户，从高权限用户登录到低权限不需填写密码";
        helpText[ 3] = " logout                                      返回到未登录状态";
        helpText[ 4] = " useradd [user‐id] [passwd] [7/3/1] [name]   增加一个指定权限的用户，不能创建不小于自己权限的账户";
        helpText[ 5] = " register [user‐id] [passwd] [name]          注册一个带有这些信息的权限1用户";
        helpText[ 6] = " delete [user‐id]                            删除某用户";
        helpText[ 7] = " passwd [user‐id] [old‐passwd] [new‐passwd]  修改密码，root不需要填写旧密码，其余账户需要";
        helpText[ 8] = " select [ISBN]                               选定ISBN为指定值的图书，若不存在则创建该ISBN的书并将其余信息留空等待modify进行填写";
        helpText[ 9] = " modify ‐ISBN=[?] ‐name=[?] ‐author=[?] ‐keyword=[?] ‐price=[?]   参数可省略，也不要求输入顺序，会更新(替换而非添加)上次选中的书至新的信息";
        helpText[10] = " show ‐ISBN=[?] ‐name=[?] ‐author=[?] ‐keyword=[?]                参数可省略，也不要求输入顺序，将匹配的图书以ISBN号排序输出，需要注意该命令关键字项只支持单关键字";
        helpText[11] = " import [quantity] [cost_price(in total)]    将上次选中的书以总共[cost_price]的价格进[quantity]本";
        helpText[12] = " show finance [time]                         time项省略时，输出总的收入与支出;否则输出近[time]次进货、卖出操作(分别算一次)的收入支出。";
        helpText[13] = " report finance                              会生成一张赏心悦目的财务报表";
        helpText[14] = " report employee                             会生成一张赏心悦目的员工工作情况表，记录其操作";
        helpText[15] = " log                                         会返回赏心悦目的日志记录，包括系统操作类的谁干了什么，以及财务上每一笔交易情况";
        helpText[16] = " report myself                               返回员工自己的操作记录";
        command[ 1] = "load";
        command[ 2] = "su";
        command[ 3] = "logout";
        command[ 4] = "useradd";
        command[ 5] = "register";
        command[ 6] = "delete";
        command[ 7] = "passwd";
        command[ 8] = "select";
        command[ 9] = "modify";
        command[10] = "show";
        command[11] = "import";
        command[12] = "show finance";
        command[13] = "report finance";
        command[14] = "report employee";
        command[15] = "log";
        command[16] = "report myself";
        argText[ 1] = "文件名。";
        argText[ 2] = "用户名，密码。";
        argText[ 3] = "";
        argText[ 4] = "用户名，密码，权限，姓名。";
        argText[ 5] = "用户名。";
        argText[ 6] = "用户名，原密码（如果不是root），新密码。";
        argText[ 7] = "ISBN号。";
        argText[ 8] = "描述信息";
        argText[ 9] = "数量，总价。";
        argText[10] = "描述信息";
        argText[11] = "显示次数（可选）";
        argText[12] = "ISBN号，购买数量。";
        argText[13] = "";
        argText[14] = "";
        argText[15] = "";
        argText[16] = "";
    }
    void startingView() {
        system("clear");
        std::cout << "+-------------------------------------------------------------------------------------------------------------------------------------------+" << std::endl;
        std::cout << "|                                    //==\\\\                                                                                                 |" << std::endl;
        std::cout << "|                                   /.....|                                                                                                 |" << std::endl;
        std::cout << "|                                  |......|                                                                                                 |" << std::endl;
        std::cout << "|                                  |......|         ==\\                                                                                     |" << std::endl;
        std::cout << "|     //=...\\\\\\=......=========    |...../       /....\\|                                                                                    |" << std::endl;
        std::cout << "|   //........\\\\................===\\\\..//       /......|                                                                                    |" << std::endl;
        std::cout << "| //...........||......./===\\........\\\\\\\\      |......|                                欢迎来到网上书店管理系统！                           |" << std::endl;
        std::cout << "| ||.@@.........|.....//     \\\\..........\\\\\\  |....../                                                                                      |" << std::endl;
        std::cout << "| |........@@..||.....|   @@  |.//   \\\\\\....=\\|\\...//                                                                                       |" << std::endl;
        std::cout << "| ||.........../......\\\\  @  //||      ||.......\\\\\\                                                        By      Haichen Dong             |" << std::endl;
        std::cout << "|  \\\\........//.........\\===/..||  @@@ ||..........\\\\                                                      For     Programming Homework     |" << std::endl;
        std::cout << "|    \\\\====//...................\\\\\\ =///............\\\\                                                                                      |" << std::endl;
        std::cout << "|       \\\\\\...........................................\\\\                                                                                    |" << std::endl;
        std::cout << "|         \\\\\\..........................................\\\\                                                                                   |" << std::endl;
        std::cout << "|            \\\\\\\\..............................!!!!!....|                                                                                   |" << std::endl;
        std::cout << "|                ||..........................!!!!!!!!!..||                                                                                  |" << std::endl;
        std::cout << "|                |..........................!!!!!!!!!!!..|                                                                                  |" << std::endl;
        std::cout << "|                |....|.....................!!!!!!!!!!!..|                                                                                  |" << std::endl;
        std::cout << "|                |..........................!!!!!!!!!!...|                                                                                  |" << std::endl;
        std::cout << "|                ||....\\\\....................!!!!!!!....||                                                                                  |" << std::endl;
        std::cout << "|                 |......\\\\........../..................|                                                                                   |" << std::endl;
        std::cout << "|                 \\\\.......\\======/....................//                        请输入命令并回车，如需获取帮助，请输入\"help\"。             |" << std::endl;
        std::cout << "|                  \\\\.................................//                         当你遇到了\"invalid\"，请不要悲伤，不要心急，                |" << std::endl;
        std::cout << "|                    \\\\.............................//                           可能是你的权限，或者是命令格式出了点小问题，请检查。       |" << std::endl;
        std::cout << "|                     \\\\...........................//                            求求尊敬的用户们不要乱搞系统，吹风机那么可爱！             |" << std::endl;
        std::cout << "|                       \\\\\\.....................///                                                                                         |" << std::endl;
        std::cout << "|                          \\\\\\=.............=///                                                                                            |" << std::endl;
        std::cout << "|                               ===========                                                                                                 |" << std::endl;
        std::cout << "+-------------------------------------------------------------------------------------------------------------------------------------------+" << std::endl;
    }
    std::string help() {
        std::cout << "请输入数字来进入对应操作:  " << std::endl;
        for (int i = 1; i <= 16; i++) {
            std::cout << i << (i < 10? " " : "") << ":" << helpText[i] << std::endl;
        }
        int id;
        std::cin >> id;
        std::cin.ignore(100, '\n');
        std::string ret = command[id];
        char cot[205];
        if(argText[id] != "") {
            std::cout << "请依次输入" << argText[id] << std::endl;
            std::cin.getline(cot, 200);
            ret = ret + " " + std::string(cot);
        }
        std::cout << "开始执行   " << ret << std::endl;
        return ret;
    }
    std::string readCommand(Person *user) {
        if (user->level > 0) {
            std::cout << "[" << levelMap[user->level] << "]  " << user->name << "(" << user->userid << ")@BookStore $ ";
        } else {
            std::cout << "[" << levelMap[user->level] << "]  guest@BookStore $ ";
        }
        
        if (std::cin.getline(str, 200)) {
            return std::string(str);
        } else {
            throw 1;
        }
    }
};

#endif /* UI_hpp */
