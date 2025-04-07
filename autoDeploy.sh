#!/bin/bash

while true
do
    date
    echo "Checking newer image on the server"
    
    pullResult=$(docker pull svitlana023/warlock-server | grep "Downloaded newer image")
    
    if [ -n "$pullResult" ]; then
        echo $pullResult
        echo "Newer image downloaded"
        echo "Restarting srv1"
        echo "    sending SIGINT to srv1"
        docker kill --signal=SIGINT srv1
        echo "    waiting for server to terminate"
        docker wait srv1
        echo "    starting new server"
        docker run --name srv1 --rm -d --cpuset-cpus 0 --entrypoint="" svitlana023/warlock-server /bin/sh -c "cd /home/warlock-host && chmod +x series && echo '2' | ./series"
        echo "Done"
    else
        echo "Image is up to date"
    fi
    
    sleep 10
done
