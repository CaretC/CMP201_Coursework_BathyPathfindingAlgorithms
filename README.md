CMP201 Coursework - Bathymetry Pathfinding Algorithms
=====================================================

Overview
--------
This project compares pathfinding algorithms for use with seabed bathymetry data. 
As the aim of this is to find a path suitable for subsea cable routes it aims to 
find the smoothest path between the start point and endpoint.

Real World Need
---------------
It is a common issue in the offshore tidal energy industry to need to optimise subsea
cable routes between offshore tidal energy platforms and the shore to allow the export
for the generated electrical power. Although the shorted possible cable length is 
advantagious it is not the only factor. Due to the cable routing and felixibility the
topology of the seabed often needs to be considered and the smoothest route to the shore
is often required to ensure maximum cable seabed stability.

Algorithms Chosen
-----------------
For this comparison the smoothest rough through the bathy data will be calculated using
the `Lee` and the `A*` shortest path algorithms. The performance and results of these 
will be conmpared.

Smoothness
----------
To allow for the smoothest route to betweem the start position and the end position to be 
selected the bathy data will be represented as a grid. Each Node in the grid will be 
assigned a `depth` value. This depth will be used to calcuate the cost for moving to this
cell, in this case this is the difference in depth between the two nodes. 
