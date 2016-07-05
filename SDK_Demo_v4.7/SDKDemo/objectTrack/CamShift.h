#ifndef _CAMSHiFT_H
#define _CAMSHiFT_H
#include "opencv.hpp"
class CamShift
{
public:
    CamShift(int width, int height);
    ~CamShift();
    bool run(cv::Mat &image);
    void set_target_windows(cv::Mat &image, cv::Rect rect);
private:
    int m_width;
    int m_height;
    cv::Mat hsv;
    cv::Mat hue;
    cv::Mat mask;
    cv::Mat backproj;
    cv::Mat histimg;
    cv::MatND hist;


    cv::Rect m_selection;//用于保存鼠标选择的矩形框
    int trackObject;
    cv::Rect trackWindow;                    


};
#endif