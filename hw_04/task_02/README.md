граф в файле `adj_graph.txt`. из лекции. где:
```
1я вершина - Иван
2. Стрела
3. Лягушка
4. Кожа
5. Яга
6. Василиса
7. Лебедь
8. Кощей
```
команда для запуска:
```sh
gcc -fopenmp pagerank.c 
./a.out
```
вывод:
```
Page rank:
 0: 0.018750 
 1: 0.021938 
 2: 0.040584 
 3: 0.033252 
 4: 0.018750 
 5: 0.053247
 6: 0.064010
 7: 0.079533
sum: 0.330064
```
Page rank максимален у Кощея - `0.079533`
