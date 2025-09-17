#!/usr/bin/env bash
set -euo pipefail

# Repository name (local test images)
REPO="bongocat-test"

# Check if Docker login is needed
if ! docker info >/dev/null 2>&1; then
  echo "Docker does not seem to be running. Please start Docker."
  exit 1
fi

echo "Docker is running"

TMP_DIR=$(mktemp -d)
trap 'rm -rf "$TMP_DIR"' EXIT

DOCKERFILE="Dockerfiles/nix-test"
IMAGE_TAG="${REPO}:nix-test"

if [[ ! -f "$DOCKERFILE" ]]; then
  echo "Skipping $OS (Dockerfile not found: $DOCKERFILE)"
  continue
fi

echo "Building image for nix..."
docker build --rm -t "$IMAGE_TAG" -f "$DOCKERFILE" .

echo "Running test build for nix..."
CONTAINER_ID=$(docker run -d "$IMAGE_TAG" sleep infinity)

# Create filtered tarball and copy
tar --exclude='build' --exclude='cmake-build-*' --exclude='bin' --exclude='*.o' -czf ${TMP_DIR}/src.tar.gz .
docker cp ${TMP_DIR}/src.tar.gz "$CONTAINER_ID":/tmp/
docker exec "$CONTAINER_ID" sh -c "mkdir -p /home/nixuser/src && tar -xzf /tmp/src.tar.gz -C /home/nixuser/src"
rm ${TMP_DIR}/src.tar.gz

# Run test build inside container
docker exec "$CONTAINER_ID" sh -c "
  cd /home/nixuser/src/;
  . /home/nixuser/.nix-profile/etc/profile.d/nix.sh;
  nix flake show;
  nix flake check --print-build-logs;
  nix build --print-build-logs
"

# Clean up
docker rm -f "$CONTAINER_ID"

echo "Done!"
