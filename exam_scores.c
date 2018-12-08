#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// functions
double h(double, double);            
double J();
double dJ_dt(int, int);

void updateParams();
void test();
void iterate();


// Accepted into college
double y[] = {0,0,0,1,1,0,1,1,1,1,0,0,1,1,0,1,1,0,1,1,0,1,0,0,1,1,1,0,0,0,1,1,0,1,0,0,0,1,0,0,1,0,1,0,0,0,1,1,1,1,1,1,1,0,0,0,1,0,1,1,1,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1}; 
// Exam 1 scores
double x1[] = {34.623661,30.286711,35.847408,60.182598,79.032738,45.083279,61.106663,75.024742,76.098785,84.432823,95.861557,75.013657,82.307053,69.364586,39.538338,53.971050,69.070145,67.946854,70.661507,76.978783,67.372025,89.676773,50.534790,34.212063,77.924095,62.271015,80.190178,93.114388,61.830208,38.785805,61.379288,85.404518,52.107979,52.045406,40.236893,54.635105,33.915501,64.176987,74.789253,34.183640,83.902397,51.547722,94.443367,82.368752,51.047752,62.222675,77.193031,97.771599,62.073063,91.564972,79.944817,99.272530,90.546715,34.524513,50.286495,49.586678,97.645638,32.577202,74.248688,71.796463,75.395615,35.286114,56.253819,30.058823,44.668262,66.560898,40.457550,49.072563,80.279572,66.746719,32.722832,64.039322,72.346497,60.457886,58.840958,99.827858,47.264271,50.458160,60.455555,82.226662,88.913895,94.834503,67.319260,57.238705,80.366753,68.468521,42.075455,75.477699,78.635422,52.348003,94.094330,90.448547,55.482162,74.492691,89.845810,83.489166,42.261700,99.315010,55.340019,74.775894}; 
// Exam 2 scores
double x2[] = {78.024696,43.894997,72.902199,86.308556,75.344376,56.316372,96.511429,46.554012,87.420570,43.533394,38.225277,30.603264,76.481964,97.718689,76.036812,89.207352,52.740471,46.678574,92.927139,47.575962,42.838440,65.799362,48.855812,44.209530,68.972359,69.954460,44.821629,38.800671,50.256107,64.995682,72.807884,57.051983,63.127625,69.432861,71.167747,52.213886,98.869438,80.908058,41.573414,75.237717,56.308044,46.856289,65.568924,40.618256,45.822701,52.060993,70.458199,86.727821,96.768822,88.696289,74.163116,60.999031,43.390602,60.396343,49.804539,59.808952,68.861572,95.598549,69.824570,78.453560,85.759933,47.020515,39.261471,49.592976,66.450089,41.092098,97.535187,51.883213,92.116058,60.991394,43.307175,78.031685,96.227592,73.095001,75.858452,72.369255,88.475868,75.809860,42.508408,42.719879,69.803787,45.694305,66.589355,59.514282,90.960152,85.594307,78.844788,90.424538,96.647430,60.769505,77.159103,87.508789,35.570702,84.845139,45.358284,48.380287,87.103851,68.775406,64.931938,89.529816};


// theta values
double t[] = {-10, 0.5, 0.5};
/* Pretrained parameters
{-25.159203759658 , 0.206214680594 , 0.201454361528}; // J() = 0.10174885685 */

// stores theta derivatives
double td[] = {0.0,0.0,0.0};
// learning rate alpha
double a = 0.001;
// previous and current cost function value
double cost = 3000.0;
double prevCost = 0;


// number of training sets
int m = sizeof(x1)/sizeof(double);
// index variable for training sets
int i;  

// number of parameters
int n = sizeof(t)/sizeof(double);
// index variable for parameters
int j;  

int iteration = 1;




int main(){

	// performs gradient descent on the values until convergence
	iterate();

	
	// test the model
	/*int correctGuesses = 0;

	for(i = 0; i < m; i++){
		int correct = 0;
		if( y[i] == 1 ){
			correct = ( h(x1[i],x2[i]) > 0.5 );
		}
		if( y[i] == 0){
			correct = ( h(x1[i],x2[i]) < 0.5 );
		}

		printf("\nh(%f, %f) = %.2f (%.1f) %s", x1[i], x2[i], h(x1[i],x2[i]), y[i], correct ? "✅":"💔" );

		correctGuesses += correct;
		//printf("\nln( h(%.3f, %.3f) ) = ln( %f ) = %f", x1[i], x2[i], h(x1[i],x2[i]), log( h(x1[i], x2[i]) ));
	}*/

	return 0;
}



// runs iterations until while loop is broken
void iterate(){

	do{  
		prevCost = cost;
		cost = J();

		// print values
		printf("\n\n      Iteration #%i ~ Cost: %.11f\n", iteration, cost );
		for(j = 0; j < n; j++){
			printf(" %15.12f%c",t[j],(j==n-1?'\n':','));
		}
	
		updateParams();
		iteration++;

		// decrease learning rate with each iteration
		//a *= 0.999;

	}while(iteration < 100000000);//prevCost > cost);   // while cost isn't getting larger 
}



// hypothesis
double h(double x1, double x2){

	double z = t[0] + t[1]*x1 + t[2]*x2;

	return 1 / ( 1 + exp(-z) );

}



// cost function
double J(){
	double sum = 0.0;

	for(i = 0; i < m; i++){
		
		sum += -y[i] * log( h(x1[i], x2[i]) )  -  (1 - y[i]) * log( 1 - h(x1[i], x2[i]) );

	}

	return sum/(2*m);
}



// update parameters to add cost function derivative
void updateParams(){
	double sum = 0.0;

	// loops through parameters and stores derivative function of J() in theta derivative array
	for(j = 0; j < n; j++){
		// sums up all x values
		for(i = 0; i < m; i++){
			// derivative of J()
			sum += dJ_dt(j, i) / m; 
		}
		td[j] = sum;
		sum = 0.0;
	}


	// sets parameters simultaneously
	for(j = 0; j < n; j++){
		t[j] -= a*td[j];
	}
}


// derivative of J w.r.t theta(j)
double dJ_dt(int j, int i){

	if(j==0){
		return (h(x1[i], x2[i]) - y[i]) * 1;
	}
	if(j==1){
		return (h(x1[i], x2[i]) - y[i]) * x1[i];
	}
	if(j==2){
		return (h(x1[i], x2[i]) - y[i]) * x2[i];
	}

	return 0;
}






/*
Extract data from text file
#include <stdio.h>
int main(){

	FILE *f;
	f = fopen("exam.txt","r");

	float x1[100];
	float x2[100];
	int y[100];


	for(int i = 0; i < 100; i++){
		fscanf(f,"%f,%f,%d", &x1[i], &x2[i], &y[i]);
	}


	for(int i = 0; i < 100; i++){
		printf("%f,",x2[i]);
	}
	for(int i = 0; i < 100; i++){
		printf("%d,",y[i]);
	}


	puts("");

	return 0;
}
*/
