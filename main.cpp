/*
	Author: Kishaan G

	Description: Functions assignment. Determine the equation of the line passing through the first two points. Determine the shortest distance between the third point and the line passing through the first two points.

	Last modified: 11 May, 2022.
*/


/// ======================= Pre-processor commands =======================

#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

/// ============================= Structures =============================

struct Point
{
	double xCoord;
	double yCoord;
};

struct Line
{
	double slope;
	double yInt;
};

/// ============================= Prototypes =============================

void keyToContinue();
double getDouble(string);
void getPoints(Point &, Point &, Point &);
int menu(string, string[], int, string);
double getSlope(Point, Point);
double getYIntercept(double, Point);
void displayEquation(Line);
double getNegativeReciprocal(double);
double getDistBetweenPoints(Point, Point);
Line equationOfFirstTwoPoints(Point, Point);
double shortestDistOfLineAndPoint(Line, Point);
void mainInterface();

/// ============================= Definitions =============================

void keyToContinue()
{
	cin.ignore();
	cout << "Type any key to continue..." << endl;
	getchar();
	return;
}

/// =======================================

double getDouble(string prompt)
{
	double response = 0;
	cout << prompt << endl; // Displays the message given when it's called.
	cin >> response; // Recieves then returns the double the user inputs.
	return response;
}

/// =======================================

void getPoints(Point & _point1, Point & _point2, Point & _point3)
{
	do{
		_point1.xCoord = getDouble("What would you like to be the x coordinate of the first point.");
		system("clear"); // Gets the x and y coordinates of the three points.
	
		_point1.yCoord = getDouble("What would you like to be the y coordinate of the first point.");
		system("clear");
	
		_point2.xCoord = getDouble("What would you like to be the x coordinate of the second point.");
		system("clear");
	
		_point2.yCoord = getDouble("What would you like to be the y coordinate of the second point.");
		system("clear");
		if(_point1.xCoord == _point2.xCoord and _point1.yCoord == _point2.yCoord)
		{// Checks if the user gave two of the same points.
			cout << "Please type in different points." << endl;
			keyToContinue();
			system("clear");
		}
	}while(_point1.xCoord == _point2.xCoord and _point1.yCoord == _point2.yCoord); // If the user gave 2 identical points, the program asks for new points again.
	
	_point3.xCoord = getDouble("What would you like to be the x coordinate of the third point.");
	system("clear");

	_point3.yCoord = getDouble("What would you like to be the y coordinate of the third point.");
	system("clear");
	return;
}

/// =======================================

int menu(string prompt, string options[], int numberOfOptions, string errorMsg)
{
	int response;
	do
	{
		cout << prompt << endl;
		for(int i = 0; i < numberOfOptions; i++)
		{
			cout << i+1 << ") " << options[i] << endl;
		}
		cin >> response;
		if(response < 1 or response > numberOfOptions)
		{
			cout << errorMsg << endl;
			keyToContinue();
			system("clear");
		}
	}while (response < 1 or response > numberOfOptions);
	return response;
}

/// =======================================

double getSlope(Point _point1, Point _point2)
{
	if((_point2.yCoord - _point1.yCoord) == 0)
	{
		return 0; // If the y coordinate is the same for two points, the line isn't increasing, meaning there is no slope.
	}
	else if((_point2.xCoord - _point1.xCoord) == 0)
	{
		return INFINITY; // If the x coordinate is the same for two points, the line isn't moving to a side, meaning the slope is infinity.
	}
	return (_point2.yCoord - _point1.yCoord) / (_point2.xCoord - _point1.xCoord); // Uses the slope formula to determine the slope of the given point.
}

/// =======================================

double getYIntercept(double _slope, Point _point)
{
	if(_slope == INFINITY)
	{
		return _point.xCoord; // When the slope is infinity, I use the x intercept instead of the y intercept. 
	}
	else if(_slope == 0)
	{
		return _point.yCoord; // When the slope is 0, the y intercept is the y coordinate of any point on the line. 
	}
	return _point.yCoord - (_slope * _point.xCoord); // Gets the y intercept by isolating b on a side and performing all the calculations on the other side of the equation. 
}

/// =======================================

void displayEquation(Line line)
{
	if(line.slope == INFINITY)
	{
		cout << "x = " << line.yInt; // If the slope is infinity, this writes x = the x intercept. 
	}
	else if(line.slope == 0)
	{
		cout << "y = " << line.yInt; // If the slope is 0, this writes y = the y intercept of the line
	}
	else if(line.yInt == 0)
	{
		cout << "y = " << line.slope << "x";  // If the y intercept is 0, you do not need to display + 0.
	}
	else if (line.yInt < 0)
	{
		cout << "y = " << line.slope << "x - " << -1 * line.yInt; // If the y intercept is negative, you do not need to display + -yInt, instead display - yInt.
	}
	else cout << "y = " << line.slope << "x + " << line.yInt; // Otherwise, display the slope and y intercept in standard y = mx + b form. 	
	return;
}

