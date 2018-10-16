//
// Created by lut on 18-10-16.
//

#ifndef IMAGECOV_IMAGE_H
#define IMAGECOV_IMAGE_H

namespace lutTools {
    class Image {
        //实现单通道图像
    private:
        unsigned char *img = NULL;
        int rows;//行, H
        int cols;//列, W

    public:
        //目前都是深度拷贝
        Image(){
            img = NULL;
            rows = 0;
            cols = 0;
        }

        Image(Image* ptr_image){
            rows = ptr_image->GetRows();
            cols = ptr_image->GetCols();
            if(img != NULL)
                delete img;
            img = new unsigned char[rows*cols];
            for(int i=0; i<rows*cols; i++)
                img[i] = ptr_image->GetImage()[i];
        }

        Image(int rows, int cols){
            if(img != NULL){
                delete img;
            }
            this->rows = rows;
            this->cols = cols;
            img = new unsigned char[rows*cols];
        }

        ~Image(){
            delete img;
            img = NULL;
        }
        //0~rows-1 0-cols-1
        unsigned char GetPixel(int row, int col) const{
            return img[row * cols + col];
        }

        unsigned char GetPixel(int index) const{
            return img[index];
        }

        static inline float ucharToFloat(unsigned char val) {
            //把uchar 转换成 float类型对应的数
            float f_val = (float) val;//一定是正整数
            return f_val;
        }

        unsigned char* GetImage() const{
            return img;
        }

        void SetImage(unsigned char* val, int len){
            //img = val;//这里就浅拷贝了，不好
            for(int i=0; i<len; i++)
                img[i] = val[i];
        }
        void SetImage(unsigned char* val){
            for(int i=0; i<rows*cols; i++)
                img[i] = val[i];
        }

        int GetRows() const{
            return rows;
        }

        int GetCols() const{
            return cols;
        }
    };
    template <typename T>
    static inline unsigned char T2unchar(T val){
        unsigned char uchar_val = (unsigned char)val;
        return uchar_val;
    }
}


#endif //IMAGECOV_IMAGE_H
