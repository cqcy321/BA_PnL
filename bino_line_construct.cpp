#include "header.h"
#include"bino_line_construct.h"

using namespace BA_PnL;

//Input Vectors are as such:
//Endpoint 0 of line 1
//Endpoint 1 of line 1
//Endpoint 0 of line 2
//Endpoint 1 of line 2
//          .
//          .
//          .
void bino_line_construct::reconstruct(vector<Point2d> & ilEPs, vector<Point2d> & irEPs)
{
    vector<iEndpoints> iEl, iEr;
    reshape_Epts(ilEPs, iEl);
    reshape_Epts(irEPs, iEr);
    for(size_t i = 0; i < iEl.size(); i++)
    {
        Pluckerlines.push_back(reconstruct(iEl[i], iEr[i]));
    }
}

Vec6d bino_line_construct::reconstruct(iEndpoints & ilEP, iEndpoints & irEP)
{
    Vec3d ilinel, iliner;
    calc_iLine_Expn(ilEP, ilinel);
    calc_iLine_Expn(irEP, iliner);
    Vec4d nl = P1.t() * ilinel;
    Vec4d nr = P2.t() * iliner;

    //Normal of the back projection plane
    Vec3d v = Vec3d(nl[0],nl[1],nl[2]).cross(Vec3d(nr[0],nr[1],nr[2]));
    v = v / sqrt(v.dot(v));

    //Calculation a point A in the 3D line
    //solve the equation to find a point on the exact line
    Vec2d b(-1000*nl(2) - nl(3),-1000*nr(2)-nr(3));
    Matx22d A(nl(0),nl(1),nr(0),nr(1));
    Vec2d x;
    solve(A,b,x);
    Vec3d point_linel(x(0),x(1),1000);
    Vec3d u = point_linel.cross(v);

    //u--normal vector then v--direction vector
    return Vec6d(u[0],u[1],u[2],v[0],v[1],v[2]);
}
