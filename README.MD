Dense and Sparse Data Generator
=

[![Build Status](https://travis-ci.org/luyi0619/datagen.svg?branch=master)](https://travis-ci.org/luyi0619/datagen)

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
./dense-gen --file dense-data.txt --n_points 100 --n_dimension 100 --type real --distribution gamma --alpha 2 --beta 2
./dense-gen --file dense-data.txt --n_points 100 --n_dimension 100 --type real --distribution weibull --a 2 --b 4
```

# Sparse data examples

```sh
./sparse-gen --file sparse-data.txt --n_points 10000 --n_dimension 10000 --type binary --bernoulli 0.9 --sparsity 0.0001 --zipf 0.8 --format dok
./sparse-gen --file sparse-data.txt --n_points 10000 --n_dimension 10000 --type int --range_low 0 --range_high 100 --sparsity 0.0001 --zipf 0.8 --format dok
./sparse-gen --file sparse-data.txt --n_points 10000 --n_dimension 10000 --type real --distribution uniform --range_low 0 --range_high 100 --sparsity 0.0001 --zipf 0.8 --format dok
./sparse-gen --file sparse-data.txt --n_points 10000 --n_dimension 10000 --type real --distribution normal --mean 100 --stddev 10 --sparsity 0.0001 --zipf 0.8 --format dok
./sparse-gen --file sparse-data.txt --n_points 100 --n_dimension 100 --type real --distribution normal --mean 100 --stddev 10 --sparsity 0.1 --zipf 0.8 --format dense
./sparse-gen --file sparse-data.txt --n_points 100 --n_dimension 100 --type real --distribution normal --mean 100 --stddev 10 --sparsity 0.1 --zipf 0.0 --format line --row_uncertainty 0.2
./sparse-gen --file sparse-data.txt --n_points 100 --n_dimension 100 --type real --distribution gamma --alpha 2 --beta 2 --sparsity 0.1 --zipf 0.0 --format line --row_uncertainty 0.2
./sparse-gen --file sparse-data.txt --n_points 100 --n_dimension 100 --type real --distribution weibull --a 2 --b 4 --sparsity 0.1 --zipf 0.0 --format line --row_uncertainty 0.2
```

# Deploy data generator using Docker

```sh
# See https://www.docker.com for Docker installation
git clone https://github.com/luyi0619/datagen.git
cd datagen
docker build -t datagen .
docker run --rm -ti -v $local_path_to_data_files:/data datagen /bin/bash
cd /datagen
# run commands above
```