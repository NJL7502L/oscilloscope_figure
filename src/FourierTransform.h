#ifndef FourierTransform_h
#define FourierTransform_h

#include <Arduino.h>

class FourierTransform {
public:
    int T_MIN = 0;
    int T_MAX = 200;
    int ARR_LENGTH = 10000;

    float T_RES = ((T_MAX - T_MIN)/(float)ARR_LENGTH);

    float (*return_x)(float);
    float (*return_y)(float);

    FourierTransform(float (*ret_x)(float), float (*ret_y)(float));
    
    // void init(int t_min, int t_max, int arr_length);
    void store_parameter(int t_min, int t_max, int arr_length);

    class CarCoor{
    public:
        float x;
        float y;

        int x_i;
        int y_i;
    };

    CarCoor *figure;

private:

    float x_min;
    float x_max;
    float y_min;
    float y_max;

    float mapf(float val, float in_min, float in_max, float out_min, float out_max);
};
#endif