FROM gcc:8

COPY . /monitoria

WORKDIR /monitoria/src/

RUN  gcc -o monitoria main.c -lpthread && \
    chmod +x monitoria
