vlib modelsim_lib/work
vlib modelsim_lib/msim

vlib modelsim_lib/msim/util_vector_logic_v2_0_1
vlib modelsim_lib/msim/xil_defaultlib

vmap util_vector_logic_v2_0_1 modelsim_lib/msim/util_vector_logic_v2_0_1
vmap xil_defaultlib modelsim_lib/msim/xil_defaultlib

vlog -work util_vector_logic_v2_0_1 -64 -incr -mfcu \
"../../../../lab1.gen/sources_1/bd/design_2/ipshared/3f90/hdl/util_vector_logic_v2_0_vl_rfs.v" \

vlog -work xil_defaultlib -64 -incr -mfcu \
"../../../bd/design_2/ip/design_2_util_vector_logic_0_0/sim/design_2_util_vector_logic_0_0.v" \
"../../../bd/design_2/ip/design_2_util_vector_logic_1_0/sim/design_2_util_vector_logic_1_0.v" \
"../../../bd/design_2/sim/design_2.v" \

vlog -work xil_defaultlib \
"glbl.v"

