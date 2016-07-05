#ifndef _MEANSHiFT_H
#define _MEANSHiFT_H
#include "opencv.hpp"
class MeanShift
{
public:
    MeanShift(int width, int height);
    ~MeanShift();
    bool run(cv::Mat &image);
    void set_target_windows(cv::Mat &image, cv::Rect rect);
//     static void onMouse( int event, int x, int y, int flags, void* param);
private:
    int m_width;
    int m_height;
    cv::Mat hsv;
    cv::Mat hue;
    cv::Mat mask;
    cv::Mat backproj;
    cv::Mat histimg;
    cv::MatND hist;




    cv::Rect trackWindow; 
    static void (*MouseCallback)(int event, int x, int y, int flags, void* userdata);
//     int hsize;
//     const static int histsize[3];
//     static float hranges[2];
//      const float* phranges;
};
#endif