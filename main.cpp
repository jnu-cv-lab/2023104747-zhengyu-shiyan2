#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

// 辅助函数：将OpenCV数据类型编号转为字符串
string type2str(int type) {
    string r;
    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);
    switch (depth) {
        case CV_8U:  r = "8U"; break;
        case CV_8S:  r = "8S"; break;
        case CV_16U: r = "16U"; break;
        case CV_16S: r = "16S"; break;
        case CV_32S: r = "32S"; break;
        case CV_32F: r = "32F"; break;
        case CV_64F: r = "64F"; break;
        default:     r = "User"; break;
    }
    r += "C";
    r += (chans + '0');
    return r;
}

int main() {
    // 任务1：读取测试图片（替换为你的图片路径）
    Mat src_img = imread("/home/lenovo/cv-course/program/微信图片_20260401231459_187_291.jpg");
    if (src_img.empty()) {
        cout << "错误：无法读取图片，请检查路径是否正确！" << endl;
        return -1;
    }
    cout << "✅ 任务1完成：成功读取图片" << endl;

    // 任务2：输出图像基本信息
    int width = src_img.cols;
    int height = src_img.rows;
    int channels = src_img.channels();
    string dtype = type2str(src_img.type());

    cout << "\n==================== 图像基本信息 ====================" << endl;
    cout << "图像尺寸(宽x高)：" << width << " × " << height << endl;
    cout << "图像通道数：" << channels << endl;
    cout << "图像数据类型：" << dtype << endl;
    cout << "========================================================" << endl;
    cout << "✅ 任务2完成：打印图像信息" << endl;

    // 任务3：显示原图
    namedWindow("原图", WINDOW_NORMAL);
    imshow("原图", src_img);
    cout << "\n✅ 任务3完成：显示原图" << endl;

    // 任务4：转换为灰度图并显示
    Mat gray_img;
    cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
    namedWindow("灰度图", WINDOW_NORMAL);
    imshow("灰度图", gray_img);
    cout << "✅ 任务4完成：转换并显示灰度图" << endl;

    // 任务5：保存灰度图
    imwrite("gray_result.jpg", gray_img);
    cout << "\n✅ 任务5完成：灰度图已保存为 gray_result.jpg" << endl;

    // 任务6：类NumPy操作（像素值+裁剪）
    // 1. 读取指定像素值
    Vec3b pixel = src_img.at<Vec3b>(100, 100);
    cout << "\n坐标(100,100)的像素值(B,G,R)：" 
         << (int)pixel[0] << ", " 
         << (int)pixel[1] << ", " 
         << (int)pixel[2] << endl;

    // 2. 裁剪左上角200x200区域
    Rect roi(0, 0, 200, 200);
    Mat crop_img = src_img(roi);
    imwrite("crop_result.jpg", crop_img);
    namedWindow("裁剪图(左上角200x200)", WINDOW_NORMAL);
    imshow("裁剪图(左上角200x200)", crop_img);
    cout << "✅ 任务6完成：读取像素值+裁剪图像并保存" << endl;

    // 等待按键后关闭窗口
    waitKey(0);
    destroyAllWindows();

    return 0;
}