# Entrega.md

## Identificação

Nome: Rafael Vales Bettker

Disciplina: ELC139 - Programação Paralela

## Pthreads

1. Explique como se encontram implementadas as 4 etapas de projeto: particionamento, comunicação, aglomeração, mapeamento (use trechos de código para ilustrar a explicação).

2. Considerando o tempo (em microssegundos) mostrado na saída do programa, qual foi a aceleração (speedup) com o uso de threads?

    ```
    $ ./pthreads_dotprod 1 1000000 2000
    10000.000000
    1 thread(s), 7325004 usec
    $ ./pthreads_dotprod 2 500000 2000
    10000.000000
    2 thread(s), 3684726 usec
    $ ./pthreads_dotprod 4 250000 2000
    10000.000000
    4 thread(s), 2802964 usec
    ```
    O speedup foi de 1.9879 com o uso de 2 threads (eficiência de 99,395%) e de 2.6133 com 4 threads (eficiência de 65,333%).

3. A aceleração se sustenta para outros tamanhos de vetores, números de threads e repetições? Para responder a essa questão, você terá que realizar diversas execuções, variando o tamanho do problema (tamanho dos vetores e número de repetições) e o número de threads (1, 2, 4, 8..., dependendo do número de núcleos). Cada caso deve ser executado várias vezes, para depois calcular-se um tempo de processamento médio para cada caso. Atenção aos fatores que podem interferir na confiabilidade da medição: uso compartilhado do computador, tempos muito pequenos, etc.

4. Elabore um gráfico/tabela de aceleração a partir dos dados obtidos no exercício anterior.

5. Explique as diferenças entre [pthreads_dotprod.c](pthreads_dotprod/pthreads_dotprod.c) e [pthreads_dotprod2.c](pthreads_dotprod/pthreads_dotprod2.c). Com as linhas removidas, o programa está correto?

A única diferença entre os dois programas é a remoção das duas linhas referentes ao lock e unlock do mutex *mutexsum*. Com essa alteração o programa fica incorreto, podendo gerar resultados não esperados, pois a falta do mutex para aquela instrução permite que mais de uma thread a execute ao mesmo tempo, e por ser uma região crítica, pode levar a inconsistências no seu valor uma vez que uma thread A pode fazer a leitura da variável *dotdata.c* momentos antes de uma thread B atualizá-la, assim a thread A fará a soma com o valor desatualizado e a soma feita por B, que havia sido salva, será perdida.
## OpenMP

## Referências

- Slides. Projeto de programas paralelos. https://github.com/AndreaInfUFSM/elc139-2019a/tree/master/slides
- Unioeste. aula8. http://www.inf.unioeste.br/~guilherme/tsc/aula8
- Parasol Laboratory. Parallel Programs. https://parasol.tamu.edu/~rwerger/Courses/654/ch2.pdf
- Lawrence Livermore. Introduction to Parallel Computing
. https://computing.llnl.gov/tutorials/parallel_comp/
- FCUP. Introdução ao 
OpenMP. https://www.dcc.fc.up.pt/~fds/aulas/PPD/0708/intro_openmp-1x2.pdf
