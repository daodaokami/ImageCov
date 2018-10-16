#include <iostream>
#include "include/image.h"
#include "tools.h"
using namespace std;

void show(const lutTools::Image* target);
int main() {
    //强制转换过程中会进行向下取整
    lutTools::Image image(3, 4);
    unsigned char* val = new unsigned char[9];
    for(int i=0; i<12; i++){
        val[i] = i+1;
    }
    image.SetImage(val);

    int W = 3, H = 3;
    double* patch = new double[9];

    for(int i=0; i<9; i++)
        patch[i] = 1;
    lutTools::Image target(3, 4);
    lutTools::Tools tools;
    tools.Cov(&image, patch, W, H, 101, &target);

    show(&target);
    return 0;
}

void show(const lutTools::Image* target){
    int rows = target->GetRows();
    int cols = target->GetCols();

    for(int i=0; i<rows*cols; i++) {
        if(i != 0 && i % cols == 0)
            cout<<"\n";
        cout << (int) target->GetPixel(i)<<" ";
    }
}