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
#include "CsvWriter.h"
// =============================================================================================




// =============================================================================================
// Public Functions
// ================
void CsvWriter::WriteToCsv(UtmCoord& coord, std::string outFilePath, ConsoleGUI& ui)
{
	ui.PrintMessage("Writting to .csv file ...");

	// Open Ouput File Stream
	std::ofstream outFile;
	outFile.open(outFilePath);

	if (outFile.is_open())
	{
		ui.PrintSuccess("Output file " + outFilePath + "opened successfully!");
		ui.PrintMessage("Writting file data ...");

		// Write data to file
		outFile << std::to_string(coord.UTM_Eastings) << "," << std::to_string(coord.UTM_Northing) << std::endl;


		// Close File
		ui.PrintSuccess("Data write complete!");
		outFile.close();
		ui.PrintSuccess(outFilePath + " .csv data write complete. " + outFilePath + " closed!");

	}
	else
	{
		ui.PrintWarning("Output file " + outFilePath + " failed to open, exiting application");
		exit(1);
	}
}

void CsvWriter::WriteToCsv(std::vector<UtmCoord>& coordvector, std::string outFilePath, ConsoleGUI &ui)
{
	ui.PrintMessage("Writting to .csv file ...");

	// Open Ouput File Stream
	std::ofstream outFile;
	outFile.open(outFilePath);

	if (outFile.is_open())
	{
		ui.PrintSuccess("Output file " + outFilePath + "opened successfully!");
		ui.PrintMessage("Writting file data ...");

		// Write data to file
		for (auto& coord : coordvector) {
			outFile << std::to_string(coord.UTM_Eastings) << "," << std::to_string(coord.UTM_Northing) << std::endl;
		}

		// Close File
		ui.PrintSuccess("Data write complete!");
		outFile.close();
		ui.PrintSuccess(outFilePath + " .csv data write complete. " + outFilePath + " closed!");

	}
	else
	{
		ui.PrintWarning("Output file " + outFilePath + " failed to open, exiting application");
		exit(1);
	}
}
// =============================================================================================

// =============================================================================================
// Private Functions
// ================

// =============================================================================================


