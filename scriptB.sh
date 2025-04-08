#!/bin/bash

make_request() {
    echo "$(date) - Sending request"
    curl -s -X GET http://localhost/compute > /dev/null
    echo "$(date) - Request complete"
}

while true; do
    # Генеруємо випадкову кількість паралельних запитів (для створення навантаження)
    num_requests=$(shuf -i 1-3 -n 1)
    echo "Making $num_requests parallel requests"
    
    # Запускаємо запити паралельно
    for i in $(seq 1 $num_requests); do
        make_request &
    done
    
    # Випадкова пауза від 5 до 10 секунд
    sleep_time=$(shuf -i 5-10 -n 1)
    echo "Sleeping for $sleep_time seconds..."
    sleep $sleep_time
done
