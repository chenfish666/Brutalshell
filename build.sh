#!/usr/env bash

uv sync
uv build

cd wrapper || exit 1
cmake -B build
cmake --build build --config RELEASE || echo "Wrapper build failed, continuing..."
cd .. || exit 1

cd helper || exit 1
cmake -B build
cmake --build build --config RELEASE || echo "Helper build failed, continuing..."
cd .. || exit 1

echo "Build completed."