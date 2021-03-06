#include <iostream>
#include "../Utilities/ray.h"
#include "../Utilities/sphere.h"
#include "../Utilities/hitable_list.h"
#include "float.h"
#include "../Utilities/camera.h"
#include "../Utilities/drand48.h"

using namespace std;

vec3 random_in_unit_sphere()
{
	vec3 p;
	do
	{
		p = vec3(drand48(), drand48(), drand48())*2.0 - vec3(1, 1, 1);
	} while (dot(p, p) >= 1.0);
	return p;
}

vec3 color(const ray& r, hitable *world)
{
	hit_record rec;

	if (world->hit(r, 0.0, FLT_MAX, rec))
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return color(ray(rec.p, target - rec.p), world)*0.5;
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = (unit_direction.y() + 1.0)*0.5;
		return vec3(1.0, 1.0, 1.0)*(1.0 - t) + vec3(0.5, 0.7, 1.0)*t;
	}

}

int main()
{
	int nx = 200;
	int ny = 100;
	int ns = 100;
	cout << "P3\n" << nx << " " << ny << "\n255\n";

	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);

	camera cam;

	for (int j = ny - 1; j >= 0; j--)
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0, 0, 0);

			for (int s = 0; s < ns; s++)
			{
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world);
			}

			col /= float(ns);			

			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);

			cout << ir << " " << ig << " " << ib << "\n";
		}
}