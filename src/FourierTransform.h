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

    float aspect_x = 1;
    float aspect_y = 1;

    void aspect_ratio(float as_x,float as_y){
        if(as_x > as_y){
            aspect_y = as_y/as_x;
        }else if(as_y > as_x){
            aspect_x = as_x/as_y;
        }
        return;
    }

    class CarCoor{
    public:
        float x;
        float y;
    };

    CarCoor *figure;
    CarCoor getFigure(float t){
        int arrIndex = mapf(t,0,1,0,ARR_LENGTH);
        return figure[arrIndex];
    }
    const char *p;
private:

    float x_min;
    float x_max;
    float y_min;
    float y_max;

    float mapf(float val, float in_min, float in_max, float out_min, float out_max);
    void progress(int state,int i){

        Serial.print("\tINITIALIZE\t");
        Serial.print(p);
        Serial.print("\t:\t");
        Serial.print(i + (state * ARR_LENGTH));
        Serial.print("\t/\t");
        Serial.print(ARR_LENGTH * 2);
        Serial.print("\t:\t");
        Serial.print(100.0*(i + (state * ARR_LENGTH))/(ARR_LENGTH * 2));
        Serial.print("\t%");

        Serial.println();
    }
};
#endif