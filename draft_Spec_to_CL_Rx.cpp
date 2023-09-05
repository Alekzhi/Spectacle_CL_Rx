#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

/*
  Conversion ng Spectacle Rx to CL Rx.
  For Dr. Kry (Doctor of Optometry)
  Dcl =  CL Rx (Contact Lens Prescription)
  Dv = Vertex Factor
  d = Vertex Distance (12mm) in decimal: 0.012 (meter x 0.001)
  Formula: Dcl = Dv / (1 - (d (Dv)))
*/
const double d = 0.012;  
double FloorDcl;
double GetDcl(double Dv);
double DiffBetween(double Dcl, double DclFloorBy025);
double GetDclRx (double Dcl);
void showPatientEOR(double Dcl);

int main() {
  double DclRx;
  double Dcl;
  double Dv;  
  double LowerDcl;
  double UpperDcl;
  
  cout << "\n\nConversion of Spectacle Rx to CL Rx." << endl;
  cout << "To get CL Rx, input the Spectacle Vertex Factor: ";
  cin >> Dv;
  showPatientEOR(Dv);
  Dcl = GetDcl(Dv);
  DclRx = GetDclRx(Dcl);
  cout << "\nDv = "<< Dv << "\n d = " << d;
  cout << "\nDcl = "<< Dcl << endl; 
  cout << "\nRecommendee CL Rx is " << DclRx << " D\n\n";
  system("pause");
  return 0;
}

double GetDcl(double Dv) {
  return Dv / (1 - (d * Dv));;
}

double DiffBetween(double Dcl, double DclFloorBy025) {
  return abs(Dcl - DclFloorBy025);
}

double GetDclRx(double Dcl) {
  double DclRx = 0;
  double FloorDcl;
  double List_of_Increments[] = {0.0, 0.25, 0.50, 0.75, 1.0};
  
  double ClosestIncrement = 0.0;
  cout << "\n---Fetching DclRx..";
  Dcl = abs(Dcl);
  printf("\nabs(Dcl): %.2lf", Dcl);  FloorDcl = floor(Dcl);
  printf("\nfloor(Dcl): %.2lf\n", FloorDcl);
  int Count = 0;
  for (double EachIncrement : List_of_Increments) {
      printf("\nIncr: %.2lf ", EachIncrement);
      List_of_Increments[Count] = FloorDcl + EachIncrement;
      printf("- %.2lf", List_of_Increments[Count]);
      Count++;
  }
 
//  for(double Arr : IncrementBy025) {
//    if(DiffBetween(Dcl, FloorDcl+Arr) < DiffBetween(Dcl, FloorDcl+(Arr+1))) {
//      printf("%.2lf %.2f", Arr, Arr+1);
//      cout <<'\n'; 
//      ClosestIncrement = Arr;
//    } else {
//        ClosestIncrement = Arr+1;
//    }
//  }
//  DclRx = FloorDcl + ClosestIncrement;
//  cout << "\n...\nDclRx before *(-1) = " << DclRx << endl;
//  DclRx = DclRx * (-1);
  return DclRx;
}

void showPatientEOR(double Dv) {
  bool DvIsNegative = false;
  if (Dv < 0) 
      DvIsNegative = true;
  (DvIsNegative == true) 
      ? cout << "Patient is near-sighted.\n" 
      : cout << "Patient is far-sighted.\n";
}