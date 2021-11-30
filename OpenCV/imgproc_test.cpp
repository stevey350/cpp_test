
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void filter_test(Mat img)
{
    // 1-线性滤波器
    Mat result;
    boxFilter(img, result, img.depth(), Size(3, 3), Point(-1, -1), true);       // 相当于均值滤波
    // boxFilter(img, result, img.depth(), Size(3, 3), Point(-1, -1), false);
    // blur(img, result, Size(3, 3));               // 均值滤波

    Mat gauss_kernel = getGaussianKernel(9, 0.5);
    cout << gauss_kernel << endl;
    // GaussianBlur(img, result, Size(3, 3), 0);    // 高斯滤波

    // 2-非线性滤波
    Mat result2;
    // medianBlur(img, result2, 5);                 // 中值滤波
    bilateralFilter(img, result2, 25, 25*2, 25/2);  //

    // imshow("raw image", img);
    imshow("filtered image2", result2);
    imshow("filtered image", result);
}

void resize_test(Mat img)
{
    imshow("raw image", img);
    cout << "raw image: rows, cols " << img.rows << ", " << img.cols << endl;

    Mat new_image;
    resize(img, new_image, Size(), 3, 3, INTER_NEAREST);
    imshow("new image", new_image);
    cout << "new image: rows, cols " << new_image.rows << ", " << new_image.cols << endl;

    resize(img, new_image, Size(), 3, 3, INTER_LINEAR);
    imshow("new image2", new_image);
}

void sobel_test(Mat img)
{
    // sobel算子获取
    cv::Mat kx, ky;
    cv::getDerivKernels(kx, ky, 0, 1, 3, false, CV_32FC1);
    cout << "kx: \n" << kx << endl;
    cout << "ky: \n" << ky << endl;

    cv::Mat patternx = kx * ky.t();
    cv::Mat patterny = patternx.t();
    cout << "patternx: \n" << patternx << endl;
    cout << "patterny: \n" << patterny << endl;

    // 单独采用Sobel
    Mat sobel_x, sobel_y;
    Sobel(img,      // 输入 
          sobel_x,  // 输出
          CV_8U,    // 输出图像元素类型，通道不变
          1, 0,     // 内核规格 dx起作用
          3,        // 内核尺寸 (1, 3, 5, 7) 值越大，边缘越明显
          0.4, 128);// 比例和偏移 运算结果可能会超出像素值域的范围(将结果按比例0.4缩放，并加上偏移量128)
    Sobel(img, sobel_y, CV_8U, 0, 1, 3, 0.4, 128);
    cout << "soble_x channel: " << sobel_x.channels() << endl;
    imshow("sobel x image", sobel_x);
    imshow("soble y image", sobel_y);

    // GaussianBlur(img, img, Size(7, 7), 0);

    // 整合Sobel的结果
    cvtColor(img, img, CV_BGR2GRAY);
    Mat sobel, sobelX, sobelY;
    // Sobel(img, sobelX, CV_16S, 1, 0);
    // Sobel(img, sobelY, CV_16S, 0, 1);
    Sobel(img, sobelX, CV_32F, 1, 0);
    Sobel(img, sobelY, CV_32F, 0, 1);
    sqrt(sobelX.mul(sobelX) + sobelY.mul(sobelY), sobel);   // L2 范数
    // sobel = abs(sobelX) + abs(sobelY);                   // L1 范数
    cout << "sobel channel: " << sobel.channels() << endl;

    double sob_min, sob_max;
    Point min_pos, max_pos;
    minMaxLoc(sobel, &sob_min, &sob_max, &min_pos, &max_pos);
    cout << "max values: " << sobel.at<float>(max_pos) << endl;
    cout << "direction: " << atan2(sobelY.at<float>(max_pos), sobelX.at<float>(max_pos)) << endl;

    // 梯度幅值和角度验证-将笛卡儿坐标换算成极坐标，得到幅值和角度
    cv::Mat norm, dir;
    cv::cartToPolar(sobelX, sobelY, norm, dir);
    cout << "norm at max_pos: " << norm.at<float>(max_pos) << endl;
    cout << "dir at max_pos: " << dir.at<float>(max_pos) << endl;

    Mat sobel_image, sobel_image2;
    sobel.convertTo(sobel_image, CV_8UC3, -255/sob_max, 255);   // 除了映射到0-255范围内外，还做了取反
    sobel.convertTo(sobel_image2, CV_8UC3, 255/sob_max);        // 直接映射成0-255范围内  255-sobel_image
    sobel_image2 = Scalar::all(255) - sobel_image2;
    imshow("sobel image", sobel);
    imshow("sobelimage", sobel_image);
    imshow("sobleimage2", sobel_image2);
}


