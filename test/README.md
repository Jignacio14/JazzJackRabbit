# Test 

Los archivos de la carpeta test son un conjunto de archivos .cpp que ejecutan validaciones sobre el comportamiento del protocolo estos test estan hechos para probar el correcto traspaso de informacion mediante el socket y verificar que dicha informacion sea lo esperado. 

## Requisitos

Los archivos de test tienen los mismos requerimientos que el juego para poder ser ejecutados 

## Ejecucion 

Los test son bastantes sencillos de ejecutar y prueban las funcionalidades basicas de los protocolos del cliente y el servidor. Para poder ejecutarlos se debera estar en la ruta contenedora del juego, una vez en alli:

        cd test/
        mkdir build
        cd build 
        cmake .. 
        make 

Debera ejecutarse siempre el archivo del servidor primero, el cual esta diseñado para esperar la conexión realizada por el archivo de pruebas del cliente. 

Una vez compilados ambos archivos se ejecuta 

    ./serverTests

Y en otra terminal se ejecuta:

    ./clientTests

Es importante recalcar que se estaria usando "localhost" y el puerto "8080" para poder ejecutar estas pruebas, es importante esto ya que si se tiene ocupado el puerto, las pruebas no funcionaran 
