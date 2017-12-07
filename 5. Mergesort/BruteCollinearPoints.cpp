#include "BruteCollinearPoints.h"
#include "LineSegment.h"
#include "Point.h"
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

using std::pair;
using std::sort;
using std::unordered_multimap;
using std::vector;

BruteCollinearPoints::BruteCollinearPoints(const vector<Point> &v): numSeg(0) {
    // order vp[] using P.compareTo(Q)
	vector<Point> vp = v;
	sort(vp.begin(), vp.end(), comparePoint);	
		
	size_t n = vp.size();	
	// use unordered_multimap because access of a (key, value) pair is done in constant time
	unordered_multimap<double, pair<Point, Point>> mp;
	
	for (size_t i = 0; i != n - 3; ++i)
		for (size_t j = i + 1; j != n - 2; ++j) { 
				double m1 = vp[i].slopeTo(vp[j]);
				for (size_t k = j + 1; k != n - 1; ++k) {
					double m2 = vp[i].slopeTo(vp[k]);
					if (m1 == m2) {
						size_t l = n - 1;
						// to find a 4th colinear point we use the fact that vp[] is sorted using comparePoint()
						while ((l >= k + 1) && (vp[i].slopeTo(vp[l]) != m1))
							--l;
						if (l >= k + 1) {
							if (mp.find(m1) != mp.end()) {
								//pair <unordered_multimap<double, pair<Point, Point>>::iterator, 
								//unordered_multimap<double, pair<Point, Point>>::iterator, ::iterator> ret;
								auto ret = mp.equal_range(m1);
								bool cod = true;
								for (auto it = ret.first; it != ret.second; ++it) {	
									// pair<Point, Point> pr = it->second;
									auto pr = it->second;
									if ((pr.first == vp[i]) || (m1 == (pr.first).slopeTo(vp[i]))) {
										cod = false;
										break;
									}
								}
								if (cod) 
									mp.insert({m1, {vp[i], vp[l]}});
							} else 
								mp.insert({m1, {vp[i], vp[l]}});	
						}
					}						
				}
			}
	for (auto it = mp.begin(); it != mp.end(); ++it) 
		vecSeg.push_back(LineSegment((it->second).first, (it->second).second));
	numSeg = vecSeg.size();
}
