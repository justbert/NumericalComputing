/**********************************************************************
Filename:			ass2.cpp
Version: 			1.0
Author:				Justin Bertrand
Student No:  		040 786 592
Course Name/Number:	Numerical Computing - CST8233
Lab Sect: 			301
Assignment #:		2
Assignment name:	Linear Regression Least Squares Fit to Data
Due Date:			November 09th, 2015
Submission Date:	November 09th, 2015
Professor:			Andrew Tyler
Purpose: 			Allows the interpolation or extrapolation of the 
						linear, power, or exponential growth of global
						CO2 levels;
*********************************************************************/
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

#define YEAROFFSET 1960
#define CO2OFFSET 316.5

using namespace std;

char* filename;
double* year;
double* levels;
int records;
double slope;
double intercept;

void displayFunctionTypeMenu();
void loadFile();
void releaseMemory();
void linear();
void power();
void exponential();
void interExtrapolate(char);

/********************************************************************
Function name:		main
Purpose:			main function
					Calculates the growth.
In parameters:		none
Out parameters:		0 for successful execution
Version:			1.0
Author:				Justin Bertrand
**********************************************************************/
int main()
{
	char input = '0';
	
	while (input != '4')
	{
		displayFunctionTypeMenu();
		cin >> input;

		switch (input)
		{
		case '1':
			loadFile();
			linear();
			cout << "Linear: Straight Line Fit to " << filename << ":" << endl;
			cout << "CO2 level = " << slope << "t + " << intercept << endl << endl;
			interExtrapolate('L');
			releaseMemory();
			break;
		case '2':
			loadFile();
			power();
			cout << "Power Law: Power Law Fit to " << filename << ":" << endl;
			cout << "CO2 level = (" << slope << ")t^(" << intercept << ")" << endl << endl;
			interExtrapolate('P');
			releaseMemory();
			break;
		case '3':
			loadFile();
			exponential();
			cout << "Exponential: Exponential Fit to " << filename << ":" << endl;
			cout << "CO2 level = (" << slope << ")e^(" << intercept << "t)" << endl << endl;
			interExtrapolate('E');
			releaseMemory();
			break;
		case '4':

			break;
		default:
			cout << "UNRECOGNIZED INPUT";
			continue;
		}
	}
}

/********************************************************************
Function name:		displayFunctionTypeMenu
Purpose:			Displays the function type menu
In parameters:		None
Out parameters:		None
Version:			1.0
Author:				Justin Bertrand
**********************************************************************/
void displayFunctionTypeMenu()
{
	cout << "*******************************************************" << endl;
	cout << "Linear Regression of Data - Function Type Menu" << endl;
	cout << "1. Linear:     y = m*x + c" << endl;
	cout << "2. Power Law:  y = m*x^c" << endl;
	cout << "3. Exponential:  y = m*e^(cx)" << endl;
	cout << "4. Quit" << endl;
	cout << "*******************************************************" << endl;
	cout << "Select and option: ";
}

/********************************************************************
Function name:		loadFile
Purpose:			Allows for the loading in of preformatted 
						values from a file.
In parameters:		None
Out parameters:		None
Version:			1.0
Author:				Justin Bertrand
**********************************************************************/
void loadFile()
{
	char buffer[256];

	cout << endl << "Please enter the name of the file to open: ";
	cin.clear();
	cin.ignore(256, '\n');
	cin.getline(buffer, 256);

	fstream file(buffer);
	
	if (!file.is_open())
	{
		cout << "FAILED TO LOAD FILE" << endl;
		return;
	}
	
	cout << "FILE OPENED FOR READING" << endl;

	filename = new char[strlen(buffer) + 1];
	strcpy(filename, buffer);

	records = 0;
	string line;

	while (getline(file, line))
	{
		++records;
		//cout << line << endl;
	}

	cout << "There are " << records << " records." << endl << endl;

	file.clear();
	file.seekg(0, ios::beg);

	year = new double[records];
	levels = new double[records];

	for (int index = 0; index < records; ++index)
	{
		file >> year[index];
		//cout << year[index] << "   ";
		file >> levels[index];
		//cout << levels[index] << endl;
	}
}

/********************************************************************
Function name:		releaseMemory
Purpose:			Releases or resets all memory that has been 
						allocated.
In parameters:		None
Out parameters:		None
Version:			1.0
Author:				Justin Bertrand
**********************************************************************/
void releaseMemory()
{
	delete filename;
	delete levels;
	delete year;

	records = 0;
	slope = 0;
	intercept = 0;
}

