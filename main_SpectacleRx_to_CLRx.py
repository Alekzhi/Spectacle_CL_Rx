"""
Conversion of Spectacle Rx to CL Rx
For Dr. Kry
Dcl =  CL Rx (Contact Lens Prescription)
Dv = Vertex Factor
d = Vertex Distance (12mm) in decimal: 0.012 (meter x 0.001)
Formula: Dcl = Dv / (1 - (d (Dv)))
TODO: Develop this into a GUI-App
"""
import pdb

class Patient:
    def __init__(self):
        self.Dv_VertexFactor = 1.0
        self.d_VertexDistance = 0.012
        self.Dcl_Initial_CL_Prescription = 1.0
        self.DclRx_Final_CL_Prescription = 1.0
        self.Error_ofRefraction = 1.0

    def diagnostics(self):
        print("____________________________________")
        print("Conversion of Spectacle Rx to Contact Lens Rx.")
        print("------------------------------------")
        self.Dv_VertexFactor = float(input("[Py] Input the Spectacle Vertex Factor (Dv): "))
        self.Error_ofRefraction = self.getPatientEOR()
        self.Dcl_Initial_CL_Prescription = self.get_Dcl()
        self.DclRx_Final_CL_Prescription = self.get_DclRx()
        print("Dv =", self.Dv_VertexFactor)
        print("d =", self.d_VertexDistance)
        print("Dcl =", self.Dcl_Initial_CL_Prescription)
        print(f"DclRx = {self.DclRx_Final_CL_Prescription}D  --> recommended prescription!")

    def getPatientEOR(self):
        print("Checking patient's sight's Error of Refraction...")
        if self.Dv_VertexFactor < 0:
            print("Patient is near-sighted.")
            return -1
        else:
            print("Patient is far-sighted.")
            return 1

    def get_Dcl(self):  # Dcl = Dv / (1 - (d (Dv)))
        Dcl = float(self.Dv_VertexFactor / (1 - (self.d_VertexDistance * self.Dv_VertexFactor)))
        return float(f"{Dcl:.2f}")

    def get_DclRx(self):
        Dcl = self.Dcl_Initial_CL_Prescription
        list_of_DcL_Increments = [0.0, 0.25, 0.50, 0.75, 1.0]
        Dcl_decimal = float(f"{Dcl % float(int(Dcl)):.2f}")
        Dcl_decimal = abs(Dcl_decimal)
        list_of_DcL_Increments.append(Dcl_decimal)
        list_of_DcL_Increments.sort()
        leftIndex_of_Dcl = list_of_DcL_Increments.index(Dcl_decimal) - 1
        rightIndex_of_Dcl = list_of_DcL_Increments.index(Dcl_decimal) + 1
        left_of_Dcl_decimal = list_of_DcL_Increments[leftIndex_of_Dcl]
        right_of_Dcl_decimal = list_of_DcL_Increments[rightIndex_of_Dcl]
        if abs(Dcl_decimal - left_of_Dcl_decimal) <= abs(Dcl_decimal - right_of_Dcl_decimal):
            DclRx = int(abs(Dcl)) + left_of_Dcl_decimal
        else:
            DclRx = int(abs(Dcl)) + right_of_Dcl_decimal
        return DclRx * self.Error_ofRefraction


def main():
    run_program = 'y'
    while run_program.lower() != 'q':
        # _________write program flow from here____________________________

        patient = Patient()
        patient.diagnostics()

        # ---------end the program by pressing 'q'-------------------------
        run_program = input("\nPress 'q' to exit program or any key to continue: ")
        # pdb.set_trace()


if __name__ == "__main__":
    main()
