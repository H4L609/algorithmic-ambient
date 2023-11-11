#include "DroneNoise.h"

DroneNoise::DroneNoise() {
    DroneNoise(0.5);
}

DroneNoise::DroneNoise(float volume) {
    this->volume = volume;
}

void DroneNoise::setVolume(short oscIndex, float volume) {
    volume = clamp(volume, 0.0f, 1.0f);
    this->volume = volume;
}

float DroneNoise::play(std::vector<double> frequency) {
    return val * this->volume;
}
