# C++ Assembly Line & Order Processing Simulator

A **console-based C++17 academic project** that models the movement of customer orders through a configurable assembly line. Workstations fill order items when inventory is available, forward orders to the next station, and classify finished orders as complete or incomplete.

> **Academic sharing:** This repository is intended for **private portfolio storage** until the course's code-sharing and academic-integrity policy is confirmed. The assignment may include instructor-provided test/starter code. Review permissions before making any content public.

## Features

- Load workstation and inventory data from delimited text files.
- Load customer orders with multiple required items.
- Configure workstation links using `AssemblyLine.txt` and determine the initial station.
- Move orders through stations using `std::deque`, reference/pointer links, and C++ move semantics.
- Assign unique serial numbers to fulfilled items and reduce stock quantities.
- Route processed orders into completed and incomplete queues.
- Print order status, station information, and remaining inventory.

## Core C++ concepts

**C++17**, object-oriented design, inheritance (`Workstation` inherits from `Station`), dynamic memory management, move construction/assignment, `std::vector`, `std::deque`, standard algorithms (`std::find_if`), file streams, parsing delimited text, and input/output formatting.

## Main modules

| File | Purpose |
|---|---|
| `Station.*` | Stores inventory item information, quantities, and serial numbers |
| `Workstation.*` | Processes queued orders and passes them to the next workstation |
| `CustomerOrder.*` | Represents customer orders and tracks which requested items are filled |
| `LineManager.*` | Constructs the station chain and coordinates processing iterations |
| `Utilities.*` | Tokenizes delimited records and tracks field widths |
| `tester_3.cpp` | Course assignment test driver / program entry point |

## Build and run

From a terminal **in this folder**, use a C++17 compiler such as `clang++` on macOS or `g++` on Linux:

```bash
clang++ -std=c++17 -Wall -Wextra -pedantic \
  tester_3.cpp CustomerOrder.cpp LineManager.cpp Station.cpp \
  Utilities.cpp Workstation.cpp -o assembly-simulator

./assembly-simulator Stations1.txt Stations2.txt CustomerOrders.txt AssemblyLine.txt
```

Use `g++` instead of `clang++` if needed. Input files must be accessible from your current working directory.

## Example test results

For the included sample data, the program processed **5 customer orders** in **18 iterations**: **3 completed** and **2 incomplete** (some requested products ran out of stock). These results were observed in a local run of the supplied test driver, not an exhaustive test suite.

## Notes

- This was created as a **Seneca academic assignment**, presented here as a technical project for professional portfolio purposes.
- The primary source code was retained; only personal identification in file headers was removed in this copy.
- `tester_3.cpp` and any instructor-provided source must be reviewed against course redistribution rules before public release.
- Generated binaries and macOS debug bundles are excluded via `.gitignore`.
