# port-scanner
a simple TCP port scanner written in C using POSIX sockets to identify open ports on IPv4 hosts

---

## Overview

* This project implements a basic TCP connect scanner that checks a specified range of ports on an IPv4 address.
* It attempts to establish a TCP connection to each port and reports the ports that accept connections.
* The project is built using standard C and POSIX networking APIs, without external libraries.

---

## Project Structure

```
port-scanner/
├── src/
│   └── portscan.c
├── Makefile
└── README.md
```

* ```src/portscan.c```: Contains the scanning logic, socket operations, input validation, and command line argument handling.
* ```Makefile```: Compiles the source code using clang with compiler warnings enabled.

---

## How it Works

1. Parse arguments: Accepts an IPv4 address and a starting and ending port.
2. Create a socket: Uses socket() to create a TCP socket for each port.
3. Configure the target: Uses inet_pton() to convert the IPv4 address and htons() to set the port in network byte order.
4. Attempt a connection: Calls connect() to check whether the target port accepts a TCP connection.
5. Report results: Displays ports where the connection succeeds and prints a summary when scanning finishes.
6. Close sockets: Releases each socket after the connection attempt.

**This is a basic sequential scanner. Ports that fail to connect are not necessarily closed, as firewalls and network errors can also prevent
connections.**

---

## Build and Run

### Build

```
make
```

### Run

```
./portscan <IPv4-address> <start-port> <end-port>
```
