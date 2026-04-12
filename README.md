# multiplex-management-system

Terminal-based cinema management system handling movies, screenings, seat booking, and ticket sales.

## About

A menu-driven C++ application that simulates the full operation of a multiplex cinema: managing movie listings, scheduling screenings, selecting seats, processing ticket sales, and tracking customers. The system renders an ASCII seat map in the terminal, distinguishing preferential and general rows, and marks reserved seats in real-time.

Built as the final project for the Algorithmic Thinking course (2016-1) in the Electronics Engineering program at Pontificia Universidad Javeriana, Bogota.

The original code targeted Windows with `conio.h` and `system("CLS")`. A cross-platform `compat.h` shim was added to compile on POSIX systems using `termios`.

## Stack

| Component | Detail |
|---|---|
| Language | C++ |
| Data model | Structs for rooms, seats (200x200 grid), movies, screenings |
| Persistence | File-based I/O (sales and attendance arrays) |
| UI | Console menu with ASCII seat map rendering |
| Platform shim | `compat.h` (POSIX `termios` / Windows `conio.h`) |
| Build | Single-file compilation with g++ |

## How to Build / Run

```bash
g++ -o multiplex main.cpp
./multiplex
```

Navigate through the terminal menus to:

- Configure screening rooms (preferential rows, general rows, columns)
- Add and list movies with showtimes
- View the seat map and reserve seats
- Process ticket sales and track attendance

## License

GPL-3.0
