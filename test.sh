#!/bin/sh

test_number="$1"
input_file="test/${test_number}.in"
output_file="test/${test_number}.ans"

./run.sh <"$input_file" >"$output_file"
