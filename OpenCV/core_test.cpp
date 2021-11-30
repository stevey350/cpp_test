#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void mat_test(Mat img)
{
    Mat img_A, img_B;
    img_A = img;

    cout << "image A size: " << sizeof(img_A) << endl;
    cout << "imag A row, col, total: " << img_A.rows << " " << img_A.cols << " " << img_A.total() << endl;  // 96
    cout << "image B size: " << sizeof(img_B) << endl;  // 96
    cvtColor(img_A, img_B, COLOR_BGR2BGRA);
    img_B = img_A(Range::all(), Range(100, 1000));
    imshow("win_name", img_B);

    // 创建Mat对象的一些方法
    Mat M1(2, 2, CV_8UC3, Scalar(0, 10, 0));     // 构造函数
    cout << "M1 =\n" << M1.dims << endl << M1 << endl;

    int sz[3] = {2, 3, 4};
    std::vector<int> sizes {2, 3, 4};
    // Mat M2(3, sz, CV_8UC3, Scalar::all(0));     // 创建超过两维的矩阵
    Mat M2(sizes, CV_8UC3, Scalar::all(0));
    cout << "M2 row, col, total: " << M2.rows << " " << M2.cols << " " << M2.total() << endl;
    cout << "M2 =\n" << M2.dims << endl;

    // Mat M3 = Mat::eye(2, 2, CV_8U);
    Mat M3 = Mat::ones(2, 2, CV_8U);
    // Mat M3 = Mat::zeros(2, 2, CV_8U);           // 类Matlab创建
    cout << "M3 = \n" << M3 << endl;

    M3.create(4, 4, CV_8U);                        // 重新指定尺寸大小和为数据开辟内存
    cout << "M3 create = \n" << M3 << endl;

    Mat M4 = (Mat_<int>(2, 2) << 1, 2, 3, 4);       // 逗号分隔式初始化？？
    cout << "M4 = \n" << M4 << endl;

    Mat M_rowClone = M4.row(0).clone();             // 为已存在的对象创建新的信息头
    cout << "M_rowClone = \n" << M_rowClone << endl;

    // 其它常用数据结构
    Point2f p1(6, 2);
    cout << "p = " << p1 << endl;

    Point3f p2(6, 3, 2);

    std::vector<Point2f> points;
    points.push_back(Point2f(1, 2));
    points.push_back(Point2f(7, 8));
    Mat M_points(points);
    cout << "M_points = \n" << M_points << endl;
}

/**
 * @brief  depth() 返回Mat中每个数据元素的类型，存储在低3位
 *                 #define CV_8U   0
 *                 #define CV_8S   1
 *                 #define CV_16U  2
 *                 ...
 *         type() 除元素的数据类型（低3位）外，还包括通道(channel）的个数（高3位）
 *                 #define CV_8UC1 CV_MAKETYPE(CV_8U,1)
 *                 #define CV_8UC2 CV_MAKETYPE(CV_8U,2)
 *                 #define CV_8UC3 CV_MAKETYPE(CV_8U,3)
 * 
 *                 #define CV_MAKETYPE(depth,cn) (CV_MAT_DEPTH(depth) + (((cn)-1) << 3))
 *                 #define CV_MAT_DEPTH(flags)     ((flags) & 7)        // 深度在低3位
 * 
 */
void mat_type_test(Mat img)
{
    Mat img2;
    img.convertTo(img2, CV_32F, 1.0/255, 0.0);
    cout << "img/img2 depth: " << img.depth() << "/" << img2.depth() << endl;   // depth()返回每个数据元素的类型    
    cout << "img/img2 type: " << img.type() << "/" << img2.type() << endl;    // 除元素的数据类型（低3位）外，还包括通道(channel）的个数（高3位）
    imshow("converted image", img2);
}

void look_up_table(Mat img, int divide_width)
{
    // uchar table[256];
    // Mat table(1, 256, CV_8U);
    Mat table(256, 1, CV_8U);
    uchar *ptr = table.data;
    for(int i=0; i<256; i++) {
        // table[i] = divide_width*(i/divide_width);
        ptr[i] = divide_width*(i/divide_width);
    }

    // 1ms左右
    double time_start = getTickCount();
    Mat img_out;
    LUT(img, table, img_out);
    double time_delta = ((double)getTickCount() - time_start)/getTickFrequency();
    cout << "LUT time cost: " << time_delta << endl;
    imshow("color reduction", img_out);
}

