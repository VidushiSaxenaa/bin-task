#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

void getContours(Mat imgDil, Mat img)
{ 

   vector<vector<Point>>contours;
   vector<Vec4i>hierarchy;

   findContours(imgDil,contours,hierarchy,RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
  
   
   //always above for loop
   vector<vector<Point>> conPoly(contours.size());//we need to define the size of it as it cannot exceed no. of contours 
   vector<Rect> boundRect(contours.size()); //boundRect is the variable whereas boundingRect is func to find the bounding box
 
   for(int i=0; i<contours.size(); i++)
   {
       int area=contourArea(contours[i]); //to find area so that we can sort req shape
       cout<< area<< endl; 

       
      if(area>4000)
       {
          float peri = arcLength(contours[i], true); //to find out perimeter
          approxPolyDP(contours[i],conPoly[i], 0.02*peri,true); //to analyse polygon based on perimeter
          drawContours(img,conPoly,i,Scalar(255,0,0),2);//to print only the req shapes
          //cout<< conPoly[i].size()<< endl;//to print no. of edges

          boundRect[i] = boundingRect(conPoly[i]);// this will draw the bounding box or will give the coordinates of the bounding box

             rectangle(img,boundRect[i].tl(),boundRect[i].br(),Scalar(0, 69, 255),5);//tl=top left||br=bottom right
//in rectagle function we can call top left and bottom right points 

       }


   }
}

int main()
{
    
    string path ="/home/vidushi/auv_bin/sample2.jpg";
    Mat img = imread (path);

    Mat imgResize;
    Mat imgHSV,mask;
    int hmin, smin, vmin;
    int hmax, smax, vmax;
    int area;
    char a;
    

    resize(img,imgResize, Size(640,480));
   
    cvtColor(imgResize,imgGray,COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3,3), 3,0);
    Canny(imgBlur, imgCanny, 25,75);  
    Mat kernel= getStructuringElement(MORPH_RECT, Size(5,5));
    dilate(imgCanny,imgDil,kernel);

    getContours(imgDil, imgResize);
       
    cvtColor(imgResize, imgHSV, COLOR_BGR2HSV);
    
    cout<<"Enter the char accoding to the choosen side"<<endl;
    cin>>a;
       
    if((a=='B')||(a=='b'))
  
   {   

       hmin=0, smin=101, vmin=153;
       hmax=19, smax=240, vmax=255;
       Scalar lower(hmin, smin, vmin);
       Scalar upper(hmax, smax, vmax);
       inRange(imgHSV, lower, upper, mask);
       imshow("Image mask", mask);
   }

    else if((a=='G')||(a=='g'))
 
   {   
       hmin=109, smin=116, vmin=75;
       hmax=179, smax=255, vmax=255;
       Scalar lower(hmin, smin, vmin);
       Scalar upper(hmax, smax, vmax);
       inRange(imgHSV, lower, upper, mask);
       imshow("Image mask", mask);   
   }
     

    
      //imshow("Image",   imgResize);
    //imshow("Image Gray", imgGray);
    //imshow("Image Blur", imgBlur);
    //imshow("Image Canny", imgCanny);//in canny img the fig has some gaps in the edges.
    //imshow("Image Dil", imgDil);// no gaps in dilated img hence is a better choice for img detection.
    
    waitKey(0);
}
      
   
