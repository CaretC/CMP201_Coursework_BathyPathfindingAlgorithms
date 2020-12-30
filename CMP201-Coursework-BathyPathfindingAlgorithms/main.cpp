/*
	CMP201 Coursework Bathymetry Pathfinding Algorithm Comparison
	=============================================================
	Author: Joseph Lee (1903399)
	E-mail: 1903399@uad.ac.uk
	Decription: The aim of this program is to find the shortest path between the
				start point and the end point within a given set of bathymetry data.
				The route is selected with the aim of using this route for subsea
				cable installation so the route is selected to be the smoothest route
				avaliable to prevent the need for the cable to go over any ridges.
	Date: 29/12/2020
	Usage: This code is written for sumbission for academic assessment at Abertay University 
		   for module CMP201, it should not be shared or distibuted for any other purpose 
		   without conscent from author.
*/

// =============================================================================================
// Includes
// ========
#include<vector>

#include"ConsoleGUI.h"
#include"DataLoader.h"
// =============================================================================================

// =============================================================================================
// Function Prototypes
// ===================
// =============================================================================================

// =============================================================================================
// Main
// ====
int main() {
	// Create UI Instance
	ConsoleGUI ui;
	ui.Initialize();

	// Print Welcome Screen
	ui.WelcomeScreen();

	// Print message
	ui.PrintBlankLine();
	ui.PrintMessage("Test Message");
	ui.PrintWarning("Warning");
	ui.PrintSuccess("Success");

	// Load Data
	DataLoader loader;
	std::vector<std::vector<DataNode>> gridData = loader.LoadDataFile("ConnelBathyDataSampleTinyTrimmed.csv", &ui);

	return 0;
}
// =============================================================================================

// =============================================================================================
// Functions
// =========
// =============================================================================================