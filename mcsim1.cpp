// mcsim1.cpp : Defines the entry point for the console application.
// This simulation tries to use law of large numbers to estimate call price return
// Author: Xin Wang
// http://en.cppreference.com/w/cpp/numeric/random

#include "stdafx.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>

using namespace std;

// class European Option Price
class EOprice{
	double intrate_r;
	double volatile_sigma;
	double time_t;
	double strike_k;
	double s_0;
public:
	double tprice_s;
	EOprice();
	~EOprice();
	int num_sim; // number of simulations;
	double call_price(double num_sim, double strike_k, double intrate_r, double volatile_sigma, double s_0, double time_t);	
};

EOprice::EOprice(){
	tprice_s = 0;
};

EOprice::~EOprice(){
	cout << "Simulation done" << endl;
};

double EOprice::call_price(double num_sim, double strike_k, double intrate_r, double volatile_sigma, double s_0, double time_t) {

	double s_t; // the stock price at time t;
	double v_time=0; // return value for European option;
	double sfront = s_0*exp((intrate_r-0.5*pow(volatile_sigma, 2))*time_t); // non random part of s;
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0, 1); // mean 0, sigma volatile;
	for (int i=0; i<num_sim; i++){
		double nrand_num = distribution(generator); // non restriction normal distribution number;
		s_t = sfront*exp(sqrt(time_t)*volatile_sigma*nrand_num);
		v_time += std::max((s_t-strike_k), 0.0);		
	}
	tprice_s = (v_time/num_sim)*exp(-1*intrate_r*time_t);
	return tprice_s;
}

int main(int argc, char* argv[])
{
	// first initialize the object;
	double s0, rate_r, k, vsigma, time_t;
	double vprice; // the estimated option price;
	int simnum;

	cout<< "Input the number of simulations: \n";
	cin >> simnum;

	cout<< "Input the volatility sigma: \n";
	cin >> vsigma;

	cout<< "Input the time in years t: \n";
	cin >> time_t;

	cout << "Input the current stock price S0: \n";
	cin >> s0;

	cout << "Interest rate r: \n";
	cin >> rate_r;

	cout << "Interest strike k: \n";
	cin >> k;
	
	EOprice voption;
	vprice = voption.call_price(simnum, k, rate_r, vsigma, s0, time_t);

	// output the result;
	cout << "The Monte Carlo simulated option price is:";
	cout << vprice << "\n";

	return 0;
}

Enter file contents here
