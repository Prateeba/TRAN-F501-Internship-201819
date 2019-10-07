/*
Copyright (c) 2013 Daniel Stahlke

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <fstream>
#include <vector>
#include <map>
#include <limits>
#include <cmath>
#include <cstdio>
#include <boost/tuple/tuple.hpp>
#include <boost/foreach.hpp>

// Warn about use of deprecated functions.
#define GNUPLOT_DEPRECATE_WARN
#include "gnuplot-iostream.h"
#include "plotter.h"

#ifndef M_PI
#	define M_PI 3.14159265358979323846
#endif

// http://stackoverflow.com/a/1658429
#ifdef _WIN32
	#include <windows.h>
	inline void mysleep(unsigned millis) {
		::Sleep(millis);
	}
#else
	#include <unistd.h>
	inline void mysleep(unsigned millis) {
		::usleep(millis * 1000);
	}
#endif

void pause_if_needed() {
#ifdef _WIN32
	// For Windows, prompt for a keystroke before the Gnuplot object goes out of scope so that
	// the gnuplot window doesn't get closed.
	std::cout << "Press enter to exit." << std::endl;
	std::cin.get();
#endif
}

// Tell MSVC to not warn about using fopen.
// http://stackoverflow.com/a/4805353/1048959
#if defined(_MSC_VER) && _MSC_VER >= 1400
#pragma warning(disable:4996)
#endif


void demo_png(std::vector<std::vector<double>> dataset) {
	Gnuplot gp;

	gp << "set terminal png\n";

	/*std::vector<std::pair<double, double> > xy_pts_A;
	for(double x=-2; x<2; x+=0.01) {
		double y = x*x*x;
		xy_pts_A.push_back(std::make_pair(x, y));
	}

	std::vector<std::pair<double, double> > xy_pts_B;
	for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
		double theta = alpha*2.0*3.14159;
		xy_pts_B.push_back(std::make_pair(cos(theta), sin(theta)));
	} */

	std::cout << "Creating my_graph_2.png" << std::endl;
	gp << "set output 'my_graph_2.png'\n";
	gp << "set xrange [-20:20]\nset yrange [-20:20]\n";
	
	for (int i = 0; i < dataset.size(); i++) {
		std::vector<std::pair<double, double> > xy_pts_curves;
		for (int j = 1; j < dataset[i].size()-1; j++) {
			xy_pts_curves.push_back(std::make_pair(dataset[i][0], dataset[i][j])) ; 

		}
		gp << "plot '-' with linespoints\n";
		gp.send1d(xy_pts_curves) ; 
		gp.flush();

	}
}


void demo_animation() {
#ifdef _WIN32
	// No animation demo for Windows.  The problem is that every time the plot
	// is updated, the gnuplot window grabs focus.  So you can't ever focus the
	// terminal window to press Ctrl-C.  The only way to quit is to right-click
	// the terminal window on the task bar and close it from there.  Other than
	// that, it seems to work.
	std::cout << "Sorry, the animation demo doesn't work in Windows." << std::endl;
	return;
#endif

	Gnuplot gp;

	std::cout << "Press Ctrl-C to quit (closing gnuplot window doesn't quit)." << std::endl;

	gp << "set yrange [-1:1]\n";

	const int N = 1000;
	std::vector<double> pts(N);

	double theta = 0;
	while(1) {
		for(int i=0; i<N; i++) {
			double alpha = (double(i)/N-0.5) * 10;
			pts[i] = sin(alpha*8.0 + theta) * exp(-alpha*alpha/2.0);
		}

		gp << "plot '-' binary" << gp.binFmt1d(pts, "array") << "with lines notitle\n";
		gp.sendBinary1d(pts);
		gp.flush();

		theta += 0.2;
		mysleep(100);
	}
}


void demo_segments(std::vector<std::vector<double>> dataset) {
	// Demo of disconnected segments.  Plot a circle with some pieces missing.

	Gnuplot gp;
	gp << "set xrange [-20:20]\nset yrange [-20:20]\n";

	std::vector<std::vector<std::pair<double, double> > > all_segments;
	for(int i=0; i<dataset.size(); i++) {
		std::vector<std::pair<double, double> > segment;
		for(int j=1; j<dataset[i].size()-1; j++) {
			segment.push_back(std::make_pair(dataset[i][0], dataset[i][j]));
		}
		all_segments.push_back(segment);
	}

	gp << "plot '-' with linespoints\n";
	// NOTE: send2d is used here, rather than send1d.  This puts a blank line between segments.
	gp.send2d(all_segments);

	pause_if_needed();
}


int main(int argc, char **argv) {
	std::vector<std::vector<double>> dataset{{1.0, 5.0, 14.0, 19.0},{5, 2.0, 12.0, 19.5}} ; 
	demo_segments(dataset) ; 
}
