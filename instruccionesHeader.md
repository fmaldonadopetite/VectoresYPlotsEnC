https://www.youtube.com/watch?v=tOQZlD-0Scc&t=113s

# Idea General
Al tratar de compilar un archivo con una función no declarada ni definida, se obtienen dos errores, primero en tiempo de compilación
(se obtiene sólo un warning por "explicit declaration" confiando en que el linker la encuentre), y luego en tiempo de enlazamiento, 
directamente un error "undefined reference to `funcion`" pues no sabe a dónde enlazar el objeto para obtener la función.j

Si la función no definida está en una librería que podemos enlazar, es esperable que venga con un 
header file, este header contiene información legible para nosotros de la función (como un api o documentación)
pero principalmente entrega la declaración de la función, para que el código sepa cómo funciona (info de tipos
y uso de memoria) en la fase de compilación, por lo que incluyendo este header, nos libramos del primer warning.
Y enlazando la librería con las flags de compilación, le permitimos al linker enlazar el objeto a compilar con el 
objeto librería y así construir el ejecutable sin errores.
Luego añadiendo la librería al LD_LIBRARY_PATH, le permitimos al loader encontrar la librería en runtime y el código corre
sin problemas.

Análogamente al crear un programa en múltiples archivos, el header entrega información de las distintas funciones distribuidas
en los archivos, así como de los tipos, estructuras y enums, a cada uno de los source files, para poder compilar y enlazar los 
distintos objetos asociados.

# Cómo Funcionan Realmente
## Preprocesador
Para comprender los archivos header, necesitamos tener nociones básicas del funcionamiento
del preprocesador.

El preprocesador es un procesador de macros simples que procesa el texto fuente de un 
programa C antes de que el compilador lo lea. Se controla vía directivas de una línea
y transforma el texto fuente original interpretando las macros para añadir, borrar o
sustituir texto basándose en las directivas, sin conocimiento de sintáxis de C, ni de tipos
ni de nada. El código resultante debe ser código de C válido.

Directivas básicas del preprocesador:
* **#include:**    Insert text from another source file.
* **#define:**     Add a preprocessor macro definition.
* **#undef:**      Remove a preprocessor macro definition.
* **#ifdef:**      Conditionally include some text if the macro is defined.
* **#ifndef:**     Conditionally include some text if the macro is not defined.
* **#if:**         Conditionally include some text based on the value of a conditional expression.
* **#else :**      Conditionally include some text when the value of #if, #ifdef, #ifndef, or #elif failed.
* **#elif:**       Equivalent to #else #if in a single directive.
* **#endif:**      Terminate conditional text.
* **#error:**      Produce a compile-time error with the designated message.
* **#pragma:**     Specify implementation-dependent information to the compiler.

## Incluir Header Files
Al utilizar la directiva `#include`, el archivo referenciado se copia completo en el código
fuente dónde se le referencia. 
Obs: `#include <file>` busca el archivo en los directorios predefinidos de headers del sistema
     `include "file"` busca el archivo localmente.

## Escribir Header Files
La directiva `#define <name> <literal>` define una macro. Es distántemente similar a una variable,
pero en verdad sólo reemplaza tontamente de forma textual el nombre de la macro por el literal entregado,
allí dónde aparezca en el código fuente.
Si no se le entrega texto, la macro no es reemplazada por nada, pero el procesador sabe de su existencia.
Esto nos sirve ayuda a entender las guardas:

### Guardas
Al escribir un archivo someHeaderFile.c, es lo usual que su contenido esté en el siguiente formato:
```C
#ifndef _SOME_HEADER_FILE_H_
#define _SOME_HEADER_FILE_H_

// contenido del header
..
...
...
#endif
```
Que como ya hemos visto, lo que hace es que el texto dentro del #ifndef #endif no se
copia  si está definida la macro _SOME_HEADER_FILE_H_. En caso de que no esté definida,
se define y se copia el contenido del header al código fuente en que se incluya.
Esto evita que al incluir headers que incluyen headers se acabe copiando una y otra
vez el mismo código al código fuente.
Para esto basta usar cualquier nombre de macro que se use exclusivamente para este propósito,
pero es estándar utilizar el nombre de la librería en mayúsculas y separada por guiones bajos.

### Contenido
* Los archivos header permiten evitar el desorden y abultamiento de contener todas las
declaraciones de funciones y tipos personalizados en el código fuente.
* Permiten a un código fuente tener la información acerca de funciones y tipos
que son llamados desde otros códigos fuentes en la compilación.
* A través de archivos header podemos centralizar todos los archivos header de la librerías
estándar de C y escritos por nosotros, que necesitemos en los distintos archivos fuentes
que compilemos a nuestro progarama final.
*Los archivos header sirven para documentar el funcionamiento de nuestro código fuente,
conteniendo la información de las funciones que define.

SÍ va en un archivo header:
1. Declaraciones de funciones.
2. Definiciones de tipos personalizados (enums y structs).
3. Directivas de preprocesador como #define e #include.

NO va en un archivo header:
1. Nada que aloje memoria, como declaraciones de variables y constantes.
2. Definiciones de funciones.

    #### ¿Por qué no?
    Como vimos, un header es sólo un texto que el preprocesador copia en el archivo fuente,
    por lo que, en teoría, se podría incluir cualquier código de C en un archivo header.
    El problema es que el archivo header se escribe en cada uno de los códigos fuentes que 
    componen el programa, y al compilar los distintos objetos asociados, el compilador tratará
    de alojar la memoria cada vez usando el mismo nombre, no pudiendo determinar cuál memoria es 
    referenciada por el identificador de la variable en el caso de declarar una variable, o cuál es  la
    dirección correcta de la función, en caso de definir una función.

### Cuándo escribir header files
En general es necesario hacer un header cuando será referenciado por dos archivos fuentes. Pero
no hay problema con hacer un header para ordenar las declaraciones de un único archivo.
Lo importante es que cuando se crea un programa con varios códigos fuentes, hay que crear un header
centralizado para importar en todos. Puede haber un header de cada archivo fuente y llamarlos a todos
en el header principal.

Luego al compilar el programa se entregan como input todos los archivos fuente y objetos intermedios/librerías
necesarios. No se hace referencia a los header en el comando de compilación.
