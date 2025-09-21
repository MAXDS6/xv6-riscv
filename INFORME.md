# Informe Tarea 1 

**Nombre:** Maximiliano Diaz y Francisco Delgado


## Que se hizo en este trabajo

Agregué dos syscalls nuevas en xv6:
- `getppid()`: retorna el PID del proceso padre
- `getancestor(int n)`: retorna el PID del ancestro n-ésimo

### Archivos modificados para esta tarea N1:
- `kernel/syscall.h` - números de syscall (#21 y #22)
- `kernel/syscall.c` - declaraciones y tabla
- `kernel/sysproc.c` - implementación
- `user/user.h` - declaraciones para usuario
- `user/usys.pl` - stubs
- `Makefile` - programa de prueba yosoytupadre

### Códigos principales

Para `getppid()` La función obtiene el proceso actual usando myproc(), que retorna un puntero a la estructura del proceso. Cada proceso en xv6 tiene un campo parent que apunta al proceso padre.

Para `getancestor()` uso un loop que sube n niveles por la cadena de procesos padre. Si n=0 retorno mi PID, si n=1 mi padre, etc. Retorno -1 si no hay más ancestros.

## Programa de prueba pedido 

Hicimos `yosoytupadre.c` que muestra:
```
Mi PID: 3
PID de mi padre: 2
Ancestro 0: 3
Ancestro 1: 2
Ancestro 2: 1
Ancestro 3: -1
```

Esto confirma la jerarquía init(1) → shell(2) → programa(3), la cual es la que queremos comprobar que funciona de dicha manera

## Problemas que tuvimos a lo largo del trabajo

1. `argint()` en xv6 es void, no retorna error como pensé inicialmente.
2. Faltó un ; en entry("getancrestor") en `usys.pl` lo cual me generó el mismo problemas varias veces y tuve que revisar todos los archivos de forma manual. 
3. Tardamos en entender como se conectan todos los archivos del sistema de syscalls ya que nuestro entendimiento sobre c no es tan alto y tuvimos que investigar bastante para entender bien como funciona todo. 
4. Tuvimos varios errores de identación y de escritar de comandos en WSL al momento de hacer los trabajos.

## Compilación de todo lo modificado dentro del repo

```bash
make clean
make qemu
# En xv6:
yosoytupadre


Ambas syscalls funcionan correctamente.

