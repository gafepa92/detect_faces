
//OpenCV
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/objdetect.hpp"
//#include "opencv2/highgui.hpp"


#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"



//std
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stdio.h>

/*//constants
const int GAUSSIAN_BLUR_SIZE = 7;
const double GAUSSIAN_BLUR_SIGMA = 2;
const double CANNY_EDGE_TH = 150;
const double HOUGH_ACCUM_RESOLUTION = 2;
const double MIN_CIRCLE_DIST = 40;
const double HOUGH_ACCUM_TH = 70;
const int MIN_RADIUS = 20;
const int MAX_RADIUS = 80;*/

/** Global variables */
/*download face detector file from build folder*/
cv::String face_cascade_name = "haarcascade_frontalface_default.xml";
cv::CascadeClassifier face_cascade;
/*name of the web_cam window opened*/
cv::String window_name = "Capture - Face detection";
/*variables needed in order to do the detection of the eyes
In order to do so it's necessary to download the eyes detect file from the opencv library*/
//cv::String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
//cv::CascadeClassifier eyes_cascade;

int main(int argc, char *argv[])
{
    cv::VideoCapture camera; //OpenCV video capture object
    cv::Mat image; //OpenCV image object
	  int cam_id; //camera id . Associated to device number in /dev/videoX
    std::vector<cv::Rect> faces; //vector in which data abaout the faces will be saved
    cv::Mat gray_image;// gray image for detecting data
    /*std::vector<cv::Vec3f> circles;
    cv::Point center;*/
    int radius;
    //download the file from build folder in our repository. if file not found the code is over
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
	//check user args detect web_cam
	switch(argc)
	{
		case 1: //no argument provided, so try /dev/video0
			cam_id = 0;
			break;
		case 2: //an argument is provided. Get it and set cam_id
			cam_id = atoi(argv[1]);
			break;
		default:
			std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl;
			std::cout << "EXIT program." << std::endl;
			break;
	}

	//advertising to the user
	std::cout << "Opening video device " << cam_id << std::endl;

    //open the video stream and make sure it's opened
    if( !camera.open(cam_id) )
	 {
        std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    //Process loop. Capture and point feature extraction. User can quit pressing a key
    while(1)
	 {
		//Read image and check it. Blocking call up to a new image arrives from camera.
        if(!camera.read(image))
		    {
            std::cout << "No image" << std::endl;
            cv::waitKey();
        }
    //**************** Find circles in the image ****************************

        //clear previous circles
        //circles.clear();

        // If input image is RGB, convert it to gray
        cv::cvtColor(image, gray_image, CV_BGR2GRAY);
        cv::equalizeHist(gray_image,gray_image);
        //Reduce the noise so we avoid false circle detection filter
        //cv::GaussianBlur( gray_image, gray_image, cv::Size(GAUSSIAN_BLUR_SIZE, GAUSSIAN_BLUR_SIZE), GAUSSIAN_BLUR_SIGMA );
        //-- Detect faces
        face_cascade.detectMultiScale(gray_image, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30) ); //CV_HAAR_SCALE_IMAGE CASCADE_SCALE_IMAGE
        //Apply the Hough Transform to find the circles
	      // third parameter is used to select the Hough method HOUGH_STANDARD,HOUGH_PROBABILISTIC, 		HOUGH_MULTI_SCALE & HOUGH_GRADIENT
        //cv::HoughCircles( gray_image, circles, CV_HOUGH_GRADIENT, HOUGH_ACCUM_RESOLUTION, MIN_CIRCLE_DIST, CANNY_EDGE_TH, HOUGH_ACCUM_TH, MIN_RADIUS, MAX_RADIUS );

        //draw circles on the image
        for(unsigned int ii = 0; ii < faces.size(); ii++ )
        {
          cv::Point center(faces[ii].x + faces[ii].width/2, faces[ii].y + faces[ii].height/2);
          cv::ellipse(image, center, cv::Size(faces[ii].width/2, faces[ii].height/2), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
          //cv::Mat faceROI = gray_image(faces[i]);
            /*        cv::circle(image, center, 5, cv::Scalar(0,0,255), -1, 8, 0 );// circle center in green
                    cv::circle(image, center, radius, cv::Scalar(0,255,0), -1, 8, 0 );
		    // *///circle perimeter in red (0,0,x) green (0,x,0) blue (x,0,0)
        }

    //********************************************************************

        //show image
        cv::imshow("Output Window", image);
        //cv::imshow(window_name, image);
		//Waits 1 millisecond to check if a key has been pressed. If so, breaks the loop. Otherwise continues.
        if( (unsigned char)(cv::waitKey(30) & 0xff) == 'q' ) break; //line modified as it is in the others files
    }
}
