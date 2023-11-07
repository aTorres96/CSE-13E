//Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"

//User Libraries
#include"MatrixMath.h"

#define DIM2 2

void MatrixSubPrint(float mat[2][2]);
float MatrixDeterminant2x2(float mat[2][2]);
int MatrixSubEqual(float mat1[2][2], float mat2[2][2]);

void MatrixPrint(float mat[3][3])
{
    int i, j;
    for(i=0; i<DIM; i++)
    {
        printf("\n");
        for(j=0; j<DIM; j++)
            printf("%.2f ", mat[i][j]);
    }
    printf("\n");
}

void MatrixSubPrint(float mat[2][2])
{
    int i, j;
    for(i=0; i<DIM2; i++)
    {
        printf("\n");
        for(j=0; j<DIM2; j++)
            printf("%f ", mat[i][j]);
    }
    printf("\n");
}

int MatrixSubEqual(float mat1[2][2], float mat2[2][2])
{
    int i, j, equalsCounter, goal;
    equalsCounter = 0;
    goal = 4;
    for(i=0; i<DIM2; i++)
    {
        for(j=0; j<DIM2; j++)
        {
            if (mat1[i][j] == mat2[i][j])
                equalsCounter++;
        }
    }
        if (equalsCounter == goal)
             return 1; 
        else 
            return 0;
}

int MatrixEquals(float mat1[3][3], float mat2[3][3])
{
    int i, j, equalsCounter, goal;
    equalsCounter = 0;
    goal = 9;
    for(i=0; i<DIM; i++)
    {
        for(j=0; j<DIM; j++)
        {
            if (mat1[i][j] - mat2[i][j] <= FP_DELTA)
                equalsCounter++;
            else if(mat1[i][j] - mat2[i][j] <= -FP_DELTA)
                equalsCounter++;
        }
    }
        if (equalsCounter == goal)
             return 1; 
        else 
            return 0;
}

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    int i, j;
    for(i=0; i<DIM; i++)
    {
        for(j=0; j<DIM; j++)
            result[i][j] = (mat1[i][j] + mat2[i][j]);
    }
   return;
}

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3])
{    
    int i, j, k;
    int sum = 0;
    
    for(i=0; i<DIM; i++)
    {
        for(j=0; j<DIM; j++)
        {
            for(k=0; k<DIM; k++)
            {
                sum +=  (mat1[i][k] * mat2[k][j]);
            }
            result[i][j] = sum;
            sum = 0;
        }
    }
    return;
}

void MatrixScalarAdd(float x, float mat[3][3], float result[3][3])
{
    int i, j;
    for(i=0; i<DIM; i++)
    {
        for(j=0; j<DIM; j++)
            result[i][j] = (mat[i][j] + x);
    }
    return;
}

void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3])
{
    int i, j;
    for(i=0; i<DIM; i++)
    {
        for(j=0; j<DIM; j++)
            result[i][j] = (mat[i][j] * x);
    }
    return;
}

float MatrixTrace(float mat[3][3])
{
    int answer;
    answer = mat[0][0] + mat[1][1] + mat[2][2];
    return answer;
}

void MatrixTranspose(float mat[3][3], float result[3][3])
{
    int i, j;
    for(i=0; i<DIM; i++)
    {
        for(j=0; j<DIM; j++)
            result[i][j] = mat[j][i];
    }
    return;
}

void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2])
{
    int x, y;

    for(x=0; x<DIM; x++)
    {
        for(y=0; y<DIM; y++)
        {
            if (x < i && y < j)
                result[x][y] = mat[x][y];
            else if (x > i && y < j)
                result[x-1][y] = mat[x][y];
            else if (x < i && y > j)
                result[x][y-1] = mat[x][y];
            else if (x > i && y > j)
                result[x-1][y-1] = mat[x][y];
        }
    }

    return;
}

float MatrixDeterminant(float mat[3][3])
{
    int i, j, k;
    float a, b, c;
    float result;
    float lil_matrix[2][2]  = {{0,0},{0,0}};
    i = 0, j = 1, k = 2;
    
    MatrixSubmatrix(i, i, mat, lil_matrix);
    a = (mat[0][0] * MatrixDeterminant2x2(lil_matrix));
    MatrixSubmatrix(i, j, mat, lil_matrix);
    b = (mat[0][1] * MatrixDeterminant2x2(lil_matrix));
    MatrixSubmatrix(i, k, mat, lil_matrix);
    c = (mat[0][2] * MatrixDeterminant2x2(lil_matrix));
    result = (a - b + c);
    
    return result;
}

float MatrixDeterminant2x2(float mat[2][2])
{
    float result;
    
    result = (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
    
    return result;
}

void MatrixInverse(float mat[3][3], float result[3][3])
{
    int i, j;
    float determinant;
    determinant = MatrixDeterminant(mat);
    float lil_matrix[2][2] = {{0,0},{0,0}};
    float trans_matrix[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

    
    for(i=0;i<DIM;i++)
    {
        for(j=0;j<DIM;j++)
        {
        MatrixSubmatrix(i, j, mat, lil_matrix);
        if((i+j)%2 == 0)
            trans_matrix[i][j] = MatrixDeterminant2x2(lil_matrix);
        else
            trans_matrix[i][j] = (-1 * MatrixDeterminant2x2(lil_matrix));
        }
    }
    
    MatrixTranspose(trans_matrix, result);
    
    for(i=0;i<DIM;i++)
    {
        for(j=0;j<DIM;j++)
        {
            result[i][j] *= (1/determinant);
        }
    }
    
    
    return;
}
