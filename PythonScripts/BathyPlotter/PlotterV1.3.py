import sys
import csv
import math
import time
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import griddata

# =============
# Script Setup
# =============
# Max Data Segment Rows
maxRows = 20000

# Directories
inputDirectory = "DataInputs/"
outputDirectory = "DataOutputs/"
plotsDirectory = "Plots/"

# Files
# Input
inputFileDirectory = "Connel/ConnelTiny/"
inputFile = "ConnelTinyHalf.csv"

# Outputs
outputPlotDirectory = "Connel/ConnelTiny/"
outPlot = "HalfLeePath"

# Interpolation Method
interpMethod = 'linear'

# Output Names
plotName = plotsDirectory + outputPlotDirectory +interpMethod.capitalize() + outPlot
plotTitle = "Connel Area Half - Lee Path"

# Plot Config
level = 14

# Points
pointColors = 'ro'
pathFileName = inputDirectory + inputFileDirectory + 'LeePath.csv'
plotPoints = []
print("Loading " + pathFileName + " data...")
with open(pathFileName, 'r') as csvFile:
    csvReader = csv.reader(csvFile, delimiter=',')
    for csvRow in csvReader:
        plotPoints.append(csvRow)
print("Load complete")
pathPointCount = len(plotPoints)
print("Path Plot Point Count = " + str(pathPointCount))


# Full Image
fullImageMode = False

# Inverted Colours
invert_colors = False

# Resolution Multiplier
resolution_multiplier = 1

# Sort Data
sort_data = True

# ===========
# Read CSV
# ===========
csvFileName = inputDirectory + inputFileDirectory + inputFile
print("Loading " + csvFileName + " data...")
csvData = []
with open(csvFileName, 'r') as csvFile:
    csvReader = csv.reader(csvFile, delimiter=',')
    for csvRow in csvReader:
        csvData.append(csvRow)
print("Load complete")

# ====================
# Check Data Length
# ====================
dataRowCount = len(csvData)
print("Data Row Count = " + str(dataRowCount))

# ==========================
# Segment Data Notification
# ==========================
allSegmentsProcessed = False
segCount = 0
if dataRowCount > maxRows:
    print("Large Data Set Detected - Data Segmentation Required")
    segsRequired = math.ceil(dataRowCount/maxRows)
    print("Data will be split into " + str(segsRequired) + " segments")
    usrInput = input("Do you really want to process this much data? (yes(y) or no(n))\n")
    if usrInput.lower() == "y" or usrInput.lower() == "yes":
        print("Segmenting Data")
        fullImageMode = True
    else:
        quit()
else:
    print("Small Data Set Detected - Single Data Set Processing")
    segsRequired = 1

# ==============
# Convert Data
# ==============y
print("Convering RAW data to numPy array...")
csvData = np.array(csvData).astype(np.float)
plotPoints = np.array(plotPoints).astype(np.float)
#np.round(csvData, 8)
print("Raw Data Converted.")

# ============
# Sort Data
# ============
if sort_data:
    print("Sorting Data...")
    csvData = csvData[csvData[:,0].argsort()] # First sort doesn't need to be stable.
    csvData = csvData[csvData[:,1].argsort(kind='mergesort')]
    print("Data Sorted")

# ===============
# Proccess Data
# ===============
while not allSegmentsProcessed:
    # ================
    # Segment Timer
    # ================
    seg_start = time.monotonic()

    # ==============
    # Segment Data
    # ==============
    segmentData = []
    if segsRequired > 1:
        print("Segmenting Data - Segment " + str(segCount))       
        rowD = segCount * maxRows
        print("Starting From Row - " + str(rowD))
        while rowD < (maxRows + (maxRows * segCount)) and rowD < dataRowCount:
            segmentData.append(csvData[rowD])
            rowD = rowD + 1
        segmentData = np.array(segmentData)
        print("Segmentation of Segment " + str(segCount) + " Complete")

        print(segmentData)
        # input("Segment")
    else:
        segmentData = csvData   

    # ======================
    # Find data dimensions
    # ======================
    print("Analysing Data...")
    x = segmentData[:,0]
    x_max = max(x)
    x_min = min(x)
    x_len = len(x)
    del x

    y = segmentData[:,1]
    y_max = max(y)
    y_min = min(y)
    y_len = len(y)
    del y

    print("Plotting between " + str(x_min) + ", " + str(y_min) + " and " + str(x_max) + ", " + str(y_max))

    # Resolution Selected for the whole dataset to avoid change segment to segment
    if segCount == 0:
        z = csvData[:,2]
        z_max = max(z)
        z_min = min(z)
        z_range = abs(float(z_max) - float(z_min))
        level = int(math.ceil(z_range)) * resolution_multiplier
        print("Plot resolution has been set to " + str(level) + " levels")
        print("(Data depth range of " + str(z_range) + "m and a resolution multiplier of " + str(resolution_multiplier) + ")")
        del z
    print("Analysis Complete")

    # ==============
    # Generte Grid
    # ==============
    print("Generating XY Grid...")
    x_line = np.linspace(float(x_min), float(x_max), int(x_len))
    y_line = np.linspace(float(y_min), float(y_max), int(y_len))


    X, Y = np.meshgrid(x_line, y_line)
    print("XY Grid Generated")

    # ===========================
    # Interpolate the Z results
    # ===========================
    print("Interpolating the Z data...")
    Z = griddata((segmentData[:,0], segmentData[:,1]), segmentData[:,2], (X,Y), method=interpMethod).astype(np.float)
    print("Interpolation Complete")

    # =========
    # Cleanup
    # =========
    print("Cleaning Up Data...")
    del(segmentData)
    print("Cleanup Complete")

    # =========
    # Plotting
    # =========
    print("Plotting Data...")
    fig, ax = plt.subplots()
    #ax.axis('tight')

    # Fill Contour
    if invert_colors:
        CS = ax.contourf(X, Y, -Z, levels=level)
    else:
        CS = ax.contourf(X, Y, Z, levels=level)

    #if not fullImageMode:
    print("Plotting Complete")

    # =============
    # Plot Points
    # =============
    for point in plotPoints:        
        ax.plot(point[0], point[1], pointColors)    

    # ===========
    # Save Plot
    # ===========
    print("Saving Plot...")
    ax.set_title(plotTitle + " (" + interpMethod.capitalize() + ")" + " Segment " + str(segCount))
    cbar = fig.colorbar(CS, ax=ax)
    cbar.set_label("Water Depth (m)")
    plt.savefig(plotName + "(" + str(segCount) + ").png")
    print("Plot Saved " + plotName)

    # =============
    # Toggle Axis
    # =============
    if fullImageMode:
        plt.axis('off')
        plt.title('')
        cbar.remove()
        plt.savefig((plotName + "Full"+ "(" + str(segCount) + ").png"), bbox_inches='tight', pad_inches = 0)
        plt.axis('on')

    # ===========
    # Rendering
    # ===========
    if segsRequired == 1:
        print("Rendering...")
        plt.show()
        print("Render Complete")

    # ===================
    # Segment Increment
    # ===================
    seg_stop = time.monotonic()

    if segCount < segsRequired:
        seg_duration = seg_stop - seg_start
        segCount = segCount + 1
        data_remaining_time = seg_duration * (segsRequired - segCount)
        print("Segment " + str(segCount) + " took " + str(round(seg_duration)) + " seconds, based on this the remaining " + str(segsRequired - segCount) + " will take approximatly "  + str(round(data_remaining_time)) + " seconds")

    if segCount == segsRequired:
        allSegmentsProcessed = True
        break
    

print("All Data Processed - Exiting Programme")
    











