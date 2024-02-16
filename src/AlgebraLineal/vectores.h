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
} iVector;

typedef struct {
    u32 size;
    double *v;
} Vector;

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

iVector ivector_create(u32 size);
iVector ivector_create_range(i32 start, i32 end, i32 step);
iVector ivector_create_copy(iVector vector);
void ivector_destroy(iVector vector);//lalalal

Vector vector_create(u32 size);
Vector vector_create_range(double start, double end, double step);
Vector vector_create_copy(Vector vector);
void vector_destroy(Vector vector);


//operaciones
Vec2 vec2_dot_add(Vec2 vector, i32 num);
Vec2 vec2_dot_divide(Vec2 vector, i32 num);
Vec2 vec2_dot_multiply(Vec2 vector, int num);
i32 vec2_inner_prod(Vec2 vector1, Vec2 vector2);
Vec2 vec2_multiply( Vec2 vector1, Vec2 vector2);
Vec2 vect2_add( Vec2 vector1, Vec2 vector2);
double vec2_norm(Vec2 vector);
Vec2 vec2_map( Vec2 vector, i32 (*func)(i32));

u32 ivector_len(iVector vector);
void ivector_dot_add(iVector vector, u32 num);
void ivector_dot_divide(iVector vector, u32 num);
void ivector_dot_multiply(iVector vector, int num);
i32 ivector_inner_prod(iVector vector1, iVector vector2);
void ivector_multiply(iVector result, iVector vector1, iVector vector2);
void ivector_add(iVector result, iVector vector1, iVector vector2);
double ivector_norm(iVector vector);
void ivector_map(iVector result, iVector vector, i32 (*func)(i32));
u32 ivector_fold(iVector vector, u32 (*func)(u32, u32));
void ivector_to_vector(Vector result, iVector vector);

u32 vector_len(Vector vector);
void vector_dot_add(Vector vector, double num);
void vector_dot_divide(Vector vector, double num);
void vector_dot_multiply(Vector vector, double num);
double vector_inner_prod(Vector vector1, Vector vector2);
void vector_multiply(Vector result, Vector vector1, Vector vector2);
void vector_add(Vector result, Vector vector1, Vector vector2);
double vector_norm(Vector vector);
void vector_map(Vector result, Vector vector, double (*func)(double));
double vector_fold(Vector vector, double (*func)(double, double));

#endif
