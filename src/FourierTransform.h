#ifndef FourierTransform_h
#define FourierTransform_h

#include <Arduino.h>

class FourierTransform {
public:

    // typedef double (*FourierFunction)(double);
    using FourierFunction = double (*)(double);
    class CarCoorFunction{
    public:
        FourierFunction x;
        FourierFunction y;
    };

    CarCoorFunction *figureFunctions;
    FourierTransform(CarCoorFunction functions[]);

    class CarCoorPoint{
    public:
        double x;
        double y;
    };

    CarCoorPoint *figurePoints;
    CarCoorPoint getFigure(double t){
        int arrIndex = mapf(t,0,1,0,NumPoints);
        return figurePoints[arrIndex];
    }

    void aspect_ratio(CarCoorPoint as){
        if(as.x > as.y){
            aspect.y = as.y/as.x;
        }else if(as.y > as.x){
            aspect.x = as.x/as.y;
        }
        return;
    }

    void store_parameter(int t_min, int t_max, int arr_length);

    const char *p;
private:
    int T_MIN = 0;
    int T_MAX = 200;
    int NumPoints = 10000;
    double T_RES = ((T_MAX - T_MIN)/(double)NumPoints);

    int NumFunctions = 1;

    CarCoorPoint aspect;
    CarCoorPoint minVal;
    CarCoorPoint maxVal;

    double mapf(double val, double in_min, double in_max, double out_min, double out_max);
    void progress(int i){

        Serial.print(p);
        Serial.print("\t:\t");
        Serial.print(100.0*(i/(double)NumPoints));

        Serial.println();
    }
};
#endif