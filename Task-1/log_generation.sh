#!/bin/bash
LOG_FILE="system.log"

if [ ! -f "$LOG_FILE" ]; then
	touch '$LOG_FILE'
fi

echo "Timestamp, CPU Load, Memory Utilization(%), Task Counter, Sum of all PIDs, CPU Temperature" > "$LOG_FILE"

while true; do

	TIMESTAMP=$(date +'%d/%m/%y - %H:%M:%S')
	
	CPU_LOAD=$(awk '{print $1}' /proc/loadavg)
	
	MEM_UTIL=$(free -m | grep -i "mem" | awk '{printf "%.2f%%\n", $3/$2 * 100}')
	
	TASK_COUNTER=$(ps aux | wc -l)
	
	SUM_OF_PIDs=$(ps -eo pid | awk 'BEGIN {sum = 0} {sum += $1} END {print sum}')
	
	CPU_TEMP=$(cat /sys/class/thermal/thermal_zone*/temp | awk 'BEGIN {TEMP=0} {TEMP=$1} END {print TEMP}')

	echo "$TIMESTAMP, $CPU_LOAD, $MEM_UTIL, $TASK_COUNTER, $SUM_OF_PIDs, $CPU_TEMP" >> "$LOG_FILE"

	sleep 1
done


