#!/bin/bash

# Loop through each file in the maps directory
for map_file in maps/*; do
  # Check if it's a regular file
  if [ -f "$map_file" ]; then
    # Extract the filename
    filename=$(basename "$map_file")

    echo "Running so_long with: $filename"
    ./so_long "$map_file"

    # Print an empty line
    echo ""
  fi
done
