#include "../AlgebraLineal/vectores.h"



FILE *plot_create() {
    return popen ("gnuplot-qt -persistent", "w");
}

int plot_destroy(FILE * plot_pipe){
    return pclose(plot_pipe);
}

int main(void){

    //tres columnas y para un mismo x, vi que se puede cambiar el x para alguna, pero no sé cómo funcione para vcolumnas de distinto largo
    char * commandsForGnuplot = "set title \"título de gráfico\" ; set grid; plot 'data_set.dat' using 1:3 title '2x' with linespoint ,'data_set.dat' using 1:2 title 'x^2' with linespoint , 'data_set.dat' using 1:4 title 'random' with linespoint ";

    FILE * plot = plot_create();
    fprintf(plot, "%s \n", commandsForGnuplot); //Send commands to gnuplot one by one.

    plot_destroy(plot);

    i32 y = 5;
    fVec2 v = fvec2(4,y);
    printf("%f\n", v.y);
    return 0;
}
