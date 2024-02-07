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
## Precompilador
* **#include:** Insert text from another source file.
* #define:     Add a preprocessor macro definition.
* #undef:      Remove a preprocessor macro definition.
* #ifdef :     Conditionally include some text if the macro is defined.
* #ifndef :    Conditionally include some text if the macro is not defined.
* #if:         Conditionally include some text based on the value of a conditional expression.
* #else :      Conditionally include some text when the value of #if, #ifdef, #ifndef, or #elif failed.
* #elif:       Equivalent to #else #if in a single directive.
* #endif:      Terminate conditional text.
* #error:      Produce a compile-time error with the designated message.
* #pragma:     Specify implementation-dependent information to the compiler.


