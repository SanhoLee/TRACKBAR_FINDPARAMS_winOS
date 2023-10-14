# Contents
- [Background](#background)
- [How to work](#how-to-work)
- [Snapshots](#snapshots)
- [TODOs](#todos)

<br>

# Background
- OS : Windows11
- IDE : Visual Studio 2022 Community
- dependency : **opencv** for conventional computer vision process.
- Finding several parameters for pre-processing of an img when you want to get edge data of specifc area.
- Can be used with 2 different types of pre-processing in real-time,
    1) Finding parameters of Canny-edge algorithm method
    2) With HLS colored img, both max and min values of each boundaries(H,L,S) for masking could be identified. 

# How to work
1. Canny-Edge Trackbar : Just dragging either max or min threshold value on trackbar.
2. HLS Trackbar : ...
 

# Snapshots

1. Trackbar by [Canny-edge](https://docs.opencv.org/3.4/da/d5c/tutorial_canny_detector.html) algorithm method.
<br>

| Original Img  | ![imgOriginal](img/road.jpg) |
| :---: | :---: | 
| **Canny Img** | ![imgCanny](img/canny_edge_demo.gif) |
<br>

2. Trackbar by HLS algorithm method.
...


# Todos
- [x] make controller looks pretty -> integrating trackbar with the reuslt img on a single window.
- [x] make another window for checking original img.
- [x] getting Current File automatically or making dialog to get a source img.
- [ ] Do same process in case of HLS img(trackbar).
- [ ] organizing readme file
