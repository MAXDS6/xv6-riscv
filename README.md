Tarea 2: Lottery Scheduling en XV6
Grupo: J
Integrantes: Maximiliano Diaz, Francisco Delgado
Fecha: 20 de Octubre 2025
Descripción
Cambiamos el scheduler de XV6 de Round-Robin a Lottery Scheduling. Los procesos ahora tienen "tickets" y mientras más tickets tengan, más probabilidad tienen de ejecutarse.
Funcionamiento
El scheduler hace una lotería cada vez que elige un proceso:

Suma todos los tickets de los procesos RUNNABLE
Genera un número random entre 1 y ese total
Va acumulando tickets hasta llegar al número ganador
Ejecuta el proceso donde llegó al número

Ejemplo: Si tengo procesos con 10, 30 y 60 tickets (total=100) y sale el número 45, gana el tercero porque 10+30+5=45.
Archivos modificados
kernel/proc.h: Agregué int tickets y int run_slices a struct proc
kernel/proc.c:

En allocproc() inicialicé los campos nuevos (100 tickets por defecto)
Función settickets() para cambiar tickets (mínimo 1)
Función rand() para generar números aleatorios (usé LCG)
Reescribí scheduler() completo para implementar la lotería

kernel/sysproc.c: Agregué sys_settickets() como wrapper de la syscall
kernel/syscall.h y syscall.c: Registré la syscall con número 22
kernel/defs.h: Declaré settickets() y rand()
user/user.h y usys.pl: Expuse settickets() al espacio de usuario
user/demo.c: Programa de prueba con 10 procesos (tickets: 50, 100, 150... 500)
Makefile: Agregué demo a UPROGS
Problemas encontrados
1. Kernel panic con locks
Mi scheduler hacía break cuando encontraba el ganador, pero dejaba locks sin liberar. Solución: usé una variable found en vez de break para seguir liberando todos los locks.
2. argint() es void
En mi versión no retorna valor, así que no pude hacer if(argint(...) < 0). Moví la validación directamente a settickets().
3. División por cero
Si no hay procesos RUNNABLE, agregué un if(total_tickets == 0) continue;
4. Errores de compilación
Olvidé agregar int antes de settickets, usé cpu_slices en vez de run_slices, entre otros. Los fui corrigiendo siguiendo los mensajes del compilador.
Cómo probar
bashmake qemu
# Dentro de XV6:
demo
# Después presiona Ctrl+P para ver estadísticas
Los procesos con más tickets deberían tener más run_slices.
Problemas del Lottery Scheduling

No es determinístico: Un proceso puede tener mala suerte y no ejecutarse por un rato
Overhead O(n): Recorre todos los procesos dos veces vs O(1) de Round-Robin
No considera I/O: Trata igual a procesos I/O-bound y CPU-bound
Calidad del random: Un mal generador puede dar distribución injusta
No sirve para tiempo real: Todo es probabilístico, no hay garantías

Conclusión
Lottery Scheduling es simple de implementar pero tiene limitaciones. Lo más difícil fue manejar bien los locks en el scheduler. Para sistemas normales Round-Robin probablemente es mejor, pero esto sirve cuando quieres control proporcional simple sobre CPU