/********************************************************************
Function name:		linear
Purpose:			Calculates the least squares-fit of a linear 
						function.
In parameters:		None
Out parameters:		None
Version:			1.0
Author:				Justin Bertrand
**********************************************************************/
void linear()
{
	double sumXY = 0.0;
	double sumX = 0.0;
	double sumY = 0.0;
	double sumX_sq = 0.0;

	for (int index = 0; index < records; ++index)
	{
		sumXY += levels[index] * year[index];
		sumX += year[index];
		sumY += levels[index];
		sumX_sq += year[index] * year[index];
	}
	
	//cout << sumXY << endl << sumX << endl << sumY << endl << sumX_sq << endl;

	slope = records*sumXY - sumX*sumY;
	slope = slope / (records*sumX_sq - sumX*sumX);

	intercept = sumX_sq*sumY - sumXY*sumX;
	intercept = intercept / (records*sumX_sq - sumX*sumX);
}

/********************************************************************
Function name:		power
Purpose:			Calculates the least squares fit of a power
						formula.
In parameters:		None
Out parameters:		None
Version:			1.0
Author:				Justin Bertrand
**********************************************************************/
void power()
{
	double sumXY = 0.0;
	double sumX = 0.0;
	double sumY = 0.0;
	double sumX_sq = 0.0;
	double C = 0.0;
	double M = 0.0;

	for (int index = 0; index < records; ++index)
	{
		sumXY += log(levels[index]) * log(year[index]);
		sumX += log(year[index]);
		sumY += log(levels[index]);
		sumX_sq += log(year[index]) * log(year[index]);
	}

	//cout << sumXY << endl << sumX << endl << sumY << endl << sumX_sq << endl;


	M = records*sumXY - sumX*sumY;
	M = M / (records*sumX_sq - sumX*sumX);

	C = sumX_sq*sumY - sumXY*sumX;
	C = C / (records*sumX_sq - sumX*sumX);

	slope = exp(C);
	intercept = M;
}

/********************************************************************
Function name:		exponential
Purpose:			Calculates the least-squared fit for an 
						exponential function.
In parameters:		None
Out parameters:		None
Version:			1.0
Author:				Justin Bertrand
**********************************************************************/
void exponential()
{
	double sumXY = 0.0;
	double sumX = 0.0;
	double sumY = 0.0;
	double sumX_sq = 0.0;
	double C = 0.0;
	double M = 0.0;

	for (int index = 0; index < records; ++index)
	{
		sumXY += log(levels[index]) * year[index];
		sumX += year[index];
		sumY += log(levels[index]);
		sumX_sq += year[index] * year[index];
	}

	//cout << sumXY << endl << sumX << endl << sumY << endl << sumX_sq << endl;


	M = records*sumXY - sumX*sumY;
	M = M / (records*sumX_sq - sumX*sumX);

	C = sumX_sq*sumY - sumXY*sumX;
	C = C / (records*sumX_sq - sumX*sumX);

	slope = exp(C);
	intercept = M;
}

/********************************************************************
Function name:		loadFile
Purpose:			Interpolates or extrapolates with a given year.
In parameters:		Char representing the type of function.
Out parameters:		None
Version:			1.0
Author:				Justin Bertrand
**********************************************************************/
void interExtrapolate(char type)
{
	char input = '0';
	double year = 0.0;

	while (input != '2')
	{
		cout << "*******************************************************" << endl;
		cout << "Extapolation of data Menu" << endl;
		cout << "1. Do an interpolation/extrapolation" << endl;
		cout << "2. Return to main menu" << endl;
		cout << "*******************************************************" << endl;
		cout << "Select an option: ";

		cin >> input;
		cin.clear();
		cin.ignore(256, '\n');

		switch (input)
		{
		case '1':
			cout << "Input a year to interpolate/extrapolate to : ";
			cin >> year;
			cout << "CO2 level (" << setprecision(0) << year << ") = ";
			switch (type)
			{
			case 'P':
				cout << slope*pow(year - YEAROFFSET, intercept) + CO2OFFSET;
				break;
			case 'L':
				cout << slope*(year - YEAROFFSET) + intercept + CO2OFFSET;
				break;
			case 'E':
				cout << slope*exp(intercept*(year - YEAROFFSET)) + CO2OFFSET;
				break;
			}
			cout << endl << endl;
			break;
		case '2':
			break;
		default:
			cout << "UNRECOGNISED INPUT";
		}
	}
}