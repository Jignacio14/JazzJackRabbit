# JazzJackRabbit
Repositorio del grupo 7 para la materia taller de programacion 

## Setup para desarrollo

Instalar pre-commit hooks:

```shell
pre-commit install
```

Para crear un commit sin correr los hooks se debe ejecutar:

```shell
git commit --no-verify
```

Para correr cppcheck sin necesidad de un commit se debe ejecutar:

```shell
pre-commit run --all-files
```