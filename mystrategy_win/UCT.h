#ifndef UCT_H_
#define UCT_H_

#include "Node.h"

class uct
{
private:
    Node* pool;//内存池
    int num;//下一个可用节点
    int** board;//棋局
    const int* top;//顶点
    int noX;
    int noY;//不可落子点
    int** boardtmp;
    int* toptmp;
    int M;
    int N;//棋盘规模
    double c;
public:
    uct(int** _board,const int* _top,int _M,int _N,int _noX,int _noY,double _c=1.0);
    ~uct();
    void uctsearch(int* _x,int* _y);
    int treepolicy();
    int defultpolicy(int bg);
    void backup(int bg,int _profit);
};

#endif
