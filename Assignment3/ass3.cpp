/**********************************************************************
Filename:			ass3.cpp
Version: 			1.0
Author:				Justin Bertrand
Student No:  		040 786 592
Course Name/Number:	Numerical Computing - CST8233
Lab Sect: 			301
Assignment #:		2
Assignment name:	Bungee
Due Date:			December 06th, 2015
Submission Date:	December 06th, 2015
Professor:			Andrew Tyler
Purpose: 			A real-time simulation of a man performing bungee
*********************************************************************/

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;

double const gravity = 9.8; //g
double const vmax = 46.0;
double const height_init = 400.0; //h
double const bungee = 0.04; //k
double const a = 8.0;
double const m = 68.0;

unsigned long long time_init, time_current, time_current_plus1, time_delta;
double height;
double dvdt;
double velocity, velocity_plus1;
double drag; //c

int main(void)
{
	int choice = 'r';

	while (choice == 'r')
	{
		//Initialize default values
		velocity = 0;
		height = 400;
		drag = 10.0;

		int key;

		time_init = time_current = GetTickCount64();

		// dv/dt = g - c/m *(v + a*(v/vmax)^2) - B
		dvdt = gravity - drag / m *(velocity + a*pow(velocity / vmax, 2.0));

		HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO buffer_info;

		GetConsoleScreenBufferInfo(console_handle, &buffer_info);
		SetConsoleTextAttribute(console_handle, 10);

		cout << setiosflags(ios::fixed | ios::showpoint);
		cout << setprecision(3);

		while (true)
		{
			time_current_plus1 = GetTickCount64();
			time_delta = time_current_plus1 - time_current;

			if (time_delta)
			{

				dvdt = gravity - drag / m *(velocity + a*pow(velocity / vmax, 2.0)) - bungee*(height_init - height);

				//vi+1 = vi + accni*time_elapsed
				velocity_plus1 = velocity + dvdt*double(time_delta)/1000.0;
				//hi+1 = hi-((vi +vi+1)/2) 
				height = height - ((velocity + velocity_plus1) / 2)*double(time_delta) / 1000.0;

				velocity = velocity_plus1;

				unsigned long long current_time = time_current_plus1 - time_init;
				unsigned long long millisec = current_time % 1000;
				current_time /= 1000;
				unsigned long long seconds = current_time % 60;
				current_time /= 60;
				unsigned long long minutes = current_time % 60;

				system("cls");
				cout << "Press q to quit; w to increase drag; e to increase drag" << endl;
				cout << "Starting bungee jump: Wind drag = " << drag << endl;
				cout << "Elapsed time: " << minutes << " minutes " << seconds << " seconds " << millisec << " milliseconds"<< endl;
				cout << "Speed of descent = " << velocity << "m/s" << endl;
				cout << "Height above ground = " << height << "metres" << endl;

				time_current = GetTickCount64();
			}
			
			if (kbhit())
			{
				key = getch();
				switch (key)
				{
				case 'w':
					if (drag < 10.0)
						++drag;
					break;
				case 'e':
					if (drag > 0)
						--drag;
					break;
				case 'q':
					exit(0);
				}
			}

			if (velocity < 0.0 && height > 1.0)
			{
				cout << "Unfortunately, you didn't make it to the ground." << endl;
				break;
			}

			if (height <= 1.0 && velocity < 1.0)
			{
				cout << "Congratulations, you landed safely." << endl;
				break;
			}
				
			if (height <= 0.0 && velocity >= 1.0)
			{
				cout << "Unfortunately, you hit the ground too fast." << endl;
				break;
			}
		}
		
		cout << "To restart press r; to quit press q";

		choice = getch();
		while (choice != 'q' && choice != 'r')
			choice = getch();

		if (choice == 'q')
			break;
	}
		
}