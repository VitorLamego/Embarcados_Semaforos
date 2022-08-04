## Servidor Central

O servidor central deve ser rodado na placa cujo Ip corresponde a: 164.41.98.26.

Para correta execução do servidor central rode os seguintes comandos: 

```
cd trabalho1/servidor_central
make
bin/run
```

## Servidores Distribuídos

Para correta execução dos servidores distribuídos, rode os seguintes comandos:

```
cd trabalho1/cruzamentos
make
bin/run ${Número do cruzamento}
```

Sendo assim, para o ip com final .17 será rodado os seguintes comandos:

```
bin/run 1
bin/run 2
```

Para a placa com o ip com final .26, serão rodados os seguintes comandos:

```
bin/run 3
bin/run 4
```

## Observação

Os relatórios de infração e velocidade apenas são mostrados na seleção da opção 2 no menu. A opção 1 é encarregada por mostrar apenas a quantidade de carros que passaram em cada sinal.
