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
#pragma once
#include<vector>
#include<string>
#include<fstream>
#include<sstream> // std::stringstream
#include<unordered_set>

#include"DataNode.h"
#include "ConsoleGUI.h"
// =============================================================================================

// =============================================================================================
class DataLoader
{
	// -----------------------------------------------------------------------------------------
	// Public
	// ------
	public:
	// Load a bathy data file 
	std::vector<std::vector<DataNode>> LoadDataFile(std::string filePath, ConsoleGUI* gui);

	// -----------------------------------------------------------------------------------------

	// -----------------------------------------------------------------------------------------
	// Private
	// ------
	private:
	std::vector<DataNode> loadedData;

	// -----------------------------------------------------------------------------------------
};
// =============================================================================================

