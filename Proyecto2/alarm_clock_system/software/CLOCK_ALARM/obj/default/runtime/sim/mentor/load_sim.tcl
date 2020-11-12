# ------------------------------------------------------------------------------
# Top Level Simulation Script to source msim_setup.tcl
# ------------------------------------------------------------------------------
set QSYS_SIMDIR obj/default/runtime/sim
source msim_setup.tcl
# Copy generated memory initialization hex and dat file(s) to current directory
file copy -force F:/santi/Projects/EMBEBIDOS/alarm_clock_system/software/CLOCK_ALARM/mem_init/hdl_sim/system_RAM.dat ./ 
file copy -force F:/santi/Projects/EMBEBIDOS/alarm_clock_system/software/CLOCK_ALARM/mem_init/system_RAM.hex ./ 
