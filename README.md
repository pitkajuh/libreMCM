# libreMCM

libreMCM (libre Multi Compartment Modelling) is a free software for carrying out deterministic and probabilistic modelling.

Please note that the program is still WIP.

## Planned features

- Tools for sensitivity analysis
- Integrated radioactive decay and reactions
- Probabilistic modelling
- A lot more

## How to build

In order to build libreMCM on Linux, run the following commands

```shell
mkdir build
cd build/
cmake -DCMAKE_BUILD_TYPE=RELEASE ../libreMCM
make
```

## How to use

Run Lotka-Volterra simulation and plot the results

```shell
./main tutorials/lotka-volterra/
python3 tutorials/lotka-volterra/plot_results.py
```
