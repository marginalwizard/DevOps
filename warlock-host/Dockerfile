FROM alpine AS build
RUN apk add --no-cache build-base automake autoconf git
WORKDIR /home/warlock-host
RUN git clone -b branchHTTPserver https://github.com/marginalwizard/DevOps.git .
RUN autoreconf -fi
RUN ./configure && \
    sed -i 's/LDFLAGS =/LDFLAGS = -static/g' Makefile && \
    make

FROM alpine
WORKDIR /home/warlock-host
COPY --from=build /home/warlock-host/series .
COPY --from=build /home/warlock-host/start-server.sh .
RUN chmod +x ./start-server.sh
ENTRYPOINT ["./start-server.sh"]
