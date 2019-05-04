# Entrega.md

## Identificação

Nome: Rafael Vales Bettker

Disciplina: ELC139 - Programação Paralela

Plataforma: [specs.txt](t2/specs.txt)

## Parte 1

- [parte1.c](parte1.c)

## Parte 2

- [parte2.c](parte2.c)

## Parte 3

- Programa [mpi_errado1.c](mpi_errado1.c) corrigido: [mpi_certo1.c](mpi_certo1.c)

A tag usada para o envio e recebimento das mensagens era igual ao id do processo. Assim, o processo 0 enviava mensagem para o 1 com a tag 0, porém o processo 1 esperava receber um mensagem com a tag 1 e vice-versa, o que só funcionaria se um processo enviasse uma mensagem para ele mesmo (para a tag corresponder). Desse modo, os processos permaneciam esperando pela mensagem eternamente.

- Programa [mpi_errado2.c](mpi_errado2.c) corrigido: [mpi_certo2.c](mpi_certo2.c)

O MPI não foi finalizado (sem chamada para a função MPI_Finalize()).

## Referências

- Slides. Programação paralela com MPI. https://github.com/AndreaInfUFSM/elc139-2019a/tree/master/slides
- MPI Tutorial. MPI Send and Receive. http://mpitutorial.com/tutorials/mpi-send-and-receive/
