#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;
void LoadData(double[], double[], double[40][40], int &row, int &column);
void TemperatureCheck(double[], int column, double usertempreture);
void WindCheck(double[], int row, double userwindspeed);
int ColumnNumber(double[], int column, double usertempreture);
int RowNumber(double[], int row, double userwindspeed);;
double WindChill(double[40][40], int colnum, int rownum, double usertempreture);
int main()
{
	//declaring variables
	int row = 0, column = 0;
	int rowindex, columnindex;
	double finalvalue;
	//declaring arrays, and variables
	double temperature[40], windspeed[40], windchill[40][40], usertempreture, userwindspeed;
	string userinput;
	bool exit = false;
	// calling load data function to open the data from the file and put it into arrays
	LoadData(temperature, windspeed, windchill, row, column);
	//Using an infenite loop to keep asking the user for inputs
	while (!exit) {
		//asking the user to input temperature
		cout << "To exit the program press 1" << endl;
		cout << "Please enter the temperature in Celsius" << endl;
		cin >> usertempreture;
		// if the user enter 1 then the program will exit
		if (usertempreture == 1) {
			exit = true;
			break;
		}
		//calling function to check the temperature range 
		TemperatureCheck(temperature, column, usertempreture);
		//asking the user for wind speed as an input
		cout << "Please enter the wind speed in km/h" << endl;
		cin >> userwindspeed;
		if (userwindspeed == 1) {
			exit = true;
			break;
		}
		// calling functions windcheck
		WindCheck(windspeed, row, userwindspeed);
		//assigning function columnNumber to columnindex
		columnindex = ColumnNumber(temperature, column, usertempreture);
		//assigning function RowNumber to rowindex
		rowindex = RowNumber(windspeed, row, userwindspeed);
		//assigning Windchill function to final value
		finalvalue = WindChill(windchill, columnindex, rowindex, usertempreture);
		cout << " the Wind Chill is " << finalvalue << endl;
	}



	system("pause");
	return 0;
}
// opening the function to load data
void LoadData(double temperature[], double windspeed[], double windchill[40][40], int &row, int &column)
{

	int count = 0;
	string line;
	// opening file
	ifstream infile;
	//checking if the files open or not
	infile.open("chill.txt", ios::in);
	if (infile.fail())
	{
		//print message if the file is not opening
		cerr << "Error opening the file" << endl;
		system("pause");
		exit(0);
	}
	// do loop to store data from file into array

	do
	{

		infile >> temperature[column];
		column++;
	} while (infile.get() != '\n');

	// do loop to store data from file into array
	do
	{
		infile >> windspeed[row];
		row++;
	} while (infile.get() != '\n');
	//for loop to store data from file into 2d array

	for (int k = 0; k < row; k++)
		for (int i = 0; i < column; i++)
		{
			infile >> windchill[k][i];
		}
	// function used to return the pointer to the begining of the line
	infile.clear();
	infile.seekg(0, ios::beg);
	// functtion to read data from file into a line
	while (getline(infile, line))
		count++;
	// we use this to find Number of lines containing temperature drop values is not equal to the number of values in the second line.
	if (row != count - 2) {
		//print error message
		cerr << " Eror Loading the Matrix" << endl;
		system("pause");
		exit(-1);
	}
	// function used to return the pointer to the begining of the line
	infile.clear();
	infile.seekg(0, ios::beg);
	int Allvalues = 0, Linevalues = 0;
	// We use this to see if Number of values in a temperature drop line not equal to the number of values in the first line too small.
	while (!infile.eof())
	{
		infile.get();
		if (infile.peek() == '\n' || infile.peek() == ' ')
			Allvalues++;
	}

	Linevalues = (Allvalues - row - column) / (count - 2);
	if (column != Linevalues) {
		//print error message 
		cerr << " Error Loading the Matrix 101";
		system("pause");
		exit(-1);
	}
}




void TemperatureCheck(double temperature[], int column, double usertempreture)
{
	//this function we use to check if the temperature is in the range
	while ((usertempreture > temperature[0]) || (usertempreture < temperature[column - 1]))
	{
		// if not, the following would be printed on the screen.

		cout << "Tempreture is out of the range:" << endl;
		cout << "Please input tempreture between:  " << temperature[0] << " and " << temperature[column - 1] << endl;
		cin >> usertempreture;
	}
}
void WindCheck(double windspeed[], int row, double userwindspeed) {
	//this function is to check if the user windspeed is in the range
	while ((userwindspeed < windspeed[0]) || (userwindspeed > windspeed[row - 1]))
	{
		// if not, the following would be printed on the screen.
		cout << "Windspeed is out of the range" << endl;
		cout << "Please input windspeed between:  " << windspeed[0] << " and " << windspeed[row - 1] << endl;
		cin >> userwindspeed;
	}
}
int ColumnNumber(double temperature[], int column, double usertempreture)
{
	// we use this function to find the closest number for the number that the user enter for temperature if it is not on the chart
	//the equation is to round the  number to the number next to it or before it on the chart, depending on the number, if it it is a midpoint then it will round up, if it is smaller than midpoint it will round down and if it is greater than midpoint it will round up
	int index = 0;
	for (int i = 0; i < column - 1; i++)
	{
		if ((usertempreture <= temperature[i]) && (usertempreture >= temperature[i + 1]))
		{
			double average;
			average = (temperature[i] + temperature[i + 1]) / 2;
			if (usertempreture >= average)
			{
				index = i;
			}
			else if ((usertempreture < average))
			{
				index = i + 1;
			}
		}
	}
	return(index);
}
int RowNumber(double windspeed[], int row, double userwindspeed) {
	{
		// we use this function to find the closest number for the number that the user enter for windspeed if it is not on the chart
		// the equation is to round the  number to the number next to it or before it on the chart, depending on the number, if it it is a midpoint then it will round up, if it is smaller than midpoint it will round down and if it is greater than midpoint it will round up


		int index = 0;
		for (int i = 0; i <= row - 1; i++)
		{
			if ((userwindspeed >= windspeed[i]) && (userwindspeed <= windspeed[i + 1]))
			{
				double average;
				average = (windspeed[i] + windspeed[i + 1]) / 2;
				if (userwindspeed < average)
				{
					index = i;
				}
				else if ((userwindspeed >= average))
				{
					index = i + 1;
				}
			}
		}
		return(index);
	}
}
double WindChill(double windchill[40][40], int colnum, int rownum, double usertempreture) {
	// we subtract the returned array whcih is windchill[rownum][colnum] from the temperature that user inputed and  will return it into final value
	double finalvalue;
	finalvalue = usertempreture - windchill[rownum][colnum];
	return finalvalue;
}




