#!/usr/bin/bash

dir="$1"
for f in "$dir"/*.zip; do
    if [ -f "$f" ]; then
        echo "$f"
    fi
done