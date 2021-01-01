/*
	Performance Monitor
	===================
	Author: Joseph Lee (1903399)
	E-mail: 1903399@uad.ac.uk
	Decription: Simple performance monitor too to keep track of application performance information
	Date: 29/12/2020
	Usage: This code is written for sumbission for academic assessment at Abertay University
		   for module CMP201, it should not be shared or distibuted for any other purpose
		   without conscent from author.
*/

// =============================================================================================
// Includes
// ========
#include "PerformanceMonitor.h"
// =============================================================================================

// =============================================================================================
// Public Functions
// ================
void PerformanceMonitor::Start()
{
	startTime = performaceClock.now();
}

void PerformanceMonitor::Stop()
{
	stopTime = performaceClock.now();
	duration = std::chrono::duration_cast<std::chrono::duration<double>>(stopTime - startTime);
}

void PerformanceMonitor::Save()
{
	performanceResults.push_back(duration.count());
}

void PerformanceMonitor::Clear()
{
	performanceResults.clear();
}

std::vector<double> PerformanceMonitor::GetResutls()
{
	return performanceResults;
}


// =============================================================================================

// =============================================================================================
// Private Functions
// =================

// =============================================================================================
