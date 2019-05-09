#include "IntegralOnR3.h"
#include <iRRAM.h>
#include <tuple>
#include <stdio.h>
#include <cmath>
using namespace iRRAM;


std::tuple<REAL, REAL, REAL> scaling(const REAL& x, const REAL& y, const REAL& z){
    return std::tuple<REAL, REAL, REAL>(x*pi(), y*pi(), scale(z*pi(),1));
}

std::tuple<REAL, REAL, REAL, REAL> coordinate_change(const REAL& eta, const REAL& theta, const REAL& phi){
    return std::tuple<REAL, REAL, REAL, REAL>(cos(eta), sin(eta)*cos(theta), sin(eta)*sin(theta)*cos(phi), sin(eta)*sin(theta)*sin(phi));
}

REAL abs_sum_H1(const REAL& x, const REAL& y, const REAL& z){
    REAL eta = x*pi();
    REAL theta = y*pi();
    REAL phi = z*pi()*2;
    REAL det_scaling = 1*pi()*pi()*pi()*2;
    REAL a = cos(eta);
    REAL b = sin(eta)*cos(theta);
    REAL c = sin(eta)*sin(theta)*cos(phi);
    REAL d = sin(eta)*sin(theta)*sin(phi);
    REAL det_coordinate_change = sin(eta)*sin(eta)*sin(theta);
    REAL function_value = abs(a)+abs(b)+abs(c)+abs(d);
    return function_value*det_coordinate_change*det_scaling;
}

REAL root_sum_square_H1(const REAL& x, const REAL& y, const REAL& z){
    REAL eta = x*pi();
    REAL theta = y*pi();
    REAL phi = z*pi()*2;
    REAL det_scaling = 1*pi()*pi()*pi()*2;
    REAL a = cos(eta);
    REAL b = sin(eta)*cos(theta);
    REAL c = sin(eta)*sin(theta)*cos(phi);
    REAL d = sin(eta)*sin(theta)*sin(phi);
    REAL det_coordinate_change = sin(eta)*sin(eta)*sin(theta);
    REAL function_value = sqrt(a*a + b*b + c*c + d*d);
    return function_value*det_coordinate_change*det_scaling;
}

REAL reduced_SU2_integral(int c){
    // f: SU(2) -> R. SU(2)=H_1 (unit quaternions aka versors)
    // Representation of versors: a+ib+jc+kd. So f takes (a,b,c,d) and interpret it as a+ib+jc+kd.
    // Rough Algorithm:
    // g := coordinate_change from (eta,theta,phi) in [0,pi)*[0,pi)*[0,2pi) to (a,b,c,d) (Consider |det(g)|)
    // which gives fg: [0,pi)*[0,pi)*[0,2pi) -> R.
    // h := scaling from [0,1)^3 to [0,pi)*[0,pi)*[0,2pi) (Consider |det(h)|)
    // which gives fgh: [0,1)^3 -> R.
    // Apply reduced_R3_average!
    // But how to express composition with function pointers?
    // TODO
    // For now, let's just give up recieving f as parameter and just declare it in the code.
    // It will allow us to reference it with a function pointer.
    // versors = unit quarternions = H1 = SU2
    return reduced_unit_R3_integral(abs_sum_H1, c);
}

REAL reduced_SO3_integral(int c){
    // SO3 is doubly covered by H1. Let this covering to be C.
    // function f on SO3 is represented as repr_f:H1->R s.t. C(q1) = C(q2) => repr_f(q1) = repr_f(q2).
    // sum_H1: H1->R but not satisfies the last condition.
    // However root_sum_square_H1 satisfies.
    return reduced_unit_R3_integral(abs_sum_H1, c);
}

void compute(){
    cout << setRwidth(1) << "\n";
    int c;
    cout << "Enter output scaling modifier (positive gives you less iRRAM digit requirement. Fast: 60): ";
    cin >> c;
    cout << "The integral of absolute sum function on SU(2) multiplied by 2^" << -c << ": " << reduced_SU2_integral(c) << "\n";
}