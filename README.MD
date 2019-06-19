# Dense data examples

```sh
./dense-gen --file dense-data.txt --n_points 100 --n_dimension 100 --type binary --bernoulli 0.9
./dense-gen --file dense-data.txt --n_points 100 --n_dimension 100 --type int --range_low 0 --range_high 100
./dense-gen --file dense-data.txt --n_points 100 --n_dimension 100 --type real --distribution uniform --range_low 0 --range_high 100
./dense-gen --file dense-data.txt --n_points 100 --n_dimension 100 --type real --distribution normal --mean 100 --stddev 10
```