FROM ubuntu:xenial
MAINTAINER Florian Weik <fweik@icp.uni-stuttgart.de>
ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update && apt-get install -y \
	apt-utils \
	cmake \
	build-essential \
	openmpi-bin \
	libfftw3-dev \
	libboost-dev libboost-serialization-dev libboost-mpi-dev libboost-filesystem-dev libboost-test-dev \
	cython python python-numpy \
	tcl-dev \
	git \
	pep8 \
	python-pyvtk \
&& apt-get clean \
&& rm -rf /var/lib/apt/lists/*

RUN useradd -m espresso
USER espresso
WORKDIR /home/espresso

