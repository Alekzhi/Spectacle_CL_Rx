/*  
Conversion of Spectacle Rx to Contact Lense Rx
For Dr. Kry. This is just a draft in C that I'm going to develop in Python 
*/

#include <stdio.h>
#include <math.h>

// Constants
#define D_VERTEX_DISTANCE 0.012

// Function prototypes
float get_Dcl(float Dv);
float get_DclRx(float Dcl, float ErrorofRefraction);
int getPatientEOR(float Dv);

int main() {
    float Dv_VertexFactor = 1.0;
    float Dcl_Initial_CL_Prescription = 1.0;
    float DclRx_Final_CL_Prescription = 1.0;
    float ErrorofRefraction = 1.0;
    char run_program = 'y';

    while (run_program != 'q') {
        // Input Spectacle Vertex Factor (Dv)
        printf("[C] Input the Spectacle Vertex Factor (Dv): ");
        scanf("%f", &Dv_VertexFactor);

        // Check patient's sight's Error of Refraction
        ErrorofRefraction = getPatientEOR(Dv_VertexFactor);

        // Calculate Initial CL Prescription (Dcl)
        Dcl_Initial_CL_Prescription = get_Dcl(Dv_VertexFactor);

        // Calculate Final CL Prescription (DclRx)
        DclRx_Final_CL_Prescription = get_DclRx(Dcl_Initial_CL_Prescription, ErrorofRefraction);

        // Output results
        printf("Dv = %f\n", Dv_VertexFactor);
        printf("d = %f\n", D_VERTEX_DISTANCE);
        printf("Dcl = %f\n", Dcl_Initial_CL_Prescription);
        printf("DclRx = %.2fD --> recommended prescription!\n", DclRx_Final_CL_Prescription);

        // Ask user to continue or exit
        printf("\nPress 'q' to exit program or any key to continue: ");
        scanf(" %c", &run_program);
    }

    return 0;
}

// Calculate Dcl: Dcl = Dv / (1 - (d * Dv))
float get_Dcl(float Dv) {
    return Dv / (1 - (D_VERTEX_DISTANCE * Dv));
}

// Calculate DclRx
float get_DclRx(float Dcl, float ErrorofRefraction) {
    float list_of_DcL_Increments[] = {0.0, 0.25, 0.50, 0.75, 1.0};
    float Dcl_decimal = Dcl - (int)Dcl;
    int num_increments = sizeof(list_of_DcL_Increments) / sizeof(list_of_DcL_Increments[0]);
    float closest_increment = list_of_DcL_Increments[0];
    for (int i = 1; i < num_increments; i++) {
        float current_diff = fabs(Dcl_decimal - list_of_DcL_Increments[i]);
        if (current_diff < Dcl_decimal - closest_increment)
        {
            closest_increment = list_of_DcL_Increments[i];
            // Monitoring the values of some indices
            // printf("Dcl_decimal: %.3f , closest_increment: %.3f, current_diff: %.3f next\n",
            //        Dcl_decimal, closest_increment, current_diff);
        }
    }

    return ((int)Dcl + closest_increment) * ErrorofRefraction;
}

// Check patient's sight's Error of Refraction
int getPatientEOR(float Dv) {
    printf("Checking patient's sight's Error of Refraction...\n");
    if (Dv < 0) {
        printf("Patient is near-sighted.\n");
        return -1;
    } else {
        printf("Patient is far-sighted.\n");
        return 1;
    }
}
