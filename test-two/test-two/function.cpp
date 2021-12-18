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
	Mat elementC = getStructuringElement(2, Size(5, 5));	//0������ 1��ʮ���� 2����Բ��
	Mat elementO = getStructuringElement(2, Size(3, 3));
	//imshow("p1", p1);
	//imshow("p2", p2);

	//�������ת�Ҷȣ���ת�ҶȺ������д�����
	//absdiff(p1, p2, dst);
	//cvtColor(dst, dst, CV_BGR2GRAY);
	cvtColor(p1, p1, CV_BGR2GRAY);            
	cvtColor(p2, p2, CV_BGR2GRAY);   
	absdiff(p1, p2, dst);
	imshow("֡��",dst);
	//�Ƿ���Ҫ�˲��д�����
	//medianBlur(dst, dst, 5);	//��ֵ�˲�
	//GaussianBlur(dst, dst, Size(5, 5), 0);	//��˹�˲�ȥ��С���

	//�������ֶ�ֵ�������д�����
	threshold(dst, dst, 180, 255, THRESH_BINARY);
	//adaptiveThreshold(dst, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 7, 0);//�Զ���ֵ�ָ��˹����
	//threshold(dst, dst, 0, 255, THRESH_OTSU);	//�����䷽��ָ�
	imshow("֡���ֵ��", dst);

	morphologyEx(dst, dst, CV_MOP_OPEN, elementO);	//�����㣬ȥ��С�׵㣬ȥ��
	morphologyEx(dst, dst, CV_MOP_CLOSE, elementC);	//�����㣬ȥ��С�ڵ㣬ʹ���׸��ӱ���	
	imshow("��ȡ����", dst);
	//imwrite("dankong.jpg", dst);

	//ģ��ƥ�䣨������
	//1.�������ͼ��resultImg(ע���С������)
	//���ԭͼ(������ͼ��)�ߴ�ΪW x H, ��ģ��ߴ�Ϊ w x h, ����ͼ��ߴ�һ����(W-w+1)x(H-h+1)
	//���ͼ�����Ϊ��ͨ��32λ������ͼ��
	int width = dst.cols - temp.cols + 1;
	int height = dst.rows - temp.rows + 1;
	Mat matchresult(Size(width, height), CV_32FC1);
	//2.ģ��ƥ��
	cvtColor(dst, dst, CV_GRAY2BGR);
	matchTemplate(dst, temp, matchresult, 5);
	//3.����(��һ����0-1)
	normalize(matchresult, matchresult, 0, 1, NORM_MINMAX, -1);
	//4.����resultImg������ɸѡ������ɸѡ��ǰ����ƥ��λ��
	int tempX = 0, tempY = 0;
	int maxX = 0, maxY = 0;
	double maxValue = 0;
	for (int i = 0; i < matchresult.rows; i++)		//��
	{
		for (int j = 0; j < matchresult.cols; j++)	//��
		{
			//���resultImg��(j,x)λ�õ�ƥ��ֵmatchValue
			double matchValue = matchresult.at<float>(i, j);
			//�κ�ѡ�еĵ���x�����y�����϶�Ҫ����һ�����3(���⻭�߿���Ӱ�����)
			if (matchValue > 0.98)
			//if (matchValue > 0.92&& abs(i - tempY) > 3 && abs(j - tempX) > 3)
			{
				//5.��ɸѡ���ĵ㻭���߿�
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
	
	//ģ��ƥ�䣨�����
	//int n;
	//Mat temp1 = imread("");	//��ȡģ��ͼ1
	//Mat temp2 = imread("");	//��ȡģ��ͼ2
	////1.�������ͼ��resultImg(ע���С������)
	////���ԭͼ(������ͼ��)�ߴ�ΪW x H, ��ģ��ߴ�Ϊ w x h, ����ͼ��ߴ�һ����(W-w+1)x(H-h+1)
	////���ͼ�����Ϊ��ͨ��32λ������ͼ��
	//int width1 = dst.cols - temp1.cols + 1;
	//int height1 = dst.rows - temp1.rows + 1;
	//Mat matchresult1(Size(width1, height1), CV_32FC1);
	//int width2 = dst.cols - temp2.cols + 1;
	//int height2 = dst.rows - temp2.rows + 1;
	//Mat matchresult2(Size(width2, height2), CV_32FC1);
	////2.ģ��ƥ��
	//matchTemplate(dst, temp1, matchresult1, 5);
	//matchTemplate(dst, temp1, matchresult2, 5);
	////3.����(��һ����0-1)
	//normalize(matchresult1, matchresult1, 0, 1, NORM_MINMAX, -1);
	//normalize(matchresult2, matchresult2, 0, 1, NORM_MINMAX, -1);
	////4.����resultImg������ɸѡ������ɸѡ��ǰ����ƥ��λ��
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
	//				//���resultImg��(j,x)λ�õ�ƥ��ֵmatchValue
	//				double matchValue = matchresult1.at<float>(i, j);
	//				//�κ�ѡ�еĵ���x�����y�����϶�Ҫ����һ�����5(���⻭�߿���Ӱ�����)
	//				if (matchValue > 0.85&& abs(i - tempY) > 5 && abs(j - tempX) > 5)
	//				{
	//					//5.1��ɸѡ���ĵ㻭���߿�
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
	//				//���resultImg��(j,x)λ�õ�ƥ��ֵmatchValue
	//				double matchValue = matchresult1.at<float>(i, j);
	//				//�κ�ѡ�еĵ���x�����y�����϶�Ҫ����һ�����5(���⻭�߿���Ӱ�����)
	//				if (matchValue > 0.85&& abs(i - tempY) > 5 && abs(j - tempX) > 5)
	//				{
	//					//5.2��ɸѡ���ĵ㻭���߿�
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
	
	//�������п����ǵ��׵ĵ������
	
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

	//��ת�ҶȺ��˲��������˲���ת�Ҷ��д�����

	cvtColor(p1, p1, CV_BGR2GRAY);

	//���������˲������д�����
	medianBlur(p1, p1, 3);	//��ֵ�˲�
	//GaussianBlur(dst, dst, Size(5, 5), 0);	//��˹�˲�ȥ��С���
	//imshow("�Ҷ�", p1);

	//�������ֶ�ֵ�������д�����
	threshold(p1, p1, 127, 255, THRESH_BINARY);
	//adaptiveThreshold(p1, p1, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 3, 0);//�Զ���ֵ�ָ��˹����
	//threshold(p1, p1, 0, 255, THRESH_OTSU);	//�����䷽��ָ�
	//imshow("��ֵ��", p1);

	//ֻ�п���������ܲ��ܵõ�������ͼ���ڴ�֮ǰ�ɼ���ϸ����y�����Ի��������ֽ���ϸ������ϸ���ή��ʵʱ��
	morphologyEx(p1, p1, CV_MOP_CLOSE, elementC);	//���ģ�����㣬ȥ������10
	morphologyEx(p1, p1, CV_MOP_OPEN, elementO);	//���ģ�����㣬ȥ������������
	
	//imshow("���Բ", p1);
	vector<Vec3f> circles;	//��⵽Բ�Ĵ洢�֣�������������Բ������(x,y)�Ͱ뾶.
	HoughCircles(p1, circles, HOUGH_GRADIENT, 1.5, 20, 120, 20, 52, 54);
	for (int i = 0; i < circles.size(); i++)
	{

		Vec3f c;
		c = circles[i];
		circle(pic1, Point(cvRound(c[0]), cvRound(c[1])), 3, Scalar(0, 255, 50), 2);	//cvRound():���ظ�������ӽ�������ֵ,����������
		circle(pic1, Point(cvRound(c[0]), cvRound(c[1])), cvRound(c[2]), Scalar(0, 255, 50), 2, 8, 0);
		printf("��%d��ԲԲ������Ϊ:��%d,%d��,�뾶Ϊ��%d\n", i + 1, cvRound(c[0]), cvRound(c[1]), cvRound(c[2]));
		//imshow("pic1", pic1);
		//����Բ��������뾶
		if (circles.size() < 2)
		{
			a[0] = cvRound(c[0]);	
			a[1] = cvRound(c[1]);
			a[2] = cvRound(c[2]);
		}
		
	}	
}

int calculate_loop(int a[100][2], int b[3], int HoleC)//a:�������꣬b:����ԲԲ��������뾶
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