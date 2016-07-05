#ifndef _OBJECTTRACK_H
#define _OBJECTTRACK_H
#include "opencv.hpp"
#include "frameProcessor.h"
#include "CamShift.h"
#include "meanShift.h"
class objectTrack
{
public:
    objectTrack()
    {
        m_cs = new CamShift(1280, 720);
        m_ms = new MeanShift(1280, 720);
    }
    ~objectTrack()
    {
        delete m_cs;
    }
    void run(cv::Mat &frame,cv::Mat &output);
private:
    //cv::Mat m_mat;
    BGFGSegmentor process;
    CamShift *m_cs;
    MeanShift *m_ms;
};
#endif