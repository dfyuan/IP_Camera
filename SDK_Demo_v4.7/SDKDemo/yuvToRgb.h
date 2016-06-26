#ifndef _YUVTORGB_H
#define _YUVTORGB_H            
extern "C" {
#include "yuv2rgb.h"
}                      
// #include "hi_vscp_devs_cli.h" 
// #include "ScreenPannel.h"
// #include "hi_dataType.h" 
#include "stdafx.h"
#include "SDKDemo.h"
class YuvToRgb
{
public:
    YuvToRgb(){}
    ~YuvToRgb(){}
    bool YUV12ToBGR(const FRAME_INFO_S *pFrameInfo, unsigned char* pBGR24); 
private:

protected:              
    bool YUV420_To_BGR24(unsigned char *puc_y, unsigned char *puc_u, unsigned char *puc_v, unsigned char *puc_rgb, int width_y, int height_y);
    bool YV12ToBGR24_Table(unsigned char *puc_y, unsigned char *puc_u, unsigned char *puc_v,unsigned char* pBGR24,int width,int height);
    bool YV12ToBGR24_Pinknoise(unsigned char *puc_y, unsigned char *puc_u, unsigned char *puc_v,unsigned char* pBGR24,int width,int height);
};


#endif