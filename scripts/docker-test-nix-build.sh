#!/bin/bash

docker build -t bongocat-test-nixos -f ./scripts/Dockerfile.test-nixos .
docker run --rm bongocat-test-nixos
