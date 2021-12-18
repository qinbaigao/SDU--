/*
1.adaptiveThreshold
����1��InputArray���͵�src������ͼ���ͨ������8λ��������Mat���ɡ�
����2�����������Ľ��������⡣��Ϊ���ͼ��������ͼ��ͬ���ĳߴ�����ͣ���
����3��Ԥ���������������ֵ��
����4��ָ������Ӧ��ֵ�㷨����ѡ��ADAPTIVE_THRESH_MEAN_C �� ADAPTIVE_THRESH_GAUSSIAN_C���֡�
����5��ָ����ֵ���͡���ѡ��THRESH_BINARY����THRESH_BINARY_INV���֡�������������ֵ�򷴶�������ֵ����
����6����ʾ������С����������������ֵ��һ��ѡ��Ϊ3��5��7......�ȡ�
����7������C��ʾ���㷨�йصĲ���������һ���Ӿ�ֵ���Ȩ��ֵ��ȡ�ĳ����������Ǹ�����

2.void medianBlur( InputArray src, OutputArray dst,int ksize );
src �� ����ͼ��
dst �� ���ͼ��, ������ src ��ͬ����
ksize �� �ں˴�С (ֻ��һ��ֵ����Ϊʹ�������δ���)������Ϊ������

3.VideoCapture::get���������б�
CV_CAP_PROP_POS_MSEC	��Ƶ�ļ��ĵ�ǰλ�ã��Ժ���Ϊ��λ����Ƶ����ʱ���.
CV_CAP_PROP_POS_FRAMES	����0����һ��Ҫ����/�����֡������
CV_CAP_PROP_POS_AVI_RATIO��Ƶ�ļ������λ�ã�0-��Ӱ�Ŀ�ʼ��1-��Ӱ�Ľ���
CV_CAP_PROP_FRAME_WIDTH	��Ƶ���е�֡�Ŀ��
CV_CAP_PROP_FRAME_HEIGHT��Ƶ���е�֡�ĸ߶�
CV_CAP_PROP_FPS			֡����
CV_CAP_PROP_FOURCC		�����4���ַ�����
CV_CAP_PROP_FRAME_COUNT	��ʽ��֡������
CV_CAP_PROP_MODE		�ض��ں�˵�ֵ��ָʾ��ǰ�Ĳ���ģʽ
CV_CAP_PROP_BRIGHTNESS	ͼ������ȣ��������������
CV_CAP_PROP_CONTRAST	ͼ��ĶԱȶȣ��������������
CV_CAP_PROP_SATURATION	ͼ��ı��Ͷȣ��������������
CV_UE					ͼ������棨�������������
CV_CAP_PROP_GAIN		ͼ������棨�������������
CV_CAP_PROP _EXPOSURE	�ع⣨���������������
CV_CAP_PROP_CONVERT_RGB	�����ͱ�־��ָʾ�Ƿ�Ӧ��ͼ��ת��ΪRGB
CV_CAP_PROP_WHITE_BALANCE��ǰ��֧��
CV_CAP_PROP_RECTIFICATION�����������������־

4.HoughCircles(p1, circles, HOUGH_GRADIENT, 1.2, 200, 200, 60, 50, 500);
image:			���� 8-���ء���ͨ���Ҷ�ͼ��.
circle_storage����⵽��Բ�洢��. �������ڴ�洢�� (��������£�һ���߶������ڴ洢���б������������ɺ������أ������ǰ���Բ��
				�����������͵ľ��е���/���е�CV_32FC3�;���(CvMat*). ����ͷΪ�������޸ģ�ʹ������ cols/rows ������һ���⵽
				��Բ����� circle_storage �Ǿ��󣬶�ʵ��Բ����Ŀ��������ߴ磬��ô��������Ŀ��Բ������. ÿ��Բ������������
				��ʾ��Բ������(x,y)�Ͱ뾶.
methodHough��	�任��ʽ��Ŀǰֻ֧��CV_HOUGH_GRADIENT, 
dp��			�ۼ���ͼ��ķֱ��ʡ��������������һ��������ͼ��ֱ��ʵ͵��ۼ�����������������Ϊ��������Ϊͼ���д��ڵ�Բ����
				Ȼ���͵���ͼ������ͬ�����ķ��룩�����dp����Ϊ1����ֱ�������ͬ�ģ��������Ϊ�����ֵ������2�����ۼ����ķֱ�
				���ܴ�Ӱ����С���������Ϊһ�룩��dp��ֵ���ܱ�1С��
min_dist��		�ò��������㷨���������ֵ�������ͬԲ֮�����С���롣
param1��		����Canny�ı�Ե��ֵ���ޣ����ޱ���Ϊ���޵�һ�롣
param2��		�ۼ����ķ�ֵ��
min_radius��	��СԲ�뾶��
max_radius��	���Բ�뾶��

5.normalize
src             �������飻
dst             ������飬����Ĵ�С��ԭ����һ�£�
alpha           1,�����淶ֵ��2.�淶��Χ�����������ޣ�
beta            ֻ�����淶��Χ���������ޣ�
norm_type		��һ��ѡ�����ѧ��ʽ���ͣ�
dtype			��Ϊ��������ڴ�С���ͨ�������������룬��Ϊ�������ֻ����������粻ͬ����ͬ�ĵط���dtype������
mark            ���롣ѡ�����Ȥ����ѡ����ֻ�ܶԸ�������в�����

6.ͼƬУ���������������ĸ��㣩

	Mat im_src = imread(".jpg");
	vector<Point2f> pts_src;
	pts_src.push_back(Point2f(130, 88));
	pts_src.push_back(Point2f(704, 190));
	pts_src.push_back(Point2f(102, 1048));
	pts_src.push_back(Point2f(785, 960));

	Mat im_dst = imread(".jpg");
	vector<Point2f> pts_dst;
	pts_dst.push_back(Point2f(0, 0));
	pts_dst.push_back(Point2f(864, 0));
	pts_dst.push_back(Point2f(0, 1152));
	pts_dst.push_back(Point2f(864, 1152));

	Mat h = findHomography(pts_src, pts_dst);

	Mat im_out;
	warpPerspective(im_src, im_out, h, im_dst.size());

	imshow("Source Image", im_src);
	imshow("Destination Image", im_dst);
	imshow("Warped Source Image", im_out);

	waitKey(0);

7.threshold(img, threshold, maxval,type)
THRESH_BINARY		������ֵ�Ĳ��ֱ���Ϊ255��С�ڲ��ֱ���Ϊ0
THRESH_BINARY_INV	������ֵ���ֱ���Ϊ0��С�ڲ��ֱ���Ϊ255
THRESH_TRUNC		������ֵ���ֱ���Ϊthreshold��С�ڲ��ֱ���ԭ��
THRESH_TOZERO		С����ֵ���ֱ���Ϊ0�����ڲ��ֱ��ֲ���
THRESH_TOZERO_INV	������ֵ���ֱ���Ϊ0��С�ڲ��ֱ��ֲ���
THRESH_OTSU			��Ϊͼ������Ӧ��ֵ����һ�����ŵ��㷨Otsu����㷨�Ĳ���

8.void HoughLinesP(InputArray image, OutputArray lines, double rho, double theta, int threshold, double minLineLength=0, double maxLineGap=0 )
image	����ͼ��8λ��ͨ��������ͼ��
lines	�洢��⵽�������˵�����
rho		ֱ������ʱ�Ľ����ߴ�ĵ�λ�뾶
theta	ֱ������ʱ�Ľ����ߴ�ĵ�λ�Ƕ�
threshold	ʶ��ĳ����Ϊͼ�е�һ��ֱ��ʱ�����ۼ�ƽ���б���ﵽ��ֵ
minlinelength	��Ĭ��ֵ0����ʾ����߶εĳ���
maxlinegap	��Ĭ��ֵ0������ͬһ�е����֮���������������ľ���















*/

