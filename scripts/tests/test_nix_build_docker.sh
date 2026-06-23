#!/usr/bin/env bash
set -euo pipefail

docker build -f Dockerfiles/nix-test -t bongocat-nix-test .
docker run --rm bongocat-nix-test