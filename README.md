# JazzJackRabbit 2
Repositorio del grupo 7 para la materia taller de programacion 

## Setup para desarrollo

Instalar pre-commit hooks:

```shell
pre-commit install --hook-type commit-msg
```

Para crear un commit sin correr los hooks se debe ejecutar:

```shell
git commit --no-verify
```

Para correr cppcheck sin necesidad de un commit se debe ejecutar:

```shell
pre-commit run --all-files
``` 

## Cómo modificar CMake

Cuando se agregan subcarpetas dentro de src, hace falta trackearlas en el CMake para que se agregen todos los .h y los .cpp. Esto se puede hacer agregan la rupa de las subcarpetas dentro de las funciones file del CMake que contienen la keyword GLOB_RECURSE. Se puede agregar el tracking de todos los *.h y los **.cpp de manera análoga a como ya está hecho con el caso de la UI.

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

### Detalles sobre Vagrant

El Vagrantfile usa sintaxis del lenguaje de programación Ruby para declarar las configuraciones.

Por default, todo lo que está en la carpeta donde el Vagrantfile se encuentra ubicado será compartido con la VM como una carpeta compartida. Ésta será la carpeta `/vagrant`, o sea, ubicada en el root de la VM. Desde aquí se harán los manejos necesarios de archivos, es decir, la build se guardará en esta carpeta así como también se ejecutarán los binarios ejecutables.
