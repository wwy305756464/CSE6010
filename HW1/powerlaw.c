#include <stdio.h>
#include <math.h>

#define arraySize 19
// z = c * u^a, -> log(z) = log(c) + a * log(u)
// knows: z = max speed, u = body mass
// to find: value of a, c
// define arthropod's body mass and max speed
double mass[arraySize] = {4.22e-4, 4.50e-4, 3.90e-4, 0.0138, 5.22e-6, 6.86e-6, 1.30e-6, 1.76e-7, 7.47e-7, 7.89e-8, 2.05e-7, 9.00e-5,
    1.70e-4, 0.0015, 4.73e-5, 0.002, 0.002, 6.52e-5, 1.01e-4};
double maxSpeed[arraySize] = {36, 27, 25.92, 36, 6.48, 4.8, 3.6, 3.24, 6.84, 3.06, 4.32, 36, 36, 25.56, 6, 19.08, 18, 10.8, 23.76};

// double mass[arraySize] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
// double maxSpeed[arraySize] = {6, 24, 54, 96, 150, 216, 294, 384, 486, 600};

void verifyResult(double originMass[arraySize], double originSpeed[arraySize], double a, double c); 

int main() {
    // get the log array of body mass and max speed
    double massLog[arraySize];
    double maxSpeedLog[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        massLog[i] = log(mass[i]); // log(u)
        maxSpeedLog[i] = log(maxSpeed[i]);  // log(z)
        // printf("log test is %f" , massLog[i] );
    }

    //  yj = k0 + k1 * xj,
    //  yj -> maxSpeedLog[i], k0 -> log(c), k1 -> a, xj -> massLog[i]

    // calculate coeffcients for M and b
    double m11 = arraySize;
    double m12 = 0;
    double m21 = 0;
    double m22 = 0;
    double b1 = 0;
    double b2 = 0;

    for (int i = 0; i < arraySize; ++i) {
        m12 += massLog[i];
        m22 += massLog[i] * massLog[i];
        b1 += maxSpeedLog[i];
        b2 += massLog[i] * maxSpeedLog[i];
    }
    m21 = m12;

    // get inverse M
    double inverseM_11, inverseM_12, inverseM_21, inverseM_22;
    inverseM_11 = 1 / (m11*m22 - m12*m21) * m22;
    inverseM_12 = 1 / (m11*m22 - m12*m21) * (-m12);
    inverseM_21 = 1 / (m11*m22 - m12*m21) * (-m21);
    inverseM_22 = 1 / (m11*m22 - m12*m21) * m11;

    // get a c
    double k0 = inverseM_11* b1 + inverseM_12 * b2;
    double a = inverseM_21 * b1 + inverseM_22 * b2;
    double c = exp(k0);

    printf("c is %f, a is %f \n \n", c, a);

    verifyResult(mass, maxSpeed, a, c);

    return 0;
}

// write a sub-function to show difference between calculated speed and original speed
void verifyResult(double originMass[arraySize], double originSpeed[arraySize], double a, double c) {
    double calculatedSpeed[arraySize];
    double diff[arraySize];

    for (int i = 0; i < arraySize; ++i) {
        calculatedSpeed[i] = c * pow(originMass[i], a);
        diff[i] = calculatedSpeed[i] - maxSpeed[i];
        printf("difference of %d's velocity is: %f \n", i+1, diff[i]);
    }
}


