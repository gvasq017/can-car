#!/usr/bin/env python3
# EML 4840 Robot Design
# Florida International University
# Department of Mechanical and Materials Engineering
# Anthony Abrahao <aabra037@fiu.edu>
# Miami, Spring 2018
 
import cv2 as cv
import time

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

# Create a capture object from device number (or video file)
cap = cv.VideoCapture(0)
 
print("Press any key to exit...")
while True:
	# Exit if any key is pressed
	if cv.waitKey(1) > -1:
		break
	# Capture frame
	okay, image = cap.read()
	# Skip frame if any capture error happened (or video ended)
	if okay == False:
		continue
	# Convert frame image from BGR to HSV color space
	hsv = cv.cvtColor(image, cv.COLOR_BGR2HSV)
	
	#color = 91 * (176/255)
	color = 64 * (176/255)
	#color = 46 
	colorLower = (color - 20, 80, 80)
	colorUpper = (color + 20, 255, 255)
	
	mask = cv.inRange(hsv, colorLower, colorUpper)
	
	# Image Processing
	mask = cv.erode(mask, None, iterations = 4)
	mask = cv.dilate(mask, None, iterations = 4)
	
	x,y = centroid(mask)
	# Draw centroid over frame image
	cv.circle(image, (x,y), 10, (0,0,255), 10)
	
	# Feedback
	cv.imshow('EML4840: Video', image)
	cv.imshow('EML4840: Mask', mask)
	
	# Slow video
	time.sleep(.01)

# Clean resources
cap.release()
cv.destroyAllWindows()
print("That's all folks!")