void laplacian_test(Mat img)
{
    Mat img_lap;
    Laplacian(img, img_lap, CV_32F);

    imshow("laplacian image", img_lap);
}


void canny_test(Mat img)
{
    // 直接应用Canny
    Mat result;
    Canny(img, result, 6, 18);

    // 经过预处理后，再应用Canny
    Mat result2, dst;
    cvtColor(img, result2, CV_BGR2GRAY);
    blur(result2, result2, Size(3, 3));
    Canny(result2, result2, 6, 18);
    img.copyTo(dst, result2);

    imshow("raw image", img);
    imshow("canny result", result);
    imshow("canny result2", result2);
}

void hough_test(Mat img)
{
    Mat result;
    
    Canny(img, result, 50, 200);
    if (result.type() != CV_8UC1) {
        cout << "Warning: result type is not CV_8UC1" << endl;
    }
    imshow("canny result", result);

    // 标准霍夫线检测
    Mat hough_lines_result = img.clone();
    vector<Vec2f> lines;
    HoughLines(result, lines, 1, CV_PI/180, 190);
    for(size_t i=0; i<lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        double sin_theta = sin(theta), cos_theta = cos(theta);
        double x0 = rho*cos_theta, y0 = rho*sin_theta;
        Point pt1, pt2;

        pt1.x = cvRound(x0 + 1000*sin_theta);
        pt1.y = cvRound(y0 - 1000*cos_theta);
        pt2.x = cvRound(x0 - 1000*sin_theta);
        pt2.y = cvRound(y0 + 1000*cos_theta);

        line(hough_lines_result, pt1, pt2, Scalar(55, 100, 195));
    }
    imshow("HoughLines result", hough_lines_result);

    // 概率霍夫线检测
    Mat hough_linesP_result = img.clone();
    vector<Vec4i> linesp;
    HoughLinesP(result, linesp, 1, CV_PI/180, 180, 50, 5);

    for(size_t i=0; i<linesp.size(); i++) {
        Vec4i l = linesp[i];

        line(hough_linesP_result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(55, 100, 195));
    }
    imshow("HougLinesP result", hough_linesP_result);

    // 梯度霍夫圆检测
    Mat hough_circle_result = img.clone();
    Mat img_gray;
    cvtColor(img, img_gray, CV_BGR2GRAY);
    vector<Vec3f> circles;
    HoughCircles(img_gray, circles, HOUGH_GRADIENT, 1, 50, 150, 150);
    // HoughCircles(img_gray, circles, HOUGH_GRADIENT, 2, 50, 150, 350, 30, 250);
    for(size_t i=0; i<circles.size(); i++) {
        Vec3f c = circles[i];
        Point center(cvRound(c[0]), cvRound(c[1]));
        int radius = cvRound(c[2]);

        // 绘圆心
        circle(hough_circle_result, center, 3, Scalar(0, 0, 255), -1);

        // 会圆
        circle(hough_circle_result, center, radius, Scalar(155, 50, 195), 2);
    }
    imshow("HougCircles result", hough_circle_result);
}



int main(int argc, char **argv)
{
    Mat img = imread("./ubuntu.png");

    // filter_test(img.clone());
    // resize_test(img.clone());
    sobel_test(img.clone());
    // laplacian_test(img.clone());
    // canny_test(img.clone());
    // hough_test(img.clone());

    waitKey(0);
    return 0;
}

