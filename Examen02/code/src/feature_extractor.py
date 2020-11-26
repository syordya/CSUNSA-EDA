from imutils import paths
import argparse
import csv
import cv2
import imutils
import numpy as np
import os

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-d", "--dataset", required=True, help="path to input dataset")
args = vars(ap.parse_args())

# grab the list of images that we'll be describing
print("[INFO] describing images...")
imagePaths = list(paths.list_images(args["dataset"]))

# feature matrix
features = [["meanB","meanG","meanR","stdevB","stdevG","stdevR","class"]]

# loop over the input images
for (i, imagePath) in enumerate(imagePaths):
    # load the image and extract the class label (assuming that our
    # path as the format: /path/to/dataset/{class}.{image_num}.jpg
    image = cv2.imread(imagePath)
    label = imagePath.split(os.path.sep)[-1].split(".")[0]

    # resize the image to a fixed size
    image = cv2.resize(image, (64, 64))

    # image descriptor: color mean and standard deviation
    (means, stds) = cv2.meanStdDev(image)
    stats = np.concatenate([means, stds]).flatten()

    stats = stats.tolist()
    stats.append(label)

    # add features
    features.append(stats)

    # show an update every 1,000 images
    if i > 0 and i % 1000 == 0:
        print("[INFO] processed {}/{}".format(i, len(imagePaths)))

with open('moche_vs_yuan-tests.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerows(features)
