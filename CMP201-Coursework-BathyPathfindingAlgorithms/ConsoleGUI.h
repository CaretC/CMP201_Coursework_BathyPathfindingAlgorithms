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
#include<iostream>
#include<string>
#include<Windows.h>
#include<assert.h>
#include<cmath>
#include <iostream>
#include <iomanip>
// =============================================================================================

// =============================================================================================
#pragma once
class ConsoleGUI
{
	// -----------------------------------------------------------------------------------------
	// Public
	// ------
	public:
		// Initialize the console for gui
		void Initialize();

		// Displays the welcome screen to the console
		void WelcomeScreen();
		
		// Prints message string to the console at the current cursor position as line
		void PrintMessage(std::string message);

		// Print balnk line to the console
		void PrintBlankLine();

		// Prints warning message to the console at the current cursor position as line
		void PrintWarning(std::string warningMessage);

		// Prints success message to the console at the current cursor position as line
		void PrintSuccess(std::string successMessage);

		// Prints a sub title to the console at the current cursor position as line
		void PrintSubTitle(std::string subTitle);

		// Prints Press any key to continue message and wait for keep press
		void WaitForKeyPress();

		/* Prints status bar to console based on the current value and displays as a percentage of
		the full value*/
		void StatusBar(std::string barName, int currentValue, int fullValue);

	// -----------------------------------------------------------------------------------------

	// -----------------------------------------------------------------------------------------
	// Private
	// -------
	private:
		// Variables
		// ---------
		// Console Handle
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		// Colors
		const int TITLE_COLOR = 11;
		const int DEFAULT_COLOR = 7;
		const int WARNING_COLOR = 12;
		const int SUCCESS_COLOR = 10;
		const int EMPHASIS_COLOR = 13;

		// Functions
		// ---------
		// Sets the console text colour to the colour code specifed
		void SetTextColour(const int& colourCode);

		// Set the console text colour to the default color
		void SetTextDefault();

		// Prints the program title bloc to the console at the current cursor position
		void PrintTitle();

	// -----------------------------------------------------------------------------------------	
};
// =============================================================================================

