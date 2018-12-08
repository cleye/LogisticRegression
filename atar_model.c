#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// functions
double h(double);            
double J();
double dh_dt(int, double);

void updateParams();
void test();
void iterate();

double randomNum(double, double);
void loadData();


// ATAR Score array
double *y;
// TEA Score array
double *x;


// theta values
double t[] = {  99.951052628383,  2.314107713892,  4.437402228273,  6.456970792411,  1.057083074229 }; 

// 2017
// 80.00 - 99.95 { 99.951052628383,  2.314107713892,  4.437402228273,  6.456970792411,  1.057083074229 } cost: 0.029492
// 30.05 - 99.95 { 99.948851354578,  2.179848698938,  4.141666381081,  8.032943994047,  1.070814981640 } cost: 0.022067

// 2016
// 30.05 - 99.95 { 94.6360838509581 , 2.2682264746169 , 4.4265824743542 , 12.8391018323147 , 1.0648458217895} cost: 0.032941
// 80.00 - 99.95 { 94.6298596035790 , 2.4998915145444 , 5.0040167829926 , 13.1294202805079 , 1.0756699367712} cost: 0.025570

// stores theta derivatives
double td[] = {0.0,0.0,0.0,0.0,0.0};
// learning rate alpha
double a = 0.0001;
// previous and current cost function value
double cost = 10000.0;
double prevCost = 0;


// number of training sets
int m = 49;  // 24 for 80.00 - 99.95,   49 for 30.05 - 99.95
// number of features
int n = 5;

int iteration = 1;



int main(){

	loadData();

	// performs gradient descent on the values until convergence
	iterate();

	for(int i = 0; i < m; i++){
		printf(" h(%.1f) = %.6f (%.2f) \n", x[i], h(x[i]), y[i] );
	}

	
	free(x);
	free(y);

	return 0;
}



// runs iterations until while loop is broken
void iterate(){

	do{  
		prevCost = cost;
		cost = J();

		// print values
		printf("\n\n      Iteration #%i ~ Cost: %.11f\n", iteration, cost );
		for(int i = 0; i < n; i++){
			printf(" %15.12f%c",t[i],(i==4?'\n':','));
		}
	
		updateParams();
		iteration++;

		// decrease learning rate with each iteration
		//a *= 0.999;

	}while(iteration < 10000  &&  cost < prevCost);   // while cost isn't getting larger 
}



// hypothesis
double h(double x){

	return t[0] / ( t[4] + exp(-t[1]*x/100 + t[2]) )  +  t[3];

}



// cost function
double J(){
	double sum = 0.0;

	for(int i = 0; i < m; i++){
		sum += pow(  h(x[i]) - y[i]  , 2  );
	}

	return sum/(2*m);
}



// update parameters to add cost function derivative
void updateParams(){
	double sum = 0.0;

	// loops through parameters and stores derivative function of J() in theta derivative array
	for(int i = 0; i < n; i++){
		// sums up all x values
		for(int k = 0; k < m; k++){
			// derivative of J(), including dh_dt for chain rule
			sum += ( h(x[k]) - y[k] ) * dh_dt(i, x[k]) / m;
		}
		td[i] = sum;
		sum = 0.0;
	}

	// sets parameters simultaneously
	for(int i = 0; i < n; i++){
		t[i] -= a*td[i];
	}
}


// derivative of h w.r.t theta(j)
double dh_dt(int j, double x){
	if(j == 0){
		return 1 / ( t[4] + exp(-t[1]*x/100 + t[2]) );
	}
	if(j == 1){
		return t[0]*x*exp(-t[1]*x/100 + t[2]) / ( 100*pow( ( t[4] + exp(-t[1]*x/100 + t[2]) ) , 2) );
	}
	if(j == 2){
		return -t[0] * exp(-t[1]*x/100 + t[2]) / pow( ( t[4] + exp(-t[1]*x/100 + t[2]) ) , 2);
	}
	if(j == 3){
		return 1;
	}
	if(j == 4){
		return -t[0] / pow( ( t[4] + exp(-t[1]*x/100 + t[2]) ) , 2 );
	}
	return 0;
}

double randomNum(double lower, double upper){
	return  lower + 
		(double)(
			rand() % (
			 (int)( 
			 	(upper-lower)*10000000.0) 
			 ) 
		) 
		/ 10000000;
}

void loadData(){

	x = malloc(m * sizeof(double));
	y = malloc(m * sizeof(double));

	if(x == NULL || y == NULL){
		printf("Couldn't allocate memory \n");
	}

	FILE *data;
	data = fopen("tea2017.txt","r");
	if(data == NULL){
		printf("Error opening file");
	}

	int i = 0;
	while(i < m){
		fscanf(data, "%lf\t%lf\n", &x[i], &y[i]);
		printf("%f %f\n",y[i],x[i]);
		i++;
	}

	fclose(data);
	

}
