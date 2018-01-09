#include "opencv2/opencv.hpp"

std::vector<cv::Rect> detectLetters(cv::Mat img)
{
    std::vector<cv::Rect> boundRect;
    cv::Mat img_gray, img_sobel, img_threshold, element;
    cvtColor(img, img_gray, CV_BGR2GRAY);
    cv::Sobel(img_gray, img_sobel, CV_8U, 1, 0, 3, 1, 0, cv::BORDER_DEFAULT);
    cv::threshold(img_sobel, img_threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
    element = getStructuringElement(cv::MORPH_RECT, cv::Size(17, 3) );
    cv::morphologyEx(img_threshold, img_threshold, CV_MOP_CLOSE, element); //Does the trick
    std::vector< std::vector< cv::Point> > contours;
    cv::findContours(img_threshold, contours, 0, 1);
    std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
    for( int i = 0; i < contours.size(); i++ )
        if (contours[i].size()>110)
        {
            cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );
            cv::Rect appRect( boundingRect( cv::Mat(contours_poly[i]) ));
            if (appRect.width>appRect.height)
                boundRect.push_back(appRect);
        }
    return boundRect;
}

int main(int argc,char** argv)
{
    int N = 17;
    for (int i = 10; i < N; ++i)
    {
        //Read
        cv::Mat img = cv::imread("test/test+example+6-" + std::to_string(i) + ".jpg");
        //Detect
        std::vector<cv::Rect> letterBBoxes = detectLetters(img);

        //Display
        for(int i=0; i< letterBBoxes.size(); i++)
            cv::rectangle(img,letterBBoxes[i],cv::Scalar(0,255,0),3,8,0);
        cv::imwrite( "test/res_" + std::to_string(i) + ".jpg", img);
    }

    return 0;

    //Read
    cv::Mat img1=cv::imread("test/test_1.jpg");
    cv::Mat img2=cv::imread("test/test_2.jpg");
    cv::Mat img3=cv::imread("test/test_3.jpg");
    cv::Mat img4=cv::imread("test/test_4.jpg");
    //Detect
    std::vector<cv::Rect> letterBBoxes1=detectLetters(img1);
    std::vector<cv::Rect> letterBBoxes2=detectLetters(img2);
    std::vector<cv::Rect> letterBBoxes3=detectLetters(img3);
    std::vector<cv::Rect> letterBBoxes4=detectLetters(img4);

    //Display
    for(int i=0; i< letterBBoxes1.size(); i++)
        cv::rectangle(img1,letterBBoxes1[i],cv::Scalar(0,255,0),3,8,0);
    cv::imwrite( "test/res_1.jpg", img1);

    for(int i=0; i< letterBBoxes2.size(); i++)
        cv::rectangle(img2,letterBBoxes2[i],cv::Scalar(0,255,0),3,8,0);
    cv::imwrite( "test/res_2.jpg", img2);

    for(int i=0; i< letterBBoxes3.size(); i++)
        cv::rectangle(img3,letterBBoxes3[i],cv::Scalar(0,255,0),3,8,0);
    cv::imwrite( "test/res_3.jpg", img3);

    for(int i=0; i< letterBBoxes4.size(); i++)
        cv::rectangle(img4,letterBBoxes4[i],cv::Scalar(0,255,0),3,8,0);
    cv::imwrite( "test/res_4.jpg", img4);


    return 0;
}
