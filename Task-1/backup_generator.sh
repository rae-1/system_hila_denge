#!/bin/bash

LOG_FILE='system.log'
BACKUP_DIR='backup_system_log'
INTERVAL=''

mkdir -p "$BACKUP_DIR"

create_backup()
{
	END_TIME=$(date +'%y%m%d-%H%M%S')
	BACKUP_FILE_PATH="./$BACKUP_DIR/bak-system-$START_TIME-$END_TIME.tar.gz"

	tar -czf "$BACKUP_FILE_PATH" "$LOG_FILE"
}

# Extracting the flag-
# https://stackoverflow.com/questions/7069682/how-to-get-arguments-with-flags-in-bash
case "$1" in
	--prod)
		INTERVAL=300
		;;
	--test)
		INTERVAL=10
		;;
	*)
		echo "use flag --prod for production or --test for testing."
		exit 1
		;;
esac

while true; do
	START_TIME=$(date +'%y%m%d-%H%M%S')
	create_backup
	sleep "$INTERVAL"
done
