#include"main.h"

int find_hole(Mat pic1, Mat pic2, Mat framework, Mat show, int a[100][2], int HoleC)
{
	Mat dst; 
	Mat p1, p2, temp;
	pic1.copyTo(p1); 
	pic2.copyTo(p2);
	framework.copyTo(temp);
	//imshow("temp", temp);
	Rect rect;
	Mat elementC = getStructuringElement(2, Size(5, 5));	//0：矩形 1：十字形 2：椭圆形
	Mat elementO = getStructuringElement(2, Size(3, 3));
	//imshow("p1", p1);
	//imshow("p2", p2);

	//先做差后转灰度，先转灰度后做差有待试验
	//absdiff(p1, p2, dst);
	//cvtColor(dst, dst, CV_BGR2GRAY);
	cvtColor(p1, p1, CV_BGR2GRAY);            
	cvtColor(p2, p2, CV_BGR2GRAY);   
	absdiff(p1, p2, dst);
	imshow("帧差",dst);
	//是否需要滤波有待试验
	//medianBlur(dst, dst, 5);	//中值滤波
	//GaussianBlur(dst, dst, Size(5, 5), 0);	//高斯滤波去除小噪点

	//运用那种二值化方法有待试验
	threshold(dst, dst, 180, 255, THRESH_BINARY);
	//adaptiveThreshold(dst, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 7, 0);//自动阈值分割，高斯邻域
	//threshold(dst, dst, 0, 255, THRESH_OTSU);	//最大类间方差法分割
	imshow("帧差二值化", dst);

	morphologyEx(dst, dst, CV_MOP_OPEN, elementO);	//开运算，去除小白点，去噪
	morphologyEx(dst, dst, CV_MOP_CLOSE, elementC);	//闭运算，去除小黑点，使弹孔更加饱满	
	imshow("提取弹孔", dst);
	//imwrite("dankong.jpg", dst);

	//模板匹配（单个）
	//1.构建结果图像resultImg(注意大小和类型)
	//如果原图(待搜索图像)尺寸为W x H, 而模版尺寸为 w x h, 则结果图像尺寸一定是(W-w+1)x(H-h+1)
	//结果图像必须为单通道32位浮点型图像
	int width = dst.cols - temp.cols + 1;
	int height = dst.rows - temp.rows + 1;
	Mat matchresult(Size(width, height), CV_32FC1);
	//2.模版匹配
	cvtColor(dst, dst, CV_GRAY2BGR);
	matchTemplate(dst, temp, matchresult, 5);
	//3.正则化(归一化到0-1)
	normalize(matchresult, matchresult, 0, 1, NORM_MINMAX, -1);
	//4.遍历resultImg，给定筛选条件，筛选出前几个匹配位置
	int tempX = 0, tempY = 0;
	int maxX = 0, maxY = 0;
	double maxValue = 0;
	for (int i = 0; i < matchresult.rows; i++)		//列
	{
		for (int j = 0; j < matchresult.cols; j++)	//行
		{
			//获得resultImg中(j,x)位置的匹配值matchValue
			double matchValue = matchresult.at<float>(i, j);
			//任何选中的点在x方向和y方向上都要比上一个点大3(避免画边框重影的情况)
			if (matchValue > 0.98)
			//if (matchValue > 0.92&& abs(i - tempY) > 3 && abs(j - tempX) > 3)
			{
				//5.给筛选出的点画出边框
				rectangle(show, Point(j, i), Point(j + temp.cols, i + temp.rows), Scalar(0, 255, 0), 1, 8);
				imshow("dankong", show);
				tempX = j;
				tempY = i;
				if (maxValue < matchValue) 
					{
						maxValue = matchValue;
						maxX = tempX;
						maxY = tempY;
					}

			}
		}
	}
	rectangle(show, Point(maxX, maxY), Point(maxX + temp.cols, maxY + temp.rows), Scalar(0, 0, 255), 1, 8);
	cout << "maxvalue=" << maxValue << ", maxX=" << maxX << ", maxY=" << maxY << endl;
	
	//模板匹配（多个）
	//int n;
	//Mat temp1 = imread("");	//读取模板图1
	//Mat temp2 = imread("");	//读取模板图2
	////1.构建结果图像resultImg(注意大小和类型)
	////如果原图(待搜索图像)尺寸为W x H, 而模版尺寸为 w x h, 则结果图像尺寸一定是(W-w+1)x(H-h+1)
	////结果图像必须为单通道32位浮点型图像
	//int width1 = dst.cols - temp1.cols + 1;
	//int height1 = dst.rows - temp1.rows + 1;
	//Mat matchresult1(Size(width1, height1), CV_32FC1);
	//int width2 = dst.cols - temp2.cols + 1;
	//int height2 = dst.rows - temp2.rows + 1;
	//Mat matchresult2(Size(width2, height2), CV_32FC1);
	////2.模版匹配
	//matchTemplate(dst, temp1, matchresult1, 5);
	//matchTemplate(dst, temp1, matchresult2, 5);
	////3.正则化(归一化到0-1)
	//normalize(matchresult1, matchresult1, 0, 1, NORM_MINMAX, -1);
	//normalize(matchresult2, matchresult2, 0, 1, NORM_MINMAX, -1);
	////4.遍历resultImg，给定筛选条件，筛选出前几个匹配位置
	//int tempX = 0, tempY = 0;
	//int maxX = 0, maxY = 0;
	//double maxValue = 0;
	//for (n = 1; n < 3; n++)
	//{	
	//	if (n == 1)
	//	{
	//		for (int i = 0; i < matchresult1.rows; i++)
	//		{
	//			for (int j = 0; j < matchresult1.cols; j++)
	//			{
	//				//获得resultImg中(j,x)位置的匹配值matchValue
	//				double matchValue = matchresult1.at<float>(i, j);
	//				//任何选中的点在x方向和y方向上都要比上一个点大5(避免画边框重影的情况)
	//				if (matchValue > 0.85&& abs(i - tempY) > 5 && abs(j - tempX) > 5)
	//				{
	//					//5.1给筛选出的点画出边框
	//					rectangle(dst, Point(j, i), Point(j + temp1.cols, i + temp1.rows), Scalar(0, 255, 0), 1, 8);
	//					tempX = j;
	//					tempY = i;
	//					if (maxValue < matchValue)
	//					{
	//						maxValue = matchValue;
	//						maxX = tempX;
	//						maxY = tempY;
	//					}
	//				}
	//			}
	//		}
	//	}
	//	if (n == 2)
	//	{
	//		for (int i = 0; i < matchresult1.rows; i++)
	//		{
	//			for (int j = 0; j < matchresult1.cols; j++)
	//			{
	//				//获得resultImg中(j,x)位置的匹配值matchValue
	//				double matchValue = matchresult1.at<float>(i, j);
	//				//任何选中的点在x方向和y方向上都要比上一个点大5(避免画边框重影的情况)
	//				if (matchValue > 0.85&& abs(i - tempY) > 5 && abs(j - tempX) > 5)
	//				{
	//					//5.2给筛选出的点画出边框
	//					rectangle(dst, Point(j, i), Point(j + temp1.cols, i + temp1.rows), Scalar(0, 0, 255), 1, 8);
	//					tempX = j;
	//					tempY = i;
	//					if (maxValue < matchValue)
	//					{
	//						maxValue = matchValue;
	//						maxX = tempX;
	//						maxY = tempY;
	//					}
	//				}
	//			}
	//		}
	//	}		
	//}
	
	//传递最有可能是弹孔的点的坐标
	
	if (maxValue > 0.9)
	{
		HoleC++;
		a[HoleC][0] = maxX + temp.cols / 2;
		a[HoleC][1] = maxY + temp.rows / 2;
	}
	return HoleC;
}

