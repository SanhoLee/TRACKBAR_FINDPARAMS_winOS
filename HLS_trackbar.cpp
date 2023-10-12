#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>
#include "commonFunction.hpp"
#include "variables.hpp"

using namespace std;

int main(int argc, char **argv)
{
    char curPath[256];
    char imgSrcPath[256];
    char imgReadPath[256];
    char imgOutPath[256];

    char srcDir[100];
    char hlsOutDir[100];

    Mat img, imgHLS, imgMasked;
    int rtnKey = 0;

    memset(curPath, 0, sizeof(curPath));
    getcwd(curPath, sizeof(curPath));

    // get filename.
    if (argc == 0)
    {
        cout << " INPUT ERROR :: ARGUMENT NUMBER : 0 " << endl;
        return -1;
    }
    else if (argc != 2)
    {
        cout << " INPUT ERROR :: ARGUMENT NUMBER SHOULD BE 2. " << endl;
        cout << " INPUT ERROR :: ARGUMENT NUMBER : " << argc << endl;
        return -1;
    }
    else
    {
        memset(imgSrcPath, 0, sizeof(imgSrcPath));
        memset(imgReadPath, 0, sizeof(imgReadPath));
        memset(imgOutPath, 0, sizeof(imgOutPath));
        memset(srcDir, 0, sizeof(srcDir));
        memset(hlsOutDir, 0, sizeof(hlsOutDir));

        strcpy(srcDir, "/data/imgSRC/");
        strcpy(hlsOutDir, HLS_outDIR);

        makeTargetPath(curPath, srcDir, imgSrcPath);
        makeTargetPath(curPath, hlsOutDir, imgOutPath);
        makeTargetPath(imgSrcPath, argv[1], imgReadPath);
    }

    // create window.
    namedWindow(HLS_TRACKBAR, WINDOW_NORMAL);

    // create new trackbar.
    createTrackbar("hmin : ", HLS_TRACKBAR, &hmin, 179);
    createTrackbar("lmin : ", HLS_TRACKBAR, &lmin, 255);
    createTrackbar("smin : ", HLS_TRACKBAR, &smin, 255);
    createTrackbar("hmax : ", HLS_TRACKBAR, &hmax, 179);
    createTrackbar("lmax : ", HLS_TRACKBAR, &lmax, 255);
    createTrackbar("smax : ", HLS_TRACKBAR, &smax, 255);

    while (true)
    {
        // read origin img
        img = imread(imgReadPath);
        if (isImgEmpty(img, imgReadPath))
        {
            return 0;
        }

        // convert color space to HLS.
        cvtColor(img, imgHLS, COLOR_BGR2HLS);

        // masking img with specific color elements.
        Scalar lowerb_(hmin, lmin, smin);
        Scalar upperb_(hmax, lmax, smax);
        inRange(imgHLS, lowerb_, upperb_, imgMasked);

        // show current masking color boundary.
        show_HLSValue(hmin, lmin, smin, hmax, lmax, smax);

        // show masked img.
        imshow("imgMasked", imgMasked);
        rtnKey = waitKey(1);

        // save masked img when esc key is pressed.
        if (rtnKey == 27)
        {
            strcat(imgOutPath, HLS_OUTPUT);
            imwrite(imgOutPath, imgMasked);
            return 0;
        }
    }
    return 0;
}