void color_reduce(Mat img, int divide_width)
{
    uchar table[256];
    for(int i=0; i<256; i++) {
        table[i] = (i/divide_width)*divide_width;
    }

    double time_start = static_cast<double>(getTickCount());
    // 遍历方式1  4.6ms
    // int col_elems = img.cols*img.channels();
    // for(int i=0; i<img.rows; i++) {
    //     uchar *data = img.ptr(i);
    //     for(int j=0; j<col_elems; j++) {
    //         data[j] = table[data[j]];
    //     }
    // }

    // 遍历方式2 25ms
    // Mat_<Vec3b>::iterator it = img.begin<Vec3b>();
    // Mat_<Vec3b>::iterator it_end = img.end<Vec3b>();
    // for(; it != it_end; it++) {
    //     (*it)[0] = table[(*it)[0]];
    //     (*it)[1] = table[(*it)[1]];
    //     (*it)[2] = table[(*it)[2]];
    // }

    // 遍历方式3 16ms
    // for(int i=0; i<img.rows; i++) {
    //     for(int j=0; j<img.cols; j++) {
    //         img.at<Vec3b>(i, j)[0] = table[img.at<Vec3b>(i, j)[0]];
    //         img.at<Vec3b>(i, j)[1] = table[img.at<Vec3b>(i, j)[1]];
    //         img.at<Vec3b>(i, j)[2] = table[img.at<Vec3b>(i, j)[2]];

    //         // img.at<Vec3b>(i, j) = Vec3b(table[img.at<Vec3b>(i, j)[0]], table[img.at<Vec3b>(i, j)[1]], table[img.at<Vec3b>(i, j)[2]]);
    //     }
    // }

    // 遍历方式4
    int n_rows = img.rows;
    int n_cols = img.cols*img.channels();
    if(img.isContinuous()) {
        n_cols *= n_rows;
        n_rows = 1;
        // img = img.reshape(1, 1);
        // cout << "row, col, channel2\n" << img.rows << " " << img.cols << " " << img.channels() << endl;
    }
    for(int i=0; i<n_rows; i++) {
        uchar *data = img.ptr(i);
        for(int j=0; j<n_cols; j++) {
            data[j] = table[data[j]];
        }
    }

    double time_delta = ((double)getTickCount() - time_start)/getTickFrequency();
    cout << "color reduce time cost: " << time_delta << endl;

    imshow("color reduction2", img);
}

void roi_test(Mat img)
{
    Mat img_logo = img(Range(58, 316), Range(768, 994)).clone();

    Mat img_roi = img(Rect(50, 50, img_logo.cols, img_logo.rows));
    img_logo.copyTo(img_roi);

    img.colRange(0, 50).setTo(Scalar(0));

    imshow("raw+logo", img);
}

void split_test(Mat img)
{
    std::vector<Mat> channels;
    split(img, channels);

    cout << "channels size: " << channels.size() << endl;
    Mat blue_channel = channels[0];
    Mat green_channel = channels.at(1);
    Mat red_channel = channels[2];

    // imshow("blue channel", blue_channel);
    // waitKey(0);
    // imshow("green_channel", green_channel);
    // waitKey();
    // imshow("red_channel", red_channel);

    std::vector<Mat> img_merge_in {blue_channel, green_channel, Mat(blue_channel.rows, blue_channel.cols, CV_8U, Scalar(250))};
    Mat img_merge_out;
    merge(img_merge_in, img_merge_out);
    imshow("merge out", img_merge_out);
}

int g_contrast_value = 0;
int g_bright_value = 0;
void on_contrast_bright(int pos, void* userdata)
{

    Mat img_in = *((Mat *)userdata);
    Mat img_out = img_in.clone();

    int col_elems = img_in.cols*img_in.channels();
    for(int i=0; i<img_in.rows; i++) {
        uchar *ptr_row_in = img_in.ptr<uchar>(i);
        uchar *ptr_row_out = img_out.ptr(i);
        for(int j=0; j<col_elems; j++) {
            ptr_row_out[j] = cv::saturate_cast<uchar>( (g_contrast_value*0.01)*ptr_row_in[j] + g_bright_value);
        }
    }

    imshow("result", img_out);
}

void contrast_bright_test(Mat img)
{
    imshow("img_win_name", img);
    createTrackbar("constrast_track_name", "img_win_name", &g_contrast_value, 300, on_contrast_bright, (void *)&img);
    createTrackbar("bright_track_name", "img_win_name", &g_bright_value, 200, on_contrast_bright, (void *)&img);
}

void remap_test(const cv::Mat image) 
{
    // 映射参数
    cv::Mat srcX(image.rows, image.cols, CV_32F);
    cv::Mat srcY(image.rows, image.cols, CV_32F);
    // 创建映射参数
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            // (i,j)像素的新位置
            srcX.at<float>(i, j) = j;  // 保持在同一列
            // 原来在第 i 行的像素，现在根据一个正弦曲线移动
            srcY.at<float>(i, j) = i + 5 * sin(j / 10.0);
        }
    }

    // 应用映射参数
    cv::Mat result;
    cv::remap(image,              // 源图像
              result,             // 目标图像
              srcX,               // x 映射
              srcY,               // y 映射
              cv::INTER_LINEAR);  // 填补方法
    imshow("remap result", result);
}

int main(int argc, char **argv)
{
    Mat img = imread("./ubuntu.png");

    // mat_test(img.clone());
    mat_type_test(img.clone());
    // look_up_table(img.clone(), 30);
    // color_reduce(img.clone(), 30);
    // roi_test(img.clone());
    // split_test(img.clone());
    // contrast_bright_test(img.clone());
    remap_test(img.clone());

    waitKey(0);

    return 0;
}