void find_center(Mat pic1, int a[2])
{
	Mat p1;
	pic1.copyTo(p1);
	Mat elementO = getStructuringElement(2, Size(5, 5));
	Mat elementC = getStructuringElement(2, Size(19, 19));

	//先转灰度后滤波还是先滤波后转灰度有待试验

	cvtColor(p1, p1, CV_BGR2GRAY);

	//运用那种滤波方法有待试验
	medianBlur(p1, p1, 3);	//中值滤波
	//GaussianBlur(dst, dst, Size(5, 5), 0);	//高斯滤波去除小噪点
	//imshow("灰度", p1);

	//运用那种二值化方法有待试验
	threshold(p1, p1, 127, 255, THRESH_BINARY);
	//adaptiveThreshold(p1, p1, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, 0);//自动阈值分割，高斯邻域
	//threshold(p1, p1, 0, 255, THRESH_OTSU);	//最大类间方差法分割
	//imshow("二值化", p1);

	//只有开闭运算可能不能得到完美的图像，在此之前可加入细化算y法，对环线与数字进行细化，但细化会降低实时性
	morphologyEx(p1, p1, CV_MOP_CLOSE, elementC);	//大规模闭运算，去除数字10
	morphologyEx(p1, p1, CV_MOP_OPEN, elementO);	//大规模开运算，去除环线与数字
	
	//imshow("大白圆", p1);
	vector<Vec3f> circles;	//检测到圆的存储仓，三个浮点数：圆心坐标(x,y)和半径.
	HoughCircles(p1, circles, HOUGH_GRADIENT, 1.5, 20, 120, 20, 52, 54);
	for (int i = 0; i < circles.size(); i++)
	{

		Vec3f c;
		c = circles[i];
		circle(pic1, Point(cvRound(c[0]), cvRound(c[1])), 3, Scalar(0, 255, 50), 2);	//cvRound():返回跟参数最接近的整数值,即四舍五入
		circle(pic1, Point(cvRound(c[0]), cvRound(c[1])), cvRound(c[2]), Scalar(0, 255, 50), 2, 8, 0);
		printf("第%d个圆圆心坐标为:（%d,%d）,半径为：%d\n", i + 1, cvRound(c[0]), cvRound(c[1]), cvRound(c[2]));
		//imshow("pic1", pic1);
		//传递圆心坐标与半径
		if (circles.size() < 2)
		{
			a[0] = cvRound(c[0]);	
			a[1] = cvRound(c[1]);
			a[2] = cvRound(c[2]);
		}
		
	}	
}

