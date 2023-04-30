# libreMCM

The goal of libreMCM (libre Multi Compartment Modelling) is to be a free (free as in freedom) software for carrying out deterministic and probabilistic modelling.

Please note that the program is still WIP.

## Planned features

- Tools for sensitivity analysis
- Integrated radioactive decay and reactions
- Probabilistic modelling
- Support for Ecolego's file format
- A lot more

## How to build

In order to build libreMCM on Linux, run the following commands
```shell
mkdir build
cd build/
cmake ..
make
```

## Quick start

1. In order to create a simulation, the following files are required: compartments.csv, compartments, bin and sim_params. Check the contents of the files from the tutorials folder in order to see, how they should created.
2. The main folder which contains the main.cpp file also contains a file called models_cfg. The directory containing the simulation files are listed in this file. The example file contains one of the tutorial simulations (solution to Lotka-Volterra equations). If multiple directories are added to the file, they will be executed one after another.
3. The result of the simulation will be writen to text files (named after the compartments) which will be located in the directorie(s) set in the model_cfg file.
