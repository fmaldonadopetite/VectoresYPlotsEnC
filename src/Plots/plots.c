#include "../AlgebraLineal/vectores.h"
#include <locale.h>
#include <time.h>
//Podría implementar una estructura PlotComponent, que incluyera x,y,label,color, estilo, y permitiera agregar flexibilidad a la entrada de plot_add, definiendo un método diferente plot_add_component(PlotComponent instancia);


#define MAXTITLE 100
#define MAXFILENAME 16

typedef struct nodo {
    char *label;
    struct nodo *siguiente;

} NodoColaLabels;
typedef struct {
    NodoColaLabels *principio, **pfinal;
    u32 largo;
} ColaLabels;

ColaLabels *colaLabels_create();
void colaLabels_destroy(ColaLabels *q);
void colaLabels_put(ColaLabels *q, char* label);
char *colaLabels_get(ColaLabels *q);
char *colaLabels_peek(ColaLabels *q);
i32 colaLabels_is_empty(ColaLabels *q);

typedef struct {
    char title[MAXTITLE];
    u32 nplots;
    FILE *temp_file;
    char temp_file_name[MAXFILENAME];
    ColaLabels *labels;
} Plot;
Plot plot_create(char *title);
void plot_destroy(Plot plot);
void plot_add(Plot *plot, Vector x, Vector y, char *label);
void plot_draw(Plot *plot);


#if defined CORRER
int main(void){
    Plot plot = plot_create("Esta es una prueba de gráfico");
    Vector x1 = vector_create_range(0, 50, 1);
    Vector y1 = vector_create_copy(x1);
    Vector x2 = vector_create_range(0, 100, 1);
    Vector y2 = vector_create_copy(x2);
    vector_multiply(y2,y2,y2);
    vector_dot_divide(y2,100);
    plot_add(&plot, x2,y2, "cuadrático");
    plot_add(&plot, x1,y1, "lineal");
    vector_map(y2, y2, cos);
    plot_add(&plot, x2,y2, "coseno cuadrático");
    plot_draw(&plot);
    
    vector_destroy(x1);
    vector_destroy(y1);
    x1 = vector_create_range(0, 100, 30);
    y1 = vector_create_copy(x1);
    vector_dot_divide(y1, 20);
    vector_map(y1, y1, exp);
    plot_add(&plot, x1,y1, "exponencial");
    plot_draw(&plot);


    plot_destroy(plot);
    vector_destroy(x1);
    vector_destroy(y1);
    vector_destroy(x2);
    vector_destroy(y2);
    return 0;
}
#endif

Plot plot_create(char *title) {
    char file_name[MAXFILENAME]; 
    snprintf(file_name, MAXFILENAME, "%d.txt", rand());
    FILE *temp_file  = fopen(file_name, "w+");
    //
    Plot plot = {
        .title = {0},
        .nplots = 0,
        .temp_file=temp_file,
        .labels=colaLabels_create(),
    };
    char *ptr1, *ptr2;
    ptr1 = plot.title;
    while((*ptr1++ = *title++));
    ptr1 = plot.temp_file_name;
    ptr2 = file_name;
    while((*ptr1++ = *ptr2++));
    return plot;
}
void plot_destroy(Plot plot){
    fclose(plot.temp_file);
    remove(plot.temp_file_name); 
    colaLabels_destroy(plot.labels);
}

void plot_draw(Plot *plot){
    FILE *plot_pipe = popen ("gnuplot-qt -persistent", "w");
    char *final_command = malloc(MAXTITLE + (MAXFILENAME + MAXTITLE +100)*plot->nplots +1);
    ColaLabels *new_labels = colaLabels_create();//para reciclar los labels y poder dibujar el plot más de una vez
    char *ptr, *ptr2;

    //settings previos (~MAXTITLE caracteres)
    char *settings1 = "set grid; set title \"";
    char *settings2 = "\" ;";
    char *title = plot->title;
    ptr = final_command;
    while( (*ptr++ = *settings1++) );
    ptr--;
    while( (*ptr++ = *title++) );
    ptr--;
    while( (*ptr++ = *settings2++) );
    ptr--;

    //plot como tal
    char *command_start = "plot ";
    ptr2 = command_start;
    while( (*ptr++ = *ptr2++) );
    ptr--;
    for (u32 i=0; i<plot->nplots; i++){
        //agregar "\'{plot.temp_file_name}\' using {(2*i+1)}:{(2*i+2)} title \'{label}\' with linespoint,;" <-  ~MAXFILENAME + 100 chars
        char *file_name = plot->temp_file_name;
        i32 columna1, columna2;
        columna1 = 2*i+1;
        columna2 = 2*i+2;
        char *label = colaLabels_get(plot->labels);
        colaLabels_put(new_labels, label);

        char nuevaLinea[MAXFILENAME + 100 + 1];
        snprintf(nuevaLinea, MAXFILENAME + 100 + 1, "\'%s\' using %d:%d title \'%s\' with lines,", file_name, columna1, columna2, label );
        ptr2 = nuevaLinea;
        while( (*ptr++ = *ptr2++) );
        ptr--;

    }
    ptr--;//para borrar la última coma
    *ptr='\0';

    fprintf(plot_pipe, "%s \n", final_command); 
    pclose(plot_pipe);
    free(final_command);
    colaLabels_destroy(plot->labels);
    plot->labels = new_labels;
}

