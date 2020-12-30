/*
	CSV Writer
	==========
	Author: Joseph Lee (1903399)
	E-mail: 1903399@uad.ac.uk
	Decription: Provides a simple method of writting data to a .csv file.
	Date: 29/12/2020
	Usage: This code is written for sumbission for academic assessment at Abertay University
		   for module CMP201, it should not be shared or distibuted for any other purpose
		   without conscent from author.
*/

// =============================================================================================
// Includes
// ========
// =============================================================================================
#pragma once
#include<vector>
#include<string>
#include <fstream>

#include"UtmCoord.h";
#include"ConsoleGUI.h";
// =============================================================================================

class CsvWriter
{
	// -----------------------------------------------------------------------------------------
	// Public
	// ------
	public:
		// Write vector of Coord data to a .csv file
		void WriteToCsv(UtmCoord& coord, std::string outFilePath, ConsoleGUI& ui);
		void WriteToCsv(std::vector<UtmCoord> &coordvector, std::string outFilePath, ConsoleGUI &ui);
	// -----------------------------------------------------------------------------------------

	// -----------------------------------------------------------------------------------------
	// Private
	// -------
	private:
	// -----------------------------------------------------------------------------------------

};
// =============================================================================================
