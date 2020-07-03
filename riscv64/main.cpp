//
//  main.cpp
//  cv-riscv
//
//  Created by Low Tech on 2020/7.2.
//  Copyright © 2020 Low Tech. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <stdio.h>
using namespace std;
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
using namespace cv;

map<string, char> mp;

void map_init(){
    mp["122"] = 'X';
    mp["222"] = '0';
    mp["111"] = '1';
    mp["311"] = '2';
    mp["300"] = '3';
    mp["221"] = '4';
    mp["333"] = '5';
    mp["312"] = '6';
    mp["211"] = '7';
    mp["322"] = '8';
    mp["321"] = '9';

//    string a = "111";
//    printf("maptest:%c\n",mp[a]);
}

char read_num(Mat &img){
    char number = '#';
//    vector<int> filter_x1, filter_x2, filter_y;
//    vector<int> num_vector;
    int filter_x1, filter_x2, filter_y;
    int tmp1, tmp2;
    string codes = "000";
    filter_x1 = int(img.rows*0.3);
//    filter_x1 = int(img.rows*0.4);
    filter_x2 = int(img.rows*0.66);
    filter_y = int(img.cols*0.5);

//    printf("row = %d ; col = %d\n",img.rows,img.cols);
//    printf("%d\n",filter_x1);

    int count1 = 0, count2 = 0, count3 = 0;
    uchar* data1 = img.ptr<uchar>(filter_x1);
    uchar* data2 = img.ptr<uchar>(filter_x2);
    Mat img_rot;
//    img.copyTo(img_rot);
    transpose(img, img_rot);
//    imshow("trans",img_rot);
//    waitKey();
    uchar* data3 = img_rot.ptr<uchar>(filter_y);
    for(int i = 0;i<img.cols;i++){
//        printf("i = %d, data = %d\n",i,data1[i]);
        if((i == 0 && data1[i] == 255) || (i >0 && data1[i] == 255 && data1[i-1] != 255)){
//            printf("i = %d, data = %d\n",i,data1[i]);
//            vector_x1.push_back(i);

            count1++;
//            printf("i = %d\n",i);
//        if(i>1 && data[i-1] == )
        }
    }

        for(int j = 0;j<img.cols;j++){
            if((j == 0 && data2[j] == 255) || (j >0 && data2[j] == 255 && data2[j-1] != 255)){
//                printf("j = %d, data = %d\n",j,data2[j]);
//                vector_x1.push_back(i);
                count2++;
    //            printf("i = %d\n",i);
    //        if(i>1 && data[i-1] == )
            }
        }

        for(int k = 0;k<img_rot.cols;k++){
//            printf("k = %d, data = %d\n",k,data3[k]);

            if((k == 0 && data3[k] == 255) || (k >0 && data3[k] == 255 && data3[k-1] != 255)){
//                printf("k = %d, data = %d\n",k,data3[k]);
//                vector_x1.push_back(i);
                count3++;
    //            printf("i = %d\n",i);
    //        if(i>1 && data[i-1] == )
            }
        }
    if(count3 == 3 && count1 == 1 && count2 == 1){
        for(int i = 0;i<img.cols;i++){
            if(data1[i] == 255){
                tmp1 = i;
                break;
            }
        }
        for(int j = 0;j<img.cols;j++){
            if(data2[j] == 255){
                tmp2 = j;
                break;
            }
        }
        if(tmp1 > int(img.cols/2) && tmp2 > int(img.cols/2)){
            count1 = 0;
            count2 = 0;
        }
        else if (tmp1 < int(img.cols/2) && tmp2 > int(img.cols/2)){
            count1 = 3;
            count2 = 3;
        }
    }
//    else if (count3 == 3 && count1 == 1 && count2 == 1)

//    printf("num3: %d\n", count3);
//    printf("num1: %d\n", count1);
//    printf("num2: %d\n", count2);
    codes[0] = 48+count3;
    codes[1] = 48+count1;
    codes[2] = 48+count2;
//    num_vector.push_back(count3);
//    num_vector.push_back(count1);
//    num_vector.push_back(count2);

//    filter_x1 = int(img.rows*0.4);
//    filter_x2 = int(img.rows*0.66);
//    filter_y = int(img.cols*0.5);
//    x1 = (filter_x1 == 1);
//    x2 = (filter_x2 == 1);
//    y = (filter_y == 1);
//    printf("%d\n",filter_x1);

    number = mp[codes];
//    cout<<"codes: "<<codes<<endl;
//    printf("a = %c\n",mp[codes]);
    return number;
}

