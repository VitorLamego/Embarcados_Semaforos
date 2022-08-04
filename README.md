## Servidor Central

O servidor central deve ser rodado na placa cujo Ip corresponde a: 164.41.98.26.

Caso o IP tenha sido alterado, o servidor central deve ser rodado na mesma placa que o Cruzamento 3 e 4. Sendo necessário a alteração do código que está como hardcode. Os arquivos que contém informações de IP, em todo o projeto, são:

```
cruzmento/src/cliente.c - Linha 21
cruzamento/src/variables.c - Linha 69 e 70 e Linha 93 e 94
servidor_central/src/cliente.c - Linha 47 a 50
```

Para correta execução do servidor central rode os seguintes comandos: 

```
cd trabalho1/servidor_central
make
bin/run
```

## Servidores Distribuídos

Para correta execução dos servidores distribuídos, primeiramente, substitua no código o endereço IP das placas, se necessário:

```
IPs atuais:

Cruzamento: 1 e 2 - 164.41.98.17
Cruzamento: 3 e 4 - 164.41.98.26
```

Substitua os ips, caso seja necessário e ainda não tenha sido feito na etapa do Servidor Central.

Rode os comandos:

```
cd trabalho1/cruzamentos
make
bin/run ${Número do cruzamento}
```

Sendo assim, para o ip com final .17 (placa com os cruzamentos 1 e 2) será rodado os seguintes comandos:

```
bin/run 1
bin/run 2
```

Para a placa com o ip com final .26 (placa com os cruzamentos 3 e 4), serão rodados os seguintes comandos:

```
bin/run 3
bin/run 4
```

## Observação

Os relatórios de infração e velocidade apenas são mostrados na seleção da opção 2 no menu. A opção 1 é encarregada por mostrar apenas a quantidade de carros que passaram em cada sinal.

É sugerido que seja pesquisado na raíz do projeto o endereço IP atualmente utilizado, como descrito acima, e mude todas as ocorrências para o novo endereço IP.
