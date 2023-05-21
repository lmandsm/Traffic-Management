#pragma execution_character_set("utf-8")
#include"ALGraph.h"
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<queue>
#include<stack>
#include<algorithm>
#define INF 0xfffff

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::istringstream;
using std::setw;
using std::setiosflags;
using std::resetiosflags;
using std::ios_base;
using std::ifstream;
using std::string;
using std::vector;
using std::map;
using std::set;
using std::pair;
using std::make_pair;

//using std::vector;



// Time 对象的"<"重载，实现两个 Time 对象的比较
bool operator > (Time t1, Time t2) {
    return t1.getTotalMinute() > t2.getTotalMinute();
}

bool operator < (Time t1, Time t2) {
    return t1.getTotalMinute() < t2.getTotalMinute();
}

//查询城市是否存在
bool ALGraph::ifCityExist(const std::string& city_name) {
    auto it = m.find(city_name);
    return it != m.cend();
}

//判断起点和终点的合法性并给出提示
bool ALGraph::check_sc_and_ec(const std::string& sc, const std::string& ec) {
    QString tmp;
    if ((!ifCityExist(sc)) && (!ifCityExist(ec))) {
        //cout << "系统中未存在" << sc << "和" << ec << "这两座城市，请先添加这两座城市！" << endl;
        tmp="系统未存在"+QString::fromStdString(sc)+"和"+QString::fromStdString(ec)+"这两座城市，请先添加这两座城市！";
        QMessageBox::warning(nullptr,"错误",tmp);
        return 0;
    }

    if (!ifCityExist(sc)) {
        tmp="系统中未存在"+QString::fromStdString(sc)+"这座城市，请先添加这座城市!";
        QMessageBox::warning(nullptr,"错误",tmp);
        return 0;
    }

    if (!ifCityExist(ec)) {
        tmp="系统中未存在"+QString::fromStdString(ec)+"这座城市，请先添加这座城市!";
        QMessageBox::warning(nullptr,"错误",tmp);
        return 0;
    }
    return  1;
}


// 手动添加城市
void ALGraph::addCity(const string& city_name) {

    if (ifCityExist(city_name)) {
        cout << "该城市已经存在，无需重复添加！" << endl;
        return;
    }
    vector<LineNode> tmp = {};
    m.insert({ city_name, tmp });
}


// 从文件中读取以添加城市
void ALGraph::addCityFromFile(const char FILENAME[MAXFILESIZE]) {


    cout << "不会说中文？？" << endl;
    cout << "开始从" << FILENAME << "中读入并添加城市！" << endl;

    ifstream file(FILENAME);  // 打开失败返回NULL
    if (!file) {
        cout << "打开文件失败！" << endl;
        return;
    }

    // 读取城市名
    string line;
    while (getline(file, line)) {
        istringstream istr(line);  // 利用 istringstream 类直接将 string 输入到 name
        string name;
        istr >> name;
        addCity(name);
    }
    cout << "城市导入完毕，当前系统中有" << m.size() << "个城市！" << endl;
    file.close();  // 读取后关闭文件
}//addCityFromFile



//手动添加线路
void ALGraph::addLine() {
    string vehicle;
    string line_number;
    Time start_time, end_time;
    string start_city_name;
    string end_city_name;
    //信息输入
    float spend_money;
    // 火车或飞机的班次

    cin >> line_number;
    cin >> start_city_name;
    cin >> end_city_name;
    cin >> spend_money;

    if (!check_sc_and_ec(start_city_name, end_city_name)) return;


    if (start_time > end_time) {
        cout << "出发时间大于到达时间，输入错误，请重新输入！" << endl;
        return;
    }


    auto it = m.find(start_city_name);
    if (it != m.end() || mp.count(line_number)) {
        (*it).second.push_back(LineNode(vehicle, line_number, start_city_name, end_city_name, start_time, end_time, spend_money));
        mp.insert({ line_number,LineNode(vehicle, line_number, start_city_name, end_city_name, start_time, end_time, spend_money) });
        cout << "添加路线成功！" << endl;
    }
    else {
        cout << "班次已存在" << endl;
    }

}//addLine



