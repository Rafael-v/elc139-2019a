# Entrega.md

## Identificação

Nome: Rafael Vales Bettker

Disciplina: ELC139 - Programação Paralela

## Parte 1

A nova versão de [matrix_mult_sr.c](matrix_mult_sr.c) foi implementada com a ajuda das funções ``MPI_Scatter()`` e ``MPI_Bcast()``, além de ``MPI_Gather()`` que já estava presente.

A principal alteração feita foi a retirada da estrutura *if else* que fazia com que o processo 0 possuisse um papel adicional comparado aos demais, sendo encarregado de realizar o cálculo e envio do intervalo da matriz *A* correspondente a cada processo, além da matriz *B*.

Com a alteração, o envio da matriz *B* é feito pela função ``MPI_Bcast()``, que distribui a mesma mensagem (a matriz *B*, nesse caso) entre todos processos. Para a matriz *A*, era feita a divisão em intervalos e enviado apenas o intervalo correspondente que cada processo realizaria o cálculo, assim foi utilizado ``MPI_Scatter()`` que se encarrega de dividir a mensagem em *n* pedaços e enviar cada pedaço para um processo, exatamente como era feito antes. Além disso, como o cálculo do intervalo de cada processo foi retirado, também foi necessário fazer uma alteração no for que realiza a multiplicação das matrizes, alterando o intervalo que *i* executa e o local na matriz *C* onde é armazenado o resultado.

O código-fonte pode ser encontrado em [parte1.c](parte1.c).


## Parte 2

[Send-receive considered harmful: Myths and realities of message passing](https://dl.acm.org/citation.cfm?id=963780)

O artigo demonstra fatos e argumentos que indicam que o uso de *send-receive* não é uma boa prática, mostrando as operações coletivas como alternativa que desempenham a mesma função.

O primeiro mito citado é a simplicidade da primitiva *send-receive*, o qual é refutado com argumentos de que possui diversas combinações de chamadas diferentes que pode acabar se tornando não muito simples ao programador, além de citar um programa onde um dado é compartilhado usando ``MPI_Bcast()`` em apenas três linhas de código contra 31 linhas na versão do mesmo programa com *send-receive*. Esse ponto pôde ser notado na parte 1 ao ser feita remoção de todo o bloco do *if else* pela função ``MPI_Bcast()``, deixando o programa muito mais simples e com menos linhas de código.

Outro ponto discutido no artigo é de que programas com *send-receive* possuem melhor desempenho em relação à implementações com operações coletivas, porém é demonstrado que não há evidências quanto a isso. Para teste, ambas versões da parte 1 foram executadas mas o desempenho foi praticamente o mesmo, o que pode demonstrar o que é defendido pelo autor.

Além disso, foi discutido outros pontos como a expressividade, onde o autor demonstra que um amplo número de padrões de comunicação encontrados em aplicações paralelas utilizam operações coletiva; a programabilidade onde é reforçado que operações coletivas facilitam transformações de programas de alto nível; e a previsibilidade.

São argumentos bons que demonstram que o uso de operações coletivas é uma melhor prática de programação do que *send-receive* na programação paralela.

## Referências

- Slides. Operações coletivas em MPI. https://github.com/AndreaInfUFSM/elc139-2019a/tree/master/slides
