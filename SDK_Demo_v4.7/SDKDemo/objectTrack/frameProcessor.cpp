// #include "frameProcessor.h"
// 
// void BGFGSegmentor::process(Mat &frame,Mat &output){  
//     //ת��Ϊ�Ҷ�ͼ  
//     cvtColor (frame,gray,CV_BGR2GRAY);  
//     if(background.empty ())
//     {
//         //��һ֡  
//         gray.convertTo (background,CV_32F);
//     }
//     //����תΪCV_8U��ʽ�Ա���ȡ�͵�ǰ֡��ľ���ֵ  
//     background.convertTo (backImage,CV_8U);  
//     //��ǰ֡�뱳���Ĳ��  
//     absdiff (backImage,gray,foreground);  
//     //���˵�ǰ�����뱳����𲻴���Ŷ���  
//     cv:: threshold(foreground,output,threshold,255,THRESH_BINARY_INV);  
//     //���±�����output��Ϊ����  
//     accumulateWeighted (gray,background,learningRate,output);  
// } 