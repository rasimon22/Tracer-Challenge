//
// Created by Rick Simon on 2018-12-28.
//

#ifndef TRACER_CHALLENGE_COLOR_H
#define TRACER_CHALLENGE_COLOR_H

#include "../../Primitives/Include/Tuple.h"

namespace Render {
    class Color : public Primitives::Tuple {

    public:
        Color();

        Color(float, float, float);

        explicit Color(const Primitives::Tuple &);

        float &red;
        float &green;
        float &blue;

        bool operator==(const Color &) const;

        Color operator*(const Color &) const;

        Color &operator=(const Color &);


    };

    std::ostream &operator<<(std::ostream &, const Color &);
}


#endif //TRACER_CHALLENGE_COLOR_H
