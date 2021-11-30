/**
 * @file highgui_test.cpp
 * @brief OpenCV图形用户界面组件hightgui
 * @author sj.su (sj.su@tungthih.com.cn)
 * @version 1.0
 * @date 2021-10-20
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
 *     <th>2021-10-20
 *     <th>v0.0.1
 *     <th>sj.su
 *     <th>原型开发
 * </tr>
 * </table>
 */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define BAR_NAME    "bar_name"
#define WIN_NAME    "win_name"

Rect g_rectangle;
bool g_drawingbox = false;
RNG g_rng(1);

void on_trackbar_callback(int bar_value, void *user_data)
{
    cout << "bar value: " << bar_value << "   user data: " << (char *)user_data << endl;
}

void on_mouse_callback(int event, int x, int y, int flags, void* userdata)
{
    Mat &img_temp = *(Mat *)userdata;

    switch (event)
    {
    case EVENT_MOUSEMOVE:
        if(g_drawingbox) {
            cout << "mouse move x: " << x << " y: " << y << endl; 
            g_rectangle.width = x - g_rectangle.x;
            g_rectangle.height = y - g_rectangle.y;
        }

        break;
    
    case EVENT_LBUTTONDOWN:
        cout << "mouse button down x: " << x << " y: " << y << endl;
        g_drawingbox = true;
        g_rectangle = Rect(x, y, 0, 0);     // 记录起点

        break;

    case EVENT_LBUTTONUP:
        cout << "mouse button up: " << x << " y: " << y << endl;
        g_drawingbox = false;
        if(g_rectangle.width < 0) {
            g_rectangle.x += g_rectangle.width;
            g_rectangle.width *= -1;
        }

        if(g_rectangle.height < 0) {
            g_rectangle.y += g_rectangle.height;
            g_rectangle.height *= -1;
        }

        rectangle(img_temp, g_rectangle, Scalar(g_rng.uniform(0, 2555)));
        imshow(WIN_NAME, img_temp);

        break;

    default:
        break;
    }
}

void draw_graph(Mat &img)
{
    line(img, Point(100, 100), Point(500, 100), Scalar(255));
    circle(img, Point(500, 500), 50, Scalar(0, 255));
    rectangle(img, Rect(50, 50, 500, 500), Scalar(0, 0, 255));

    imshow("draw image", img);
}

int main(int argc, char **argv)
{
    Mat img = imread("./ubuntu.png");
    // InputArray arrimg;

    imshow(WIN_NAME, img);

    draw_graph(img);

    // 创建滑窗
    int bar_value = 0;
    char user_data[] = "user_data";
    createTrackbar(BAR_NAME, WIN_NAME, &bar_value, 30, on_trackbar_callback, user_data);

    // 创建鼠标响应
    g_rectangle = Rect(-1, -1, 0, 0);
    setMouseCallback(WIN_NAME, on_mouse_callback, (void *)&img);

    waitKey(0);

    // 获取当前bar的位置值
    int cur_bar_value = getTrackbarPos(BAR_NAME, WIN_NAME);
    cout << "current bar value: " << cur_bar_value << endl;

    return 0;
}
