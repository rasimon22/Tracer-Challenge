//
// Created by Rick Simon on 2018-12-29.
//

#ifndef TRACER_CHALLENGE_CANVAS_H
#define TRACER_CHALLENGE_CANVAS_H

#include <cstdlib>
#include <Color.h>
#include <memory>
#include <string>

namespace Render {

    class Canvas {
    public:
        Canvas(size_t, size_t);

        void print(std::ostream &);

        void write(std::string);

        Color &at(size_t, size_t);

        Primitives::Tuple shape();

    private:
        size_t width, height;
        std::unique_ptr<Color[]> data;

    };

}

#endif //TRACER_CHALLENGE_CANVAS_H
