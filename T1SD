from tkinter.filedialog import askopenfilename

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import datetime
import os
from PIL import Image, ImageDraw, ImageFont
from fpdf import FPDF

"""
 This script is only to analyse the Kinovea results from test 1 small drop, the file to analyse need to be in the
 folder T1SD_result with the name T1SD_P.csv for the position and T1SD_V.csv for the velocity
"""

stanchions_length = 160
fork_travel = 150

# Open file and create Pandas DataFrame while changing the header, specifying the separator and defining data type,
# we also need to change the decimal delimiter from , to . to convert str value into float
df_p = pd.read_csv('T1SD_result/T1SD_P.csv', sep=';', names=['time', 'position'], header=0,
                   decimal=',', dtype={'time': int, 'position': float})

df_v = pd.read_csv('T1SD_result/T1SD_V.csv', sep=';', names=['time', 'velocity'], header=0,
                   decimal=',', dtype={'time': int, 'velocity': float})

# CLEANING VALUES
# replacing position value greater than the stanchion length (impossible value) by the maximum value (stanchion_length)
df_p.loc[(df_p.position > stanchions_length), "position"] = stanchions_length
# offset the value by stanchion length - fork travel
df_p.loc[:, "position"] -= stanchions_length - fork_travel
# replacing position value below 0 by 0
df_p.loc[(df_p.position < 0), "position"] = 0
# Convert velocity unit to mm/s (1 mm/s = 0.001 m/s)
df_v.loc[:, "velocity"] *= 1000

# PRINT DATAFRAMES FOR VERIFICATION
# print(df_p)  # show the position DataFrame
# print(df_v)  # show the velocity DataFrame

# CREATE TRAVEL TRACKING GRAPH
df_p.plot(x="time", y="position", kind='line', title='Travel Tracking', xlabel='Time (ms)', ylabel='Position (mm)')
# determine the first peak value corresponding to the fork full extension before the wheel hit the ground
first_peak = df_p.loc[(df_p.position == df_p.position.max()), 'time'].tolist()[0]
# compute the average value between tracking start and the peak value
average_before_peak = df_p.loc[(df_p.time <= first_peak), "position"].mean()
# draw this average line corresponding to "sag" after compression settings
plt.axhline(y=average_before_peak, color='green', linestyle='-', label='Average')
plt.legend()
plt.savefig('T1SD_result/Travel_Tracking.png') # save the graph
plt.show()

# CREATE VELOCITY GRAPH
df_v.plot(x="time", y="velocity", kind='line', title='Velocity', xlabel='Time (ms)', ylabel='Velocity (mm/s)')

# Low speed / high speed range for graph building and analysis
hsr_limit = df_v.velocity.max()  # check the fastest rebound speed
lsr_limit = 127  # exact number to define
lsc_limit = -127  # exact number to define
hsc_limit = df_v.velocity.min()  # check the fastest compression speed

# If the value are inferior do not show high velocity facecolor
# adjust the range of low velocity to the fastest compression speed and rebound speed
if df_v.velocity.max() > lsr_limit:
    plt.axhspan(lsr_limit, hsr_limit, facecolor='red', alpha=0.5, label="High speed rebound")

if df_v.velocity.min() < lsc_limit:
    plt.axhspan(lsc_limit, hsc_limit, facecolor='royalblue', alpha=0.5, label="High speed compression")

plt.axhspan(0, lsr_limit, facecolor='tomato', alpha=0.5, label="Low speed rebound")
plt.axhspan(0, lsc_limit, facecolor='lightsteelblue', alpha=0.5, label="Low speed Compression")

plt.legend()
plt.savefig('T1SD_result/velocity.png')
plt.show()

# CREATE BAR CHART FOR NUMBER OF VALUE WITHIN TRAVEL RANGE
# Define number of value by travel range and create a DataFrame
array_travel_range = np.arange(0, fork_travel, 10)
count_travel_range = []
range_travel = []
for x in array_travel_range:
    count_travel_range.append(df_p.loc[(df_p.position <= x + 10) & (df_p.position > x), "position"].count())
    range_travel.append(str(x) + '-' + str(x + 10))

df_count_travel_range = {'count': count_travel_range, 'range': range_travel}
df_travel_range = pd.DataFrame(df_count_travel_range)  # DataFrame construction
df_travel_range.plot(x="range", y="count", title='Number of value by travel range',
                     kind='bar', xlabel='Travel range (mm)', ylabel='Number of value')
# save the graph, with bbox_inches='tight' since the graph exceed the security limit in height it will be crop otherwise
plt.savefig('T1SD_result/count_travel_range.png', bbox_inches='tight')
plt.show()



# REBOUND SPEED BAR CHART
n_bar = 6  # The bar charts for rebound and comprssion has 6 ranges calculated from max value
range_delimiter_rebound = hsr_limit / n_bar  # define the value to increment range for rebound speed
range_delimiter_compression = hsc_limit / n_bar  # define the value to increment range for compression speed
array_rspeed_range = np.arange(0, hsr_limit, range_delimiter_rebound)
count_rspeed_range = []
range_rspeed = []
for y in array_rspeed_range:
    count_rspeed_range.append(
        df_v.loc[(df_v.velocity <= y + range_delimiter_rebound) & (df_v.velocity > y), "velocity"].count())
    range_rspeed.append(str(round(y)) + '-' + str(round(y + range_delimiter_rebound)))

