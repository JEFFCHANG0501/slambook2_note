FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive
ARG OPENCV_VERSION=4.x

RUN apt-get update && \
    apt-get install -y \
    build-essential \
    wget \
    unzip \
    git \
    libeigen3-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libepoxy-dev \
    python3-dev \
    libgtk2.0-dev \
    pkg-config && \
    rm -rf /var/lib/apt/lists/*

# install cmake-3.28.0 to match Sophus library
RUN wget https://github.com/Kitware/CMake/releases/download/v3.28.0/cmake-3.28.0-linux-x86_64.tar.gz && \
    tar -zxvf cmake-3.28.0-linux-x86_64.tar.gz -C /opt/ && \
    rm cmake-3.28.0-linux-x86_64.tar.gz

ENV PATH="/opt/cmake-3.28.0-linux-x86_64/bin:${PATH}"

# download opencv
RUN wget -O opencv.zip "https://github.com/opencv/opencv/archive/${OPENCV_VERSION}.zip" && \
    unzip opencv.zip && \
    rm opencv.zip && \
    mv "opencv-${OPENCV_VERSION}" opencv

# build and install opencv
WORKDIR /opencv
RUN mkdir build && cd build && \
    cmake .. && \
    make -j$(nproc) && \
    make install && \
    ldconfig
