# Entrega.md

## Identificação

Nome: Rafael Vales Bettker

Disciplina: ELC139 - Programação Paralela

## Programa

em [OpenMPDemoABC.cpp](OpenMPDemoABC.cpp).

## Exemplo de saída

  Para os casos da saída abaixo foi utilizado 3 threads com um vetor compartilhado de 60 posições e chunk igual a 6.
  ```
  $ g++ -std=c++11 OpenMPDemoADC.cpp -fopenmp -o OpenMPDemoADC 
  $ ./OpenMPDemoADC
  ```
  `static`: os dois primeiros casos de testes possuem schedule static, um com e outro sem chunk. Com esse schedule os laços foram divididos pelo tamanho do chunk (sendo 1 para o caso sem chunk) e distribuidos de forma circular entre as threads, ou seja, o primeiro chunk fica de responsabilidade da thread A, o segundo da B, o terceiro da C, o quarto da A novamente e assim em diante. Observa-se que no primeiro caso o tamanho da chunk é de 1, assim todas possuem o mesmo número de presenças no vetor, diferente do segundo caso que as chunks foram divididas em tamanho 6 resultando em 10 chunks, que na divisão entre as três threads acabou sobrando um, dado para a primeira thread.
  ```
  Schedule STATIC sem chunk
  time: 146428usec
  AAAAAAAAAAACCCCCCCCCCCCCCCCCCCCBBBBBBBBBBBBBBBBBBBBAAAAAAAAA
  A=20 B=20 C=20 

  Schedule STATIC com chunk
  time: 146632usec
  BBBBBBBCCCCCCCCCCCCCCCCCCAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBB
  A=24 B=18 C=18 
  ```
  `dynamic`: os casos seguintes utilizaram schedule dynamic, com e sem chunk. Nesse caso os três primeiros chunks foram dados as três threads, e a medida que cada uma terminou a execução do seu chunk, pegou o próximo. Esse caso não garante que as threads executem números parecidos de laços, como podemos ver no primeiro caso onde a thread B fez significativamente menos trabalho que as outras. No caso com chunk as threads obtiveram desempenho bem dividido, e todas resultando em um número de presenças multiplo de 6 como esperado, que é o tamanho da chunk.
  ```
  Schedule DYNAMIC sem chunk
  time: 144926usec
  BCAACABCCCCACBCCCCCCCCBAAAAAAAAAAAAAACCCCCCAACCCCBAAAAAAAACB
  A=28 B=6 C=26 

  Schedule DYNAMIC com chunk
  time: 145954usec
  BBBBBBCCCCCCABBBBBBAAAAAACCCCCCAACABACABACBCACABCACACBACBCCC
  A=18 B=18 C=24 
  ```
  `guided`: para os próximos casos foi utilizado shcedule guided, com e sem chunk também. Bastante parecido com o dynamic, porém o tamanho do chunk começa em um número e vai decrementando até o valor dado para ele (1 para sem chunk, 6 para com). Essa opção ajuda a balancear melhor a divisão do trabalho.
  ```
  Schedule GUIDED sem chunk
  time: 145200usec
  CAAAAAAAAAAACCCCCCCCAAACCCCCCCCCCCAAAAAAAAABBBBBBBBBCCCCBCAA
  A=25 B=10 C=25 

  Schedule GUIDED com chunk
  time: 145509usec
  CCCCCCCCCCCCABCABCABABCBABCBCACACABABCABCBACACABCABACACBAAAA
  A=20 B=14 C=26 
  ```
  `runtime`: aqui foi utilizado runtime como opção para a cláusula schedule. Nesse caso pode-se escolher, em tempo de execução, um dos três casos mostrados acima para ser usado. Para o caso testado foi utilizado o default.
  ```
  Schedule RUNTIME
  time: 144837usec
  CACCCACBAAAACACCCAAAAAAABCCCCCCAAAAAAAAAAACBCACACABCACACABAC
  A=32 B=5 C=23 
  ```
  `auto`: no seguinte caso a opção auto foi testada. Aqui é dada ao compilador a liberdade de escolher o melhor caso a ser utilizado. Na saída vista abaixo, foi dividido igualmente o trabalho entre as três threads, assim como no primeiro caso (static sem chunk), porém não é possível afirmar com certeza que foi essa opção utilizada.
  ```
  Schedule AUTO
  time: 147023usec
  CCCCCCBBBBBBCCCCCCCCCCCCCCAAAAAAAAAAAAAAAABABABABABBBBBBBBBB
  A=20 B=20 C=20 
  ```
  `sem mutex`: os dois últimos casos foram feitos sem o uso do mutex, tendo assim uma saída incorreta por conta de haver acesso a um vetor compartilhado que necessita do uso de exclusão mútua. Além de haver dois espaços do vetor não preenchido, é possível observar também uma grande diferença no tempo de execução se comparado aos casos com mutex, uma vez que sem ele as threads não precisam ficar esperando para o acesso a área crítica como nos outros casos.
  ```
  Sem exclusao mutua 1
  time: 54897usec
  ABACBACBACBACBACBACBACBACBACBBACBACBACBACBACBACBACBACBAC-AC-
  A=20 B=19 C=19 

  Sem exclusao mutua 2
  time: 54631usec
  BBACBACBACBACBACBACBACBACBACBACBACBACBACBACBACBBACBACBAC-AC-
  A=19 B=20 C=19
  ```

## Referências

- FCUP. Introdução ao OpenMP. https://www.dcc.fc.up.pt/~fds/aulas/PPD/0708/intro_openmp-1x2.pdf
- UFSC. OpenMP Scheduling. http://www.inf.ufsc.br/~bosco.sobral/ensino/ine5645/OpenMP_Dynamic_Scheduling.pdf
- FSU. Scheduling Loop Iterations in OpenMP. https://people.sc.fsu.edu/~jburkardt/c_src/schedule_openmp/schedule_openmp.html
- Aalto University. Chapter 3: schedule. http://ppc.cs.aalto.fi/ch3/schedule/
- Intel Software. OpenMP* Loop Scheduling. https://software.intel.com/en-us/articles/openmp-loop-scheduling
