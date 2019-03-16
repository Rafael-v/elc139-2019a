[Programação Paralela](https://github.com/AndreaInfUFSM/elc139-2019a) > T1

TOP500 & me: Comparativo de Arquiteturas Paralelas
--------------------------------------------------

Nome: Rafael Vales Bettker

| Característica                                            | Computador no TOP500  | Meu computador  |
| --------------------------------------------------------- | --------------------- | --------------- |
| Nome/Título                                               | Edison | Samsung Expert X23 NP300E5MG |
| Imagem (foto, diagrama, screenshot, etc.)                 | <img src="https://i.imgur.com/76666mr.jpg" width="384"> | <img src="https://i.imgur.com/L6b3AwG.png" width="384">|
| Classificação de Flynn                                    | MIMD | MIMD |
| Memória: compartilhada, distribuída ou ambas?             | Ambas | Compartilhada |
| Número total de núcleos de processamento                  | 133,824 | 2 |
| Fabricante e modelo do(s) processador(es)                 | Intel Xeon E5-2695 v2 | Intel Core i5-7200U
| Frequência do(s) processador(es)                          | 2.4 GHz | 2.5 GHz |
| Memória total                                             | 356,864 GB | 8 GB |
| Tipo(s) de interconexão entre os núcleos/processadores    | Cray Aries com topologia Dragonfly | Intel QuickPath Interconnect (QPI) |
| Desempenho Linpack                                        | 1,654.7 TFlop/s | 76.7581 GFlop/s&ast; |

&ast; Máximo desempenho LINPACK alcançado. Saída completa em [win_xeon64.txt](./win_xeon64.txt).

### Referências
- TOP 500 Supercomputer Sites. Edison - Cray XC30. https://www.top500.org/system/178443
- NERSC. Edison. https://www.nersc.gov/users/computational-systems/edison/
- Samsung. Notebook Expert X23. https://www.samsung.com/br/support/model/NP300E5M-XD1BR/
- Intel. Intel® Xeon® Processor E5-2695 v2. https://ark.intel.com/content/www/us/en/ark/products/75281/intel-xeon-processor-e5-2695-v2-30m-cache-2-40-ghz.html
- Intel. Processador Intel® Core™ i5-7200U. https://ark.intel.com/content/www/br/pt/ark/products/95443/intel-core-i5-7200u-processor-3m-cache-up-to-3-10-ghz.html
- NERSC. Interconnect. https://www.nersc.gov/users/computational-systems/edison/configuration/interconnect/
- Intel. Intel® LINPACK Benchmark. https://software.intel.com/en-us/articles/intel-linpack-benchmark-download-license-agreement
