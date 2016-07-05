// #include "frameProcessor.h"
// 
// void BGFGSegmentor::process(Mat &frame,Mat &output){  
//     //转化为灰度图  
//     cvtColor (frame,gray,CV_BGR2GRAY);  
//     if(background.empty ())
//     {
//         //第一帧  
//         gray.convertTo (background,CV_32F);
//     }
//     //背景转为CV_8U格式以便求取和当前帧差的绝对值  
//     background.convertTo (backImage,CV_8U);  
//     //求当前帧与背景的差别  
//     absdiff (backImage,gray,foreground);  
//     //过滤掉前景中与背景差别不大的扰动点  
//     cv:: threshold(foreground,output,threshold,255,THRESH_BINARY_INV);  
//     //更新背景，output作为掩码  
//     accumulateWeighted (gray,background,learningRate,output);  
// } 