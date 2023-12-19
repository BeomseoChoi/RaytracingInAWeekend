#include <iostream>
#include <fstream>
#include "sphere.h"
#include "hitable_list.h"
#include <climits>

vec3 color(const ray& r, hitable* world) {
	hit_record rec;
	if (world->hit(r, 0.0, FLT_MAX, rec)) {
		return 0.5f * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}

	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5f * (unit_direction.y() + 1.0f);

	return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
}

int main() {
	std::string filePath = "result.ppm";
	std::ofstream writeFile(filePath.data());
	if (!writeFile.is_open()) {
		std::printf("Failed to open ofstream.\n");
		return 1;
	}

	int nx = 200;
	int ny = 100;
	writeFile << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0.0f, 0.0f);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);

	hitable* list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5f);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable* world = new hitable_list(list, 2);

	// PPM image coordinates. (LT, RT, LB, RB)
	// (ny - 1, 0) ~ (ny - 1, nx - 1)
	// (0, 0) ~ (0, 0)
	for (int j = ny - 1; j >= 0; --j) {
		for (int i = 0; i < nx; ++i) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);

			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 col = color(r, world);

			int ir = int(255.99 * col.r());
			int ig = int(255.99 * col.g());
			int ib = int(255.99 * col.b());

			writeFile << ir << " " << ig << " " << ib << "\n";
		}
	}

	writeFile.close();

	return 0;
}