from imutils import paths
import argparse
import csv
import cv2
import imutils
import numpy as np
import os

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-i", "--image", required=True, help="path to input image")
args = vars(ap.parse_args())

# grab image filename
imageFilename = args["image"]

# load the image
image = cv2.imread(imageFilename)

# resize the image to a fixed size
image = cv2.resize(image, (64, 64))

# feature matrix
features = []

# image descriptor: color mean and standard deviation
means = cv2.mean(image)
stats = means[:3]



# add features
features.append(stats)

with open('tests2.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerows(features)
