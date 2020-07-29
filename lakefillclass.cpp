#ifndef std
#include <iostream>
#endif
#ifndef vector_h
#include <vector>
#endif
#include<queue>
#include<cmath>
#include <stdio.h>
#include <fstream>

#ifndef fastsclass_hpp
#define fastsclass_hpp
//#include "omp.h"
#include<set>


class lakefill{
public:
    std::vector<int> usedstack;
    void setgridloc(std::string &loc);
    std::vector<int> BC;
    std::vector<double> landsurf;
    void landsed();
    void readgrid();
    std::string gridloc;
    void initializevariables(int,int,int,int,std::vector<int>&);
    int failcount;
    int nx;
    int ny;
    class cmpr
    {
        std::vector<double> *dem;
    public:
        cmpr(std::vector<double> *demi)
        {dem=demi;}
        bool operator() (const int &i,const int &j) const
        {
            if ((*dem)[i]>(*dem)[j])
            {
                return true; 
            }
            else
            {
                return false;
            }
        }
    };
    void lakefill2();
    double dx;
    std::vector<double> grid;
    double dy;
    std::vector<double> dx2;
    int nstep;
    int nn;
    double dt;
    int firstcall;
    double tt;
    std::vector<int> BCX;
    int tstep;
    
private:
    std::vector<bool> usedr;
    int nrecur;
    int nseds;
    std::vector<int> next;
    std::vector<int> idx;
    int  stckcount;
    double mintot;
    int mintotloc;
    std::vector<int> runningstck;
    double minstck;
    double highgrd;

    double area;
    double sedextra;
    int maxo;
    void recursivesed(int);
    int usestacklocal;
    int xl;
    int yl;
    
    
    
};


#endif



void lakefill::initializevariables(int ddx,int ddy,int nnx,int nny,std::vector<int> &BCi)
{
    dx = ddx;
    dy = ddy;
    ny = nny;
    nx = nnx;
    nn = nx*ny;
  
    BC = BCi;
    BCX.resize(nn+1);
    std::cout<<BC.size()<<std::endl;
    for (int i=1;i<=BC.size();i++)
    {
        //std::cout<<BC[i]<<std::endl;
        if (BC[i]<=0||BC[i]>=grid.size())
        {
            break;
        }
    }

    idx.resize(8);
    idx[0]=1;idx[1]=-1;idx[2]=ny;idx[3]=-ny;
    idx[4]=ny+1;
    idx[5]=ny-1;idx[6]=-ny+1;idx[7]=-ny-1;
    
    std::fill(grid.begin(),grid.end(),0.0);
}

void lakefill::lakefill2()
{ 
    double pittop;
    int c=0;
    int p = 0;
    std::vector<bool> closed;
    std::vector<int> pit;
    closed.resize(nn+1);
    //std::vector<int> pq;
    //pq.resize(nn+1);
    //std:fill(pq.begin(),pq.end(),-9999);
    pit.resize(nn+1);
   typedef std::priority_queue<int,std::vector<int>,cmpr> mpr;
   mpr open ((cmpr(&grid)));
   //priorityq open(grid);

   if (1)
   {
   for (int i=1;i<BC.size();i++)
    {
           if (BC[i]<=0||BC[i]>=grid.size())
    {
        break;
    }
       open.push(BC[i]);
        closed[BC[i]]=true;
        c++;

   }
   std::cout<<"here2"<<std::endl;

   }
   for (int i=1;i<=ny;i++)
   {
       if (closed[i]==false)
       {
                  closed[i]=true;

           open.push(i);
           
           c++;
       }
       
   }

   for (int i=nn-ny+1;i<=nn;i++)
   {
       if (closed[i]==false)
       {
       closed[i]=true;

           open.push(i);
           
           c++;
       }
   }
   for (int i=ny;i<=nn;i+=ny)
   {
       if (closed[i]==false)
       {
       closed[i]=true;

           open.push(i);
           
           c++;
       }
   }
   for (int i=ny+1;i<=nn;i+=ny)
   {
       if (closed[i]==false)
       {
       closed[i]=true;

           open.push(i);
           
           c++;
       }
   }
    int s;
    int si=1;
    int ij;
    int ii;
    int jj;
    int ci=1;
    pittop=-9999;
    while (c>0||p>0)
    {
        if (p>0&&c>0&&pit[p-1]==-9999)//pq[c-1]==pit[p-1])
        {
            s=open.top();
            open.pop();
            c--;
            pittop=-9999;
        }
        else if (p>0)
        {
            
            s=pit[p-1];
            pit[p-1]=-9999;
            p--;
            if (pittop==-9999)
            {
                pittop=grid[s];
            }
        }
        else
        {
            s=open.top();
            open.pop();
            c--;
            pittop=-9999;
        }
        
                  //  #pragma omp parallel for

        for (int i=0;i<=7;i++)
        {
            
            ij = idx[i]+s;

            ii= (ij-1)%ny+1;
            jj = (int)((ij-1)/ny)+1;
            if ((ii>=1)&&(jj>=1)&&(ii<=ny)&&(jj<=nx)&&closed[ij]==false)//)
            {

                closed[ij]=true;
                
                if (grid[ij]<=grid[s])
                {
                    grid[ij]=grid[s]+1e-3;
                    
                    pit[p]=ij;
                    p++;
                    
                }
                
                else
                {
                    open.push(ij);
                    c++;
                }
                
            }
        }
    }
    

    
 }
 















