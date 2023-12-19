#include <iostream>
#include <fstream>
#include "../Utils/ray.h"
#include "../Utils/vec3.h"

bool hit_sphere(const vec3& center, float radius, const ray& r) {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0f * dot(r.direction(), r.origin() - center);
	float c = dot(oc, oc) - radius * radius;

	float discriminant = b * b - 4 * a * c;

	return (discriminant > 0);
}

vec3 color(const ray& r) {
	if (hit_sphere(vec3(0, 0, -1), 0.5f, r)) {
		return vec3(1, 0, 0);
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

	// PPM image coordinates. (LT, RT, LB, RB)
	// (ny - 1, 0) ~ (ny - 1, nx - 1)
	// (0, 0) ~ (0, 0)
	for (int j = ny - 1; j >= 0; --j) {
		for (int i = 0; i < nx; ++i) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);

			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 col = color(r);

			int ir = int(255.99 * col.r());
			int ig = int(255.99 * col.g());
			int ib = int(255.99 * col.b());

			writeFile << ir << " " << ig << " " << ib << "\n";
		}
	}

	writeFile.close();

	return 0;
}