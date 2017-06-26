#ifndef BA_PNL_HPP
#define BA_PNL_HPP
#include "header.h"

namespace BA_PnL{



class PnL_optimization
{
public:
    //Construct optimizer with camera intrinsics and
    PnL_optimization(const Mat& K_, int opt_ = 20):K(K),opt(opt_){}

    //Set by hand
    void set_cameraMatrix(Mat& Intrisic)
    {
        if(Intrisic.size() != Size(3,3))
            cerr<<"Error not valid camera Matrix"<<endl;
        K = Matx33d(Intrisic);
    }

    void set_Optimize_iterates(int iterates)
    {
        opt = iterates;
    }

    //Optimize from 6d pluckerlines and image points
    void optimize(const vector<Vec6d> &wPluckerlines, const vector<Point2d> &cEndpoints, Matx33d& R, Vec3d& t, Matx33d R_, Vec3d t_ );

    //Optimize from 3d endpoints and image points
    void optimize(const vector<Point3d> &wEndpoints3D,  const vector<Point2d> &cEndpoints, Matx33d& R, Vec3d& t, Matx33d R_, Vec3d t_);

private:
    //Optimize times
    int opt;

    //Endpoints in world coordinates and Camera coordinates.
    vector<Point3d> wEPts, cEPts;

    //Endpoints in the image
    vector<Point2d> iEPts;

    //Lines in Plucker coordinates in world frame.
    vector<Vec6d> wLines, cLines;

    //Camera intrinsics
    Matx33d K;

    //Optimized result
    Matx33d R;
    Vec3d t;

    //Get skew3 cross product matrix.
    Matx33d skew3(Vec3d ksi)
    {
        return Matx33d(  0  ,-ksi[2],  ksi[1],
                      ksi[2],    0  , -ksi[0],
                     -ksi[1], ksi[0],    0    );
    }

    //Get camera Projection matrix of u
    Matx33d Pu_fromR_t(Matx33d &R, Vec3d &t)
    {
        return skew3(t)*R;
    }

    //Get camera Projection matrix of v
    Matx33d Pv_fromR_t(Matx33d &R)
    {
        return R;
    }

    //Convert 2D points to its homogeneous coordinates
    void to2DHomo(const vector<Point2d>& in, vector<Vec3d>& out)
    {
        for(size_t i = 0; i< in.size();i++)
            out.push_back(Vec3d(in[i].x,in[i].y,1));
    }

    //get Jacobian


};

}
#endif // BA_PNL_HPP

