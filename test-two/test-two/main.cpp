/*
ȱ��ϸ������
*/
#include"main.h"

int high = 1500;//��ȡͼ��ĸ�
int wide = 1500;//��ȡͼ��Ŀ�
int loop;		//����
int holecount = 0;	//��������
int hole_coordinate[100][2] = { 0 };	//��������x,y 
int center_coordinate1[3] = { 0,0,0 };	//src1����Բ������뾶
int center_coordinate2[3] = { 0,0,0 };	//src2����Բ������뾶
double d_htc, d_htc_true;	//���׵����ĵ����ؾ��룬���׵����ĵ���ʵ��
double r;	//����Բ�����ذ뾶

int main()
{


	Mat src1, src2, show;	//��һ֡ͼƬ����֡ͼƬ��Ч��ͼͼƬ
	Mat frame, frame_p, frame_pp, h, im_out;
	Mat size(626, 630, CV_8UC1);	//����һ����200����100�ĻҶ�ͼ
	//src1 = imread("pre2.jpg");
	//src2 = imread("pre1.jpg");
	Mat framework = imread("formwork2.jpg");	//��ȡģ��ͼ
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
		cout << "���ǵ�" << framecount << "֡��Ƶ" << endl;
		imshow("��һ֡��Ƶ", frame);

	//ͼ����ʹ�÷���任����ֱ�ӿ�	
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
			cout << "��������Ϊ��" << hole_coordinate[holecount][0] << "," << hole_coordinate[holecount][1] << endl;
			cout << "��������Ϊ��" << holecount << endl;
			cout << "Բ������Ϊ��" << center_coordinate2[0] << "," << center_coordinate2[1] << endl;
			cout << "����Բ�뾶Ϊ��" << center_coordinate2[2] << endl;


		}


		if (delay >= 0 && waitKey(delay) >= 0)	
			waitKey();

		if (holecount > 0)//�ҵ�һ��������ͣ
			waitKey();

		if (firstframe == 1)
			firstframe = 0;
	}


	
}