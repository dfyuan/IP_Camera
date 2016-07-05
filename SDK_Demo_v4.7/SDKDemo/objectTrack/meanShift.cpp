#include "meanShift.h"

cv::Rect m_selection;//���ڱ������ѡ��ľ��ο�
int trackObject; 
cv::Point origin;
std::string displayStr = "CamShift Demo";
bool selectObject = false;

void onMouse( int event, int x, int y, int flags, void* param)
{
    if( selectObject )//ֻ�е�����������ȥʱ����Ч��Ȼ��ͨ��if�������Ϳ���ȷ����ѡ��ľ�������selection��
    {
        m_selection.x = std::min(x, origin.x);//�������ϽǶ�������
        m_selection.y = std::min(y, origin.y);
        m_selection.width = std::abs(x - origin.x);//���ο�
        m_selection.height = std::abs(y - origin.y);//���θ�

        //         m_selection &= cv::Rect(0, 0, image.cols, image.rows);//����ȷ����ѡ�ľ���������ͼƬ��Χ��
    }

    switch( event )
    {
    case CV_EVENT_LBUTTONDOWN:
        origin = cv::Point(x,y);
        m_selection = cv::Rect(x,y,0,0);//���հ���ȥʱ��ʼ����һ����������
        selectObject = true;
        break;
    case CV_EVENT_LBUTTONUP:
        selectObject = false;
        if( m_selection.width > 0 && m_selection.height > 0 )
            trackObject = -1;
        break;
    }
}
// using namespace cv;
// void MeanShift::(*MouseCallback)(int event, int x, int y, int flags, void* userdata) = onMouse;
MeanShift::MeanShift(int width, int height)
    :m_width(width), m_height(height)//, trackObject(false)//, hsize(16),phranges(hranges)
//     ,MouseCallback(onMouse)
{
    //     image = cvCreateImage( cvGetSize(frame), 8, 3 );
    //     hsv = cvCreateImage( cvGetSize(frame), 8, 3 );  
    //     hue = cvCreateImage( cvGetSize(frame), 8, 1 );  
    //     mask = cvCreateImage( cvGetSize(frame), 8, 1 );  
    //     backproject = cvCreateImage( cvGetSize(frame), 8, 1 );  
    //     hist = cvCreateHist( 1, &hdims, CV_HIST_ARRAY, &hranges, 1 );   //float hranges_arr[] = {0,180};  float* hranges = hranges_arr;  //int hdims = 16;  
    //     //����ֱ��ͼ  
    //     histimg = cvCreateImage( cvSize(320,200), 8, 3 );   //????why the porpuse  
    //     cvZero( histimg ); 

//     hsv.create(m_height, m_width, CV_8UC3); 
//     hue.create(m_height, m_width, CV_8UC1);
//     mask.create(m_height, m_width, CV_8UC1);
//     backproj.create(m_height, m_width, CV_8UC1);
    trackObject =false;

    histimg.zeros(200, 320, CV_8UC3);

    cv::namedWindow( displayStr, 1 );
    cv::setMouseCallback( displayStr, onMouse, 0 );//��Ϣ��Ӧ����


    //m_selection.x = 0;//�������ϽǶ�������
    //m_selection.y = 200;
    //m_selection.width = 100;//���ο�
    //m_selection.height = 100;//���θ�
    ////     m_selection &= cv::Rect(0, 0, image.cols, image.rows);//����ȷ����ѡ�ľ���������ͼƬ��Χ��
    trackObject = 0;

    //histing
}



void MeanShift::set_target_windows(cv::Mat &image, cv::Rect rect)
{
    m_selection = rect;

}
MeanShift::~MeanShift()
{

}             
//     const int MeanShift::histsize[]={16,16,16}; 
//     float MeanShift::hranges[] = {0,180};//hranges�ں���ļ���ֱ��ͼ������Ҫ�õ�
// //    const float* phranges = hranges; 

