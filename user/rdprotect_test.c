#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
  // Usamos sbrk(0) para obtener la dirección actual (alineada a página)
  char *addr = sbrk(0);

  // Reservar una página (4096 bytes)
  if(sbrk(4096) == (void*)-1){
    printf("sbrk falló\n");
    exit(1);
  }

  printf("Página alocada en %p\n", addr);

  // 1. Escribir valor inicial (debería funcionar)
  addr[0] = 'Z';
  printf("Escritura inicial 'Z' exitosa.\n");

  // 2. Proteger la página contra lectura (len = 1 página)
  if (mrdprotect(addr, 1) < 0) {
    printf("mrdprotect falló\n");
    exit(1);
  }
  printf("Página protegida contra lectura (PTE_R=0).\n");

  // 3. Segunda escritura (debería funcionar, PTE_W sigue activo)
  addr[0] = 'A';
  printf("Segunda escritura 'A' exitosa (Write-Only).\n");

  // 4. Intento de lectura (debería fallar)
  printf("Intentando leer... (esto provocará un Page Fault y el kernel matará el proceso)\n");

  // La siguiente línea causa un 'load page fault' (Causa 13)
  char c = addr[0];

  // 5. Este código es INALCANZABLE si mrdprotect funciona
  printf("ERROR: ¡La lectura fue exitosa! Valor: %c\n", c);
  printf("ERROR: ¡Esto NO debería imprimirse!\n");

  // 6. Revertir protección (inalcanzable en este test)
  if (munrdprotect(addr, 1) < 0) {
    printf("munrdprotect falló\n");
    exit(1);
  }
  printf("Protección revertida correctamente.\n");

  exit(0);
}
