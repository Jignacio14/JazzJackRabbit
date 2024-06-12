# Manual de usuario

Este documento cubre cómo instalar las dependencias y el juego, cómo correrlo y cómo usarlo.

Tabla de contenidos:

1. [Cómo buildear y correr en local](#Cómo-buildear-y-correr-en-local)
1. [Cómo setupear y correr con Vagrant](#Cómo-setupear-y-correr-con-Vagrant)

## Cómo buildear y correr en local

Para instalar los paquetes necesarios correr el script:

```shell
./scripts/setup_libs.sh
```

Para crear los ejecutables (cliente y servidor) correr el script:

```shell
./scripts/build.sh
```

### Ejecución sin Valgrind

Los ejecutables se encontrarán en la carpeta recién creada build por lo que para ejecutarlos hay que correr el siguiente comando estando con la terminal situada en la carpeta del root del proyecto:

```shell
./build/client
```

```shell
./build/server
```

### Ejecución con Valgrind

Disclaimer: los archivos de supresión no están del todos optimizados para la máquina de Vagrant.

Los ejecutables se encontrarán en la carpeta recién creada build por lo que para ejecutarlos con Valgrind y los archivos de supresión hay que correr:

```shell
valgrind --tool=memcheck --leak-check=full --show-reachable=yes --trace-children=yes --track-fds=yes --track-origins=yes --gen-suppressions=all --suppressions=./valgrind/memcheck.supp --suppressions=./valgrind/qt.supp --suppressions=./valgrind/sdl.supp ./build/client
```

```shell
valgrind --tool=memcheck --leak-check=full --show-reachable=yes --trace-children=yes --track-fds=yes --track-origins=yes --gen-suppressions=all --suppressions=./valgrind/memcheck.supp ./build/sever
```

## Cómo setupear y correr con Vagrant

### Vagrant setup

Para instalar los paquetes necesarios para levantar la virtual machine (vm) con Vagrant de acuerdo a las configuraciones declaradas al Vagrantfile hay que correr los siguientes comandos.

Utilizaremos VirtualBox como VM Provider, para instalarlo hay que correr:

```shell
sudo apt-get --yes install virtualbox
```

```shell
sudo apt-get --yes install virtualbox-ext-pac
```

> Probado con VirtualBox version 7.0.14

Para instalar Vagrant hay que correr:

```shell
sudo apt-get --yes install vagrant
```

> Probado con Vagrant version 2.3.6

Utilizaremos un plugin de Vagrant para reiniciar la VM en provision time y así realizar un setup correcto. Para instalarlo hay que correr:

```shell
vagrant plugin install vagrant-reload
```

### Cómo correr la VM

Para ejecutar y provisionar la VM hay que correr:

```shell
vagrant up
```

De esta manera se realizarán todos los pasos para realizar un correcto provisioning de una VM corriendo Ubuntu 22.04 con el entorno gráfico xubuntu-desktop.

Una vez que en la consola donde Vagrant corre se puede observar el mensaje "Provisioning complete", es decir, la VM tiene el juego listo para correr (en esta etapa la VM se reinició dos veces), hay que logearse en la VM con la contraseña `vagrant` y correr el cliente o servidor de la siguiente manera. El proceso de provisioning puede tardar 10 minutos con una PC y conexión a internet buena buena o más dependiendo del estado de la conexión y los recursos de la computadora host que instalará las dependencias.

Primero abrir una terminal, con `CTRL + ALT + T` por ejemplo. Y luego situarse en la carpeta root del proyecto con el comando:

```shell
cd /vagrant/
```

Luego, para ejecutar el servidor correr:

```shell
/vagrant/build/server <puerto>
```

Y para ejecutar un cliente correr:

```shell
/vagrant/build/client
```

### Comandos útles de Vagrant

1. Si se actualizaron los scripts de provisioning, se puede correr el siguiente comando para aplicar los scripts sobre la misma VM actual:

```shell
vagrant reload --provision
```

2. Si sólo se quiere reiniciar la VM:

```shell
vagrant reload
```

3. Si se cambió la estructura de la VM, es decir, se editó el Vagrantfile, hay que correr (preferentemente antes de guardar los cambios del Vagrantfile) el siguiente comando para destruir la VM (la para y luego la elimina):

```shell
vagrant destroy
```

Luego levantar una nueva VM con la nueva configuración con el comando:

```shell
vagrant up
```

4. Si se quiere apagar la VM:

```shell
vagrant halt
```

5. Para acceder a una terminal dentro del sistema operativo de la VM:

```shell
vagrant ssh
```

## Cómo funciona la interfaz del juego

### Interfaz del servidor

El servidor se lanza por terminal corriendo el binario con un parámetro que es el puerto, y correrá en el hostname `localhost`.

### Interfaz del cliente

El cliente primero lanza una UI construida con Qt que llamaremos `Lobby`, una vez finalazas las acciones del lobby e iniciada la conexión para comenzar a jugar, el lobby se cerrará y se abrirá el `Juego`, construido íntegramente con SDL2.

#### Lobby

La primera acción a realizar es ejecutar la conexión del cliente con el servidor. Esto se hace rellenando el hostname y el puerto, posteriormente apretando el botón de conexión. Si se habilitan los botones de la ventana inicial la conexión fue exitosa. Por defecto el servidor espera una conexión en localhost, así que en el campo de hostname poner `localhost` y luego el puerto correspondiente.

Todos los campos de texto tienen validación de input así que si un dato se puso de manera incorrecta o la conexión falla, se mostrará un mensaje con lo que está ocurriendo.

En la ventana inicial podemos elegir entre crear una partida o unirse a una de las partidas ya creadas.

Si creamos una nueva partida debemos ingresar nuestro nombre de usuario, las configuraciones de una partida como ser la duración de la partida y la cantidad de jugadores de la misma está definida en el archivo de configuración del juego, ubicado en el root del proyecto y usado en todos los componentes del juego llamado `games_config.yaml`. Luego se selecciona el personaje que uno quiera utilizar y se quedará en la ventana de espera hasta que se conecten todos los jugadores y se llene la partida.

Si se seleccionó ingresar a un juego ya existente, la partida se visualizará con el nombre del usuario que la creó. Hay un botón para refrescar las partidas que están en vivo en el momento. Luego de ingresar a la partida deseada con el botón `Join` correspondiente se verán las opciones del juego y se debe ingresar el nombre de usuario. Una vez completado ese paso se procede a la pantalla de espera.

#### Juego

Cuando todos los jugadores entraron a la partida, la ventana del Lobby se cierra y se abre el Juego.

Los controles son los siguientes:

- `FLECHA DERECHA`: mueve el jugador a la derecha
- `FLECHA IZQUIERDA:` mueve el jugador a la izquierda
- `FLECHA ARRIBA`: ejecuta la acción de salto
- `BARRA ESPACIADORA`: ejecuta la acción de disparo
- `Q`: cierra el juego
- `ESCAPE`: cierra el juego
- `F1`: muestra el panel de información debug, como los FPS

La cámara del juego sigue al personaje que el jugador está controlando.