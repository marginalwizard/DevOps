#!/bin/bash

make_request() {
    local id=$1
    echo "$(date) - Request #$id sent"
    curl -s -X GET --max-time 180 --retry 2 --retry-delay 5 http://localhost/compute > /dev/null
    local status=$?
    echo "$(date) - Request #$id completed (status: $status)"
}

echo "Running the overlay scenario..."

run_request_cycle() {
    local thread_id=$1
    local base_interval=$2
    
    while true; do
        make_request $thread_id
        
        # випадковий інтервал навколо базового значення
        local variation=$(( RANDOM % 4 - 2 ))
        local sleep_time=$(( base_interval + variation ))
        echo "Stream #$thread_id: waiting $sleep_time seconds..."
        sleep $sleep_time
    done
}

# 3 постійних потоки запитів з різними інтервалами
run_request_cycle 1 10 &
sleep 2
run_request_cycle 2 12 &
sleep 2
run_request_cycle 3 11 &


# періодично "хвилі" додаткових запитів
while true; do
    sleep_time=$(shuf -i 30-60 -n 1)
    echo "Waiting $sleep_time seconds before the next wave of requests..."
    sleep $sleep_time
    
    echo "Starting a wave of additional requests..."
    make_request "wave" &
    sleep 1
    make_request "wave" &
    sleep 1
    make_request "wave" &
done
