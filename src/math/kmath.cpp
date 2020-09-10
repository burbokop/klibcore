#include "kmath.h"
#include <QVector>
#include <QVector2D>
#include <math.h>

#define NOISE_LEVEL 0.2
#define GAIN1_MAX 0.8

KMath::KMath(QObject *parent) : QObject (parent) {}

float KMath::constrainAngle(float value) const {
    const float max = static_cast<float>(M_PI * 2);
    value = fmod(value, max);
    if (value < 0)
        value += max;
    return value;
}

float KMath::constrainDegrees(float value) const {
    const float max = 360.0;
    value = fmod(value, max);
    if (value < 0)
        value += max;
    return value;
}

double KMath::constrainDegrees(double value) const {
    const double max = 360.0;
    value = fmod(value, max);
    if (value < 0)
        value += max;
    return value;
}

float KMath::determinant(QVector2D vector1, QVector2D vector2) const {
    return vector1.x() * vector2.y() - vector1.y() * vector2.x();
}

float KMath::getAngle(QVector2D vector1, QVector2D vector2) const {
    const float dot = QVector2D::dotProduct(vector1, vector2);
    const float det = determinant(vector1, vector2);
    return -std::atan2(det, dot);
}

float KMath::getDegrees(QVector2D vector1, QVector2D vector2) const {
    const float dot = QVector2D::dotProduct(vector1, vector2);
    const float det = determinant(vector1, vector2);
    return -std::atan2(det, dot) * static_cast<float>(180 / M_PI);
}

bool KMath::direction(float dstAngle, float angle) const {
    if((dstAngle - angle) < 0) {
        if(std::abs(dstAngle - angle) < 180) {
            return 1; // //
        } else {
            return 0; //right//
        }
    } else {
        if(std::abs(dstAngle - angle) < 180) {
            return 0; //right//
        } else {
            return 1; //left//
        }
    }
}

bool KMath::direction(double dstAngle, double angle) const {
    if((dstAngle - angle) < 0) {
        if(std::abs(dstAngle - angle) < 180) {
            return 1; // //
        } else {
            return 0; //right//
        }
    } else {
        if(std::abs(dstAngle - angle) < 180) {
            return 0; //right//
        } else {
            return 1; //left//
        }
    }
}

float KMath::distance(float dstAngle, float angle) const {
    if((dstAngle - angle) < 0) {
        if(std::abs(dstAngle - angle) < 180) {
            return std::abs(dstAngle - angle);
        } else {
            return std::abs(dstAngle - angle);
        }
    } else {
        if(std::abs(dstAngle - angle) < 180) {
            return std::abs(dstAngle - angle);
        } else {
            return std::abs(dstAngle - angle);
        }
    }
}

float KMath::degreesDistance(float angle1, float angle2) const {
    float max = 360;
    float abs = qAbs(angle1 - angle2);
    return abs > (max * 0.5f) ? (max - abs) : abs;
}

float KMath::degreesDifference(float angle1, float angle2) const {
    float max = 360;
    float diff = angle1 - angle2;
    return qAbs(diff) > (max * 0.5f)
            ? ((diff >= 0)
               ? (diff - max)
               : (diff + max)
                 )
            : diff;}

double KMath::degreesDistance(double angle1, double angle2) const {
    double max = 360;
    double abs = qAbs(angle1 - angle2);
    return abs > (max * 0.5) ? (max - abs) : abs;
}

double KMath::degreesDifference(double angle1, double angle2) const {
    double max = 360;
    double diff = angle1 - angle2;
    return qAbs(diff) > (max * 0.5)
            ? ((diff >= 0)
               ? (diff - max)
               : (diff + max)
                 )
            : diff;
}


float KMath::map(float value, float inMin, float inMax, float outMin, float outMax) const {
    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

double KMath::dmap(double value, double inMin, double inMax, double outMin, double outMax) const {
    return (value - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

double KMath::limitValue(double value, double min, double max) const {
    return std::max(std::min(value, max), min);
}

double KMath::limitedMap(double value, double inMin, double inMax, double outMin, double outMax) const {
    return dmap(limitValue(value, inMin, inMax), inMin, inMax, outMin, outMax);
}

double KMath::sigm(double value) const {
    return 1 / (1 + std::exp(-value));
}

double KMath::gaus(double value) const {
    return exp(-value * value);
}

QVector<double> KMath::bubbleSort(const QVector<double> &array) const {
    QVector<double> result = array;
    bubbleSort(&result);
    return result;
}
QVector<quint64> KMath::vectorIndices(const QVector<double> &vector) const {
    return customContainerIndices(vector);
}


double KMath::random() const {
    return static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
}

double KMath::randomStep() const {
    static int i = std::rand() % 32;
    static double noise = random();

    if(i-- == 0) {
        i = std::rand() % 32;
        noise = random();
    }
    return noise;
}

double KMath::toKnots(double value) const {
    return value * 1.9438444924574;
}

double KMath::fromKnots(double value) const {
    return value * 0.5144444444444;
}

int KMath::toTop(double value) const {
    int i = static_cast<int>(value);
    if(!KCompareEngine<double>::compare(static_cast<double>(i), value)) {
        i++;
    }
    return i;
}

QVector<double> KMath::resampling(const QVector<double> &input, int sizeMultiplier) const {
    if(sizeMultiplier > 1) {
        QVector<double> result;
        for(int i = 0; i < input.size() - 1; i++) {
            result.push_back(input[i]);
            for(int j = 1; j < sizeMultiplier; j++) {
                result.push_back((input[i + 1] - input[i]) / sizeMultiplier * j + input[i]);
            }
        }

        for(int j = 1; j < sizeMultiplier; j++) {
            result.push_back((input[0] - input[input.size() - 1]) / sizeMultiplier * j + input[input.size() - 1]);
        }
        return result;
    }
    return input;
}

QVector<double> KMath::integrate(QVector<double> input, double alpha) const {
    for(int i = 1; i < input.size(); ++i) {
        input[i] = alpha * input[i - 1] + (1 - alpha) * input[i];
    }
    input[0] = alpha * input[input.size() - 1] + (1 - alpha) * input[0];
    return input;
}

QVector<double> KMath::smooth(const QVector<double> &input, double alpha, int sizeMultiplier) const {
    return integrate(resampling(input, sizeMultiplier), alpha);
}



