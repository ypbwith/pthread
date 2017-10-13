#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(){

  // Create a VideoCapture object and use camera to capture the vide
  VideoCapture cap_2(2);
  VideoCapture cap_1(1); 
  VideoCapture cap_0(0);
  
  cap_2.set(CAP_PROP_FRAME_WIDTH,640);
  cap_2.set(CAP_PROP_FRAME_HEIGHT,480);
  cap_2.set(CAP_PROP_FPS ,5);
  //cap_2.set(CAP_V4L2,0); 
  cap_1.set(CAP_PROP_FRAME_WIDTH,640);
  cap_1.set(CAP_PROP_FRAME_HEIGHT,480);
  cap_1.set(CAP_PROP_FPS ,5);
  //cap_1.set(CAP_V4L2,0); 
  cap_0.set(CAP_PROP_FRAME_WIDTH,640);
  cap_0.set(CAP_PROP_FRAME_HEIGHT,480);
  cap_0.set(CAP_PROP_FPS ,5);
  //cap_0.set(CAP_V4L2,0); 


  // Check if camera opened successfully
  
   if(!cap_2.isOpened())
    {
        cout << "Error opening video stream cap_2" << endl;
        return -1;
    }
   if(!cap_1.isOpened())
   {
   	cout << "Error opening video stream cap_1" << endl;
        return -1;
   }
  
  if(!cap_0.isOpened())
  {
        cout << "Error opening video stream cap_0" << endl;
        return -1;
  }
 

  // Default resolutions of the frame are obtained.The default resolutions are system dependent.

  
   
  printf("%f:",cap_0.get(CAP_PROP_BUFFERSIZE ));

   int frame_width = cap_0.get(CV_CAP_PROP_FRAME_WIDTH);
   int frame_height = cap_0.get(CV_CAP_PROP_FRAME_HEIGHT);
  // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.
  
  VideoWriter video_2("out_2.avi",CV_FOURCC('M','J','P','G'),10,Size(frame_width,frame_height));
  VideoWriter video_1("out_1.avi",CV_FOURCC('M','J','P','G'),10,Size(frame_width,frame_height));
  VideoWriter video_0("out_0.avi",CV_FOURCC('M','J','P','G'),10,Size(frame_width,frame_height));

  while(1){

    Mat frame_2;
    Mat frame_1;
    Mat frame_0;
    // Capture frame-by-frame
    cap_2 >> frame_2;
    cap_1 >> frame_1;
    cap_0 >> frame_0;
    // If the frame is empty, break immediately
	
    if (frame_2.empty())
      break;
    if (frame_1.empty())
      break;
    if (frame_0.empty())
       break;    
    // Write the frame into the file 'outcpp.avi'
    video_2.write(frame_2);
    video_1.write(frame_1);
    video_0.write(frame_0);
    // Display the resulting frame   
    imshow("f2",frame_2);
    imshow( "f1", frame_1 );
   imshow("f0",frame_0);    
 

    // Press  ESC on keyboard to  exit
    char c = (char)waitKey(1);
    if( c == 27 ) 
      break;
  }

  // When everything done, release the video capture and write object
  cap_2.release();
  cap_1.release();
  cap_0.release();
  video_2.release();
  video_1.release();
  video_0.release();

  // Closes all the frames
  destroyAllWindows();
  return 0;

}
