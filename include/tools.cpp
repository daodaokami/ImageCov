//
// Created by lut on 18-10-16.
//

#include <iostream>
#include "image.h"
#include "tools.h"
using namespace std;
namespace lutTools {
    void Tools::Cov(const Image *ptr_image, const double *patch, const int W, const int H, const int border_type, Image *target) {
        if (border_type != 101) {
            return;
        }
        if (W % 2 == 0 || H % 2 == 0)
            cerr << "patch must be 2*n+1" << endl;
        int rows = ptr_image->GetRows(), cols = ptr_image->GetCols();
        if (target == NULL) {
            target = new Image(rows, cols);
        }else if(target->GetCols() != cols || target->GetRows() != rows){
            delete target;
            target = new Image(rows, cols);
        }
        int border_w = W / 2, border_h = H / 2;

        //对Image做卷积操作
        unsigned char *working_image = ptr_image->GetImage();//这是浅拷贝
        unsigned char *target_val = new unsigned char[cols*rows];
        float val;
        for (int i = 0; i < rows * cols; i++) {
            //cur position is i
            target_val[i] = 0;
            int row = i / cols;
            int col = i - row * cols;
            if (row - border_h < 0 || row + border_h >= rows ||
                col - border_w < 0 || col + border_w >= cols) {
                //出了边界后，怎么找到相应的坐标位置
                for(int delta_y = -border_h; delta_y<border_h+1; delta_y++){
                    for(int delta_x = -border_w; delta_x<border_w+1; delta_x++){
                        //这里不继续用delta_y ,采用新的out_x, out_y
                        int new_row, new_col;
                        new_row = row + delta_y;
                        new_col = col + delta_x;
                        int out_x, out_y;
                        if(new_row<0){
                            out_y = -new_row;
                        }else if((out_y = new_row - rows +1) > 0){
                            out_y = -out_y;
                        }else{
                            out_y = delta_y;
                        }

                        if(new_col<0){
                            out_x = -new_col;
                        }else if((out_x = new_col- cols +1) > 0){
                            out_x = -out_x;
                        }else{
                            out_x = delta_x;
                        }
                        val = (float)working_image[(out_y+row)*cols+col+out_x];
                        //cout<<(int)working_image[(out_y+row)*cols+col+out_x]<<" ";
                        target_val[i] += (unsigned char)(val * patch[(delta_y+border_h)*W+delta_x+border_w]);
                    }

                }
                //cout<<endl;

            } else {
                //在边界之内，那么通过卷积来求解, 因为每个点都在image内，那么可以方便的得到该点周围点的位置
                for (int delta_y = -border_h; delta_y < border_h + 1; delta_y++) {
                    for (int delta_x = -border_w; delta_x < border_w + 1; delta_x++) {
                        val = (float)working_image[(delta_y + row) * cols + col + delta_x];
                        //cout << (int)working_image[(delta_y + row) * cols + col + delta_x]<<" ";
                        target_val[i] += (unsigned char)(val * patch[(delta_y+border_h)*W+delta_x+border_w]);
                    }
                }
                //cout<<endl;
            }
        }
        target->SetImage(target_val);
    }
}