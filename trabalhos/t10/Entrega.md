# Entrega.md

## Identificação

Rafael Vales Bettker & Natan Luiz Berwaldt

Disciplina: ELC139 - Programação Paralela

## Trabalho 10

### Estudo acerca de implementações MPI com compartilhamento de memória.

Técnicas hibridas utilizando MPI/OpenMP demonstram bons resultados de paralelismo a muito tempo, usando MPI para a comunicação
entre nodos e o OpenMP para a comunicação interna entre as threads.  

Porém com o passar das versões o MPI começou a adotar soluções internas para a aceleração da comunicação entre processos 
que estão localizados no mesmo nó e permitem o uso de memória compartilhada.  

Uma nova alternativa hibrida foi introduzida a partir do MPI 3 da biblioteca MPI da Intel, com o modelo *MPI SHM (shared memory)*. 
Este modelo basicamente converte codigos MPI normais em metodos que aceleram a comunicação entre processos que compartilham memória.
Porém, como esta biblioteca pertence a Intel, não parece haver código fonte disponível na web, impossibilitando assim que façamos 
uma maior averiguação do funcionamento do mesmo.  

O *Open MPI* por sua vez faz uso de modulos *BTL (Byte Transport Layer)* sendo a versão mais recente chamada "vader",
de modo geral, o sender escreve na memória compartilhada o dado e então o receiver acessa essa posição da memória e lê o mesmo, 
para ter acesso à estes métodos o proprio MPI avalia se a aplicação requer ou não o compartilhamento de memória e se ela terá vantagem
em questão de velocidade, se a resposta é afirmativa, ao invés de utilizar a função padrão que é feita através da rede, ela utiliza uma função
especifica de memória compartilhada.  
função padrão: "coll_bcast.c"  
função com memoria compartilhada: "coll_sm_bcast.c" (localizada em: ompi-master\ompi-master\ompi\mca\coll\sm\coll_sm_bcast.c)  

Outra implementação do MPI, o *MPICH* utiliza em sua base o subsistema de mensagem "Nemesis", o qual é responsável pelo controle 
de comunicação em alta performance em memória compartilhada.  

Nota-se que em nenhuma das implementações há uso explicito de OpenMP ou pthreads, o que indica que a forma como foi implementado 
o paralelismo lcoal com compartilhamento de memória é baseado em estratégias próprias desenvolvidas pelos programadores de 
cada aplicação, ou estão envoltos por uma interface a qual não conseguimos interpretar no tempo estipulado do trabalho.

*(Mais informações não puderam ser encontradas devido ao curto prazo disponível.)*

## Códigos-fonte

MPICH
https://github.com/pmodels/mpich

OPEN MPI
https://github.com/open-mpi/ompi

MPICH BCAST REFERENCE
http://formalverification.cs.utah.edu/sawaya/html/d9/d69/mpi_2coll_2bcast_8c.html

## Referências

- MORALES, Diego Francisco de Gastal. Compilação de código C/Mpi para C/Pthreads. UFRGS, 2008.  

- BRINSKIY ,Mikhail. An Introduction to MPI-3 Shared Memory Programming. Intel Articles, 2015.  

- THAKUR, Rajeev. RABENSEIFNER, Rolf. GROPP, WEilliam. Optimization of Collective Communication Operations in MPICH. 

- MVAPICH team. MVAPICH 1.2 User and Tuning Guide. OHIO, 2012
