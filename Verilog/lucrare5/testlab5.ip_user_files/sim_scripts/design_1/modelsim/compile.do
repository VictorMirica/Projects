vlib modelsim_lib/work
vlib modelsim_lib/msim

vlib modelsim_lib/msim/xil_defaultlib

vmap xil_defaultlib modelsim_lib/msim/xil_defaultlib

vlog -work xil_defaultlib -64 -incr \
"../../../bd/design_1/ip/design_1_extragere_0_0/sim/design_1_extragere_0_0.v" \
"../../../bd/design_1/ip/design_1_refacere_0_0/sim/design_1_refacere_0_0.v" \
"../../../bd/design_1/ip/design_1_rezultatFinal_0_0/sim/design_1_rezultatFinal_0_0.v" \
"../../../bd/design_1/ip/design_1_registru16_0_0/sim/design_1_registru16_0_0.v" \
"../../../bd/design_1/ip/design_1_registru16_1_0/sim/design_1_registru16_1_0.v" \
"../../../bd/design_1/ip/design_1_registru48_0_0/sim/design_1_registru48_0_0.v" \
"../../../bd/design_1/ip/design_1_registru48_1_0/sim/design_1_registru48_1_0.v" \
"../../../bd/design_1/ip/design_1_compara_0_0/sim/design_1_compara_0_0.v" \
"../../../bd/design_1/ip/design_1_concatenare_0_0/sim/design_1_concatenare_0_0.v" \
"../../../bd/design_1/ip/design_1_registru57_0_0/sim/design_1_registru57_0_0.v" \
"../../../bd/design_1/ip/design_1_alege_0_0/sim/design_1_alege_0_0.v" \
"../../../bd/design_1/ip/design_1_aliniere_0_0/sim/design_1_aliniere_0_0.v" \
"../../../bd/design_1/ip/design_1_registru8_0_0/sim/design_1_registru8_0_0.v" \
"../../../bd/design_1/ip/design_1_registru8_1_0/sim/design_1_registru8_1_0.v" \
"../../../bd/design_1/ip/design_1_registru8_2_0/sim/design_1_registru8_2_0.v" \
"../../../bd/design_1/ip/design_1_adun_scad_0_0/sim/design_1_adun_scad_0_0.v" \
"../../../bd/design_1/ip/design_1_registru26_0_0/sim/design_1_registru26_0_0.v" \
"../../../bd/design_1/ip/design_1_norm_0_0/sim/design_1_norm_0_0.v" \
"../../../bd/design_1/ip/design_1_ajustare_0_0/sim/design_1_ajustare_0_0.v" \
"../../../bd/design_1/ip/design_1_registru24_0_0/sim/design_1_registru24_0_0.v" \
"../../../bd/design_1/sim/design_1.v" \


vlog -work xil_defaultlib \
"glbl.v"

