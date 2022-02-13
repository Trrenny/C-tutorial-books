#include "modules/common/math/path_matcher.h"

#include <algorithm>
#include <cmath>
#include <vector>

#include "glog/logging.h"
#include <functional>
#include "modules/common/math/linear_interpolation.h"

using namespace std::placeholder;


PathPoint PathMatcher::MatchPoint(const std::vector<PathPoint> &reference_line, double x, double y, double* dis )
{
	CHECK_GT(reference_line.size(), 0);//检查是否为0
	//设计lamda小函数：求参考线上每一点到起点（x,y）的距离
	auto calculate_dis_square = [] (const PathPoint &pathpoint, double x , double y)
	{
		double dx = pathpoint.x - x;
		double dy = path[oint.y - y;
		double dis_square = dx * dx + dy * dy;
		
		if (dis_square < *dis)
			*dis = dis_square; 
		
		return dx * dx + dy * dy;
	};
	
	//保存最小值
	double min_dis{};
	double* dis = &min_dis;
	//double min_dis = calculate_dis_square(reference_line.front(),x,y);
	//double* dis = &min_dis;
	
	std::size_t index_min = 0; 
	
	for_each(reference_line.begin(),reference_line.end(),bind(calculate_dis_square,_1,x,y,dis));
	
	std::size_t index_start = (index_min == 0 )? index_min:index_min-1;
	std::size_t index_end = (index_min+1 == reference_line.size())? index_min : index_min+1;
	
	if(index_start == index_end)
		return reference_line[index_start];
	else
		return FindProjectionPoint(reference_line[index_start],reference[index_end],x,y);
	
}

PathPoint PathMatcher::FindProjectionPoint(const PathPoint &p1,const PathPoint &p2,double x, double y)
{
	double b_x = p2.x() - p1.x();
	double b_y = p2.y() - p1.y();
	
	double a_x = x - p1.x();
	double a_y = y - p1.y();
	
	double dot = a_x * b_x + a_y * b_y;
	double dis_b = std::sqrt(b_x * b_x + b_y * b_y);
	
	double delta_s = dot / dis_b;
	
	return InterpolateUsingLinearApproximation(p1,p2,p1.s();delta_s)
}