/**
 * @file feature2d_test.cpp
 * @brief OpenCV中，特征点指由关键点(key-point)和描述子(descriptor)两部分组成
 *        Harris和FAST没有描述子，所以只能算关键点，不算特征点
 * @author sj.su (sj.su@tungthih.com.cn)
 * @version 1.0
 * @date 2021-10-25
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
 *     <th>2021-10-25
 *     <th>v0.0.1
 *     <th>sj.su
 *     <th>原型开发
 * </tr>
 * </table>
 */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void get_corner_points(const Mat &corner_map, std::vector<Point> &points)
{
    for(size_t y=0; y<corner_map.rows; y++) {
        const uchar *ptr_row = corner_map.ptr<uchar>(y);
        for(size_t x=0; x<corner_map.cols; x++) {
            if(ptr_row[x]) {
                points.push_back(Point(x, y));
            }
        }
    }
}

void draw_corners(Mat &img, const vector<Point> &points) 
{
    vector<Point>::const_iterator it = points.begin();
    while (it != points.end())
    {
        circle(img, *it, 3, Scalar(50, 100, 150));
        it++;
    }
}

void harris_test(Mat img)
{
    Mat img_gray;
    cvtColor(img, img_gray, CV_BGR2GRAY);
    Mat corner_strength;
    cornerHarris(img_gray, corner_strength,  // 输出浮点型角点强度图像
                      3,                // 邻域尺寸
                      3,                // 口径尺寸
                      0.01);
    // imshow("corner strength", corner_strength);
    // 自适应取阈值 最大值*0.02
    double max_strength, thres;
    minMaxLoc(corner_strength, 0, &max_strength);       // 得到最大强度值
    thres = 0.02*max_strength;
    cout << "max strength: " << max_strength << endl;

    // 检测局部最大值
    Mat dilated, local_max_strength;
    dilate(corner_strength, dilated, Mat());            // 膨胀，大的值会往外扩张
    compare(corner_strength, /*max_strength*/ dilated, local_max_strength, CMP_EQ);
    imshow("local_max_strength", local_max_strength);

    // 阈值化
    Mat harris_corners;
    threshold(corner_strength, harris_corners, thres, 255, THRESH_BINARY);  
    imshow("harris corners binary", harris_corners);

    cout << "harris corner type " << harris_corners.type() << " " << harris_corners.channels() << endl;

    // 非极大值抑制
    Mat corner_map;
    harris_corners.convertTo(corner_map, CV_8UC1);      // 输出的harris_corners是32FC1
    bitwise_and(corner_map, local_max_strength, corner_map);
    imshow("corner_map", corner_map);

    // vector<Point> points;
    // get_corner_points(corner_map, points);
    // draw_corners(img, points);
    // imshow("harris result", img);

    // harris改进版good-feature-to-track (GFTT)
    std::vector<cv::KeyPoint> key_points;
    cv::Ptr<cv::GFTTDetector> ptr_gftt = cv::GFTTDetector::create(500, 0.01, 10);
    ptr_gftt->detect(img, key_points);
    drawKeypoints(img, key_points, img, Scalar(100, 150, 200));
    imshow("gftt results", img);
}


/**
 * @brief 关键点的提取
 */
void fast_test(Mat img)
{
    // 封装的类
    vector<KeyPoint> key_points;
    // 阈值说明：一个点与圆心强度值之差所要达到的阈值，才被认为是明显更亮或更暗的点
    Ptr<FastFeatureDetector> ptr_fast = FastFeatureDetector::create(40);
    ptr_fast->detect(img, key_points);
    cout << "key points num: " << key_points.size() << endl;
    Mat img_result1;
    drawKeypoints(img, key_points, img_result1, Scalar(100, 150, 200));
    imshow("fast result", img_result1);

    // 独立函数
    key_points.clear();
    Mat img_gray;
    cvtColor(img, img_gray, CV_BGR2GRAY);
    FAST( img_gray, key_points, 40, true, FastFeatureDetector::TYPE_9_16);
    cout << "key points num: " << key_points.size() << endl;
    Mat img_result2;
    drawKeypoints(img, key_points, img_result2, Scalar(120, 170, 220));
    imshow("fast result2", img_result2);

    // 扩展后续处理
    int num_points = 300;
    if(num_points < key_points.size()) {
        std::nth_element(key_points.begin(), key_points.begin()+num_points,
                         key_points.end(),
                         [](cv::KeyPoint &a, cv::KeyPoint &b) {
                             return a.response > b.response;
                         });
        
        vector<KeyPoint> key_points_temp(key_points.begin(), key_points.begin()+num_points);
        cout << "key points temp num: " << key_points_temp.size() << endl;
        Mat img_result3;
        drawKeypoints(img, key_points_temp, img_result3, Scalar(120, 170, 220));
        imshow("fast result3", img_result3);
    }

}