char slice_num(Mat img, int X, int Y, int Width, int Height, int index){
    Mat slice_img(img, Rect(Point(X,Y), Point(X+Width, Y+Height)));

//    imwrite("/Users/tongbohan/Desktop/"+to_string(index)+".jpg", slice_img);
//    printf("index: %d\n",index);
    char result = read_num(slice_img);
//    printf("result = %c\n",result);
//    imshow("slice", slice_img);
//    waitKey(0);
    return result;
}

int main(int argc, const char * argv[]) {
//    // insert code here...
//    cout << "Hello, World!\n";
//    string path = "/Users/tongbohan/Desktop/RISC-V/RISC-V Digilent 测试库/身份证/4.jpg";
//    cv::Mat image;
//    image = cv::imread("/Users/tongbohan/Desktop/RISC-V/RISC-V Digilent 测试库/身份证/4.jpg",cv::IMREAD_GRAYSCALE);
//    cout<<"row: "<<image.rows<<" col: "<<image.cols<<" channel: "<<image.channels()<<endl;
//    return 0;
    FILE *fp = fopen("result.txt", "a");
    map_init();
    vector<char> results;
    printf("\nread pic");
    printf("%s\n",argv[1]);
    Mat srcImg = imread(argv[1]);

    cvtColor(srcImg, srcImg, COLOR_BGR2GRAY);
    threshold(srcImg, srcImg, 100, 255, THRESH_BINARY); //二值化
    bitwise_not(srcImg, srcImg);
//    imshow("threshold", srcImg);
//    waitKey();
    Mat dstImg = srcImg.clone();
    vector<vector<Point>> contours;
    vector<Vec4i> hierarcy;
    findContours(srcImg, contours, hierarcy, RETR_EXTERNAL, CHAIN_APPROX_NONE);
    vector<Rect> boundRect(contours.size());  //定义外接矩形集合
    vector<RotatedRect> box(contours.size()); //定义最小外接矩形集合
    Point2f rect[4];
//    for(int i=0; i<contours.size(); i++)
    for(int i=contours.size()-1; i>=0; i--)
    {
        char tmp;
        box[i] = minAreaRect(Mat(contours[i]));  //计算每个轮廓最小外接矩形
        boundRect[i] = boundingRect(Mat(contours[i]));
//        printf("%d %d %d %d\n",boundRect[i].x, boundRect[i].y, boundRect[i].width, boundRect[i].height);
    //    circle(dstImg, Point(box[i].center.x, box[i].center.y), 5, Scalar(0, 255, 0), -1, 8);  //绘制最小外接矩形的中心点
        box[i].points(rect);  //把最小外接矩形四个端点复制给rect数组
        tmp = slice_num(dstImg, boundRect[i].x, boundRect[i].y, boundRect[i].width, boundRect[i].height, i);
        rectangle(dstImg, Point(boundRect[i].x, boundRect[i].y), Point(boundRect[i].x + boundRect[i].width, boundRect[i].y + boundRect[i].height), Scalar(0, 255, 0), 2, 8);
        results.push_back(tmp);

//    for(int j=0; j<4; j++)
//   {
//      line(dstImg, rect[j], rect[(j+1)%4], Scalar(0, 0, 255), 2, 8);  //绘制最小外接矩形每条边
//   }
    }
    printf("results: \n");
    int i = 0;
//    printf("%c\n", *(argv[1]+i));
//    printf("%c\n", *(argv[1]+1));
//    printf("%c\n", *(argv[1]+2));
    while(*(argv[1]+i) != '.'){
        fprintf(fp, "%c", *(argv[1]+i));
        i++;
    }
    fprintf(fp, " ");
    for(vector<char>::iterator it = results.begin();it != results.end();it++){
        printf("%c",*it);
        fprintf(fp, "%c", *it);
    }
    printf("\n");
    fprintf(fp, "\n");
//    imshow("dst", dstImg);
//    waitKey(0);
    fclose(fp);
}


