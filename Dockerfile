FROM gcc:latest
COPY . .
RUN make
CMD ["./target.exe"]
