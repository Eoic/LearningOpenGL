#!/bin/sh

# Version declarations.
GLEW_VERSION=2.2.0
GLFW_VERSION=3.4

# URLs.
GLEW_URL="https://github.com/nigels-com/glew/releases/download/glew-${GLEW_VERSION}/glew-${GLEW_VERSION}.zip"
GLFW_URL="https://github.com/glfw/glfw/releases/download/${GLFW_VERSION}/glfw-${GLFW_VERSION}.zip"

# Create a vendor directory if it doesn't exist.
mkdir -p vendor

# Change to the vendor directory.
cd vendor || { echo "Failed to enter vendor directory."; exit 1; }

# Function to download and unzip files.
download_and_unzip() {
    local url=$1
    local output_name=$2
    local version=$3
    
    echo "Downloading ${output_name}..."
    curl -fLo "${output_name}.zip" "${url}"
    
    if [ $? -ne 0 ]; then
        echo "Error: failed to download ${output_name}. Exiting."
        exit 1
    fi
    
    echo "Unzipping ${output_name}..."
    unzip -q "${output_name}.zip" && rm "${output_name}.zip"
    
    if [ $? -ne 0 ]; then
        echo "Error: failed to unzip ${output_name}. Exiting."
        exit 1
    fi
    
    # Ask for confirmation if dependency already exists.
    if [ -d "${output_name}" ]; then
        echo "${output_name} directory already exists."
        read -p "Do you want to overwrite it? (y/N) " choice
        
        case "$choice" in
            y|Y ) echo "Overwriting ${output_name}...";;
            * ) echo "Skipping ${output_name} download."; rm -rf "${output_name}-${version}"; return;;
        esac
        
        rm -rf "${output_name}"
    fi
    
    mv "${output_name}-${version}" "${output_name}"
    
    if [ $? -ne 0 ]; then
        echo "Error: failed to rename ${output_name}-${version}. Exiting."
        exit 1
    fi
    
    echo "${output_name} downloaded and unzipped successfully."
}

# Check for required tools.
command -v curl >/dev/null 2>&1 || { echo >&2 "curl is required but it's not installed. Aborting."; exit 1; }
command -v unzip >/dev/null 2>&1 || { echo >&2 "unzip is required but it's not installed. Aborting."; exit 1; }

# Acquire sources.
download_and_unzip "$GLEW_URL" "glew" "$GLEW_VERSION"
download_and_unzip "$GLFW_URL" "glfw" "$GLFW_VERSION"