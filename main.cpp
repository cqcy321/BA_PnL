#include "header.h"
#include "ba_pnl.hpp"
#include "bino_line_construct.h"
using namespace BA_PnL;

string intrin = "param/intrinsics.yml";
string extrin = "param/extrinsics.yml";


int main(int argc, char *argv[])
{
    Vec4d a1(1,2,4,1);
    Vec4d b1(4,5,6,1);

    Vec4d a2(2,2,4,1);
    Vec4d b2(3,5,6,1);

    Vec4d a3(1,2,3,1);
    Vec4d b3(4,5,8,1);

    Bino_Cam cam(intrin,extrin);

    vector<Point2d> linel,liner;

    Matx34d P1(cam.P1);
    linel.push_back(proj(P1*a1));
    linel.push_back(proj(P1*b1));


    linel.push_back(proj(P1*a2));
    linel.push_back(proj(P1*b2));


    linel.push_back(proj(P1*a3));
    linel.push_back(proj(P1*b3));

    PnL_optimization optimizer(cam.P1.rowRange(0,3).colRange(0,3));
//    optimizer.optimize();
    return 0;
}


////TEST BINOCULAR-----------------------------------------------------------------------------

//Vec3d a(1,2,4);
//Vec3d b(4,5,6);

//Vec4d a4(1,2,4,1);
//Vec4d b4(4,5,6,1);

//Mat a5(a4);
//Mat b5(b4);
//vector<Point2d> linel,liner;
//Vec3d c = a.cross(b);
//Vec6d d(c[0],c[1],c[2],3,3,2);
//cout<<d<<endl;

//Bino_Cam cam(intrin,extrin);
//bino_line_construct BL((cam.P1),(cam.P2));
//Matx34d P1(cam.P1);
//Matx34d P2(cam.P2);
////    linel.push_back(p1);


////    cout<<proj(P1*a4)<<endl;
////    cout<<proj(P1*b4)<<endl;
//linel.push_back(proj(P1*a4));
//linel.push_back(proj(P1*b4));
//liner.push_back(proj(P2*a4));
//liner.push_back(proj(P2*b4));

//for (auto& it : linel) {
//    cout<<it<<endl;
//     }
//BL.reconstruct(linel,liner);
//BL.print_Pluckers();
////    bino_line_construct((cam.P1),(cam.P2));
