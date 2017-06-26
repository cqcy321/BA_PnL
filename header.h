#ifndef HEADER_H
#define HEADER_H
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <map>
using namespace std;
using namespace cv;

namespace BA_PnL
{
//An Endpoints struct contains the 2 end points of one single line.
struct Point_pair
{
    Point2d start;
    Point2d end;
};

typedef Point_pair iEndpoints;

void reshape_Epts(vector<Point2d>  , vector<iEndpoints>& out);

void calc_iLine_Expn(const vector<Point2d>& in , vector<Vec3d>& expn );

void calc_iLine_Expn_non_homo(const vector<Point2d>& in , vector<Vec2d>& expn );

void calc_iLine_Expn(iEndpoints &i, Vec3d& expn );

void covert2Plucker(const vector<Point3d>& in , vector<Vec6d> & pluckerlines);

//Projection function from homogeneous coordinates to non-homo (Vec3-Vec2)
Vec2d proj(Vec3d pt);

class Bino_Cam
{
public:

    Bino_Cam(string intrin, string extrin)
    {
        FileStorage fs(intrin,FileStorage::READ);
        fs["M1"] >> M1;
        fs["D1"] >> D1;
        fs["M2"] >> M2;
        fs["D2"] >> D2;
        fs.open(extrin,FileStorage::READ);
        fs["R"] >> R;
        fs["t"] >> t;
        fs["R1"] >> R1;
        fs["R2"] >> R2;
        fs["P1"] >> P1;
        fs["P2"] >> P2;

    }



//private:

    //Intrinsic Matrix
    Mat M1, M2;

    //Distortion Matrix
    Mat D1, D2;

    //Extrinsic
    Mat R, t;

    //Binocular rectify
    Mat R1, R2;

    //Final Camera model
    Mat P1, P2;


};

}


#endif // HEADER_H