//从文件中读取以添加线路
void ALGraph::addLineFromFile(const char FILENAME[MAXFILESIZE]) {
    cout << "从" << FILENAME << "中读取并导入线路！" << endl;
    ifstream file(FILENAME);
    if (!file) {
        cout << "打开文件" << FILENAME << "失败！" << endl;;
        ; return;
    }
    string catalogue; //存储第一行的目录
    getline(file, catalogue);

    //从第二行开始读取真正需要存储的信息
    string line;
    while (getline(file, line)) {
        istringstream istr(line);
        string vehicle;
        string line_number;
        string start_city_name;
        string end_city_name;
        Time start_time, end_time;
        float spend_money;


        istr >> vehicle >> line_number >> start_city_name >> end_city_name
            >> start_time.month >> start_time.day >> start_time.hour >> start_time.minute
            >> end_time.month >> end_time.day >> end_time.hour >> end_time.minute >> spend_money;
        auto it = m.find(start_city_name);
        if (it != m.end()) {
            (*it).second.push_back(LineNode(vehicle, line_number, start_city_name, end_city_name, start_time, end_time, spend_money));
            mp.insert({ line_number,LineNode(vehicle, line_number, start_city_name, end_city_name, start_time, end_time,spend_money) });
        }
    }
    file.close(); //打开存储线路的文件完毕，关闭file
}//addLineFromFile



// 删除城市，并删除以该城市为起点与终点的航班和列车
void ALGraph::delCity(const string& city_name) {

    if (!ifCityExist(city_name)) {
        cout << city_name << "不存在！请重新输入正确的城市名或者新建该城市！" << endl;
        return;
    }

    cout << "正在删除" << city_name << "城市及其相关线路！" << endl;

    // 删除以该城市为起点的线路数据
    auto key = city_name;
    auto _it = m.find(key);
    if (_it != m.end()) {
        m.erase(key);
    }

    cout << "已删除" << city_name << "城市及其相关线路！" << endl;

}//delCity


//删除边
void ALGraph::delLine(const string& line_number) {

    if (!mp.count(line_number)) {
        cout << "不存在该班次， 请输入正确的班次" << endl;
        return;
    }

    //首先删除城市表中的
    auto key = mp[line_number].start_city_name;
    for (auto _it = m[key].begin(); _it != m[key].end(); _it++) {
        if (_it->line_number == line_number) {
            m[key].erase(_it);
            break;
        }
    }

    //再删除班次表中的
    auto _it = mp.find(line_number);
    mp.erase(_it);
}

//输出所有城市
void ALGraph::showAllCity() {
    if (m.size() == 0) {
        cout << "没有城市" << endl;
    }
    else {
        for (auto i : m) {
            cout << i.first << " ";
        }
    }
}//showAllCity

//显示所有班次
void ALGraph::showAllLine() {

    if (mp.size() == 0) {
        cout << "系统中没有任何线路的信息！" << endl;
        return;
    }
    else {
        cout << "系统当前一共有 " << mp.size() << " 条线路的信息！" << endl;
    }
    auto it = m.cbegin();
    while (it != m.cend()) {
        for (auto beg = (*it).second.cbegin(); beg != (*it).second.cend(); ++beg) {
            cout << (*beg).line_number;
        }
        ++it;
    }
}  // showAllLine


// 输出从起点城市到终点城市，中转次数最少的路径
    void ALGraph::printLeastTransferPath(QTableWidget *parent, const std::string& sc, const std::string& ec, const int st_time) {

    if (!check_sc_and_ec(sc, ec)){QMessageBox::critical(parent,"错误","抱歉,不存在对应路线") ;return;}

    map<string, int> dis; //计入中转次数
    map<string, string> pre; // 城市 -> 班次
    vector<string> result;  // 存储最终要打印的路径的班次

    struct reach_node {
        int r_time;  //到达时间
        int cost;  //中转次数
        string line_num; //编号
        bool operator < (const reach_node& x) const {
            if (r_time == x.r_time) {
                return cost < x.cost;
            }
            return r_time < x.r_time;
        }
    };

    std::priority_queue<reach_node, vector<reach_node>> pq;

    auto m_iter = m.cbegin();
    while (m_iter != m.cend()) {
        dis.insert({ (*m_iter).first, INT_MAX });
        ++m_iter;
    }

    // 初始化 distanced 中起点城市的信息
    auto _dist_iter = dis.find(sc);
    if (_dist_iter != dis.end()) {
        (*_dist_iter).second = 0; //起点站费用为零
    }


    for (auto lnd : mp) {
        if (lnd.second.start_time.getTotalMinute() > st_time) {
            pq.push({ lnd.second.start_time.getTotalMinute(),0,lnd.first });
        }
    }

    while (!pq.empty()) {
        int now_time = pq.top().r_time;
        int now_cost = pq.top().cost;
        string line_num = pq.top().line_num;
        pq.pop();

        string now_city = mp[line_num].start_city_name, nxt_city = mp[line_num].end_city_name;

        if (now_time == mp[line_num].start_time.getTotalMinute()) {
            pq.push({ mp[line_num].end_time.getTotalMinute(),dis[now_city] + 1, line_num });//保存到达时间的价钱
        }
        else {
            pre[nxt_city] = now_city;

            if (nxt_city == ec && now_cost < dis[nxt_city]) {
                result = { line_num };
                while (now_city != sc) {
                    result.push_back(pre[now_city]);
                    now_city = mp[pre[now_city]].start_city_name;
                }
            }

        }
    }

    if (dis[ec] == INF) {
        QMessageBox::critical(parent,"错误","抱歉,并未找到对应的路线");
    }
    else {
        std::reverse(result.begin(), result.end());
        //for (auto lnd : result) {
        //    cout << mp[lnd].line_number << " " << endl;
        //}

        //每次加载数据前清空表格数据
        if(parent->rowCount()>0){
            for(int rn=parent->rowCount();rn>=parent->rowCount();--rn){
                parent->removeRow(rn);
            }
        }

        //打印数据
        parent->setRowCount(result.size());
        int ri=0;
        //vector<LineNode>::iterator iter= result.begin();
        for(auto lnd:result){
            QString st=QString::number(mp[lnd].start_time.month)+'/'+QString::number(mp[lnd].start_time.day)+'/'+QString::number(mp[lnd].start_time.hour)+'/'+QString::number(mp[lnd].start_time.minute);
            QString et=QString::number(mp[lnd].end_time.month)+'/'+QString::number(mp[lnd].end_time.day)+'/'+QString::number(mp[lnd].end_time.hour)+'/'+QString::number(mp[lnd].end_time.minute);

            parent->setItem(ri,0,new QTableWidgetItem(QString::fromStdString(mp[lnd].line_number)));
            parent->setItem(ri,1,new QTableWidgetItem(QString::fromStdString(mp[lnd].start_city_name)));
            parent->setItem(ri,2,new QTableWidgetItem(QString::fromStdString(mp[lnd].end_city_name)));
            parent->setItem(ri,3,new QTableWidgetItem(st));
            parent->setItem(ri,4,new QTableWidgetItem(et));
            parent->setItem(ri,5,new QTableWidgetItem(mp[lnd].spend_money));
            ri++;
        }
    }
}

