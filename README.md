# TP1-Cryptosockets
# Alumna: Azul Zaietz
# Padrón: 102214

En este trabajo se implementa un programa que actúa por un lado como cliente y por el otro como servidor. El rol del cliente es el de leer un archivo y enviarlo cifrado al servidor con el método especificado. El servidor recibe el mensaje y lo decodifica.

El siguiente informe detalla información relevante del proceso de desarrollo del programa: su esqueleto, diagramas de flujo y soluciones a algunos problemas presentados.

# DISEÑO

Antes de implementar la solución, se empezó por diseñarla, planteando las diferentes estructuras del programa y cómo iban a relacionarse entre sí. 

El diseño se pensó usando como base la programación orientada a objetos.

En un principio se plantearon los siguientes:

- METODOS DE CIFRADO: era necesario crear un TDA por cada método de cifrado con atributo "key" y métodos "code()" y "decode()". 
Debían implementarse independientemente entre sí y del resto de los objetos del programa. Esta abstracción permite que puedan usarse para cifrar y descifrar cualquier mensaje que sea pasado por los mismos.

- SOCKET: un TDA socket con los métodos necesarios para poder efectuar la comunicación entre cliente y servidor: abrir el socket, esperar a una conexión, aceptarla, enviar y recibir mensajes a través del mismo, y finalmente cerrar el socket correctamente.

- SERVIDOR: TDA que use a los mencionados anteriormente para cumplir su función: abrir un socket, esperar a recibir un mensaje, descifrarlo y mostrarlo.

- CLIENTE: al igual que el servidor, debía ser un TDA que utilice al socket y a los métodos de cifrado para enviar un mensaje cifrado al servidor.

- FILE CODER: para delegar responsabilidad, se pensó este TDA con la función de leer un archivo y cifrarlo. Va a ser usado por el cliente cuando corresponda.


# IMPLEMENTACIÓN

El primer problema que surgió a la hora de implementar el diseño pensado fue la falta de polimorfismo en C. Idealmente en programación orientada a objetos, todos los cifradores iban a tener un método "code()" y otro "decode()" que iban a poder usarse siempre y automáticamente el programa iba a darse cuenta de qué cifrador se trataba debido a que iba a poder saber qué objeto era. 
La solución que se planteó fue crear un nuevo TDA llamado CODER SELECTOR, cuya función era reconocer de qué tipo de dato se trataba y usar los métodos correspondientes en cada caso. 

Otras solución que surgió durante de la implementación fue la necesidad de el uso de una función común para poder parsear los parámetros leídos de la línea de comandos de la terminal, para que pueda ser usada tanto por el servidor como por el cliente.

## Diagrama de secuencia: Servidor recibe mensaje de cliente.

```plantuml
@startuml
    Server -> Socket : socket_bind_and_listen()
    Server -> Socket : socket_accept()
    Server -> CoderSelector : coder_selector_init()
    Server -> Socket : socket_receive()
    Server -> CoderSelector : decode(coder_selector_t, message)
    CoderSelector -> Server : decoded message
    note right Server #palegreen: show message
    Server -> Socket : socket_uninit()
    
@enduml
```
![server](./server_receive.svg)

## Diagrama de secuencia: Cliente envia mensaje a servidor.

```plantuml
@startuml
    Client -> Socket : socket_connect()
    Client -> CoderSelector : coder_selector_init()
    Client -> FileCoder : file_coder_init()
    Client -> FileCoder: code_file(coder_selector_t, buffer)
    FileCoder -> CoderSelector : code(coder_selector_t, buffer)
    FileCoder -> Client : read_bytes
    Client -> Socket : socket_send(buffer, read_bytes)
    Client -> FileCoder : file_coder_uninit()
    Client -> Socket : socket_uninit()
    
@enduml
```
![client](./client_send.svg)

# Diagrama de clases representativo de la solución final:

```plantuml
@startuml

class server
class client
class socket
class file_coder
class cesar
class vigenere
class rc4

server : char* method
server : char* key
server : char* server_port
server : receive_coded_message_from_client()

client : char* method
client : char* key
client : char* server_port
client : char* server_host
client : send_coded_message_to_server()

socket : int fd
socket : socket_bind_and_listen()
socket : socket_accept()
socket : socket_connect()
socket : socket_send()
socket : socket_receive()

file_coder : FILE* fp
file_coder : code_file()

cesar : int key
cesar : cesar_code()
cesar : cesar_decode()

vigenere : unsigned char* key
vigenere : size_t len_key
vigenere : int pos_key
vigenere : vigenere_code()
vigenere : vigenere_decode()

rc4 : unsigned char state_vector[256]
rc4 : unsigned char i
rc4 : unsigned char j
rc4 : rc4_code()

client o-- file_coder
server *-- socket
client *-- socket
coder_selector *-- rc4
coder_selector *-- vigenere
coder_selector *-- cesar
client o-- coder_selector
server o-- coder_selector
@enduml
```
![uml](./uml_tp_cryptosockets.svg)
