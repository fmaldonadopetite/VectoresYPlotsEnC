#include "vectores.h"
//Obs, los vectores float no comienzan con mayúscula

#if defined CORRER
u32 suma(u32 x, u32 y){
     return x+y;
 }


int main(void){
    //prueva Vector, Vector
    iVector ivec = ivector_create_range(0, 6, 1);
    Vector vec = vector_create(ivec.size);
    ivector_to_vector(vec, ivec);
    vector_dot_add(vec,5);
    //vector_add(fvec, fvec, fvec);
    vector_dot_divide(vec, 7);
    vector_map(vec, vec, exp);
    for (size_t i=0; i<ivec.size; i++){
        printf("%f", vec.v[i]);
        printf("\n");
    }
    ivector_dot_multiply(ivec, 0);
    ivector_dot_add(ivec, 1);
    printf("%d\n", ivector_fold(ivec, suma));
    ivector_destroy(ivec);
    vector_destroy(vec);

    //prueba Vec2, fVec2
    Vec2 v = vec2(4,10);
    fVec2 fv2 = fvec2(vec2_norm(v),  vec2_norm(v));
    printf("(%f, %f)\n", fv2.x, fv2.y);
    vec2_dot_multiply(v, 5);
    fv2 = fvec2(vec2_norm(v),  vec2_norm(v));
    printf("(%f, %f)\n", fv2.x, fv2.y);
    return 0;
}
#endif


/*
  ____                _                   _                      
 / ___|___  _ __  ___| |_ _ __ _   _  ___| |_ ___  _ __ ___  ___ 
| |   / _ \| '_ \/ __| __| '__| | | |/ __| __/ _ \| '__/ _ \/ __|
| |__| (_) | | | \__ \ |_| |  | |_| | (__| || (_) | | |  __/\__ \
 \____\___/|_| |_|___/\__|_|   \__,_|\___|\__\___/|_|  \___||___/
 */

Vec2 vec2(u32 x,u32 y){
    Vec2 vec ={x,y};
    return vec;
}

fVec2 fvec2(double x,double y){
    fVec2 vec ={x,y};
    return vec;
}

iVector ivector_create(u32 size){
    i32 *v = calloc(size, sizeof(i32));
    iVector vector = {0};
    if(v)  {
        vector.size = size;
        vector.v = v;
    } 

    return vector;
}

iVector ivector_create_copy(iVector vector){
    iVector new_vector = ivector_create(vector.size);
    ivector_add(new_vector, vector, new_vector);
    return new_vector;
}

iVector ivector_create_range(i32 start, i32 end, i32 step){
    //start + size*step = end
    iVector vector = {0};

    if (end<=start) return vector;

    u32 size = abs(end/step);
    if (end%step != 0) size +=1;

    i32 *v = calloc(size, sizeof(i32));
    if(v)  {
        vector.size = size;
        v[0]=start;
        for (u32 i=1; i<size; i++) v[i] = v[i-1] + step;
        vector.v = v;
    } 
    return vector;
}

void ivector_destroy(iVector vector){
    free(vector.v);
}

Vector vector_create(u32 size){

    double *v = calloc(size, sizeof(double));
    Vector vector = {0};
    if(v)  {
        vector.size = size;
        vector.v = v;
    } 

    return vector;
}

Vector vector_create_copy(Vector vector){
    Vector new_vector = vector_create(vector.size);
    vector_add(new_vector, vector, new_vector);
    return new_vector;
}

Vector vector_create_range(double start, double end, double step){
    //start + size*step = end
    Vector vector = {0};

    if (end<=start) return vector;

    u32 size = trunc((fabs(end/step)));
    if (end/step != trunc(end/step)) size +=1;

    double *v = calloc(size, sizeof(double));
    if(v)  {
        vector.size = size;
        v[0]=start;
        for (u32 i=1; i<size; i++) v[i] = v[i-1] + step;
        vector.v = v;
    } 
    printf("%d\n", size);
    return vector;
}