df_count_rspeed_range = {'count': count_rspeed_range, 'range': range_rspeed}
df_rspeed_range = pd.DataFrame(df_count_rspeed_range)  # DataFrame construction
df_rspeed_range.plot(x="range", y="count", title='Number of value by rebound speed range',
                     kind='bar', xlabel='rebound speed range (mm/s)', ylabel='Number of value')
plt.savefig('T1SD_result/count_rspeed_range.png', bbox_inches='tight')
plt.show()

# COMPRESSION SPEED BAR CHART
array_cspeed_range = np.arange(0, hsc_limit, range_delimiter_compression)
count_cspeed_range = []
range_cspeed = []
for z in array_cspeed_range:
    count_cspeed_range.append(
        df_v.loc[(df_v.velocity >= z + range_delimiter_compression) & (df_v.velocity < z), "velocity"].count())
    range_cspeed.append(str(round(z)) + '-' + str(round(z + range_delimiter_compression)))

df_count_cspeed_range = {'count': count_cspeed_range, 'range': range_cspeed}
df_cspeed_range = pd.DataFrame(df_count_cspeed_range)  # DataFrame construction
df_cspeed_range.plot(x="range", y="count", title='Number of value by compression speed range',
                     kind='bar', xlabel='compression speed range (mm/s)', ylabel='Number of value')
plt.savefig('T1SD_result/count_cspeed_range.png', bbox_inches='tight')
plt.show()

# ASK THE USER FOR ITS SETTINGS DURING THIS TEST
sag_percent = input("Enter amount of sag in %: ")
hsc_user = input("Enter amount of HSC click from firmest to lightest : ")
lsc_user = input("Enter amount of LSC click from firmest to lightest : ")
hsr_user = input("Enter amount of HSR click from fastest to slowest : ")
lsr_user = input("Enter amount of LSR click from fastest to slowest : ")
token_user = input("Enter amount of token : ")
img = Image.new('RGB', (425, 70), color=(70, 70, 70))
font = ImageFont.truetype("consola.ttf", 18, encoding="unic")
canvas = ImageDraw.Draw(img)
canvas.text((10, 10), "HSC: " + hsc_user + "/16", fill='#FFFFFF', font=font)
canvas.text((10, 40), "LSC: " + lsc_user + "/14", fill='#FFFFFF', font=font)
canvas.text((135, 10), "HSR: " + hsr_user + "/8", fill='#FFFFFF', font=font)
canvas.text((135, 40), "LSR: " + lsr_user + "/16", fill='#FFFFFF', font=font)
canvas.text((250, 10), "SAG: " + sag_percent + "%", fill='#FFFFFF', font=font)
canvas.text((250, 40), "TOKEN: " + token_user, fill='#FFFFFF', font=font)
img.save('T1SD_result/current_settings.png')
img.show()

# CREATE THE PDF WITH ALL THE RESULT
pdf_title = input("Enter the subtitle of the PDF : ")
pdf = FPDF()
pdf.add_page()
pdf.set_font('Arial', 'B', 16)
pdf.cell(0, 10, 'Test Result', ln=1, align='C')
pdf.set_font('Arial', '', 12)
pdf.cell(0, 10, pdf_title, ln=1, align='C')
today_date = datetime.datetime.now()
pdf.cell(0, 10, txt=str(today_date), ln=1, align='C')
# 1px= 0.264583mm
pdf.image('T1SD_result/Travel_Tracking.png', x=None, y=None, w=float(640 * 0.264583 * 0.7),
          h=float(480 * 0.264583 * 0.7))
pdf.image('T1SD_result/count_travel_range.png', x=None, y=None, w=float(640 * 0.264583 * 0.7),
          h=float(480 * 0.264583 * 0.7))
pdf.image('T1SD_result/Velocity.png', x=None, y=None, w=float(640 * 0.264583 * 0.7), h=float(480 * 0.264583 * 0.7))
pdf.image('T1SD_result/count_rspeed_range.png', x=None, y=None, w=float(640 * 0.264583 * 0.7),
          h=float(480 * 0.264583 * 0.7))
pdf.image('T1SD_result/count_cspeed_range.png', x=None, y=None, w=float(640 * 0.264583 * 0.7),
          h=float(480 * 0.264583 * 0.7))
pdf.cell(0, 10, txt="Settings for this test", ln=1)
pdf.image('T1SD_result/current_settings.png', x=None, y=None, w=float(425 * 0.264583), h=float(70 * 0.264583))
pdf.output('T1SD_result/'+pdf_title+'.pdf', 'F')

# DELETING INTERMEDIATE FILES
os.remove("T1SD_result/Travel_Tracking.png")
os.remove("T1SD_result/count_travel_range.png")
os.remove("T1SD_result/Velocity.png")
os.remove("T1SD_result/count_rspeed_range.png")
os.remove("T1SD_result/count_cspeed_range.png")
os.remove("T1SD_result/current_settings.png")
