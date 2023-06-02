#ifndef ALGRAPH_H
#define ALGRAPH_H

#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<assert.h>
#include<QMessageBox>
#include<QTableWidget>
#include<QDebug>
#include<QLabel>
#define MAXFILESIZE 50

struct Time {
    //时间格式: month,day,hour,minute

    Time(const int mon = 1, const int d = 0, const int h = 0, const int min = 0)
        : month(mon), day(d), hour(h), minute(min) {}

    int month;
    int day;
    int hour;
    int minute;

    int getTotalMinute() const {
        int totalMinutes = 0;

        // 计算前几个月的总分钟数
        for (int i = 1; i < month; i++) {
            switch (i) {
            case 2:
                totalMinutes += 28 * 24 * 60;  // 二月份假设为28天
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                totalMinutes += 30 * 24 * 60;  // 四、六、九、十一月份为30天
                break;
            default:
                totalMinutes += 31 * 24 * 60;  // 其他月份为31天
                break;
            }
        }

        // 加上当前月的分钟数
        totalMinutes += (day - 1) * 24 * 60;
        totalMinutes += hour * 60;
        totalMinutes += minute;

        return totalMinutes;
    }

};



struct LineNode {  // 线路信息，作为边表的元素

    LineNode(const std::string v, const std::string ln, const std::string scn, const std::string ecn, const Time st, const Time et, const float sm)
        : vehicle(v), line_number(ln), start_city_name(scn), end_city_name(ecn),
        start_time(st), end_time(et), spend_money(sm) {}

    LineNode() = default;

    std::string vehicle;  // 交通工具类型，如飞机、火车等
    std::string line_number;  // 班次号，如火车、飞机班次等
    std::string start_city_name;  // 出发城市
    std::string end_city_name;  // 到达城市
    Time start_time;  // 出发时间
    Time end_time;  // 到达时间
    float spend_money;  // 花费的金钱
};



class ALGraph {
public:
    bool ifCityExist(const std::string& city_name);  // 查询城市是否存在

    bool check_sc_and_ec(const std::string& sc, const std::string& ec); //判断起点和终点的合法性并给出提示

    void addCity(const std::string& city_name);  // 手动添加城市

    void addCityFromFile(const std::string& FILENAM);  // 从文件读取以添加城市

    void addLine(const struct LineNode newLineNode);  //手动添加线路

    void addLineFromFile(const std::string& FILENAME);  // 从文件读取以添加线路

    void delLine(const std::string& line_number);// 删除线路，按照班次删除

    void delCity(const std::string& city_name);  // 删除城市，并删除以该城市为起点的航班和列车信息

    void showAllCity(QTableWidget *parent);  // 输出所有城市

    void showAllLine(QTableWidget *parent);  // 输出所有线路

    // 输出从起点城市到终点城市，中转次数最少的路径
    void printLeastTransferPath(QTableWidget *parent, QLabel *ResShow, const std::string& sc, const std::string& ec, const int st_time);

    // 输出从起点城市到终点城市，花费最小的线路
    void printLeastMoneyPath(QTableWidget *parent, QLabel *ResShow, const std::string& sc, const std::string& ec, const int st_time);

    // 输出从起点城市到终点城市，总时间最短的线路
    void printLeastTimePath(QTableWidget *parent,QLabel *ResShow, const std::string& sc, const std::string& ec, const int st_time);

public:

    std::map <std::string, std::vector<LineNode>> m;  //以城市为关键字存储
    std::map <std::string, LineNode> mp;  // 以班次为关键字存储
    int Transit_time;

};

#endif // ALGRAPH_H
