FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    wget \
    git \
    libeigen3-dev && \
    rm -rf /var/lib/apt/lists/*

# install cmake-3.28.0 to match Sophus library
RUN wget https://github.com/Kitware/CMake/releases/download/v3.28.0/cmake-3.28.0-linux-x86_64.tar.gz && \
    tar -zxvf cmake-3.28.0-linux-x86_64.tar.gz -C /opt/ && \
    rm cmake-3.28.0-linux-x86_64.tar.gz

ENV PATH="/opt/cmake-3.28.0-linux-x86_64/bin:${PATH}"