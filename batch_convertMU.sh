#!/bin/bash
./convertMU -i  MU_density_range_gsz.raw  --inPixelSize 2 2 2 --inMatrixSize 128 128 55 --outPixelSize 4.2 4.2  4.2  --outMatrixSize 96 96 48
echo "convertMU finished!"
exit 
