#ifndef BINO_LINE_CONSTRUCT
#define BINO_LINE_CONSTRUCT
#include"header.h"

namespace BA_PnL{

class bino_line_construct{
public:
    //Initialize with the camera projection matrix
    bino_line_construct(Mat& left, Mat& right):P1(Matx34d(left)), P2(Matx34d(right)){}

    //reconstruct
    void reconstruct(vector<Point2d> & ilEPs, vector<Point2d> & irEPs);

    Vec6d reconstruct(iEndpoints & ilEP, iEndpoints & irEP);

    void set_Camera_left(Mat left)
    {
        P1 = left;
    }

    void set_Camera_right(Mat right)
    {
        P2 = right;
    }

    Point3d to2D_nonHomo(Vec2d point){
        return Point3d(point[0], point[1], 1);
    }

    void print_Pluckers()
    {
        for(size_t i = 0; i < Pluckerlines.size(); i++)
            cout<<Pluckerlines[i] / Pluckerlines[i][5]<<endl;
    }

    vector<Vec6d> get_Pluckerlines()
    {
        return Pluckerlines;
    }

private:
    //Camera matrix left and right
    Matx34d P1 ,P2;

    //Reconstruct lines
    Vec3d u,v;

    //Reconstructed Plucker lines
    vector<Vec6d> Pluckerlines;



};

}
#endif // BINO_LINE_CONSTRUCT