// 输出从起点城市到终点城市，总时间最短的线路
void ALGraph::printLeastTimePath(QTableWidget *parent, const std::string& sc, const std::string& ec, const int st_time) {


    if (!check_sc_and_ec(sc, ec)){QMessageBox::critical(parent,"错误","抱歉,不存在对应路线") ;return;}

    set<string> visited;
    map<string, int> reach_time;
    map<string, string> pre; // 城市 -> 班次
    vector<LineNode> result;  // 存储最终要打印的路径

    struct reach_node {
        string city;
        int r_time;  //到达时间
        bool operator < (const reach_node& x) const {
            return r_time < x.r_time;
        }
    };

    std::priority_queue<reach_node, vector<reach_node>> q; //采用堆优化dij


    auto m_iter = m.cbegin();
    while (m_iter != m.cend()) {
        reach_time.insert({ (*m_iter).first, INT_MAX });
        ++m_iter;
    }


    // 初始化 distanced 中起点城市的信息
    auto _dist_iter = reach_time.find(sc);
    if (_dist_iter != reach_time.end()) {
        (*_dist_iter).second = st_time;
    }

    q.push({ sc,st_time });

    while (!q.empty()) {
        reach_node x = q.top();
        q.pop();
        if (visited.count(x.city)) continue;
        visited.insert(x.city);

        int current_time = reach_time[x.city];

        vector<LineNode> adj = m[x.city];

        for (auto r = adj.cbegin(); r <= adj.cend(); r++) {

            if (current_time < r->start_time.getTotalMinute() && reach_time[r->end_city_name] < r->end_time.getTotalMinute()) {
                reach_time[r->end_city_name] = r->end_time.getTotalMinute();

                q.push({ r->end_city_name,reach_time[r->end_city_name] });
                pre[r->end_city_name] = { r->line_number };
            }

        }
    }

    if (reach_time[ec] == INT_MAX) {
        QMessageBox::critical(parent,"错误","抱歉,并未找到对应的路线");
    }
    else {
        string now_city = ec;
        while (now_city != sc) {
            result.push_back(mp[pre[now_city]]);
            now_city = mp[pre[now_city]].start_city_name;
        }
        std::reverse(result.begin(), result.end());

        //每次加载数据前清空表格数据
        if(parent->rowCount()>0){
            for(int rn=parent->rowCount();rn>=parent->rowCount();--rn){
                parent->removeRow(rn);
            }
        }

        //打印数据
        parent->setRowCount(result.size());
        int ri=0;
        //for(auto lnd:result){
        //    QString st=QString::number(mp[lnd].start_time.month)+'/'+QString::number(mp[lnd].start_time.day)+'/'+QString::number(mp[lnd].start_time.hour)+'/'+QString::number(mp[lnd].start_time.minute);
        //    QString et=QString::number(mp[lnd].end_time.month)+'/'+QString::number(mp[lnd].end_time.day)+'/'+QString::number(mp[lnd].end_time.hour)+'/'+QString::number(mp[lnd].end_time.minute);

        //    parent->setItem(ri,0,new QTableWidgetItem(QString::fromStdString(mp[lnd].line_number)));
        //    parent->setItem(ri,1,new QTableWidgetItem(QString::fromStdString(mp[lnd].start_city_name)));
        //    parent->setItem(ri,2,new QTableWidgetItem(QString::fromStdString(mp[lnd].end_city_name)));
        //    parent->setItem(ri,3,new QTableWidgetItem(st));
        //    parent->setItem(ri,4,new QTableWidgetItem(et));
        //    parent->setItem(ri,5,new QTableWidgetItem(mp[lnd].spend_money));
        //    ri++;
        //}

    }

}