void plot_add(Plot *plot, Vector x, Vector y, char *label){
    /*
     * Convenciones: 
     *      -toda adición al plot vendrá en la forma de dos vectores de igual largo
     *      -no toda adición tiene por qué ser del mismo largo, pero aunque sea con espacios toda columna es del mismo largo
     */
    assert((x.size == y.size) && "vectores deben ser de igual tamaño");
    assert((plot->nplots <= 3) && "número máximo de plots alcanzados");//para hacer más hay que arreglar la conversión de columnas a char en plot_draw
    FILE *fp = plot->temp_file;
    char *ptr1;
    char *ptr2;

    //primer plot
    if (plot->nplots == 0){
        for(u32 i=0; i<x.size; i++){
            fprintf(fp,"%f,\t%f\n",x.v[i],y.v[i]);
        }
    } else { //plot siguientes
        //número de líneas
        fseek(fp, 0, SEEK_SET);
        u32 nlineas=0;
        char c;
        while( (c=getc(fp))>0) if (c=='\n') nlineas++;

        //alargamos el archivo al porte de los nuevos vectores de ser necesario
        //obs:el indicador ya está al final del archivo.
        while(nlineas < x.size){
            for(u32 i=0; i<(plot->nplots*2-1); i++){
                fputc(',', fp); fputc('\t', fp);
            }
            fputc('\n', fp);
            nlineas++;
        }
        fflush(plot->temp_file);

        //creamos una copia del archivo
        char command[110] = "cp ";
        char *copia = "caca.txt";
        ptr1 = command+3;
        ptr2 = plot->temp_file_name;
        while( (*ptr1++=*ptr2++) );
        ptr1--; *ptr1++=' ';
        ptr2 = copia;
        while( (*ptr1++=*ptr2++) );
        system(command);
        FILE *copyp  = fopen("caca.txt", "r");
        remove("caca.txt");

        //copiamos cada línea en la copia a file_temp agregando los nuevos vectores
        fseek(fp, 0, SEEK_SET);
        for(u32 i=0; i<nlineas; i++){
            char a =  fgetc(copyp);
            while(a!='\n'){
                fputc(a, fp);
                a =  fgetc(copyp);
            }
            fputc(',', fp); fputc('\t', fp);
            if (i<x.size){
                fprintf(fp,"%f,\t%f\n",x.v[i],y.v[i]);
            } else {
                fputc(',', fp); fputc('\t', fp); fputc('\n', fp);
            }
        }
        fclose(copyp);
        //volvemos al inicio del archivo, y para cada línea, nos posicionamos
    }
    fflush(plot->temp_file);
    plot->nplots+=1;
    char *newLabel = malloc(MAXTITLE+1);
    char *p1 = newLabel;
    char *p2 = label;

    while( (*p1++=*p2++) );
    
    colaLabels_put(plot->labels, newLabel);
}





ColaLabels *colaLabels_create(){
    ColaLabels *q = malloc(sizeof(ColaLabels));
    q->principio = NULL;
    q->pfinal = &q->principio;
    q->largo = 0;
    return q;
}
void colaLabels_destroy(ColaLabels *q){
    NodoColaLabels *nodo = q->principio;
    while(nodo){
        NodoColaLabels *siguiente = nodo->siguiente;
        free(nodo);
        nodo = siguiente;
    }
    free(q);
    q =NULL;
}

void colaLabels_put(ColaLabels *q, char* label){
    //Se crea el nodo
    NodoColaLabels *nodo = malloc(sizeof(NodoColaLabels));
    if(nodo){
        nodo->label = label;
        nodo->siguiente = NULL;
    }
    *q->pfinal = nodo;
    q->pfinal = &nodo->siguiente;
    q->largo++;
}
char *colaLabels_get(ColaLabels *q){
    if(!q->principio) return NULL;
    char *label = q->principio->label;
    NodoColaLabels *siguiente = q->principio->siguiente;
    if(!siguiente){
        free(q->principio);
        q->principio = NULL;
        q->pfinal = &q->principio;
    } else{
        free(q->principio);
        q->principio = siguiente;
    }
    q->largo--;

    return label;
}
char *colaLabels_peek(ColaLabels *q){
    if(!q->principio) return NULL;
    return q->principio->label;
}

i32 colaLabels_is_empty(ColaLabels *q){
    return q->principio==NULL;
}
