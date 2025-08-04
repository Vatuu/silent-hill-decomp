FROM python:3.12-slim-bookworm
ARG USERNAME=user
ARG UID=1000
ARG GID=1000
# Install packages with minimal overhead
RUN apt-get update && apt-get install -y --no-install-recommends \
    make \
    gcc \
    binutils-mips-linux-gnu \
    cpp-mips-linux-gnu \
    bchunk \
    p7zip-full \
    progress \
    sudo \
    && apt-get autoremove -y \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* \
    && groupadd -g $GID $USERNAME \
    && useradd -m -u $UID -g $GID -s /bin/bash $USERNAME \
    && echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

COPY requirements.txt /tmp/requirements.txt
RUN pip install --no-cache-dir -r /tmp/requirements.txt && rm /tmp/requirements.txt

USER $USERNAME
WORKDIR /app
