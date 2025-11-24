Informe Tarea 3: Implementación de mrdprotect

Nombre: Grupoj

1. Descripción de la Tarea

El objetivo de esta tarea era modificar el kernel de xv6 para agregar dos nuevas llamadas al sistema (syscalls): mrdprotect y munrdprotect.

La idea principal es poder proteger una región de memoria para que sea "solo escritura" (Write-Only). Esto serviría para guardar datos sensibles (como claves) sin que nadie pueda leerlos después. Si un proceso intenta leer esa memoria, el sistema operativo debería detenerlo.

2. Implementación

Para lograr esto, tuve que tocar varios archivos del sistema. Como mi conocimiento de C es básico, traté de guiarme por cómo estaban hechas las otras funciones del sistema.

Pasos principales:

Syscalls: Registré las nuevas funciones en syscall.h, syscall.c y usys.pl para que el usuario pudiera llamarlas.

kernel/sysproc.c: Aquí implementé las funciones que reciben los argumentos desde el usuario (addr y len).

kernel/vm.c: Aquí hice la lógica real. Creé una función auxiliar que recorre las páginas de memoria usando walk().

Para mrdprotect: Apago el bit de lectura usando operaciones binarias (pte &= ~PTE_R).

Para munrdprotect: Vuelvo a encender el bit (pte |= PTE_R).

3. Dificultades y Errores Encontrados

Esta parte fue la que más me costó. Tuve varios errores de compilación y de ejecución que tuve que ir solucionando:

Problemas con C (void value not ignored):
En sysproc.c, intenté verificar si argaddr devolvía error poniendo un if. El compilador me tiró un error porque no me di cuenta de que en esta versión de xv6 esas funciones son void (no devuelven nada). Me costó darme cuenta, pero al final vi que tenía que llamarlas directo sin el if.

Error en el Makefile:
Cuando agregué mi programa de prueba al Makefile, el compilador me decía recipe commences before first target. Resulta que dejé una barra invertida (\) al final de la última línea y eso rompía todo.

Git:
Tuve varios problemas para subir el código. Primero intenté subirlo al repo del MIT en vez del mío (error 403), y luego me equivoqué en la URL de mi propio repo (error 404).

4. Pruebas y Resultados

Para probarlo, creé un programa rdprotect_test.c.

Al principio, me confundí mucho porque cuando protegía la memoria, el programa fallaba al intentar escribir, no al leer. Me salía un error scause 0xf (Store Page Fault).

Investigando un poco, entendí que en la arquitectura RISC-V, si le quitas el permiso de lectura a una página, el hardware automáticamente bloquea también la escritura (porque una página "solo escritura" no es válida en este hardware).

Para confirmar que mi código sí funcionaba, modifiqué el test para intentar leer directamente. Ahí sí me dio el error scause 0xd (Load Page Fault), que es exactamente lo que pedía la tarea: que el programa fallara al intentar leer.

5. Conclusión

Logré implementar las syscalls correctamente. Aunque el hardware de RISC-V es más estricto de lo que pensaba y bloquea todo acceso (lectura y escritura) cuando quito el bit PTE_R, la funcionalidad de protección de lectura se cumple perfectamente.
