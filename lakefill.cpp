//
//  mexmain.cpp
//  fasts
//
//  Created by Gregor on 6/8/16.
//  Copyright © 2016 su. All rights reserved.
//
#include <vector>


#include<mex.h>
#include<matrix.h>
#include "lakefillclass.cpp"

void mexFunction(
        int          nlhs,
        mxArray      *plhs[],
        int          nrhs,
        const mxArray *prhs[]
        )
{
    
    double      ddx, ddy,nny,nnx;
    double dx,dy;
    double U;
    
    std::vector<double> freed;
    std::vector<int> BC;
    std::vector<double> array,eros;
    int i=1;
    
    /* Check for proper number of arguments */

    
    
    
    double *inarray = mxGetPr(prhs[0]);
    double *inBC = mxGetPr(prhs[1]);
    int ny = mxGetScalar(prhs[2]);
    int nx = mxGetScalar(prhs[3]);
    int nn=ny*nx;

    array.resize(ny*nx+1);
    for (i = 1;i<=nn;i++){
        array[i] = inarray[i-1];
        
    }
    BC.resize(ny*nx+1);
    
    for (i=1;i<BC.size();i++)
    {
        BC[i]=inBC[i-1];
    }

    
    lakefill grid;
    grid.initializevariables(1,1, nx,ny,BC);
    grid.grid=array;
    grid.landsurf=grid.grid;
    if (BC.size()>0)
    {
   
       grid.lakefill2();
    }
    plhs[0] = mxCreateNumericMatrix(1, nn,mxDOUBLE_CLASS, mxREAL);
    double* data = (double *) mxGetData(plhs[0]);
    
    
    for (i =0;i<nn;i++)
    {
        
        data[i] = grid.grid[i+1];
    }
    
};
