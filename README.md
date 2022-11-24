# libreMCM

The goal of libreMCM (libre Multi Compartment Modelling) is to be a free (free as in freedom) software for modelling the transfer of radionuclides.

## Quick start

1. Create a compartment to file compartment.csv located in cfg/ directory. You can use a spreadsheet editor such as LibreOffice Calc to create the file easily. The delimiter must be ";".
2. Insert the contents of the compartments to the file cfg/compartments (at the moment only single material/radionuclide is supported).
3. Add the variables (compartment names), constants (if any) and equation/transfer function to the file cfg/bin.
4. Compile using the following command "g++ -v *.cpp -o main && ./main" (on Debian 11).
5. The result of the simulation will be writen to file "r.txt".
