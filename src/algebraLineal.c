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
    float x;
    float y;
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

fVec2 fvec2(float x,float y){
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
fVector fvector_create(u32 size){

    float *v = calloc(size, sizeof(float));
    fVector vector = {0};
    if(v)  {
        vector.size = size;
        vector.v = v;
    } 

    return vector;
}

void vector_destroy(Vector vector){
    free(vector.v);
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
void vector_dot_add(Vector vector, int num){
    for(size_t i=0; i<vector.size; i++ ){
        vector.v[i] += num;
    }
}

void vector_dot_divide(Vector vector, int num){
    for(size_t i=0; i<vector.size; i++ ){
        vector.v[i] /= num;
    }
}

void vector_dot_multiply(Vector vector, int num){
    for(size_t i=0; i<vector.size; i++ ){
        vector.v[i] *= num;
    }
}

u32 vector_inner_prod(Vector vector1, Vector vector2){
    assert((vector1.size == vector2.size) && "message");
    u32 result = 0;
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


int main(void){
    Vector vec = vector_create(5);
    vector_dot_add(vec,5);
    vector_add(vec, vec, vec);
    vector_dot_divide(vec, 7);
    for (size_t i=0; i<vec.size; i++){
        printf("%d", vec.v[i]);
        printf("\n");
    }
    return 0;
}
