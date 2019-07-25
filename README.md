# Drone

## RRT

Heuristic bi-direction star RRT algorithm.

### Dependencies

- C++: gRPC (newest version, aka CORE_VERSION = 7.0.0, CPP_VERSION = 1.22.0)
- Python3
    - numpy
    - Rtree
    - plotly 
    - grpcio

### Usage

1. set `ROUTE_ALGORITHM` in `config.ini` as `RRTRPC`
2. start RRT server: `python route_guide_server.py`
3. start V-REP
4. start Planning program
