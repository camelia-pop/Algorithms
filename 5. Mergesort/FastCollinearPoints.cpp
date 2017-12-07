#include "FastCollinearPoints.h"
#include "LineSegment.h"
#include "Point.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using std::bind;
using std::cout;
using std::endl;
using std::pair;
using std::sort;
using std::stable_sort;
using std::unordered_multimap;
using std::vector;
using namespace std::placeholders;

FastCollinearPoints::FastCollinearPoints(const vector<Point> &v): numSeg(0) {
    // copy vp[] to a new vector because we will change it by sorting
	// we sort vp[] so that we don't add multiple times the same segment
	vector<Point> vp = v;
	sort(vp.begin(), vp.end(), comparePoint);	
	
	size_t n = vp.size();	
	// use unordered_multimap because access of a (key, value) pair is done in constant time
	unordered_multimap<double, pair<Point, Point>> mp;
	
	for (size_t i = 0; i != n; ++i) {
		vector<Point> vpc = vp;
		stable_sort(vpc.begin(), vpc.end(), bind(compareSlope, vp[i], _1, _2));
		size_t j = 1, k;
		while (j < n){
			double m = vp[i].slopeTo(vpc[j]);
			k = j + 1;
			while ((k < n) && (m == vp[i].slopeTo(vpc[k]))) 
				++k;
			if (k - j >= 3) {
				if (mp.find(m) != mp.end()) {
					//pair <unordered_multimap<double, pair<Point, Point>>::iterator, 
					//unordered_multimap<double, pair<Point, Point>>::iterator, ::iterator> ret;
					auto ret = mp.equal_range(m);
					bool cod = true;
					for (auto it = ret.first; it != ret.second; ++it) {	
						// pair<Point, Point> pr = it->second;
						auto pr = it->second;
						if ((pr.first == vp[i]) || (m == (pr.first).slopeTo(vp[i]))) {
							cod = false;
							break;
						}
					}
					if (cod) 
						mp.insert({m, {vp[i], vpc[k - 1]}});										
				} else 
					mp.insert({m, {vp[i], vpc[k - 1]}});						
			}			
			j = k;
		}
	}
	for (auto it = mp.begin(); it != mp.end(); ++it) 
		vecSeg.push_back(LineSegment((it->second).first, (it->second).second));
	numSeg = vecSeg.size();
}
