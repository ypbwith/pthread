/*thread_example.c :  c multiple thread programming in linux
  *author : falcon
  *E-mail : tunzhj03@st.lzu.edu.cn
  */
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "opencv2/opencv.hpp"
//#define MAX 1000

using namespace std;
using namespace cv;

pthread_t thread[2];
pthread_mutex_t mut;
int number=0, i;

 void *thread1(void *)
{
        printf ("thread1 : I'm thread 1\n");

/*   
        for (i = 0; i < MAX; i++)
        {
                printf("thread1 : number = %d\n",number);
                pthread_mutex_lock(&mut);
                        number++;
                pthread_mutex_unlock(&mut);
                //sleep(2);
        }
*/

        // Create a VideoCapture object and use camera to capture the video
        VideoCapture cap(1); 
      
        // Check if camera opened successfully
        if(!cap.isOpened()){
         	cout << "Error opening video stream" << endl;
           
        }
        
        // Default resolutions of the frame are obtained.The default resolutions are system dependent.
        int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
        
        // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.
        VideoWriter video("outcpp.avi",CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height));
      
        while(1){
      
          Mat frame;
         
          // Capture frame-by-frame
          cap >> frame;
       
          // If the frame is empty, break immediately
          if (frame.empty())
            break;
          
          // Write the frame into the file 'outcpp.avi'
          video.write(frame);
         
          // Display the resulting frame    
          imshow( "Frame", frame );
       
          // Press  ESC on keyboard to  exit
          char c = (char)waitKey(1);
          if( c == 27 ) 
            break;
        }
      
        // When everything done, release the video capture and write object
        cap.release();
        video.release();
      
        // Closes all the frames
        destroyAllWindows();
       
        printf("thread1:~~~~~\n");
        pthread_exit(NULL);
}

 void *thread2( void *)
{
        printf("thread2 : I'm thread 2\n");

/*  
        for (i = 0; i < MAX; i++)
        {
                printf("thread2 : number = %d\n",number);
                pthread_mutex_lock(&mut);
                        number++;
                pthread_mutex_unlock(&mut);
                //sleep(3);
        }
*/

       // Create a VideoCapture object and use camera to capture the video
        VideoCapture cap(0); 
      
        // Check if camera opened successfully
        if(!cap.isOpened()){
         	cout << "Error opening video stream" << endl;
           
        }
        
        // Default resolutions of the frame are obtained.The default resolutions are system dependent.
        int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
        int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
        
        // Define the codec and create VideoWriter object.The output is stored in 'outcpp.avi' file.
        VideoWriter video("outcpp1.avi",CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height));
      
        while(1){
      
          Mat frame;
         
          // Capture frame-by-frame
          cap >> frame;
       
          // If the frame is empty, break immediately
          if (frame.empty())
            break;
          
          // Write the frame into the file 'outcpp.avi'
          video.write(frame);
         
          // Display the resulting frame    
          imshow( "Frame1", frame );
       
          // Press  ESC on keyboard to  exit
          char c = (char)waitKey(1);
          if( c == 27 ) 
            break;
        }
      
        // When everything done, release the video capture and write object
        cap.release();
        video.release();
      
        // Closes all the frames
        destroyAllWindows();
       
       
        printf("thread2 :~~~~~~~~~~~~~~~~\n");
        pthread_exit(NULL);
}

void thread_create(void)
{
        int temp;
        memset(&thread, 0, sizeof(thread));          //comment1
        /*创建线程*/
        if((temp = pthread_create(&thread[0], NULL, thread1, NULL)) != 0)  //comment2     
                printf("thread1 failure\n");
        else
                printf("thread1 created\n");

        if((temp = pthread_create(&thread[1], NULL, thread2, NULL)) != 0)  //comment3
                printf("thread2 failure\n");
        else
                printf("thread2 created\n");
}

void thread_wait(void)
{
        /*等待线程结束*/
        if(thread[0] !=0)
           {             //comment4    
                pthread_join(thread[0],NULL);
                printf("thread1 over\n");
          }
        if(thread[1] !=0) 
           {  
                //comment5
               pthread_join(thread[1],NULL);
                printf("thread2 over\n");
         }
}

int main()
{
        /*用默认属性初始化互斥锁*/
        pthread_mutex_init(&mut,NULL);

        printf("Main\n");
        thread_create();
        printf("Main\n");
        thread_wait();

        return 0;
}