void vector_destroy(Vector vector){
    free(vector.v);
}


/*
  ___                            _                       
 / _ \ _ __   ___ _ __ __ _  ___(_) ___  _ __   ___  ___ 
| | | | '_ \ / _ \ '__/ _` |/ __| |/ _ \| '_ \ / _ \/ __|
| |_| | |_) |  __/ | | (_| | (__| | (_) | | | |  __/\__ \
 \___/| .__/ \___|_|  \__,_|\___|_|\___/|_| |_|\___||___/
      |_|                                                
      */
//vec2
Vec2 vec2_dot_add(Vec2 vector, i32 num){
    vector.x += num;
    vector.y += num;
    return vector;
}

Vec2 vec2_dot_divide(Vec2 vector, i32 num){
    vector.x /= num;
    vector.y /= num;
    return vector;
}

Vec2 vec2_dot_multiply(Vec2 vector, int num){
    vector.x *= num;
    vector.y *= num;
    return vector;
}

i32 vec2_inner_prod(Vec2 vector1, Vec2 vector2){
    return vector1.x * vector2.x + vector1.y * vector2.y;
}
Vec2 vec2_multiply( Vec2 vector1, Vec2 vector2){
    u32 x = vector1.x * vector2.x;
    u32 y = vector1.y * vector2.y;
    Vec2 v = {x,y};
    return v;
}

Vec2 vec2_add( Vec2 vector1, Vec2 vector2){
    u32 x = vector1.x - vector2.x;
    u32 y = vector1.y - vector2.y;
    Vec2 v = {x,y};
    return v;
}

double vec2_norm(Vec2 vector){
    double num = sqrt(vector.x * vector.x + vector.x * vector.x);
    return num;
}

Vec2 vec2_map( Vec2 vector, i32 (*func)(i32)){
    u32 x = func(vector.x);
    u32 y = func(vector.y);
    Vec2 v = {x,y};
    return v;
}

//fvec2
void fvec2_dot_add(fVec2 vector, u32 num){
    vector.x += num;
    vector.y += num;
}

void fvec2_dot_divide(fVec2 vector, u32 num){
    vector.x /= num;
    vector.y /= num;
}

void fvec2_dot_multiply(fVec2 vector, int num){
    vector.x *= num;
    vector.y *= num;
}

double fvec2_inner_prod(fVec2 vector1, Vec2 vector2){
    return vector1.x * vector2.x + vector1.y * vector2.y;
}
Vec2 fvec2_multiply( fVec2 vector1, fVec2 vector2){
    u32 x = vector1.x * vector2.x;
    u32 y = vector1.y * vector2.y;
    Vec2 v = {x,y};
    return v;
}

Vec2 fvec2_add( fVec2 vector1, fVec2 vector2){
    u32 x = vector1.x - vector2.x;
    u32 y = vector1.y - vector2.y;
    Vec2 v = {x,y};
    return v;
}

double fvec2_norm(fVec2 vector){
    double num = sqrt(vector.x * vector.x + vector.x * vector.x);
    return num;
}

fVec2 fvec2_map( fVec2 vector, i32 (*func)(i32)){
    double x = func(vector.x);
    double y = func(vector.y);
    fVec2 v = {x,y};
    return v;
}

//ivector
u32 ivector_len(iVector vector){
    return vector.size;
}
void ivector_dot_add(iVector vector, u32 num){
    for(size_t i=0; i<vector.size; i++ ){
        vector.v[i] += num;
    }
}

void ivector_dot_divide(iVector vector, u32 num){
    for(size_t i=0; i<vector.size; i++ ){
        vector.v[i] /= num;
    }
}

void ivector_dot_multiply(iVector vector, int num){
    for(size_t i=0; i<vector.size; i++ ){
        vector.v[i] *= num;
    }
}