// 输出某个城市到其他各城市的花费最少的路线
    void ALGraph::printLeastMoneyPath(QTableWidget *parent,  const std::string& sc, const std::string& ec, const int st_time) {

    if (!check_sc_and_ec(sc, ec)) {QMessageBox::critical(parent,"错误","抱歉，未查询查询到对应路线！") ;return;}
           //MinCostFail=true;
        map<string, double> dis; //计入费用
        map<string, string> pre; // 城市 -> 班次
        vector<string> result;  // 存储最终要打印的路径的班次

        struct reach_node {
            int r_time;  //到达时间
            double cost;
            string line_num; //编号
            bool operator < (const reach_node& x) const {
                if (r_time == x.r_time) {
                    return cost < x.cost;
                }
                return r_time < x.r_time;
            }
        };

        std::priority_queue<reach_node, vector<reach_node>> pq;

        auto m_iter = m.cbegin();
        while (m_iter != m.cend()) {
            dis.insert({ (*m_iter).first, INT_MAX });
            ++m_iter;
        }

        // 初始化 distanced 中起点城市的信息
        auto _dist_iter = dis.find(sc);
        if (_dist_iter != dis.end()) {
            (*_dist_iter).second = 0; //起点站费用为零
        }


        for (auto lnd : mp) {
            if (lnd.second.start_time.getTotalMinute() > st_time) {
                pq.push({ lnd.second.start_time.getTotalMinute(),0,lnd.first });
            }
        }

        while (!pq.empty()) {
            int now_time = pq.top().r_time;
            int now_cost = pq.top().cost;
            string line_num = pq.top().line_num;
            pq.pop();

            string now_city = mp[line_num].start_city_name, nxt_city = mp[line_num].end_city_name;

            if (now_time == mp[line_num].start_time.getTotalMinute()) {
                pq.push({ mp[line_num].end_time.getTotalMinute(),dis[now_city] + mp[line_num].spend_money, line_num });//保存到达时间的价钱
            }
            else {
                pre[nxt_city] = now_city;

                if (nxt_city == ec && now_cost < dis[nxt_city]) {
                    result = { line_num };
                    while (now_city != sc) {
                        result.push_back(pre[now_city]);
                        now_city = mp[pre[now_city]].start_city_name;
                    }
                }

            }
        }

        if (dis[ec] == INF) {
            //FindMinCostFail=true;
            //cout<<"没路"<<endl;
            QMessageBox::critical(parent,"错误","抱歉，未查询对应路线！");
        }
        else {
            std::reverse(result.begin(), result.end());
                //for (auto lnd : result) {
                //cout << mp[lnd].line_number << " " << endl;
            //}
            //每次加载数据前清空表格数据
            if(parent->rowCount()>0){
                for(int rn=parent->rowCount();rn>=parent->rowCount();--rn){
                    parent->removeRow(rn);
                }
            }

            //打印数据
            parent->setRowCount(result.size());
            int ri=0;
            //vector<LineNode>::iterator iter= result.begin();
            for(auto lnd:result){
                QString st=QString::number(mp[lnd].start_time.month)+'/'+QString::number(mp[lnd].start_time.day)+'/'+QString::number(mp[lnd].start_time.hour)+'/'+QString::number(mp[lnd].start_time.minute);
                QString et=QString::number(mp[lnd].end_time.month)+'/'+QString::number(mp[lnd].end_time.day)+'/'+QString::number(mp[lnd].end_time.hour)+'/'+QString::number(mp[lnd].end_time.minute);

                parent->setItem(ri,0,new QTableWidgetItem(QString::fromStdString(mp[lnd].line_number)));
                parent->setItem(ri,1,new QTableWidgetItem(QString::fromStdString(mp[lnd].start_city_name)));
                parent->setItem(ri,2,new QTableWidgetItem(QString::fromStdString(mp[lnd].end_city_name)));
                parent->setItem(ri,3,new QTableWidgetItem(st));
                parent->setItem(ri,4,new QTableWidgetItem(et));
                parent->setItem(ri,5,new QTableWidgetItem(mp[lnd].spend_money));
                ri++;
            }


        }



}
