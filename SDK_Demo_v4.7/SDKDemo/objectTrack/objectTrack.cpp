#include "objectTrack.h"

void objectTrack::run(cv::Mat &frame,cv::Mat &output)
{
//      process.process(frame, output);  
//      cv::imshow("output", output);

    //m_cs->run(frame);
    m_ms->run(frame);
}
