/*
	Console GUI
	===========
	Author: Joseph Lee (1903399)
	E-mail: 1903399@uad.ac.uk
	Decription: Provides a simple console application GUI for CMP201 coursework.
	Date: 29/12/2020
	Usage: This code is written for sumbission for academic assessment at Abertay University
		   for module CMP201, it should not be shared or distibuted for any other purpose
		   without conscent from author.
*/

// =============================================================================================
// Includes
// ========
#include "ConsoleGUI.h"
// =============================================================================================

void ConsoleGUI::Initialize()
{
	// Set cursor vis
	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// =============================================================================================
// Public Functions
// ================
void ConsoleGUI::WelcomeScreen()
{
	PrintTitle();
}

void ConsoleGUI::PrintMessage(std::string message)
{
	std::cout << " " << message << std::endl;
}

void ConsoleGUI::PrintBlankLine()
{
	std::cout << std::endl;
}

void ConsoleGUI::PrintWarning(std::string warningMessage)
{
	SetTextColour(WARNING_COLOR);
	std::cout << " " << warningMessage << std::endl;
	SetTextDefault();
}

void ConsoleGUI::PrintSuccess(std::string successMessage)
{
	SetTextColour(SUCCESS_COLOR);
	std::cout << " " << successMessage << std::endl;
	SetTextDefault();
}

void ConsoleGUI::PrintSubTitle(std::string subTitle)
{
	SetTextColour(EMPHASIS_COLOR);
	std::cout << " " << subTitle << std::endl;
	SetTextDefault();

	std::cout << " ";

	for (int i = 0; i < subTitle.size(); i++)
	{
		std::cout << "-";
	}

	std::cout << std::endl;
}

void ConsoleGUI::WaitForKeyPress()
{
	PrintMessage("Press [ENTER] to continue ...");
	std::cin.get();
}

void ConsoleGUI::StatusBar(std::string barName, int currentValue, int fullValue)
{
	double percentage = (double)currentValue / (double)fullValue * 100;
	double numberOfBars = round(percentage / 5);
	int numberOfSpaces = 20 - numberOfBars;

	// Overwrite Line
	std::cout << "\r\b";


	std::cout << " [";

	// Set Bar Color
	if (percentage != 100)
	{
		SetTextColour(TITLE_COLOR);
	}
	else
	{
		SetTextColour(SUCCESS_COLOR);
	}

	// Print Bars
	for (int i = 0; i < numberOfBars; i++) {
		std::cout << "=";
	}

	// Print Spaces
	for (int i = 0; i < numberOfSpaces; i++) {
		std::cout << " ";
	}

	SetTextDefault();

	//std::cout << "] - " << std::setprecision(3) << percentage << "%";
	std::cout << "] - " << (int)percentage << "%";

	// If Complete end line
	if (percentage == 100)
	{
		std::cout << std::endl;
	}
}


// =============================================================================================

// =============================================================================================
// Private Functions
// ================
void ConsoleGUI::SetTextColour(const int& colorCode)
{
	// Check clourcode is within range
	assert(colorCode > 0 && colorCode <= 25 && "Invalid Console Color Code");

	// Set console text colour
	SetConsoleTextAttribute(hConsole, colorCode);
}

void ConsoleGUI::SetTextDefault()
{
	// Set console text colour
	SetConsoleTextAttribute(hConsole, DEFAULT_COLOR);
}

void ConsoleGUI::PrintTitle()
{
	std::cout << " ###############################################" << std::endl;
	std::cout << " # ";
	SetTextColour(TITLE_COLOR);
	std::cout << "Bathymetry Pathfinding Algorithm Comparison";
	SetTextDefault();
	std::cout << " #" << std::endl;
	std::cout << " ###############################################" << std::endl;
}
// =============================================================================================


