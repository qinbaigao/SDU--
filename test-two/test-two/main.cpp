/*
缺少细化函数
*/
#include"main.h"

int high = 1500;//截取图像的高
int wide = 1500;//截取图像的宽
int loop;		//环数
int holecount = 0;	//弹孔数量
int hole_coordinate[100][2] = { 0 };	//弹孔坐标x,y 
int center_coordinate1[3] = { 0,0,0 };	//src1中心圆坐标与半径
int center_coordinate2[3] = { 0,0,0 };	//src2中心圆坐标与半径
double d_htc, d_htc_true;	//弹孔到中心的像素距离，弹孔到中心的真实距
double r;	//中心圆的像素半径

int main()
{


	Mat src1, src2, show;	//上一帧图片，此帧图片，效果图图片
	Mat frame, frame_p, frame_pp, h, im_out;
	Mat size(626, 630, CV_8UC1);	//创建一个高200，宽100的灰度图
	//src1 = imread("pre2.jpg");
	//src2 = imread("pre1.jpg");
	Mat framework = imread("formwork2.jpg");	//读取模板图
	int firstframe = 1, framecount = 0, holecount = 0;
	//imshow("yuantu", src1);
	//imshow("dankongtu", src2);
	//src1.copyTo(show1);
	//src2.copyTo(show2);

	

	VideoCapture capture("1.MOV");

	while(1)
	{
		int delay = 1;
		Rect rect1(660, 190, 580, 570);

		if (firstframe == 0)
		{
			frame.copyTo(frame_p);
			show = frame(rect1);
		}
		capture >> frame;
		framecount++;
		cout << "这是第" << framecount << "帧视频" << endl;
		imshow("这一帧视频", frame);

	//图像不正使用仿射变换，正直接扣	
	/*vector<Point2f> pts_src;
	pts_src.push_back(Point2f(630, 184));
	pts_src.push_back(Point2f(1260, 184));
	pts_src.push_back(Point2f(630, 810));
	pts_src.push_back(Point2f(1260, 810));
	vector<Point2f> pts_dst;
	pts_dst.push_back(Point2f(0, 0));
	pts_dst.push_back(Point2f(630, 0));
	pts_dst.push_back(Point2f(0, 626));
	pts_dst.push_back(Point2f(630, 626));
	h = findHomography(pts_src, pts_dst);
	warpPerspective(frame, im_out, h, size.size());*/
		
		src1 = frame(rect1);
		if (firstframe == 0)
		{
			src2 = frame_p(rect1);

			find_center(src1, center_coordinate2);
			holecount = find_hole(src1, src2, framework, show, hole_coordinate, holecount);

			//loop = calculate_loop(hole_coordinate, center_coordinate2, holecount);

			cout << "loop = " << loop << endl;
			cout << "弹孔坐标为：" << hole_coordinate[holecount][0] << "," << hole_coordinate[holecount][1] << endl;
			cout << "弹孔数量为：" << holecount << endl;
			cout << "圆心坐标为：" << center_coordinate2[0] << "," << center_coordinate2[1] << endl;
			cout << "中心圆半径为：" << center_coordinate2[2] << endl;


		}


		if (delay >= 0 && waitKey(delay) >= 0)	
			waitKey();

		if (holecount > 0)//找到一个弹孔暂停
			waitKey();

		if (firstframe == 1)
			firstframe = 0;
	}


	
}