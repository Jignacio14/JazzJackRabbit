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

## Vagrant steps (work in progress)

sudo apt-get install virtualbox
vagrant up --provider virtualbox
