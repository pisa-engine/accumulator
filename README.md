# Accumulator

Benchmarking several score accumulators used in IR.


|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |     total | Clear
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|----------:|:------
|           16,707.63 |           59,852.90 |    0.5% |           27.00 |       56,650.86 |  0.000 |      0.00 | `Clear Simple accumulator of size 2^{16}`
|           66,990.24 |           14,927.55 |    0.4% |           27.01 |      227,135.09 |  0.000 |      0.00 | `Clear Simple accumulator of size 2^{18}`
|          308,432.72 |            3,242.20 |    0.1% |           27.07 |    1,044,588.31 |  0.000 |      0.00 | `Clear Simple accumulator of size 2^{20}`
|       11,450,716.33 |               87.33 |    0.0% |           29.90 |   38,743,455.15 |  0.000 |      0.13 | `Clear Simple accumulator of size 2^{25}`
|                4.32 |      231,538,736.79 |    1.1% |           42.00 |           14.64 |  2.868 |      0.00 | `Clear Paged accumulator of size 2^{16}`
|                6.19 |      161,435,836.45 |    0.0% |           56.00 |           21.00 |  2.666 |      0.00 | `Clear Paged accumulator of size 2^{18}`
|               10.93 |       91,521,611.34 |    0.1% |           84.00 |           37.05 |  2.267 |      0.00 | `Clear Paged accumulator of size 2^{20}`
|              156.03 |        6,409,033.47 |    0.0% |           24.00 |          529.04 |  0.045 |      0.00 | `Clear Paged accumulator of size 2^{25}`
|                4.26 |      234,760,790.84 |    0.6% |           42.00 |           14.43 |  2.911 |      0.00 | `Clear MaxBlock accumulator of size 2^{16}`
|                6.20 |      161,338,627.17 |    0.0% |           56.00 |           21.02 |  2.665 |      0.00 | `Clear MaxBlock accumulator of size 2^{18}`
|               10.92 |       91,549,612.54 |    0.1% |           84.00 |           37.04 |  2.268 |      0.00 | `Clear MaxBlock accumulator of size 2^{20}`
|               82.00 |       12,195,431.55 |    0.0% |           24.00 |          278.02 |  0.086 |      0.00 | `Clear MaxBlock accumulator of size 2^{25}`

|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |     total | Accumulate
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|----------:|:-----------
|           48,013.24 |           20,827.59 |    0.0% |       52,430.98 |      162,710.40 |  0.322 |      0.00 | `Accumulate elements in Simple accumulator of size 2^{20} and ratio 1%`
|          488,130.93 |            2,048.63 |    0.0% |      524,291.10 |    1,654,351.05 |  0.317 |      0.01 | `Accumulate elements in Simple accumulator of size 2^{20} and ratio 10%`
|        2,714,464.21 |              368.40 |    0.0% |    2,621,446.65 |    9,185,893.23 |  0.285 |      0.03 | `Accumulate elements in Simple accumulator of size 2^{20} and ratio 50%`
|        4,379,916.16 |              228.31 |    0.0% |    4,194,307.07 |   14,821,676.46 |  0.283 |      0.05 | `Accumulate elements in Simple accumulator of size 2^{20} and ratio 80%`
|        5,714,204.50 |              175.00 |    0.1% |    5,242,887.41 |   19,334,857.76 |  0.271 |      0.06 | `Accumulate elements in Simple accumulator of size 2^{20} and ratio 100%`
|           46,300.51 |           21,598.03 |    0.0% |      125,827.99 |      156,937.64 |  0.802 |      0.00 | `Accumulate elements in Paged accumulator of size 2^{20} and ratio 1%`
|          465,474.98 |            2,148.34 |    0.0% |    1,258,292.10 |    1,577,474.80 |  0.798 |      0.01 | `Accumulate elements in Paged accumulator of size 2^{20} and ratio 10%`
|        2,663,509.48 |              375.44 |    0.1% |    6,291,464.65 |    9,012,103.87 |  0.698 |      0.03 | `Accumulate elements in Paged accumulator of size 2^{20} and ratio 50%`
|        4,426,454.60 |              225.91 |    0.1% |   10,066,329.10 |   14,977,551.94 |  0.672 |      0.05 | `Accumulate elements in Paged accumulator of size 2^{20} and ratio 80%`
|        5,556,884.88 |              179.96 |    0.0% |   12,582,921.39 |   18,801,878.62 |  0.669 |      0.06 | `Accumulate elements in Paged accumulator of size 2^{20} and ratio 100%`
|          123,418.90 |            8,102.49 |    0.0% |      178,256.03 |      418,382.56 |  0.426 |      0.00 | `Accumulate elements in MaxBlock accumulator of size 2^{20} and ratio 1%`
|        1,247,847.19 |              801.38 |    0.0% |    1,782,580.32 |    4,229,252.95 |  0.421 |      0.01 | `Accumulate elements in MaxBlock accumulator of size 2^{20} and ratio 10%`
|        6,658,265.82 |              150.19 |    0.0% |    8,912,908.68 |   22,538,015.57 |  0.395 |      0.07 | `Accumulate elements in MaxBlock accumulator of size 2^{20} and ratio 50%`
|       10,677,917.93 |               93.65 |    0.0% |   14,260,633.70 |   36,141,447.42 |  0.395 |      0.12 | `Accumulate elements in MaxBlock accumulator of size 2^{20} and ratio 80%`
|       13,314,001.91 |               75.11 |    0.0% |   17,825,806.37 |   45,064,937.83 |  0.396 |      0.15 | `Accumulate elements in MaxBlock accumulator of size 2^{20} and ratio 100%`
|           68,249.12 |           14,652.20 |    0.0% |      104,855.99 |      231,330.92 |  0.453 |      0.00 | `Accumulate elements in Counter accumulator of size 2^{20} and ratio 1%`
|          689,449.68 |            1,450.43 |    0.0% |    1,048,576.15 |    2,335,804.13 |  0.449 |      0.01 | `Accumulate elements in Counter accumulator of size 2^{20} and ratio 10%`
|        3,862,844.95 |              258.88 |    0.1% |    5,242,886.94 |   13,070,969.80 |  0.401 |      0.04 | `Accumulate elements in Counter accumulator of size 2^{20} and ratio 50%`
|        6,215,171.22 |              160.90 |    0.0% |    8,388,607.53 |   21,031,096.17 |  0.399 |      0.07 | `Accumulate elements in Counter accumulator of size 2^{20} and ratio 80%`
|        7,745,109.44 |              129.11 |    0.1% |   10,485,767.93 |   26,209,442.26 |  0.400 |      0.09 | `Accumulate elements in Counter accumulator of size 2^{20} and ratio 100%`

