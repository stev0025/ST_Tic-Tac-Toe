# Use Ubuntu as the base image
FROM ubuntu:latest

# Install development tools and applications
RUN apt-get update && apt-get install -y \
    make gcc libc-dev git bash vim \
    && rm -rf /var/lib/apt/lists/* \
    && update-alternatives --set editor /usr/bin/vim.basic

# Set a working directory
WORKDIR /workspace

# Copy your project directory into the Docker image
COPY . .

# Add your custom bash prompt setup
RUN echo "function parse_git_branch {" > /root/.bashrc && \
    echo "    git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'" >> /root/.bashrc && \
    echo "}" >> /root/.bashrc && \
    echo "export PS1=\"\\u@\\h \\[\\033[32m\\]\\w\\[\\033[33m\\]\\$(parse_git_branch)\\[\\033[00m\\] $ \"" >> /root/.bashrc

# Keep the container running, so developers can exec into it
CMD ["tail", "-f", "/dev/null"]
