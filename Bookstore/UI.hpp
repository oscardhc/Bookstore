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

class UI {
    char str[205];
public:
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
        std::cout << "|                 \\\\.......\\======/....................//                        请输入命令，如需获取帮助，请输入\"help\"。                   |" << std::endl;
        std::cout << "|                  \\\\.................................//                         当你遇到了\"invalid\"，请不要悲伤，不要心急，                |" << std::endl;
        std::cout << "|                    \\\\.............................//                           可能是你的权限，或者是命令格式出了点小问题，请检查。       |" << std::endl;
        std::cout << "|                     \\\\...........................//                            求求尊敬的用户们不要乱搞系统，小猪佩奇那么可爱！           |" << std::endl;
        std::cout << "|                       \\\\\\.....................///                                                                                         |" << std::endl;
        std::cout << "|                          \\\\\\=.............=///                                                                                            |" << std::endl;
        std::cout << "|                               ===========                                                                                                 |" << std::endl;
        std::cout << "+-------------------------------------------------------------------------------------------------------------------------------------------+" << std::endl;
    }
    void help() {
        std::cout << "load [destination]                          从[destination]文件中读取每行一个的命令并由权限7开始逐个执行" << std::endl;
        std::cout << "su [user‐id] [passwd]                       登录到某用户，从高权限用户登录到低权限不需填写密码" << std::endl;
        std::cout << "logout                                      返回到未登录状态" << std::endl;
        std::cout << "useradd [user‐id] [passwd] [7/3/1] [name]   增加一个指定权限的用户，不能创建不小于自己权限的账户" << std::endl;
        std::cout << "register [user‐id] [passwd] [name]          注册一个带有这些信息的权限1用户" << std::endl;
        std::cout << "delete [user‐id]                            删除某用户" << std::endl;
        std::cout << "passwd [user‐id] [old‐passwd] [new‐passwd]  修改密码，root不需要填写旧密码，其余账户需要" << std::endl;
        std::cout << "select [ISBN]                               选定ISBN为指定值的图书，若不存在则创建该ISBN的书并将其余信息留空等待modify进行填写" << std::endl;
        std::cout << "modify ‐ISBN=[?] ‐name=[?] ‐author=[?] ‐keyword=[?] ‐price=[?]   参数可省略，也不要求输入顺序，会更新(替换而非添加)上次选中的书至新的信息" << std::endl;
        std::cout << "show ‐ISBN=[?] ‐name=[?] ‐author=[?] ‐keyword=[?]                参数可省略，也不要求输入顺序，将匹配的图书以ISBN号排序输出，需要注意该命令关键字项只支持单关键字" << std::endl;
        std::cout << "import [quantity] [cost_price(in total)]    将上次选中的书以总共[cost_price]的价格进[quantity]本" << std::endl;
        std::cout << "show finance [time]                         time项省略时，输出总的收入与支出;否则输出近[time]次进货、卖出操作(分别算一次)的收入支出。" << std::endl;
        std::cout << "report finance                              会生成一张赏心悦目的财务报表" << std::endl;
        std::cout << "report employee                             会生成一张赏心悦目的员工工作情况表，记录其操作" << std::endl;
        std::cout << "log                                         会返回赏心悦目的日志记录，包括系统操作类的谁干了什么，以及财务上每一笔交易情况" << std::endl;
        std::cout << "report myself                               返回员工自己的操作记录" << std::endl;

    }
    std::string readCommand() {
        std::cout << "请输入你的命令，如需帮助请输入\"help\"：  ";
        if (std::cin.getline(str, 200)) {
            return std::string(str);
        } else {
            throw 1;
        }
    }
};

#endif /* UI_hpp */
