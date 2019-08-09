//
// Created by Rick Simon on 2018-12-29.
//

#include "../Include/Canvas.h"
#include <memory>
#include <iostream>
#include <fstream>

Render::Canvas::Canvas(size_t w, size_t h) : width(w), height(h) {
  this->data = std::make_unique<Render::Color[]>(w * h);
}

void Render::Canvas::print(std::ostream &stream) {
  for (auto i = 0; i < this->height; ++i) {
    for (auto j = 0; j < this->width; ++j) {
      stream << data[i * this->width + j];
    }
    stream << std::endl;
  }
}

Render::Color &Render::Canvas::at(size_t x, size_t y) {
  return data[y * width + x];
}

Primitives::Tuple Render::Canvas::shape() {
  return Primitives::Tuple(width, height, 0.0f, 0.0f);
}

void Render::Canvas::write(std::string path) {
  std::ofstream file;
  try {
    file.open(path, std::ios::out | std::ios::trunc);
    file << "P3" << std::endl;
    file << this->width << ' ' << this->height << std::endl;
    file << 255 << std::endl;
    this->print(file);
  } catch (...) {
    file.close();
  }
  file.close();
}
