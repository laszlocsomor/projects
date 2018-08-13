# Java iterators vs. C-style for loop performance

String array with 50M elements, 5 runs per iteration approach.

## Each element is `new String()`

|                 | Min    | Max    | Average  | Median   |
|---------------- |:------:|:------:|:--------:|:--------:|
| For-loop        | 100 ms | 129 ms | 105.7 ms | 102.5 ms |
| Iterators       | 97 ms  | 107 ms | 98.8 ms  | 98 ms    |
| Streams forEach | 101 ms | 144 ms | 105.8 ms | 101 ms   |

## Each element is `Integer.toString(index)`

|                 | Min    | Max    | Average  | Median   |
|---------------- |:------:|:------:|:--------:|:--------:|
| For-loop        | 219 ms | 238 ms | 222.3 ms | 220 ms   |
| Iterators       | 144 ms | 224 ms | 152.2 ms | 144 ms   |
| Streams forEach | 223 ms | 268 ms | 228.6 ms | 224 ms   |
