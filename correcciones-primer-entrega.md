* Usar static en métodos "privados" del tda.
* client_main.c: Validar al menos que estén la cantidad de argumentos necesarios.
* code_selector.c: ubicar los TDAs de los encriptadores dentro del selector, de esta manera se evita esa situación en `send_coded_message_to_server` donde se instancian todos los TDAs y no se inicializan. (Nota al margen, no soy muy "fan" de las estructuras `union`, pero creo que es un buen caso de uso de los mismos).
* Headers: incluir sólo los necesarios, sobre todos los includes dentro de headers, es preferible que estén en las unidades de compilación (ej: `#include <stdlib.h>` en varios headers)
