/**************************************************

file: main.c
purpose: simple demo that receives characters from
the serial port and print them on the screen

**************************************************/
//지그비 모터 제어 01   ,46
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "rs232.h"
#include "zigbee.h"
#include <cv.h>
#pragma warning(disable:4996)
//opencv 헤더
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "myhead.h"
using namespace cv;
using namespace std;
#define PI 3.141592




Mat hsv,threshhsv,src_gray;
int cport_nr=8,        /* /dev/ttyS0 (COM1 on windows) */
      bdrate=115200;       /* 9600 baud */
int flag=0;
Mat image; 
struct carstruct
{
	char name[17];
};
carstruct car;

void thresh_callback(int, void* );

void moving_callback(int control)
{
    switch(control)
   {
   case 119: ahead(car.name,cport_nr);  break; //ascii 'w'
   case 115: back(car.name,cport_nr); break;  //ascii 's'
   case 120: stop(car.name,cport_nr); break;   //ascii 'x'
   case 97: turnleft(car.name,cport_nr); break;//ascii 'a'
   case 100: turnright(car.name,cport_nr); break;//ascii 'd'
   default: break;
   }   
}



void main(int argc, char** argv)
{
//////////////////////////////////
  int control=0;
  Mat imgOut;
 if(RS232_OpenComport(cport_nr, bdrate))
  {
    printf("Can not open comport\n");
  }
 strcpy((char*)car.name,"0001950000005427");
////////////// RS 232 port 열기


 //////////// opencv 설정창
	VideoCapture san_cap("http://192.168.233.101:8000/videofeed?something.mjpeg");  
	namedWindow("src");
 
/////////////////

   while(true)
  {  
    san_cap.read(image);
    imshow("src",image);

    cvtColor( image, src_gray, CV_BGR2GRAY );
    blur( src_gray, src_gray, Size(3,3) );
     thresh_callback( 0, src_gray );
    imshow("blur",src_gray);


    ///////자동차 이동
 control=waitKey(10); 
 moving_callback(control);
////////
  }
}