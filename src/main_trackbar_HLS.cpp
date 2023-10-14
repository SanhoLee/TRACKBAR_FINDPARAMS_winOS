#include <iostream>
#include <string>
#include <filesystem>
#include "commonFunction.hpp"
#include "variables.hpp"

using namespace std;

int main(int argc, char **argv)
{

    Mat imgSrc, imgHLS, imgMasked;
    int rtnKey = 0;

    // create window.
    namedWindow(TRACKBAR_HLS, WINDOW_AUTOSIZE);
    namedWindow(WIN_IMG_ORIGIN, WINDOW_AUTOSIZE);


    // create new trackbar.
    createTrackbar("hmin : ", TRACKBAR_HLS, &hmin, 179);
    createTrackbar("lmin : ", TRACKBAR_HLS, &lmin, 255);
    createTrackbar("smin : ", TRACKBAR_HLS, &smin, 255);
    createTrackbar("hmax : ", TRACKBAR_HLS, &hmax, 179);
    createTrackbar("lmax : ", TRACKBAR_HLS, &lmax, 255);
    createTrackbar("smax : ", TRACKBAR_HLS, &smax, 255);

    while (true)
    {
        // read origin img
        imgSrc = imread(IMG_FILENAME);
        if (imgSrc.empty()) {
            cout << "IMG LOADED FAILED " << endl;
            return -1;
        }

        // convert color space to HLS.
        cvtColor(imgSrc, imgHLS, COLOR_BGR2HLS);

        // masking img with specific color elements.
        Scalar lowerb_(hmin, lmin, smin);
        Scalar upperb_(hmax, lmax, smax);
        inRange(imgHLS, lowerb_, upperb_, imgMasked);

        // show current masking color boundary.
        show_HLSValue(hmin, lmin, smin, hmax, lmax, smax);

        // show origin and masked img.
        imshow(WIN_IMG_ORIGIN, imgSrc);
        imshow(TRACKBAR_HLS, imgMasked);
        rtnKey = waitKey(1);

        // Release img data.
        imgSrc.release();
        imgMasked.release();

        // save masked img when esc key is pressed.
        if (rtnKey == 27)
        {
            destroyAllWindows();
            return 0;
        }
    }
    return 0;
}