/// =======================================

double getNegativeReciprocal(double _slope)
{
	if(_slope == INFINITY)
	{// The negative reciprocal of infinity is 0.
		return 0;
	}
	if(_slope == 0)
	{// The negative reciprocal of 0 is infinity.
		return INFINITY;
	}
	return 1/(_slope * -1); // The negative reciprocal is 1/the slope * -1. 
}

/// =======================================

double getDistBetweenPoints(Point _point1, Point _point2)
{
	return sqrt((pow((_point2.xCoord - _point1.xCoord), 2)) + (pow((_point2.yCoord - _point1.yCoord), 2))); // Uses the distance formula to get the distance between 2 given points. 
}

/// =======================================

Line equationOfFirstTwoPoints(Point _firstPoint, Point _secondPoint)
{
	Line line;
	line.slope = getSlope(_firstPoint, _secondPoint);
	line.yInt = getYIntercept(line.slope, _firstPoint);
	return line;
}

/// =======================================


double shortestDistOfLineAndPoint(Line _mainLine, Point _point)
{
	Point POI;
	Line negativeRecipLine;
	double distBetweenPoiAndPoint = 0;

	if(_mainLine.slope == INFINITY)
	{// If the slope is infinity, the shortest distance between the point and the line is the difference in the x coordinate of the point, and the x intercept of the line. 
		distBetweenPoiAndPoint = _point.xCoord - _mainLine.yInt;
	}
	else if(_mainLine.slope == 0)
	{// If the slope is 0, the shortest distance between the point and the line is the difference in the y coordinate of the point, and the y intercept of the line. 
		distBetweenPoiAndPoint = _point.yCoord - _mainLine.yInt;
	}
	else if(_point.yCoord == _mainLine.slope*_point.xCoord + _mainLine.yInt)
	{// If the point is on the line, the distance is 0. This is added so the computer doesn't have to perform extra calculations if the point is on the line. 
		distBetweenPoiAndPoint = 0;
	}
	else
	{
		negativeRecipLine.slope = getNegativeReciprocal(_mainLine.slope); // Gets the negative reciprocal of the mainLine slope. 
		negativeRecipLine.yInt = getYIntercept(negativeRecipLine.slope, _point); // Gets the y intercept of the line when the line with the negative reciprocal slope passes through a given point. 

		POI.xCoord = ((_mainLine.yInt - negativeRecipLine.yInt) / (_mainLine.slope - negativeRecipLine.slope))*-1; // Divides the difference of the y intercepts by the difference of the slopes to get the x coordinate of the POI.
		
	
		POI.yCoord = (_mainLine.slope * POI.xCoord) + _mainLine.yInt; // Subs in the x coordinate into the mainLine equation to solve for the POI. 

		distBetweenPoiAndPoint = getDistBetweenPoints(POI, _point);// Gets the distance between the POI and the point given by the user. 
	}

	return distBetweenPoiAndPoint; // Returns the closest distance between the line and the point. 
}

/// =======================================

void mainInterface()
{
	Line mainLine; // This is the line of the points point1 and point 2.
	Point point1; // These are the points given by the user. 
	Point point2;
	Point point3;
	string options[4] = {"Determine the equation of the line passing through the first two points.", "Determine the shortest distance between the third point and the line passing through the first two points.", "Change the points.", "Quit"};
	string prompt = "What would you like to do:";
	string errorMsg = "Please type either 1, 2, 3 or 4.";
	int userMenuChoice = 0;
	getPoints(point1, point2, point3);
	
	do
	{
		mainLine = equationOfFirstTwoPoints(point1, point2); // Calculates the equation of the mainLine with the first two points.
		userMenuChoice = menu(prompt, options, 4, errorMsg); // Determines what function the user wants to run. 
		switch(userMenuChoice)
		{
			case 1:
				system("clear");
				cout << "The equation is:" << endl;
				displayEquation(mainLine); // Displays the equation of the mainLine. 
				cout << endl;
				keyToContinue();
				system("clear");
				break;

			case 2:
				system("clear");
				cout << abs(shortestDistOfLineAndPoint(mainLine, point3)) << " units is the shortest distance between (" << point3.xCoord << ", " << point3.yCoord << ") and the line "; // Displays the shortest distance between the thrid point and the mainLine. 
				displayEquation(mainLine);
				cout << ".\n";
				keyToContinue();
				system("clear");
				break;

			case 3:
				system("clear");
				getPoints(point1, point2, point3); // Changes the points determined by the user. 
				break;

			case 4: // Quit option
				break;
		}
	}while(userMenuChoice != 4);
	return;
}

/// =======================================

int main()
{
	mainInterface(); // Runs the main interface. 
	return 0;
}