int calculate_loop(int a[100][2], int b[3], int HoleC)//a:弹孔坐标，b:中心圆圆心坐标与半径
{
	double dis = 0, dis_true, z;
	dis = (double)sqrt((a[HoleC][0] - b[0])*(a[HoleC][0] - b[0]) + (a[HoleC][1] - b[1])*(a[HoleC][1] - b[1]));
	z = (double)dis * R ;
	dis_true = z / b[2];
	if (dis_true < 55)
		return 10;
	else if (dis_true < 104)
		return 9;
	else if (dis_true < 156.5)
		return 8;
	else if (dis_true < 205.3)
		return 7;
	else if (dis_true < 250.7)
		return 6;
	else
		return 0;

}

void findh()
{
	vector<Point2f> pts_src;
	pts_src.push_back(Point2f(630, 184));
	pts_src.push_back(Point2f(1260, 184));
	pts_src.push_back(Point2f(630, 810));
	pts_src.push_back(Point2f(1260, 810));

	
	vector<Point2f> pts_dst;
	pts_dst.push_back(Point2f(0, 0));
	pts_dst.push_back(Point2f(630, 0));
	pts_dst.push_back(Point2f(0, 526));
	pts_dst.push_back(Point2f(630, 526));
	  
	Mat h = findHomography(pts_src, pts_dst);
}