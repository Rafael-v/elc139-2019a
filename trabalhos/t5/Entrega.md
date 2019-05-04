# Entrega.md

## Identificação

Nome: Rafael Vales Bettker

Disciplina: ELC139 - Programação Paralela

Plataforma: [specs.txt](../t2/specs.txt)

## Parte 1

- [parte1.c](parte1.c)

|   size   | repetitions |    time (1p)   | speedup (2p) | speedup (3p) | speedup (4p) | speedup (5p) |
|----------|-------------|----------------|--------------|--------------|--------------|--------------|
| 10000000 |     5000    | 151272051 usec | 1.93731649   | 2.28855317   | 2.66222864   | 2.67059467   |
| 10000000 |      500    |  14987997 usec | 1.95163809   | 2.21035150   | 2.54592535   | 2.66477524   |
|  5000000 |    10000    | 165458152 usec | 2.07083613   | 2.47197542   | 2.79018288   | 2.98547622   |
|  5000000 |     5000    |  74451123 usec | 1.96817752   | 2.24771577   | 2.64100222   | 2.71131818   |
|  1000000 |    10000    |  30052513 usec | 2.00537857   | 2.30524198   | 2.61516220   | 2.64192830   |
|  1000000 |     2000    |   6023120 usec | 1.91133341   | 2.26740802   | 2.52212627   | 2.57600302   |
|    20000 |    15000    |    906601 usec | 1.83094385   | 2.25888441   | 2.43945367   | 2.76768956   |
|    20000 |     2000    |    143636 usec | 1.84188862   | 2.12721591   | 2.55830439   | 2.76111570   |

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
