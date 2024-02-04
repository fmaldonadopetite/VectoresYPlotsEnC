#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>

typedef int8_t i8;      //char
typedef uint8_t u8;
typedef int16_t i16;    //short
typedef uint16_t u16;
typedef int32_t i32;    //int, long (size of pointer),
typedef uint32_t u32;   //size_t
typedef int64_t i64;    //long long
typedef uint64_t u64;   //pointer


/*
 ____        __ _       _      _                       
|  _ \  ___ / _(_)_ __ (_) ___(_) ___  _ __   ___  ___ 
| | | |/ _ \ |_| | '_ \| |/ __| |/ _ \| '_ \ / _ \/ __|
| |_| |  __/  _| | | | | | (__| | (_) | | | |  __/\__ \
|____/ \___|_| |_|_| |_|_|\___|_|\___/|_| |_|\___||___/
 */
                                                       
typedef struct {
    double x;
    double y;
} fVec2;

typedef struct {
    i32 x;
    i32 y;
} Vec2;

typedef struct {
    u32 size;
    i32 *v;
} Vector;

typedef struct {
    u32 size;
    float *v;
} fVector;

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

Vector vector_create(u32 size){
    i32 *v = calloc(size, sizeof(i32));
    Vector vector = {0};
    if(v)  {
        vector.size = size;
        vector.v = v;
    } 

    return vector;
}

