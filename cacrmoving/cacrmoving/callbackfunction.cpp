#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cv.h>
#define PI 3.141592
using namespace cv;
using namespace std;

Mat src; 
int thresh = 100;
int max_thresh = 255;

/// Function header

/* @function main *//*
int main( int argc, char** argv )
{
  /// Load source image and convert it to gray
  src = imread("C:/opencv/samples/c/pca_test1.jpg");

  /// Convert image to gray and blur it
  cvtColor( src, src_gray, CV_BGR2GRAY );
  blur( src_gray, src_gray, Size(3,3) );

  /// Create Window
  char* source_window = "Source";
  namedWindow( source_window, CV_WINDOW_AUTOSIZE );
  imshow( source_window, src );

  createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
  thresh_callback( 0, 0 );

  waitKey(0);
  return(0);
}
*/
/* @function thresh_callback */
void thresh_callback(int, Mat src_gray )
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using canny
  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
  /// Get the moments
  vector<Moments> mu(contours.size() );
  for( int i = 0; i < contours.size(); i++ )
     { mu[i] = moments( contours[i], false ); }

  ///  Get the mass centers:
  vector<Point2f> mc( contours.size() );
  for( int i = 0; i < contours.size(); i++ )
     { mc[i] = Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ); }
  

  // Get orientation
  /* vector<Point3f>mo(contours.size());	*/
   for( int i = 0; i < contours.size(); i++ )
	 { 
  		double theta = 0.5*atan2(2 * mu[i].mu11,(mu[i].mu20-mu[i].mu02));////////////?????????????????? atan2(2*Ixy/(Ixx-Iyy);
	
		Scalar color = Scalar(0, 0, 1);
		drawContours( src_gray, contours, i, color, 2, 8, hierarchy, 0, Point() );
	    circle( src_gray, mc[i], 4, color, -1, 8, 0 );
  
	   //draw center line
	 line(src_gray
		 ,Point(mc[i].x,mc[i].y)-Point(100*cos(theta),100*sin(theta)),
		 Point(mc[i].x, mc[i].y)+Point(100*cos(theta), 100*sin(theta)),
		 Scalar(255,0,0),2); 
   
   }
    
  /// Draw contours
 


  /// Show in a window

  /// Calculate the area with the moments 00 and compare with the result of the OpenCV function

}