//
// Created by Rick Simon on 2018-12-17.
//

#ifndef TRACER_CHALLENGE_TUPLE_H
#define TRACER_CHALLENGE_TUPLE_H
#include <iostream>

namespace Primitives {
    class Tuple {
    public:
        float x, y, z, w;

        Tuple(float, float, float, float);

        enum Type {
            Point,
            Vector
        };
        Type type();

        bool operator==(const Primitives::Tuple&) const;

        Tuple operator+(const Primitives::Tuple&) const;

        Tuple operator-(const Primitives::Tuple&) const;

        Tuple operator-() const;

        //TODO: look into templating these
        Tuple operator*(const float&);

        void operator*=(const float&);

        Tuple operator/(const float&);

        void operator/=(const float&);

    private:
        Type _type;

    };

    Tuple point(float, float, float);
    Tuple point(const Tuple&);
    Tuple vector(float, float, float);
    Tuple vector(const Tuple&);
    bool float_equal(float, float);
    std::ostream& operator << (std::ostream &os, const Primitives::Tuple&);
}
#endif //TRACER_CHALLENGE_TUPLE_H