bool MeanShift::run(cv::Mat &image)
{                 
    const int histsize[]={16,16,16};
    int hsize = 16;
    float hranges[] = {0,180};//hranges�ں���ļ���ֱ��ͼ������Ҫ�õ�
    const float* phranges = hranges;

    int vmin = 10, vmax = 256, smin = 30;

    cvtColor(image, hsv, CV_BGR2HSV);//��rgb����ͷ֡ת����hsv�ռ��
    if( trackObject )//trackObject��ʼ��Ϊ0,���߰�����̵�'c'����ҲΪ0������굥���ɿ���Ϊ-1
    {

   
    int _vmin = vmin, _vmax = vmax;

    //inRange�����Ĺ����Ǽ����������ÿ��Ԫ�ش�С�Ƿ���2��������ֵ֮�䣬�����ж�ͨ��,mask����0ͨ������Сֵ��Ҳ����h����
    //����������hsv��3��ͨ�����Ƚ�h,0~180,s,smin~256,v,min(vmin,vmax),max(vmin,vmax)�����3��ͨ�����ڶ�Ӧ�ķ�Χ�ڣ���
    //mask��Ӧ���Ǹ����ֵȫΪ1(0xff)������Ϊ0(0x00).
    inRange(hsv, cv::Scalar(0, smin, MIN(_vmin,_vmax)),
        cv::Scalar(180, 256, MAX(_vmin, _vmax)), mask);
    int ch[] = {0, 0};
    hue.create(hsv.size(), hsv.depth());//hue��ʼ��Ϊ��hsv��С���һ���ľ���ɫ���Ķ������ýǶȱ�ʾ�ģ�������֮�����120�ȣ���ɫ���180��
    mixChannels(&hsv, 1, &hue, 1, ch, 1);//��hsv��һ��ͨ��(Ҳ����ɫ��)�������Ƶ�hue�У�0��������

    if(trackObject < 0)//���ѡ�������ɿ��󣬸ú����ڲ��ֽ��丳ֵ1
    {
        //�˴��Ĺ��캯��roi�õ���Mat hue�ľ���ͷ����roi������ָ��ָ��hue����������ͬ�����ݣ�selectΪ�����Ȥ������
        cv::Mat roi(hue, m_selection), maskroi(mask, m_selection);//mask�����hsv����Сֵ

        //calcHist()������һ������Ϊ����������У���2��������ʾ����ľ�����Ŀ����3��������ʾ��������ֱ��ͼά��ͨ�����б���4��������ʾ��ѡ�����뺯��
        //��5��������ʾ���ֱ��ͼ����6��������ʾֱ��ͼ��ά������7������Ϊÿһάֱ��ͼ����Ĵ�С����8������Ϊÿһάֱ��ͼbin�ı߽�
        calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);//��roi��0ͨ������ֱ��ͼ��ͨ��mask����hist�У�hsizeΪÿһάֱ��ͼ�Ĵ�С
        normalize(hist, hist, 0, 255, CV_MINMAX);//��hist����������鷶Χ��һ��������һ����0~255

        trackWindow = m_selection;
        trackObject = 1;//ֻҪ���ѡ�������ɿ�����û�а�������0��'c'����trackObjectһֱ����Ϊ1����˸�if����ֻ��ִ��һ�Σ���������ѡ���������

        histimg = cv::Scalar::all(0);//�밴��'c'����һ���ģ������all(0)��ʾ���Ǳ���ȫ����0
        int binW = histimg.cols / hsize;  //histing��һ��200*300�ľ���hsizeӦ����ÿһ��bin�Ŀ�ȣ�Ҳ����histing�����ֳܷ�����bin����
        cv::Mat buf(1, hsize, CV_8UC3);//����һ�����嵥bin����
        for( int i = 0; i < hsize; i++ )//saturate_case����Ϊ��һ����ʼ����׼ȷ�任����һ����ʼ����
            buf.at<cv::Vec3b>(i) = cv::Vec3b(cv::saturate_cast<uchar>(i*180./hsize), 255, 255);//Vec3bΪ3��charֵ������
        cv::cvtColor(buf, buf, CV_HSV2BGR);//��hsv��ת����bgr

        for( int i = 0; i < hsize; i++ )
        {
            int val = cv::saturate_cast<int>(hist.at<float>(i)*histimg.rows/255);//at����Ϊ����һ��ָ������Ԫ�صĲο�ֵ
            cv::rectangle( histimg, cv::Point(i*binW,histimg.rows),    //��һ������ͼ���ϻ�һ���򵥳�ľ��Σ�ָ�����ϽǺ����½ǣ���������ɫ����С�����͵�
                cv::Point((i+1)*binW,histimg.rows - val),
                cv::Scalar(buf.at<cv::Vec3b>(i)), -1, 8 );
        }
    }

    cv::calcBackProject(&hue, 1, 0, hist, backproj, &phranges);//����ֱ��ͼ�ķ���ͶӰ������hueͼ��0ͨ��ֱ��ͼhist�ķ���ͶӰ��������backproj��
    backproj &= mask;

    //opencv2.0�Ժ�İ汾��������ǰû��cv�����ˣ������������������2����˼�ĵ���Ƭ����ɵĻ�����ǰ���Ǹ�Ƭ�β����ɵ��ʣ����һ����ĸҪ
    //��д������Camshift�������һ����ĸ�Ǹ����ʣ���Сд������meanShift�����ǵڶ�����ĸһ��Ҫ��д
                meanShift(backproj, trackWindow,               //trackWindowΪ���ѡ�������TermCriteriaΪȷ��������ֹ��׼��
                    cv::TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));//CV_TERMCRIT_EPS��ͨ��forest_accuracy,CV_TERMCRIT_ITER
    if( trackWindow.area() <= 1 )                                                  //��ͨ��max_num_of_trees_in_the_forest  
    {
        int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5)/6;
        trackWindow = cv::Rect(trackWindow.x - r, trackWindow.y - r,
            trackWindow.x + r, trackWindow.y + r) &
            cv::Rect(0, 0, cols, rows);//Rect����Ϊ�����ƫ�ƺʹ�С������һ��������Ϊ��������Ͻǵ����꣬�����ĸ�����Ϊ����Ŀ�͸�
    }

    //     if( backprojMode )
//     cvtColor( backproj, image, CV_GRAY2BGR );//���ͶӰģʽ����ʾ��Ҳ��rgbͼ��
//     ellipse( image, trackBox, cv::Scalar(0,0,255), 3, CV_AA );//���ٵ�ʱ������ԲΪ����Ŀ�� 
    rectangle(image,cv::Point(trackWindow.x,trackWindow.y),cv::Point(trackWindow.x+trackWindow.width,trackWindow.y+trackWindow.height),cv::Scalar(0,0,255),2,CV_AA);
    }
     if( selectObject && m_selection.width > 0 && m_selection.height > 0 )
     {
           cv::Mat roi(image, m_selection);
           cv::bitwise_not(roi, roi);//bitwise_notΪ��ÿһ��bitλȡ��
     }

    imshow( displayStr, image );
    imshow( "Histogram", histimg );
    cv::waitKey(1);
    return true;
}
