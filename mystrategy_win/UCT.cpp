#include <cstdlib>
#include <ctime>
#include "UCT.h"
#include "Judge.h"

#define memorylimitation 1500000
#define timelimitation 2500

uct::uct(int** _board,const int* _top,int _M,int _N,int _noX,int _noY,double _c):
board(_board),top(_top),M(_M),N(_N),noX(_noX),noY(_noY),c(_c)
{
    pool=new Node[memorylimitation+10];
    num=1;
    boardtmp=new int*[_M];
    for(int i=0;i<_M;++i)
    	boardtmp[i]=new int[_N];
    toptmp=new int[_N];
    int _next;
    for(_next=0;_next<_N;++_next)
    {
        if(_top[_next]>0)
            break;
    }
    pool[0].change(-1,-1,1,0,-1,_next);
    srand((unsigned)time(NULL));
}

uct::~uct()
{
    delete[] pool;
    delete[] toptmp;
	for(int i=0;i<M;i++)
		delete[] boardtmp[i];
	delete[] boardtmp;
}

void uct::uctsearch(int* _x,int* _y)
{
    int starttime=clock();
    int ch;//扩展节点
    int p;//收益
    while(clock()-starttime<timelimitation && num<memorylimitation)
    {
        for(int j=0;j<N;++j)
        {
            toptmp[j]=top[j];
            for(int i=0;i<M;++i)
                boardtmp[i][j]=board[i][j];
        }
        ch=treepolicy();
        p=defultpolicy(ch);
        backup(ch,p);
    }
    int best=pool[0].bestchild(pool,0.0);
    *_x=pool[best].x;
    *_y=pool[best].y;
}

int uct::treepolicy()
{
    int hot=0;
    int yy,xx,fa;
    while(1)
    {
        if(pool[hot].next<N)
        {
            int re=pool[hot].expand(pool,num,toptmp,noX,noY,N);
			if(re!=-1)
			{
				++num;
				boardtmp[pool[re].x][pool[re].y]=pool[re].who;
				return re;
			}
        }
        else
        {
			fa=hot;
            hot=pool[hot].bestchild(pool,c);
            if(hot==-1)
                return fa;
			xx=pool[hot].x;
            yy=pool[hot].y;
            boardtmp[xx][yy]=pool[hot].who;
            toptmp[yy]=xx;
        }
    }
}

int uct::defultpolicy(int bg)//从选中节点开始
{
    int yy;
    int ww=pool[bg].who;
	if(ww==2 && machineWin(pool[bg].x,pool[bg].y,M,N,boardtmp))
	{
		pool[bg].next=N;
		return 1; 
	}
	if(ww==1 && userWin(pool[bg].x,pool[bg].y,M,N,boardtmp))
	{
		pool[bg].next=N;
		return 1;
	}
	if(isTie(N,toptmp))
		return 0;
    while(1)
    {
		yy=rand()%N;
        while(toptmp[yy]==0)
            yy=rand()%N;
        --toptmp[yy];
        if(yy==noY && toptmp[yy]==noX)
		{
			if(noX>0)
				--toptmp[yy];
			else if(isTie(N,toptmp))
				return 0;
			else
				continue;				
		}
		ww=3-ww;
		boardtmp[toptmp[yy]][yy]=ww;
        if(ww==2)
        {
            if(machineWin(toptmp[yy],yy,M,N,boardtmp))
            {
                if(pool[bg].who==2)
					return 1;
                else
					return -1;
            }
        }
        else
        {
            if(userWin(toptmp[yy],yy,M,N,boardtmp))
            {
                if(pool[bg].who==2)
					return -1;
                else
					return 1;
            }
        }
        if(isTie(N,toptmp))
			return 0; 
    }
}

void uct::backup(int bg,int _profit)
{
    int hot=bg;
    while(hot!=-1)
    {
        ++pool[hot].visitednum;
        pool[hot].profit+=_profit;
        _profit=-_profit;
        hot=pool[hot].father;
    }
}