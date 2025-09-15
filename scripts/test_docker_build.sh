#!/usr/bin/env bash
set -euo pipefail

# List of OS targets
MATRIX=("alpine" "archlinux" "debian" "fedora" "opensuse" "gentoo")

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

for OS in "${MATRIX[@]}"; do
  DOCKERFILE="Dockerfiles/${OS}"
  IMAGE_TAG="${REPO}:${OS}"

  if [[ ! -f "$DOCKERFILE" ]]; then
    echo "Skipping $OS (Dockerfile not found: $DOCKERFILE)"
    continue
  fi

  echo "Building image for $OS..."
  docker build --rm -t "$IMAGE_TAG" -f "$DOCKERFILE" .

  echo "Running test build for $OS..."
  CONTAINER_ID=$(docker run -d "$IMAGE_TAG" sleep infinity)

  # Create filtered tarball and copy
  tar --exclude='build' --exclude='cmake-build-*' --exclude='bin' --exclude='*.o' -czf ${TMP_DIR}/src.tar.gz .
  docker cp ${TMP_DIR}/src.tar.gz "$CONTAINER_ID":/tmp/
  docker exec "$CONTAINER_ID" sh -c "mkdir -p /src && tar -xzf /tmp/src.tar.gz -C /src"
  rm ${TMP_DIR}/src.tar.gz

  # Run test build inside container
  docker exec "$CONTAINER_ID" sh -c "cd /src && make"

  # Clean up
  docker rm -f "$CONTAINER_ID"

  echo "Test build succeeded for $OS"
done

echo "Done!"
