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
#pragma once
#include<chrono>
#include<vector>
// =============================================================================================

// =============================================================================================
class PerformanceMonitor
{
	// -----------------------------------------------------------------------------------------
	// Public
	// ------
	public:
		// Starts the performace clock
		void Start();

		// Stops the performance clock
		void Stop();

		// Saves Current performance clock time performance vector
		void Save();



	// -----------------------------------------------------------------------------------------

	// -----------------------------------------------------------------------------------------
	// Private
	// -------
	private:
		// Performance Clock Instance
		std::chrono::steady_clock performaceClock;

		// StartTime
		std::chrono::time_point< std::chrono::steady_clock> startTime;

		// StartTime
		std::chrono::time_point< std::chrono::steady_clock> stopTime;

		// Duration
		std::chrono::duration<double> duration;

		// Vector of saved performance times
		std::vector<double> performanceResutls;
	// -----------------------------------------------------------------------------------------
};
// =============================================================================================
