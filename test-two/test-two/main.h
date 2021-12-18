#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>
#include<stdio.h>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/imgproc/imgproc_c.h>

#define PI 3.1415926;
#define R 55.0;	//中心圆的实际半径

using namespace cv;
using namespace std;

int find_hole(Mat pic1, Mat pic2, Mat framework, Mat show, int a[100][2], int HoleC);
void find_center(Mat pic1, int a[2]);
int calculate_loop(int a[100][2], int b[3], int HoleC);
void findh();