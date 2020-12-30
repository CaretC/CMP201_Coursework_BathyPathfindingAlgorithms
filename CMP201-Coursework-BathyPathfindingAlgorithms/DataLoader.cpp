/*
	Data Loader
	===========
	Author: Joseph Lee (1903399)
	E-mail: 1903399@uad.ac.uk
	Decription: Loads bathy data from .csv files ready for pathfinding algorithm
	Date: 29/12/2020
	Usage: This code is written for sumbission for academic assessment at Abertay University
		   for module CMP201, it should not be shared or distibuted for any other purpose
		   without conscent from author.
*/

// =============================================================================================
// Includes
// ========
#include "DataLoader.h"
// =============================================================================================

// =============================================================================================
// Public Functions
// ================
std::vector<std::vector<DataNode>> DataLoader::LoadDataFile(std::string filePath, ConsoleGUI* gui)
{
	gui->PrintMessage("Attempting to load data file " + filePath + " ...");

	// Create Input File Stream
	std::ifstream inFile(filePath);

	// Create Location To Save Data Lines
	std::string line;

	// If File is open
	if (inFile.is_open())
	{
		gui->PrintSuccess("Data file " + filePath + " opened successfully!");
		gui->PrintMessage("Loading raw data from " + filePath + " ...");

		// Read Data Line-by-line
		while (std::getline(inFile, line)) {
			double lineItem[3];
			int item = 0;

			// Stringsteam to store the current line for processing
			std::stringstream ss(line);

			// Split the string stream by the , delim
			while (ss.good()) {
				std::string value;
				std::getline(ss, value, ',');
				lineItem[item] = std::stod(value);
				item++;
			}

			// Create New Data Node
			DataNode newNode;
			newNode.UTM_Easting = lineItem[0];
			newNode.UTM_Nothing = lineItem[1];
			newNode.Depth = lineItem[2];

			// Push Data Node to loadedData Vector
			loadedData.push_back(newNode);
		}

		// Close Datafile
		gui->PrintSuccess("Raw data load from " + filePath + " completed!");
		inFile.close();
		gui->PrintSuccess(filePath + " closed");
		
	}
	else
	{
		// File Failed to open
		gui->PrintWarning("Data file " + filePath + " failed to open, exiting program!");
		exit(1);
	}

	// Calculate Data Dimensions
	int rawDataLen = loadedData.size();
	
	gui->PrintMessage("Processing raw Data ...");
	gui->PrintMessage(std::to_string(rawDataLen) + " raw data lines loaded");

	// Confirm x & y dimensions
	std::unordered_set<int> xSet;
	std::unordered_set<int> ySet;

	for (auto& node : loadedData) {
		xSet.insert(node.UTM_Easting);
		ySet.insert(node.UTM_Nothing);
	}

	int xWidth = xSet.size();
	int yWidth = ySet.size();

	gui->PrintMessage("Data grid size is (" + std::to_string(xWidth) + ", " + std::to_string(yWidth) + ")  (x, y)");
	gui->PrintSuccess("Raw data processing completed");

	// Convert vector to grid
	gui->PrintMessage("Converting raw data to grid ...");

	// Define Grid
	std::reverse(loadedData.begin(), loadedData.end());
	std::vector<std::vector<DataNode>> grid;
	grid.resize(xWidth, std::vector<DataNode>(yWidth));

	int row = 0;
	int col = 0;
	int lineNumber = 0;
	
	// Insert Data into grid
	for (const auto& dataNode : loadedData) {

		if (col == yWidth) {
			col = 0;
			row++;
		}

		grid[row][col].UTM_Easting = dataNode.UTM_Easting;
		grid[row][col].UTM_Nothing = dataNode.UTM_Nothing;
		grid[row][col].Depth = dataNode.Depth;

		col++;
		lineNumber++;

		gui->StatusBar("Grid Status", lineNumber, rawDataLen);
	}

	gui->PrintSuccess("Raw data conversion to grid completed!");
	return grid;
}

// =============================================================================================

// =============================================================================================
// Private Functions
// ================

// =============================================================================================