|               ns/op |                op/s |    err% |          ins/op |          cyc/op |    IPC |     total | Aggregate
|--------------------:|--------------------:|--------:|----------------:|----------------:|-------:|----------:|:----------
|       18,863,243.09 |               53.01 |    0.2% |  134,217,737.00 |   63,828,354.55 |  2.103 |      0.21 | `Aggregate elements in Simple accumulator of size 2^{25} and ratio 1%`
|       18,834,688.00 |               53.09 |    0.1% |  134,217,737.00 |   63,738,548.18 |  2.106 |      0.21 | `Aggregate elements in Simple accumulator of size 2^{25} and ratio 10%`
|       18,764,642.27 |               53.29 |    0.2% |  134,217,737.00 |   63,518,806.18 |  2.113 |      0.21 | `Aggregate elements in Simple accumulator of size 2^{25} and ratio 50%`
|       18,770,896.45 |               53.27 |    0.2% |  134,217,737.00 |   63,534,409.09 |  2.113 |      0.21 | `Aggregate elements in Simple accumulator of size 2^{25} and ratio 80%`
|       18,753,186.90 |               53.32 |    0.1% |  134,217,737.00 |   63,475,344.60 |  2.114 |      0.21 | `Aggregate elements in Simple accumulator of size 2^{25} and ratio 100%`
|       19,351,353.70 |               51.68 |    0.1% |  167,976,974.64 |   65,492,874.00 |  2.565 |      0.21 | `Aggregate elements in Paged accumulator of size 2^{25} and ratio 1%`
|       19,319,371.30 |               51.76 |    0.1% |  167,976,974.64 |   65,377,354.36 |  2.569 |      0.21 | `Aggregate elements in Paged accumulator of size 2^{25} and ratio 10%`
|       19,266,497.82 |               51.90 |    0.1% |  167,976,974.64 |   65,217,248.36 |  2.576 |      0.21 | `Aggregate elements in Paged accumulator of size 2^{25} and ratio 50%`
|       19,038,713.20 |               52.52 |    0.4% |  167,976,974.64 |   64,449,553.40 |  2.606 |      0.21 | `Aggregate elements in Paged accumulator of size 2^{25} and ratio 80%`
|       19,224,789.91 |               52.02 |    0.1% |  167,976,974.64 |   65,073,694.18 |  2.581 |      0.21 | `Aggregate elements in Paged accumulator of size 2^{25} and ratio 100%`
|            7,670.36 |          130,371.92 |    0.0% |      102,423.64 |       26,013.09 |  3.937 |      0.00 | `Aggregate elements in MaxBlock accumulator of size 2^{25} and ratio 1%`
|            7,670.90 |          130,362.80 |    0.0% |      102,423.64 |       26,013.09 |  3.937 |      0.00 | `Aggregate elements in MaxBlock accumulator of size 2^{25} and ratio 10%`
|            7,670.64 |          130,367.28 |    0.0% |      102,423.64 |       26,013.09 |  3.937 |      0.00 | `Aggregate elements in MaxBlock accumulator of size 2^{25} and ratio 50%`
|            7,671.45 |          130,353.38 |    0.0% |      102,423.64 |       26,019.27 |  3.936 |      0.00 | `Aggregate elements in MaxBlock accumulator of size 2^{25} and ratio 80%`
|            7,670.73 |          130,365.74 |    0.0% |      102,423.64 |       26,013.40 |  3.937 |      0.00 | `Aggregate elements in MaxBlock accumulator of size 2^{25} and ratio 100%`
|       24,381,731.73 |               41.01 |    0.1% |  234,881,041.91 |   82,507,361.09 |  2.847 |      0.27 | `Aggregate elements in Counter accumulator of size 2^{25} and ratio 1%`
|       24,410,149.00 |               40.97 |    0.1% |  234,881,041.91 |   82,605,203.20 |  2.843 |      0.27 | `Aggregate elements in Counter accumulator of size 2^{25} and ratio 10%`
|       24,970,166.82 |               40.05 |    0.1% |  234,881,042.09 |   84,514,164.73 |  2.779 |      0.27 | `Aggregate elements in Counter accumulator of size 2^{25} and ratio 50%`
|       24,711,991.64 |               40.47 |    0.2% |  234,881,042.09 |   83,622,499.27 |  2.809 |      0.27 | `Aggregate elements in Counter accumulator of size 2^{25} and ratio 80%`
|       24,820,492.00 |               40.29 |    0.1% |  234,881,042.09 |   84,003,589.82 |  2.796 |      0.27 | `Aggregate elements in Counter accumulator of size 2^{25} and ratio 100%`
