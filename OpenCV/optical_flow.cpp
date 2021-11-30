
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

void draw_corners(Mat &img, const vector<Point2f> &points) 
{
    vector<Point2f>::const_iterator it = points.begin();
    while (it != points.end())
    {
        circle(img, Point(it->x, it->y), 3, Scalar(50, 100, 150));
        it++;
    }
}

int main(int argc, char **argv)
{
    Mat img1, img2;
    img1 = imread("1.png");
    img2 = imread("2.png");

    // 关键点检测
    vector<KeyPoint> key_points1, key_points2;
    Ptr<FastFeatureDetector> ptr_fast = FastFeatureDetector::create(40);
    ptr_fast->detect(img1, key_points1);
    ptr_fast->detect(img2, key_points2);

    Mat img1_result;
    drawKeypoints(img1, key_points1, img1_result);
    imshow("img1 result", img1_result);

    // 光流
    vector<Point2f> points1, points2;
    for(auto &kp : key_points1) points1.push_back(kp.pt);
    // for(auto &kp : key_points2) points2.push_back(kp.pt);

    vector<uchar> status;
    vector<float> error;
    calcOpticalFlowPyrLK(img1, img2, points1, points2, status, error);

    draw_corners(img2, points2);
    imshow("img2 result", img2);

    cout << "points1 size: " << points1.size() << endl;
    cout << "points2 size: " << points2.size() << endl;

    waitKey();

    return 0;
}
