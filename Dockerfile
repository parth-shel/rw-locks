FROM gcc:latest
COPY . /bin
WORKDIR /bin
RUN make
CMD ["/bin/target.exe"]
