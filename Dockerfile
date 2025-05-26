FROM python:3.12-slim-bookworm

# Install packages with minimal overhead
RUN apt-get update && apt-get install -y --no-install-recommends \
    make \
    binutils-mips-linux-gnu \
    cpp-mips-linux-gnu \
    bchunk \
    p7zip-full \
    && apt-get autoremove -y \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

COPY requirements.txt /tmp/requirements.txt
RUN pip install --no-cache-dir -r /tmp/requirements.txt && rm /tmp/requirements.txt

WORKDIR /app
