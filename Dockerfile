FROM ubuntu:18.10

WORKDIR /statix

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update; \
    apt-get install -y software-properties-common; \
    add-apt-repository ppa:apt-fast/stable; \
    apt-get -y install apt-fast;

RUN apt-fast install -y git cmake gcc-8 g++-8 libboost-all-dev; \
    update-alternatives --remove-all gcc; \
    update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 80 --slave /usr/bin/g++ g++ /usr/bin/g++-8;

COPY . .

WORKDIR /statix/build

RUN cmake -DCMAKE_BUILD_TYPE=Release .. && \
    cmake --build .

EXPOSE 80

CMD ./bin/StatiX
