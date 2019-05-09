#include "IntegralOnR3.h"

typedef struct _Cube{
    // It represents a cube of coordinate (2^n*[x,x+1]) \times (2^n*[y,y+1]) \times (2^n*[z,z+1])
    int x, y, z;
    int n;
} Cube;

int global_modulus(REAL (*f)(const REAL &, const REAL &, const REAL &), Cube domain, int target_precision){
    // <summary>
    // Assumes that the domain of f is *domain* and compute the global modulus on the domain.
    // Warning: even with m=-8, it will run for like 2^8 seconds..
    // <\summary>
    REAL x, y, z;
    x = scale(REAL(domain.x), domain.n);
    y = scale(REAL(domain.y), domain.n);
    z = scale(REAL(domain.z), domain.n);
    int m = modulus(f, target_precision, x, y, z);
    if(m >= domain.n){
        return m;
    }
    else{
        int min_modulus = domain.n;
        for(int i=0; i<pow(2, domain.n - m); i++){
            for(int j=0; j<pow(2, domain.n - m); j++){
                for(int k=0; k<pow(2, domain.n - m); k++){
                    Cube subdomain;
                    subdomain.x = domain.x * pow(2, domain.n - m) + i;
                    subdomain.y = domain.y * pow(2, domain.n - m) + j;
                    subdomain.z = domain.z * pow(2, domain.n - m) + k;
                    subdomain.n = m;
                    int ret = global_modulus(f, subdomain, target_precision);
                    if(ret < min_modulus)
                        min_modulus = ret;
                }
            }
        }
        return min_modulus;
    }
}

REAL reduced_unit_R3_integral(REAL (*f)(const REAL&, const REAL&, const REAL&), int c){
    // <summary>
    // It computes 2^{-c}\int_[0,1]^3 fdx.
    // By computing \int_[0,1]^3 fdx with precision target_prec+c
    // and then multiplying it with 2^{-c}.
    // Even with c=42, it runs for like 10min.
    // <\summary>
    auto result_in_seq = [f, c](int target_prec) -> REAL{
        REAL ret = REAL(0);
        Cube domain;
        domain.x = domain.y = domain.z = domain.n = 0;
        int m = global_modulus(f, domain, target_prec + c);
        REAL cube_volume = scale(REAL(1), 3*m);
        // TODO: have to convert from int to long if -m gets bigger
        for(int i=0; i<pow(2, -m); i++){
            for(int j=0; j<pow(2, -m); j++){
                for(int k=0; k<pow(2, -m); k++){
                    ret += f(
                            scale(REAL(i)+REAL(0.5), m),
                            scale(REAL(j)+REAL(0.5), m),
                            scale(REAL(k)+REAL(0.5), m)
                    )*cube_volume;
                }
            }
        }
        return scale(ret, -c);
    };
    return limit(result_in_seq);
}