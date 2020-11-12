
module system (
	clk_clk,
	h_1_export,
	h_2_export,
	m_1_export,
	m_2_export,
	reset_reset_n,
	s_1_export,
	s_2_export,
	set_export);	

	input		clk_clk;
	output	[3:0]	h_1_export;
	output	[3:0]	h_2_export;
	output	[3:0]	m_1_export;
	output	[3:0]	m_2_export;
	input		reset_reset_n;
	output	[3:0]	s_1_export;
	output	[3:0]	s_2_export;
	input	[4:0]	set_export;
endmodule
