#!/bin/bash

echo "Anzahl Knoten: $(head -n 1 $1)";
echo "Anzahl Kanten: $(wc -l < $1)"
