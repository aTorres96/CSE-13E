// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"




// User libraries:
#include "MatrixMath.h"


// Module-level variables:
float a_matrix[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
float b_matrix[3][3] = {{9,8,7},{6,5,4},{3,2,1}};
float c_matrix[3][3] = {{2,2,2},{2,2,2},{2,2,2}};
float d_matrix[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
float det1_matrix[3][3] = {{2,-3,1},{2,0,-1},{1,4,5}};
float det2_matrix[3][3] = {{2,1,3},{4,-2,-1},{-5,2,6}};
float result_matrix[3][3] = {{},{},{}};
float negOne_matrix[3][3] = {{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}};
float ten_matrix[3][3] = {{10,10,10},{10,10,10},{10,10,10}};
float minOne_matrix[3][3] = {{0,1,2},{3,4,5},{6,7,8}};
float double_matrix[3][3] = {{2,4,6},{8,10,12},{14,16,18}};
float scaAdd_matrix[3][3] = {{2,3,4},{5,6,7},{8,9,10}};
float scaAddTwo_matrix[3][3] = {{3,4,5},{6,7,8},{9,10,11}};
float subAns1_matrix[2][2] = {{1,3},{7,9}};
float subAns2_matrix[2][2] = {{6,5},{3,2}};
float neg_matrix[3][3] = {{-1,-2,-3},{-4,-5,-6},{-7,-8,-9}};  
float transOne_matrix[3][3] = {{1,4,7},{2,5,8},{3,6,9}};
float transTwo_matrix[3][3] = {{9,6,3},{8,5,2},{7,4,1}};
float mulOne_matrix[3][3] = {{30,24,18},{84,69,54},{138,114,90}};
float mulNeg_matrix[3][3] ={{-6,-6,-6},{-15,-15,-15},{-24,-24,-24}};
float lil_matrix[2][2] = {{0,0},{0,0}};
float inverse_matrix[3][3] = {{3,0,2},{2,0,-2},{0,1,1}};
float inverse2_matrix[3][3] = {{1,0,1},{-4,1,-1},{6,-2,1}};
float invAns1_matrix[3][3] = {{0.2,0.2,0.0},{-0.2,0.3,1},{0.2,-0.3,0}};
float invAns2_matrix[3][3] = {{-1,-2,-1},{-2,-5,-3},{2,2,1}};

int main()
{
    
    BOARD_Init();
    
    int eqCount = 0;
    int mulCount = 0;
    int addCount = 0;
    int scaMulCount = 0;
    int detCount = 0;
    int detAns1 = 49;
    int detAns2 = -45;
    int scaAddCount = 0;
    int subCount = 0;
    int invCount = 0;
    int tranCount = 0;
    int traceCount = 0;
    int scaVar = 1;
    int scaVarTwo = 2;
    int scaNeg = -1;
    int subInt1 = 0;
    int subInt2 = 1;
    int subInt3 = 2;
    float traceAnsOne = 15;
    float traceAnsTwo = -15;
    double percentCorrect = 0;
    double numOfFunc = 20;
    double numPassed = 0;
    
    printf("Beginning atorre83's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);
    
    if(MatrixEquals(a_matrix, d_matrix) == TRUE)
    {
        eqCount++;
        numPassed++;
    }
    if(MatrixEquals(a_matrix, b_matrix) == FALSE)
    {
        eqCount++;
        numPassed++;
    }
        

    MatrixAdd(a_matrix, b_matrix, result_matrix);
    if(MatrixEquals(result_matrix, ten_matrix) == TRUE)
    {
        addCount++;
        numPassed++;
    }
    MatrixAdd(a_matrix, negOne_matrix, result_matrix);
    if(MatrixEquals(result_matrix, minOne_matrix) == TRUE)
    {
        addCount++;
        numPassed++;
    }
    
    
    MatrixMultiply(a_matrix, b_matrix, result_matrix);
    if(MatrixEquals(result_matrix, mulOne_matrix));
    {
        mulCount++;
        numPassed++;
    }
    MatrixMultiply(a_matrix, negOne_matrix, result_matrix);
    if(MatrixEquals(result_matrix, mulNeg_matrix));
    {
        mulCount++;
        numPassed++;
    }
    
    
    MatrixScalarAdd(scaVar, a_matrix, result_matrix);
    if(MatrixEquals(result_matrix, scaAdd_matrix) == TRUE)
    {
        scaAddCount++;
        numPassed++;
    }
    MatrixScalarAdd(scaVarTwo, a_matrix, result_matrix);
    if(MatrixEquals(result_matrix, scaAddTwo_matrix) == TRUE)
    {
        scaAddCount++;
        numPassed++;
    }
    
    
    MatrixScalarMultiply(scaVarTwo, a_matrix, result_matrix);
    if(MatrixEquals(result_matrix, double_matrix) == TRUE)
    {
        scaMulCount++;
        numPassed++;
    }
    MatrixScalarMultiply(scaNeg, a_matrix, result_matrix);
    if(MatrixEquals(result_matrix, neg_matrix) == TRUE)
    {
        scaMulCount++;
        numPassed++;
    }
    
    
    if(MatrixTrace(a_matrix) == traceAnsOne)
    {
        traceCount++;
        numPassed++;
    }
    if(MatrixTrace(neg_matrix) == traceAnsTwo)
    {
        traceCount++;
        numPassed++;
    }
    
    
    MatrixTranspose(a_matrix, result_matrix);
    if(MatrixEquals(result_matrix, transOne_matrix) == TRUE)
    {
        tranCount++;
        numPassed++;
    }
    MatrixTranspose(b_matrix, result_matrix);
    if(MatrixEquals(result_matrix, transTwo_matrix) == TRUE)
    {
        tranCount++;
        numPassed++;
    }
    
    
    MatrixSubmatrix(subInt2, subInt2, a_matrix, lil_matrix);
    if(MatrixSubEqual(lil_matrix, subAns1_matrix) == TRUE)
    {
        subCount++;
        numPassed++;
    }
    MatrixSubmatrix(subInt1, subInt3, b_matrix, lil_matrix);
    if(MatrixSubEqual(lil_matrix, subAns2_matrix) == TRUE)
    {
        subCount++;
        numPassed++;
    }

    
    if(MatrixDeterminant(det1_matrix) == detAns1);
    {
        detCount++;
        numPassed++;
    }
    if(MatrixDeterminant(det2_matrix) == detAns2);
    {
        detCount++; 
        numPassed++;
    }
    
    
    MatrixInverse(inverse_matrix, result_matrix);
    if(MatrixEquals(result_matrix, invAns1_matrix))
    {
        invCount++;
        numPassed++;
    }
    MatrixInverse(inverse2_matrix, result_matrix);
    if(MatrixEquals(result_matrix, invAns2_matrix))
    {
        invCount++;
        numPassed++;
    }

    
    printf("PASSED (%d/2): MatrixEquals()\n", eqCount);
    printf("PASSED (%d/2): MatrixAdd()\n", addCount);
    printf("PASSED (%d/2): MatrixMul()\n", mulCount);
    printf("PASSED (%d/2): MatrixDeterminant()\n", detCount);
    printf("PASSED (%d/2): MatrixScalarMultiply()\n", scaMulCount);
    printf("PASSED (%d/2): MatrixScalarAdd()\n", scaAddCount);
    printf("PASSED (%d/2): MatrixSubmatrix()\n", subCount);
    printf("PASSED (%d/2): MatrixInverse()\n", invCount);
    printf("PASSED (%d/2): MatrixTrace()\n", traceCount);
    printf("PASSED (%d/2): MatrixTranspose()\n\n", tranCount);
    printf("---------------------------------------\n");
    
    percentCorrect = ((numPassed/numOfFunc) * 100);
    
    printf("%.1f of %.1f functions passed %.1f percent.\n\n", numPassed/2, numOfFunc/2, percentCorrect);

    printf("Demonstrating MatrixPrint():\n");
    
    MatrixPrint(a_matrix);
    
    printf("Expected output of MatrixPrint():\n\n");
    printf("1.00 2.00 3.00\n");
    printf("4.00 5.00 6.00\n");
    printf("7.00 8.00 9.00\n");

    printf("\n");
    // Add more tests here!
    BOARD_End();
    while (1);
}
