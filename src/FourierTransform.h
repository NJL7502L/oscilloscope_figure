#ifndef FourierTransform_h
#define FourierTransform_h

#include <Arduino.h>

class FourierTransform {
public:
    int T_MIN = 0;
    int T_MAX = 200;
    int ARR_LENGTH = 10000;

    double T_RES = ((T_MAX - T_MIN)/(double)ARR_LENGTH);

    double (*return_x)(double);
    double (*return_y)(double);

    FourierTransform(double (*ret_x)(double), double (*ret_y)(double));
    
    // void init(int t_min, int t_max, int arr_length);
    void store_parameter(int t_min, int t_max, int arr_length);

    double aspect_x = 1;
    double aspect_y = 1;

    void aspect_ratio(double as_x,double as_y){
        if(as_x > as_y){
            aspect_y = as_y/as_x;
        }else if(as_y > as_x){
            aspect_x = as_x/as_y;
        }
        return;
    }

    class CarCoor{
    public:
        double x;
        double y;
    };

    CarCoor *figure;
    CarCoor getFigure(double t){
        int arrIndex = mapf(t,0,1,0,ARR_LENGTH);
        return figure[arrIndex];
    }
    const char *p;
private:

    double x_min;
    double x_max;
    double y_min;
    double y_max;

    double mapf(double val, double in_min, double in_max, double out_min, double out_max);
    void progress(int i){

        Serial.print(p);
        Serial.print("\t:\t");
        Serial.print(100.0*(i/(double)ARR_LENGTH));

        Serial.println();
    }
};
#endif