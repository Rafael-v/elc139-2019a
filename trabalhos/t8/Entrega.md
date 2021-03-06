# Entrega.md

## Identificação

Nome: Rafael Vales Bettker

Disciplina: ELC139 - Programação Paralela

## Parte 1

O código desenvolvido se encontra em [wavecuda1.cu](wavecuda1.cu). Para a analise do desempenho foram feitas execuções com tamanho de imagem de 1024 e variação de 100, 200, 400 e 800 frames entre as execuções. A comparação dos resultados das execuções paralela, em que cada frame é computado por uma thread diferente, com a sequencial pode ser vista abaixo.

| width frames | wave.cpp  | wavecuda1.cu | speedup |
| ------------ | --------- | ------------ | ------- |
| 1024  100    |  42.4468s |      0.6151s |    69.0 |
| 1024  200    |  84.7403s |      0.6732s |   125.9 |
| 1024  400    | 169.3149s |      1.3003s |   130.2 |
| 1024  800    | 338.5237s |      2.3285s |   145.4 |
| 1024 1600    | 676.7345s |      4.2005s |   161.1 |

Os tempos de execução para o programa sem paralelismo obtiveram um crescimento linear, começando em 42.4s para 100 frames e duplicando esse valor a medida que os frames também eram duplicados para os testes seguintes. Para o programa onde foi feita a paralelização de cada frame em uma thread, os dois menores valores de frames, 100 e 200, obtiveram tempos de execução muito próximos, ambos na casa dos 600ms. Fazendo o teste com apenas 1 frame foi notado que esse é o tempo mínimo de execução para os valores mais baixos e que começa a subir quando se aproxima dos 200 frames, a partir disso o tempo de execução vai aumentando um pouco menos que o dobro, assim aumentando gradativamente o speedup para imagens com mais quadros. Porém, como o número de threads (que é igual ao número de frames) aumenta exponencialmente, o speedup não consegue acompanhar e a eficiência acaba despencando para valores mais altos.

## Parte 2

O segundo programa pode ser visto em [wavecuda2.cu](wavecuda2.cu). Para melhorar o aproveitamento do paralelismo da GPU, foram adicionados multiplos blocos (igual ao tamanho width), assim cada bloco ficou responsável por computar uma linha da imagem, enquanto as threads se mantiveram computando cada frame como na parte 1. As execuções para analise do desempenho foram feitas com variações de tamanho (512, 1024 e 2048) e número de frames (100, 200, 400 e 800). Os tempos obtidos estão na tabela abaixo.

| width frames | wave.cpp  | wavecuda2.cu | speedup  |
| ------------ | --------- | ------------ | -------- |
|  512 100     |  10.7236s |      0.0081s |   1323.9 |
|  512 200     |  21.3183s |      0.0181s |   1177.8 |
|  512 400     |  42.4642s |      0.0377s |   1126.4 |
|  512 800     |  84.7404s |      0.0778s |   1089.2 |
| 1024 100     |  42.4468s |      0.0440s |    964.7 |
| 1024 200     |  84.7403s |      0.0849s |    998.1 |
| 1024 400     | 169.3149s |      0.1954s |    866.5 |
| 1024 800     | 338.5237s |      0.5235s |    646.7 |
| 2048 100     | 169.3148s |      0.1709s |    990.7 |
| 2048 200     | 338.4813s |      0.3496s |    968.2 |
| 2048 400     | 676.6940s |      0.7951s |    851.1 |

Assim como já visto na primeira parte, o tempo de execução do programa sem paralelismo cresceu linearmente. Ao utilizar a técnica de paralelismo com blocos o desempenho melhorou consideravelmente em relação ao programa paralelo da parte 1, como era de se esperar. Ao analisar os tempos obtidos é percebido que o maior speedup está na configuração com menor blocos e threads. Apesar do tempo se manter em menos de 1 segundo para todos testes, a aceleração e eficiência caem a medida que os testes vão sendo feitos em imagens de tamanho e frames maiores.

## Slides

[slides.pdf](slides.pdf)

## Ambiente dos testes

Dispositivo da plataforma Google Colaboratory usado durante as execuções:

| CUDA Device                    |             |
| ------------------------------ | ----------- |
| Major revision number:         | 7           |
| Minor revision number:         | 5           |
| Name:                          | Tesla T4    |
| Total global memory:           | 15812263936 |
| Total shared memory per block: | 49152       |
| Total registers per block:     | 65536       |
| Maximum threads per block:     | 1024        |
| Maximum dimension 0 of block:  | 1024        |
| Maximum dimension 1 of block:  | 1024        |
| Maximum dimension 2 of block:  | 64          |
| Maximum dimension 0 of grid:   | 2147483647  |
| Maximum dimension 1 of grid:   | 65535       |
| Maximum dimension 2 of grid:   | 65535       |
| Clock rate:                    | 1590000     |
| Total constant memory:         | 65536       |
| Number of multiprocessors:     | 40          |

## Referências

- Programming Guide :: CUDA Toolkit Documentation. https://docs.nvidia.com/cuda/cuda-c-programming-guide/
