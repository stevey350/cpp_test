/**
 * @file geometry_test.cpp
 * @brief  矩形、椭圆框绘制
 * @author sj.su (sj.su@tungthih.com.cn)
 * @version 1.0
 * @date 2021-11-11
 * 
 * @copyright Copyright (c) 2021 Xiamen Tung Thih Electron CO.,LTD
 * 
 * @par History:
 * <table>
 * <tr>
 *     <th>Date
 *     <th>Version
 *     <th>Author
 *     <th>Description
 * </tr>
 * <tr>
 *     <th>2021-11-11
 *     <th>v0.0.1
 *     <th>sj.su
 *     <th>原型开发
 * </tr>
 * </table>
 */
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

void draw_rotatedRect(cv::Mat &image, RotatedRect rotate_rect, Scalar color=Scalar(0, 0, 255))
{
    Point2f pts[4];
    rotate_rect.points(pts);
    for(uchar i=0; i<4; i++) {
        line(image, pts[i], pts[(i+1)%4], color);
    }
}

// 点的拟合
void points_fitting_test(void)
{
    cv::Mat image = cv::Mat::ones(480, 640, CV_8UC3)*255;

    // 输入拟合点并绘制到空白图上
    std::vector<cv::Point> points;

    points.push_back(cv::Point(200, 240));
    points.push_back(cv::Point(300, 400));
    points.push_back(cv::Point(400, 360));
    points.push_back(cv::Point(500, 300));
    points.push_back(cv::Point(500, 200));
    points.push_back(cv::Point(300, 150));

    for (int i = 0; i < points.size(); i++) {
        cv::circle(image, points[i], 5, cv::Scalar(0, 0, 255), 2, 8, 0);
    }

    // 拟合
    cv::RotatedRect rotate_rect = cv::fitEllipse(points);
    draw_rotatedRect(image, rotate_rect);

    // cv::rectangle(image, rotate_rect, cv::Scalar(0, 255, 0));

    cv::imshow("pts fitting result", image);
}

void rotatedRect_fitting_test(void)
{
    //创建一个用于绘制图像的空白图
    cv::Mat image(480, 640, CV_8UC3, Scalar(255, 255, 255));

    // 创建一个带方向的矩形框
    Point2f center(300, 300);
    cv::circle(image, center, 5, cv::Scalar(0, 0, 255), 2, 8, 0);
    cv::RotatedRect rotate_rect(center, cv::Size(150, 100), 45);
    draw_rotatedRect(image, rotate_rect);

    // 外接矩形
    cv::Rect rect = rotate_rect.boundingRect();
    cv::rectangle(image, rect, Scalar(0, 255, 0));      // 绿色
    // cout << "rect tl" << rect.tl() << " size" << rect.size() << endl;

    // 内接椭圆
    // 通过RotatedRect的长方体替代椭圆表示法。这意味着函数将绘制一个内接在旋转矩形中的椭圆
    cv::ellipse(image, rotate_rect, cv::Scalar(0, 255, 255), 2, 8);


    imshow("rotated rect fitting result", image);
}

void rect_operate_test(Mat image)
{
    cv::Rect rect1(Point2f(200, 200), Size2f(200, 100));
    cv::Rect rect2(Point2f(250, 250), Size2f(200, 100));
    rectangle(image, rect1, Scalar(0, 255, 0));
    rectangle(image, rect2, Scalar(0, 0, 255));

    // 并操作
    // cv::Rect rect = rect1 | rect2;
    // rectangle(image, rect, Scalar(255));

    // 与操作
    cv::Rect rect = rect1 & rect2;
    rectangle(image, rect, Scalar(255));

    imshow("rotated rect operate result", image);
}

int main(int argc, char **argv)
{
    cv::Mat image(480, 640, CV_8UC3);
    image.setTo(cv::Scalar(255, 255, 255));     // 设置白色背景

    // points_fitting_test();
    // rotatedRect_fitting_test();
    rect_operate_test(image.clone());

    // test-2
    cv::RNG rng;  // if add operator (), it will cause a problem, why?
    cout << "rng: " << endl;
    for(int i=0; i<20; i++) {
        cout << rng.uniform(0, 5) << endl;
    }


    // CV_Assert(0);        // 在Release下也起作用
    // assert(0);              // 只在Debug下起作用

    cv::waitKey(0);

    return 0;
}