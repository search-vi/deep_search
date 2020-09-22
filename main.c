#include<iostream>
#include"queue"
#include"string"
#include<list>
 
using namespace std;
 
const string GOAL = "803214765";
 
class Situation{
private:
    
public:
    string father;
    string code;//当前状态
    int deep;
    Situation up();
    Situation down();
    Situation left();
    Situation right();
    bool isGoal();
    bool isInOpen(deque<Situation> &open);
    bool isInClosed(deque<Situation> &closed);
    void show() const;
    void show(string) const;
    void show_deque(deque<Situation> &) const;
    deque<Situation> showWay(deque<Situation> &closed);
    void showAnswer(deque<Situation> &closed);//显示解答
    Situation() :father(""), code(""), deep(-1){};
};

Situation Situation::up(){
    string::size_type loc = code.find('0');//0的位置,从0开始计数
    Situation son;
    son.code = code;
    son.deep = deep + 1;
    if (loc>=3){
        char temp = son.code[loc];//即0
        son.code[loc] = son.code[loc - 3];
        son.code[loc-3] = temp;
    }
    else{
        son.code = "";
    }
    return son;
}
 
Situation Situation::down(){
    string::size_type loc = code.find('0');//0的位置,从0开始计数
    Situation son;
    son.code = code;
    son.deep = deep + 1;
    if (loc<=5){
        char temp = son.code[loc];//即0
        son.code[loc] = son.code[loc + 3];
        son.code[loc + 3] = temp;
    }
    else{
        son.code = "";
    }
    return son;
}
 
Situation Situation::left(){
    string::size_type loc = code.find('0');//0的位置,从0开始计数
    Situation son;
    son.code = code;
    son.deep = deep + 1;
    if (loc!=0&&loc!=3&&loc!=6){
        char temp = son.code[loc];//即0
        son.code[loc] = son.code[loc - 1];
        son.code[loc - 1] = temp;
    }
    else{
        son.code = "";
    }
    return son;
}
 
Situation Situation::right(){
    string::size_type loc = code.find('0');//0的位置,从0开始计数
    Situation son;
    son.code = code;
    son.deep = deep + 1;
    if (loc!=2&&loc!=5&&loc!=8){
        char temp = son.code[loc];//即0
        son.code[loc] = son.code[loc + 1];
        son.code[loc + 1] = temp;
    }
    else{
        son.code = "";
    }
    return son;
}
 
bool Situation::isGoal(){
    return code == GOAL;
}
 
bool Situation::isInOpen(deque<Situation> &open){
    /*deque<Situation>::iterator it = open.begin();
    while (it != open.end()){
        if (code == (*it).code){
            return true;
        }
        it++;
    }*/
    for (int i = 0; i < open.size();i++){
        if (code==open.at(i).code){
            return true;
        }
    }
    return false;
}
 
bool Situation::isInClosed(deque<Situation> &closed){
    /*deque<Situation>::iterator it = closed.begin();
    while (it!=closed.end()){
        if (code == (*it).code){
            return true;
        }
        it++;
    }*/
    for (int i = 0; i < closed.size(); i++){
        if (code == closed.at(i).code){
            return true;
        }
    }
    return false;
}
 
void Situation::show() const{
    if (!code.empty()){
        cout << code[0] << code[1] << code[2] << endl
            << code[3] << code[4] << code[5] << endl
            << code[6] << code[7] << code[8] << endl << endl;
    }
    else{
        cout << "空的" << endl;
    }
}
 
void Situation::show(string code) const{
    if (!code.empty()){
        cout << code[0] << code[1] << code[2] << endl
            << code[3] << code[4] << code[5] << endl
            << code[6] << code[7] << code[8] << endl << endl;
    }
    else{
        cout << "空的" << endl;
    }
}
 
