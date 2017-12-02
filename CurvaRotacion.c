/* prints the message of 
*/

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define PI 3.14159265358979323846

int n=300;
int t=10000;
double bb=0.2497, bd=5.16, ad=0.3105, ah=64.3;
int i, j ,k;

double likelihood(double *x, double *y);
double *modelo(double *z, double mb0, double md0, double mh0);
double gaussrand();
//double *modelo(void);
int main(void){
	 
	//apartar memoria
	double * R=malloc(n*sizeof(double));
	double * V=malloc(n*sizeof(double));
	double * mb=malloc(t*sizeof(double));
	double * md=malloc(t*sizeof(double));
	double * mh=malloc(t*sizeof(double));
	double * l=malloc(t*sizeof(double));
	double * v_init=malloc(t*sizeof(double));
	//double * v_p=malloc(n*sizeof(double));
	//double *v_init;

	//Inicializar
	
	double var1, var2;

	/*
	for(i=0; i<n;i++){
		R[i]=0.0;
		V[i]=0.0;
	}
	*/
	//srand48(time(NULL));
	FILE *in;
	in=fopen("RadialVelocities.dat","r");

	FILE *fp;
	fp=fopen("datos.txt","wb");
	


	while(fscanf(in, "%lf %lf", &var1 , &var2)==2){
		R[i]=var1;
		V[i]=var2;
		i += 1;
	}

	fclose(in);
	/*
	for(i=0; i<n;i++){

		fprintf(fp,"%lf %lf\n ", R[i] , V[i]);
			
	}
	*/
	
	//res=likelihood(R,V);
	//l=modelo(R,2.0,3.0,4.0);


	mb[0]=drand48();
	md[0]=drand48();
	mh[0]=drand48();
	l[0]=drand48();
	//l=modelo();
	double g1, g2;
	g1=gaussrand();
	g2=gaussrand();
	v_init=modelo(R, mb[0], md[0], mh[0]);
	l[0]=likelihood(V, v_init);
	
	/*
	double mb_p;
	double md_p;
	double mh_p;
	double l_p;
	double l_init=0.01;
	*/
	for(i=0; i<t;i++){
		
		double mb_p=(gaussrand()*70+mb[i-1]);
		double md_p=(gaussrand()*70+md[i-1]);
		double mh_p=(gaussrand()*70+mh[i-1]);
			
		//printf("%lf\n ", mb_p);
		
		double * v_p=malloc(n*sizeof(double));
		
		v_p=modelo(R, mb_p, md_p, mh_p);
		
		
		v_init=modelo(R, mb[i-1], md[i-1], mh[i-1]);
		
		

		double l_p=likelihood(V,v_p);
		double l_init=likelihood(V,v_init);
		

		
		double alpha=l_p/l_init;
		//printf("%lf %lf %lf\n ", l_p, l_init, alpha);	
			
		
		if(alpha>=1.0){
			mb[i]=mb_p;		
			md[i]=md_p;
			mh[i]=mh_p;
			l[i]=l_p;				
		}else{
			double beta=drand48();
			if(beta<=alpha){
				mb[i]=mb_p;		
				md[i]=md_p;
				mh[i]=mh_p;
				l[i]=l_p;
			}else{
				mb[i]=mb[i-1];		
				md[i]=md[i-1];
				mh[i]=mh[i-1];
				l[i]=l_init;		
			}
		}
	
		
	}	

	
		
	/*	
	for(i=0; i<n;i++){

		printf("%lf %lf\n ", v_init[i], v_p[i]);
			
	}
	*/
	for(i=0; i<t;i++){

		fprintf(fp,"%lf %lf %lf %lf\n ", mb[i] , md[i], mh[i], l[i]);
			
	}
	
	double l_max=0.0;
	int l_max_ind=0;
	for(i=0; i<t;i++){
		if(l[i]>l_max){
			l_max=l[i];
			l_max_ind=i;		
		}
		
			
	}
	double best_mb;
	double best_md;
	double best_mh;
	best_mb=mb[l_max_ind];
	best_md=md[l_max_ind];
	best_mh=mh[l_max_ind];
	
	//printf("%lf %ld\n ", l_max, l_max_ind);
	printf("%lf %lf %lf\n ", pow(best_mb,2.0), pow(best_md,2.0),pow(best_mh,2.0));
	//printf("%lf %lf %lf %lf %lf %lf", mb[0], md[0], mh[0],l[0],g1,g2);
	
	return 0;

}

double likelihood(double *x, double *y){
	double chi=0.0;
	for(j=0; j<n;j++){
		double resta=x[j]-y[j];
		chi+= pow((resta/100.0),2);
	}
	return exp(-chi/2.0);
}
/*
double *modelo(void){
	double * mod=malloc(n*sizeof(double)); 
	for(i=0; i<n;i++){
		mod[i]=i;
	}
	return mod;
}

*/

double *modelo(double *z, double mb0, double md0, double mh0){
	double * mod=malloc(n*sizeof(double)); 	
	for(j=0; j<n;j++){
		double denb=pow(z[j],2)+pow(bb,2);
		double dend=pow(z[j],2)+pow((bd+ad),2);
		double denh=pow(z[j],2)+pow(ah,2);
		mod[j]=mb0*z[j]/(pow(denb,3.0/4.0))+md0*z[j]/(pow(dend,3.0/4.0))+mh0/(pow(denh,1.0/4.0));
	}
	return mod;
}



double gaussrand(){
	static double U, V;
	static int phase = 0;
	double Z;

	if(phase == 0) {
		U = (rand() + 1.) / (RAND_MAX + 2.);
		V = rand() / (RAND_MAX + 1.);
		Z = sqrt(-2 * log(U)) * sin(2 * PI * V);
	} else
		Z = sqrt(-2 * log(U)) * cos(2 * PI * V);

	phase = 1 - phase;

	return Z;
}
	
