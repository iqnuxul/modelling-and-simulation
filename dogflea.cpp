#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;


// question 1
 void PrintIterations() {

 	int fleaA = 20;
	int fleaB = 0;
	int rNum;

	// ---- initial (i=0) -> fleaA:20, fleaB:0
	int i=1;
	while (i<=20){
        rNum = rand() % 20 + 1;
        if(rNum <= fleaA){
            fleaA--;
            fleaB++;
        }
        else{
            fleaA++;
            fleaB--;
        }

		cout<<i << ", " <<rNum<< ", " <<"X(" << i << ")" <<  "=" << " " << "(" << fleaA << "," << fleaB << ")" << endl;

        i++;

	}


 }


 // question 2
 int averageValue(){

	int fleaA = 20;
	int fleaB = 0;
	int rand (void);
	int rNum;
	int count=0;


	for(;;){


		rNum = rand() % 20 + 1;


		if(rNum <= fleaA){
		fleaA--;
		fleaB++;
		}

		else{
		fleaA++;
		fleaB--;
		}

		count++;

		if(fleaA==20 && fleaB==0) {
			break;
		}

	}

	return count;
}






int main(int argc, char** argv) {

srand(static_cast<unsigned>(time(0)));

	PrintIterations();

	cout<<endl;

	int avg;
	int sum;
	int simu = 0;
    while (simu < 20){
        sum+= averageValue();
        simu++;
    }

	avg=sum/20;
	cout<<" Average value of iterations= "<<avg<<endl;

	return 0;
}
