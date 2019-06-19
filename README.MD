# Dependencies

```sh
sudo apt-get update
sudo apt-get install -y zip make cmake g++ libjemalloc-dev libboost-dev libgoogle-glog-dev
```


# Dense data examples

```sh
./dense-gen --file dense-data.txt --n_points 100 --n_dimension 100 --type binary --bernoulli 0.9
./dense-gen --file dense-data.txt --n_points 100 --n_dimension 100 --type int --range_low 0 --range_high 100
./dense-gen --file dense-data.txt --n_points 100 --n_dimension 100 --type real --distribution uniform --range_low 0 --range_high 100
./dense-gen --file dense-data.txt --n_points 100 --n_dimension 100 --type real --distribution normal --mean 100 --stddev 10
```


# Sparse data examples

```sh
./sparse-gen --file sparse-data.txt --n_points 10000 --n_dimension 10000 --type binary --bernoulli 0.9 --sparsity 0.0001 --zipf 0.8
./sparse-gen --file sparse-data.txt --n_points 10000 --n_dimension 10000 --type int --range_low 0 --range_high 100 --sparsity 0.0001 --zipf 0.8
./sparse-gen --file sparse-data.txt --n_points 10000 --n_dimension 10000 --type real --distribution uniform --range_low 0 --range_high 100 --sparsity 0.0001 --zipf 0.8
./sparse-gen --file sparse-data.txt --n_points 10000 --n_dimension 10000 --type real --distribution normal --mean 100 --stddev 10 --sparsity 0.0001 --zipf 0.8
```