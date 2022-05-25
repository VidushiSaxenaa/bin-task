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
  
   
   
   vector<vector<Point>> conPoly(contours.size()); 
   vector<Rect> boundRect(contours.size()); 
 
   for(int i=0; i<contours.size(); i++)
   {
       int area=contourArea(contours[i]); 
       //cout<< area<< endl; 

       
       if(area > 10000)
       {
          float peri = arcLength(contours[i], true); 
          approxPolyDP(contours[i],conPoly[i], 0.000007*peri,true); 
          drawContours(img,conPoly,i,Scalar(255,0,0),5);
          //cout<< conPoly[i].size()<< endl;

          boundRect[i] = boundingRect(conPoly[i]);

             rectangle(img,boundRect[i].tl(),boundRect[i].br(),Scalar(0, 69, 255),5); 

       }


   }
}



int main()
{
   
    string path ="/home/vidushi/auv_bin/sample1.jpg";
    Mat img = imread (path);
    

    cvtColor(img,imgGray,COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3,3), 3,0);
    Canny(imgBlur, imgCanny, 25,75);  
    Mat kernel= getStructuringElement(MORPH_RECT, Size(5,5));
    dilate(imgCanny,imgDil,kernel);

    getContours(imgDil,img);

    imshow("Image", img);
    //imshow("Image Gray", imgGray);
    //imshow("Image Blur", imgBlur);
    //imshow("Image Canny", imgCanny);
    //imshow("Image Dil", imgDil);
    
    waitKey(0);
}
    
