import cv2
import numpy as np
import time
def mp(bin_code):
    num_map = {'122':'X',
               '222':'0',
               '111':'1',
               '311':'2',
               '300':'3',
               '221':'4',
               '333':'5',
               '312':'6',
               '211':'7',
               '322':'8',
               '321':'9',
               '000':'#'}
    result = num_map[bin_code]
    return result

def slice_num(src_img, X, Y, Width, Height, index):
    # slice_img = cv2.rectangle(img, (X,Y), (X+Width,Y+Height), (0,255,0),2)

    img = src_img[Y:Y+Height,X:X+Width]
    # cv2.imshow('slice',slice_img)
    # cv2.waitKey(0)
    # cv2.destroyAllWindows()
    number = '#'
    codes = '000'
    img_row = img.shape[0]
    img_col = img.shape[1]
    # print('img_col = %d,img_row = %d'%(img_col,img_row))
    filter_x1 = int(img_row*0.3)#row 18
    filter_x2 = int(img_row*0.66)#row 5
    filter_y = int(img_col*0.5)
    count1 = 0
    count2 = 0
    count3 = 0

    for i in range(0,img_col):
        # print(img[filter_x1,i])
        if (i == 0 and img[filter_x1,i] == 255):
            count1 += 1
        elif i > 0 and img[filter_x1,i] == 255 and img[filter_x1,i-1] != 255:
            count1 += 1
    # print('\n')
    for j in range(0,img_col):
        # print(img[filter_x2,j])
        if (j == 0 and img[filter_x2,j] == 255):
            count2 += 1
        elif j > 0 and img[filter_x2,j] == 255 and img[filter_x2,j-1] != 255:
            count2 += 1
    for k in range(0,img_row):
        if (k == 0 and img[k,filter_y] == 255):
            count3 += 1
        elif k > 0 and img[k,filter_y] == 255 and img[k-1,filter_y] != 255:
            count3 += 1
    # cv2.line(img,(filter_x1,0),(filter_x1,img_col),(0,0,255))
    if count3 == 3 and count1 == 1 and count2 == 1:
        for m in range(0,img_col):
            if img[filter_x1,m] == 255:
                tmp1 = m
        for n in range(0,img_col):
            if img[filter_x2,n] == 255:
                tmp2 = n
                break
        if tmp1 > img_col/2 and tmp2 > img_col/2:
            count1 = 0
            count2 = 0
        elif tmp1 < img_col/2 and tmp2 > img_col/2:
            count1 = 3
            count2 = 3

    codes = repr(count3)+repr(count1)+repr(count2)
    # print("codes")
    # print(count3,count1,count2)

    number = mp(codes)
    print('the number '+str(number))

    return number

def rect_find(path):
    start_time = time.time()
    srcImg = cv2.imread(path)
    dstImg = srcImg.copy()
    srcImg = cv2.cvtColor(srcImg,cv2.COLOR_BGR2GRAY)
    srcImg = cv2.threshold(srcImg, 100, 255, cv2.THRESH_BINARY)[1]
    srcImg = cv2.bitwise_not(srcImg,srcImg)

    contours, hierarcy = cv2.findContours(srcImg, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)

    numbers = []
    for i in range(0,len(contours)):
        box_i = cv2.minAreaRect(contours[i])
        boundRect_i = cv2.boundingRect(contours[i])
        # print('11111111')
        # print(boundRect_i)
        dstImg = cv2.rectangle(dstImg, (boundRect_i[0], boundRect_i[1]), (boundRect_i[0]+boundRect_i[2], boundRect_i[1]+boundRect_i[3]),(0,0,255))
        # cv2.imshow("img1", dstImg)
        # cv2.waitKey(0)
        tmp = slice_num(srcImg, boundRect_i[0], boundRect_i[1], boundRect_i[2], boundRect_i[3], i)
        numbers.append(tmp)
        finish_time = time.time()
        print('cost %f sec to process rect %d\n'%(finish_time-start_time, i))
        start_time = time.time()

    # cv2.imshow('1',dstImg)
    # cv2.waitKey(0)
    # cv2.destroyAllWindows()
    numbers = numbers[::-1]
    numbers = "".join(numbers)
    return numbers

if __name__ == '__main__':
    total_start_time = time.time()
    path = '/Users/tongbohan/Desktop/RISC-V/RISC-V Digilent 测试库/身份证/10.jpg'
    answer = rect_find(path)
    print(answer)
    total_end_time = time.time()
    print('total cost %f sec'%(total_end_time-total_start_time))
