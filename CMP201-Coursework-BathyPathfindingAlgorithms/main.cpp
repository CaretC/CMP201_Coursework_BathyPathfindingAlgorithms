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

#include"Coord.h"
#include"UtmCoord.h"
#include"ConsoleGUI.h"
#include"DataLoader.h"
#include"CsvWriter.h"
#include"AStar.h"
#include"Lee.h"
#include"PerformanceMonitor.h"
// =============================================================================================

// =============================================================================================
// Function Prototypes
// ===================
// =============================================================================================

// =============================================================================================
// Global Variables
// ================
const int NUMBER_OF_RUNS = 1000;
const int SAVE_VISITED_NODES = false;
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
	ui.PrintSubTitle("Setup");
	ui.PrintMessage("Loading Required Bathy Data ...");

	// Load Data
	DataLoader loader;
	std::vector<std::vector<DataNode>> gridData = loader.LoadDataFile("ConnelBathyDataSampleTinyTrimmed.csv", &ui);
	//std::vector<std::vector<DataNode>> gridData = loader.LoadDataFile("ConnelBathyDataSampleTinyTrimmedHalf.csv", &ui);
	//std::vector<std::vector<DataNode>> gridData = loader.LoadDataFile("ConnelBathyDataSampleTinyTrimmedQuarter.csv", &ui);

	// Specify Start Point
	// Plot 1
	//Coord StartPoint = {20, 226};
	//Coord EndPoint = { 42, 0 };
	// Plot 2
	Coord StartPoint = { 20, 113 };
	Coord EndPoint = { 42, 0 };
	// Plot 3
	//Coord EndPoint = { 10, 90 };
	//Coord StartPoint = { 40, 0 };
	// Half / Quarter
	//Coord EndPoint = { 10, 113 };
	//Coord StartPoint = { 12, 0 };


	// Convert to UTM For test
	UtmCoord StartPointUTM = { (double)gridData[StartPoint.X][StartPoint.Y].UTM_Easting, (double)gridData[StartPoint.X][StartPoint.Y].UTM_Northing };
	UtmCoord EndPointUTM = { (double)gridData[EndPoint.X][EndPoint.Y].UTM_Easting, (double)gridData[EndPoint.X][EndPoint.Y].UTM_Northing };

	// Write Start/ End to .csv
	CsvWriter csvW;
	csvW.WriteToCsv(StartPointUTM, "StartPoint.csv", ui);
	csvW.WriteToCsv(EndPointUTM, "EndPoint.csv", ui);

	// Plot points message
	ui.PrintMessage("Start Point: {" + std::to_string(StartPoint.X) + "," + std::to_string(StartPoint.Y) + "}");
	ui.PrintMessage("End Point: {" + std::to_string(EndPoint.X) + "," + std::to_string(EndPoint.Y) + "}");
	ui.PrintMessage(std::to_string(NUMBER_OF_RUNS) + " itterations of each algorithm will be conducted");

	// Wait
	ui.WaitForKeyPress();

	// Lee Algorithm
	// -------------
	PerformanceMonitor leePerformance;	
	Lee lee;
	std::vector<UtmCoord> leePath;

	ui.PrintSubTitle("Lee Algorithm");
	ui.StatusBar("Lee Status", 0, NUMBER_OF_RUNS);

	for (int i = 0; i < NUMBER_OF_RUNS; i++) {
		leePerformance.Start();
		leePath = lee.LeePath(gridData, StartPoint, EndPoint, SAVE_VISITED_NODES);
		leePerformance.Stop();	
		
		leePerformance.Save();
		ui.StatusBar("Lee Status", i+1, NUMBER_OF_RUNS);
	}

	csvW.WriteToCsv(leePath, "LeePath.csv", ui);	
	csvW.WriteToCsv<double>(leePerformance.GetResutls(), "LeePerformance.csv", ui);

	// Wait
	ui.WaitForKeyPress();

	// A* Algorithm
	// ------------
	PerformanceMonitor aStarPerformance;
	AStar astar;
	std::vector<UtmCoord> aStarPath;

	ui.PrintSubTitle("A* Algorithm");
	ui.StatusBar("A-Star Status", 0, NUMBER_OF_RUNS);

	for (int i = 0; i < NUMBER_OF_RUNS; i++) {
		aStarPerformance.Start();
		aStarPath = astar.AStarPath(gridData, StartPoint, EndPoint, SAVE_VISITED_NODES);
		aStarPerformance.Stop();
		aStarPerformance.Save();
		ui.StatusBar("A-Star Status", i+1, NUMBER_OF_RUNS);
	}

	csvW.WriteToCsv(aStarPath, "AStarPath.csv", ui);
	csvW.WriteToCsv<double>(aStarPerformance.GetResutls(), "AStarPerformance.csv", ui);

	// Wait
	ui.WaitForKeyPress();

	return 0;
}
// =============================================================================================

// =============================================================================================
// Functions
// =========
// =============================================================================================