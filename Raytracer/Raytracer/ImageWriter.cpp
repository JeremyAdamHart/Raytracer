#include "ImageWriter.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

void writePng(glm::vec3 *data, int width, int height, std::string filename) {
	unsigned char* imageBytes = new unsigned char[width*height*3];

	for (int i = 0; i < width*height; i++) {
		imageBytes[3 * i] = char(254.f*glm::clamp(data[i].x, 0.f, 1.f));
		imageBytes[3 * i + 1] = char(254.f*glm::clamp(data[i].y, 0.f, 1.f));
		imageBytes[3 * i + 2] = char(254.f*glm::clamp(data[i].z, 0.f, 1.f));
	}

	stbi_write_png(filename.c_str(), width, height, 3, imageBytes, 0);

	delete[] imageBytes;
}