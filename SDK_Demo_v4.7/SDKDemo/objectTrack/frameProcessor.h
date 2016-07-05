#ifndef _FRAMEPROCESSOR_H
#define _FRAMEPROCESSOR_H
//  using namespace cv;
//  using namespace std;
class FrameProcessor{  
public:  
    virtual void process(cv::Mat &input,cv::Mat &ouput)=0;  
};
class BGFGSegmentor : public FrameProcessor{  
    cv::Mat gray;//当前帧灰度图  
    cv::Mat background;//背景图，格式为32位浮点  
    cv::Mat backImage;//CV_8U格式背景图  
    cv::Mat foreground;//前景图  
    double learningRate;//学习率  
    int threshold;//阈值，滤去扰动  
public:  
    BGFGSegmentor():threshold(30),learningRate(0.6){}  
    //帧处理函数  
    void process(cv::Mat &frame, cv::Mat &output)
    {  
        //转化为灰度图  
        cv::cvtColor (frame, gray, CV_BGR2GRAY);  
        if(background.empty ())
        {
            //第一帧  
             gray.convertTo (background,CV_32F);
//            background = frame.clone();
        }
        //背景转为CV_8U格式以便求取和当前帧差的绝对值  
        background.convertTo (backImage, CV_8U);  
        //求当前帧与背景的差别  
        cv::absdiff (backImage, gray, foreground);  
        //过滤掉前景中与背景差别不大的扰动点  
        cv::threshold(foreground, output, threshold, 255, cv::THRESH_BINARY_INV);  
        //更新背景，output作为掩码  
        cv::accumulateWeighted (gray, background, learningRate, output); 

//         std::vector<std::vector<cv::Point>> contours;
//         std::vector<cv::Vec4i>hierarchy;
//         cv::findContours(gray, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

//         CvMemStorage* storage = cvCreateMemStorage( 0 );
//         CvSeq* contours = NULL;
// //         IplImage img(gray);
        std::vector<std::vector<cv::Point>> contours;
        //cv::findContours(output, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE );
//         for( ; contours != NULL; contours = contours -> h_next )
//         {
//             CvRect rect = cv::boundingRect( *contours);
//             cv::rectangle( gray, cvPoint( rect.x, rect.y ),cvPoint( rect.x + rect.width, rect.y + rect.height ), cvScalar(0,0,0), 0 );
//         }

        gray.convertTo (background, CV_32F); 
//         background = frame.clone();
    }  
};
#endif