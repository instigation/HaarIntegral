#include <iRRAM.h>
#include <stdio.h>
#include <cmath>

using namespace iRRAM;

REAL identity(const REAL &x){ return x; }
REAL quadratic(const REAL &x){ return x*x; }

int global_modulus(REAL (*f)(const REAL &), int target_prec){
	// <summary>
	// Assumes that the domain of f is [0,1] and compute the modulus on the interval.
	// <\summary>
	REAL end = REAL(0);
	int m_at_1 = module(f, REAL(1), target_prec);
	int global_m = m_at_1;
	while(choose(end > REAL(1)-scale(REAL(1),m_at_1), end < REAL(1)) == 2){
		int m = module(f, end, target_prec);
		if(m < global_m)
			global_m = m;
		end += scale(REAL(1),m);
	}
	return global_m;
}

REAL reduced_unit_R_integral(REAL (*f)(const REAL &)){
	// <summary>
	// It computes 2^{-30}\int_[0,1] fdx.
	// By computing \int_[0,1] fdx with precision target_prec+30
	// and then multiplying it with 2^{-30}.
	// It will give approximation of 2^{-30}\int_[0,1] fdx with precision target_prec.
	// <\summary>
	auto result_in_seq = [f](int target_prec) -> REAL{
		REAL ret = REAL(0);
		int m = global_modulus(f, target_prec + 30);
		REAL segment_width = scale(REAL(1), m);
		// TODO: have to convert from int to long if -m gets bigger
		for(int i=0; i<pow(2, -m); i++){
			ret += f(scale(REAL(i)+REAL(0.5), m))*segment_width;
		}
		return scale(ret,-30);
	};
	return limit(result_in_seq);
}

void compute(){
	int r_width;
	cout << "Enter r_width (i.e. how much \"precision\" you want. Recommended value is 10): ";
	cin >> r_width;
	cout << setRwidth(r_width) << "\n";
	REAL r1 = reduced_unit_R_integral(identity);
	cout << "The integral of identity function on [0,1]: " << scale(r1, 30) << "\n";
	REAL r2 = reduced_unit_R_integral(quadratic);
	cout << "The integral of quadratic function on [0,1]: " << scale(r2, 30) << "\n";
	REAL r3 = reduced_unit_R_integral(sin);
	cout << "The integral of sine function on [0,1]: " << scale(r3, 30) << "\n";
	cout << "The correct answer for integral of sine function : 1-cos1 = " << REAL(1)-cos(REAL(1)) << "\n";
}
