# Imports
# =======
import numpy as np
import matplotlib.pyplot as plt
import csv

# Script Setup
# ============
# Plot Name
plotName = "A* Algorithm Box Plot - Grid Generation By Col Then Row"

# Plot Data
plotData = []
plotDataFilePath = "AStarPerformance.csv"

# Output Plot File Name
PlotFileName = "output/AStarBoxPlot-GridColRow.png"

# Welcome Message
# ===============
print("Box Plotter Script Started")

# Load Data From CSV
# ==================
print("Loading " + plotDataFilePath + " data ...")
with open(plotDataFilePath, 'r') as csvFile:
    csvReader = csv.reader(csvFile, delimiter=',')
    for csvRow in csvReader:
        plotData.append(csvRow)
print("Load complete")

# Convert Data To Numpy Array
# ===========================
print("Converting data array to numpy array ...")
plotData = np.array(plotData).astype(np.float)
print("Conversion Complete")

# Plotting
# ========
print("Plotting Boxplot ...")
fig, ax = plt.subplots()
ax.set_title(plotName)
ax.boxplot(plotData)
print("Boxplot Plotting Complete")

# Show Plot
# =========
print("Renering Plot ...")
plt.show()
print("Renering Complete")

# Save Plot
# =========
print("Saving Plot " + PlotFileName)
fig.savefig(PlotFileName, bbox_inches='tight')
print("Plot Saved ")

# Finish Message
# ==============
print("Box Plotter Script Finished")