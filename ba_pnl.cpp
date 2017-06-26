#include "header.h"
#include"ba_pnl.hpp"

namespace BA_PnL{

void PnL_optimization::optimize(const vector<Point3d> &wEndpoints3D,  const vector<Point2d> &cEndpoints, Matx33d& R, Vec3d& t, Matx33d R_, Vec3d t_)
{
    vector<Vec6d> pluckerlines;
    //Calculate plucker coordinates and then optimize
    covert2Plucker(wEndpoints3D,pluckerlines);
    Vec3d z(0,0,0);
    optimize(pluckerlines,cEndpoints, R, t, Matx33d::eye(), z);
}


void PnL_optimization::optimize(const vector<Vec6d> &wPluckerlines, const vector<Point2d> &cEndpoints, Matx33d& R, Vec3d& t, Matx33d R_, Vec3d t_ )
{
    int NLINES = wPluckerlines.size();
    vector<Vec3d> homo_2dlines;
    vector<Vec2d> non_homo_Lcn;
    calc_iLine_Expn(cEndpoints,homo_2dlines);

    Matx33d inv_K = K.t().inv();

    for(auto& it : homo_2dlines)
    {
        it = inv_K * it;
        non_homo_Lcn.push_back(proj(it));
    }

    //Divide plucker lines into u & v.
    vector<Vec3d> wu, wv;
    for(auto& it : wPluckerlines)
    {
        wu.push_back(Vec3d(it[0], it[1],it[2]));
        wv.push_back(Vec3d(it[3], it[4],it[5]));
    }

    //Generalize points, unprojected from the camera model
    Matx33d uPu_ = Pu_fromR_t(R_, t_);
    Matx33d uPv_ = Pv_fromR_t(R_);

    //Iteration for optimization
    for(int iterates = 0;iterates < opt; iterates ++)
    {
        //Residual error 2N * 1
        vector<double> res;
        vector<Vec3d> cu_, cv_;

        //Jacobian 2N * 6
        Mat J(CV_64F,2*NLINES, 6);

        for(int i = 0; i < wu.size();i++)
        {
            Vec3d estim_u = uPu_ * wu[i] + uPv_ * wv[i];
            Vec2d err =non_homo_Lcn[i] - proj(estim_u);
            res.push_back(err[0]);
            res.push_back(err[1]);
            cu_.push_back(estim_u);
            cv_.push_back(uPu_ * wv[i]);

            Matx33d ju_u, ju_v;
            Matx23d j_c(0, 1, -estim_u[0]/estim_u[2],
                        1, 0, -estim_u[1]/estim_u[2]);
            Mat ju;
            // Partial derivative of u of se3
            ju_u = -skew3(estim_u);
            ju_v = -skew3(uPu_ * wv[i]);

            //Camera model
            j_c = j_c * inv_K *(1/estim_u[2]) ;

            ju.rowRange(0,3).colRange(0,3) = Mat(ju_u);
            ju.rowRange(0,3).colRange(3,6) = Mat(ju_v);

            Mat j1 = Mat(j_c) * ju;
            J.rowRange(2*i,2*i+3) = j1;


        }

        //Jacobian Matrix

    }

}

Mat Update_se3(Matx33d &R, Vec3d t, Vec6d delta)
{
    Vec3d u(delta(0), delta(1), delta(2));
    Vec3d v(delta(3), delta(4), delta(5));
}

}
