/**********************************************************************
Filename:			ass1.cpp
Version: 			1.0                                         
Author:				Justin Bertrand                                              
Student No:  		040 786 592                                          
Course Name/Number:	Numerical Computing - CST8233                                 
Lab Sect: 			301                        
Assignment #:		1
Assignment name:	Catastrophic Vibration
Due Date:			October 20th, 2015                                           
Submission Date:	October 20th, 2015
Professor:			Andrew Tyler                                           
Purpose: 			Calculates the value of a Maclaurin series for the
					function e^(t)*sin(t) to up to 5 terms and compares
					it to the math library implementations.
*********************************************************************/
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

//DEFINES
#define WIDTH 15

//Function prototypes
double power(double, int);
double factorial(int);

/********************************************************************
Function name:		main
Purpose:			main function
					Calculates the Maclaurin series
In parameters:		none
Out parameters:		0 for successful execution
Version:			1.0
Author:				Justin Bertrand
**********************************************************************/
int main(void) {

	char input = 0;
	int num_of_terms = 0;
	double t_value = 0.0;
	double maclaurin_values[] = { 1.0, 2.0, 2.0, 0.0, -4.0, -8.0, -8.0 };

	while (true) {
		cout << "Evaluate the Taylor Series approximation to D(t) = exp(t)*sin(t)" << endl;

		cout << "1: Evaluate the series" << endl;
		cout << "2: quit" << endl;

		cin >> input;

		//
		double t_values[10] = { 0.0 };
		double series_values[10] = { 0.0 };
		double truncated_terms[10] = { 0.0 };
		double exact_values[10] = { 0.0 };
		double calculation = 0;
		int term_index = 0;

		switch (input)
		{
		case '1':
			cout << "Evaluating the series" << endl;
			cout << "Please enter the number of non-zero terms in the series (1, 2, 3, 4, or 5): ";
			cin >> num_of_terms;

			if (t_value < 0.0 || t_value > 1.0)
			{
				cout << "Invalid value of t." << endl;
				break;
			}
			cout << endl << "Please enter the range of t to evaluate in 10 increments (0.0 < t < +1.0): ";
			cin >> t_value;
			
			if (t_value < 0.0 || t_value > 1.0)
			{
				cout << "Invalid value of t." << endl;
				break;
			}
					
			for (int t_index = 0; t_index < 10; ++t_index)
			{
				int count = 1;
				t_values[t_index] = t_value / 10.0 * (double)(t_index + 1);
				exact_values[t_index] = exp(t_values[t_index]) * sin(t_values[t_index]);

				term_index = 0;
				calculation = t_values[t_index];				
				
				for (int calc_index = 0; calc_index < num_of_terms; ++calc_index)
				{
					if (maclaurin_values[term_index] != 0) {
						double calculation = maclaurin_values[term_index];
						calculation *= power(t_values[t_index], count);
						calculation /= factorial(count);
						series_values[t_index] += calculation;
					}
					else {
						--calc_index;
					}

					++count;
					++term_index;
				}

				if (maclaurin_values[term_index] == 0) {
					++count;
					++term_index;
				}
				truncated_terms[t_index] = maclaurin_values[term_index];
				truncated_terms[t_index] *= power(t_values[t_index], count);
				truncated_terms[t_index] /= factorial(count);
				
			}

			cout << endl << "MACLAURIN SERIES" << endl;
			cout <<  setiosflags(ios::scientific|ios::showpoint);
			cout << setw(WIDTH) << "  t" << setw(WIDTH) << "D(t) Series" << setw(WIDTH) << "D(t) Exact";
			cout << setw(WIDTH) << "%RExactE" << setw(WIDTH) << "%RSerE" << endl;
			
			cout << setw(WIDTH) << setprecision(3) << 0.0;
			cout << setw(WIDTH) << setprecision(5) << 0.0;
			cout << setw(WIDTH) << 0.0;
			cout << setw(WIDTH) << 0.0;
			cout << setw(WIDTH) << 0.0;
			cout << endl;

			for (int index = 0; index < 10; ++index)
			{
				cout << setw(WIDTH) << setprecision(3) << t_values[index];
				cout << setw(WIDTH) << setprecision(5) << series_values[index];
				cout << setw(WIDTH) << exact_values[index];
				cout << setw(WIDTH) << (exact_values[index] - series_values[index])/exact_values[index] * 100.0;
				cout << setw(WIDTH) << 100.0 * truncated_terms[index] / series_values[index];
				cout << endl;
			}
			cout << endl;

			break;
		case '2':
			return EXIT_SUCCESS;
		}
	}
}

/********************************************************************
Function name:		factorial
Purpose:			Calculates the factorial up to the given term.
In parameters:		int term to calculate up tp
Out parameters:		double: result of the calculations
Version:			1.0
Author:				Justin Bertrand
**********************************************************************/
double factorial(int term) {
	
	double result = 1.0;
	
	for (double index = 1.0; index <= term; ++index) {
		result *= index;
	}

	return result;
}

/********************************************************************
Function name:		power
Purpose:			Calculates the exponentials
In parameters:		double: term to use
					int: exponent to be raised to
Out parameters:		double: result of the calculations
Version:			1.0
Author:				Justin Bertrand
**********************************************************************/
double power(double term, int exponent) {
	double result = 1.0;

	for (int index = 0; index < exponent; ++index) {
		result *= term;
	}
	return result;
}