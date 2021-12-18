/*
1.adaptiveThreshold
参数1：InputArray类型的src，输入图像，填单通道，单8位浮点类型Mat即可。
参数2：函数运算后的结果存放在这。即为输出图像（与输入图像同样的尺寸和类型）。
参数3：预设满足条件的最大值。
参数4：指定自适应阈值算法。可选择ADAPTIVE_THRESH_MEAN_C 或 ADAPTIVE_THRESH_GAUSSIAN_C两种。
参数5：指定阈值类型。可选择THRESH_BINARY或者THRESH_BINARY_INV两种。（即二进制阈值或反二进制阈值）。
参数6：表示邻域块大小，用来计算区域阈值，一般选择为3、5、7......等。
参数7：参数C表示与算法有关的参数，它是一个从均值或加权均值提取的常数，可以是负数。

2.void medianBlur( InputArray src, OutputArray dst,int ksize );
src — 输入图像
dst — 输出图像, 必须与 src 相同类型
ksize — 内核大小 (只需一个值，因为使用正方形窗口)，必须为奇数。

3.VideoCapture::get函数参数列表
CV_CAP_PROP_POS_MSEC	视频文件的当前位置，以毫秒为单位或视频捕获时间戳.
CV_CAP_PROP_POS_FRAMES	基于0的下一个要解码/捕获的帧的索引
CV_CAP_PROP_POS_AVI_RATIO视频文件的相对位置：0-电影的开始，1-电影的结束
CV_CAP_PROP_FRAME_WIDTH	视频流中的帧的宽度
CV_CAP_PROP_FRAME_HEIGHT视频流中的帧的高度
CV_CAP_PROP_FPS			帧速率
CV_CAP_PROP_FOURCC		编码的4个字符代码
CV_CAP_PROP_FRAME_COUNT	格式的帧数返回
CV_CAP_PROP_MODE		特定于后端的值，指示当前的捕获模式
CV_CAP_PROP_BRIGHTNESS	图像的亮度（仅适用于相机）
CV_CAP_PROP_CONTRAST	图像的对比度（仅适用于相机）
CV_CAP_PROP_SATURATION	图像的饱和度（仅适用于相机）
CV_UE					图像的增益（仅适用于相机）
CV_CAP_PROP_GAIN		图像的增益（仅适用于相机）
CV_CAP_PROP _EXPOSURE	曝光（仅适用于摄像机）
CV_CAP_PROP_CONVERT_RGB	布尔型标志，指示是否应将图像转换为RGB
CV_CAP_PROP_WHITE_BALANCE当前不支持
CV_CAP_PROP_RECTIFICATION立体摄像机的整流标志

4.HoughCircles(p1, circles, HOUGH_GRADIENT, 1.2, 200, 200, 60, 50, 500);
image:			输入 8-比特、单通道灰度图像.
circle_storage；检测到的圆存储仓. 可以是内存存储仓 (此种情况下，一个线段序列在存储仓中被创建，并且由函数返回）或者是包含圆参
				数的特殊类型的具有单行/单列的CV_32FC3型矩阵(CvMat*). 矩阵头为函数所修改，使得它的 cols/rows 将包含一组检测到
				的圆。如果 circle_storage 是矩阵，而实际圆的数目超过矩阵尺寸，那么最大可能数目的圆被返回. 每个圆由三个浮点数
				表示：圆心坐标(x,y)和半径.
methodHough：	变换方式，目前只支持CV_HOUGH_GRADIENT, 
dp：			累加器图像的分辨率。这个参数允许创建一个比输入图像分辨率低的累加器。（这样做是因为有理由认为图像中存在的圆会自
				然降低到与图像宽高相同数量的范畴）。如果dp设置为1，则分辨率是相同的；如果设置为更大的值（比如2），累加器的分辨
				率受此影响会变小（此情况下为一半）。dp的值不能比1小。
min_dist：		该参数是让算法能明显区分的两个不同圆之间的最小距离。
param1：		用于Canny的边缘阀值上限，下限被置为上限的一半。
param2：		累加器的阀值。
min_radius：	最小圆半径。
max_radius：	最大圆半径。

5.normalize
src             输入数组；
dst             输出数组，数组的大小和原数组一致；
alpha           1,用来规范值，2.规范范围，并且是下限；
beta            只用来规范范围并且是上限；
norm_type		归一化选择的数学公式类型；
dtype			当为负，输出在大小深度通道数都等于输入，当为正，输出只在深度与输如不同，不同的地方游dtype决定；
mark            掩码。选择感兴趣区域，选定后只能对该区域进行操作。

6.图片校正（程序内设置四个点）

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
THRESH_BINARY		大于阈值的部分被置为255，小于部分被置为0
THRESH_BINARY_INV	大于阈值部分被置为0，小于部分被置为255
THRESH_TRUNC		大于阈值部分被置为threshold，小于部分保持原样
THRESH_TOZERO		小于阈值部分被置为0，大于部分保持不变
THRESH_TOZERO_INV	大于阈值部分被置为0，小于部分保持不变
THRESH_OTSU			作为图像自适应二值化的一个很优的算法Otsu大津算法的参数

8.void HoughLinesP(InputArray image, OutputArray lines, double rho, double theta, int threshold, double minLineLength=0, double maxLineGap=0 )
image	输入图像，8位单通道二进制图像
lines	存储检测到的线条端点坐标
rho		直线搜索时的进步尺寸的单位半径
theta	直线搜索时的进步尺寸的单位角度
threshold	识别某部分为图中的一条直线时它在累加平面中必须达到的值
minlinelength	有默认值0，表示最低线段的长度
maxlinegap	有默认值0，允许将同一行点与点之间连接起来的最大的距离















*/