void orb_test(Mat img)
{
    vector<KeyPoint> key_points;
    // 200个强度最大的关键点，1.2缩放因子进行下采样，采样8个尺度
    cv::Ptr<cv::ORB> ptr_orb = cv::ORB::create(200, 1.2, 8);
    ptr_orb->detect(img, key_points);
    cout << "key points num: " << key_points.size() << endl;
    
    // 遍历输出部分关键点信息  lu->long unsigned int
    for(size_t i=0; i<key_points.size()/*min(20lu, key_points.size())*/; i++) {
        cout << key_points[i].size << " " << key_points[i].angle << " " << key_points[i].octave << " " << key_points[i].class_id << endl;
    }

    Mat img_result;
    drawKeypoints(img, key_points, img_result, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    imshow("orb result", img_result);
}

/**
 * @brief 关键点的描述与匹配
 */
void fast_feature_match(Mat img1, Mat img2)
{
    // 检测关键点
    vector<KeyPoint> key_points1, key_points2;
    Ptr<FastFeatureDetector> ptr_fast = FastFeatureDetector::create(40);
    ptr_fast->detect(img1, key_points1);
    ptr_fast->detect(img2, key_points2);

    Mat img1_result, img2_result;
    drawKeypoints(img1, key_points1, img1_result, Scalar(150, 200, 250));
    drawKeypoints(img2, key_points2, img2_result, Scalar(150, 200, 250));
    cout << "key points1 num: " << key_points1.size() << endl;
    cout << "key points2 num: " << key_points2.size() << endl;
    imshow("img1 result", img1_result);
    imshow("img2 result", img2_result);

    // 定义关键点的邻域
    const int nsize(11);
    Rect neighborhood(0, 0, nsize, nsize);
    Mat patch1, patch2;
    vector<DMatch> matches;
    Mat match_result;
    
    // 第一层循环
    for(size_t i=0; i<key_points1.size(); i++) {
        neighborhood.x = key_points1[i].pt.x - nsize/2;
        neighborhood.y = key_points1[i].pt.y - nsize/2;

        // 是否超出图像范围判断
        if(neighborhood.x < 0 || neighborhood.y < 0 ||
           neighborhood.x+nsize >= img1.cols ||
           neighborhood.y+nsize >= img1.rows)
           continue;

        patch1 = img1(neighborhood);

        DMatch best_match;      // 会初始化一个非常大的distance
        // cout << "best match distance: " << best_match.distance << endl;

        // 第二层循环
        for(size_t j=0; j<key_points2.size(); j++) {
            neighborhood.x = key_points2[j].pt.x - nsize/2;
            neighborhood.y = key_points2[j].pt.y - nsize/2;

            if(neighborhood.x < 0 || neighborhood.y < 0 ||
               neighborhood.x + nsize >= img2.cols || 
               neighborhood.y + nsize >= img2.rows)
               continue;
            
            patch2 = img2(neighborhood);
            matchTemplate(patch1, patch2, match_result, TM_SQDIFF);
            if(match_result.at<float>(0, 0) < best_match.distance) {
                best_match.distance = match_result.at<float>(0, 0);
                best_match.queryIdx = i;
                best_match.trainIdx = j;
            }
        }
        // 添加最佳匹配
        matches.push_back(best_match);
    }

    // 提取最佳25个匹配项
    cout << "matches num: " << matches.size() << endl;
    nth_element(matches.begin(), matches.begin()+25, matches.end());    // DMatch已经重载了运算符< (less is better)
    matches.erase(matches.begin()+25, matches.end());
    cout << "matches num after distillation: " << matches.size() << endl;

    // 画出匹配结果
    Mat draw_match;
    drawMatches(img1, key_points1, img2, key_points2, matches, draw_match);
    imshow("draw matches", draw_match);
}

void orb_feature_match(Mat img1, Mat img2)
{
    // 关键点Oriented ORB检测
    vector<KeyPoint> key_points1, key_points2;
    Ptr<ORB> ptr_orb = ORB::create(500);
    ptr_orb->detect(img1, key_points1);
    ptr_orb->detect(img2, key_points2);

    // 根据关键点位置计算BRIEF描述子
    Mat descriptors1, descriptors2;
    ptr_orb->compute(img1, key_points1, descriptors1);
    ptr_orb->compute(img2, key_points2, descriptors2);

    // 1-原始匹配
    BFMatcher matcher(NORM_HAMMING);
    vector<DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);

    // 绘制
    Mat match_result;
    drawMatches(img1, key_points1, img2, key_points2, matches, match_result);
    imshow("orb feature match", match_result);

    // 2-匹配点对筛选1
    auto min_max = minmax_element(matches.begin(), matches.end());
    double min_dist = min_max.first->distance;
    double max_dist = min_max.second->distance;
    cout << "min-max distance: " << min_dist << "-" << max_dist << endl;

    vector<DMatch> good_matches;
    for(size_t i=0; i<matches.size(); i++) {
        if(matches[i].distance <= max(2*min_dist, 30.0)) {
            good_matches.push_back(matches[i]);
        }
    }
    cout << "good matches: " << good_matches.size() << endl;

    // 绘制
    Mat match_result2;
    drawMatches(img1, key_points1, img2, key_points2, good_matches, match_result2);
    imshow("orb good matches", match_result2);

    // 3-取最优匹配的79个
    nth_element(matches.begin(), matches.begin()+79, matches.end(), [](DMatch &a, DMatch &b){return a.distance < b.distance;});
    matches.erase(matches.begin()+79, matches.end());

    Mat match_result3;
    drawMatches(img1, key_points1, img2, key_points2, good_matches, match_result3);
    imshow("orb good matches3", match_result3);
}

int main(int argc, char **argv)
{
    Mat img_ubuntu = imread("./ubuntu.png");
    Mat img1 = imread("./1.png");
    Mat img2 = imread("./2.png");

    // 关键点检测
    harris_test(img1.clone());
    // fast_test(img.clone());
    // orb_test(img_ubuntu.clone());

    // 关键点描述与匹配 -> 特征点
    // fast_feature_match(img1.clone(), img2.clone());
    // orb_feature_match(img1.clone(), img2.clone());

    waitKey();
    return 0;
}
