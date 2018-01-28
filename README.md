# webcam_circles
Circle detection from online webcam images

# The Hough Transformation

The Hough transformation is used in order to detect lines or circles

The circles Hough transformation is the one performed in this code and it detects a circle and also shows the center.

This method could be applied in two ways. For a fixed radius or the radius is unknown.

The code is able to detect two diferent circle, the ones with variable radius are detected and drawn blue. With a fix radius, 5 is its value, are drawn red. In this case there is a condition with which the circle will be filled. (When the thickness is negative).

Before this, three steps are done:
  - The image must be converted into grey scale.
  - Afterwards is used a filter in order to reduce the number of circles which could be wrong.
  - Finally the Hough transformation is aplied. The function need the grey-scale image and a parameter with which we select the Hough           transform method. This function will return an array with the information needed for drawing the circles.

