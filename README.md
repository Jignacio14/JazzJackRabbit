# JazzJackRabbit 2

Repositorio del Grupo 7 para la materia Taller de Programación 1 - Curso Veiga

#### Tabla de contenidos

1. [Setup para desarrollo](#Setup-para-desarrollo)
1. [Cómo modificar CMake](#Cómo-modificar-CMake)
1. [Cómo buildear y correr](#Cómo-buildear-y-correr)
1. [Cómo setupear y correr con Vagrant](#Cómo-setupear-y-correr-con-Vagrant)
   1. [Vagrant setup](#Vagrant-setup)
   1. [Cómo correr la VM](#Cómo-correr-la-VM)
   1. [Comandos útles de Vagrant](#Comandos-útles-de-Vagrant)
   1. [Cómo desarrollar con la VM de Vagrant](#Cómo-desarrollar-con-la-VM-de-Vagrant)
   1. [Detalles sobre Vagrant](#Detalles-sobre-Vagrant)

## Setup para desarrollo

Instalar pre-commit hooks:

```shell
pre-commit install --hook-type commit-msg
```

> Se espera que el sistema que corra los hooks tenga como mínimo cppcheck version 2.13, cpplint version 1.6 y clang-format version 16

Para crear un commit sin correr los hooks se debe ejecutar:

```shell
git commit --no-verify
```

Para correr cppcheck sin necesidad de un commit se debe ejecutar:

```shell
pre-commit run --all-files
```

## Cómo modificar CMake

Cuando se agregan subcarpetas dentro de src, hace falta trackearlas en el CMake para que se agregen todos los .h y los .cpp. Esto se puede hacer agregan la rupa de las subcarpetas dentro de las funciones file del CMake que contienen la keyword GLOB_RECURSE. Se puede agregar el tracking de todos los \*.h y los \*\*.cpp de manera análoga a como ya está hecho con el caso de la UI.

## Cómo buildear y correr

Para instalar los paquetes necesarios correr el script:

```shell
./scripts/setup_libs.sh
```

Para crear los ejecutables (cliente y servidor) correr el script:

```shell
./scripts/build.sh
```

Los ejecutables se encontrarán en la carpeta recién creada build por lo que para ejecutarlos hay que correr:

```shell
./build/client
```

```shell
./build/server
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

Una vez que en la consola donde Vagrant corre se puede observar el mensaje "Provisioning complete", es decir, la VM tiene el juego listo para correr (en esta etapa la VM se reinició dos veces), hay que logearse en la VM con la contraseña `vagrant` y correr el cliente o servidor de la siguiente manera.

Primero abrir una terminal, con `CTRL + ALT + T` por ejemplo.

Luego, para ejecutar el servidor correr:

```shell
/vagrant/build/server
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

### Cómo desarrollar con la VM de Vagrant

Recomiendo crear la VM una vez y no cambiar el Vagrantfile o los scripts de provisioning seguido, así no hace falta crear de nuevo la VM que tarda unos minutos entre instalar las librerías y el entorno gráfico.

Una vez que se tiene la VM creada, es mejor levantarla solamente, `vagrant up` no ejecuta el provisioning una vez que ya se ejecutó al menos una vez. Así que si se actualizó el código, simplemente correr `/vagrant/scripts/build_for_vagrant.sh` para buildear de nuevo dentro de la VM y ahí correr, por ejemplo el cliente para probarlo con `/vagrant/build/client`.

### Detalles sobre Vagrant

El Vagrantfile usa sintaxis del lenguaje de programación Ruby para declarar las configuraciones.

Por default, todo lo que está en la carpeta donde el Vagrantfile se encuentra ubicado será compartido con la VM como una carpeta compartida. Ésta será la carpeta `/vagrant`, o sea, ubicada en el root de la VM. Desde aquí se harán los manejos necesarios de archivos, es decir, la build se guardará en esta carpeta así como también se ejecutarán los binarios ejecutables.