Vector vector_create_range(i32 start, i32 end, i32 step){
    //start + size*step = end
    Vector vector = {0};

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

void vector_destroy(Vector vector){
    free(vector.v);
}

fVector fvector_create(u32 size){

    float *v = calloc(size, sizeof(float));
    fVector vector = {0};
    if(v)  {
        vector.size = size;
        vector.v = v;
    } 

    return vector;
}

fVector fvector_create_range(float start, float end, float step){
    //start + size*step = end
    fVector vector = {0};

    if (end<=start) return vector;

    u32 size = trunc((fabs(end/step)));
    if (end/step != trunc(end/step)) size +=1;

    float *v = calloc(size, sizeof(float));
    if(v)  {
        vector.size = size;
        v[0]=start;
        for (u32 i=1; i<size; i++) v[i] = v[i-1] + step;
        vector.v = v;
    } 
    printf("%d\n", size);
    return vector;
}

void fvector_destroy(fVector vector){
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
void vec2_dot_add(Vec2 vector, u32 num){
    vector.x += num;
    vector.y += num;
}

void vec2_dot_divide(Vec2 vector, u32 num){
    vector.x /= num;
    vector.y /= num;
}

void vec2_dot_multiply(Vec2 vector, int num){
    vector.x *= num;
    vector.y *= num;
}

i32 vec2_inner_prod(Vec2 vector1, Vec2 vector2){
    return vector1.x * vector2.x + vector1.y * vector2.y;
}
void vector_multiply(Vector result, Vector vector1, Vector vector2){
    assert((result.size == vector1.size ) && (vector1.size == vector2.size) && "message");
    for(size_t i=0; i<vector1.size; i++ ){
        result.v[i] = vector1.v[i] * vector2.v[i];
    }
}

void vector_add(Vector result, Vector vector1, Vector vector2){
    assert((result.size == vector1.size ) && (vector1.size == vector2.size) && "message");
    for(size_t i=0; i<vector1.size; i++ ){
        result.v[i] = vector1.v[i] + vector2.v[i];
    }
}

double vector_norm(Vector vector){
    u32 result=0;
    for(size_t i=0; i<vector.size; i++ ){
        result += vector.v[i]*vector.v[i]; 
    }
    return sqrt(result);
}

void vector_map(Vector result, Vector vector, i32 (*func)(i32)){
    for(size_t i=0; i<vector.size; i++ ){
        result.v[i] = func(vector.v[i]);
    }
}
void vector_dot_add(Vector vector, u32 num){
    for(size_t i=0; i<vector.size; i++ ){
        vector.v[i] += num;
    }
}

void vector_dot_divide(Vector vector, u32 num){
    for(size_t i=0; i<vector.size; i++ ){
        vector.v[i] /= num;
    }
}

void vector_dot_multiply(Vector vector, int num){
    for(size_t i=0; i<vector.size; i++ ){
        vector.v[i] *= num;
    }
}

i32 vector_inner_prod(Vector vector1, Vector vector2){
    assert((vector1.size == vector2.size) && "message");
    i32 result = 0;
    for(size_t i=0; i<vector1.size; i++ ){
        result += vector1.v[i] * vector2.v[i];
    }
    return result;
}
void vector_multiply(Vector result, Vector vector1, Vector vector2){
    assert((result.size == vector1.size ) && (vector1.size == vector2.size) && "message");
    for(size_t i=0; i<vector1.size; i++ ){
        result.v[i] = vector1.v[i] * vector2.v[i];
    }
}

void vector_add(Vector result, Vector vector1, Vector vector2){
    assert((result.size == vector1.size ) && (vector1.size == vector2.size) && "message");
    for(size_t i=0; i<vector1.size; i++ ){
        result.v[i] = vector1.v[i] + vector2.v[i];
    }
}

double vector_norm(Vector vector){
    u32 result=0;
    for(size_t i=0; i<vector.size; i++ ){
        result += vector.v[i]*vector.v[i]; 
    }
    return sqrt(result);
}

void vector_map(Vector result, Vector vector, i32 (*func)(i32)){
    for(size_t i=0; i<vector.size; i++ ){
        result.v[i] = func(vector.v[i]);
    }
}

void vector_to_fvector(fVector result, Vector vector){
    for(size_t i=0; i<vector.size; i++ ){
        result.v[i] = (float) vector.v[i];
    }
    
}

void fvector_dot_add(fVector vector, float num){
    for(size_t i=0; i<vector.size; i++ ){
        vector.v[i] += num;
    }
}

void fvector_dot_divide(fVector vector, float num){
    for(size_t i=0; i<vector.size; i++ ){
        vector.v[i] /= num;
    }
}

void fvector_dot_multiply(fVector vector, float num){
    for(size_t i=0; i<vector.size; i++ ){
        vector.v[i] *= num;
    }
}

float fvector_inner_prod(fVector vector1, fVector vector2){
    assert((vector1.size == vector2.size) && "message");
    float result = 0;
    for(size_t i=0; i<vector1.size; i++ ){
        result += vector1.v[i] * vector2.v[i];
    }
    return result;
}
void fvector_multiply(fVector result, fVector vector1, fVector vector2){
    assert((result.size == vector1.size ) && (vector1.size == vector2.size) && "message");
    for(size_t i=0; i<vector1.size; i++ ){
        result.v[i] = vector1.v[i] * vector2.v[i];
    }
}

void fvector_add(fVector result, fVector vector1, fVector vector2){
    assert((result.size == vector1.size ) && (vector1.size == vector2.size) && "message");
    for(size_t i=0; i<vector1.size; i++ ){
        result.v[i] = vector1.v[i] + vector2.v[i];
    }
}

double fvector_norm(fVector vector){
    float result=0;
    for(size_t i=0; i<vector.size; i++ ){
        result += vector.v[i]*vector.v[i]; 
    }
    return sqrt(result);
}

void fvector_map(fVector result, fVector vector, float (*func)(float)){
    for(size_t i=0; i<vector.size; i++ ){
        result.v[i] = func(vector.v[i]);
    }
}

i32 suma4(i32 x){ 
    return x*25;
}


float euler(float x){ 
    return exp(x);
}


int main(void){
    Vector vec = vector_create_range(0, 6, 1);
    fVector fvec = {vec.size, (float *) vec.v};
    vector_to_fvector(fvec, vec);
    fvector_dot_add(fvec,5);
    //fvector_add(fvec, fvec, fvec);
    fvector_dot_divide(fvec, 7);
    fvector_map(fvec, fvec, &euler);
    for (size_t i=0; i<vec.size; i++){
        printf("%f", fvec.v[i]);
        printf("\n");
    }
    vector_destroy(vec);
    return 0;
}
