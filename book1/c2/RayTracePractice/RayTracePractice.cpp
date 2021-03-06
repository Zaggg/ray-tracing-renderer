// RayTracePractice.cpp: 定义控制台应用程序的入口点。
//
#include "ppm2png.h"
#include "vec3.h"

int main()
{
	int nx = 200;
	int ny = 100;
	ppm2png png;
	std::vector<RGB> image;

	for(int j=ny-1;j>=0;j--)
		for (int i = 0; i < nx; i++)
		{
			RGB rgb;
			vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
			rgb.r = int(255.99*col[0]);
			rgb.g = int(255.99*col[1]);
			rgb.b = int(255.99*col[2]);
			image.push_back(rgb);
		}

	png.get_image(image, nx, ny);
    return 0;
}

