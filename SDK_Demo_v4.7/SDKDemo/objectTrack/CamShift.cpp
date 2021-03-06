#include "CamShift.h"
// using namespace cv;
CamShift::CamShift(int width, int height):m_width(width), m_height(height), trackObject(0)
{
    //     image = cvCreateImage( cvGetSize(frame), 8, 3 );
    //     hsv = cvCreateImage( cvGetSize(frame), 8, 3 );  
    //     hue = cvCreateImage( cvGetSize(frame), 8, 1 );  
    //     mask = cvCreateImage( cvGetSize(frame), 8, 1 );  
    //     backproject = cvCreateImage( cvGetSize(frame), 8, 1 );  
    //     hist = cvCreateHist( 1, &hdims, CV_HIST_ARRAY, &hranges, 1 );   //float hranges_arr[] = {0,180};  float* hranges = hranges_arr;  //int hdims = 16;  
    //     //构建直方图  
    //     histimg = cvCreateImage( cvSize(320,200), 8, 3 );   //????why the porpuse  
    //     cvZero( histimg ); 

//     hsv.create(m_height, m_width, CV_8UC3); 
//     hue.create(m_height, m_width, CV_8UC1);
//     mask.create(m_height, m_width, CV_8UC1);
//     backproj.create(m_height, m_width, CV_8UC1);
    histimg.zeros(200, 320, CV_8UC3);


    m_selection.x = 0;//矩形左上角顶点坐标
    m_selection.y = 200;
    m_selection.width = 100;//矩形宽
    m_selection.height = 100;//矩形高
    //     m_selection &= cv::Rect(0, 0, image.cols, image.rows);//用于确保所选的矩形区域在图片范围内
    trackObject = -1;

    //histing
}

