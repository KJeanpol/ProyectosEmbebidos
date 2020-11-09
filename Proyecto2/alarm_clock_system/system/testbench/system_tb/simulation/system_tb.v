// system_tb.v

// Generated using ACDS version 20.1 711

`timescale 1 ps / 1 ps
module system_tb (
	);

	wire        system_inst_clk_bfm_clk_clk;       // system_inst_clk_bfm:clk -> [system_inst:clk_clk, system_inst_reset_bfm:clk]
	wire  [3:0] system_inst_h_1_export;            // system_inst:h_1_export -> system_inst_h_1_bfm:sig_export
	wire  [3:0] system_inst_h_2_export;            // system_inst:h_2_export -> system_inst_h_2_bfm:sig_export
	wire  [3:0] system_inst_m_1_export;            // system_inst:m_1_export -> system_inst_m_1_bfm:sig_export
	wire  [3:0] system_inst_m_2_export;            // system_inst:m_2_export -> system_inst_m_2_bfm:sig_export
	wire  [3:0] system_inst_s_1_export;            // system_inst:s_1_export -> system_inst_s_1_bfm:sig_export
	wire  [3:0] system_inst_s_2_export;            // system_inst:s_2_export -> system_inst_s_2_bfm:sig_export
	wire  [4:0] system_inst_set_export;            // system_inst:set_export -> system_inst_set_bfm:sig_export
	wire        system_inst_reset_bfm_reset_reset; // system_inst_reset_bfm:reset -> system_inst:reset_reset_n

	system system_inst (
		.clk_clk       (system_inst_clk_bfm_clk_clk),       //   clk.clk
		.h_1_export    (system_inst_h_1_export),            //   h_1.export
		.h_2_export    (system_inst_h_2_export),            //   h_2.export
		.m_1_export    (system_inst_m_1_export),            //   m_1.export
		.m_2_export    (system_inst_m_2_export),            //   m_2.export
		.reset_reset_n (system_inst_reset_bfm_reset_reset), // reset.reset_n
		.s_1_export    (system_inst_s_1_export),            //   s_1.export
		.s_2_export    (system_inst_s_2_export),            //   s_2.export
		.set_export    (system_inst_set_export)             //   set.export
	);

	altera_avalon_clock_source #(
		.CLOCK_RATE (50000000),
		.CLOCK_UNIT (1)
	) system_inst_clk_bfm (
		.clk (system_inst_clk_bfm_clk_clk)  // clk.clk
	);

	altera_conduit_bfm system_inst_h_1_bfm (
		.sig_export (system_inst_h_1_export)  // conduit.export
	);

	altera_conduit_bfm system_inst_h_2_bfm (
		.sig_export (system_inst_h_2_export)  // conduit.export
	);

	altera_conduit_bfm system_inst_m_1_bfm (
		.sig_export (system_inst_m_1_export)  // conduit.export
	);

	altera_conduit_bfm system_inst_m_2_bfm (
		.sig_export (system_inst_m_2_export)  // conduit.export
	);

	altera_avalon_reset_source #(
		.ASSERT_HIGH_RESET    (0),
		.INITIAL_RESET_CYCLES (50)
	) system_inst_reset_bfm (
		.reset (system_inst_reset_bfm_reset_reset), // reset.reset_n
		.clk   (system_inst_clk_bfm_clk_clk)        //   clk.clk
	);

	altera_conduit_bfm system_inst_s_1_bfm (
		.sig_export (system_inst_s_1_export)  // conduit.export
	);

	altera_conduit_bfm system_inst_s_2_bfm (
		.sig_export (system_inst_s_2_export)  // conduit.export
	);

	altera_conduit_bfm_0002 system_inst_set_bfm (
		.sig_export (system_inst_set_export)  // conduit.export
	);

endmodule
