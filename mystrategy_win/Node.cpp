#include <cmath>
#include "Node.h"

void Node::change(int _x,int _y,int _who,int _self,int _father,int _next)
{
    x=_x;
    y=_y;
    who=_who;
    profit=0;
    visitednum=0;
    self=_self;
    father=_father;
    childrennum=0;
    next=_next;
}

int Node::expand(Node* _pool,int _num,int* _top,int _noX,int _noY,int _N)
{
	if(next==_N)
		return -1;
    int _x=--_top[next];
    if(next==_noY && _top[next]==_noX)
	{
		if(_noX>0)
			_x=--_top[next];
		else
		{
			for(++next;next<_N;++next)
			{
				if(_top[next]>0)
					break;
			}
			if(next==_N)
				return -1;//ÎÞ·¨À©Õ¹
			else
				_x=--_top[next];
		}
	}
    int _next;
    for(_next=0;_next<_N;++_next)
    {
        if(_top[_next]>0)
            break;
    }
    _pool[_num].change(_x,next,3-who,_num,self,_next);
    children[childrennum++]=_num;
    for(++next;next<_N;++next)
    {
        if(_top[next]>0)
            break;
    }
    return _num;
}

int Node::bestchild(Node* _pool,double _c)
{
    int best=-1;
    double max=-1e10;
    double tmp;
    int index;
    for(int i=0;i<childrennum;++i)
    {
        index=children[i];
        tmp=double(_pool[index].profit)/_pool[index].visitednum + 
			_c*sqrt(2*log(double(visitednum))/_pool[index].visitednum);
        if(tmp>max)
        {
            best=index;
            max=tmp;
        }
    }
    return best;
}
