// Standard libraries
#include <stdio.h>
#include <math.h>
#include "stdlib.h"

//User libraries:
#include "BOARD.h"




// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Subtract(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double Divide(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double CelsiusToFahrenheit(double operand);
double Average(double operand1, double operand2);
double Tangent(double operand);
double Round(double operand);

//add more prototypes here


void CalculatorRun(void)
{
    printf("\n\nWelcome to Alex's calculator program! Compiled at %s %s\n", __DATE__, __TIME__);
    
    // Your code here
    int c;
    char g; //Garbage collector
    double firstOp, secondOp;
    
    while (1){
            printf("\nEnter a mathematical operation to preform (*,/,+,-,m,a,c,f,t,r): ");
            c = getchar();

            if (c == '+'){
                printf("Enter the first operand: ");
                scanf("%lf%c", &firstOp, &g);
                        
                printf("Enter the second operand: ");
                scanf("%lf%c", &secondOp, &g);
                
                printf("Result of (%lf + %lf): %lf\n", firstOp, secondOp, Add(firstOp, secondOp));
            }
            else if (c == '-'){
                printf("Enter the first operand: ");
                scanf("%lf%c", &firstOp, &g);
                        
                printf("Enter the second operand: ");
                scanf("%lf%c", &secondOp, &g);
                
                printf("Result of (%lf - %lf): %lf\n", firstOp, secondOp, Subtract(firstOp, secondOp));
            }
            else if (c == '*'){
                printf("Enter the first operand: ");
                scanf("%lf%c", &firstOp, &g);
                        
                printf("Enter the second operand: ");
                scanf("%lf%c", &secondOp, &g);
                
                printf("Result of (%lf * %lf): %lf\n", firstOp, secondOp, Multiply(firstOp, secondOp));
            }
            else if (c == '/'){
                printf("Enter the first operand: ");
                scanf("%lf%c", &firstOp, &g);
                        
                printf("Enter the second operand: ");
                scanf("%lf%c", &secondOp, &g);
                
                if (secondOp == 0)
                printf("Divide by Zero!");
                else
                printf("Result of (%lf / %lf): %lf\n", firstOp, secondOp, Divide(firstOp, secondOp));
            }
             else if (c == 'm'){
                printf("Enter the first operand: ");
                scanf("%lf%c", &firstOp, &g);
                        
                printf("Enter the second operand: ");
                scanf("%lf%c", &secondOp, &g);
                
                printf("Average of (%lf, and %lf): %f\n", firstOp, secondOp, Average(firstOp, secondOp));
            }            
            else if (c == 'a'){
                printf("Enter an operand: ");
                scanf("%lf%c", &firstOp, &g);
                
                printf("Result of |%lf|: %lf\n", firstOp, AbsoluteValue(firstOp));
            }
             else if (c == 'c'){
                printf("Enter an operand: ");
                scanf("%lf%c", &firstOp, &g);
                
                printf("Result of %f in Celsius: %f\n", firstOp, FahrenheitToCelsius(firstOp));
            }
             else if (c == 'f'){
                printf("Enter an operand: ");
                scanf("%lf%c", &firstOp, &g);
                
                printf("Result of %f in Fahrenheit: %lf\n", firstOp, CelsiusToFahrenheit(firstOp));
            }
             else if (c == 't'){
                printf("Enter an operand: ");
                scanf("%lf%c", &firstOp, &g);
                
                printf("Result of tangent of %lf: %lf\n", firstOp, Tangent(firstOp));
            }
             else if (c == 'r'){
                 printf("Enter an operand: ");
                 scanf("%lf%c", &firstOp, &g);
                 
                 printf("Result of %lf: %lf\n", firstOp, Round(firstOp));
                 
             }
             else if (c == 'q')
             {
                 break;
             }
    }
}


//C:\Users\CityPork\atorre83\Lab02\Lab2_part1.X\Calculator.c
/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2)
{
    double result;
    
    result = operand1 + operand2;
    return result;
}

/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2)
{
	double result;
    
    result = operand1 - operand2;
    return result;
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2)
{
    double result;
    
    result = operand1 * operand2;
    return result;
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2)
{
	double result;
    
    result = operand1 / operand2;
    return result;
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand)
{
    double result;
    
    result = fabs(operand);
    return result;
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand)
{
    double result;
    
    result = (operand - 32) * 5 / 9;
    return result;
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand)
{
    double result;
    
    result = (operand * 9/5) + 32;
    return result;
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2)
{
    double result;
    
    result = (operand1 + operand2) / 2;
    return result;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
double Tangent(double operand)
{
    double result;
    
    result = tan(operand);
    
    return result;
}
/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand)
{
    double result;
    int mod;
    
    mod = operand;

    if (operand > 0){
        if (operand - mod < .5){
            result = mod;        
        }
        else
            result = (mod + 1);
    }
    
    else {
        if ((fabs(operand) - fabs(mod)) < .5){
            result = mod;        
        }
        else
            result = (mod - 1);
    }
    return result;
}



