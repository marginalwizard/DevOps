#!/bin/bash

srv1_busy_count=0
srv2_busy_count=0
srv2_idle_count=0
srv3_idle_count=0

# Перевірка завантаження CPU
check_cpu_usage() {
    local container=$1
    docker stats --no-stream $container | grep $container | awk '{print $3}' | sed 's/%//'
}

start_container() {
    local name=$1
    local cpu=$2
    echo "Starting $name on CPU #$cpu"
    docker run --name $name -d --cpuset-cpus $cpu --entrypoint="" svitlana023/warlock-server /bin/sh -c "cd /home/warlock-host && chmod +x series && echo '2' | ./series"
}

container_exists() {
    docker ps -a | grep -q "$1"
    return $?
}

container_running() {
    docker ps | grep -q "$1"
    return $?
}

stop_container() {
    local name=$1
    echo "Stopping $name..."
    docker kill --signal=SIGINT $name
    docker wait $name
    docker rm $name
    echo "$name removed"
}

if ! container_running srv1; then
    start_container srv1 0
fi

while true; do
    date
    echo "Checking containers load..."
    
    # Перевіряємо завантаження srv1
    if container_running srv1; then
        srv1_usage=$(check_cpu_usage srv1)
        echo "srv1 CPU usage: $srv1_usage%"
        
        # Якщо srv1 завантажений більше 60% протягом 2 хвилин, запускаємо srv2
        if (( $(echo "$srv1_usage > 60" | bc -l) )); then
            srv1_busy_count=$((srv1_busy_count + 1))
            echo "srv1 is busy: count=$srv1_busy_count"
            
            if [ $srv1_busy_count -ge 4 ] && ! container_running srv2; then
                start_container srv2 1
                srv1_busy_count=0
            fi
        else
            srv1_busy_count=0
        fi
    fi
    
    # Перевіряємо завантаження srv2 (якщо запущений)
    if container_running srv2; then
        srv2_usage=$(check_cpu_usage srv2)
        echo "srv2 CPU usage: $srv2_usage%"
        
        # Якщо srv2 завантажений більше 60% протягом 2 хвилин, запускаємо srv3
        if (( $(echo "$srv2_usage > 60" | bc -l) )); then
            srv2_busy_count=$((srv2_busy_count + 1))
            echo "srv2 is busy: count=$srv2_busy_count"
            srv2_idle_count=0
            
            if [ $srv2_busy_count -ge 4 ] && ! container_running srv3; then
                start_container srv3 2
                srv2_busy_count=0
            fi
        else
            srv2_busy_count=0
            
            # Перевіряємо простій srv2
            srv2_idle_count=$((srv2_idle_count + 1))
            echo "srv2 is idle: count=$srv2_idle_count"
            
            # Якщо srv2 простоює протягом 2 хвилин, зупиняємо його
            if [ $srv2_idle_count -ge 4 ]; then
                stop_container srv2
                srv2_idle_count=0
            fi
        fi
    fi
    
    # Перевіряємо srv3 (якщо запущений)
    if container_running srv3; then
        srv3_usage=$(check_cpu_usage srv3)
        echo "srv3 CPU usage: $srv3_usage%"
        
        # Перевіряємо простій srv3
        if (( $(echo "$srv3_usage < 10" | bc -l) )); then
            srv3_idle_count=$((srv3_idle_count + 1))
            echo "srv3 is idle: count=$srv3_idle_count"
            
            # Якщо srv3 простоює протягом 2 хвилин, зупиняємо його
            if [ $srv3_idle_count -ge 4 ]; then
                stop_container srv3
                srv3_idle_count=0
            fi
        else
            srv3_idle_count=0
        fi
    fi
    
    # Перевірка наявності оновлень образу
    echo "Checking for image updates..."
    pullResult=$(docker pull svitlana023/warlock-server | grep "Downloaded newer image")
    
    if [ -n "$pullResult" ]; then
        echo "New image available, updating containers..."
        
        # Оновлюємо контейнери послідовно, щоб хоча б один був доступний
        
        # Оновлюємо srv3 якщо існує
        if container_running srv3; then
            stop_container srv3
            start_container srv3 2
        fi
        
        # Оновлюємо srv2 якщо існує
        if container_running srv2; then
            stop_container srv2
            start_container srv2 1
        fi
        
        # Оновлюємо srv1 останнім
        if container_running srv1; then
            stop_container srv1
            start_container srv1 0
        fi
    fi
    
    sleep 30  # Перевіряємо кожні 30 секунд (4 періоди = 2 хвилини)
done
