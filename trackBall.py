#!/usr/bin/env python3
# EML ???? Smart MAchine Design and Development
# Florida International University
# Department of Mechanical and Materials Engineering
# Jason Soto <jsoto103@fiu.edu>
# Miami, Spring 2018
 
import cv2 as cv
import numpy as np
import time
#import serial

#ser = serial.Serial('/dev/ttyACM0',9600) 	# 


# USER INPUTS ----------------------------------------------------------

pix_width  = 640
pix_height = 480

# FUNCTIONS ------------------------------------------------------------

# Define function that computes centroid of monochrome blob (mask)
def centroid( mask ):
	M = cv.moments(mask,True)
	m00 = M['m00']
	if m00 == 0: # Ops, don't want divide by zero!
		x = -100 
		y = -100
	else:
		x = int( M['m10']/m00 )
		y = int( M['m01']/m00 )
	return x,y

def weightfcn( x ):
	offset = x - 640/2
	weight = int( offset * 255/(640/2) )
	return weight
	

# PRIMARY LOOP --------------------------------------------------------- 

cap = cv.VideoCapture(0)		# Set up capture source (camera=0)

print("Press any key to exit...")
while True:
	# Exit if any key is pressed
	if cv.waitKey(1) > -1:
		break
	
	# Obtain Data
	okay, image = cap.read()    # Capture frame
	if okay == False:			# Skip frame if any capture error happened
		continue
	
	#ino_data = ser. readline() 			# Read Serial Data From Arduino (not working)
	
	# Image Processing
	hsv = cv.cvtColor(image, cv.COLOR_BGR2HSV)	# image from BGR to HSV color
	
	#color = 46 						# lime green color
	#color = 91 * (176/255)				# Brown/green Chip bag color
	color = 64 * (176/255) 				# Yellow bag color
	
	colorLower = (color - 20, 80, 80)
	colorUpper = (color + 20, 255, 255)
	
	mask = cv.inRange(hsv, colorLower, colorUpper)
	mask = cv.erode(mask, None, iterations = 2)
	mask = cv.dilate(mask, None, iterations = 2)
	
	
	
	# Data extraction
	x,y = centroid(mask)
	cv.circle(image, (x,y), 10, (0,0,255), 10)
	

	n_white_pix = np.sum(mask == 255)
	
	rows = len(mask)
	columns = len(mask[0])
	
	weight = weightfcn(x)
	
	# Publish Data
	
	# Feedback
	cv.imshow('EML4840: Video', image)
	cv.imshow('EML4840: Mask', mask)
	
	print('Number of white pixels:', n_white_pix)
	print('Centroid Location (X,Y)', [x,y])
	print('PWM Speed Weight       ', weight)
	
	print('Size of image box      ', [rows, columns])
	#print('Arduino Data'		   , ino_data)				# not working yet
	
	#print('Data array', [n_white_pix, x, y])
	
	# Slow video
	time.sleep(.01)

# Clean resources
cap.release()
cv.destroyAllWindows()
print("That's all folks!")
