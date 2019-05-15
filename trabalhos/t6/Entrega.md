# Entrega.md

## Identificação

Nome: Rafael Vales Bettker

Disciplina: ELC139 - Programação Paralela

## Parte 1

A nova versão de [matrix_mult_sr.c](matrix_mult_sr.c) foi implementada com a ajuda das funções ``MPI_Scatter()`` e ``MPI_Bcast()``, além de ``MPI_Gather()`` que já estava presente.

A principal alteração feita foi a retirada da estrutura if else que fazia com que o processo 0 possuisse um papel adicional comparado aos demais, sendo encarregado de realizar o cálculo e envio do intervalo da matriz A correspondente a cada processo, além da matriz B.

Com a alteração, o envio da matriz B é feito pela função ``MPI_Bcast()``, que distribui a mesma mensagem (a matriz B, nesse caso) entre todos processos. Para a matriz A, era feita a divisão em intervalos e enviado apenas o intervalo correspondente que cada processo realizaria o cálculo, assim foi utilizado ``MPI_Scatter()`` que se encarrega de dividir a mensagem em n pedaços e enviar cada pedaço a um processo, exatamente como era feito antes.

O código-fonte pode ser encontrado em [parte1.c](parte1.c).


## Parte 2


## Referências

- Slides. Operações coletivas em MPI. https://github.com/AndreaInfUFSM/elc139-2019a/tree/master/slides
