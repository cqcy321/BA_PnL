#include "header.h"

namespace BA_PnL
{
//Reshape Endpoints to pairs
void reshape_Epts(vector<Point2d> in, vector<iEndpoints>& out){
    if(in.size()%2 != 0 || in.size() == 0)
        return;
    for(size_t i = 0; i < in.size(); i+=2)
    {
        iEndpoints iEP;
        iEP.start = in[i];
        iEP.end = in[i+1];
        out.push_back(iEP);
    }
}

Vec2d proj(Vec3d pt){
    return Vec2d(pt[0] / pt[2], pt[1] / pt[2]);
}

void calc_iLine_Expn(const vector<Point2d>& in , vector<Vec3d>& expn )
{
    vector<iEndpoints> iEpts;
    reshape_Epts(in,iEpts);
    for (auto& it : iEpts) {
        Vec3d exp;
        calc_iLine_Expn(it,exp);
        expn.push_back(exp);
    }
}

void calc_iLine_Expn_non_homo(const vector<Point2d>& in , vector<Vec2d>& expn )
{
    vector<iEndpoints> iEpts;
    reshape_Epts(in,iEpts);
    for (auto& it : iEpts) {
        Vec3d exp;
        calc_iLine_Expn(it,exp);
        expn.push_back(Vec2d(exp[0]/exp[1],exp[1]/exp[2]));
    }
}

//2D line expression
void calc_iLine_Expn(iEndpoints& i, Vec3d& expn )
{
    Point i1 = i.start;
    Point i2 = i.end;
    if(i1.x==i2.x)
        expn=Vec3d(1,0,i1.y);
    else
    {
        float k=(float)(i2.y-i1.y)/(i2.x-i1.x);
        expn=Vec3d(k,-1,i1.y-k*i1.x);
    }
}


void covert2Plucker(const vector<Point3d>& in , vector<Vec6d> & pluckerlines)
{
    for(int i=0;i<in.size();i+=2)
    {
        Vec3d u,v;
        u = in[i].cross(in[i+1]);
        v = in[i+1] - in[i];
        pluckerlines.push_back(Vec6d(u[0],u[1],u[2],v[0],v[1],v[2]));
    }
}
}