void Situation::show_deque(deque<Situation> &m_deque) const{
    /*deque<Situation>::iterator it = m_deque.begin();
    while (it!=m_deque.end())
    {
        (*it).show();
        it++;
    }*/
    for (int i = 0; i < m_deque.size();i++){
        m_deque.at(i).show();
    }
}
 
//路径
deque<Situation> Situation::showWay(deque<Situation> &closed){
    //cout << closed.size() << endl;
    deque<Situation> dequeList;
    Situation temp = closed.back();
    dequeList.push_back(temp);
 
    //closed表从后往前，根据father值找到路径
    for (int i = closed.size()-1; i >= 0;i--){
        if (temp.father==closed.at(i).code){
            dequeList.push_back(closed.at(i));
            temp = closed.at(i);
        }
    }
    //cout << dequeList.size() << endl;
    return dequeList;
}
 
void Situation::showAnswer(deque<Situation> &closed){
    deque<Situation> way(showWay(closed));
    cout << "共需要" << way.size() << "步" << endl;
    for (int i = way.size() - 1; i >= 0; i--)
    {
        way.at(i).show();
    }
    //输出目标
    show(GOAL);
}

void loop(deque<Situation> &open, deque<Situation> &closed, int range);
 
int main(){
    string original = "283164705";
    Situation first;
    deque<Situation> open, closed;//open存放未扩展节点，closed存放已扩展节点
    int range = 10;//深度界限
 
    first.code = original;
    first.deep = 0;
    open.push_back(first);
    loop(open,closed,range);
    return 0;
}
 
void loop(deque<Situation> &open, deque<Situation> &closed,int range){
    Situation a;
    int i = 0;
    while (!open.empty()){
        cout << i++ << endl;
        if (open.front().code == GOAL){
            cout << "成功：" << endl;
            a.showAnswer(closed);
            return;
        }
        if (open.empty()){
            cout << "失败" << endl;
            return;
        }
        closed.push_back(open.front());
        open.pop_front();
        //节点n的深度是否等于深度界限
        if (closed.back().deep == range){
            //loop(open,closed,range);不能用递归
            continue; 
        }
        else{
            //扩展节点n,把其后裔节点放入OPEN表的末端
            Situation son1 = closed.back().up();
            Situation son2 = closed.back().down();
            Situation son3 = closed.back().left();
            Situation son4 = closed.back().right();
            /*
            广度优先搜索和深度优先搜索的唯一区别就是子节点放到open表的位置：
            （1）广度优先搜索放到open表的后面
            （2）深度优先搜索放到open表的前面
            */
            if (!son1.code.empty()){
                if (!son1.isInOpen(open)&&!son1.isInClosed(closed)){
                    son1.father = closed.back().code;
                    open.push_front(son1);
                }
            }
            if (!son2.code.empty()){
                if (!son2.isInOpen(open) && !son2.isInClosed(closed)){
                    son2.father = closed.back().code;
                    open.push_front(son2);
                }
            }
            if (!son3.code.empty()){
                if (!son3.isInOpen(open) && !son3.isInClosed(closed)){
                    son3.father = closed.back().code;
                    open.push_front(son3);
                }
            }
             if (!son4.code.empty()){
                if (!son4.isInOpen(open) && !son4.isInClosed(closed)){
                    son4.father = closed.back().code;
                    open.push_front(son4);
                }
                
            }
            //是否有任何后继节点为目标节点
            if (son1.isGoal()){
                cout << "后继节点中有目标节点：" << endl;
                son1.showAnswer(closed);
                break;
            }
            if (son2.isGoal()){
                cout << "后继节点中有目标节点：" << endl;
                son2.showAnswer(closed);
                break;
            }
            if (son3.isGoal()){
                cout << "后继节点中有目标节点：" << endl;
                son3.showAnswer(closed);
                break;
            }
            if (son4.isGoal()){
                cout << "后继节点中有目标节点：" << endl;
                son4.showAnswer(closed);
                break;
            }
        }
    }
}
