#include <stdio.h>
#include <stdlib.h>
#include "opencv2/core.hpp"
#include "highgui.h"

int main( int argc, char** argv )
{  
    if (argc < 2)
    {
        printf("!!! Usage: ./program <filename>\n");
        return -1;
    }

    printf("* Filename: %s\n", argv[1]);   

    CvCapture *capture = cvCaptureFromAVI(argv[1]);
    if(!capture) 
    {
        printf("!!! cvCaptureFromAVI failed (file not found?)\n");
        return -1; 
    }

    int fps = (int) cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
    printf("* FPS: %d\n", fps);

    IplImage* frame = NULL;
    int frame_number = 0;
    char key = 0;   

    while (key != 'q') 
    {
        // get frame 
        frame = cvQueryFrame(capture);       
        if (!frame) 
        {
            printf("!!! cvQueryFrame failed: no frame\n");
            break;
        }       

        char filename[100];
        strcpy(filename, "frame_");

        char frame_id[30];
        frame_id = std::to_string(frame_id);
        //itoa(frame_number, frame_id, 10);
        strcat(filename, frame_id);
        strcat(filename, ".jpg");

        printf("* Saving: %s\n", filename);

        if (!cvSaveImage(filename, frame))
        {
            printf("!!! cvSaveImage failed\n");
            break;
        }

        frame_number++;

        // quit when user press 'q'
        key = cvWaitKey(1000 / fps);
    }

    // free resources
    cvReleaseCapture(&capture);

    return 0;
}