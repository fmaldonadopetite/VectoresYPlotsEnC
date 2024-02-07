#ifndef VECTORES_H_
#define VECTORES_H_

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
 _____ _                 
|_   _(_)_ __   ___  ___ 
  | | | | '_ \ / _ \/ __|
  | | | | |_) | (_) \__ \
  |_| |_| .__/ \___/|___/
        |_|              
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
    double *v;
} fVector;

/*
 _____                 _                       
|  ___|   _ _ __   ___(_) ___  _ __   ___  ___ 
| |_ | | | | '_ \ / __| |/ _ \| '_ \ / _ \/ __|
|  _|| |_| | | | | (__| | (_) | | | |  __/\__ \
|_|   \__,_|_| |_|\___|_|\___/|_| |_|\___||___/
*/
                                              
                                                                 

//constructores
Vec2 vec2(u32 x,u32 y);
fVec2 fvec2(double x,double y);

Vector vector_create(u32 size);
Vector vector_create_range(i32 start, i32 end, i32 step);
void vector_destroy(Vector vector);

fVector fvector_create(u32 size);
fVector fvector_create_range(double start, double end, double step);
void fvector_destroy(fVector vector);


//operaciones
void vec2_dot_add(Vec2 vector, u32 num);
void vec2_dot_divide(Vec2 vector, u32 num);
void vec2_dot_multiply(Vec2 vector, int num);
i32 vec2_inner_prod(Vec2 vector1, Vec2 vector2);
Vec2 vec2_multiply( Vec2 vector1, Vec2 vector2);
Vec2 vect2_add( Vec2 vector1, Vec2 vector2);
double vec2_norm(Vec2 vector);
Vec2 vec2_map( Vec2 vector, i32 (*func)(i32));

void vector_dot_add(Vector vector, u32 num);
void vector_dot_divide(Vector vector, u32 num);
void vector_dot_multiply(Vector vector, int num);
i32 vector_inner_prod(Vector vector1, Vector vector2);
void vector_multiply(Vector result, Vector vector1, Vector vector2);
void vector_add(Vector result, Vector vector1, Vector vector2);
double vector_norm(Vector vector);
void vector_map(Vector result, Vector vector, i32 (*func)(i32));
u32 vector_fold(Vector vector, u32 (*func)(u32, u32));
void vector_to_fvector(fVector result, Vector vector);

void fvector_dot_add(fVector vector, double num);
void fvector_dot_divide(fVector vector, double num);
void fvector_dot_multiply(fVector vector, double num);
double fvector_inner_prod(fVector vector1, fVector vector2);
void fvector_multiply(fVector result, fVector vector1, fVector vector2);
void fvector_add(fVector result, fVector vector1, fVector vector2);
double fvector_norm(fVector vector);
void fvector_map(fVector result, fVector vector, double (*func)(double));
double fvector_fold(fVector vector, double (*func)(double, double));

#endif