i32 ivector_inner_prod(iVector vector1, iVector vector2){
    assert((vector1.size == vector2.size) && "vectores deben ser de igual tamaño");
    i32 result = 0;
    for(size_t i=0; i<vector1.size; i++ ){
        result += vector1.v[i] * vector2.v[i];
    }
    return result;
}
void ivector_multiply(iVector result, iVector vector1, iVector vector2){
    assert((result.size == vector1.size ) && (vector1.size == vector2.size) && "vectores deben ser de igual tamaño");
    for(size_t i=0; i<vector1.size; i++ ){
        result.v[i] = vector1.v[i] * vector2.v[i];
    }
}

void ivector_add(iVector result, iVector vector1, iVector vector2){
    assert((result.size == vector1.size ) && (vector1.size == vector2.size) && "vectores deben ser de igual tamaño");
    for(size_t i=0; i<vector1.size; i++ ){
        result.v[i] = vector1.v[i] + vector2.v[i];
    }
}

double ivector_norm(iVector vector){
    u32 result=0;
    for(size_t i=0; i<vector.size; i++ ){
        result += vector.v[i]*vector.v[i]; 
    }
    return sqrt(result);
}

void ivector_map(iVector result, iVector vector, i32 (*func)(i32)){
    for(size_t i=0; i<vector.size; i++ ){
        result.v[i] = func(vector.v[i]);
    }
}

u32 ivector_fold(iVector vector, u32 (*func)(u32, u32)){
    u32 result =  vector.v[0];
    for(size_t i=1; i<vector.size; i++ ){
        result = func(vector.v[i], result);
    }
    return result;
}

void ivector_to_vector(Vector result, iVector vector){
    for(size_t i=0; i<vector.size; i++ ){
        result.v[i] = (double) vector.v[i];
    }
    
}

//vector
u32 vector_len(Vector vector){
    return vector.size;
}

void vector_dot_add(Vector vector, double num){
    for(size_t i=0; i<vector.size; i++ ){
        vector.v[i] += num;
    }
}

void vector_dot_divide(Vector vector, double num){
    for(size_t i=0; i<vector.size; i++ ){
        vector.v[i] /= num;
    }
}

void vector_dot_multiply(Vector vector, double num){
    for(size_t i=0; i<vector.size; i++ ){
        vector.v[i] *= num;
    }
}

double vector_inner_prod(Vector vector1, Vector vector2){
    assert((vector1.size == vector2.size) && "vectores deben ser de igual tamaño");
    double result = 0;
    for(size_t i=0; i<vector1.size; i++ ){
        result += vector1.v[i] * vector2.v[i];
    }
    return result;
}
void vector_multiply(Vector result, Vector vector1, Vector vector2){
    assert((result.size == vector1.size ) && (vector1.size == vector2.size) && "vectores deben ser de igual tamaño");
    for(size_t i=0; i<vector1.size; i++ ){
        result.v[i] = vector1.v[i] * vector2.v[i];
    }
}

void vector_add(Vector result, Vector vector1, Vector vector2){
    assert((result.size == vector1.size ) && (vector1.size == vector2.size) && "vectores deben ser de igual tamaño");
    for(size_t i=0; i<vector1.size; i++ ){
        result.v[i] = vector1.v[i] + vector2.v[i];
    }
}

double vector_norm(Vector vector){
    double result=0;
    for(size_t i=0; i<vector.size; i++ ){
        result += vector.v[i]*vector.v[i]; 
    }
    return sqrt(result);
}

void vector_map(Vector result, Vector vector, double (*func)(double)){
    for(size_t i=0; i<vector.size; i++ ){
        result.v[i] = func(vector.v[i]);
    }
}

double vector_fold(Vector vector, double (*func)(double, double)){
    double result =  vector.v[0];
    for(size_t i=1; i<vector.size; i++ ){
        result = func(vector.v[i], result);
    }
    return result;
}
