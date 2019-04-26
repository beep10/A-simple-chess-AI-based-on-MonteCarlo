#ifndef NODE_H_
#define	NODE_H_

class Node
{
public:
    int x;
    int y;//相较于父节点改变的节点
    int who;//执（落）子一方，1为对方，2为己方
    int profit;//收益
    int visitednum;//被访问次数
    int self;//自身地址
    int father;//父节点
    int childrennum;//子节点数量
    int children[12];//子节点
    int next;//下一个可扩展的子节点所在的列
public:
    void change(int _x,int _y,int _who,int _self,int _father,int _next);
    int expand(Node* _pool,int _num,int* _top,int _noX,int _noY,int _N);
    int bestchild(Node* _pool,double _c);
};

#endif