#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


// functions
double h(int);            
double J();
double dJ_dt(int);

void mapFeatures();
void updateParams();
void test();
void iterate();


// Passed test
double y[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
// Test 1 value
double test1[] = {0.051267,-0.092742,-0.213710,-0.375000,-0.513250,-0.524770,-0.398040,-0.305880,0.016705,0.131910,0.385370,0.529380,0.638820,0.736750,0.546660,0.322000,0.166470,-0.046659,-0.173390,-0.478690,-0.605410,-0.628460,-0.593890,-0.421080,-0.115780,0.201040,0.466010,0.673390,-0.138820,-0.294350,-0.265550,-0.161870,-0.173390,-0.282830,-0.363480,-0.300120,-0.236750,-0.063940,0.062788,0.229840,0.293200,0.483290,0.644590,0.460250,0.627300,0.575460,0.725230,0.224080,0.442970,0.322000,0.137670,-0.006336,-0.092742,-0.207950,-0.207950,-0.438360,-0.219470,-0.138820,0.183760,0.224080,0.298960,0.506340,0.615780,0.604260,0.765550,0.926840,0.823160,0.961410,0.938360,0.863480,0.898040,0.851960,0.828920,0.794350,0.592740,0.517860,0.466010,0.350810,0.287440,0.085829,0.149190,-0.133060,-0.409560,-0.392280,-0.743660,-0.697580,-0.755180,-0.697580,-0.403800,-0.380760,-0.507490,-0.547810,0.103110,0.057028,-0.104260,-0.081221,0.287440,0.396890,0.638820,0.823160,0.673390,1.070900,-0.046659,-0.236750,-0.150350,-0.490210,-0.467170,-0.288590,-0.611180,-0.663020,-0.599650,-0.726380,-0.830070,-0.720620,-0.593890,-0.484450,-0.006336,0.632650}; 
// Test 2 value
double test2[] = {0.699560,0.684940,0.692250,0.502190,0.465640,0.209800,0.034357,-0.192250,-0.404240,-0.513890,-0.565060,-0.521200,-0.243420,-0.184940,0.487570,0.582600,0.538740,0.816520,0.699560,0.633770,0.597220,0.334060,0.005117,-0.272660,-0.396930,-0.601610,-0.535820,-0.535820,0.546050,0.779970,0.962720,0.801900,0.648390,0.472950,0.312130,0.027047,-0.214180,-0.184940,-0.163010,-0.411550,-0.228800,-0.184940,-0.141080,0.012427,0.158630,0.268270,0.443710,0.524120,0.670320,0.692250,0.575290,0.399850,0.553360,0.355990,0.173250,0.217110,-0.016813,-0.272660,0.933480,0.779970,0.619150,0.758040,0.728800,0.597220,0.502190,0.363300,0.275580,0.085526,0.012427,-0.082602,-0.206870,-0.367690,-0.521200,-0.557750,-0.740500,-0.594300,-0.418860,-0.579680,-0.769740,-0.755120,-0.579680,-0.448100,-0.411550,-0.258040,-0.258040,0.041667,0.290200,0.684940,0.706870,0.918860,0.904240,0.706870,0.779970,0.918860,0.991960,1.108900,1.087000,0.823830,0.889620,0.663010,0.641080,0.100150,-0.579680,-0.638160,-0.367690,-0.301900,-0.133770,-0.060673,-0.067982,-0.214180,-0.418860,-0.082602,0.312130,0.538740,0.494880,0.999270,0.999270,-0.030612};

// Features consisting of all possible polynomial terms of test1 and test2 
double x[118][28];


// theta values
double t[28] = {2.98695, -0.25502, 3.96098, -5.19302, -9.13164, 4.22814, 5.69945, 12.76224, 17.87164, -2.75289, 8.84817, 1.20228, -15.05260, -0.13660, -28.53447, -0.02772, -6.77121, 13.66021, -12.49277, -20.38953, 14.66195, -30.30898, -13.15262, -5.87990, 18.58671, -28.09428, -20.80702, 0.79870}; 

// stores theta derivatives
double td[28];
// learning rate alpha
double a = 2;
// regularisation parameter lambda
double L = 1;
// previous and current cost function value
double cost = 3000.0;
double prevCost = 0;


// number of training sets
int m = sizeof(y)/sizeof(double);
// index variable for training sets = int i;  

// number of parameters
int n = sizeof(t)/sizeof(double);
// index variable for parameters = int j;  

int iteration = 1;




int main(){

	// initialise parameters to 0
	for(int j = 0; j < n; j++){t[j] = 0;}


	mapFeatures();

	// performs gradient descent on the values until convergence
	iterate();

	
	// write model as equation
	/*int j = 0;
	printf("1/(1+e^(");
	for(int a = 0; a <= 6; a++){
		for(int b = 0; b <= a; b++){
			printf("%fx^%dy^%d+",t[j],a-b,b);
			j++;
		}
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
		for(int j = 0; j < n; j++){
			printf(" %7.5f%c",t[j],(j==n-1?'\n':','));
		}
	
		updateParams();
		iteration++;

		// decrease learning rate with each iteration
		//a *= 0.999;

	}while(prevCost >= cost && iteration <= 100000);   // while cost isn't getting larger 
}


// hypothesis for training set i
double h(int i){

	double z = 0;
	// product of features and parameters
	for(int j = 0; j < n; j++){
		z += x[i][j] * t[j];
	}

	return 1 / ( 1 + exp(-z) );

}



// cost function
double J(){
	double sum = 0.0;

	// mean square error
	for(int i = 0; i < m; i++){
		
		sum += -y[i] * log( h(i) )  -  (1 - y[i]) * log( 1 - h(i) );

	}

	// regularisation
	for(int j = 1; j < n; j++){

		sum += pow( t[j] , 2 ) * L / (2*m);

	}

	return sum/(2*m);
}



// update parameters to add cost function derivative
void updateParams(){

	// loops through parameters and stores derivative function of J() in theta derivative array
	for(int j = 0; j < n; j++){
		// sums up all x values
		td[j] = dJ_dt(j);
	}


	// sets parameters simultaneously
	for(int j = 0; j < n; j++){
		t[j] -= a*td[j];
	}

}


// derivative of J w.r.t theta(j)
double dJ_dt(int j){
	double sum = 0.0;
	for(int i = 0; i < m; i++){
		// derivative of J()
		sum += ( h(i) - y[i] ) * x[i][j]; 
	}
	return ( sum + t[j] * L ) / m ;
}


// creates features based off polynomial terms of the test scores 
void mapFeatures(){
	// tracks which feature is being mapped
	int j = 3;
	// to what power are the features mapped
	int degree = 6;

	for(int i = 0; i < m; i++){
		x[i][0] = 1;
		x[i][1] = test1[i];
		x[i][2] = test2[i];
		// creates the different polynomials
		for(int a = 2; a <= degree; a++){
			for(int b = 0; b <= a; b++){

				x[i][j] = pow(test1[i], a-b) * pow(test2[i], b);
				
				j++;
			}
		}

		j = 3;
	}

}


/*#include <stdio.h>
int main(){

	FILE *f;
	f = fopen("micro.txt","r");

	float x1[118];
	float x2[118];
	int y[118];


	for(int i = 0; i < 118; i++){
		fscanf(f,"%f,%f,%d", &x1[i], &x2[i], &y[i]);
	}


	for(int i = 0; i < 118; i++){
		printf("%f,",x1[i]);
	}puts("");

	for(int i = 0; i < 118; i++){
		printf("%f,",x2[i]);
	}puts("");

	for(int i = 0; i < 118; i++){
		printf("%d,",y[i]);
	}


	puts("");

	return 0;
}*/
