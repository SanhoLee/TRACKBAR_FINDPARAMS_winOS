//original name : cannyEdge_trackbar.cpp

#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>
#include "commonFunction.hpp"
#include "variables.hpp"

using namespace std;

int main(int argc, char **argv)
{

    Mat imgSrc, imgBlur, imgCanny;
    int rtnKey = 0;

    // create window.
    namedWindow(TRACKBAR_CANNY, WINDOW_AUTOSIZE);
    namedWindow(WIN_IMG_ORIGIN, WINDOW_AUTOSIZE);

    // create new trackbar.
    createTrackbar("LOW", TRACKBAR_CANNY, &lowThres, 200);
    createTrackbar("HIGH", TRACKBAR_CANNY, &highThres, 200);

    while (true)
    {
        /* read origin img */
        imgSrc = imread(IMG_FILENAME);
        if (imgSrc.empty()) {
            cout << "IMG LOADED FAILED " << endl;
            return -1;
        }
       
        /* Blur img and Canny Edge function run. */
        GaussianBlur(imgSrc, imgBlur, Size(kernelSize, kernelSize), kernelSize, kernelSize);
        Canny(imgBlur, imgCanny, lowThres, highThres);

        // show origin and cannyEdge img.
        imshow(WIN_IMG_ORIGIN, imgSrc);
        imshow(TRACKBAR_CANNY, imgCanny);
        rtnKey = waitKey(1);

        // Release img data.
        imgSrc.release();
        imgCanny.release();

        /* save masked img when esc key is pressed. */
        if (rtnKey == 27)
        {
            destroyAllWindows();
            return 0;
        }
    }
    return 0;
}