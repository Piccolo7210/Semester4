#!/bin/bash

# Function to process a single log file
process_log() {
  local log_file="$1"
  local date=${log_file##*/}  # Extract date from filename
  local user_count=$(awk '!seen[$0]++' "$log_file" | wc -l)  # Count unique users with awk
  # Update daily user counts and track min/max dates
  ((daily_counts[$date]=user_count))
  if [[ -z $min_date ]] || [[ $user_count -lt ${daily_counts[$min_date]} ]]; then
    min_date="$date"
  fi
  if [[ -z $max_date ]] || [[ $user_count -gt ${daily_counts[$max_date]} ]]; then
    max_date="$date"
  fi
}

# Initialize variables
declare -A daily_counts  # Associative array to store daily user counts
min_date=""
max_date=""

# Process all log files in the user_logs directory
for log_file in log-*.txt; do
  process_log "$log_file"
done

# Print the report
echo "** Login Summary Report **"
echo
echo "Total Unique Logins by Date:"
for date in "${!daily_counts[@]}"; do
  echo "  - $date: ${daily_counts[$date]}"
done

# Print max and min login dates
echo
echo "Date with Highest Logins: $max_date with ${daily_counts[$max_date]} users"
echo "Date with Lowest Logins: $min_date with ${daily_counts[$min_date]} users"

