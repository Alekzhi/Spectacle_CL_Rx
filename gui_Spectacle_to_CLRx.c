/*  
Conversion of Spectacle Rx to Contact Lense Rx
For Dr. Kry. This is just a draft in C that I'm going to develop in Python 
*/

#include <stdio.h>
#include <math.h>
#include <gtk/gtk.h>  // TODO

// Constants
#define D_VERTEX_DISTANCE 0.012

// Function prototypes
float get_Dcl(float Dv);
float get_DclRx(float Dcl, float ErrorofRefraction);
int getPatientEOR(float Dv);

// Callback function for the "Convert" button
void convert(GtkWidget *widget, gpointer data)
{
    // Get user input from the entry field
    GtkWidget *entry = (GtkWidget *)data;
    const gchar *entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
    float Dv_VertexFactor = atof(entry_text);

    // Check patient's sight's Error of Refraction
    float ErrorofRefraction = getPatientEOR(Dv_VertexFactor);

    // Calculate Initial CL Prescription (Dcl)
    float Dcl_Initial_CL_Prescription = get_Dcl(Dv_VertexFactor);

    // Calculate Final CL Prescription (DclRx)
    float DclRx_Final_CL_Prescription = get_DclRx(Dcl_Initial_CL_Prescription, ErrorofRefraction);

    // Display results in labels
    GtkWidget *dcl_label = GTK_WIDGET(gtk_builder_get_object(builder, "dclLabel"));
    GtkWidget *dclrx_label = GTK_WIDGET(gtk_builder_get_object(builder, "dclrxLabel"));

    gchar dcl_text[50];
    gchar dclrx_text[50];
    snprintf(dcl_text, sizeof(dcl_text), "Dcl = %.2f", Dcl_Initial_CL_Prescription);
    snprintf(dclrx_text, sizeof(dclrx_text), "DclRx = %.2fD", DclRx_Final_CL_Prescription);

    gtk_label_set_text(GTK_LABEL(dcl_label), dcl_text);
    gtk_label_set_text(GTK_LABEL(dclrx_label), dclrx_text);
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Spectacle Rx to Contact Lens Rx");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 300, 150);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box container
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Create a label and entry for Spectacle Vertex Factor
    GtkWidget *label = gtk_label_new("Spectacle Vertex Factor:");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    GtkWidget *entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    // Create a button to convert
    GtkWidget *convert_button = gtk_button_new_with_label("Convert to Contact Lenses Rx");
    g_signal_connect(convert_button, "clicked", G_CALLBACK(convert), entry);
    gtk_box_pack_start(GTK_BOX(vbox), convert_button, FALSE, FALSE, 0);

    // Create labels to display results
    GtkWidget *dcl_label = gtk_label_new("");
    GtkWidget *dclrx_label = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(vbox), dcl_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), dclrx_label, FALSE, FALSE, 0);

    // Show all widgets
    gtk_widget_show_all(window);

    gtk_main();

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
