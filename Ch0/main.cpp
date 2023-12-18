#include <iostream>
#include <fstream>

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

	// PPM image coordinates. (LT, RT, LB, RB)
	// (ny - 1, 0) ~ (ny - 1, nx - 1)
	// (0, 0) ~ (0, 0)
	for (int j = ny - 1; j >= 0; --j) {
		for (int i = 0; i < nx; ++i) {
			float r = float(i) / float(nx);
			float g = float(j) / float(ny);
			float b = 0.2f;

			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);

			writeFile << ir << " " << ig << " " << ib << "\n";
		}
	}

	writeFile.close();

	return 0;
}