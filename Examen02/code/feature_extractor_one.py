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
image = cv2.resize(image, (32, 32))

# feature matrix
features = []

# image descriptor: color mean and standard deviation
(means, stds) = cv2.meanStdDev(image)
stats = np.concatenate([means, stds]).flatten()

stats = stats.tolist()

# add features
features.append(stats)

with open('input.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerows(features)
