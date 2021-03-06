// RayTracePractice.cpp: 定义控制台应用程序的入口点。
//
#include "ppm2png.h"
#include "camera.h"
#include "sphere.h"
#include "hitable_list.h"
#include <float.h>
#include "lambertian.h"
#include "metal.h"

vec3 color(const ray& r,hitable* world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec))
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return vec3(0, 0, 0);
		}
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
	}
}

int main()
{
	int nx = 200;
	int ny = 100;
	int ns = 100;
	ppm2png png;
	std::vector<RGB> image;
	
	hitable* list[4];
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8,0.3,0.3)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8,0.8,0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8,0.6,0.2), 1));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.8, 0.8, 0.8), 0.3));


	hitable *world = new hitable_list(list, 4);
	camera cam;

	for(int j=ny-1;j>=0;j--)
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0, 0, 0);
			RGB rgb;
			for (int s = 0; s < ns; s++)
			{
				float u = float(i+ rg.dice()) / float(nx);
				float v = float(j+ rg.dice()) / float(ny);
				ray r = cam.get_ray(u, v);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			rgb.r = int(255.99*col[0]);
			rgb.g = int(255.99*col[1]);
			rgb.b = int(255.99*col[2]);
			image.push_back(rgb);
		}

	png.get_image(image, nx, ny);
    return 0;
}