void CamShift::set_target_windows(cv::Mat &image, cv::Rect rect)
{
    m_selection = rect;

}
CamShift::~CamShift()
{

}                    
bool CamShift::run(cv::Mat &image)
{                           
              
    const int histsize[]={16,16,16};
    int hsize = 16;

    float hranges[] = {0,180};//hranges在后面的计算直方图函数中要用到
    const float* phranges = hranges;
    int vmin = 10, vmax = 256, smin = 30;
    cvtColor(image, hsv, CV_BGR2HSV);//将rgb摄像头帧转化成hsv空间的

    int _vmin = vmin, _vmax = vmax;

    //inRange函数的功能是检查输入数组每个元素大小是否在2个给定数值之间，可以有多通道,mask保存0通道的最小值，也就是h分量
    //这里利用了hsv的3个通道，比较h,0~180,s,smin~256,v,min(vmin,vmax),max(vmin,vmax)。如果3个通道都在对应的范围内，则
    //mask对应的那个点的值全为1(0xff)，否则为0(0x00).
    inRange(hsv, cv::Scalar(0, smin, MIN(_vmin,_vmax)),
        cv::Scalar(180, 256, MAX(_vmin, _vmax)), mask);
    int ch[] = {0, 0};
    hue.create(hsv.size(), hsv.depth());//hue初始化为与hsv大小深度一样的矩阵，色调的度量是用角度表示的，红绿蓝之间相差120度，反色相差180度
    mixChannels(&hsv, 1, &hue, 1, ch, 1);//将hsv第一个通道(也就是色调)的数复制到hue中，0索引数组

    if( trackObject < 0 )//鼠标选择区域松开后，该函数内部又将其赋值1
    {
        //此处的构造函数roi用的是Mat hue的矩阵头，且roi的数据指针指向hue，即共用相同的数据，select为其感兴趣的区域
        cv::Mat roi(hue, m_selection), maskroi(mask, m_selection);//mask保存的hsv的最小值

        //calcHist()函数第一个参数为输入矩阵序列，第2个参数表示输入的矩阵数目，第3个参数表示将被计算直方图维数通道的列表，第4个参数表示可选的掩码函数
        //第5个参数表示输出直方图，第6个参数表示直方图的维数，第7个参数为每一维直方图数组的大小，第8个参数为每一维直方图bin的边界
        calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);//将roi的0通道计算直方图并通过mask放入hist中，hsize为每一维直方图的大小
        normalize(hist, hist, 0, 255, CV_MINMAX);//将hist矩阵进行数组范围归一化，都归一化到0~255

        trackWindow = m_selection;
        trackObject = 1;//只要鼠标选完区域松开后，且没有按键盘清0键'c'，则trackObject一直保持为1，因此该if函数只能执行一次，除非重新选择跟踪区域

        histimg = cv::Scalar::all(0);//与按下'c'键是一样的，这里的all(0)表示的是标量全部清0
        int binW = histimg.cols / hsize;  //histing是一个200*300的矩阵，hsize应该是每一个bin的宽度，也就是histing矩阵能分出几个bin出来
        cv::Mat buf(1, hsize, CV_8UC3);//定义一个缓冲单bin矩阵
        for( int i = 0; i < hsize; i++ )//saturate_case函数为从一个初始类型准确变换到另一个初始类型
            buf.at<cv::Vec3b>(i) = cv::Vec3b(cv::saturate_cast<uchar>(i*180./hsize), 255, 255);//Vec3b为3个char值的向量
        cv::cvtColor(buf, buf, CV_HSV2BGR);//将hsv又转换成bgr

        for( int i = 0; i < hsize; i++ )
        {
            int val = cv::saturate_cast<int>(hist.at<float>(i)*histimg.rows/255);//at函数为返回一个指定数组元素的参考值
            cv::rectangle( histimg, cv::Point(i*binW,histimg.rows),    //在一幅输入图像上画一个简单抽的矩形，指定左上角和右下角，并定义颜色，大小，线型等
                cv::Point((i+1)*binW,histimg.rows - val),
                cv::Scalar(buf.at<cv::Vec3b>(i)), -1, 8 );
        }
    }

    cv::calcBackProject(&hue, 1, 0, hist, backproj, &phranges);//计算直方图的反向投影，计算hue图像0通道直方图hist的反向投影，并让入backproj中
    backproj &= mask;

    //opencv2.0以后的版本函数命名前没有cv两字了，并且如果函数名是由2个意思的单词片段组成的话，且前面那个片段不够成单词，则第一个字母要
    //大写，比如Camshift，如果第一个字母是个单词，则小写，比如meanShift，但是第二个字母一定要大写
    cv::RotatedRect trackBox = cv::CamShift(backproj, trackWindow,               //trackWindow为鼠标选择的区域，TermCriteria为确定迭代终止的准则
        cv::TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));//CV_TERMCRIT_EPS是通过forest_accuracy,CV_TERMCRIT_ITER
    if( trackWindow.area() <= 1 )                                                  //是通过max_num_of_trees_in_the_forest  
    {
        int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5)/6;
        trackWindow = cv::Rect(trackWindow.x - r, trackWindow.y - r,
            trackWindow.x + r, trackWindow.y + r) &
            cv::Rect(0, 0, cols, rows);//Rect函数为矩阵的偏移和大小，即第一二个参数为矩阵的左上角点坐标，第三四个参数为矩阵的宽和高
    }

    //     if( backprojMode )
//     cvtColor( backproj, image, CV_GRAY2BGR );//因此投影模式下显示的也是rgb图？
     ellipse( image, trackBox, cv::Scalar(0,0,255), 3, CV_AA );//跟踪的时候以椭圆为代表目标 
//    rectangle(image,cv::Point(trackWindow.x,trackWindow.y),cv::Point(trackWindow.x+trackWindow.width,trackWindow.y+trackWindow.height),cv::Scalar(0,0,255),2,CV_AA);

    //     if( false && m_selection.width > 0 && m_selection.height > 0 )
    //     {
    //           cv::Mat roi(image, m_selection);
    //           bitwise_not(roi, roi);//bitwise_not为将每一个bit位取反
    //     }

    imshow( "CamShift Demo", image );
    imshow( "Histogram", histimg );
    cv::waitKey(1);
    return true;
}
