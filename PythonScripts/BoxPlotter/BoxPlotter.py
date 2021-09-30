# Imports
# =======
import numpy as np
import matplotlib.pyplot as plt
import statistics
import csv

# Script Setup
# ============
# Plot Name
plotName = "Full Performace Data"
# plotName = "Plot 1 Performace Data"

# Plot Data
Full1 = []
Full1Lee = []
Full1DataFilePathLee = "LeePerformanceFull1.csv"
Full1DataFilePath = "AStarPerformanceFull1.csv"

Full2 = []
Full2Lee = []
Full2Dijkstra = []
Full2DataFilePath = "AStarPerformanceFull2.csv"
Full2DataFilePathLee = "LeePerformanceFull2.csv"
Full2DataFilePathDijkstra = "DijkstraPerformanceFull2.csv"


Half = []
HalfLee = []
HalfDataFilePath = "AStarPerformanceHalf.csv"
HalfDataFilePathLee = "LeePerformanceHalf.csv"

Quarter = []
QuarterLee = []
QuarterDataFilePath = "AStarPerformanceQuarter.csv"
QuarterDataFilePathLee = "LeePerformanceQuarter.csv"

# Output Plot File Name
PlotFileName = "output/FullPerformanceComparison.png"
# PlotFileName = "output/Plot1ComparisonPerformance.png"

# Welcome Message
# ===============
print("Box Plotter Script Started")

# Load Data From CSV
# ==================
# FullData1
print("Loading " + Full1DataFilePath + " data ...")
with open(Full1DataFilePath, 'r') as csvFile:
    csvReader = csv.reader(csvFile, delimiter=',')
    for csvRow in csvReader:
        Full1.append(csvRow)
print("Load complete")

print("Loading " + Full1DataFilePathLee + " data ...")
with open(Full1DataFilePath, 'r') as csvFile:
    csvReader = csv.reader(csvFile, delimiter=',')
    for csvRow in csvReader:
        Full1Lee.append(csvRow)
print("Load complete")

# FullData2
print("Loading " + Full2DataFilePath + " data ...")
with open(Full2DataFilePath, 'r') as csvFile:
    csvReader = csv.reader(csvFile, delimiter=',')
    for csvRow in csvReader:
        Full2.append(csvRow)
print("Load complete")

print("Loading " + Full2DataFilePathLee + " data ...")
with open(Full2DataFilePath, 'r') as csvFile:
    csvReader = csv.reader(csvFile, delimiter=',')
    for csvRow in csvReader:
        Full2Lee.append(csvRow)
print("Load complete")

print("Loading " + Full2DataFilePathDijkstra + " data ...")
with open(Full2DataFilePath, 'r') as csvFile:
    csvReader = csv.reader(csvFile, delimiter=',')
    for csvRow in csvReader:
        Full2Dijkstra.append(csvRow)
print("Load complete")

# HalfData
print("Loading " + HalfDataFilePath + " data ...")
with open(HalfDataFilePath, 'r') as csvFile:
    csvReader = csv.reader(csvFile, delimiter=',')
    for csvRow in csvReader:
        Half.append(csvRow)
print("Load complete")

print("Loading " + HalfDataFilePathLee + " data ...")
with open(HalfDataFilePath, 'r') as csvFile:
    csvReader = csv.reader(csvFile, delimiter=',')
    for csvRow in csvReader:
        HalfLee.append(csvRow)
print("Load complete")

# QuarterData
print("Loading " + QuarterDataFilePath + " data ...")
with open(QuarterDataFilePath, 'r') as csvFile:
    csvReader = csv.reader(csvFile, delimiter=',')
    for csvRow in csvReader:
        Quarter.append(csvRow)
print("Load complete")

print("Loading " + QuarterDataFilePathLee + " data ...")
with open(QuarterDataFilePath, 'r') as csvFile:
    csvReader = csv.reader(csvFile, delimiter=',')
    for csvRow in csvReader:
        QuarterLee.append(csvRow)
print("Load complete")


# Convert Data To Numpy Array
# ===========================
print("Converting data array to numpy array ...")
Full1 = np.array(Full1).astype(np.float)
Full1Lee = np.array(Full1Lee).astype(np.float)
Full2 = np.array(Full2).astype(np.float)
Full2Lee = np.array(Full2Lee).astype(np.float)
Full2Dijkstra = np.array(Full2Dijkstra).astype(np.float)
Half = np.array(Half).astype(np.float)
HalfLee = np.array(HalfLee).astype(np.float)
Quarter = np.array(Quarter).astype(np.float)
QuarterLee = np.array(QuarterLee).astype(np.float)

medianFull1 = statistics.median(Full1)
medianFull1Lee = statistics.median(Full1Lee)
medianFull2 = statistics.median(Full2)
medianFull2Lee = statistics.median(Full2Lee)
medianFull2Dijkstra = statistics.median(Full2Dijkstra)
medianHalf = statistics.median(Half)
medianHalfLee = statistics.median(HalfLee)
medianQuarter = statistics.median(Quarter)
medianQuarterLee = statistics.median(QuarterLee)

#medians = [medianFull1, medianFull2]
medians = [medianFull1, medianFull1Lee, medianFull2, medianFull2Lee, medianFull2Dijkstra, medianHalf, medianHalfLee, medianQuarter, medianQuarterLee]
print("Conversion Complete")

# Plotting
# ========
print("Plotting Boxplot ...")
fig, ax = plt.subplots()
ax.set_title(plotName)
ax.boxplot([Full1.flatten(), Full1Lee.flatten(), Full2.flatten(), Full2Lee.flatten(), Full2Dijkstra.flatten(), Half.flatten(), HalfLee.flatten(), Quarter.flatten(), QuarterLee.flatten()])
#ax.boxplot([Full1.flatten(), Full2.flatten()])
ax.set_xticklabels(['Full 1 A*', 'Full 1 Lee', 'Full 2 A*', 'Full 2 Lee', 'Full 2 Dijkstra', 'Half A*', 'Half Lee', 'Quarter A*', 'Quarter Lee'])
ax.set_ylabel('Algorithms Execution Time (sec)')

# col = 0
# for value in medians:
#     ax.text(col + .7, value - (0.01 - (col / 1000)), str(value))
#     col = col + 1


# ax.text( .7, medians[0] - 0.015, str(medians[0]))
# ax.text( 1+ .7, medians[1] - 0.015, str(medians[1]))
# ax.text( 2+ .7, medians[2] - 0.007, str(medians[2]))
# ax.text( 3+ .7, medians[3] + 0.007, str(medians[3]))
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