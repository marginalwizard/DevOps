FROM alpine
WORKDIR /home/warlock-host
COPY ./series .
COPY ./start-server.sh .
RUN apk add libstdc++
RUN apk add libc6-compat
RUN chmod +x ./start-server.sh
ENTRYPOINT ["./start-server.sh"]
