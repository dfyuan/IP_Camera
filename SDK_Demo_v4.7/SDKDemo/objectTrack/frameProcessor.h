#ifndef _FRAMEPROCESSOR_H
#define _FRAMEPROCESSOR_H
//  using namespace cv;
//  using namespace std;
class FrameProcessor{  
public:  
    virtual void process(cv::Mat &input,cv::Mat &ouput)=0;  
};
class BGFGSegmentor : public FrameProcessor{  
    cv::Mat gray;//��ǰ֡�Ҷ�ͼ  
    cv::Mat background;//����ͼ����ʽΪ32λ����  
    cv::Mat backImage;//CV_8U��ʽ����ͼ  
    cv::Mat foreground;//ǰ��ͼ  
    double learningRate;//ѧϰ��  
    int threshold;//��ֵ����ȥ�Ŷ�  
public:  
    BGFGSegmentor():threshold(30),learningRate(0.6){}  
    //֡������  
    void process(cv::Mat &frame, cv::Mat &output)
    {  
        //ת��Ϊ�Ҷ�ͼ  
        cv::cvtColor (frame, gray, CV_BGR2GRAY);  
        if(background.empty ())
        {
            //��һ֡  
             gray.convertTo (background,CV_32F);
//            background = frame.clone();
        }
        //����תΪCV_8U��ʽ�Ա���ȡ�͵�ǰ֡��ľ���ֵ  
        background.convertTo (backImage, CV_8U);  
        //��ǰ֡�뱳���Ĳ��  
        cv::absdiff (backImage, gray, foreground);  
        //���˵�ǰ�����뱳����𲻴���Ŷ���  
        cv::threshold(foreground, output, threshold, 255, cv::THRESH_BINARY_INV);  
        //���±�����output��Ϊ����  
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