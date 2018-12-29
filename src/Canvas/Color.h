//
// Created by Rick Simon on 2018-12-28.
//

#ifndef TRACER_CHALLENGE_COLOR_H
#define TRACER_CHALLENGE_COLOR_H

#include "../Primitives/Tuple.h"

namespace Canvas {
    class Color : public Primitives::Tuple {

    public:
        Color();

        Color(float, float, float);

        explicit Color(const Primitives::Tuple&);

        float &red;
        float &green;
        float &blue;

        bool operator ==(const Color&) const;
        Color operator *(const Color&) const;

    };
}


#endif //TRACER_CHALLENGE_COLOR_H
