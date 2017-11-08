#ifndef UTILS_H
#define UTILS_H

class CircleUtils {
public:
    static constexpr double min_scale = 0.001;
    static constexpr double max_scale = 100.0;
    static constexpr double min_speed = 0.0;
    static constexpr double max_speed = 1.0;
    static constexpr int max_nballs = 500;
    static constexpr int calcTime = 40;
    static constexpr int renderTime = 10;
    static constexpr double default_radius = 5.0;
    static constexpr double distEps = 0.9;
    CircleUtils() = delete;
    static double scale(double const scl) {
        return scl < min_scale ? min_scale : scl > max_scale ? max_scale : scl;
    }
    static double speed(double const spd) {
        return spd < min_speed ? min_speed : spd > max_speed ? max_speed : spd;
    }
};

#endif // UTILS_H
