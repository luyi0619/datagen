FROM ubuntu:latest
RUN apt-get -y update && apt-get install -y zip git make cmake g++ libjemalloc-dev libboost-dev libgoogle-glog-dev
RUN git clone https://github.com/luyi0619/datagen.git
RUN cd datagen && ./compile.sh
