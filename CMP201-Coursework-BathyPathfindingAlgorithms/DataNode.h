/*
	Data Node
	===========
	Author: Joseph Lee (1903399)
	E-mail: 1903399@uad.ac.uk
	Decription: A struct to store the data loaded from the bathy data files
	Date: 29/12/2020
	Usage: This code is written for sumbission for academic assessment at Abertay University
		   for module CMP201, it should not be shared or distibuted for any other purpose
		   without conscent from author.
*/

#pragma once

struct DataNode {
	double UTM_Easting = -1;
	double UTM_Nothing = -1;
	double Depth;
};
