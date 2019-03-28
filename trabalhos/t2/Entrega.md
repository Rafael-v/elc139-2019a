# Entrega.md

## Identificação

Nome: Rafael Vales Bettker

Disciplina: ELC139 - Programação Paralela

## Pthreads

1. Explique como se encontram implementadas as 4 etapas de projeto: particionamento, comunicação, aglomeração, mapeamento (use trechos de código para ilustrar a explicação).

- **Particionamento:** Essa parte é onde ocorre a divisão da tarefa entre as threads para aproveitar ao máximo o paralelismo. Nesse programa, isso é feito no seguinte trecho de código:

    ```
    long offset = (long) arg;
    double *a = dotdata.a;
    double *b = dotdata.b;
    int wsize = dotdata.wsize;
    int start = offset*wsize;
    int end = start + wsize;
    ```
Esse trecho se encontra na função *dotprod_worker* que recebe o argumento *arg*, correspondendo ao id da thread que está executando, assim cada thread terá um valor para *arg* e consequentemente um *offset* diferente. Dessa maneira, é possível delimitar um intervalo que cada thread executará, utilizando o *offset* e o tamanho do intervalo *wsize* para definir o início e final, como calculado nas duas últimas linhas do trecho.

- **Comunicação:** A comunicação é feita no seguinte trecho de código:
    ```
    pthread_mutex_lock (&mutexsum);
    dotdata.c += mysum;
    pthread_mutex_unlock (&mutexsum);
    ```
A variável *dotdata* e *mutexsum* são compartilhados por todas as threads, sendo em *dotdata.c* armazenado o resultado obtido pelos calculos de cada uma. O *mutexsum* ajuda na sincronização.

- **Aglomeração:** Serve para reduzir as comunicações. Nesse código é feito no seguinte trecho:
    ```
    for (i = start; i < end ; i++)  {
        mysum += (a[i] * b[i]);
    }
    ```
Onde cada thread faz os cálculos do seu intervalo afim de obter um resultado parcial que será juntado com o das outras threads mais pra frente, no trecho mostrado na comunicação.

- **Mapeamento:** Aqui é feito um balanceamento da tarefa entre as threads, estático nesse programa. Mostrado no trecho a seguir:
    ```
    for (i = 0; i < nthreads; i++) {
        pthread_create(&threads[i], &attr, dotprod_worker, (void *) i);
    }
    ```
Cada thread é criada e fica responsável por um intervalo de cálculo de tamanho igual para todas (estático), definido pelo seu indice que servirá de offset, como visto no trecho do particionamento.

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

Sim, aceleração se mantém praticamente igual para todos casos testados. Observando os testes vemos que houve um ganho de cerca de 1.9 em todos os casos ao passar de 1 para 2 threads, muito próximo de 2, que seria a aceleração teoricamente esperada. Já a aceleração com 4 threads ficou na casa dos 2.6, houveram ganhos de desempenho porém ficou um pouco mais distante dos 4 esperados na teoria.
Cada caso foi executado cinco vezes, e então obtido o *usec* médio.

4. Elabore um gráfico/tabela de aceleração a partir dos dados obtidos no exercício anterior.

|  size   | repetitions | speedup (2 threads) | speedup (4 threads) |
|---------|-------------|---------------------|---------------------|
| 6000000 |     5000    |        1.9997       |        2.6231       |
| 5000000 |      500    |        1.9930       |        2.6131       |
| 1000000 |     5000    |        1.9805       |        2.6069       |
| 1000000 |     2000    |        1.9879       |        2.6133       |
|  500000 |    10000    |        1.9876       |        2.6099       |

Resultados completos de todas execuções em [results.csv](results.csv).

5. Explique as diferenças entre [pthreads_dotprod.c](pthreads_dotprod/pthreads_dotprod.c) e [pthreads_dotprod2.c](pthreads_dotprod/pthreads_dotprod2.c). Com as linhas removidas, o programa está correto?

A única diferença entre os dois programas é a remoção das duas linhas referentes ao lock e unlock do mutex *mutexsum*. Com essa alteração o programa fica incorreto, podendo gerar resultados não esperados, pois a falta do mutex para aquela instrução permite que mais de uma thread a execute ao mesmo tempo, e por ser uma região crítica, pode levar a inconsistências no seu valor uma vez que uma thread A pode fazer a leitura da variável *dotdata.c* momentos antes de uma thread B atualizá-la, assim a thread A fará a soma com o valor desatualizado e a soma feita por B, que havia sido salva, será perdida.

## OpenMP

1. Implemente um programa equivalente a [pthreads_dotprod.c](pthreads_dotprod/pthreads_dotprod.c) usando OpenMP.

[openmp_dotprod.c](openmp_dotprod.c).

2. Avalie o desempenho do programa em OpenMP, usando os mesmos dados/argumentos do programa com threads POSIX.

O desempenho com OpenMP é mostrado na tabela a seguir.

|  size   | repetitions | speedup (2 threads) | speedup (4 threads) |
|---------|-------------|---------------------|---------------------|
| 6000000 |     5000    |        1.9866       |        2.5815       |
| 5000000 |      500    |        1.9959       |        2.5642       |
| 1000000 |     5000    |        1.9873       |        2.5650       |
| 1000000 |     2000    |        1.9886       |        2.5493       |
|  500000 |    10000    |        1.9897       |        2.5746       |

Os valores são praticamente os mesmos obtidos no programa com pthreads, ficando na base dos 1.99 de aceleração com 2 threads e 2.57 com 4 threads.

## Referências

- Slides. Projeto de programas paralelos. https://github.com/AndreaInfUFSM/elc139-2019a/tree/master/slides
- Unioeste. aula8. http://www.inf.unioeste.br/~guilherme/tsc/aula8
- Parasol Laboratory. Parallel Programs. https://parasol.tamu.edu/~rwerger/Courses/654/ch2.pdf
- Lawrence Livermore. Introduction to Parallel Computing
. https://computing.llnl.gov/tutorials/parallel_comp/
- FCUP. Introdução ao 
OpenMP. https://www.dcc.fc.up.pt/~fds/aulas/PPD/0708/intro_openmp-1x2.pdf
